#ifndef SRC_S21_VECTORCONSTITERATOR_H
#define SRC_S21_VECTORCONSTITERATOR_H

#include "./s21_vector_iterator.h"

namespace S21 {
template <class T>
class VectorConstIterator {
  using const_value_type = const T;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  VectorConstIterator() {}

  VectorConstIterator(const_value_type *) : item_(container) {}

  ~VectorConstIterator() {}
  /*
    VectorConstIterator &operator=(const VectorConstIterator &vi) noexcept {
      this->head_ = vi.head_;
      this->tail_ = vi.tail_;
      this->item_ = vi.item_;

      return *this;
    }
  */
  //---------------------------------------------------------------------------

  void Create(size_type capacity) {
    if (item_ == nullptr) {
      if (head_) delete[] head_;
      head_ = new const_value_type[capacity + 1]{};
      tail_ = head_ + capacity;
      item_ = nullptr;
    }
  }

  void Delete() noexcept {
    if (item_ == nullptr) {
      if (head_) delete[] head_;
      head_ = nullptr;
      tail_ = nullptr;
      item_ = nullptr;
    }
  }

  //---------------------------------------------------------------------------

  VectorConstIterator GetHead() const noexcept {
    VectorConstIterator item(*this);

    item.item_ = head_;

    return item;
  }

  VectorConstIterator GetTail() const noexcept {
    VectorConstIterator item(*this);

    item.item_ = tail_;

    return item;
  }

  //---------------------------------------------------------------------------

  const_reference operator[](size_type pos) noexcept { return *(item_ + pos); }

  const_value_type *Data() noexcept { return head_; }

  //---------------------------------------------------------------------------

  friend const_reference operator*(const VectorConstIterator &vi) noexcept {
    return (vi.item_ == nullptr) ? *(vi.head_) : *(vi.item_);
  }
  friend const_reference operator*(const VectorConstIterator &&vi) noexcept {
    return (vi.item_ == nullptr) ? *(vi.head_) : *(vi.item_);
  }

  //---------------------------------------------------------------------------

  friend VectorConstIterator &operator++(VectorConstIterator &vi) noexcept {
    if (vi.item_ != nullptr && vi.item_ != vi.tail_) vi.item_ = vi.item_ + 1;

    return vi;
  }
  friend VectorConstIterator &operator++(VectorConstIterator &&vi) noexcept {
    if (vi.item_ != nullptr && vi.item_ != vi.tail_) vi.item_ = vi.item_ + 1;

    return vi;
  }

  friend VectorConstIterator &operator--(VectorConstIterator &vi) noexcept {
    if (vi.item_ != nullptr && vi.item_ != vi.head_) vi.item_ = vi.item_ - 1;

    return vi;
  }
  friend VectorConstIterator &operator--(VectorConstIterator &&vi) noexcept {
    if (vi.item_ != nullptr && vi.item_ != vi.head_) vi.item_ = vi.item_ - 1;

    return vi;
  }

  //---------------------------------------------------------------------------

  size_type operator-(const VectorConstIterator &vi) const noexcept {
    size_type ret;

    if (this->item_ != nullptr && vi.item_ != nullptr)
      ret = this->item_ - vi.item_;
    else
      ret = 0;

    return ret;
  }

  //---------------------------------------------------------------------------

  VectorConstIterator operator+(size_type num) noexcept {
    VectorConstIterator item(*this);

    if (item.item_ != nullptr)
      for (size_type i = 0; i < num; i++) ++item;

    return item;
  }

  VectorConstIterator operator-(size_type num) noexcept {
    VectorConstIterator item(*this);

    if (item.item_ != nullptr)
      for (size_type i = 0; i < num; i++) --item;

    return item;
  }

  //---------------------------------------------------------------------------

  bool operator==(VectorConstIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ == vi.item_));
  }
  bool operator==(VectorConstIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ == vi.item_));
  }

  bool operator!=(VectorConstIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            !(this->item_ == vi.item_));
  }
  bool operator!=(VectorConstIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            !(this->item_ == vi.item_));
  }

  bool operator>=(VectorConstIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ >= vi.item_));
  }
  bool operator>=(VectorConstIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ >= vi.item_));
  }

  bool operator<=(VectorConstIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ <= vi.item_));
  }
  bool operator<=(VectorConstIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ <= vi.item_));
  }

  bool operator>(VectorConstIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ > vi.item_));
  }
  bool operator>(VectorConstIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ > vi.item_));
  }

  bool operator<(VectorConstIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ < vi.item_));
  }
  bool operator<(VectorConstIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            !(this->item_ < vi.item_));
  }

  //---------------------------------------------------------------------------

 private:
  const_value_type *head_ = nullptr;
  const_value_type *tail_ = nullptr;
  const_value_type *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_VECTORCONSTITERATOR_H
