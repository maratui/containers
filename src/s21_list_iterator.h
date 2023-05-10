#ifndef SRC_S21_LISTITERATOR_H
#define SRC_S21_LISTITERATOR_H

#include "./s21_list_allocate.h"

namespace S21 {
template <class T>
class ListIterator {
  using reference = T &;
  using size_type = size_t;

 public:
  ListIterator() {}

  ListIterator(ListAllocate<T> *ptr) : item_(ptr) {}

  ~ListIterator() {}

  //---------------------------------------------------------------------------

  reference operator[](size_type pos) noexcept { return *(*this + pos); }

  //---------------------------------------------------------------------------

  friend reference operator*(ListIterator &li) noexcept {
    return (*li.item_).value;
  }
  friend reference operator*(ListIterator &&li) noexcept { return *li; }

  //---------------------------------------------------------------------------

  friend ListIterator &operator++(ListIterator &li) noexcept {
    li.item_ = li.item_->next;

    return li;
  }
  friend ListIterator &operator++(ListIterator &&li) noexcept { return ++li; }

  friend ListIterator &operator--(ListIterator &li) noexcept {
    li.item_ = li.item_->prev;

    return li;
  }
  friend ListIterator &operator--(ListIterator &&li) noexcept { return --li; }

  //---------------------------------------------------------------------------

  size_type operator-(ListIterator &li) noexcept {
    ListIterator iter(this->item_);
    size_type size;

    size = 0U;
    if (li.item_)
      while (iter.item_ && iter.item_->prev && iter != li) {
        ++size;
        --iter;
      }

    return size;
  }
  size_type operator-(ListIterator &&li) noexcept { return *this - li; }

  //---------------------------------------------------------------------------

  ListIterator operator+(size_type num) noexcept {
    ListIterator iter(this->item_);

    for (size_type j = 0; j < num; j++) ++iter;

    return iter;
  }

  ListIterator operator-(size_type num) noexcept {
    ListIterator iter(this->item_);

    for (size_type j = 0; j < num; j++) --iter;

    return iter;
  }

  //---------------------------------------------------------------------------

  bool operator==(ListIterator &li) noexcept { return this->item_ == li.item_; }
  bool operator==(ListIterator &&li) noexcept { return *this == li; }

  bool operator!=(ListIterator &li) noexcept { return !(*this == li); }
  bool operator!=(ListIterator &&li) noexcept { return *this != li; }

  bool operator>=(ListIterator &li) noexcept {
    return *this > li || *this == li;
  }
  bool operator>=(ListIterator &&li) noexcept { return *this >= li; }

  bool operator<=(ListIterator &li) noexcept {
    return *this < li || *this == li;
  }
  bool operator<=(ListIterator &&li) noexcept { return *this <= li; }

  bool operator>(ListIterator &li) noexcept { return (*this - li) > 0; }
  bool operator>(ListIterator &&li) noexcept { return *this > li; }

  bool operator<(ListIterator &li) noexcept { return (li - *this) > 0; }
  bool operator<(ListIterator &&li) noexcept { return *this < li; }

  //---------------------------------------------------------------------------

 private:
  ListAllocate<T> *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_LISTITERATOR_H
