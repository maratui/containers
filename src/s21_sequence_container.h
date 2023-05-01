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
  SequenceContainer() {}

  explicit SequenceContainer(I (*CreatContainer)(I array, size_type n),
                             size_type n)
      : size_(n), capacity_(n) {
    array_ = CreatContainer(array_, n);
  }

  explicit SequenceContainer(I (*CreatContainer)(I array, size_type n),
                             std::initializer_list<value_type> const &items)
      : SequenceContainer(CreatContainer, items.size()) {
    InitializeSequenceContainer_(items);
  }

  SequenceContainer &Copy(I (*CreatContainer)(I array, size_type n),
                          const SequenceContainer &v) {
    if (this != &v) {
      SetPrivateFields_(v.size_, v.capacity_,
                        CreatContainer(array_, v.capacity_));
      CopySequenceContainer_(v);
    }

    return *this;
  }

  SequenceContainer &Move(I (*CreatContainer)(I array, size_type n),
                          SequenceContainer &v) noexcept {
    array_ = CreatContainer(array_, 0);
    if (this != &v) {
      SetPrivateFields_(v.size_, v.capacity_, v.Begin());
      v.SetPrivateFields_(0U, 0U, nullptr);
    } else {
      SetPrivateFields_(0U, 0U, nullptr);
    }

    return *this;
  }

  reference Front() noexcept { return *Begin(); }
  const_reference Front() const noexcept { return *Begin(); }

  reference Back() noexcept { return *(End() - 1); }
  const_reference Back() const noexcept { return *(End() - 1); }

  iterator Begin() noexcept { return array_; }
  const_iterator Begin() const noexcept { return array_; }

  iterator End() noexcept { return array_ + size_; }
  const_iterator End() const noexcept { return array_ + size_; }

  bool Empty() const noexcept { return size_ == 0; }

  size_type Size() const noexcept { return size_; }

  size_type MaxSize() const noexcept {
    std::allocator<value_type> alloc;

    return alloc.max_size();
  }

  void Clear() noexcept { size_ = 0; }

  iterator Insert(iterator pos, const_reference value) {
    auto begin = Begin();
    auto end = End();
    if ((size_ == 0) || (pos >= begin && pos <= end)) {
      InsertReserve_(begin, end, pos);
      for (auto iter = end; iter > pos; --iter) *iter = *(iter - 1);
      *pos = value;
      size_ += 1;
    }

    return pos;
  }

  void Erase(iterator pos) noexcept {
    auto end = End() - 1;
    for (auto iter = pos; iter < end; iter++) *iter = *(iter + 1);
    size_ -= 1;
  }

  void PushBack(const_reference value) { Insert(End(), value); }

  void PopBack() noexcept { Erase(End() - 1); }

  void Swap(SequenceContainer &other) {
    SequenceContainer vector(other);

    other = std::move(*this);
    *this = std::move(vector);
  }

 protected:
  size_type size_ = 0;
  size_type capacity_ = 0;
  I array_ = nullptr;

  void SetPrivateFields_(size_type size, size_type capacity, I begin) {
    size_ = size;
    capacity_ = capacity;
    array_ = begin;
  }

  void InitializeSequenceContainer_(
      std::initializer_list<value_type> const &items) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = items.begin(), end = items.end(); item < end;
           item++, iter++)
        *iter = *item;
  }

  void InsertReserve_(I begin, I end, I pos) {
    if (size_ == capacity_) {
      if (capacity_ > 0)
        capacity_ *= 2;
      else
        capacity_ = 1;
      //Reserve_(capacity_);
      end = End();
      pos += Begin() - begin;
    }
  }


 private:
  void CopySequenceContainer_(const SequenceContainer &v) noexcept {
    auto iter = Begin();
    if (iter != End()) {
      for (auto item = v.Begin(), end = v.End(); item < end; item++, iter++)
        *iter = *item;
    }
  }
  /*
      void CheckSizeBounds_(size_type pos) const {
        if (pos >= size_)
          throw std::out_of_range(
              "Incorrect input, index is outside the vector size");
      }
    */
};
}  // namespace S21

#endif  // SRC_S21_SEQUENCE_CONTAINER_H
