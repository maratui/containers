#ifndef S21_MAP_CONST_ITERATOR_H
#define S21_MAP_CONST_ITERATOR_H

#include "../s21_associative_containers/s21_rbtree.h"
#include "./s21_iterator.h"

namespace s21 {
template <class K, class T>
class MapConstIterator : public s21::Iterator<const std::pair<const K, T>,
                                              const struct RBTNode<K, T>> {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = const std::pair<const key_type, mapped_type>;
  using item_type = const struct RBTNode<K, T>;

  MapConstIterator() = delete;

  explicit MapConstIterator(item_type *item_ptr) { this->item_ptr_ = item_ptr; }
  explicit MapConstIterator(item_type *item_ptr, item_type *root_ptr) {
    this->item_ptr_ = item_ptr;
    root_ptr_ = root_ptr;
  }

  ~MapConstIterator() {}

 protected:
  using const_reference = const value_type &;

  const_reference Asterisc_() noexcept override {
    const_reference ret = (*this->item_ptr_).value;

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

  const item_type *root_ptr_ = nullptr;
};
}  // namespace s21

#endif  // S21_MAP_CONST_ITERATOR_H
