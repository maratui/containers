#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include "s21_set.h"

namespace s21 {
template <class T>
class multiset : public s21::set<T> {
  using value_type = T;
  using key_type = value_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename set<value_type>::SetIterator;
  using const_iterator = typename set<value_type>::SetConstIterator;

 public:
  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);

  multiset operator=(multiset &&ms);

  size_type count(const key_type &key);
  iterator insert(const value_type &value);
  void merge(multiset &other);
  std::pair<iterator, iterator> equal_range(const key_type &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 protected:
  using Item = typename set<value_type>::Item;
  void copy(Item *head);
  typename set<T>::iterator add(value_type value, Item **ptr_head, Item *root);
};

template <class T>
multiset<T>::multiset() : set<T>() {}

template <class T>
multiset<T>::multiset(std::initializer_list<value_type> const &items)
    : multiset() {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
  }
}

template <class T>
multiset<T>::multiset(const multiset &ms) : multiset() {
  this->copy(ms.head);
}

template <class T>
multiset<T>::multiset(multiset &&ms) : multiset() {
  this->swap(ms);
}

template <class T>
typename multiset<T>::multiset multiset<T>::operator=(multiset &&ms) {
  this->clear();
  this->copy(ms.head);
  ms.clear();
  return *this;
}

template <class T>
typename multiset<T>::size_type multiset<T>::count(const key_type &key) {
  size_type ret = 0;
  for (auto tmp = this->begin(); tmp != this->end(); ++tmp)
    if (*tmp == key) ++ret;
  return ret;
}

template <class T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const key_type &key) {
  std::pair<iterator, iterator> it;
  it.first = this->lower_bound(key);
  it.second = this->upper_bound(key);
  return it;
}

template <class T>
typename multiset<T>::iterator multiset<T>::lower_bound(const key_type &key) {
  for (auto tmp = this->begin(); tmp != this->end(); ++tmp)
    if (*tmp >= key) return tmp;
  return NULL;
}
template <class T>
typename multiset<T>::iterator multiset<T>::upper_bound(const key_type &key) {
  for (auto tmp = this->begin(); tmp != this->end(); ++tmp)
    if (key < *tmp) return tmp;
  return NULL;
}

template <class T>
typename multiset<T>::iterator multiset<T>::insert(const value_type &value) {
  iterator result = this->add(value, &this->head, nullptr);
  return result;
}

template <class T>
void multiset<T>::copy(Item *head) {
  if (head != NULL) {
    copy(head->left);
    copy(head->right);
    this->insert(head->value);
  }
}

template <class T>
void multiset<T>::merge(multiset &other) {
  for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
}

template <class T>
typename set<T>::iterator multiset<T>::add(value_type val, Item **ptr_head,
                                           Item *root) {
  if (*ptr_head == nullptr) {
    (*ptr_head) = new Item(val, root);
    (*ptr_head)->value = val;
    (*ptr_head)->left = (*ptr_head)->right = nullptr;
    (*ptr_head)->top = root;
    return typename set<T>::SetIterator(*ptr_head);
  } else {
    if (val < (*ptr_head)->value) {
      add(val, &(*ptr_head)->left, *ptr_head);
    } else
      add(val, &(*ptr_head)->right, *ptr_head);
  }
  return typename set<T>::SetIterator();
}

template <class T>
template <class... Args>
std::vector<std::pair<typename set<T>::SetIterator, bool>>
multiset<T>::insert_many(Args &&...args) {
  set<T> list{args...};
  std::vector<std::pair<iterator, bool>> ret;
  for (auto it = list.begin(); it != list.end(); ++it) {
    auto iter = this->insert(*it);
    ret.push_back(std::make_pair(iter, iter != NULL));
  }
  return ret;
}

}  // namespace s21

#endif  //  S21_MAP_H_
