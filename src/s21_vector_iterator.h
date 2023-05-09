#ifndef SRC_S21_VECTORITERATOR_H
#define SRC_S21_VECTORITERATOR_H

#include "./s21_vector_allocate.h"

namespace S21 {
template <class T>
class VectorIterator {
  using reference = T &;
  using size_type = size_t;

 public:
  VectorIterator() {}

  VectorIterator(VectorAllocate<T> *ptr) : item_(ptr) {}

  ~VectorIterator() {}

  //---------------------------------------------------------------------------

  reference operator[](size_type pos) noexcept { return (*(item_ + pos)).item; }

  //---------------------------------------------------------------------------

  friend reference operator*(VectorIterator &vi) noexcept {
    return (*vi.item_).item;
  }
  friend reference operator*(VectorIterator &&vi) noexcept { return *vi; }

  //---------------------------------------------------------------------------

  friend VectorIterator &operator++(VectorIterator &vi) noexcept {
    vi.item_ = vi.item_ + 1;

    return vi;
  }
  friend VectorIterator &operator++(VectorIterator &&vi) noexcept {
    return ++vi;
  }

  friend VectorIterator &operator--(VectorIterator &vi) noexcept {
    vi.item_ = vi.item_ - 1;

    return vi;
  }
  friend VectorIterator &operator--(VectorIterator &&vi) noexcept {
    return --vi;
  }

  //---------------------------------------------------------------------------

  size_type operator+(VectorIterator &vi) noexcept {
    return this->item_ + vi.item_;
  }
  size_type operator+(VectorIterator &&vi) noexcept { return *this + vi; }

  size_type operator-(VectorIterator &vi) noexcept {
    return this->item_ - vi.item_;
  }
  size_type operator-(VectorIterator &&vi) noexcept { return *this - vi; }

  //---------------------------------------------------------------------------

  VectorIterator operator+(size_type num) noexcept {
    VectorIterator iter(this->item_ + num);

    return iter;
  }

  VectorIterator operator-(size_type num) noexcept {
    VectorIterator iter(this->item_ - num);

    return iter;
  }

  //---------------------------------------------------------------------------

  bool operator==(VectorIterator &vi) noexcept {
    return this->item_ == vi.item_;
  }
  bool operator==(VectorIterator &&vi) noexcept { return *this == vi; }

  bool operator!=(VectorIterator &vi) noexcept {
    return !(this->item_ == vi.item_);
  }
  bool operator!=(VectorIterator &&vi) noexcept { return *this != vi; }

  bool operator>=(VectorIterator &vi) noexcept {
    return this->item_ >= vi.item_;
  }
  bool operator>=(VectorIterator &&vi) noexcept { return *this >= vi; }

  bool operator<=(VectorIterator &vi) noexcept {
    return this->item_ <= vi.item_;
  }
  bool operator<=(VectorIterator &&vi) noexcept { return *this <= vi; }

  bool operator>(VectorIterator &vi) noexcept { return this->item_ > vi.item_; }
  bool operator>(VectorIterator &&vi) noexcept { return *this > vi; }

  bool operator<(VectorIterator &vi) noexcept { return this->item_ < vi.item_; }
  bool operator<(VectorIterator &&vi) noexcept { return *this < vi; }

  //---------------------------------------------------------------------------

 private:
  VectorAllocate<T> *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_VECTORITERATOR_H
