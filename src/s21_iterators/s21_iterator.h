#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_ITERATOR_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_ITERATOR_H

namespace s21 {
template <class T, class A>
class Iterator {
 public:
  using reference = T &;
  using item_type = A;

  friend reference operator*(Iterator &i) noexcept {
    reference ret = i.Asterisc();

    return ret;
  }
  friend reference operator*(Iterator &&i) noexcept {
    reference ret = *i;

    return ret;
  }

  friend void operator++(Iterator &i) noexcept { i.Next(); }

  friend void operator--(Iterator &i) noexcept { i.Prev(); }

  bool operator==(const Iterator &i) noexcept {
    bool ret = this->item_ptr_ == i.item_ptr_;

    return ret;
  }
  friend bool operator==(Iterator &&li, Iterator &&ri) noexcept {
    bool ret = li == ri;

    return ret;
  }

  bool operator!=(const Iterator &i) noexcept {
    bool ret = !(*this == i);

    return ret;
  }
  friend bool operator!=(Iterator &&li, Iterator &&ri) noexcept {
    bool ret = li != ri;

    return ret;
  }

 protected:
  item_type *item_ptr_ = nullptr;

  virtual reference Asterisc() noexcept = 0;

  virtual void Next() noexcept = 0;

  virtual void Prev() noexcept = 0;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_ITERATORS_S21_ITERATOR_H
