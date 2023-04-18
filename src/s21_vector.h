#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <memory>
#include <stdexcept>

namespace S21 {
template <class T>
class Vector {
 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  void set_private_fields_(size_type size, size_type capacity,
                           value_type *arr) {
    m_size = size;
    m_capacity = capacity;
    this->arr = arr;
    if (!arr && capacity) this->arr = new value_type[capacity];
  }

  void copy_vector_(const Vector &v) noexcept {
    if (arr && m_capacity >= v.m_size) {
      for (size_type i = 0; i < v.m_size; ++i) arr[i] = v.arr[i];
      for (size_type i = v.m_size; i < m_capacity; ++i) arr[i] = 0;
      m_size = v.m_size;
    }
  }

  void check_bounds_(size_type pos) const {
    if (pos >= m_size)
      throw std::out_of_range("Incorrect input, index is outside the vector");
  }

  void delete_value_() {
    delete[] arr;
    set_private_fields_(0U, 0U, nullptr);
  }

  void reserve_(size_type size) {
    Vector new_vector(size);
    new_vector.copy_vector_(*this);
    *this = std::move(new_vector);
  }

 public:
  Vector() { set_private_fields_(0U, 0U, nullptr); }

  explicit Vector(size_type n) { set_private_fields_(n, n, nullptr); }

  explicit Vector(std::initializer_list<value_type> const &items) {
    size_type n;

    n = items.size();
    set_private_fields_(n, n, nullptr);
    if (arr)
      for (auto i = 0, item = items.begin(), end = items.end(); item < end;
           i++, item++)
        arr[i] = *item;
  }

  Vector(const Vector &v) {
    set_private_fields_(v.m_size, v.m_capacity, nullptr);
    copy_vector_(v);
  }

  Vector(Vector &&v) {
    set_private_fields_(v.m_size, v.m_capacity, v.arr);
    v.set_private_fields_(0U, 0U, nullptr);
  }

  ~Vector() { delete[] arr; }

  Vector &operator=(const Vector &v) {
    if (this != &v) {
      delete[] arr;
      set_private_fields_(v.m_size, v.m_capacity, nullptr);
      copy_vector_(v);
    }

    return *this;
  }

  Vector &operator=(Vector &&v) {
    delete_value_();
    if (this != &v) {
      set_private_fields_(v.m_size, v.m_capacity, v.arr);
      v.set_private_fields_(0U, 0U, nullptr);
    }

    return *this;
  }

  reference at(size_type pos) {
    check_bounds_(pos);

    return arr[pos];
  }
  const_reference at(size_type pos) const {
    check_bounds_(pos);

    return arr[pos];
  }

  reference operator[](size_type pos) { return arr[pos]; }
  const_reference operator[](size_type pos) const { return arr[pos]; }

  reference front() { return arr[0]; }
  const_reference front() const { return arr[0]; }

  reference back() { return arr[m_size - 1]; }
  const_reference back() const { return arr[m_size - 1]; }

  T *data() noexcept { return arr; }
  const T *data() const noexcept { return arr; }

  iterator begin() noexcept { return arr; }
  const_iterator begin() const noexcept { return arr; }

  iterator end() noexcept { return arr + m_size; }
  const_iterator end() const noexcept { return arr + m_size; }

  bool empty() const noexcept {
    bool ret;

    if (m_size > 0)
      ret = false;
    else
      ret = true;

    return ret;
  }

  size_type size() const noexcept { return m_size; }

  size_type max_size() const noexcept {
    std::allocator<value_type> alloc;

    return alloc.max_size();
  }

  void reserve(size_type size) {
    if (size > this->m_capacity) reserve_(size);
  }

  size_type capacity() const noexcept { return m_capacity; }

  void shrink_to_fit() {
    if (m_capacity > m_size) reserve_(m_size);
  }

  void clear() noexcept { m_size = 0; }

  iterator insert(iterator pos, const_reference value) {
    iterator start;
    iterator finish;

    start = this->begin();
    finish = this->end();
    if ((m_capacity == 0) || ((pos + 1) > start && (pos - 1) < finish)) {
      if (m_size == m_capacity) {
        if (m_capacity)
          m_capacity *= 2;
        else
          m_capacity = 1;
        reserve_(m_capacity);
        finish = this->end();
      }
      pos += this->begin() - start;
      for (auto i = finish; i > pos; --i) *i = *(i - 1);
      *pos = value;
      m_size++;
    }

    return pos;
  }

  void erase(iterator pos) {
    iterator finish;

    finish = end() - 1;
    for (auto i = pos; i < finish; ++i) *i = *(i + 1);
    m_size--;
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(end() - 1); }

  void swap(Vector &other) {
    Vector tmp(other);

    other = std::move(*this);
    *this = std::move(tmp);
  }
};
}  // namespace S21

#endif  // SRC_S21_VECTOR_H
