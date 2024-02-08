#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_ASSOCIATIVE_CONTAINERS_S21_RBTREE_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_ASSOCIATIVE_CONTAINERS_S21_RBTREE_H

#include <utility>

namespace s21 {

enum RBTColor { Black, Red };

template <class K, class T>
struct RBTNode {
  struct RBTPtrs {
    RBTNode<K, T> *parent;
    RBTNode<K, T> *left;
    RBTNode<K, T> *right;
    RBTPtrs(RBTNode<K, T> *p, RBTNode<K, T> *l, RBTNode<K, T> *r)
        : parent(p), left(l), right(r){};
  };
  using value_type = std::pair<const K, T>;
  value_type value;
  RBTColor color;
  RBTPtrs *ptrs;
  RBTNode(value_type v, RBTColor c, RBTPtrs *p) : value(v), color(c), ptrs(p){};
  RBTNode<K, T> *Next() noexcept;
  const RBTNode<K, T> *Next() const noexcept;
  RBTNode<K, T> *Prev() noexcept;
  const RBTNode<K, T> *Prev() const noexcept;
};

#define RBTNODE_NEXT                                               \
  if (node != nullptr) {                                           \
    if (node->ptrs->right != nullptr) {                            \
      node = node->ptrs->right;                                    \
      while (node->ptrs->left != nullptr) node = node->ptrs->left; \
    } else if ((node->ptrs->parent != nullptr) &&                  \
               (node->ptrs->parent->ptrs->left == node)) {         \
      node = node->ptrs->parent;                                   \
    } else {                                                       \
      while ((node->ptrs->parent != nullptr) &&                    \
             (node->ptrs->parent->ptrs->parent != nullptr) &&      \
             (node->ptrs->parent->ptrs->parent->ptrs->left !=      \
              node->ptrs->parent)) {                               \
        node = node->ptrs->parent;                                 \
      }                                                            \
      node = node->ptrs->parent;                                   \
      if (node != nullptr) {                                       \
        node = node->ptrs->parent;                                 \
      }                                                            \
    }                                                              \
  }

template <class K, class T>
const RBTNode<K, T> *RBTNode<K, T>::Next() const noexcept {
  const RBTNode<K, T> *node = this;

  RBTNODE_NEXT

  return node;
}
template <class K, class T>
RBTNode<K, T> *RBTNode<K, T>::Next() noexcept {
  RBTNode<K, T> *node = this;

  RBTNODE_NEXT

  return node;
}

#define RBTNODE_PREV                                                 \
  if (node != nullptr) {                                             \
    if (node->ptrs->left != nullptr) {                               \
      node = node->ptrs->left;                                       \
      while (node->ptrs->right != nullptr) node = node->ptrs->right; \
    } else if ((node->ptrs->parent != nullptr) &&                    \
               (node->ptrs->parent->ptrs->right == node)) {          \
      node = node->ptrs->parent;                                     \
    } else {                                                         \
      while ((node->ptrs->parent != nullptr) &&                      \
             (node->ptrs->parent->ptrs->parent != nullptr) &&        \
             (node->ptrs->parent->ptrs->parent->ptrs->right !=       \
              node->ptrs->parent)) {                                 \
        node = node->ptrs->parent;                                   \
      }                                                              \
      node = node->ptrs->parent;                                     \
      if (node != nullptr) {                                         \
        node = node->ptrs->parent;                                   \
      }                                                              \
    }                                                                \
  }

template <class K, class T>
const RBTNode<K, T> *RBTNode<K, T>::Prev() const noexcept {
  const RBTNode<K, T> *node = this;

  RBTNODE_PREV

  return node;
}
template <class K, class T>
RBTNode<K, T> *RBTNode<K, T>::Prev() noexcept {
  RBTNode<K, T> *node = this;

  RBTNODE_PREV

  return node;
}

template <class K, class T>
class RBTree {
 public:
  using value_type = std::pair<const K, T>;

  RBTree();
  ~RBTree();

  RBTNode<K, T> *Insert(value_type value);
  RBTNode<K, T> *Search(const K key) const noexcept;
  void Remove(K key) noexcept;
  void Destory() noexcept;

  RBTNode<K, T> *Begin() const noexcept;

 protected:
  bool Insert_(RBTNode<K, T> *node);

  RBTNode<K, T> *root_;

 private:
  void Destory(RBTNode<K, T> *node) noexcept;

  void BalanceInsert(RBTNode<K, T> *node);
  void Rotate(RBTNode<K, T> *&parent, RBTNode<K, T> *&node,
              RBTNode<K, T> *gparent);
  void LeftRotate(RBTNode<K, T> *node);
  void RightRotate(RBTNode<K, T> *node);

  RBTNode<K, T> *Rotate(RBTNode<K, T> *node, const K key) const noexcept;

  void Remove(RBTNode<K, T> *node) noexcept;
  void BalanceRemove(RBTNode<K, T> *node, RBTNode<K, T> *parent) noexcept;
};

template <class K, class T>
RBTree<K, T>::RBTree() : root_(nullptr) {}

template <class K, class T>
RBTree<K, T>::~RBTree() {
  Destory(root_);
}

template <class K, class T>
RBTNode<K, T> *RBTree<K, T>::Insert(value_type value) {
  struct RBTNode<K, T>::RBTPtrs *ptrs =
      new struct RBTNode<K, T>::RBTPtrs(nullptr, nullptr, nullptr);
  RBTNode<K, T> *node = new RBTNode<K, T>(value, Red, ptrs);
  if (!Insert_(node)) {
    node = nullptr;
  }

  return node;
}

template <class K, class T>
RBTNode<K, T> *RBTree<K, T>::Search(const K key) const noexcept {
  return Rotate(root_, key);
}

template <class K, class T>
void RBTree<K, T>::Remove(K key) noexcept {
  RBTNode<K, T> *node = Rotate(root_, key);
  if (node != nullptr) Remove(node);
}

template <class K, class T>
void RBTree<K, T>::Destory() noexcept {
  Destory(root_);
}

template <class K, class T>
RBTNode<K, T> *RBTree<K, T>::Begin() const noexcept {
  RBTNode<K, T> *node = root_;

  while ((node != nullptr) && (node->ptrs->left != nullptr))
    node = node->ptrs->left;

  return node;
}

// private methods

template <class K, class T>
void RBTree<K, T>::Destory(RBTNode<K, T> *node) noexcept {
  if (node != nullptr) {
    Destory(node->ptrs->left);
    Destory(node->ptrs->right);
    delete node->ptrs;
    delete node;
  }
}

template <class K, class T>
bool RBTree<K, T>::Insert_(RBTNode<K, T> *node) {
  RBTNode<K, T> *head = root_;
  RBTNode<K, T> *parent = nullptr;
  bool ret = true;

  while (head != nullptr && ret) {
    parent = head;
    if (node->value.first > head->value.first)
      head = head->ptrs->right;
    else if ((node->value.first < head->value.first) ||
             (node->value.first == head->value.first))
      head = head->ptrs->left;
    else {
      delete node->ptrs;
      delete node;
      ret = false;
    }
  }

  if (ret) {
    node->ptrs->parent = parent;
    if (parent != nullptr) {
      if (node->value.first > parent->value.first)
        parent->ptrs->right = node;
      else
        parent->ptrs->left = node;
    } else
      root_ = node;

    node->color = Red;
    BalanceInsert(node);
  }

  return ret;
}

template <class K, class T>
void RBTree<K, T>::BalanceInsert(RBTNode<K, T> *node) {
  RBTNode<K, T> *parent = node->ptrs->parent;
  RBTNode<K, T> *gparent = nullptr;
  RBTNode<K, T> *uncle = nullptr;
  int brk = 0;

  while (node != root_ && parent->color == Red && brk == 0) {
    gparent = parent->ptrs->parent;
    if (gparent->ptrs->left == parent)
      uncle = gparent->ptrs->right;
    else
      uncle = gparent->ptrs->left;

    if (uncle != nullptr && uncle->color == Red) {
      parent->color = Black;
      uncle->color = Black;
      gparent->color = Red;
      node = gparent;
      parent = node->ptrs->parent;
    } else {
      Rotate(parent, node, gparent);
      gparent->color = Red;
      parent->color = Black;
      brk = 1;
    }
  }
  root_->color = Black;
}

template <class K, class T>
void RBTree<K, T>::Rotate(RBTNode<K, T> *&parent, RBTNode<K, T> *&node,
                          RBTNode<K, T> *gparent) {
  if (gparent->ptrs->left == parent) {
    if (parent->ptrs->right == node) {
      LeftRotate(parent);
      std::swap(parent, node);
    }
    RightRotate(gparent);
  } else {
    if (parent->ptrs->left == node) {
      RightRotate(parent);
      std::swap(parent, node);
    }
    LeftRotate(gparent);
  }
}

template <class K, class T>
void RBTree<K, T>::LeftRotate(RBTNode<K, T> *node) {
  RBTNode<K, T> *right = node->ptrs->right;

  node->ptrs->right = right->ptrs->left;
  if (right->ptrs->left != nullptr) right->ptrs->left->ptrs->parent = node;

  right->ptrs->parent = node->ptrs->parent;
  if (node->ptrs->parent == nullptr)
    root_ = right;
  else {
    if (node == node->ptrs->parent->ptrs->left)
      node->ptrs->parent->ptrs->left = right;
    else
      node->ptrs->parent->ptrs->right = right;
  }

  right->ptrs->left = node;
  node->ptrs->parent = right;
}

template <class K, class T>
void RBTree<K, T>::RightRotate(RBTNode<K, T> *node) {
  RBTNode<K, T> *left = node->ptrs->left;

  node->ptrs->left = left->ptrs->right;
  if (left->ptrs->right != nullptr) left->ptrs->right->ptrs->parent = node;

  left->ptrs->parent = node->ptrs->parent;
  if (node->ptrs->parent == nullptr)
    root_ = left;
  else {
    if (node == node->ptrs->parent->ptrs->right)
      node->ptrs->parent->ptrs->right = left;
    else
      node->ptrs->parent->ptrs->left = left;
  }

  left->ptrs->right = node;
  node->ptrs->parent = left;
}

template <class K, class T>
RBTNode<K, T> *RBTree<K, T>::Rotate(RBTNode<K, T> *node,
                                    const K key) const noexcept {
  RBTNode<K, T> *ret;

  if (node == nullptr || node->value.first == key)
    ret = node;
  else if (key > node->value.first)
    ret = Rotate(node->ptrs->right, key);
  else
    ret = Rotate(node->ptrs->left, key);

  return ret;
}

template <class K, class T>
void RBTree<K, T>::Remove(RBTNode<K, T> *node) noexcept {
  RBTNode<K, T> *parent = nullptr;
  RBTNode<K, T> *child = nullptr;
  RBTColor color = Red;

  if (node->ptrs->left != nullptr && node->ptrs->right != nullptr) {
    RBTNode<K, T> *replace = node->ptrs->right;
    while (replace->ptrs->left != nullptr) replace = replace->ptrs->left;
    if (node->ptrs->parent != nullptr) {
      if (node->ptrs->parent->ptrs->left == node)
        node->ptrs->parent->ptrs->left = replace;
      else
        node->ptrs->parent->ptrs->right = replace;
    } else {
      root_ = replace;
    }
    parent = replace->ptrs->parent;
    child = replace->ptrs->right;
    color = replace->color;
    if (parent == node) {
      parent = replace;
    } else {
      if (child != nullptr) child->ptrs->parent = parent;
      parent->ptrs->left = child;
      replace->ptrs->right = node->ptrs->right;
      node->ptrs->right->ptrs->parent = replace;
    }
    replace->ptrs->parent = node->ptrs->parent;
    replace->color = node->color;
    replace->ptrs->left = node->ptrs->left;
    node->ptrs->left->ptrs->parent = replace;
  } else {
    if (node->ptrs->left != nullptr)
      child = node->ptrs->left;
    else
      child = node->ptrs->right;
    parent = node->ptrs->parent;
    color = node->color;
    if (child != nullptr) child->ptrs->parent = parent;
    if (parent != nullptr) {
      if (node == parent->ptrs->left)
        parent->ptrs->left = child;
      else
        parent->ptrs->right = child;
    } else {
      root_ = child;
    }
  }
  if ((child != nullptr || parent != nullptr) && (color == Black))
    BalanceRemove(child, parent);
  delete node->ptrs;
  delete node;
}

template <class K, class T>
void RBTree<K, T>::BalanceRemove(RBTNode<K, T> *node,
                                 RBTNode<K, T> *parent) noexcept {
  RBTNode<K, T> *othernode;
  int brk = 0;
  int left = 0;

  while ((node == nullptr || (node != root_ && node->color == Black)) &&
         brk == 0) {
    if (parent->ptrs->left == node) left = 1;
    if (left)
      othernode = parent->ptrs->right;
    else
      othernode = parent->ptrs->left;
    if (othernode->color == Red) {
      othernode->color = Black;
      parent->color = Red;
      if (left) {
        LeftRotate(parent);
        othernode = parent->ptrs->right;
      } else {
        RightRotate(parent);
        othernode = parent->ptrs->left;
      }
    }
    if ((othernode->ptrs->left == nullptr ||
         othernode->ptrs->left->color == Black) &&
        (othernode->ptrs->right == nullptr ||
         othernode->ptrs->right->color == Black)) {
      othernode->color = Red;
      node = parent;
      parent = node->ptrs->parent;
    } else {
      if (left) {
        if (othernode->ptrs->right == nullptr ||
            othernode->ptrs->right->color == Black) {
          othernode->ptrs->left->color = Black;
          othernode->color = Red;
          RightRotate(othernode);
          othernode = parent->ptrs->right;
        }
      } else {
        if (othernode->ptrs->left == nullptr ||
            othernode->ptrs->left->color == Black) {
          othernode->ptrs->right->color = Black;
          othernode->color = Red;
          LeftRotate(othernode);
          othernode = parent->ptrs->left;
        }
      }
      othernode->color = parent->color;
      parent->color = Black;
      if (left) {
        othernode->ptrs->right->color = Black;
        LeftRotate(parent);
      } else {
        othernode->ptrs->left->color = Black;
        RightRotate(parent);
      }
      node = root_;
      brk = 1;
    }
    left = 0;
  }
  if (node != nullptr) node->color = Black;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_3_SRC_S21_ASSOCIATIVE_CONTAINERS_S21_RBTREE_H
