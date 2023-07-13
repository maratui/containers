#ifndef S21_LIST_H
#define S21_LIST_H

#include <stdexcept>

#include "../s21_allocators/s21_list_allocator.h"
#include "../s21_iterators/s21_list_const_iterator.h"
#include "../s21_iterators/s21_list_iterator.h"
#include "./s21_sequence_container.h"

namespace s21 {
template <class T>
class list : public SequenceContainer<T, struct Item<T>, ListIterator<T>,
                                      ListConstIterator<T>> {
 public:
  using value_type = T;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = std::size_t;
  using item_type = struct Item<T>;
  using allocator = ListAllocator<T>;

  list() { std::tie(this->head_, this->tail_) = allocator::Allocate(0); }

  explicit list(size_type n) {
    CheckMaxSize_(n);

    this->size_ = n;
    std::tie(this->head_, this->tail_) = allocator::Allocate(this->size_);
  }

  explicit list(std::initializer_list<value_type> const &items)
      : list(items.size()) {
    this->InitializeContainer_(items);
  }

  list(const list &l) : list(l.size()) { this->CopyContainer_(l); }

  list(list &&l) noexcept { *this = std::move(l); }

  ~list() { this->head_ = allocator::Delete(this->head_); }

  list &operator=(list &&l) noexcept {
    this->head_ = allocator::Delete(this->head_);
    if (this != &l) {
      this->SetProtectedFields_(l.size_, l.head_, l.tail_);
      l.SetProtectedFields_(0U, nullptr, nullptr);
    } else {
      this->SetProtectedFields_(0U, nullptr, nullptr);
    }

    return *this;
  }

  iterator insert(iterator pos, const_reference value) override {
    CheckMaxSize_(this->size() + 1);

    Splice_(pos, list({value}));
    --pos;

    return pos;
  }

  void erase(iterator pos) noexcept override {
    if (!this->empty()) {
      iterator iter = this->begin();
      item_type *item = this->head_;
      if (pos == iter) this->head_ = this->head_->next;
      for (; iter != pos; ++iter) item = item->next;
      Erase_(item);
      this->size_ -= 1;
    }
  }

  void push_front(const_reference value) { insert(this->begin(), value); }

  void pop_front() noexcept { this->erase(this->begin()); }

  void swap(list &other) {
    list l(other);

    other = std::move(*this);
    *this = std::move(l);
  }

  void merge(list &other) {
    if (this != &other && !other.empty()) {
      Splice_(this->end(), std::move(other));
      sort();
    }
  }

  void splice(const_iterator pos, list &other) noexcept {
    Splice_(pos, std::move(other));
  }

  void reverse() noexcept {
    if (!this->empty()) {
      iterator begin_iter = this->begin();
      iterator end_iter = this->end();
      size_type size = this->size_;
      --end_iter;
      for (size_type j = 0UL; j < size; j += 1U, --end_iter, ++begin_iter) {
        std::swap(*begin_iter, *end_iter);
        size -= 1U;
      }
    }
  }

  void unique() noexcept {
    if (!this->empty()) {
      iterator riter = this->begin();
      ++riter;
      iterator liter = this->begin();
      for (size_type j = 1UL; j < this->size_; j += 1, ++liter, ++riter) {
        if (*liter == *riter) {
          this->erase(riter);
          riter = this->begin();
          ++riter;
          liter = this->begin();
          for (size_type k = 1UL; k < j; k += 1UL, ++liter, ++riter) {
          }
        }
      }
    }
  }

  void sort() {
    if (!this->empty()) {
      iterator riter = this->begin();
      ++riter;
      iterator liter = this->begin();
      for (size_type i = 0UL; i < this->size_ - 1UL; i += 1UL) {
        for (size_type j = 0UL; j < this->size_ - i - 1UL;
             j += 1UL, ++liter, ++riter) {
          if (*liter > *riter) {
            std::swap(*liter, *riter);
          }
        }
        riter = this->begin();
        ++riter;
        liter = this->begin();
      }
    }
  }

  iterator insert_many(const_iterator pos) {
    CheckMaxSize_(this->size() + 1);

    size_type p = this->FindConstIterator_(pos);
    InsertArg_(GetItem_(p), new item_type(), p);
    iterator ret = this->GetIterator_(p);

    return ret;
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    CheckMaxSize_(this->size() + sizeof...(args));

    size_type p = this->FindConstIterator_(pos);
    for (item_type arg : {args...}) {
      InsertArg_(GetItem_(p), new item_type(std::move(arg)), p);
    }
    iterator ret = this->GetIterator_(p);

    return ret;
  }

  void insert_many_back() { insert_many(this->end()); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (item_type arg : {args...}) insert_many(this->end(), std::move(arg));
  }

  void insert_many_front() { insert_many(this->begin()); }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    for (item_type arg : {args...}) insert_many(this->begin(), std::move(arg));
  }

 protected:
  item_type *SetTail_(item_type *head, size_type size) noexcept override {
    item_type *tail;

    tail = allocator::SetTail(head, size);

    return tail;
  }

 private:
  void CheckMaxSize_(size_type size) {
    if (size > this->max_size())
      throw std::length_error(
          "Incorrect input, cannot create s21::list larger than max_size()");
  }

  void Splice_(const_iterator pos, list &&other) noexcept {
    if (this != &other && !other.empty()) {
      size_type p = this->FindConstIterator_(pos);
      item_type *item = GetItem_(p);
      if (p == 0UL) this->head_ = other.head_;
      Transfer_(item, other.head_, other.tail_);
      this->size_ += other.size_;
      other.SetProtectedFields_(0U, nullptr, nullptr);
    }
  }

  void Transfer_(item_type *item, item_type *head, item_type *tail) noexcept {
    item_type *prev = item->prev;
    item_type *last = tail->prev;
    if (prev != nullptr) prev->next = head;
    head->prev = prev;
    item->prev = last;
    last->next = item;
    delete tail;
  }

  void Erase_(item_type *item) noexcept {
    item_type *prev = item->prev;
    item_type *next = item->next;
    delete item;
    if (prev != nullptr) prev->next = next;
    next->prev = prev;
  }

  item_type *GetItem_(size_type pos) noexcept {
    item_type *ret = this->head_;

    for (size_type j = 0U; j < pos; j += 1UL) ret = ret->next;

    return ret;
  }

  void InsertArg_(item_type *item, item_type *arg, size_type pos) noexcept {
    if (pos == 0UL)
      this->head_ = arg;
    else
      (item->prev)->next = arg;
    arg->prev = item->prev;
    item->prev = arg;
    arg->next = item;
    this->size_ += 1UL;
  }
};
}  // namespace s21

#endif  // S21_LIST_H
