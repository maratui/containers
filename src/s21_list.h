#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H

#include <stdexcept>

#include "./s21_sequence_container.h"
#include "./s21_list_allocate.h"
#include "./s21_list_iterator.h"

namespace S21 {
template <class T>
class Vector
    : public SequenceContainer<T, ListIterator<T>, ListIterator<const T>,
                               ListAllocate<T>> {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListIterator<const T>;
  using size_type = size_t;
  using LA = ListAllocate<T>;
  using SC = SequenceContainer<T, ListIterator<T>, ListIterator<const T>,
                               ListAllocate<T>>;

 public:
  List() : SC() {}

  explicit List(size_type n) : SC(n) {}

  explicit List(std::initializer_list<value_type> const &items)
      : SC(items) {}

  List(const List &l) : SC(l) {}

  List(List &&v) noexcept { *this = std::move(l); }

  ~List() {}

  List &operator=(const List &v) {
    if (this != &l) *this = List(l);

    return *this;
  }

  List &operator=(List &&l) noexcept {
    LA::Delete(this->head_);
    if (this != &l) {
      SetProtectedFields_(l.size_, l.head_, l.tail_);
      l.SetProtectedFields_(0U, nullptr, nullptr);
    } else {
      SetProtectedFields_(0U, nullptr, nullptr);
    }

    return *this;
  }

  reference At(size_type pos) {
    iterator iter;

    CheckSizeBounds_(pos);

    iter = this->Begin();
    iter = iter + pos;

    return *iter;
  }
  const_reference At(size_type pos) const {
    const_iterator iter;

    CheckSizeBounds_(pos);

    iter = this->Begin();
    iter = iter + pos;

    return *iter;
  }

  reference operator[](size_type pos) noexcept {
    iterator iter;

    iter = this->Begin();
    iter = iter + pos;

    return *iter;
  }

  const_reference operator[](size_type pos) const noexcept {
    const_iterator iter;

    iter = this->Begin();
    iter = iter + pos;

    return *iter;

  }

  T *Data() noexcept { return this->head_; }
  const T *Data() const noexcept { return this->head_; }

  size_type MaxSize() const noexcept {
    std::allocator<value_type> alloc;

    return alloc.max_size();
  }
/*
  void Clear() noexcept {
    this->size_ = 0;
    this->tail_ = VA::SetTail(this->head_, this->size_);
  }
*/
  iterator Insert(iterator pos, const_reference value) {
    iterator begin;
    iterator end;

    begin = this->Begin();
    end = this->End();
    if ((this->size_ == 0) || (pos >= begin && pos <= end)) {

        LA::AddNewItem(this->tail_);
        end = this->End();

      for (auto iter = end - 1; iter > pos; --iter) *iter = *(iter - 1);
      *pos = value;
      this->size_ += 1;
    }

    return pos;
  }

  void PushBack(const_reference value) { Insert(this->End(), value); }

  void Swap(List &other) {
    SC::Swap(other, other.size_);
  }

 private:
  void SetProtectedFields_(size_type size, value_type *head, value_type *tail) noexcept {
    this->size_ = size;
    this->head_ = head;
    this->tail_ = tail;
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= this->size_)
      throw std::out_of_range(
          "Incorrect input, index is outside the vector size");
  }
};
}  // namespace S21

#endif  // SRC_S21_LIST_H
