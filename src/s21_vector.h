#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

namespace s21 {
template <class T>
class vector {
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

  void copy_vector(const vector &v) noexcept {
    if (arr && m_capacity >= v.m_size)
      for (size_type i = 0; i < v.m_size; ++i) arr[i] = v.arr[i];
  }

  void check_bounds_(size_type pos) const {
    if (pos >= m_size)
      throw std::out_of_range("Incorrect input, index is outside the vector");
  }

  void delete_value_() {
    delete[] arr;
    set_private_fields_(0U, 0U, nullptr);
  }

 public:
  vector() { set_private_fields_(0U, 0U, nullptr); }

  explicit vector(size_type n) { set_private_fields_(n, n, nullptr); }

  explicit vector(std::initializer_list<value_type> const &items) {
    size_type n;

    n = items.size();
    set_private_fields_(n, n, nullptr);
    if (arr)
      for (auto i = 0, item = items.begin(), end = items.end(); item < end;
           i++, item++)
        arr[i] = *item;
  }

  vector(const vector &v) {
    set_private_fields_(v.m_size, v.m_capacity, nullptr);
    copy_vector(v);
  }

  vector(vector &&v) {
    set_private_fields_(v.m_size, v.m_capacity, v.arr);
    v.set_private_fields_(0U, 0U, nullptr);
  }

  ~vector() { delete[] arr; }

  vector &operator=(const vector &v) {
    if (this != &v) {
      delete[] arr;
      set_private_fields_(v.m_size, v.m_capacity, nullptr);
      copy_vector(v);
    }

    return *this;
  }

  vector &operator=(vector &&v) {
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

  reference at(size_type pos) const {
    check_bounds_(pos);

    return arr[pos];
  }

  size_type size() { return m_size; }
  size_type capacity() { return m_capacity; }
  void push_back(value_type v);
};
}  // namespace s21

#endif  // SRC_S21_VECTOR_H
