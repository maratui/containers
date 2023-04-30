#ifndef SRC_S21_SEQUENCE_CONTAINER_H
#define SRC_S21_SEQUENCE_CONTAINER_H

#include <iostream>
#include <memory>
#include <stdexcept>

namespace S21 {
template <class T, class I>
class SequenceContainer {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = I;
  using const_iterator = const I;
  using size_type = size_t;

 public:
  SequenceContainer() {}

  explicit SequenceContainer(I (*CreatContainer)(I array, size_type n),
                             size_type n)
      : size_(n) {
    array_ = CreatContainer(array_, n);
  }

  explicit SequenceContainer(I (*CreatContainer)(I array, size_type n),
                             std::initializer_list<value_type> const &items)
      : SequenceContainer(CreatContainer, items.size()) {
    InitializeSequenceContainer_(items);
  }

  SequenceContainer &Copy(I (*CreatContainer)(I array, size_type n),
                          const SequenceContainer &v) {
    if (this != &v) {
      array_ = CreatContainer(array_, v.size_);
      size_ = v.size_;
      CopySequenceContainer_(v);
    }

    return *this;
  }
  /*
            SequenceContainer &operator=(SequenceContainer &&v) noexcept {
              delete[] array_;
              if (this != &v) {
                SetPrivateFields_();
                v.SetPrivateFields_();
              } else {
                SetPrivateFields_();
              }

              return *this;
            }

            reference Front() noexcept { return array_[0]; }
            const_reference Front() const noexcept { return array_[0]; }

            reference Back() noexcept { return array_[size_ - 1]; }
            const_reference Back() const noexcept { return array_[size_ - 1]; }
    */
  iterator Begin() noexcept { return array_; }
  const_iterator Begin() const noexcept { return array_; }

  iterator End() noexcept { return array_ + size_; }
  const_iterator End() const noexcept { return array_ + size_; }
  /*

  `


          bool Empty() const noexcept { return size_ == 0; }
      */
  size_type Size() const noexcept { return size_; }
  /*
      size_type MaxSize() const noexcept {
        std::allocator<value_type> alloc;

        return alloc.max_size();
      }

      void Clear() noexcept { size_ = 0; }

      iterator Insert(iterator pos, const_reference value) {
        auto begin = Begin();
        auto end = End();
        if ((size_ == 0) || (pos >= begin && pos <= end)) {
          InsertReserve_();
          for (auto iter = end; iter > pos; --iter) *iter = *(iter - 1);
          *pos = value;
          size_ += 1;
        }

        return pos;
      }

      void Erase(iterator pos) noexcept {
        auto end = End() - 1;
        for (auto iter = pos; iter < end; iter++) *iter = *(iter + 1);
        size_ -= 1;
      }

      void PushBack(const_reference value) { Insert(End(), value); }

      void PopBack() noexcept { Erase(End() - 1); }

      void Swap(SequenceContainer &other) {
        SequenceContainer vector(other);

        other = std::move(*this);
        *this = std::move(vector);
      }
    */
 protected:
  size_type size_ = 0;
  I array_ = nullptr;

  void virtual SetPrivateFields_() {}

  void InitializeSequenceContainer_(
      std::initializer_list<value_type> const &items) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = items.begin(), end = items.end(); item < end;
           item++, iter++)
        *iter = *item;
  }

  void virtual InsertReserve_() {}

 private:
  void CopySequenceContainer_(const SequenceContainer &v) noexcept {
    auto iter = Begin();
    if (iter != End()) {
      for (auto item = v.Begin(), end = v.End(); item < end; item++, iter++)
        *iter = *item;
    }
  }
  /*
      void CheckSizeBounds_(size_type pos) const {
        if (pos >= size_)
          throw std::out_of_range(
              "Incorrect input, index is outside the vector size");
      }
    */
};
}  // namespace S21

#endif  // SRC_S21_SEQUENCE_CONTAINER_H
