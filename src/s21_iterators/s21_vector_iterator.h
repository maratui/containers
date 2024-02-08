#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_VECTOR_ITERATOR_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_VECTOR_ITERATOR_H

#include "./s21_iterator.h"

namespace s21 {

template <class T>
class VectorIterator : public s21::Iterator<T, T> {
 public:
  using value_type = T;

  VectorIterator() = delete;

  explicit VectorIterator(value_type *item_ptr) { this->item_ptr_ = item_ptr; }

  ~VectorIterator() {}

  operator VectorConstIterator<T>() {
    VectorConstIterator<T> const_iterator(this->item_ptr_);

    return const_iterator;
  }

 protected:
  using reference = T &;

  reference Asterisc() noexcept override {
    reference ret = *this->item_ptr_;

    return ret;
  }

  void Next() noexcept override { this->item_ptr_ += 1; }

  void Prev() noexcept override { this->item_ptr_ -= 1; }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_VECTOR_ITERATOR_H
