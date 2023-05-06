#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <memory>
#include <stdexcept>

#include "./s21_sequence_container.h"
#include "./s21_vectoriterator.h"

namespace S21 {
template <class T>
class Vector : public SequenceContainer<T, VectorIterator<T>> {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator<T>;
  using size_type = size_t;

 public:
  Vector() : SequenceContainer<T, VectorIterator<T>>() {}

  explicit Vector(size_type n) : SequenceContainer<T, VectorIterator<T>>(n) {}

  explicit Vector(std::initializer_list<value_type> const &items)
      : SequenceContainer<T, VectorIterator<T>>(items) {}

  Vector(Vector &v) : SequenceContainer<T, VectorIterator<T>>(v) {}

  Vector(Vector &&v) : SequenceContainer<T, VectorIterator<T>>(std::move(v)) {}

  ~Vector() {}

  Vector &operator=(Vector &v) {
    return (Vector &)SequenceContainer<T, VectorIterator<T>>::operator=(v);
  }

  Vector &operator=(Vector &&v) {
    return (Vector &)SequenceContainer<T, VectorIterator<T>>::operator=(std::move(v));
  }

  reference At(size_type pos) {
    iterator iter;
  
    CheckSizeBounds_(pos);

    iter = SequenceContainer<T, VectorIterator<T>>::Begin();
    iter = iter + pos;

    return *iter;
  }
  /*
  const_reference At(size_type pos) const {
    CheckSizeBounds_(pos);

    return *(SequenceContainer<T, VectorIterator<T>>::Begin() + pos);
  }
*/

  reference operator[](size_type pos) noexcept {
    return *(Data() + pos);
  }
  /*
  const_reference operator[](size_type pos) const noexcept {
    return *(SequenceContainer<T, VectorIterator<T>>::Begin() + pos);
  }
*/
  T *Data() noexcept { return SequenceContainer<T, VectorIterator<T>>::array_.Data(); }
  const T *Data() const noexcept {
    return SequenceContainer<T, VectorIterator<T>>::array_.Data();
  }

  size_type MaxSize() const noexcept {
    std::allocator<value_type> alloc;

    return alloc.max_size();
  }

  void Reserve(size_type size) {
    if (size > SequenceContainer<T, VectorIterator<T>>::capacity_)
      Reserve_(size);
  }

  size_type Capacity() const noexcept {
    return SequenceContainer<T, VectorIterator<T>>::capacity_;
  }

  void ShrinkToFit() {
    if (SequenceContainer<T, VectorIterator<T>>::capacity_ >
        SequenceContainer<T, VectorIterator<T>>::size_)
      Reserve_(SequenceContainer<T, VectorIterator<T>>::size_);
  }

  void Clear() noexcept { SequenceContainer<T, VectorIterator<T>>::size_ = 0; this->array_.SetTail(0); }

  iterator Insert(iterator pos, const_reference value) {
    iterator begin;
    iterator end;

    begin = SequenceContainer<T, VectorIterator<T>>::Begin();
    end = SequenceContainer<T, VectorIterator<T>>::End();
    if ((SequenceContainer<T, VectorIterator<T>>::size_ == 0) ||
        (pos >= begin && pos <= end)) {
      if (SequenceContainer<T, VectorIterator<T>>::size_ ==
          SequenceContainer<T, VectorIterator<T>>::capacity_) {
        if (SequenceContainer<T, VectorIterator<T>>::capacity_ > 0)
          SequenceContainer<T, VectorIterator<T>>::capacity_ *= 2;
        else
          SequenceContainer<T, VectorIterator<T>>::capacity_ = 1;
        Reserve_(SequenceContainer<T, VectorIterator<T>>::capacity_);
        end = SequenceContainer<T, VectorIterator<T>>::End();
        pos = SequenceContainer<T, VectorIterator<T>>::Begin() + (pos - begin);
      }
      for (auto iter = end; iter > pos; --iter) *iter = *(iter - 1);
      *pos = value;
      SequenceContainer<T, VectorIterator<T>>::size_ += 1;
    }

    return pos;
  }

  void PushBack(const_reference value) {
    Insert(SequenceContainer<T, VectorIterator<T>>::End(), value);
  }

 private:
  void CopyVector_(Vector &v) noexcept {
    int m;

    m = std::min(v.size_,
                 std::min(SequenceContainer<T, VectorIterator<T>>::capacity_,
                          v.capacity_));
      for (auto j = 0; j < m; j++)
        this->At(j) = v.At(j);
      SequenceContainer<T, VectorIterator<T>>::size_ = m;
      this->array_.SetTail(m);
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= SequenceContainer<T, VectorIterator<T>>::size_)
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
