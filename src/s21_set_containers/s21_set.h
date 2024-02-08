#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_SET_CONTAINERS_S21_SET_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_SET_CONTAINERS_S21_SET_H

#include <stdexcept>
#include <vector>

#include "../s21_associative_containers/s21_map.h"
#include "../s21_iterators/s21_set_const_iterator.h"
#include "../s21_iterators/s21_set_iterator.h"

namespace s21 {

template <class Key>
class set : protected map<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator<Key>;
  using const_iterator = SetConstIterator<Key>;
  using size_type = std::size_t;
  using item_type = struct RBTNode<Key, Key>;

  set() : map<Key, Key>() {}
  explicit set(std::initializer_list<value_type> const &items);
  set(const set &s) : map<Key, Key>(s) {}
  set(set &&s) noexcept { *this = std::move(s); }
  ~set() {}
  set &operator=(set &&s) noexcept;
  set &operator=(const set &s);

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  using map<Key, Key>::empty;
  using map<Key, Key>::size;
  using map<Key, Key>::max_size;

  using map<Key, Key>::clear;
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos) noexcept;
  void swap(set &other);
  void merge(set &other);

  iterator find(const Key &key) noexcept;
  const_iterator find(const Key &key) const noexcept;
  using map<Key, Key>::contains;

  std::vector<std::pair<iterator, bool>> insert_many();
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <class Key>
set<Key>::set(std::initializer_list<value_type> const &items) : set() {
  for (auto item = items.begin(); item != items.end(); ++item) insert(*item);
}

template <class Key>
set<Key> &set<Key>::operator=(set &&s) noexcept {
  this->Destory();
  if (this != &s) {
    this->root_ = s.root_;
    s.root_ = nullptr;
  } else {
    this->root_ = nullptr;
  }

  return *this;
}

template <class Key>
set<Key> &set<Key>::operator=(const set &s) {
  if (this != &s) {
    *this = set(s);
  }

  return *this;
}

template <class Key>
typename set<Key>::iterator set<Key>::begin() noexcept {
  item_type *node = this->Begin();
  iterator ret(node, this->root_);

  return ret;
}
template <class Key>
typename set<Key>::const_iterator set<Key>::begin() const noexcept {
  item_type *node = this->Begin();
  const_iterator ret(node, this->root_);

  return ret;
}

template <class Key>
typename set<Key>::iterator set<Key>::end() noexcept {
  iterator ret(nullptr, this->root_);

  return ret;
}
template <class Key>
typename set<Key>::const_iterator set<Key>::end() const noexcept {
  const_iterator ret(nullptr, this->root_);

  return ret;
}

template <class Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type &value) {
  bool inserted = false;
  item_type *node = this->Search(value);
  if (node == nullptr) {
    node =
        this->Insert(std::pair<const key_type, const value_type>(value, value));
    if (node != nullptr) inserted = true;
  }
  iterator iter(node);

  return std::pair(iter, inserted);
}

template <class Key>
void set<Key>::erase(iterator pos) noexcept {
  this->Remove(*pos);
}

template <class Key>
void set<Key>::swap(set &other) {
  item_type *root = this->root_;
  this->root_ = other.root_;
  other.root_ = root;
}

template <class Key>
void set<Key>::merge(set &other) {
  if (this != &other) {
    for (auto iter = other.begin(), iter_end = other.end(); iter != iter_end;
         ++iter)
      insert(*iter);
    other.clear();
  }
}

template <class Key>
typename set<Key>::iterator set<Key>::find(const Key &key) noexcept {
  item_type *node = this->Search(key);
  iterator ret(node);

  return ret;
}
template <class Key>
typename set<Key>::const_iterator set<Key>::find(
    const Key &key) const noexcept {
  item_type *node = this->Search(key);
  const_iterator ret(node);

  return ret;
}

template <class Key>
std::vector<std::pair<typename set<Key>::iterator, bool>>
set<Key>::insert_many() {
  std::vector<std::pair<iterator, bool>> ret;
  Key key = {};
  ret.push_back(insert(key));

  return ret;
}
template <class Key>
template <class... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  std::vector<std::pair<iterator, bool>> ret;

  for (item_type arg : {args...}) {
    ret.push_back(insert(arg.value.first));
    delete arg.ptrs;
  }

  return ret;
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_SET_CONTAINERS_S21_SET_H
