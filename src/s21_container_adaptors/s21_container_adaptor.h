#ifndef S21_CONTAINER_ADAPTOR_H
#define S21_CONTAINER_ADAPTOR_H

#include <memory>

#include "../s21_allocators/s21_list_allocator.h"

namespace s21 {
template <class T>
class ContainerAdaptor {
 public:
  using value_type = T;
  using const_reference = const T &;
  using item_type = struct Item<T>;
  using size_type = std::size_t;

  bool empty() const noexcept {
    bool ret = (head_ == nullptr);

    return ret;
  }

  constexpr size_type size() const noexcept { return size_; }

  virtual void push(const_reference value) = 0;

  void pop() noexcept {
    if (!empty()) {
      item_type *delete_item = head_;
      head_ = head_->next;
      if (head_ != nullptr) head_->prev = nullptr;
      delete delete_item;
      size_ -= 1;
    }
  }

 protected:
  size_type size_ = 0U;
  item_type *head_ = nullptr;

  void InitializeContainer_(
      std::initializer_list<value_type> const &items) noexcept {
    for (auto item = items.begin(), end = items.end(); item != end; ++item)
      push(*item);
  }

  virtual void CheckMaxSize_(size_type size) = 0;

  constexpr size_type MaxSize_() const noexcept {
    std::allocator<item_type> alloc;

    return alloc.max_size();
  }
};
}  // namespace s21

#endif  // S21_CONTAINER_ADAPTOR_H
