#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <stdexcept>

#include "../s21_allocators/s21_vector_allocator.h"
#include "../s21_iterators/s21_vector_const_iterator.h"
#include "../s21_iterators/s21_vector_iterator.h"
#include "./s21_sequence_container.h"

namespace s21 {
template <class T>
class vector : public SequenceContainer<T, T, VectorIterator<T>,
                                        VectorConstIterator<T>> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = std::size_t;
  using item_type = T;
  using allocator = VectorAllocator<T>;

  vector() {}

  explicit vector(size_type n) {
    CheckMaxSize_(n);

    this->size_ = n;
    capacity_ = n;
    std::tie(this->head_, this->tail_) =
        allocator::Allocate(this->size_, capacity_);
  }

  explicit vector(std::initializer_list<value_type> const &items)
      : vector(items.size()) {
    this->InitializeContainer_(items);
  }

  vector(const vector &v) : capacity_(v.capacity_) {
    CheckMaxSize_(capacity_);

    this->size_ = v.size_;
    std::tie(this->head_, this->tail_) =
        allocator::Allocate(this->size_, capacity_);
    this->CopyContainer_(v);
  }

  vector(vector &&v) noexcept { *this = std::move(v); }

  ~vector() { this->head_ = allocator::Delete(this->head_); }

  vector &operator=(vector &&v) noexcept {
    this->head_ = allocator::Delete(this->head_);
    if (this != &v) {
      capacity_ = v.capacity_;
      this->SetProtectedFields_(v.size_, v.head_, v.tail_);
      v.capacity_ = 0U;
      v.SetProtectedFields_(0U, nullptr, nullptr);
    } else {
      capacity_ = 0U;
      this->SetProtectedFields_(0U, nullptr, nullptr);
    }

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
    iterator iter = this->begin();
    for (size_type j = 0UL; j < pos; j += 1UL) ++iter;
    reference ret = *iter;

    return ret;
  }
  const_reference operator[](size_type pos) const noexcept {
    const_iterator iter = this->begin();
    for (size_type j = 0UL; j < pos; j += 1UL) ++iter;
    const_reference ret = *iter;

    return ret;
  }

  T *data() noexcept {
    T *ret = (T *)this->head_;

    return ret;
  }
  const T *data() const noexcept {
    const T *ret = (const T *)this->head_;

    return ret;
  }

  void reserve(size_type size) {
    if (size > capacity_) Reserve_(size);
  }

  constexpr size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ > this->size_) Reserve_(this->size_);
  }

  iterator insert(iterator pos, const_reference value) override {
    CheckMaxSize_(this->size() + 1);

    size_type p = this->FindIterator_(pos);
    AddNewItem_(p);

    iterator ret = this->GetIterator_(p);
    *ret = value;

    return ret;
  }

  void erase(iterator pos) noexcept override {
    if (!this->empty()) {
      iterator liter = this->begin();
      iterator riter = this->begin();
      ++riter;
      for (; liter != pos; ++liter, ++riter) {
      }
      iterator end_iter = this->end();
      --end_iter;
      for (; liter != end_iter; ++liter, ++riter) *liter = *riter;
      this->size_ -= 1;
      this->tail_ = allocator::SetTail(this->head_, this->size_);
    }
  }

  void swap(vector &other) {
    vector v(other);

    other = std::move(*this);
    *this = std::move(v);
  }

  iterator insert_many(const_iterator pos) {
    CheckMaxSize_(this->size() + 1);

    size_type p = this->FindConstIterator_(pos);
    AddNewItem_(p);
    *(this->head_ + p) = std::move(item_type());
    iterator ret = this->GetIterator_(p);

    return ret;
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    CheckMaxSize_(this->size() + sizeof...(args));

    size_type p = this->FindConstIterator_(pos);
    for (item_type arg : {args...}) {
      AddNewItem_(p);
      *(this->head_ + p) = std::move(arg);
    }
    iterator ret = this->GetIterator_(p);

    return ret;
  }

  void insert_many_back() { insert_many(this->end()); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (item_type arg : {args...}) insert_many(this->end(), std::move(arg));
  }

 protected:
  value_type *SetTail_(value_type *head, size_type size) noexcept override {
    value_type *tail;

    tail = allocator::SetTail(head, size);

    return tail;
  }

 private:
  size_type capacity_ = 0U;

  void CheckMaxSize_(size_type size) {
    if (size > this->max_size())
      throw std::length_error(
          "Incorrect input, cannot create s21::vector larger than max_size()");
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= this->size_)
      throw std::out_of_range(
          "Incorrect input, index is outside the vector size");
  }

  void Reserve_(size_type size) {
    vector v(size);

    v.CopyVector_(*this);
    *this = std::move(v);
  }

  void CopyVector_(const vector &v) noexcept {
    auto iter = this->begin();
    auto v_iter = v.begin();
    size_type m = std::min(v.size_, std::min(capacity_, v.capacity_));
    for (size_type j = 0UL; j < m; j += 1UL, ++iter, ++v_iter) *iter = *v_iter;

    this->size_ = m;
    this->tail_ = allocator::SetTail(this->head_, this->size_);
  }

  void AddNewItem_(size_type pos) {
    std::tie(this->size_, this->capacity_, this->head_, this->tail_) =
        allocator::Append(this->size_, this->capacity_, this->max_size(),
                          this->head_, this->tail_);

    iterator liter = this->end();
    --liter;
    iterator riter = this->end();
    --riter;
    --riter;
    for (size_type j = this->size_ - 1UL; j > pos; j -= 1UL, --liter, --riter)
      *liter = *riter;
  }
};
}  // namespace s21

#endif  // S21_VECTOR_H
