#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <memory>
#include <stdexcept>

namespace S21 {
template <class T>
class Vector {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  Vector() {}

  explicit Vector(size_type n) { SetPrivateFields_(n, n, nullptr); }

  explicit Vector(std::initializer_list<value_type> const &items) {
    SetPrivateFields_(items.size(), items.size(), nullptr);
    if (array_) {
      item_ = array_;
      for (auto item = items.begin(), end = items.end(); item < end; item++)
        *item_++ = *item;
      item_ = nullptr;
    }
  }

  Vector(const Vector &v) { *this = v; }

  Vector(Vector &&v) noexcept { *this = std::move(v); }

  ~Vector() { delete[] array_; }

  Vector &operator=(const Vector &v) {
    if (this != &v) {
      delete[] array_;
      SetPrivateFields_(v.size_, v.capacity_, nullptr);
      CopyVector_(v);
    }

    return *this;
  }

  Vector &operator=(Vector &&v) noexcept {
    delete[] array_;
    if (this != &v) {
      SetPrivateFields_(v.size_, v.capacity_, v.array_);
      v.SetPrivateFields_(0U, 0U, nullptr);
    } else {
      SetPrivateFields_(0U, 0U, nullptr);
    }

    return *this;
  }

  reference at(size_type pos) {
    CheckSizeBounds_(pos);

    return array_[pos];
  }
  const_reference at(size_type pos) const {
    CheckSizeBounds_(pos);

    return array_[pos];
  }

  reference operator[](size_type pos) noexcept { return array_[pos]; }
  const_reference operator[](size_type pos) const noexcept {
    return array_[pos];
  }

  reference front() noexcept { return array_[0]; }
  const_reference front() const noexcept { return array_[0]; }

  reference back() noexcept { return array_[size_ - 1]; }
  const_reference back() const noexcept { return array_[size_ - 1]; }

  T *data() noexcept { return array_; }
  const T *data() const noexcept { return array_; }

  iterator begin() noexcept { return array_; }
  const_iterator begin() const noexcept { return array_; }

  iterator end() noexcept { return array_ + size_; }
  const_iterator end() const noexcept { return array_ + size_; }

  bool empty() const noexcept {
    bool ret;

    if (size_ > 0)
      ret = false;
    else
      ret = true;

    return ret;
  }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    std::allocator<value_type> alloc;

    return alloc.max_size();
  }

  void reserve(size_type size) {
    if (size > this->capacity_) reserve_(size);
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ > size_) reserve_(size_);
  }

  void clear() noexcept { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    iterator start;
    iterator finish;

    start = this->begin();
    finish = this->end();
    if ((capacity_ == 0) || ((pos + 1) > start && (pos - 1) < finish)) {
      if (size_ == capacity_) {
        if (capacity_)
          capacity_ *= 2;
        else
          capacity_ = 1;
        reserve_(capacity_);
        finish = this->end();
      }
      pos += this->begin() - start;
      for (auto i = finish; i > pos; --i) *i = *(i - 1);
      *pos = value;
      size_++;
    }

    return pos;
  }

  void erase(iterator pos) {
    iterator finish;

    finish = end() - 1;
    for (auto i = pos; i < finish; ++i) *i = *(i + 1);
    size_--;
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(end() - 1); }

  void swap(Vector &other) {
    Vector tmp(other);

    other = std::move(*this);
    *this = std::move(tmp);
  }

 private:
  size_type size_ = 0;
  size_type capacity_ = 0;
  value_type *array_ = nullptr;
  value_type *item_ = nullptr;

  void SetPrivateFields_(size_type size, size_type capacity,
                         value_type *array) {
    size_ = size;
    capacity_ = capacity;
    array_ = array;
    item_ = nullptr;
    if (!array_ && capacity_) array_ = new value_type[capacity_]{};
  }

  void CopyVector_(const Vector &v) noexcept {
    int m;

    m = std::min(v.size_, std::min(capacity_, v.capacity_));
    if (array_) {
      for (auto j = 0; j < m; j++) array_[j] = v.array_[j];
      size_ = m;
    }
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= size_)
      throw std::out_of_range(
          "Incorrect input, index is outside the vector size");
  }

  void reserve_(size_type size) {
    Vector new_vector(size);
    new_vector.CopyVector_(*this);
    *this = std::move(new_vector);
  }
};
}  // namespace S21

#endif  // SRC_S21_VECTOR_H
