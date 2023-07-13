#ifndef S21_MAP_ITERATOR_H
#define S21_MAP_ITERATOR_H

#include "../s21_associative_containers/s21_rbtree.h"
#include "./s21_iterator.h"

namespace s21 {

template <class K, class T>
class MapIterator
    : public s21::Iterator<std::pair<const K, T>, struct RBTNode<K, T>> {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using item_type = struct RBTNode<K, T>;

  MapIterator() = delete;

  explicit MapIterator(item_type *item_ptr) { this->item_ptr_ = item_ptr; }
  explicit MapIterator(item_type *item_ptr, item_type *root_ptr) {
    this->item_ptr_ = item_ptr;
    root_ptr_ = root_ptr;
  }

  ~MapIterator() {}

  operator MapConstIterator<K, T>() {
    MapConstIterator<K, T> const_iterator(this->item_ptr_);

    return const_iterator;
  }

 protected:
  using reference = value_type &;

  reference Asterisc_() noexcept override {
    reference ret = (*this->item_ptr_).value;

    return ret;
  }

  void Next_() noexcept override {
    if (this->item_ptr_ != nullptr) {
      this->item_ptr_ = this->item_ptr_->Next();
    }
  }

  void Prev_() noexcept override {
    if (this->item_ptr_ != nullptr) {
      this->item_ptr_ = this->item_ptr_->Prev();
    } else {
      this->item_ptr_ = root_ptr_;
      while (this->item_ptr_->ptrs->right != nullptr) {
        this->item_ptr_ = this->item_ptr_->ptrs->right;
      }
    }
  }

  item_type *root_ptr_ = nullptr;
};
}  // namespace s21

#endif  // S21_MAP_ITERATOR_H
