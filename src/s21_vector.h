#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include "./s21_sequence_container.h"
#include "./s21_vector_allocate.h"
#include "./s21_vector_const_iterator.h"
#include "./s21_vector_iterator.h"

namespace S21 {
template <class T>
class Vector
    : public SequenceContainer<T, VectorIterator<T>, VectorConstIterator<T>,
                               VectorAllocate<T>> {
  using value_type = T;
  using size_type = size_t;
  using SC = SequenceContainer<T, VectorIterator<T>, VectorConstIterator<T>,
                               VectorAllocate<T>>;

 public:
  Vector() : SC() {}

  explicit Vector(size_type n) : SC(n) {}

  explicit Vector(std::initializer_list<value_type> const &items) : SC(items) {}

  Vector(const Vector &v) : SC(v) {}

  Vector(Vector &&v) noexcept : SC(std::move(v)) {}

  ~Vector() {}

  Vector &operator=(const Vector &v) { return (Vector &)SC::operator=(v); }

  Vector &operator=(Vector &&v) noexcept {
    return (Vector &)SC::operator=(std::move(v));
  }

  T *Data() noexcept { return (T *)this->head_; }
  const T *Data() const noexcept { return (T *)this->head_; }

  void Reserve(size_type size) {
    if (size > this->capacity_) Reserve_(size);
  }

  void ShrinkToFit() {
    if (this->capacity_ > this->size_) Reserve_(this->size_);
  }

 private:
  void Reserve_(size_type size) {
    Vector vector(size);

    vector.CopyVector_(*this);
    *this = std::move(vector);
  }

  void CopyVector_(const Vector &v) noexcept {
    int m;

    m = std::min(v.size_, std::min(this->capacity_, v.capacity_));
    for (auto j = 0; j < m; j++) this->head_[j] = v.head_[j];

    this->size_ = m;
    this->tail_ = VectorAllocate<T>::SetTail(this->head_, this->size_);
  }
};
}  // namespace S21

#endif  // SRC_S21_VECTOR_H
