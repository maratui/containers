#ifndef S21_SET_H_
#define S21_SET_H_

#include <iostream>
#include <limits>
#include <vector>

namespace s21 {

template <class T>
class set {
 protected:
  class SetIterator;
  class SetConstIterator;

 public:
  // in-class type overrides
  using value_type = T;
  using key_type = value_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;
  using size_type = std::size_t;

  // the main public methods
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  set &operator=(set &&other) noexcept;

  // the public methods for iterating over class elements
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  // the public methods for accessing the container capacity information
  bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;

  // the public methods for modifying a container
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  // the public methods for viewing the container
  iterator find(const key_type &key) noexcept;
  const_iterator find(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 protected:
  class Item {
   public:
    Item *top;
    Item *left;
    Item *right;
    value_type value;
    Item();
    Item(value_type value, Item *head_);
  };

  class SetIterator {
   public:
    SetIterator(Item *pointer);
    SetIterator();
    value_type operator*();
    value_type *operator->();
    SetIterator &operator++();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);

   protected:
    Item *item_;
  };

  class SetConstIterator {
   public:
    SetConstIterator(Item *pointer);
    SetConstIterator();
    value_type operator*();
    value_type *operator->();
    SetConstIterator &operator++();
    bool operator==(const const_iterator &other);
    bool operator!=(const const_iterator &other);

   protected:
    const Item *item_;
  };

  Item *head_;

  Item *Del_(Item *pointer, key_type key);
  size_type Traversal_(Item *pointer) const;
  iterator Add_(value_type value, Item **pointer_to_head, Item *head);
  Item *Least_(Item *pointer) const noexcept;
  void Copy_(Item *head);
  void DeleteSet_(Item *head);
};

template <class T>
set<T>::Item::Item() : value(NULL), top(NULL), left(NULL), right(NULL) {}

template <class T>
set<T>::Item::Item(T value, Item *head_)
    : top(head_), left(NULL), right(NULL), value(value) {}

template <class T>
set<T>::SetIterator::SetIterator(Item *pointer) : item_(pointer) {}
template <class T>
set<T>::SetConstIterator::SetConstIterator(Item *pointer) : item_(pointer) {}

template <class T>
set<T>::SetIterator::SetIterator() : SetIterator(NULL) {}
template <class T>
set<T>::SetConstIterator::SetConstIterator() : SetConstIterator(NULL) {}

template <class T>
typename set<T>::value_type set<T>::SetIterator::operator*() {
  if (item_ == NULL)
    throw std::invalid_argument("Out of scope");
  else
    return item_->value;
}
template <class T>
typename set<T>::value_type set<T>::SetConstIterator::operator*() {
  if (item_ == NULL) throw std::invalid_argument("Out of scope");

  return item_->value;
}

template <class T>
typename set<T>::SetIterator &set<T>::SetIterator::operator++() {
  if (item_ != NULL) {
    if (item_->right != NULL) {
      item_ = item_->right;
      while (item_->left != NULL) item_ = item_->left;
    } else {
      while (item_->top != NULL && item_->value >= item_->top->value) {
        item_ = item_->top;
      }
      item_ = item_->top;
    }
  }
  return *this;
}
template <class T>
typename set<T>::SetConstIterator &set<T>::SetConstIterator::operator++() {
  if (item_ != NULL) {
    if (item_->right != NULL) {
      item_ = item_->right;
      while (item_->left != NULL) item_ = item_->left;
    } else {
      while (item_->top != NULL && item_->value >= item_->top->value) {
        item_ = item_->top;
      }
      item_ = item_->top;
    }
  }
  return *this;
}

template <class T>
typename set<T>::value_type *set<T>::SetIterator::operator->() {
  if (item_ == NULL)
    throw std::out_of_range("Value is NULL");
  else
    return &(item_->value);
}
template <class T>
typename set<T>::value_type *set<T>::SetConstIterator::operator->() {
  if (item_ == NULL) throw std::out_of_range("Value is NULL");

  return &(item_->value);
}

template <class T>
bool set<T>::SetIterator::operator==(const iterator &other) {
  return item_ == other.item_;
}
template <class T>
bool set<T>::SetConstIterator::operator==(const const_iterator &other) {
  return item_ == other.item_;
}

template <class T>
bool set<T>::SetIterator::operator!=(const iterator &other) {
  return item_ != other.item_;
}
template <class T>
bool set<T>::SetConstIterator::operator!=(const const_iterator &other) {
  return item_ != other.item_;
}

template <class T>
set<T>::set() : head_(NULL) {}

template <class T>
set<T>::set(std::initializer_list<value_type> const &items) : set() {
  for (auto it = items.begin(); it != items.end(); ++it) insert(*it);
}

template <class T>
set<T>::set(const set &s) : set() {
  Copy_(s.head_);
}

template <class T>
set<T>::set(set &&s) : set() {
  swap(s);
  DeleteSet_(s.head_);
}

template <class T>
set<T>::~set() {
  DeleteSet_(head_);
}

template <class T>
void set<T>::Copy_(Item *head) {
  if (head != NULL) {
    Copy_(head->left);
    Copy_(head->right);
    this->insert(head->value);
  }
}

template <class T>
void set<T>::DeleteSet_(Item *head) {
  if (head != NULL) {
    DeleteSet_(head->left);
    DeleteSet_(head->right);
    delete (head);
  }
}

template <class T>
typename set<T>::set &set<T>::operator=(set &&other) noexcept {
  this->clear();
  this->Copy_(other.head_);
  other.clear();
  return *this;
}

template <class T>
typename set<T>::iterator set<T>::begin() noexcept {
  return SetIterator(Least_(head_));
}
template <class T>
typename set<T>::const_iterator set<T>::begin() const noexcept {
  return SetConstIterator(Least_(head_));
}

template <class T>
typename set<T>::iterator set<T>::end() noexcept {
  return SetIterator();
}
template <class T>
typename set<T>::const_iterator set<T>::end() const noexcept {
  return SetConstIterator();
}

template <class T>
bool set<T>::empty() const noexcept {
  bool ret = true;
  if (head_ != NULL && head_->left == NULL && head_->right == NULL &&
      head_->top == NULL)
    ret = false;

  return ret;
}

template <class T>
constexpr typename set<T>::size_type set<T>::size() const noexcept {
  return Traversal_(this->head_);
}

template <class T>
typename set<T>::size_type set<T>::Traversal_(Item *pointer) const {
  int ret = 0;
  if (pointer != NULL)
    ret = 1 + Traversal_(pointer->right) + Traversal_(pointer->left);
  return ret;
}

template <class T>
constexpr typename set<T>::size_type set<T>::max_size() const noexcept {
  return std::numeric_limits<size_t>::max() / sizeof(Item);
}
template <class T>
void set<T>::clear() noexcept {
  DeleteSet_(head_);
  head_ = NULL;
}
template <class T>
void set<T>::erase(iterator pos) {
  if (pos == NULL || size() == 0)
    throw std::invalid_argument(
        "A being erased element at pos and an iterator are supposed not to be "
        "empty");
  else
    head_ = Del_(head_, *pos);
}

template <class T>
typename set<T>::Item *set<T>::Del_(Item *pointer, key_type key) {
  Item *tmp = NULL;
  if (pointer != NULL) {
    if (key < pointer->value)  // go left
      pointer->left = Del_(pointer->left, key);
    else if (key > pointer->value)  // go right
      pointer->right = Del_(pointer->right, key);
    else if (pointer->left != NULL and pointer->right != NULL) {  // found
      pointer->value = Least_(pointer->right)->value;
      pointer->right = Del_(pointer->right, pointer->value);
    } else if (pointer->left != NULL) {  // the lefttmost
      tmp = pointer;
      pointer = pointer->left;
      pointer->top = tmp->top;
    } else if (pointer->right != NULL) {  // // the rightmost
      tmp = pointer;
      pointer = pointer->right;
      pointer->top = tmp->top;
    } else {  // the one
      DeleteSet_(pointer);
      pointer = NULL;
    }
    delete (tmp);
  }
  return pointer;
}

template <class T>
void set<T>::swap(set &other) {
  Item *tmp = this->head_;
  this->head_ = other.head_;
  other.head_ = tmp;
}

template <class T>
void set<T>::merge(set &other) {
  for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
}

template <class T>
typename set<T>::iterator set<T>::find(const key_type &key) noexcept {
  iterator ret = NULL;
  for (auto it = this->begin(); ((it != this->end()) && (ret == NULL)); ++it)
    if (*it == key) ret = it;

  return ret;
}
template <class T>
typename set<T>::const_iterator set<T>::find(
    const key_type &key) const noexcept {
  const_iterator ret = NULL;
  for (auto it = this->begin(); ((it != this->end()) && (ret == NULL)); ++it)
    if (*it == key) ret = it;

  return ret;
}

template <class T>
bool set<T>::contains(const key_type &key) const noexcept {
  return (find(key) != NULL);
}

template <class T>
typename set<T>::Item *set<T>::Least_(Item *pointer) const noexcept {
  if (pointer != NULL)
    while (pointer->left != NULL) pointer = pointer->left;

  return pointer;
}

template <class T>
std::pair<typename set<T>::SetIterator, bool> set<T>::insert(
    const typename set<T>::value_type &value) {
  iterator result = Add_(value, &head_, NULL);

  return std::pair<set<T>::SetIterator, bool>(result, result != nullptr);
}

template <class T>
typename set<T>::iterator set<T>::Add_(value_type value, Item **pointer_to_head,
                                       Item *head) {
  iterator result = NULL;
  if (*pointer_to_head == NULL) {
    *pointer_to_head = new Item(value, head);
    result = SetIterator(*pointer_to_head);
  } else {
    if (value < (*pointer_to_head)->value)
      result = Add_(value, &(*pointer_to_head)->left, *pointer_to_head);
    else if (value > (*pointer_to_head)->value)
      result = Add_(value, &(*pointer_to_head)->right, *pointer_to_head);
    else
      return NULL;
  }
  if (result != NULL)
    return SetIterator(*pointer_to_head);
  else
    return NULL;
}

template <class T>
template <class... Args>
std::vector<std::pair<typename set<T>::SetIterator, bool>> set<T>::insert_many(
    Args &&...args) {
  set<T> list{args...};
  std::vector<std::pair<iterator, bool>> ret;
  for (auto it = list.begin(); it != list.end(); ++it)
    ret.push_back(insert(*it));

  return ret;
}

}  // namespace s21

#endif  // #ifndef S21_SET_H_
