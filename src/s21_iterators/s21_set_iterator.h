#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_SET_ITERATOR_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_SET_ITERATOR_H

#include "./s21_set_const_iterator.h"

namespace s21 {
template <class T>
class SetIterator : public s21::SetConstIterator<T> {
 public:
  using key_type = T;
  using value_type = T;
  using const_reference = const value_type &;
  using item_type = const struct RBTNode<T, T>;

  SetIterator() = delete;
  explicit SetIterator(item_type *item_ptr) : SetConstIterator<T>(item_ptr) {}
  explicit SetIterator(item_type *item_ptr, item_type *root_ptr)
      : SetConstIterator<T>(item_ptr, root_ptr) {}
  ~SetIterator() {}
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_SET_ITERATOR_H
