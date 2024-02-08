#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_SEQUENCE_CONTAINERS_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_SEQUENCE_CONTAINERS_H

#include <memory>

namespace s21 {
template <class VT, class IT, class I, class CI>
class SequenceContainer {
 public:
  using value_type = VT;
  using reference = VT &;
  using const_reference = const VT &;
  using item_type = IT;
  using iterator = I;
  using const_iterator = CI;
  using size_type = std::size_t;

  reference front() noexcept {
    iterator begin_iter = begin();
    reference ret = *begin_iter;

    return ret;
  }
  const_reference front() const noexcept {
    const_iterator begin_iter = begin();
    const_reference ret = *begin_iter;

    return ret;
  }

  reference back() noexcept {
    iterator end_iter = end();
    --end_iter;
    reference ret = *end_iter;

    return ret;
  }
  const_reference back() const noexcept {
    const_iterator end_iter = end();
    --end_iter;
    const_reference ret = *end_iter;

    return ret;
  }

  iterator begin() noexcept {
    iterator ret(head_);

    return ret;
  }
  const_iterator begin() const noexcept {
    const_iterator ret(head_);

    return ret;
  }

  iterator end() noexcept {
    iterator ret(tail_);

    return ret;
  }
  const_iterator end() const noexcept {
    const_iterator ret(tail_);

    return ret;
  }

  bool empty() const noexcept {
    bool ret = begin() == end();

    return ret;
  }

  constexpr size_type size() const noexcept { return size_; }

  constexpr size_type max_size() const noexcept {
    std::allocator<item_type> alloc;

    return alloc.max_size();
  }

  void clear() noexcept {
    size_ = 0;
    tail_ = FindTail(head_, size_);
  }

  virtual iterator insert(iterator pos, const_reference value) = 0;

  virtual void erase(iterator pos) noexcept = 0;

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() noexcept {
    if (!empty()) {
      iterator end_iter = this->end();
      --end_iter;
      erase(end_iter);
    }
  }

 protected:
  size_type size_ = 0U;
  item_type *head_ = nullptr;
  item_type *tail_ = nullptr;

  void InitializeContainer(
      std::initializer_list<value_type> const &items) noexcept {
    auto iter = begin();
    if (!empty())
      for (auto item = items.begin(), end = items.end(); item != end;
           item++, ++iter)
        *iter = *item;
  }

  void CopyContainer(const SequenceContainer &sc) noexcept {
    auto iter = begin();
    if (!empty())
      for (auto item = sc.begin(), end = sc.end(); item != end; ++item, ++iter)
        *iter = *item;
  }

  void SetProtectedFields(size_type size, item_type *head,
                          item_type *tail) noexcept {
    size_ = size;
    head_ = head;
    tail_ = tail;
  }

  size_type FindIterator(iterator pos) noexcept {
    size_type ret = 0U;

    for (iterator iter = begin(); iter != pos; ++iter) ++ret;

    return ret;
  }
  iterator GetIterator(size_type pos) noexcept {
    iterator ret = begin();

    for (size_type i = 0U; i < pos; ++i) ++ret;

    return ret;
  }

  size_type FindConstIterator(const_iterator pos) noexcept {
    size_type ret = 0U;

    for (const_iterator iter = begin(); iter != pos; ++iter) ++ret;

    return ret;
  }

  virtual item_type *FindTail(item_type *head, size_type size) noexcept = 0;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_SEQUENCE_CONTAINERS_H
