#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_SET_CONTAINERS_S21_MULTISET_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_SET_CONTAINERS_S21_MULTISET_H

#include "./s21_set.h"

namespace s21 {
template <class Key>
class multiset : public s21::set<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator<Key>;
  using const_iterator = SetConstIterator<Key>;
  using size_type = std::size_t;
  using item_type = struct RBTNode<Key, Key>;

  multiset() : set<Key>() {}
  explicit multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms) noexcept { *this = std::move(ms); }
  ~multiset() {}
  multiset &operator=(multiset &&ms) noexcept;
  multiset &operator=(const multiset &ms);

  iterator insert(const value_type &value);

  constexpr size_type count(const Key &key) const noexcept;
  void merge(multiset &other);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  std::vector<std::pair<iterator, bool>> insert_many();
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <class Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items)
    : multiset() {
  for (auto item = items.begin(); item != items.end(); ++item) insert(*item);
}

template <class Key>
multiset<Key>::multiset(const multiset &ms) : multiset() {
  for (auto item = ms.begin(), item_end = ms.end(); item != item_end; ++item)
    insert(*item);
}

template <class Key>
multiset<Key> &multiset<Key>::operator=(multiset &&ms) noexcept {
  this->Destory();
  if (this != &ms) {
    this->root_ = ms.root_;
    ms.root_ = nullptr;
  } else {
    this->root_ = nullptr;
  }

  return *this;
}

template <class Key>
multiset<Key> &multiset<Key>::operator=(const multiset &ms) {
  if (this != &ms) {
    *this = multiset(ms);
  }

  return *this;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type &value) {
  item_type *node =
      this->Insert(std::pair<const key_type, const value_type>(value, value));
  iterator ret(node);

  return ret;
}

template <class Key>
constexpr typename multiset<Key>::size_type multiset<Key>::count(
    const Key &key) const noexcept {
  size_type ret = 0U;

  for (auto iter = this->begin(), iter_end = this->end(); iter != iter_end;
       ++iter)
    if (*iter == key) ret += 1U;

  return ret;
}

template <class Key>
void multiset<Key>::merge(multiset &other) {
  if (this != &other) {
    for (auto iter = other.begin(), iter_end = this->end(); iter != iter_end;
         ++iter)
      insert(*iter);
    other.clear();
  }
}

template <class Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  iterator lower_bound_iter = lower_bound(key);
  // iterator upper_bound_iter = upper_bound(key);

  return std::pair(lower_bound_iter, lower_bound_iter);
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  bool cond = true;
  auto iter = this->begin();
  for (auto iter_end = this->end(); (iter != iter_end) && cond; ++iter)
    if ((*iter > key) || (*iter == key)) cond = false;
  if (!cond) --iter;

  return iter;
}
template <class Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  bool cond = true;
  auto iter = lower_bound(key);
  for (auto iter_end = this->end(); (iter != iter_end) && cond; ++iter)
    if (*iter > key) cond = false;
  if (!cond) --iter;

  return iter;
}

template <class Key>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many() {
  std::vector<std::pair<iterator, bool>> ret;
  Key key = {};
  iterator iter = insert(key);
  ret.push_back(std::pair<iterator, bool>(iter, (iter != this->end())));

  return ret;
}
template <class Key>
template <class... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> ret;

  for (item_type arg : {args...}) {
    iterator iter = insert(arg.value.first);
    delete arg.ptrs;
    ret.push_back(std::pair<iterator, bool>(iter, (iter != this->end())));
  }

  return ret;
}
}  // namespace s21

#endif  //  CPP2_S21_CONTAINERS_3_SRC_S21_SET_CONTAINERS_S21_MULTISET_H
