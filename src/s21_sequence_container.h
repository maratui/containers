#ifndef SRC_S21_SEQUENCE_CONTAINER_H
#define SRC_S21_SEQUENCE_CONTAINER_H

#include <iostream>
#include <memory>
#include <stdexcept>

namespace S21 {
template <class T, class I, class CI, class A>
class SequenceContainer {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = I;
  using const_iterator = CI;
  using size_type = size_t;

 public:
  explicit SequenceContainer() {}

  explicit SequenceContainer(size_type n) : size_(n), head_(A::Allocate(n)), tail_(A::SetTail(head_, n)) {}

  explicit SequenceContainer(std::initializer_list<value_type> const &items)
      : SequenceContainer(items.size()) {
    InitializeContainer_(items);
  }

  SequenceContainer(const SequenceContainer &sc, const size_type capacity) : size_(sc.size_), head_(A::Allocate(capacity)), tail_(A::SetTail(head_, size_)) {
    CopyContainer_(sc);
  }

  SequenceContainer(SequenceContainer &&sc) : size_(sc.size_), head_(sc.head_), tail_(sc.tail_) {
    sc.size_ = 0;
    sc.head_ = nullptr;
    sc.tail_ = nullptr;
  }

  ~SequenceContainer() {A::Delete(head_);}

  SequenceContainer &operator=(const SequenceContainer &sc) {
    if (this != &sc) {
      A::Delete(head_);
      size_ = sc.size_;
      head_ = A::Allocate(size_);
      tail_ = A::SetTail(head_, size_);
      CopyContainer_(sc);
    }

    return *this;
  }
/*

  SequenceContainer(SequenceContainer &&v) { *this = std::move(v); }

  SequenceContainer &operator=(SequenceContainer &&v) noexcept {
    iterator iter;

    DeleteContainer_();
    if (this != &v) {
      SetProtectedFields_(v.size_, v.capacity_, &v.container_);
      v.SetProtectedFields_(0U, 0U, &iter);
    } else {
      SetProtectedFields_(0U, 0U, &iter);
    }

    return *this;
  }

  reference Front() noexcept { return *Begin(); }
  const_reference Front() const noexcept { return *Begin(); }

  reference Back() noexcept { return *(--End()); }
  const_reference Back() const noexcept { return *(--End()); }
*/
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
/*
  bool Empty() const noexcept { return size_ == 0; }
*/
  size_type Size() const noexcept { return size_; }
/*
  void Erase(iterator pos) noexcept {
    auto end = --End();
    for (auto iter = pos; iter < end; ++iter) *iter = *(iter + 1);
    size_ -= 1;
  }

  void PopBack() noexcept { Erase(--End()); }

  void Swap(SequenceContainer &other) {
    SequenceContainer vector(other);

    other = std::move(*this);
    *this = std::move(vector);
  }
*/
 protected:
  size_type size_ = 0;
  value_type *head_ = nullptr;
  value_type *tail_ = nullptr;

 private:
/*
  void CreatContainer_() {
    if (capacity_ > 0) {
      container_.Create(capacity_);
      const_container_.Create(capacity_);
    }
  }
*/
  void InitializeContainer_(
      std::initializer_list<value_type> const &items) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = items.begin(), end = items.end(); item < end;
           item++, ++iter)
        *iter = *item;
  }
/*
  void DeleteContainer_() noexcept { container_.Delete(); }

  void SetProtectedFields_(size_type size, size_type capacity,
                           I *head) noexcept {
    size_ = size;
    capacity_ = capacity;
    if (head) container_ = *head;
  }
*/
  void CopyContainer_(const SequenceContainer &sc) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = sc.Begin(), end = sc.End(); item < end; ++item, ++iter)
        *iter = *item;
  }
};
}  // namespace S21

#endif  // SRC_S21_SEQUENCE_CONTAINER_H
