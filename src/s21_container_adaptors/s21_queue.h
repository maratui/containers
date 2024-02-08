#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINER_ADAPTORS_S21_QUEUE_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINER_ADAPTORS_S21_QUEUE_H

#include "../s21_sequence_containers/s21_list.h"

namespace s21 {
template <class T, class Container = list<T>>
class queue : protected Container {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using item_type = typename Container::item_type;

  queue() : Container() {}
  explicit queue(std::initializer_list<value_type> const &items)
      : Container(items) {}
  queue(const queue &q) : Container(q) {}
  queue(queue &&q) noexcept : Container(std::move(q)) {}
  ~queue() {}

  queue &operator=(queue &&q) noexcept {
    Container::operator=(std::move(q));

    return *this;
  }

  queue &operator=(const queue &q) {
    Container::operator=(q);

    return *this;
  }

  using Container::back;
  using Container::front;

  using Container::empty;
  using Container::size;

  void push(const_reference value) { return this->push_back(value); }

  void pop() { return this->pop_front(); }

  void swap(queue &other) { Container::swap(other); }

  void insert_many_back() { this->insert_many(this->end()); }
  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (item_type arg : {args...})
      this->insert_many(this->end(), std::move(arg));
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_CONTAINER_ADAPTORS_S21_QUEUE_H
