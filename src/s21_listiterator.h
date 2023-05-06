#ifndef SRC_S21_LISTITERATOR_H
#define SRC_S21_LISTITERATOR_H

#include <memory>
#include <stdexcept>

namespace S21 {
template <class T>
class ListIterator {
  typedef struct s_item {
    T value;
    s_item *next;
    s_item *back;
  } t_item;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  ListIterator() {
    head_ = new t_item;
    tail_ = head_;
    head_->back = nullptr;
    head_->value = 0;
    head_->next = nullptr;
  }

  ListIterator(const ListIterator &li) noexcept {
    this->head_ = li.head_;
    this->tail_ = li.tail_;
  }

  ~ListIterator() {
    if (item_ == nullptr) {
      item_.Delete();
      delete head_;
    }
  }

  void Create(size_type capacity) {
    item_.Delete();
    for (auto i = 0; i < capacity; i++) {
      t_item *item = new t_item;
      item->back = tail_;
      item->value = 0;
      item->next = nullptr;
      tail_ = item;
    }
  }

  void Delete() noexcept {
    t_item *item;

    while (head_ != tail_) {
      item = tail_;
      tail_ = tail_->back;
      delete item;
    }
  }

  ListIterator &Head() noexcept {
    ListIterator item(*this);
    item.item_ = head_;

    return item;
  }

  ListIterator &Tail() noexcept {
    ListIterator item(*this);
    item.item_ = tail_;

    return item;
  }

  friend value_type &operator*(const ListIterator &li) noexcept {
    return (li.item_ == nullptr) ? *li.head_ : *li.item_;
  }

  friend ListIterator &operator++(ListIterator &li) noexcept {
    if (li.item_ != nullptr && li.item_ != li.tail_) li.item_ = li.item_.next;

    return li;
  }

  friend ListIterator &operator--(ListIterator &li) noexcept {
    if (li.item_ != nullptr && li.item_ != li.head_) li.item_ = li.item_.back;

    return li;
  }

  ListIterator &operator+(size_type num) noexcept {
    if (this->item_ != nullptr)
      for (auto i = 0; i < num; i++) ++(*this);

    return *this;
  }

  ListIterator &operator-(size_type num) noexcept {
    if (this->item_ != nullptr)
      for (auto i = 0; i < num; i++) --(*this);

    return *this;
  }

  bool &operator==(ListIterator &li) noexcept {
    return ((this->item_ != nullptr) && (li.item_ != nullptr) &&
            (this->item_ == li.item_));
  }

  bool &operator!=(ListIterator &li) noexcept {
    return ((this->item_ != nullptr) && (li.item_ != nullptr) &&
            !(this->item_ == li.item_));
  }

 private:
  t_item *head_ = nullptr;
  t_item *tail_ = nullptr;
  t_item *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_LISTITERATOR_H
