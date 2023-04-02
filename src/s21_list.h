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

  void set_private_fields_(size_type size, t_item *head, t_item *tail) noexcept {
    m_size = size;
    this->head = head;
    this->tail = tail;
    item = nullptr;
    if (size > 0 && head == nullptr) {
      head = reserve_(nullptr, nullptr);
      tail = head;
      for (size_type i = 1; i < size; i++)
        tail = reserve_(tail, nullptr);
    }
  }

  void copy_(const list &l) noexcept {
    m_size = 0;
    l.item = l.head;
    item = head;
    do {
      m_size++;
      set_value_(l.item->value);
      l.item = l.item->next;
    } while (l.item != nullptr && item != nullptr);
    item = nullptr;
  }

  void check_bounds_(size_type pos) const {
    if (pos >= m_size)
      throw std::out_of_range("Incorrect input, index is outside the vector");
  }

  bool check_pos_(iterator pos) {
    bool ret;

    ret = false;
    for (auto item = head; ret == false && item != tail; item = item->next) if (item == pos) ret = true;

    return ret;
  }

  void delete_() {
    while (head != nullptr) {
      head = head->next;
      delete head->back;
    } 
    set_private_fields_(0U, nullptr, nullptr);
  }

  t_item *reserve_(t_item *back, t_item *next) {
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
      this->item = head;
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

  list &operator=(const list &l) {
    if (this != &l) {
      delete_();
      set_private_fields_(l.m_size, l.head, l.tail);
      copy_(l);
    }

    return *this;
  }

  list &operator=(list &&l) {
    delete_();
    if (this != &l) {
      set_private_fields_(l.m_size, l.head, l.tail);
      l.set_private_fields_(0U, nullptr, nullptr);
    }

    return *this;
  }

  reference front() { return head->value; }
  const_reference front() const { return head->value; }

  reference back() { return tail->value; }
  const_reference back() const { return tail->value; }

  iterator begin() noexcept { return head; }
  const_iterator begin() const noexcept { return head; }

  iterator end() noexcept { return tail; }
  const_iterator end() const noexcept { return tail; }

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
    std::allocator<t_item> alloc;

    return alloc.max_size();
  }

  void clear() noexcept { m_size = 0; }

  iterator insert(iterator pos, const_reference value) {
    item = nullptr;
    if (head == nullptr || check_pos_(pos)) {
      if (head) {
        reserve_(pos->back, pos);
        if (pos == head) head = item;
      } else {
        reserve_(nullptr, nullptr);
        head = item;
        tail = head;
      }
      item->value = value;
      m_size++;
    }

    return item;
  }

  void erase(iterator pos) {
    if (check_pos_()) {
      if (pos == head) {
        head = pos->next;
        head->back = nullptr;
      } else {
        pos->back->next = pos->next;
        if (pos == tail) tail = pos->back;
      }
      delete pos;
      m_size--;
    }
  }

  void push_back(const_reference value) {
    tail = reserve_(tail, nullptr);
    tail->value = value;
  }

  void pop_back() { erase(tail); }

  void push_front(const_reference value) { insert(head, value); }

  void pop_front() { erase(head); }


  void swap(list &other) {
    list tmp(other);

    other = std::move(*this);
    *this = std::move(tmp);
  }
};
}  // namespace s21

#endif  // SRC_S21_LIST_H
