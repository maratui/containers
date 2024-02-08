#ifndef CPP2_S21_CONTAINERS_3_SRC_TESTS_TESTS_H
#define CPP2_S21_CONTAINERS_3_SRC_TESTS_TESTS_H

#include <gtest/gtest.h>

#include <array>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <type_traits>
#include <vector>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

struct A {
  std::string s;
  A() {}
  A(std::string str) : s(std::move(str)) {}
  A(const A &o) : s(o.s) {}
  A(A &&o) : s(std::move(o.s)) {}
  A &operator=(const A &other) {
    s = other.s;

    return *this;
  }
  A &operator=(A &&other) noexcept {
    s = std::move(other.s);

    return *this;
  }
  bool operator==(const A &o) const noexcept { return this->s == o.s; }
  bool operator!=(const A &o) const noexcept { return !(*this == o); }
  bool operator>(const A &o) const noexcept { return this->s.compare(o.s) > 0; }
  bool operator<(const A &o) const noexcept { return this->s.compare(o.s) < 0; }
};

//---------------------------------------------------------------------------

template <class T>
::testing::AssertionResult ExpectEqualVectors(
    const std::vector<T> *std_vector, const s21::vector<T> *s21_vector) {
  bool expect = true;

  EXPECT_EQ(std_vector->size(), s21_vector->size());
  EXPECT_EQ(std_vector->capacity(), s21_vector->capacity());

  auto s21_iter = s21_vector->begin();
  for (auto std_iter = std_vector->begin(), end = std_vector->end();
       std_iter != end; ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  auto std_iter = std_vector->begin();
  for (auto s21_iter = s21_vector->begin(), end = s21_vector->end();
       s21_iter != end; ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  return ((std_vector->size() == s21_vector->size()) &&
          (std_vector->capacity() == s21_vector->capacity()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class T>
::testing::AssertionResult ExpectEqualVectorBeginEnd(
    const std::vector<T> *std_vector, const s21::vector<T> *s21_vector) {
  EXPECT_EQ(std_vector->size(), s21_vector->size());
  EXPECT_EQ(std_vector->capacity(), s21_vector->capacity());
  EXPECT_TRUE(std_vector->begin() == std_vector->end());
  EXPECT_TRUE(s21_vector->begin() == s21_vector->end());

  return ((std_vector->size() == s21_vector->size()) &&
          (std_vector->capacity() == s21_vector->capacity()) &&
          (std_vector->begin() == std_vector->end()) &&
          (s21_vector->begin() == s21_vector->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class T>
::testing::AssertionResult ExpectNotEqualVectorBeginEnd(
    const std::vector<T> *std_vector, const s21::vector<T> *s21_vector) {
  EXPECT_EQ(std_vector->size(), s21_vector->size());
  EXPECT_EQ(std_vector->capacity(), s21_vector->capacity());
  EXPECT_TRUE(std_vector->begin() != std_vector->end());
  EXPECT_TRUE(s21_vector->begin() != s21_vector->end());

  return ((std_vector->size() == s21_vector->size()) &&
          (std_vector->capacity() == s21_vector->capacity()) &&
          (std_vector->begin() != std_vector->end()) &&
          (s21_vector->begin() != s21_vector->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class T>
::testing::AssertionResult ExpectEqualLists(const std::list<T> *std_list,
                                            const s21::list<T> *s21_list) {
  bool expect;

  EXPECT_EQ(std_list->size(), s21_list->size());

  expect = true;
  auto s21_iter = s21_list->begin();
  for (auto std_iter = std_list->begin(), end = std_list->end();
       std_iter != end; ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  auto std_iter = std_list->begin();
  for (auto s21_iter = s21_list->begin(), end = s21_list->end();
       s21_iter != end; ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  return ((std_list->size() == s21_list->size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class T>
::testing::AssertionResult ExpectEqualListBeginEnd(
    const std::list<T> *std_list, const s21::list<T> *s21_list) {
  EXPECT_EQ(std_list->size(), s21_list->size());
  EXPECT_TRUE(std_list->begin() == std_list->end());
  EXPECT_TRUE(s21_list->begin() == s21_list->end());

  return ((std_list->size() == s21_list->size()) &&
          (std_list->begin() == std_list->end()) &&
          (s21_list->begin() == s21_list->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class T>
::testing::AssertionResult ExpectNotEqualListBeginEnd(
    const std::list<T> *std_list, const s21::list<T> *s21_list) {
  EXPECT_EQ(std_list->size(), s21_list->size());
  EXPECT_TRUE(std_list->begin() != std_list->end());
  EXPECT_TRUE(s21_list->begin() != s21_list->end());

  return ((std_list->size() == s21_list->size()) &&
          (std_list->begin() != std_list->end()) &&
          (s21_list->begin() != s21_list->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class T, std::size_t N>
::testing::AssertionResult ExpectEqualArrays(
    const std::array<T, N> *std_array, const s21::array<T, N> *s21_array) {
  bool expect = true;

  EXPECT_EQ(std_array->size(), s21_array->size());

  auto s21_iter = s21_array->begin();
  for (auto std_iter = std_array->begin(), end = std_array->end();
       std_iter != end; ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  auto std_iter = std_array->begin();
  for (auto s21_iter = s21_array->begin(), end = s21_array->end();
       s21_iter != end; ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  return ((std_array->size() == s21_array->size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class T, std::size_t N>
::testing::AssertionResult ExpectEqualArrayBeginEnd(
    const std::array<T, N> *std_array, const s21::array<T, N> *s21_array) {
  EXPECT_EQ(std_array->size(), s21_array->size());
  EXPECT_TRUE(std_array->begin() == std_array->end());
  EXPECT_TRUE(s21_array->begin() == s21_array->end());

  return ((std_array->size() == s21_array->size()) &&
          (std_array->begin() == std_array->end()) &&
          (s21_array->begin() == s21_array->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class T, std::size_t N>
::testing::AssertionResult ExpectNotEqualArrayBeginEnd(
    const std::array<T, N> *std_array, const s21::array<T, N> *s21_array) {
  EXPECT_EQ(std_array->size(), s21_array->size());
  EXPECT_TRUE(std_array->begin() != std_array->end());
  EXPECT_TRUE(s21_array->begin() != s21_array->end());

  return ((std_array->size() == s21_array->size()) &&
          (std_array->begin() != std_array->end()) &&
          (s21_array->begin() != s21_array->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class T>
::testing::AssertionResult ExpectEqualQueues(
    const std::queue<T, std::list<T>> &std_queue,
    const s21::queue<T, s21::list<T>> &s21_queue) {
  bool expect;

  EXPECT_EQ(std_queue.size(), s21_queue.size());

  std::queue<T, std::list<T>> std(std_queue);
  s21::queue<T, s21::list<T>> s21(s21_queue);

  expect = true;
  for (size_t i = 0U; i < std_queue.size(); ++i, std.pop(), s21.pop()) {
    EXPECT_EQ(std.front(), s21.front());
    if (std.front() != s21.front()) expect = false;
  }

  return ((std_queue.size() == s21_queue.size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class T>
::testing::AssertionResult ExpectEqualQueues(const std::queue<T> &std_queue,
                                             const s21::queue<T> &s21_queue) {
  bool expect;

  EXPECT_EQ(std_queue.size(), s21_queue.size());

  std::queue<T> std(std_queue);
  s21::queue<T> s21(s21_queue);

  expect = true;

  for (size_t i = 0U; i < std_queue.size(); ++i, std.pop(), s21.pop()) {
    EXPECT_EQ(std.front(), s21.front());
    if (std.front() != s21.front()) expect = false;
  }

  return ((std_queue.size() == s21_queue.size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class T>
::testing::AssertionResult ExpectEqualStacks(const std::stack<T> &std_stack,
                                             const s21::stack<T> &s21_stack) {
  bool expect;

  EXPECT_EQ(std_stack.size(), s21_stack.size());

  std::stack<T> std(std_stack);
  s21::stack<T> s21(s21_stack);

  expect = true;
  for (size_t i = 0U; i < std_stack.size(); ++i) {
    EXPECT_EQ(std.top(), s21.top());
    if (std.top() != s21.top()) expect = false;
    if (i < std_stack.size() - 1) {
      std.pop();
      s21.pop();
    }
  }

  return ((std_stack.size() == s21_stack.size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class T>
::testing::AssertionResult ExpectEqualStacks(
    const std::stack<T, std::list<T>> &std_stack,
    const s21::stack<T, s21::list<T>> &s21_stack) {
  bool expect;

  EXPECT_EQ(std_stack.size(), s21_stack.size());

  std::stack<T, std::list<T>> std(std_stack);
  s21::stack<T, s21::list<T>> s21(s21_stack);

  expect = true;
  for (std::size_t i = 0U; i < std_stack.size(); ++i, std.pop(), s21.pop()) {
    EXPECT_EQ(std.top(), s21.top());
    if (std.top() != s21.top()) expect = false;
  }

  return ((std_stack.size() == s21_stack.size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class K, class T>
::testing::AssertionResult ExpectEqualMaps(const std::map<K, T> *std_map,
                                           const s21::map<K, T> *s21_map) {
  bool expect = true;

  EXPECT_EQ(std_map->size(), s21_map->size());

  auto s21_iter = s21_map->begin();
  for (auto std_iter = std_map->begin(), end = std_map->end(); std_iter != end;
       ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  auto std_iter = std_map->begin();
  for (auto s21_iter = s21_map->begin(), end = s21_map->end(); s21_iter != end;
       ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  return ((std_map->size() == s21_map->size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class K, class T>
::testing::AssertionResult ExpectEqualMapBeginEnd(
    const std::map<K, T> *std_map, const s21::map<K, T> *s21_map) {
  EXPECT_EQ(std_map->size(), s21_map->size());
  EXPECT_TRUE(std_map->begin() == std_map->end());
  EXPECT_TRUE(s21_map->begin() == s21_map->end());

  return ((std_map->size() == s21_map->size()) &&
          (std_map->begin() == std_map->end()) &&
          (s21_map->begin() == s21_map->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class K, class T>
::testing::AssertionResult ExpectNotEqualMapBeginEnd(
    const std::map<K, T> *std_map, const s21::map<K, T> *s21_map) {
  EXPECT_EQ(std_map->size(), s21_map->size());
  EXPECT_TRUE(std_map->begin() != std_map->end());
  EXPECT_TRUE(s21_map->begin() != s21_map->end());

  return ((std_map->size() == s21_map->size()) &&
          (std_map->begin() != std_map->end()) &&
          (s21_map->begin() != s21_map->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class Key>
::testing::AssertionResult ExpectEqualSets(const std::set<Key> *std_set,
                                           const s21::set<Key> *s21_set) {
  bool expect = true;

  EXPECT_EQ(std_set->size(), s21_set->size());

  auto s21_iter = s21_set->begin();
  for (auto std_iter = std_set->begin(), end = std_set->end(); std_iter != end;
       ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  auto std_iter = std_set->begin();
  for (auto s21_iter = s21_set->begin(), end = s21_set->end(); s21_iter != end;
       ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  return ((std_set->size() == s21_set->size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class Key>
::testing::AssertionResult ExpectEqualSetBeginEnd(
    const std::set<Key> *std_set, const s21::set<Key> *s21_set) {
  EXPECT_EQ(std_set->size(), s21_set->size());
  EXPECT_TRUE(std_set->begin() == std_set->end());
  EXPECT_TRUE(s21_set->begin() == s21_set->end());

  return ((std_set->size() == s21_set->size()) &&
          (std_set->begin() == std_set->end()) &&
          (s21_set->begin() == s21_set->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class Key>
::testing::AssertionResult ExpectNotEqualSetBeginEnd(
    const std::set<Key> *std_set, const s21::set<Key> *s21_set) {
  EXPECT_EQ(std_set->size(), s21_set->size());
  EXPECT_TRUE(std_set->begin() != std_set->end());
  EXPECT_TRUE(s21_set->begin() != s21_set->end());

  return ((std_set->size() == s21_set->size()) &&
          (std_set->begin() != std_set->end()) &&
          (s21_set->begin() != s21_set->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

template <class Key>
::testing::AssertionResult ExpectEqualMultisets(
    const std::multiset<Key> *std_multiset,
    const s21::multiset<Key> *s21_multiset) {
  bool expect = true;

  EXPECT_EQ(std_multiset->size(), s21_multiset->size());

  auto s21_iter = s21_multiset->begin();
  for (auto std_iter = std_multiset->begin(), end = std_multiset->end();
       std_iter != end; ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  auto std_iter = std_multiset->begin();
  for (auto s21_iter = s21_multiset->begin(), end = s21_multiset->end();
       s21_iter != end; ++std_iter, ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    if (*std_iter != *s21_iter) expect = false;
  }

  return ((std_multiset->size() == s21_multiset->size()) && expect)
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class Key>
::testing::AssertionResult ExpectEqualMultisetBeginEnd(
    const std::multiset<Key> *std_multiset,
    const s21::multiset<Key> *s21_multiset) {
  EXPECT_EQ(std_multiset->size(), s21_multiset->size());
  EXPECT_TRUE(std_multiset->begin() == std_multiset->end());
  EXPECT_TRUE(s21_multiset->begin() == s21_multiset->end());

  return ((std_multiset->size() == s21_multiset->size()) &&
          (std_multiset->begin() == std_multiset->end()) &&
          (s21_multiset->begin() == s21_multiset->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

template <class Key>
::testing::AssertionResult ExpectNotEqualMultisetBeginEnd(
    const std::multiset<Key> *std_multiset,
    const s21::multiset<Key> *s21_multiset) {
  EXPECT_EQ(std_multiset->size(), s21_multiset->size());
  EXPECT_TRUE(std_multiset->begin() != std_multiset->end());
  EXPECT_TRUE(s21_multiset->begin() != s21_multiset->end());

  return ((std_multiset->size() == s21_multiset->size()) &&
          (std_multiset->begin() != std_multiset->end()) &&
          (s21_multiset->begin() != s21_multiset->end()))
             ? ::testing::AssertionSuccess()
             : ::testing::AssertionFailure();
}

//---------------------------------------------------------------------------

#endif  // CPP2_S21_CONTAINERS_3_SRC_TESTS_TESTS_H
