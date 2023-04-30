#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

#include <memory>
#include <stdexcept>

#include "./s21_sequence_container.h"

namespace S21 {
template <class T>
class Vector : public SequenceContainer<T, T *> {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  Vector() : SequenceContainer<T, T *>() {}

  explicit Vector(size_type n)
      : SequenceContainer<T, T *>(CreatContainer_, n) {}

  explicit Vector(std::initializer_list<value_type> const &items)
      : SequenceContainer<T, T *>(CreatContainer_, items) {}

  // Vector(const Vector &v) : Vector() { *this = v; }
  /*
            Vector(Vector &&v) : SequenceContainer<T>(v) {}
        */
  // ~Vector() { delete[] SequenceContainer<T, T *>::array_; }

  Vector &operator=(const Vector &v) {
    return (Vector &)SequenceContainer<T, T *>::Copy(CreatContainer_, v);
  }
  /*
          Vector &operator=(Vector &&v) { return (Vector
          &)SequenceContainer<T>::operator=(v); }
      */
  reference At(size_type pos) {
    CheckSizeBounds_(pos);

    return SequenceContainer<T, T *>::array_[pos];
  }
  const_reference At(size_type pos) const {
    CheckSizeBounds_(pos);

    return SequenceContainer<T, T *>::array_[pos];
  }
  /*
      reference operator[](size_type pos) noexcept { return
     SequenceContainer<T>::array_[pos]; } const_reference operator[](size_type
     pos) const noexcept { return SequenceContainer<T>::array_[pos];
      }

      T *Data() noexcept { return SequenceContainer<T>::array_; }
      const T *Data() const noexcept { return SequenceContainer<T>::array_; }

      void Reserve(size_type size) {
        if (size > capacity_) Reserve_(size);
      }
  */
  size_type Capacity() const noexcept { return capacity_; }
  /*
      void ShrinkToFit() {
        if (capacity_ > SequenceContainer<T>::size_)
      Reserve_(SequenceContainer<T>::size_);
      }
    */

 protected:
  void SetPrivateFields_(const SequenceContainer<T, T *> &v) {
    std::cout << "v.size_ = " << v.size_ << std::endl;
    SequenceContainer<T, T *>::size_ = v.size_;
    capacity_ = v.size_;
    SequenceContainer<T, T *>::array_ = nullptr;
    // CreatContainer_();
  }

  void InsertReserve_(T *begin, T *end, T *pos) {
    if (SequenceContainer<T, T *>::size_ == capacity_) {
      if (capacity_ > 0)
        capacity_ *= 2;
      else
        capacity_ = 1;
      Reserve_(capacity_);
      end = SequenceContainer<T, T *>::End();
      pos += SequenceContainer<T, T *>::Begin() - begin;
    }
  }

  static T *CreatContainer_(T *array, size_type n) {
    if (array) delete[] array;
    if (n > 0)
      array = new value_type[n]{};
    else
      array = nullptr;

    return array;
  }

 private:
  size_type capacity_ = SequenceContainer<T, T *>::size_;

  /*
    void SetPrivateFields_(size_type size, size_type capacity,
                           value_type *array) {
      SequenceContainer<T, T *>::size_ = size;
      capacity_ = capacity;
      SequenceContainer<T, T *>::array_ = array;
      CreatContainer_();
    }
  */
  void CopyVector_(const Vector &v) noexcept {
    int m;

    m = std::min(v.size_, std::min(capacity_, v.capacity_));
    if (SequenceContainer<T, T *>::array_) {
      for (auto j = 0; j < m; j++)
        SequenceContainer<T, T *>::array_[j] = v.array_[j];
      SequenceContainer<T, T *>::size_ = m;
    }
  }

  void CheckSizeBounds_(size_type pos) const {
    if (pos >= SequenceContainer<T, T *>::size_)
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
