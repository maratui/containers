#ifndef S21_LIST_ITERATOR_H
#define S21_LIST_ITERATOR_H

#include "../s21_allocators/s21_list_allocator.h"
#include "./s21_iterator.h"

namespace s21 {

template <class T>
class ListIterator : public s21::Iterator<T, struct Item<T>> {
 public:
  using item_type = struct Item<T>;

  ListIterator() = delete;

  explicit ListIterator(item_type *item_ptr) { this->item_ptr_ = item_ptr; }

  ~ListIterator() {}

  operator ListConstIterator<T>() {
    ListConstIterator<T> const_iterator(this->item_ptr_);

    return const_iterator;
  }

 protected:
  using reference = T &;

  reference Asterisc_() noexcept override {
    reference ret = (*this->item_ptr_).value;

    return ret;
  }

  void Next_() noexcept override { this->item_ptr_ = this->item_ptr_->next; }

  void Prev_() noexcept override { this->item_ptr_ = this->item_ptr_->prev; }
};
}  // namespace s21

#endif  // S21_LIST_ITERATOR_H
