#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <memory>
#include <stdexcept>

#include "./s21_sequence_container.h"
#include "./s21_vector_const_iterator.h"
#include "./s21_vector_iterator.h"
#include "./s21_vector_allocate.h"

namespace S21 {
template <class T>
class Vector
    : public SequenceContainer<T, VectorIterator<T>, VectorConstIterator<T>, VectorAllocate<T>> {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = size_t;

 public:
  Vector()
      : SequenceContainer<T, VectorIterator<T>, VectorConstIterator<T>, VectorAllocate<T>>() {}

  explicit Vector(size_type n)
      : SequenceContainer<T, VectorIterator<T>, VectorConstIterator<T>, VectorAllocate<T>>(n), capacity_(n) {}
  
  explicit Vector(std::initializer_list<value_type> const &items)
      : SequenceContainer<T, VectorIterator<T>, VectorConstIterator<T>, VectorAllocate<T>>(items), capacity_(items.size()) {}
  
  Vector(const Vector &v)
      : SequenceContainer<T, VectorIterator<T>, VectorConstIterator<T>, VectorAllocate<T>>(v, v.capacity_), capacity_(v.capacity_) {}
  
  Vector(Vector &&v) noexcept {*this = std::move(v);}

  ~Vector() {}

  Vector &operator=(const Vector &v) {
    if (this != &v)
      *this = Vector(v);

    return *this;
  }

  Vector operator=(Vector &&v) noexcept {
    VectorAllocate<T>::Delete(this->head_);
    if (this != &v) {
      SetProtectedFields_(v.size_, v.head_, v.tail_, v.capacity_);
      v.SetProtectedFields_(0U, nullptr, nullptr, 0U);
    } else {
      SetProtectedFields_(0U, nullptr, nullptr, 0U);
    }

    return *this;
  }

  reference At(size_type pos) {
    iterator iter;

    CheckSizeBounds_(pos);

    iter = this->Begin();
    iter = iter + pos;

    return *iter;
  }
  const_reference At(size_type pos) const {
    const_iterator iter;

    CheckSizeBounds_(pos);

    iter = this->Begin();
    iter = iter + pos;

    return *iter;
  }
/*
  reference operator[](size_type pos) noexcept { return *(Data() + pos); }
*/
  /*
  const_reference operator[](size_type pos) const noexcept {
    return *(Data() + pos);
  }
*/
/*
  T *Data() noexcept { return this->container_.Data(); }
  const T *Data() const noexcept { return this->container_.Data(); }

  size_type MaxSize() const noexcept {
    std::allocator<value_type> alloc;

    return alloc.max_size();
  }

  void Reserve(size_type size) {
    if (size > this->capacity_) Reserve_(size);
  }
*/
  size_type Capacity() const noexcept { return capacity_; }
/*
  void ShrinkToFit() {
    if (this->capacity_ > this->size_) Reserve_(this->size_);
  }

  void Clear() noexcept {
    this->size_ = 0;
    this->container_.SetTail(0);
  }

  iterator Insert(iterator pos, const_reference value) {
    iterator begin;
    iterator end;

    begin = this->Begin();
    end = this->End();
    if ((this->size_ == 0) || (pos >= begin && pos <= end)) {
      if (this->size_ == this->capacity_) {
        if (this->capacity_ > 0)
          this->capacity_ *= 2;
        else
          this->capacity_ = 1;
        Reserve_(this->capacity_);
        end = this->End();
        pos = this->Begin() + (pos - begin);
      }
      for (auto iter = end; iter > pos; --iter) *iter = *(iter - 1);
      *pos = value;
      this->size_ += 1;
      this->container_.SetTail(this->size_);
    }

    return pos;
  }

  void PushBack(const_reference value) { Insert(this->End(), value); }
*/
 private:
  size_type capacity_ = 0U;

  void CopyVector_(const Vector &v) noexcept {
    int m;

    m = std::min(v.size_, std::min(capacity_, v.capacity_));
    for (auto j = 0; j < m; j++) this->head_[j] = v.head_[j];

    this->size_ = m;
    this->tail_ = VectorAllocate<T>::SetTail(this->head_, this->size_);
  }

  void SetProtectedFields_(size_type size, value_type *head, value_type *tail, size_type capacity) noexcept {
    this->size_ = size;
      this->head_ = head;
      this->tail_ = tail;
      capacity_ = capacity;
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= this->size_)
      throw std::out_of_range(
          "Incorrect input, index is outside the vector size");
  }
/*
  void Reserve_(size_type size) {
    Vector vector(size);

    vector.CopyVector_(*this);
    *this = std::move(vector);
  }
*/
};
}  // namespace S21

#endif  // SRC_S21_VECTOR_H
