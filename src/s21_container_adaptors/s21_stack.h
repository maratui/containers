#ifndef S21_STACK_H
#define S21_STACK_H

#include <stdexcept>

#include "./s21_container_adaptor.h"

namespace s21 {
template <class T>
class stack : public ContainerAdaptor<T> {
 public:
  using value_type = T;
  using const_reference = const T &;
  using reference = T &;
  using item_type = struct Item<T>;
  using size_type = std::size_t;

  stack() {}

  explicit stack(std::initializer_list<value_type> const &items) {
    this->InitializeContainer_(items);
  }

  stack(const stack &s) { CopyContainer_(s); }

  stack(stack &&s) noexcept { *this = std::move(s); }

  ~stack() {
    while (!this->empty()) this->pop();
  }

  stack &operator=(stack &&s) noexcept {
    while (!this->empty()) this->pop();
    if (this != &s) {
      SetProtectedFields_(s.size_, s.head_);
      s.SetProtectedFields_(0U, nullptr);
    } else {
      SetProtectedFields_(0U, nullptr);
    }

    return *this;
  }

  reference top() noexcept {
    reference ret = (*this->head_).value;

    return ret;
  }
  const_reference top() const noexcept {
    const_reference ret = (*this->head_).value;

    return ret;
  }

  void push(const_reference value) override {
    AddNewItem_(new item_type(value));
  }

  void swap(stack &other) {
    stack s(other);

    other = std::move(*this);
    *this = std::move(s);
  }

  void insert_many_front() {
    CheckMaxSize_(this->size() + 1);

    AddNewItem_(new item_type());
  }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    CheckMaxSize_(this->size() + sizeof...(args));

    for (item_type arg : {args...}) AddNewItem_(new item_type(std::move(arg)));
  }

 private:
  void CopyContainer_(const stack &s) {
    item_type *item = s.head_;
    for (size_type j = 1UL; j < s.size(); j += 1UL) item = item->next;
    for (size_type j = 0UL; j < s.size(); j += 1UL, item = item->prev)
      push((*item).value);
  }

  void SetProtectedFields_(size_type size, item_type *head) noexcept {
    this->size_ = size;
    this->head_ = head;
  }

  void CheckMaxSize_(size_type size) override {
    if (size > this->MaxSize_())
      throw std::length_error(
          "Incorrect input, cannot create s21::stack larger than max_size()");
  }

  void AddNewItem_(item_type *new_item) noexcept {
    new_item->next = this->head_;
    if (this->head_ != nullptr) (this->head_)->prev = new_item;
    this->head_ = new_item;
    this->size_ += 1UL;
  }
};
}  // namespace s21

#endif  // S21_STACK_H
