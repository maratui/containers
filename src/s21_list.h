#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H

#include "./s21_list_allocate.h"
#include "./s21_list_const_iterator.h"
#include "./s21_list_iterator.h"
#include "./s21_sequence_container.h"

namespace S21 {
template <class T>
class List : public SequenceContainer<T, ListIterator<T>, ListConstIterator<T>,
                                      ListAllocate<T>> {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;
  using VA = ListAllocate<T>;
  using SC = SequenceContainer<T, ListIterator<T>, ListConstIterator<T>,
                               ListAllocate<T>>;

 public:
  List() : SC() {}

  explicit List(size_type n) : SC(n) {}

  explicit List(std::initializer_list<value_type> const &items) : SC(items) {}

  List(const List &v) : SC(v) {}

  List(List &&v) noexcept : SC(std::move(v)) {}

  ~List() {}

  List &operator=(const List &v) { return (List &)SC::operator=(v); }

  List &operator=(List &&v) noexcept {
    return (List &)SC::operator=(std::move(v));
  }
};
}  // namespace S21

#endif  // SRC_S21_LIST_H
