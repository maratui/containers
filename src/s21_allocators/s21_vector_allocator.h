#ifndef S21_VECTOR_ALLOCATOR_H
#define S21_VECTOR_ALLOCATOR_H

#include <tuple>

namespace s21 {
template <class T>
class VectorAllocator {
 public:
  using item_type = T;
  using size_type = std::size_t;

  static std::tuple<item_type *, item_type *> Allocate(size_type size,
                                                       size_type capacity) {
    item_type *head = Allocate_(capacity);
    item_type *tail = SetTail(head, size);

    return {head, tail};
  }

  static item_type *SetTail(item_type *head, size_type size) noexcept {
    item_type *tail = head + size;

    return tail;
  }

  static item_type *Delete(item_type *head) noexcept {
    if (head != nullptr) {
      delete[] head;
      head = nullptr;
    }

    return head;
  }

  static std::tuple<size_type, size_type, item_type *, item_type *> Append(
      size_type size, size_type capacity, size_type max_capacity,
      item_type *head, item_type *tail) {
    if (size == capacity) {
      if (capacity > 0UL) {
        capacity *= 2UL;
        if (capacity > max_capacity) capacity = max_capacity;
      } else {
        capacity = 1UL;
      }
      item_type *array = head;
      head = Allocate_(capacity);
      for (size_type j = 0UL; j < size; j += 1UL) head[j] = array[j];
      Delete(array);
    }
    size += 1UL;
    tail = SetTail(head, size);

    return {size, capacity, head, tail};
  }

 private:
  static item_type *Allocate_(size_type capacity) {
    item_type *head = nullptr;

    if (capacity > 0UL) head = new item_type[capacity]{};

    return head;
  }
};
}  // namespace s21

#endif  // S21_VECTOR_ALLOCATOR_H
