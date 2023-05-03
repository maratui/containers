#ifndef SRC_S21_VECTORITERATOR_H
#define SRC_S21_VECTORITERATOR_H

#include <memory>
#include <stdexcept>

namespace S21 {
template <class T>
class VectorIterator {
  using value_type = T;
  using size_type = size_t;

 public:
  VectorIterator() : head_(new value_type[1]{}) {tail_ = head_; }

  VectorIterator(const VectorIterator &vi) noexcept {
    this->head_ = vi.head_;
    this->tail_ = vi.tail_;
  }

  ~VectorIterator() { if (item_ == nullptr) delete[] head_; }

  VectorIterator &operator=(const VectorIterator &vi) noexcept {
    this->head_ = vi.head_;
    this->tail_ = vi.tail_;
    this->item_ = vi.item_;

    return *this;
  }

  void Create(size_type capacity) {
    delete[] head_;
    head_ = new value_type[capacity + 1]{};
    tail_ = head_ + capacity;
  }

  void Delete() {
    delete[] head_;
    head_ = new value_type[1]{};
    tail_ = head_;
  }

  VectorIterator Head() noexcept {
    VectorIterator item(*this);
    item.item_ = head_;

    return item;
  }

  VectorIterator Tail() noexcept {
    VectorIterator item(*this);
    item.item_ = tail_;

    return item;
  }

  value_type *Data() const noexcept {
    return head_;
  }

  friend value_type &operator*(const VectorIterator &vi) noexcept {
    return (vi.item_ == nullptr) ? *(vi.head_) : *(vi.item_);
  }

  friend VectorIterator &operator++(VectorIterator &vi) noexcept {
    if (vi.item_ != nullptr && vi.item_ != vi.tail_) vi.item_ = vi.item_ + 1;

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

  size_type operator-(const VectorIterator &vi) const noexcept {
    size_type ret;
  
    if (this->item_ != nullptr && vi.item_ != nullptr) ret = this->item_ - vi.item_;
    else
      ret = 0;

    return ret;
  }

  VectorIterator &operator+(size_type num) noexcept {
    if (this->item_ != nullptr)
      for (size_type i = 0; i < num; i++)
        ++(*this);

    return *this;
  }

  VectorIterator operator-(size_type num) noexcept {
    if (this->item_ != nullptr)
      for (size_type i = 0; i < num; i++)
        --(*this);

    return *this;
  }

  bool operator==(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && (this->item_ == vi.item_));
  }

  bool operator!=(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && !(this->item_ == vi.item_));
  }

  bool operator>=(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && (this->item_ >= vi.item_));
  }

  bool operator<=(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && !(this->item_ <= vi.item_));
  }

  bool operator>(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && (this->item_ > vi.item_));
  }

  bool operator<(VectorIterator &vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && !(this->item_ < vi.item_));
  }

  bool operator==(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && (this->item_ == vi.item_));
  }

  bool operator!=(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && !(this->item_ == vi.item_));
  }

  bool operator>=(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && (this->item_ >= vi.item_));
  }

  bool operator<=(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && !(this->item_ <= vi.item_));
  }

  bool operator>(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && (this->item_ > vi.item_));
  }

  bool operator<(VectorIterator &&vi) noexcept {
    return ((this->item_ != nullptr) && (vi.item_ != nullptr) && !(this->item_ < vi.item_));
  }

 private:
  value_type *head_ = nullptr;
  value_type *tail_ = nullptr;
  value_type *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_VECTORITERATOR_H
