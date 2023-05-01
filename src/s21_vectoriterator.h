#ifndef SRC_S21_VECTORITERATOR_H
#define SRC_S21_VECTORITERATOR_H

#include <memory>
#include <stdexcept>

namespace S21 {
template <class T>
class VectorIterator {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  VectorIterator() : item_(new value_type[1]{}) {}

  ~VectorIterator() { delete[] item_ }

  void Create(size_type capacity) {
    delete[] item_;
    item_ = new value_type[capacity + 1]{};
  }

  void Delete() {
    delete[] item_;
    item_ = new value_type[1]{};
  }

 private:
  value_type *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_VECTORITERATOR_H
