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

  VectorIterator(value_type *ptr) : item_(ptr) {}

  ~VectorIterator() {}

  //---------------------------------------------------------------------------

  reference operator[](size_type pos) noexcept { return *(item_ + pos); }

  //---------------------------------------------------------------------------

  friend reference operator*(VectorIterator &vi) noexcept {
    return *(vi.item_);
  }
  friend reference operator*(VectorIterator &&vi) noexcept {
    return *(vi.item_);
  }

  //---------------------------------------------------------------------------

  friend VectorIterator &operator++(VectorIterator &vi) noexcept {
    vi.item_ = vi.item_ + 1;

    return vi;
  }
  friend VectorIterator &operator++(VectorIterator &&vi) noexcept {
    vi.item_ = vi.item_ + 1;

    return vi;
  }

  friend VectorIterator &operator--(VectorIterator &vi) noexcept {
    vi.item_ = vi.item_ - 1;

    return vi;
  }
  friend VectorIterator &operator--(VectorIterator &&vi) noexcept {
    vi.item_ = vi.item_ - 1;

    return vi;
  }

  //---------------------------------------------------------------------------

  size_type operator+(VectorIterator &vi) noexcept {
    return this->item_ + vi.item_;
  }
  size_type operator+(VectorIterator &&vi) noexcept {
    return this->item_ + vi.item_;
  }

  size_type operator-(VectorIterator &vi) noexcept {
    return this->item_ - vi.item_;
  }
  size_type operator-(VectorIterator &&vi) noexcept {
    return this->item_ - vi.item_;
  }

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
  bool operator==(VectorIterator &&vi) noexcept {
    return this->item_ == vi.item_;
  }

  bool operator!=(VectorIterator &vi) noexcept {
    return !(this->item_ == vi.item_);
  }
  bool operator!=(VectorIterator &&vi) noexcept {
    return !(this->item_ == vi.item_);
  }

  bool operator>=(VectorIterator &vi) noexcept {
    return this->item_ >= vi.item_;
  }
  bool operator>=(VectorIterator &&vi) noexcept {
    return this->item_ >= vi.item_;
  }

  bool operator<=(VectorIterator &vi) noexcept {
    return this->item_ <= vi.item_;
  }
  bool operator<=(VectorIterator &&vi) noexcept {
    return this->item_ <= vi.item_;
  }

  bool operator>(VectorIterator &vi) noexcept { return this->item_ > vi.item_; }
  bool operator>(VectorIterator &&vi) noexcept {
    return this->item_ > vi.item_;
  }

  bool operator<(VectorIterator &vi) noexcept { return this->item_ < vi.item_; }
  bool operator<(VectorIterator &&vi) noexcept {
    return this->item_ < vi.item_;
  }

  //---------------------------------------------------------------------------

 private:
  value_type *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_VECTORITERATOR_H
