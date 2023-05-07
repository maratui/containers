#ifndef SRC_S21_VECTORALLOCATE_H
#define SRC_S21_VECTORALLOCATE_H

namespace S21 {
template <class T>
class VectorAllocate {
  using value_type = T;
  using size_type = size_t;

 public:
  static value_type *Allocate(size_type capacity) {
    value_type *head;

    head = new value_type[capacity + 1]{};

    return head;
  }

  static value_type *SetTail(value_type *head, size_type size) {
    value_type *tail;

    tail = head + size;

    return tail;
  }

  static void Delete(value_type *array) noexcept {
      if (array) {
        delete[] array;
          array = nullptr;
      }
  }
};
}  // namespace S21

#endif  // SRC_S21_VECTORALLOCATE_H
