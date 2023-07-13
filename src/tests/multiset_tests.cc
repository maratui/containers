#include <gtest/gtest.h>

#include "../s21_set_containers/s21_multiset.h"
#include "common_tests.h"

template <class T>
void is_equal(multiset<T> &x, std::multiset<T> &x_orig) {
  ASSERT_EQ(x.size(), x_orig.size());
  auto it = x.begin();
  auto it_orig = x_orig.begin();
  for (; (it_orig != x_orig.end() && it != x.end()); ++it_orig, ++it)
    ASSERT_EQ((*it), (*it_orig));
}

TEST(s21_multiset, constructors) {
  multiset<double> x;
  std::multiset<double> x_orig;
  x.insert(10.102);
  x.insert(-0.02);
  x.insert(91);
  x.insert(47.102);
  x.insert(11.23);
  x_orig.insert(10.102);
  x_orig.insert(-0.02);
  x_orig.insert(91);
  x_orig.insert(47.102);
  x_orig.insert(11.23);
  is_equal(x, x_orig);

  multiset<int> y;
  auto it = y.insert(2);
  y.insert(2);
  y.insert(3);
  ++it;
  ++it;
  EXPECT_EQ(*it, 3);

  multiset<int> z{10, 20, 30, 10, 20, 30};
  std::multiset<int> z_orig{10, 20, 30, 10, 20, 30};
  is_equal(z, z_orig);

  multiset<int> v(z);
  std::multiset<int> v_orig(z_orig);
  is_equal(v, v_orig);

  multiset<int> w(std::move(z));
  std::multiset<int> w_orig(std::move(z_orig));
  is_equal(z, z_orig);
  is_equal(w, w_orig);
}

TEST(s21_multiset, lower_bound) {
  multiset<int> x{1, 2, 3, -2, 4};
  std::multiset<int> x_orig{1, 2, 3, -2, 4};
  for (int key = -5; key < 5; ++key) {
    auto it = x.lower_bound(key);
    auto it_orig = x_orig.lower_bound(key);
    EXPECT_EQ(*it, *it_orig);
  }

  auto it = x.lower_bound(5);
  auto it_orig = x_orig.lower_bound(5);
  EXPECT_EQ(it, x.end());
  EXPECT_EQ(it_orig, x_orig.end());
}

TEST(s21_multiset, upper_bound) {
  multiset<int> x{1, 2, 3, -2, 4};
  std::multiset<int> x_orig{1, 2, 3, -2, 4};

  for (int key = -5; key < 4; ++key) {
    auto it = x.upper_bound(key);
    auto it_orig = x_orig.upper_bound(key);
    EXPECT_EQ(*it, *it_orig);
  }

  auto it = x.upper_bound(5);
  auto it_orig = x_orig.upper_bound(5);
  EXPECT_EQ(it, x.end());
  EXPECT_EQ(it_orig, x_orig.end());
}

TEST(s21_multiset, count) {
  multiset<int> x{1, 2, 3, 3};
  std::multiset<int> x_orig{1, 2, 3, 3};

  EXPECT_EQ(x.count(3), x_orig.count(3));
}

TEST(s21_multiset, eq_range) {
  multiset<int> x{1, 2, 3, 3};
  std::multiset<int> x_orig{1, 2, 3, 3};

  for (int key = -7; key < 7; ++key) {
    auto it = x.equal_range(key);
    auto it_orig = x_orig.equal_range(key);
    if (it.first != x.end()) {
      EXPECT_EQ(*it.first, *it_orig.first);
    }
    if (it.second != x.end()) {
      EXPECT_EQ(*it.second, *it_orig.second);
    }
  }
}

TEST(s21_multiset, insert_many) {
  multiset<double> x{-0.2};
  x.insert_many(0.4);
  x.insert_many(4.123);
  x.insert_many(10.11);
  x.insert_many(4.4);
  x.insert_many(5.04);
  x.insert_many(5.04);
  std::multiset<double> x_orig{-0.2};
  x_orig.emplace(0.4);
  x_orig.emplace(4.123);
  x_orig.emplace(10.11);
  x_orig.emplace(4.4);
  x_orig.emplace(5.04);
  x_orig.emplace(5.04);
  is_equal(x, x_orig);
}

TEST(s21_multiset, iterators) {
  multiset<int> x{6, 2, 1,    0,  78, 0,  7,  -1,  90,
                  3, 8, -234, 98, 33, -0, 11, -99, 1234};
  std::multiset<int> x_orig{6, 2, 1,    0,  78, 0,  7,  -1,  90,
                            3, 8, -234, 98, 33, -0, 11, -99, 1234};
  auto it = x.begin();
  auto it_orig = x_orig.begin();
  ASSERT_EQ(*it, *it_orig);

  x.clear();
  it = x.begin();
  ASSERT_EQ(it, x.end());
  EXPECT_ANY_THROW(*it);

  x = {6, 2, 1, 0, 78, 0, 7, -1, 90, 3, 8, -234, 98, 33, -0, 11, -99, 1234};
  x_orig = {6, 2, 1,    0,  78, 0,  7,  -1,  90,
            3, 8, -234, 98, 33, -0, 11, -99, 1234};
  it = x.begin();
  it_orig = x_orig.begin();
  for (unsigned int i = 0; i < x.size(); ++i, ++it, ++it_orig)
    ASSERT_EQ(*it, *it_orig);

  x = {6, 2, 1, 0, 78, 0, 7, -1, 90, 3, 8, -234, 98, 33, -0, 11, -99, 1234};
  it = x.begin();
  for (unsigned int i = 0; i < x.size() - 1; ++i, ++it)
    ;
  ASSERT_EQ(1234, *it);
}

TEST(s21_multiset, empty) {
  multiset<int> x;
  std::multiset<int> x_orig;
  ASSERT_EQ(x.empty(), x_orig.empty());

  x = {9};
  x_orig = {9};
  ASSERT_EQ(x.empty(), x_orig.empty());
}

TEST(s21_multiset, size) {
  multiset<int> x{1, 2, 3};
  std::multiset<int> x_orig{1, 2, 3};
  ASSERT_EQ(x.size(), x_orig.size());
}

TEST(s21_multiset, max_size) {
  multiset<double> x;
  std::multiset<double> x_orig;
  EXPECT_GE(x.max_size(), 0);
  EXPECT_GE(x_orig.max_size(), 0);
}

TEST(s21_multiset, clear) {
  multiset<int> x{1, 2, 3};
  std::multiset<int> x_orig{1, 2, 3};
  x.clear();
  x_orig.clear();
  is_equal(x, x_orig);
}

TEST(s21_multiset, insert) {
  multiset<int> x;
  std::multiset<int> x_orig;
  for (int i = -10; i <= 10; i++) {
    x.insert(i);
    x_orig.insert(i);
  }
  is_equal(x, x_orig);

  x.insert(1);
  x_orig.insert(1);
  is_equal(x, x_orig);

  x.insert(11);
  x_orig.insert(11);
  is_equal(x, x_orig);
}

TEST(s21_multiset, erase) {
  multiset<int> x{6, 2, 1,    0,  78, 0,  7,  -1,  90,
                  3, 8, -234, 98, 33, -0, 11, -99, 1234};
  std::multiset<int> x_orig{6, 2, 1,    0,  78, 0,  7,  -1,  90,
                            3, 8, -234, 98, 33, -0, 11, -99, 1234};
  auto it = x.begin();
  auto it_orig = x_orig.begin();
  for (long unsigned int i = 0; i < x.size() / 2; ++i, ++it, ++it_orig)
    ;
  x.erase(it);
  x_orig.erase(it_orig);
  is_equal(x, x_orig);

  x = {9, 1, 4};
  x_orig = {9, 1, 4};
  it = x.begin();
  it_orig = x_orig.begin();
  x.erase(it);
  x_orig.erase(it_orig);
  is_equal(x, x_orig);

  x = {1234};
  x_orig = {1234};
  it_orig = x_orig.begin();
  it = x.begin();
  x.erase(it);
  x_orig.erase(it_orig);
  is_equal(x, x_orig);

  x.clear();
  it = x.begin();
  EXPECT_ANY_THROW(x.erase(it));

  x = {9, 1, 4};
  int initail_size = x.size();
  it = x.begin();
  x.erase(it);
  ASSERT_EQ(x.size(), initail_size - 1);

  x = {-2, -3, -4, -5, -6, -7};
  initail_size = x.size();
  it = x.begin();
  for (unsigned int i = 0; i < x.size() - 1; ++i, ++it)
    ;
  x.erase(it);
  ASSERT_EQ(x.size(), initail_size - 1);

  x = {6, 2, 1, 0, 78, 0, 7, -1, 90, 3, 8, -234, 98, 33, -0, 11, -99, 1234};
  x_orig = {6, 2, 1,    0,  78, 0,  7,  -1,  90,
            3, 8, -234, 98, 33, -0, 11, -99, 1234};
  it = x.begin();
  it_orig = x_orig.begin();
  x.erase(it);
  x_orig.erase(it_orig);
  is_equal(x, x_orig);

  x = {6, 2, 1, 0, 78, 0, 7, -1, 90};
  x_orig = {6, 2, 1, 0, 78, 0, 7, -1, 90};

  it = x.begin();
  it_orig = x_orig.begin();
  ++it;
  ++it_orig;
  x.erase(it);
  x_orig.erase(it_orig);
  is_equal(x, x_orig);

  x = {9, 1, 4};
  it = x.begin();
  x.clear();
  ASSERT_EQ(x.size(), 0);
  EXPECT_ANY_THROW(x.erase(it));
}

TEST(s21_multiset, swap) {
  multiset<int> x{1, 2, 3};
  multiset<int> y;
  std::multiset<int> x_orig{1, 2, 3};
  std::multiset<int> y_orig;
  y.swap(x);
  y_orig.swap(x_orig);
  is_equal(y, y_orig);
  is_equal(x, x_orig);

  x.swap(x);
  x_orig.swap(x_orig);
  is_equal(x, x_orig);
}

TEST(s21_multiset, merge) {
  multiset<int> x{1, 2, 3};
  multiset<int> y{6, 5, 4, 3};
  std::multiset<int> x_orig{1, 2, 3};
  std::multiset<int> y_orig{6, 5, 4, 3};

  y.merge(x);
  y_orig.merge(x_orig);
  is_equal(y, y_orig);
}

TEST(s21_multiset, find) {
  multiset<int> x{1, 2, 3};
  std::multiset<int> x_orig{1, 2, 3};
  auto it = x.find(2);
  auto it_orig = x_orig.find(2);
  ASSERT_EQ(*it, *it_orig);

  it = x.find(4);
  it_orig = x_orig.find(4);
  ASSERT_EQ(it, x.end());
  ASSERT_EQ(it_orig, x_orig.end());
}

TEST(s21_multiset, contains) {
  multiset<int> x;
  ASSERT_EQ(x.contains(4), false);

  x = {1, 2, 3};
  ASSERT_EQ(x.contains(4), false);

  set<double> y{-0.8563859, 1.9473646};
  ASSERT_EQ(y.contains(-0.8563855), false);
  ASSERT_EQ(y.contains(1.9473646), true);
}
