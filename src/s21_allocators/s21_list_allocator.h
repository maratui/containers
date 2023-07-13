#ifndef S21_LIST_ALLOCATOR_H
#define S21_LIST_ALLOCATOR_H

#include <tuple>

namespace s21 {
template <class T>
struct Item {
  Item() {}
  explicit Item(const T &t) : value(t) {}
  explicit Item(T &&t) : value(std::move(t)) {}
  ~Item() {}

  T value = {};
  Item *prev = nullptr;
  Item *next = nullptr;
};

template <class T>
class ListAllocator {
 public:
  using item_type = Item<T>;
  using size_type = std::size_t;

  static std::tuple<item_type *, item_type *> Allocate(size_type capacity) {
    item_type *head = new item_type();
    item_type *tail = head;

    for (size_type j = 0UL; j < capacity; j += 1UL) tail = Append_(tail);

    return {head, tail};
  }

  static item_type *SetTail(item_type *head, size_type size) noexcept {
    item_type *tail = head;

    for (size_type j = 0UL; j < size; j += 1UL) tail = tail->next;
    tail->next = Delete(tail->next);

    return tail;
  }

  static item_type *Delete(item_type *head) noexcept {
    item_type *item;

    while (head != nullptr) {
      item = head;
      head = item->next;
      delete item;
    }

    return head;
  }

 private:
  static item_type *Append_(item_type *tail) {
    item_type *item = new item_type();
    item->prev = tail;
    tail->next = item;
    tail = item;

    return tail;
  }
};
}  // namespace s21

#endif  // S21_LIST_ALLOCATOR_H
