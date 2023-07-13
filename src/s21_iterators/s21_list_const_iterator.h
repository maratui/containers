#ifndef S21_LIST_CONST_ITERATOR_H
#define S21_LIST_CONST_ITERATOR_H

#include "../s21_allocators/s21_list_allocator.h"
#include "./s21_iterator.h"

namespace s21 {
template <class T>
class ListConstIterator : public s21::Iterator<const T, const struct Item<T>> {
 public:
  using item_type = const struct Item<T>;

  ListConstIterator() = delete;

  explicit ListConstIterator(item_type *item_ptr) {
    this->item_ptr_ = item_ptr;
  }

  ~ListConstIterator() {}

 protected:
  using const_reference = const T &;

  const_reference Asterisc_() noexcept override {
    const_reference ret = (*this->item_ptr_).value;

    return ret;
  }

  void Next_() noexcept override { this->item_ptr_ = this->item_ptr_->next; }

  void Prev_() noexcept override { this->item_ptr_ = this->item_ptr_->prev; }
};
}  // namespace s21

#endif  // S21_LIST_CONST_ITERATOR_H
