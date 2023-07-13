#ifndef S21_ITERATOR_H
#define S21_ITERATOR_H

namespace s21 {
template <class T, class A>
class Iterator {
 public:
  using reference = T &;
  using item_type = A;

  friend reference operator*(Iterator &i) noexcept {
    reference ret = i.Asterisc_();

    return ret;
  }
  friend reference operator*(Iterator &&i) noexcept {
    reference ret = *i;

    return ret;
  }

  friend void operator++(Iterator &i) noexcept { i.Next_(); }

  friend void operator--(Iterator &i) noexcept { i.Prev_(); }

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

  virtual reference Asterisc_() noexcept = 0;

  virtual void Next_() noexcept = 0;

  virtual void Prev_() noexcept = 0;
};
}  // namespace s21

#endif  // S21_ITERATOR_H
