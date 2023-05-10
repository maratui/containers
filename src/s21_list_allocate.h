#ifndef SRC_S21_LISTALLOCATE_H
#define SRC_S21_LISTALLOCATE_H

#include <cstddef>
#include <tuple>

namespace S21 {
template <class T>
class ListAllocate {
 public:
  ListAllocate() {}

  ~ListAllocate() {}

  static std::tuple<ListAllocate *, ListAllocate *> Allocate(size_t size,
                                                             size_t capacity) {
    ListAllocate *head;
    ListAllocate *tail;

    size = size;
    head = new ListAllocate();
    tail = head;
    for (size_t i = 0; i < capacity; i++) {
      tail = Append_(tail);
    }

    return {head, tail};
  }

  static ListAllocate *SetTail(ListAllocate *head, size_t size) {
    ListAllocate *tail;

    tail = head;
    for (size_t i = 0; i < size; i++) tail = tail->next;
    Delete(tail->next);
    tail->next = nullptr;

    return tail;
  }

  static void Delete(ListAllocate *head) noexcept {
    ListAllocate *item;

    while (head != nullptr) {
      item = head;
      head = item->next;
      delete item;
    }
  }

  static std::tuple<size_t, size_t, ListAllocate *, ListAllocate *> Append(
      size_t size, size_t capacity, ListAllocate *head, ListAllocate *tail) {
    if (size == 0 && head == nullptr)
      std::tie(head, tail) = Allocate(1, 1);
    else
      tail = Append_(tail);
    size++;
    capacity++;

    return {size, capacity, head, tail};
  }

  T value = {};
  ListAllocate *prev = {};
  ListAllocate *next = {};

 private:
  static ListAllocate *Append_(ListAllocate *tail) {
    ListAllocate *item;

    item = new ListAllocate();
    item->prev = tail;
    tail->next = item;
    item->value = {};
    item->next = nullptr;
    tail = item;

    return tail;
  }
};
}  // namespace S21

#endif  // SRC_S21_LISTALLOCATE_H
