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

  ~ListIterator() {
    item_.Delete();
    delete head_;
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

  void Delete() {
    t_item *item;

    while (head_ != tail_) {
      item = tail_;
      tail_ = tail_->back;
      delete item;
    }
  }

  //  reference operator*() const noexcept { return item_->value; }

 private:
  t_item *head_ = nullptr;
  t_item *tail_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_LISTITERATOR_H
