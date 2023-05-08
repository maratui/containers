#ifndef SRC_S21_VECTORCONSTITERATOR_H
#define SRC_S21_VECTORCONSTITERATOR_H

#include "./s21_vector_iterator.h"

namespace S21 {
template <class T>
class VectorConstIterator : public VectorIterator<const T> {
  using const_value_type = const T;

 public:
  VectorConstIterator() : VectorIterator() {}

  VectorConstIterator(const_value_type *ptr) : VectorIterator<const T>(ptr) {}

  ~VectorConstIterator() {}
};
}  // namespace S21

#endif  // SRC_S21_VECTORCONSTITERATOR_H
