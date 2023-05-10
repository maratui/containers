#ifndef SRC_S21_LISTCONSTITERATOR_H
#define SRC_S21_LISTCONSTITERATOR_H

#include "./s21_list_allocate.h"

namespace S21 {
template <class T>
class ListConstIterator {
  using const_reference = const T &;
  using size_type = size_t;

 public:
  ListConstIterator() {}

  ListConstIterator(const ListAllocate<T> *ptr) : item_(ptr) {}

  ~ListConstIterator() {}

  //---------------------------------------------------------------------------

  const_reference operator[](size_type pos) noexcept { return *(*this + pos); }

  //---------------------------------------------------------------------------

  friend const_reference operator*(ListConstIterator &li) noexcept {
    return (*li.item_).value;
  }
  friend const_reference operator*(ListConstIterator &&li) noexcept {
    return *li;
  }

  //---------------------------------------------------------------------------

  friend ListConstIterator &operator++(ListConstIterator &li) noexcept {
    li.item_ = li.item_->next;

    return li;
  }
  friend ListConstIterator &operator++(ListConstIterator &&li) noexcept {
    return ++li;
  }

  friend ListConstIterator &operator--(ListConstIterator &li) noexcept {
    li.item_ = li.item_->prev;

    return li;
  }
  friend ListConstIterator &operator--(ListConstIterator &&li) noexcept {
    return --li;
  }

  //---------------------------------------------------------------------------

  size_type operator-(ListConstIterator &li) noexcept {
    ListConstIterator iter(this->item_);
    size_type size;

    size = 0U;
    if (li.item_)
      while (iter.item_ && iter.item_->prev && iter != li) {
        ++size;
        --iter;
      }

    return size;
  }
  size_type operator-(ListConstIterator &&li) noexcept { return *this - li; }

  //---------------------------------------------------------------------------

  ListConstIterator operator+(size_type num) noexcept {
    ListConstIterator iter(this->item_);

    for (size_type j = 0; j < num; j++) ++iter;

    return iter;
  }

  ListConstIterator operator-(size_type num) noexcept {
    ListConstIterator iter(this->item_);

    for (size_type j = 0; j < num; j++) --iter;

    return iter;
  }

  //---------------------------------------------------------------------------

  bool operator==(ListConstIterator &li) noexcept {
    return this->item_ == li.item_;
  }
  bool operator==(ListConstIterator &&li) noexcept { return *this == li; }

  bool operator!=(ListConstIterator &li) noexcept { return !(*this == li); }
  bool operator!=(ListConstIterator &&li) noexcept { return *this != li; }

  bool operator>=(ListConstIterator &li) noexcept {
    return *this > li || *this == li;
  }
  bool operator>=(ListConstIterator &&li) noexcept { return *this >= li; }

  bool operator<=(ListConstIterator &li) noexcept {
    return *this < li || *this == li;
  }
  bool operator<=(ListConstIterator &&li) noexcept { return *this <= li; }

  bool operator>(ListConstIterator &li) noexcept { return (*this - li) > 0; }
  bool operator>(ListConstIterator &&li) noexcept { return *this > li; }

  bool operator<(ListConstIterator &li) noexcept { return (li - *this) > 0; }
  bool operator<(ListConstIterator &&li) noexcept { return *this < li; }

  //---------------------------------------------------------------------------

 private:
  const ListAllocate<T> *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_LISTCONSTITERATOR_H
