#ifndef SRC_S21_VECTORALLOCATE_H
#define SRC_S21_VECTORALLOCATE_H

namespace S21 {
template <class T>
class VectorAllocate {
 public:
  VectorAllocate() {}

  ~VectorAllocate() {}

  static std::tuple<T *, T *> Allocate(size_t capacity) {
    T *head;
    T *tail;

    head = new T[capacity + 1]{};
    tail = SetTail(head, capacity);

    return {head, tail};
  }

  static T *SetTail(T *head, T size) {
    T *tail;

    tail = head + size;

    return tail;
  }

  static void Delete(T *array) noexcept {
    if (array) {
      delete[] array;
      array = nullptr;
    }
  }

  T *head_ = nullptr;
  T *tail_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_VECTORALLOCATE_H
