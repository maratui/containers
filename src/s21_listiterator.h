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
  ListIterator() {}

 private:
  t_item *item_ = nullptr;
};
}  // namespace S21

#endif  // SRC_S21_LISTITERATOR_H
