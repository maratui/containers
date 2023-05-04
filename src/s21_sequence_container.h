#ifndef SRC_S21_SEQUENCE_CONTAINER_H
#define SRC_S21_SEQUENCE_CONTAINER_H

#include <iostream>
#include <memory>
#include <stdexcept>

namespace S21 {
template <class T, class I>
class SequenceContainer {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = I;
  using const_iterator = const I;
  using size_type = size_t;

 public:
  explicit SequenceContainer(bool list = false) : list_(list) {}

  explicit SequenceContainer(size_type n, bool list = false)
      : size_(n), capacity_(n), list_(list) {
    CreatContainer_();
  }

  explicit SequenceContainer(std::initializer_list<value_type> const &items,
                             bool list = false)
      : SequenceContainer(items.size(), list) {
    InitializeContainer_(items);
  }

  ~SequenceContainer() {}

  SequenceContainer &Copy(SequenceContainer &v) {
    if (this != &v) {
      DeleteContainer_();
      SetProtectedFields_(v.size_, v.capacity_, array_);
      CreatContainer_();
      CopyContainer_(v);
    }

    return *this;
  }

  SequenceContainer &Move(SequenceContainer &v) noexcept {
    DeleteContainer_();
    if (this != &v) {
      SetProtectedFields_(v.size_, v.capacity_, v.array_);
      v.SetProtectedFields_(0U, 0U, I());
    } else {
      SetProtectedFields_(0U, 0U, I());
    }

    return *this;
  }

  reference Front() noexcept { return *Begin(); }
  const_reference Front() const noexcept { return *Begin(); }

  reference Back() noexcept { return *(--End()); }
  const_reference Back() const noexcept { return *(--End()); }

  iterator Begin() noexcept {
    iterator ret;

    ret = array_.Head();

    return ret;
  }
//  const_iterator Begin() const noexcept { return array_.Head(); }

  iterator End() noexcept {
    iterator ret;

    ret = array_.Tail();

    return ret;
  }
//  const_iterator End() const noexcept { return array_.Tail(); }

  bool Empty() const noexcept { return size_ == 0; }

  size_type Size() const noexcept { return size_; }

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

 protected:
  size_type size_ = 0;
  size_type capacity_ = 0;
  I array_;

 private:
  bool list_ = false;

  void CreatContainer_() {
    if (capacity_ > 0) array_.Create(capacity_);
  }

  void InitializeContainer_(
      std::initializer_list<value_type> const &items) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = items.begin(), end = items.end(); item < end;
           item++, ++iter)
        *iter = *item;
  }

  void DeleteContainer_() noexcept { array_.Delete(); }

  void SetProtectedFields_(size_type size, size_type capacity,
                           I begin) noexcept {
    size_ = size;
    capacity_ = capacity;
    array_ = begin;
  }

  void CopyContainer_(SequenceContainer &v) noexcept {
    iterator iter;

    iter = Begin();
    if (iter != End()) {
      for (auto item = v.Begin(), end = v.End(); item < end; ++item, ++iter) {
        *iter = *item;
      }
    }
  }
};
}  // namespace S21

#endif  // SRC_S21_SEQUENCE_CONTAINER_H
