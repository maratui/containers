#ifndef SRC_S21_VECTORITERATOR_H
#define SRC_S21_VECTORITERATOR_H

namespace S21 {
template <class T>
class VectorIterator {
  using value_type = T;
  using reference = T &;
  using size_type = size_t;

 public:
  VectorIterator() {}

  VectorIterator(value_type *container) : item_(container) {}

  ~VectorIterator() {}
/*
  VectorIterator &operator=(const VectorIterator &vi) noexcept {
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
      head_ = new value_type[capacity + 1]{};
      SetTail(capacity);
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

  VectorIterator GetHead() noexcept {
    VectorIterator item(*this);

    item.item_ = head_;

    return item;
  }

  VectorIterator GetTail() noexcept {
    VectorIterator item(*this);

    item.item_ = tail_;

    return item;
  }

  void SetTail(size_type size) noexcept { tail_ = head_ + size; }

  //---------------------------------------------------------------------------

  reference operator[](size_type pos) noexcept { return *(item_ + pos); }

  value_type *Data() noexcept { return head_; }

  //---------------------------------------------------------------------------

  friend reference operator*(const VectorIterator &vi) noexcept {
    return *(vi.item_);
  }
  friend reference operator*(const VectorIterator &&vi) noexcept {
    return *(vi.item_);
  }

  //---------------------------------------------------------------------------

  friend VectorIterator &operator++(VectorIterator &vi) noexcept {
    vi.item_ = vi.item_ + 1;

    return vi;
  }
  friend VectorIterator &operator++(VectorIterator &&vi) noexcept {
    if (vi.item_ != nullptr && vi.item_ != vi.tail_) vi.item_ = vi.item_ + 1;

    return vi;
  }

  friend VectorIterator &operator--(VectorIterator &vi) noexcept {
    if (vi.item_ != nullptr && vi.item_ != vi.head_) vi.item_ = vi.item_ - 1;

    return vi;
  }
  friend VectorIterator &operator--(VectorIterator &&vi) noexcept {
    if (vi.item_ != nullptr && vi.item_ != vi.head_) vi.item_ = vi.item_ - 1;

    return vi;
  }

  //---------------------------------------------------------------------------

  size_type operator-(const VectorIterator &vi) const noexcept {
    size_type ret;

    if (this->item_ != nullptr && vi.item_ != nullptr)
      ret = this->item_ - vi.item_;
    else
      ret = 0;

    return ret;
  }

  //---------------------------------------------------------------------------

  VectorIterator operator+(size_type num) const noexcept {
    VectorIterator item;

    item.item_ = this->item_ + num;

    return item;
  }

  VectorIterator operator-(size_type num) noexcept {
    VectorIterator item(*this);

    if (item.item_ != nullptr)
      for (size_type i = 0; i < num; i++) --item;

    return item;
  }

  //---------------------------------------------------------------------------

  bool operator==(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ == vi.item_));
  }
  bool operator==(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ == vi.item_));
  }

  bool operator!=(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            !(this->item_ == vi.item_));
  }
  bool operator!=(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            !(this->item_ == vi.item_));
  }

  bool operator>=(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ >= vi.item_));
  }
  bool operator>=(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ >= vi.item_));
  }

  bool operator<=(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ <= vi.item_));
  }
  bool operator<=(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ <= vi.item_));
  }

  bool operator>(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ > vi.item_));
  }
  bool operator>(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ > vi.item_));
  }

  bool operator<(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            (this->item_ < vi.item_));
  }
  bool operator<(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) &&
            !(this->item_ < vi.item_));
  }

  //---------------------------------------------------------------------------

 private:
  value_type *head_ = nullptr;
  value_type *tail_ = nullptr;
  value_type *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_VECTORITERATOR_H
