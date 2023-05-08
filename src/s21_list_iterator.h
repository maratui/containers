#ifndef SRC_S21_LISTITERATOR_H
#define SRC_S21_LISTITERATOR_H

#include "./s21_list_allocate.h"

namespace S21 {
template <class T>
class ListIterator {
  using value_type = struct Node<T>;
  using reference = T &;
  using size_type = size_t;

 public:
  ListIterator() {}

  ListIterator(value_type *ptr) : item_(ptr) {}

  ~ListIterator() {}

  //---------------------------------------------------------------------------

  reference operator[](size_type pos) noexcept { return *(*this + pos); }

  //---------------------------------------------------------------------------

  friend reference operator*(ListIterator &li) noexcept {
    return *(li.item_);
  }
  friend reference operator*(ListIterator &&li) noexcept {
    return *(li.item_);
  }

  //---------------------------------------------------------------------------

  friend ListIterator &operator++(ListIterator &li) noexcept {
    li.item_ = li.item_.next;

    return li;
  }
  friend ListIterator &operator++(ListIterator &&li) noexcept {
    li.item_ = li.item_.next;

    return li;
  }

  friend ListIterator &operator--(ListIterator &li) noexcept {
    li.item_ = li.item_.prev;

    return li;
  }
  friend ListIterator &operator--(ListIterator &&li) noexcept {
    li.item_ = li.item_.prev;

    return li;
  }

  //---------------------------------------------------------------------------

  size_type operator-(ListIterator &li) noexcept {
    ListIterator iter(*this);
    size_type = 0U;

    while (iter != li) {}

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

#endif  // SRC_S21_LISTITERATOR_H
