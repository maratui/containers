#ifndef SRC_S21_LISTALLOCATE_H
#define SRC_S21_LISTALLOCATE_H

template <class T>
struct Node {
  T value;
  Node *prev;
  Node *next;
};

namespace S21 {
template <class T>
class ListAllocate {
  using value_type = struct Node<T>;
  using size_type = size_t;

 public:
  static std::tuple<value_type *, value_type *> Allocate(size_type capacity) {
    value_type *head;
    value_type *tail;
    value_type *item;

    head = new value_type;
    tail = head;
    for (auto i = 0; i < capacity; i++) {
      item = new value_type;
      item->prev = tail;
      tail->next = item;
      item->value = {};
      item->next = nullptr;
      tail = item;
    }

    return head;
  }

  static void Append(value_type *tail) {
    value_type *item;

    item = new value_type;
    item->prev = tail;
    tail->next = item;
    item->value = {};
    item->next = nullptr;
    tail = item;
  }

  static void Delete(value_type *list) noexcept {
    value_type *item;

    while (list) {
      item = list;
      list = item.next;
      delete item;
    }
  }
};
}  // namespace S21

#endif  // SRC_S21_LISTALLOCATE_H
