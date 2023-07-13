#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <stdexcept>

#include "../s21_iterators/s21_vector_const_iterator.h"
#include "../s21_iterators/s21_vector_iterator.h"

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = std::size_t;

  array() {}

  explicit array(std::initializer_list<value_type> const &items) {
    InitializeArray_<std::initializer_list<value_type> const &>(items);
  }

  array(const array &a) { InitializeArray_<const array &>(a); }

  array(array &&a) noexcept { *this = std::move(a); }

  ~array() {}

  array &operator=(array &&a) noexcept {
    std::move(std::begin(a.array_), std::end(a.array_), &array_[0]);

    return *this;
  }

  reference at(size_type pos) {
    CheckSizeBounds_(pos);

    reference ret = (*this)[pos];

    return ret;
  }
  const_reference at(size_type pos) const {
    CheckSizeBounds_(pos);

    const_reference ret = (*this)[pos];

    return ret;
  }

  reference operator[](size_type pos) noexcept {
    iterator iter = begin();
    for (size_type j = 0UL; j < pos; j += 1UL) ++iter;
    reference ret = *iter;

    return ret;
  }
  const_reference operator[](size_type pos) const noexcept {
    const_iterator iter = begin();
    for (size_type j = 0UL; j < pos; j += 1UL) ++iter;
    const_reference ret = *iter;

    return ret;
  }

  reference front() noexcept {
    iterator iter = begin();
    reference ret = *iter;

    return ret;
  }
  const_reference front() const noexcept {
    const_iterator iter = begin();
    const_reference ret = *iter;

    return ret;
  }

  reference back() noexcept {
    iterator iter = end();
    --iter;
    reference ret = *iter;

    return ret;
  }
  const_reference back() const noexcept {
    const_iterator iter = end();
    --iter;
    const_reference ret = *iter;

    return ret;
  }

  T *data() noexcept { return array_; }
  const T *data() const noexcept { return array_; }

  iterator begin() noexcept {
    iterator ret(array_);

    return ret;
  }
  const_iterator begin() const noexcept {
    const_iterator ret(array_);

    return ret;
  }

  iterator end() noexcept {
    iterator ret(array_ + N);

    return ret;
  }
  const_iterator end() const noexcept {
    const_iterator ret(array_ + N);

    return ret;
  }

  bool empty() const noexcept {
    bool ret = this->begin() == this->end();

    return ret;
  }

  constexpr size_type size() const noexcept {
    size_type ret = N;

    return ret;
  }

  constexpr size_type max_size() const noexcept {
    size_type ret = size();

    return ret;
  }

  void swap(array &other) {
    array array(other);

    other = std::move(*this);
    *this = std::move(array);
  }

  void fill(const_reference value) noexcept {
    if (!empty())
      for (auto item = begin(), end_iter = end(); item != end_iter; ++item)
        *item = value;
  }

 private:
  value_type array_[N];

  template <class C>
  void InitializeArray_(C items) noexcept {
    if (!empty()) {
      auto iter = begin();
      auto end_iter = end();
      for (auto item = items.begin(), end = items.end();
           item != end && iter != end_iter; ++item, ++iter)
        *iter = *item;
      for (; iter != end_iter; ++iter) *iter = {};
    }
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= N)
      throw std::out_of_range(
          "Incorrect input, index is outside the array size");
  }
};
}  // namespace s21

#endif  // S21_ARRAY_H
