#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H

#include <memory>
#include <stdexcept>

namespace s21 {
template <class T>
class list {
 private:
  size_t m_size;
  typedef struct s_item {
    T value;
    s_item *next;
    s_item *back;
  } t_item;
  t_item *head;
  t_item *tail;
  t_item *item;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = t_item *;
  using const_iterator = const t_item *;
  using size_type = size_t;

  void set_private_fields_(size_type size, value_type *head, value_type *tail) noexcept {
    m_size = size;
    this->head = head;
    this->tail = tail;
    item = nullptr;
    if (size > 0 && head == nullptr) {
      head = reserve_(nullptr, nullptr);
      tail = head;
      for (auto i = 1; i < size; i++)
        tail = reserve_(tail, nullptr);
    }
  }

  void copy_(const list &l) noexcept {
    m_size = 0;
    l.item = l.head;
    item = head;
    do {
      m_size++;
      item->value = l.item->value;
      l.item = l.item->next;
      item = item->next;
    } while (l.item != nullptr && item != nullptr);
    item = nullptr;
  }

  void check_bounds_(size_type pos) const {
    if (pos >= m_size)
      throw std::out_of_range("Incorrect input, index is outside the vector");
  }

  void delete_() {
    do {
      head = head->next;
      delete head->back;
    } while (head != nullptr);
    set_private_fields_(0U, nullptr, nullptr);
  }

  iterator reserve_(t_item *back, t_item *next) {
    item = new t_item;
    item->back = back;
    item->next = next;

    return item;
  }

  void set_value_(value_type value) {
    if (item) {
      item->value = value;
      item = item->next;
    }
  }

 public:
  list() { set_private_fields_(0U, nullptr, nullptr); }

  explicit list(size_type n) { set_private_fields_(n, nullptr, nullptr); }

  explicit list(std::initializer_list<value_type> const &items) {
    size_type n;

    n = items.size();
    set_private_fields_(n, nullptr, nullptr);
    if (head) {
      item = head;
      for (auto item = items.begin(), end = items.end(); item < end; item++)
        set_value_(*item);
    }
  }

  list(const list &l) {
    set_private_fields_(l.m_size, nullptr, nullptr);
    copy_(l);
  }

  list(list &&l) {
    set_private_fields_(l.m_size, l.head, l.tail);
    l.set_private_fields_(0U, nullptr, nullptr);
  }

  ~list() { delete_(); }

  vector &operator=(const vector &v) {
    if (this != &v) {
      delete[] arr;
      set_private_fields_(v.m_size, v.m_capacity, nullptr);
      copy_vector_(v);
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

  void swap(vector &other) {
    vector tmp(other);

    other = std::move(*this);
    *this = std::move(tmp);
  }
};
}  // namespace s21

#endif  // SRC_S21_LIST_H
