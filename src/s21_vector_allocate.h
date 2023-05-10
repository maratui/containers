#ifndef SRC_S21_VECTORALLOCATE_H
#define SRC_S21_VECTORALLOCATE_H

#include <stdarg.h>

namespace S21 {
template <class T>
class VectorAllocate {
 public:
  VectorAllocate() {}

  ~VectorAllocate() {}

  static std::tuple<VectorAllocate *, VectorAllocate *> Allocate(
      size_t size, size_t capacity) {
    VectorAllocate *head;
    VectorAllocate *tail;

    head = Allocate_(capacity);
    tail = SetTail(head, size);

    return {head, tail};
  }

  static VectorAllocate *SetTail(VectorAllocate *head, size_t size) {
    VectorAllocate *tail;

    tail = head + size;

    return tail;
  }

  static void Delete(VectorAllocate *array) noexcept {
    if (array) {
      delete[] array;
      array = nullptr;
    }
  }

  static std::tuple<size_t, size_t, VectorAllocate *, VectorAllocate *> Append(
      VectorAllocate *head, ...) {
    VectorAllocate *array;
    VectorAllocate *tail;

    va_list args;
    va_start(args, head);
    size_t size = va_arg(args, size_t);
    size_t capacity = va_arg(args, size_t);
    va_end(args);

    if (size == capacity) {
      if (capacity > 0)
        capacity *= 2;
      else
        capacity = 1;
      array = head;
      head = Allocate_(capacity);
      for (size_t j = 0; j < size; j++) head[j] = array[j];
      Delete(array);
    }
    tail = SetTail(head, ++size);

    return {size, capacity, head, tail};
  }

  T item = {};

 private:
  static VectorAllocate *Allocate_(size_t capacity) {
    VectorAllocate *head;

    head = new VectorAllocate[capacity + 1]{};

    return head;
  }
};
}  // namespace S21

#endif  // SRC_S21_VECTORALLOCATE_H
