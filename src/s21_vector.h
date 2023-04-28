#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <memory>
#include <stdexcept>

#include "./s21_sequence_container.h"

namespace S21 {
template <class T>
class Vector : public SequenceContainer {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  Vector() {}

  explicit Vector(size_type n) : SequenceContainer(n) {}

  explicit Vector(std::initializer_list<value_type> const &items) : SequenceContainer(items) {}

  Vector(const Vector &v) : SequenceContainer(v) {}

  Vector(Vector &&v) : SequenceContainer(v) noexcept {}

  ~Vector() { delete[] array_; }

  reference At(size_type pos) {
    CheckSizeBounds_(pos);

    return array_[pos];
  }
  const_reference At(size_type pos) const {
    CheckSizeBounds_(pos);

    return array_[pos];
  }

  reference operator[](size_type pos) noexcept { return array_[pos]; }
  const_reference operator[](size_type pos) const noexcept {
    return array_[pos];
  }

  T *Data() noexcept { return array_; }
  const T *Data() const noexcept { return array_; }

  void Reserve(size_type size) {
    if (size > capacity_) Reserve_(size);
  }

  size_type Capacity() const noexcept { return capacity_; }

  void ShrinkToFit() {
    if (capacity_ > size_) Reserve_(size_);
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

  void CopyVector_(const Vector &v) noexcept {
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

  void Reserve_(size_type size) {
    Vector vector(size);

    vector.CopyVector_(*this);
    *this = std::move(vector);
  }
};
}  // namespace S21

#endif  // SRC_S21_VECTOR_H
