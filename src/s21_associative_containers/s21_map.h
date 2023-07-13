#ifndef S21_MAP_H
#define S21_MAP_H

#include <stdexcept>
#include <vector>

#include "../s21_iterators/s21_map_const_iterator.h"
#include "../s21_iterators/s21_map_iterator.h"
#include "./s21_rbtree.h"

namespace s21 {

template <class K, class T>
class map : protected RBTree<K, T> {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator<K, T>;
  using const_iterator = MapConstIterator<K, T>;
  using size_type = std::size_t;
  using item_type = struct RBTNode<K, T>;

  map();
  explicit map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m) noexcept;
  ~map();
  map &operator=(map &&m) noexcept;

  T &at(const K &key);
  const T &at(const K &key) const;
  T &operator[](const K &key) noexcept;
  const T &operator[](const K &key) const noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const K &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const K &key, const T &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);
  bool contains(const K &key);
  std::vector<std::pair<iterator, bool>> insert_many();
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  void CheckSizeBounds_(const item_type *node) const;
  size_type Traversal_(item_type *item_ptr) const noexcept;
};

template <class K, class T>
map<K, T>::map() : RBTree<K, T>::RBTree() {}

template <class K, class T>
map<K, T>::map(std::initializer_list<value_type> const &items) : map() {
  for (auto item = items.begin(); item != items.end(); ++item) insert(*item);
}

template <class K, class T>
map<K, T>::map(const map &m) : map() {
  for (auto item = m.begin(), item_end = m.end(); item != item_end; ++item)
    insert(*item);
}

template <class K, class T>
map<K, T>::map(map &&m) noexcept : map() {
  *this = std::move(m);
}

template <class K, class T>
map<K, T>::~map() {}

template <class K, class T>
map<K, T> &map<K, T>::operator=(map &&m) noexcept {
  this->Destory();
  if (this != &m) {
    this->root_ = m.root_;
    m.root_ = nullptr;
  } else {
    this->root_ = nullptr;
  }

  return *this;
}

template <class K, class T>
T &map<K, T>::at(const K &key) {
  item_type *node = this->Search(key);
  CheckSizeBounds_(node);

  return node->value.second;
}
template <class K, class T>
const T &map<K, T>::at(const K &key) const {
  item_type *node = this->Search(key);
  CheckSizeBounds_(node);

  return node->value.second;
}

template <class K, class T>
T &map<K, T>::operator[](const K &key) noexcept {
  item_type *node = this->Search(key);

  return node->value.second;
}
template <class K, class T>
const T &map<K, T>::operator[](const K &key) const noexcept {
  item_type *node = this->Search(key);

  return node->value.second;
}

template <class K, class T>
typename map<K, T>::iterator map<K, T>::begin() noexcept {
  item_type *node = this->Begin();
  iterator ret(node);

  return ret;
}
template <class K, class T>
typename map<K, T>::const_iterator map<K, T>::begin() const noexcept {
  item_type *node = this->Begin();
  const_iterator ret(node);

  return ret;
}

template <class K, class T>
typename map<K, T>::iterator map<K, T>::end() noexcept {
  iterator ret(nullptr, this->root_);

  return ret;
}
template <class K, class T>
typename map<K, T>::const_iterator map<K, T>::end() const noexcept {
  const_iterator ret(nullptr, this->root_);

  return ret;
}

template <class K, class T>
bool map<K, T>::empty() const noexcept {
  bool ret = false;
  if (this->root_ == nullptr) ret = true;

  return ret;
}

template <class K, class T>
constexpr typename map<K, T>::size_type map<K, T>::size() const noexcept {
  size_type ret = Traversal_(this->root_);

  return ret;
}

template <class K, class T>
constexpr typename map<K, T>::size_type map<K, T>::max_size() const noexcept {
  std::allocator<item_type> alloc;

  return alloc.max_size();
}

template <class K, class T>
void map<K, T>::clear() {
  this->Destory();
  this->root_ = nullptr;
}

template <class K, class T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(
    const value_type &value) {
  bool inserted = this->Insert(value);
  item_type *node = this->Search(value.first);
  iterator iter(node);

  return std::pair(iter, inserted);
}

template <class K, class T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(const K &key,
                                                                const T &obj) {
  return insert(std::pair<K, T>(key, obj));
}

template <class K, class T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert_or_assign(
    const K &key, const T &obj) {
  std::pair<iterator, bool> ret;

  item_type *node = this->Search(key);
  if (node == nullptr) {
    ret = insert(key, obj);
  } else {
    node->value.second = obj;
    iterator iter(node);
    ret = std::pair<iterator, bool>(iter, false);
  }

  return ret;
}

template <class K, class T>
void map<K, T>::erase(iterator pos) {
  this->Remove((*pos).first);
}

template <class K, class T>
void map<K, T>::swap(map &other) {
  item_type *root = this->root_;
  this->root_ = other.root_;
  other.root_ = root;
}

template <class K, class T>
void map<K, T>::merge(map &other) {
  if (this != &other) {
    for (auto item = other.begin(), item_end = other.end(); item != item_end;
         ++item)
      insert(*item);
    other.clear();
  }
}

template <class K, class T>
bool map<K, T>::contains(const K &key) {
  return (this->Search(key) != nullptr);
}

template <class K, class T>
std::vector<std::pair<typename map<K, T>::iterator, bool>>
map<K, T>::insert_many() {
  std::vector<std::pair<iterator, bool>> ret;
  K key = {};
  T mapped = {};
  ret.push_back(insert(key, mapped));

  return ret;
}
template <class K, class T>
template <class... Args>
std::vector<std::pair<typename map<K, T>::iterator, bool>>
map<K, T>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> ret;

  for (item_type arg : {args...}) {
    this->insert(arg.value);
    delete arg.ptrs;
    item_type *node = this->Search(arg.value.first);
    iterator iter(node);
    ret.push_back(std::pair<iterator, bool>(iter, node != nullptr));
  }

  return ret;
}

// private methods

template <class K, class T>
void map<K, T>::CheckSizeBounds_(const item_type *node) const {
  if (node == nullptr) {
    throw std::out_of_range("Incorrect input, key is outside the map");
  }
}

template <class K, class T>
typename map<K, T>::size_type map<K, T>::Traversal_(
    item_type *item_ptr) const noexcept {
  int ret = 0;

  if (item_ptr != nullptr)
    ret = 1 + Traversal_(item_ptr->ptrs->right) +
          Traversal_(item_ptr->ptrs->left);

  return ret;
}

}  // namespace s21

#endif  // S21_MAP_H
