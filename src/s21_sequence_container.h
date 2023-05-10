#ifndef SRC_S21_SEQUENCE_CONTAINER_H
#define SRC_S21_SEQUENCE_CONTAINER_H

#include <stdexcept>
#include <tuple>

namespace S21 {
template <class T, class I, class CI, class A>
class SequenceContainer {
  using item_type = A;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = I;
  using const_iterator = CI;
  using size_type = size_t;

 public:
  explicit SequenceContainer() {}

  explicit SequenceContainer(size_type n) : size_(n), capacity_(n) {
    std::tie(head_, tail_) = A::Allocate(size_, capacity_);
  }

  explicit SequenceContainer(std::initializer_list<value_type> const &items)
      : SequenceContainer(items.size()) {
    InitializeContainer_(items);
  }

  SequenceContainer(const SequenceContainer &sc)
      : size_(sc.size_), capacity_(sc.capacity_) {
    std::tie(head_, tail_) = A::Allocate(size_, capacity_);
    CopyContainer_(sc);
  }

  SequenceContainer(SequenceContainer &&sc) noexcept { *this = std::move(sc); }

  ~SequenceContainer() { A::Delete(head_); }

  SequenceContainer &operator=(const SequenceContainer &sc) {
    if (this != &sc) *this = SequenceContainer(sc);

    return *this;
  }

  SequenceContainer &operator=(SequenceContainer &&sc) noexcept {
    A::Delete(head_);
    if (this != &sc) {
      SetProtectedFields_(sc.size_, sc.capacity_, sc.head_, sc.tail_);
      sc.SetProtectedFields_(0U, 0U, nullptr, nullptr);
    } else {
      SetProtectedFields_(0U, 0U, nullptr, nullptr);
    }

    return *this;
  }

  reference At(size_type pos) {
    CheckSizeBounds_(pos);

    return (*this)[pos];
  }
  const_reference At(size_type pos) const {
    CheckSizeBounds_(pos);

    return (*this)[pos];
  }

  reference operator[](size_type pos) noexcept {
    iterator iter;

    iter = Begin();
    iter = iter + pos;

    return *iter;
  }

  const_reference operator[](size_type pos) const noexcept {
    const_iterator iter;

    iter = Begin();
    iter = iter + pos;

    return *iter;
  }

  reference Front() noexcept { return *Begin(); }
  const_reference Front() const noexcept { return *Begin(); }

  reference Back() noexcept { return *(--End()); }
  const_reference Back() const noexcept { return *(--End()); }

  iterator Begin() noexcept {
    iterator ret(head_);

    return ret;
  }
  const_iterator Begin() const noexcept {
    const_iterator ret(head_);

    return ret;
  }

  iterator End() noexcept {
    iterator ret(tail_);

    return ret;
  }
  const_iterator End() const noexcept {
    const_iterator ret(tail_);

    return ret;
  }

  size_type MaxSize() const noexcept {
    std::allocator<item_type> alloc;

    return alloc.max_size();
  }

  bool Empty() const noexcept { return size_ == 0; }

  size_type Size() const noexcept { return size_; }

  size_type Capacity() const noexcept { return capacity_; }

  void Clear() noexcept {
    size_ = 0;
    tail_ = A::SetTail(head_, size_);
  }

  iterator Insert(iterator pos, const_reference value) {
    iterator begin;
    iterator end;

    begin = Begin();
    end = End();
    if ((size_ == 0) || (pos >= begin && pos <= end)) {
      std::tie(size_, capacity_, head_, tail_) =
          A::Append(size_, capacity_, head_, tail_);
      end = End();
      pos = Begin() + (pos - begin);
      for (auto iter = end - 1; iter > pos; --iter) *iter = *(iter - 1);
      *pos = value;
    }

    return pos;
  }

  void Erase(iterator pos) noexcept {
    auto end = --End();
    for (auto iter = pos; iter < end; ++iter) *iter = *(iter + 1);
    size_ -= 1;
    tail_ = A::SetTail(head_, size_);
  }

  void PushBack(const_reference value) { Insert(End(), value); }

  void PopBack() noexcept { Erase(--End()); }

  void PushFront(const_reference value) { Insert(Begin(), value); }

  void PopFront() noexcept { Erase(Begin()); }

  void Swap(SequenceContainer &other) {
    SequenceContainer sc(other);

    other = std::move(*this);
    *this = std::move(sc);
  }

  void reverse() noexcept {
    auto iter = Begin();
    auto end = End();

    if (iter != end) {
      auto size = size_;
      --end;
      for (size_type i = 0; i < size; i++, --end, ++iter) {
        auto temp = *iter;
        *iter = *end;
        *end = temp;
        size--;
      }
    }
  }

  void Unique() noexcept {
    auto iter = Begin();
    auto end = End();

    if (iter != end) {
      ++iter;
      for (size_type i = 1; i < size_; i++, ++iter) {
        if (*iter == *(iter - 1)) {
          Erase(iter);
          iter = Begin();
          for (size_type k = 0; k < i; k++, ++iter) {
          }
        }
      }
    }
  }

  void Sort() noexcept {
    auto iter = Begin();
    auto end = End();

    if (iter != end) {
      for (size_type i = 0; i < size_ - 1; i++) {
        for (size_type j = 0; j < size_ - i - 1; j++, ++iter) {
          if (*iter > *(iter + 1)) {
            auto temp = *iter;
            *iter = *(iter + 1);
            *(iter + 1) = temp;
          }
        }
        iter = Begin();
      }
    }
  }

 protected:
  size_type size_ = 0U;
  size_type capacity_ = 0U;
  item_type *head_ = nullptr;
  item_type *tail_ = nullptr;

 private:
  void InitializeContainer_(
      std::initializer_list<value_type> const &items) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = items.begin(), end = items.end(); item < end;
           item++, ++iter)
        *iter = *item;
  }

  void SetProtectedFields_(size_type size, size_type capacity, item_type *head,
                           item_type *tail) noexcept {
    size_ = size;
    capacity_ = capacity;
    head_ = head;
    tail_ = tail;
  }

  void CopyContainer_(const SequenceContainer &sc) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = sc.Begin(), end = sc.End(); item < end; ++item, ++iter)
        *iter = *item;
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= this->size_)
      throw std::out_of_range(
          "Incorrect input, index is outside the vector size");
  }
};
}  // namespace S21

#endif  // SRC_S21_SEQUENCE_CONTAINER_H
