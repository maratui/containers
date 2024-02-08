#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_SET_CONST_ITERATOR_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_SET_CONST_ITERATOR_H

#include "./s21_map_const_iterator.h"

namespace s21 {
template <class T>
class SetConstIterator : public s21::MapConstIterator<T, T> {
 public:
  using key_type = T;
  using value_type = T;
  using const_reference = const value_type &;
  using item_type = const struct RBTNode<T, T>;

  SetConstIterator() = delete;
  explicit SetConstIterator(item_type *item_ptr)
      : MapConstIterator<T, T>(item_ptr) {}
  explicit SetConstIterator(item_type *item_ptr, item_type *root_ptr)
      : MapConstIterator<T, T>(item_ptr, root_ptr) {}
  ~SetConstIterator() {}

  friend const_reference operator*(SetConstIterator &i) noexcept {
    if (i.item_ptr_ == nullptr) --i;
    const_reference ret = i.item_ptr_->value.second;

    return ret;
  }
  friend const_reference operator*(SetConstIterator &&i) noexcept {
    const_reference ret = *i;

    return ret;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_SET_CONST_ITERATOR_H
