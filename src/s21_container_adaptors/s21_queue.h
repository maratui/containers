#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <stdexcept>

#include "./s21_container_adaptor.h"

namespace s21 {
template <class T>
class queue : public ContainerAdaptor<T> {
 public:
  using value_type = T;
  using const_reference = const T &;
  using reference = T &;
  using item_type = struct Item<T>;
  using size_type = std::size_t;

  queue() {}

  explicit queue(std::initializer_list<value_type> const &items) {
    this->InitializeContainer_(items);
  }

  queue(const queue &q) { CopyContainer_(q); }

  queue(queue &&q) noexcept { *this = std::move(q); }

  ~queue() {
    while (!this->empty()) this->pop();
  }

  queue &operator=(queue &&q) noexcept {
    while (!this->empty()) this->pop();
    if (this != &q) {
      SetProtectedFields_(q.size_, q.head_, q.tail_);
      q.SetProtectedFields_(0U, nullptr, nullptr);
    } else {
      SetProtectedFields_(0U, nullptr, nullptr);
    }

    return *this;
  }

  reference front() noexcept {
    reference ret = (*this->head_).value;

    return ret;
  }
  const_reference front() const noexcept {
    const_reference ret = (*this->head_).value;

    return ret;
  }

  reference back() noexcept {
    reference ret = (*this->tail_).value;

    return ret;
  }
  const_reference back() const noexcept {
    const_reference ret = (*this->tail_).value;

    return ret;
  }

  void push(const_reference value) override {
    AppendNewItem_(new item_type(value));
  }

  void swap(queue &other) {
    queue q(other);

    other = std::move(*this);
    *this = std::move(q);
  }

  void insert_many_back() {
    CheckMaxSize_(this->size() + 1);

    AppendNewItem_(new item_type());
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    CheckMaxSize_(this->size() + sizeof...(args));

    for (item_type arg : {args...})
      AppendNewItem_(new item_type(std::move(arg)));
  }

 private:
  item_type *tail_ = nullptr;

  void CopyContainer_(const queue &q) {
    item_type *item = q.head_;
    for (size_type j = 0UL; j < q.size(); j += 1UL, item = item->next)
      push((*item).value);
  }

  void SetProtectedFields_(size_type size, item_type *head,
                           item_type *tail) noexcept {
    this->size_ = size;
    this->head_ = head;
    tail_ = tail;
  }

  void CheckMaxSize_(size_type size) override {
    if (size > this->MaxSize_())
      throw std::length_error(
          "Incorrect input, cannot create s21::queue larger than max_size()");
  }

  void AppendNewItem_(item_type *new_item) noexcept {
    if (this->empty()) {
      this->head_ = new_item;
      tail_ = this->head_;
    } else {
      tail_->next = new_item;
      new_item->prev = tail_;
      tail_ = new_item;
    }
    this->size_ += 1UL;
  }
};
}  // namespace s21

#endif  // S21_QUEUE_H
