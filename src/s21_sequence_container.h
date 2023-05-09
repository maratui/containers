#ifndef SRC_S21_SEQUENCE_CONTAINER_H
#define SRC_S21_SEQUENCE_CONTAINER_H

namespace S21 {
template <class T, class I, class CI, class A>
class SequenceContainer {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = I;
  using const_iterator = CI;
  using size_type = size_t;

 public:
  explicit SequenceContainer() {}

  explicit SequenceContainer(size_type n) : size_(n) {
    std::tie(head_, tail_) = A::Allocate(n);
    std::tie(container.head_, container.tail_) = A::Allocate(n);
  }

  explicit SequenceContainer(std::initializer_list<value_type> const &items)
      : SequenceContainer(items.size()) {
    InitializeContainer_(items);
  }

  SequenceContainer(const SequenceContainer &sc, const size_type capacity)
      : size_(sc.size_) {
    std::tie(head_, tail_) = A::Allocate(capacity);
    std::tie(container.head_, container.tail_) = A::Allocate(capacity);
    CopyContainer_(sc);
  }

  SequenceContainer(SequenceContainer &&sc) noexcept { *this = std::move(sc); }

  ~SequenceContainer() {
    A::Delete(head_);
    A::Delete(container.head_);
  }

  SequenceContainer &operator=(const SequenceContainer &sc) {
    if (this != &sc) *this = SequenceContainer(sc);

    return *this;
  }

  SequenceContainer &operator=(SequenceContainer &&sc) noexcept {
    A::Delete(head_);
    // A::Delete(container.head_);
    if (this != &sc) {
      SetProtectedFields_(sc.size_, sc.head_, sc.tail_);
      sc.SetProtectedFields_(0U, nullptr, nullptr);
    } else {
      SetProtectedFields_(0U, nullptr, nullptr);
    }

    return *this;
  }

  reference Front() noexcept { return *Begin(); }
  const_reference Front() const noexcept { return *Begin(); }

  reference Back() noexcept { return *(--End()); }
  const_reference Back() const noexcept { return *(--End()); }

  iterator Begin() noexcept {
    iterator ret(head_);

    return ret;
  }
  const_iterator Begin() const noexcept {
    const_iterator ret(head_);

    return ret;
  }

  iterator End() noexcept {
    iterator ret(tail_);

    return ret;
  }
  const_iterator End() const noexcept {
    const_iterator ret(tail_);

    return ret;
  }

  bool Empty() const noexcept { return size_ == 0; }

  size_type Size() const noexcept { return size_; }

  void Erase(iterator pos) noexcept {
    auto end = --End();
    for (auto iter = pos; iter < end; ++iter) *iter = *(iter + 1);
    size_ -= 1;
    tail_ = A::SetTail(head_, size_);
    container.tail_ = A::SetTail(container.head_, size_);
  }

  void PopBack() noexcept { Erase(--End()); }

  void Swap(SequenceContainer &other, size_type other_capacity) {
    SequenceContainer sc(other, other_capacity);

    other = std::move(*this);
    *this = std::move(sc);
  }

 protected:
  size_type size_ = 0U;
  value_type *head_ = nullptr;
  value_type *tail_ = nullptr;
  A container;

 private:
  void InitializeContainer_(
      std::initializer_list<value_type> const &items) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = items.begin(), end = items.end(); item < end;
           item++, ++iter)
        *iter = *item;
  }

  void SetProtectedFields_(size_type size, value_type *head,
                           value_type *tail) noexcept {
    size_ = size;
    head_ = head;
    tail_ = tail;

    // container.head_ = head;
    // container.tail_ = tail;
  }

  void CopyContainer_(const SequenceContainer &sc) noexcept {
    auto iter = Begin();
    if (iter != End())
      for (auto item = sc.Begin(), end = sc.End(); item < end; ++item, ++iter)
        *iter = *item;
  }
};
}  // namespace S21

#endif  // SRC_S21_SEQUENCE_CONTAINER_H
