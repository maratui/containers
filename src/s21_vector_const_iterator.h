#ifndef SRC_S21_VECTORCONSTITERATOR_H
#define SRC_S21_VECTORCONSTITERATOR_H

#include "./s21_vector_iterator.h"

namespace S21 {
template <class T>
class VectorConstIterator {
  using const_reference = const T &;
  using size_type = size_t;

 public:
  VectorConstIterator() {}

  VectorConstIterator(const VectorAllocate<T> *ptr) : item_(ptr) {}

  ~VectorConstIterator() {}

  //---------------------------------------------------------------------------

  const_reference operator[](size_type pos) noexcept { return *(*this + pos); }

  //---------------------------------------------------------------------------

  friend const_reference operator*(VectorConstIterator &vi) noexcept {
    return (*vi.item_).item;
  }
  friend const_reference operator*(VectorConstIterator &&vi) noexcept {
    return *vi;
  }

  //---------------------------------------------------------------------------

  friend VectorConstIterator &operator++(VectorConstIterator &vi) noexcept {
    vi.item_ = vi.item_ + 1;

    return vi;
  }
  friend VectorConstIterator &operator++(VectorConstIterator &&vi) noexcept {
    return ++vi;
  }

  friend VectorConstIterator &operator--(VectorConstIterator &vi) noexcept {
    vi.item_ = vi.item_ - 1;

    return vi;
  }
  friend VectorConstIterator &operator--(VectorConstIterator &&vi) noexcept {
    return --vi;
  }

  //---------------------------------------------------------------------------

  size_type operator-(VectorConstIterator &vi) noexcept {
    size_type size;

    size = 0U;
    if (this->item_ && vi.item_) size = this->item_ - vi.item_;

    return size;
  }
  size_type operator-(VectorConstIterator &&vi) noexcept { return *this - vi; }

  //---------------------------------------------------------------------------

  VectorConstIterator operator+(size_type num) noexcept {
    VectorConstIterator iter(this->item_ + num);

    return iter;
  }

  VectorConstIterator operator-(size_type num) noexcept {
    VectorConstIterator iter(this->item_ - num);

    return iter;
  }

  //---------------------------------------------------------------------------

  bool operator==(VectorConstIterator &vi) noexcept {
    return this->item_ == vi.item_;
  }
  bool operator==(VectorConstIterator &&vi) noexcept { return *this == vi; }

  bool operator!=(VectorConstIterator &vi) noexcept { return !(*this == vi); }
  bool operator!=(VectorConstIterator &&vi) noexcept { return *this != vi; }

  bool operator>=(VectorConstIterator &vi) noexcept {
    return *this > vi || *this == vi;
  }
  bool operator>=(VectorConstIterator &&vi) noexcept { return *this >= vi; }

  bool operator<=(VectorConstIterator &vi) noexcept {
    return *this < vi || *this == vi;
  }
  bool operator<=(VectorConstIterator &&vi) noexcept { return *this <= vi; }

  bool operator>(VectorConstIterator &vi) noexcept { return (*this - vi) > 0; }
  bool operator>(VectorConstIterator &&vi) noexcept { return *this > vi; }

  bool operator<(VectorConstIterator &vi) noexcept { return (vi - *this) > 0; }
  bool operator<(VectorConstIterator &&vi) noexcept { return *this < vi; }

  //---------------------------------------------------------------------------

 private:
  const VectorAllocate<T> *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_VECTORCONSTITERATOR_H
