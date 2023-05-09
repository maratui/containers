#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <stdexcept>

#include "./s21_sequence_container.h"
#include "./s21_vector_allocate.h"
#include "./s21_vector_iterator.h"

namespace S21 {
template <class T>
class Vector : public SequenceContainer<T, VectorIterator<T>, VectorIterator<T>,
                                        VectorAllocate<T>> {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorIterator<T>;
  using size_type = size_t;
  using VA = VectorAllocate<T>;
  using SC = SequenceContainer<T, VectorIterator<T>, VectorIterator<T>,
                               VectorAllocate<T>>;

 public:
  Vector() : SC() {}

  explicit Vector(size_type n) : SC(n), capacity_(n) {}

  explicit Vector(std::initializer_list<value_type> const &items)
      : SC(items), capacity_(items.size()) {}

  Vector(const Vector &v) : SC(v, v.capacity_), capacity_(v.capacity_) {
    this->tail_ = VA::SetTail(this->head_, this->size_);
    // this->container.tail_ = VA::SetTail(this->container.head_, this->size_);
  }

  Vector(Vector &&v) noexcept { *this = std::move(v); }

  ~Vector() {}

  Vector &operator=(const Vector &v) {
    if (this != &v) *this = Vector(v);

    return *this;
  }

  Vector &operator=(Vector &&v) noexcept {
    VA::Delete(this->head_);
    // VA::Delete(this->container.head_);
    if (this != &v) {
      SetProtectedFields_(v.size_, v.head_, v.tail_, v.capacity_);
      v.SetProtectedFields_(0U, nullptr, nullptr, 0U);
    } else {
      SetProtectedFields_(0U, nullptr, nullptr, 0U);
    }

    return *this;
  }

  reference At(size_type pos) {
    CheckSizeBounds_(pos);

    return (*this)[pos];
  }
  const_reference At(size_type pos) const {
    CheckSizeBounds_(pos);

    return (*this)[pos];
  }

  reference operator[](size_type pos) noexcept {
    iterator iter;

    iter = this->Begin();
    iter = iter + pos;

    return *iter;
  }

  const_reference operator[](size_type pos) const noexcept {
    const_iterator iter;

    iter = this->Begin();
    iter = iter + pos;

    return *iter;
  }

  T *Data() noexcept { return (T *)this->head_; }
  const T *Data() const noexcept { return (T *)this->head_; }

  size_type MaxSize() const noexcept {
    std::allocator<VectorAllocate<T>> alloc;

    return alloc.max_size();
  }

  void Reserve(size_type size) {
    if (size > capacity_) Reserve_(size);
  }

  size_type Capacity() const noexcept { return capacity_; }

  void ShrinkToFit() {
    if (capacity_ > this->size_) Reserve_(this->size_);
  }

  void Clear() noexcept {
    this->size_ = 0;
    this->tail_ = VA::SetTail(this->head_, this->size_);
  }

  iterator Insert(iterator pos, const_reference value) {
    iterator begin;
    iterator end;

    begin = this->Begin();
    end = this->End();
    if ((this->size_ == 0) || (pos >= begin && pos <= end)) {
      if (this->size_ == capacity_) {
        if (capacity_ > 0)
          capacity_ *= 2;
        else
          capacity_ = 1;
        Reserve_(capacity_);
        end = this->End();
        pos = this->Begin() + (pos - begin);
      }
      for (auto iter = end; iter > pos; --iter) *iter = *(iter - 1);
      *pos = value;
      this->size_ += 1;
      this->tail_ = VA::SetTail(this->head_, this->size_);
    }

    return pos;
  }

  void PushBack(const_reference value) { Insert(this->End(), value); }

  void Swap(Vector &other) {
    SC::Swap(other, other.capacity_);
    std::swap(capacity_, other.capacity_);
  }

 private:
  size_type capacity_ = 0U;

  void CopyVector_(const Vector &v) noexcept {
    int m;

    m = std::min(v.size_, std::min(capacity_, v.capacity_));
    for (auto j = 0; j < m; j++) this->head_[j] = v.head_[j];

    this->size_ = m;
    this->tail_ = VA::SetTail(this->head_, this->size_);
  }

  void SetProtectedFields_(size_type size, VectorAllocate<T> *head,
                           VectorAllocate<T> *tail,
                           size_type capacity) noexcept {
    this->size_ = size;
    this->head_ = head;
    this->tail_ = tail;
    capacity_ = capacity;

    // this->container.head_ = head;
    // this->container.tail_ = tail;
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= this->size_)
      throw std::out_of_range(
          "Incorrect input, index is outside the vector size");
  }

  void Reserve_(size_type size) {
    Vector vector(size);

    vector.CopyVector_(*this);
    *this = std::move(vector);
  }
};
}  // namespace S21

#endif  // SRC_S21_VECTOR_H
