#ifndef S21_VECTOR_CONST_ITERATOR_H
#define S21_VECTOR_CONST_ITERATOR_H

#include "./s21_iterator.h"

namespace s21 {
template <class T>
class VectorConstIterator : public s21::Iterator<const T, const T> {
 public:
  using value_type = const T;

  VectorConstIterator() = delete;

  explicit VectorConstIterator(value_type *item_ptr) {
    this->item_ptr_ = item_ptr;
  }

  ~VectorConstIterator() {}

 protected:
  using const_reference = const T &;

  const_reference Asterisc_() noexcept override {
    const_reference ret = *this->item_ptr_;

    return ret;
  }

  void Next_() noexcept override { this->item_ptr_ += 1; }

  void Prev_() noexcept override { this->item_ptr_ -= 1; }
};
}  // namespace s21

#endif  // S21_VECTOR_CONST_ITERATOR_H
