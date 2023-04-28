#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <memory>
#include <stdexcept>

namespace S21 {
template <class T>
class SequenceContainer {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  SequenceContainer() {}

  explicit SequenceContainer(size_type n) { SetPrivateFields_(n, n, nullptr); }

  explicit SequenceContainer(std::initializer_list<value_type> const &items) {
    SetPrivateFields_(items.size(), items.size(), nullptr);
    if (array_) {
      auto iter = Begin();
      for (auto item = items.begin(), end = items.end(); item < end;
           item++, iter++)
        *iter = *item;
    }
  }

  SequenceContainer(const SequenceContainer &v) { *this = v; }

  SequenceContainer(SequenceContainer &&v) noexcept { *this = std::move(v); }

  ~SequenceContainer() { delete[] array_; }

  SequenceContainer &operator=(const SequenceContainer &v) {
    if (this != &v) {
      delete[] array_;
      SetPrivateFields_(v.size_, v.capacity_, nullptr);
      CopySequenceContainer_(v);
    }

    return *this;
  }

  SequenceContainer &operator=(SequenceContainer &&v) noexcept {
    delete[] array_;
    if (this != &v) {
      SetPrivateFields_(v.size_, v.capacity_, v.array_);
      v.SetPrivateFields_(0U, 0U, nullptr);
    } else {
      SetPrivateFields_(0U, 0U, nullptr);
    }

    return *this;
  }

  reference Front() noexcept { return array_[0]; }
  const_reference Front() const noexcept { return array_[0]; }

  reference Back() noexcept { return array_[size_ - 1]; }
  const_reference Back() const noexcept { return array_[size_ - 1]; }

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
    if ((capacity_ == 0) || (pos >= begin && pos <= end)) {
      if (size_ == capacity_) {
        if (capacity_ > 0)
          capacity_ *= 2;
        else
          capacity_ = 1;
        Reserve_(capacity_);
        end = End();
        pos += Begin() - begin;
      }
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

 private:
  size_type size_ = 0;
  size_type capacity_ = 0;
  value_type *array_ = nullptr;

  void SetPrivateFields_(size_type size, size_type capacity,
                         value_type *array) {
    size_ = size;
    capacity_ = capacity;
    array_ = array;
    if (!array_ && capacity_) array_ = new value_type[capacity_]{};
  }

  void CopySequenceContainer_(const SequenceContainer &v) noexcept {
    int m;

    m = std::min(v.size_, std::min(capacity_, v.capacity_));
    if (array_) {
      for (auto j = 0; j < m; j++) array_[j] = v.array_[j];
      size_ = m;
    }
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= size_)
      throw std::out_of_range(
          "Incorrect input, index is outside the vector size");
  }
};
}  // namespace S21

#endif  // SRC_S21_VECTOR_H
