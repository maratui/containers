#ifndef SRC_S21_VECTORALLOCATE_H
#define SRC_S21_VECTORALLOCATE_H

namespace S21 {
template <class T>
class VectorAllocate {
 public:
  VectorAllocate() {}

  ~VectorAllocate() {}

  static std::tuple<VectorAllocate *, VectorAllocate *> Allocate(size_t capacity) {
    VectorAllocate *head;
    VectorAllocate *tail;

    head = new T[capacity + 1]{};
    tail = SetTail(head, capacity);

    return {head, tail};
  }

  static VectorAllocate *SetTail(VectorAllocate *head, VectorAllocate size) {
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

  T item = {};
};
}  // namespace S21

#endif  // SRC_S21_VECTORALLOCATE_H
