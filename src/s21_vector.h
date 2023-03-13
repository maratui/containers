#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <cstring>
#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {
template <class T>
class Vector {
 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  void reserve_more_capacity(size_type size);

 public:
  Vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}
  explicit Vector(size_type n)
      : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity) {
    arr = m_size ? new T[m_size] : nullptr;
    if (arr) std::memcpy(arr, v.arr, m_size * sizeof(T));
  };
  Vector(Vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {
    v.m_size = 0;
    v.m_capacity = 0;
    v.arr = nullptr;
  }
  ~Vector() { delete[] arr; }

  size_type size() { return m_size; }
  value_type at(size_type i) { return arr[i]; }
  void push_back(value_type v);
};
}  // namespace s21

#endif  // SRC_S21_VECTOR_H
