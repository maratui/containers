#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINER_ADAPTORS_S21_STACK_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINER_ADAPTORS_S21_STACK_H

#include "../s21_sequence_containers/s21_list.h"

namespace s21 {
template <class T, class Container = list<T>>
class stack : protected Container {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using item_type = typename Container::item_type;

  stack() : Container() {}
  explicit stack(std::initializer_list<value_type> const &items)
      : Container(items) {}
  stack(const stack &s) : Container(s) {}
  stack(stack &&s) noexcept : Container(std::move(s)) {}
  ~stack() {}

  stack &operator=(stack &&s) noexcept {
    Container::operator=(std::move(s));

    return *this;
  }

  stack &operator=(const stack &s) {
    Container::operator=(s);

    return *this;
  }

  reference top() noexcept { return this->back(); }
  const_reference top() const noexcept { return this->back(); }

  using Container::empty;
  using Container::size;

  void push(const_reference value) { return this->push_back(value); }

  void pop() { return this->pop_back(); }

  void swap(stack &other) { Container::swap(other); }

  void insert_many_front() { this->insert_many(this->end()); }
  template <class... Args>
  void insert_many_front(Args &&...args) {
    for (item_type arg : {args...})
      this->insert_many(this->end(), std::move(arg));
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINER_ADAPTORS_S21_STACK_H
