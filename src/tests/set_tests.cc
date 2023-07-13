#include <gtest/gtest.h>

#include "common_tests.h"

TEST(s21_set, constructors) {
  set<int> v;
  std::set<int> v_orig;
  is_equal(v, v_orig);

  v = {1, 3, 2};
  v_orig = {1, 3, 2};
  is_equal(v, v_orig);

  v = {6, 2, 1, 0, 78, 0, 7, -1, 90, 3, 8, -234, 98, 33, -0, 11, -99, 1234};
  v_orig = {6, 2, 1,    0,  78, 0,  7,  -1,  90,
            3, 8, -234, 98, 33, -0, 11, -99, 1234};
  set<int> w = v;
  std::set<int> w_orig = v_orig;
  is_equal(w, w_orig);
  v.clear();
  v_orig.clear();

  set<double> x{-2.3, 4, 6.987654, 0, -0.000001};
  std::set<double> x_orig{-2.3, 4, 6.987654, 0, -0.000001};
  is_equal(x, x_orig);

  x = {1.234567,  2.34567,   -0,          -4.567890,   -0.987654,
       901.1,     88382221,  0.0000002,   8881234.009, -100000.01,
       123456789, -98765432, -0.000000001};
  x_orig = {1.234567,  2.34567,   -0,          -4.567890,   -0.987654,
            901.1,     88382221,  0.0000002,   8881234.009, -100000.01,
            123456789, -98765432, -0.000000001};
  set<double> y(x);
  std::set<double> y_orig(x_orig);
  is_equal(y, y_orig);

  set<double> z(std::move(x));
  std::set<double> z_orig(std::move(x_orig));
  is_equal(z, z_orig);
  is_equal(x, x_orig);

  x = {11, 2.3, 6.1, 0.1, 3, 1.09, 4.2, 0.1, 7.7, -0.1, -10};
  x_orig = {11, 2.3, 6.1, 0.1, 3, 1.09, 4.2, 0.1, 7.7, -0.1, -10};
  is_equal(x, x_orig);
}

TEST(s21_set, iterators) {
  set<int> x{6, 2, 1,    0,  78, 0,  7,  -1,  90,
             3, 8, -234, 98, 33, -0, 11, -99, 1234};
  std::set<int> x_orig{6, 2, 1,    0,  78, 0,  7,  -1,  90,
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

TEST(s21_set, empty) {
  set<int> x;
  std::set<int> x_orig;
  ASSERT_EQ(x.empty(), x_orig.empty());

  x = {9};
  x_orig = {9};
  ASSERT_EQ(x.empty(), x_orig.empty());
}

TEST(s21_set, size) {
  set<int> x{1, 2, 3};
  std::set<int> x_orig{1, 2, 3};
  ASSERT_EQ(x.size(), x_orig.size());
}

TEST(s21_set, max_size) {
  set<double> x;
  std::set<double> x_orig;
  EXPECT_GE(x.max_size(), 0);
  EXPECT_GE(x_orig.max_size(), 0);
}

TEST(s21_set, clear) {
  set<int> x{1, 2, 3};
  std::set<int> x_orig{1, 2, 3};
  x.clear();
  x_orig.clear();
  is_equal(x, x_orig);
}

TEST(s21_set, insert) {
  set<int> x;
  std::set<int> x_orig;
  for (int i = -10; i <= 10; i++) {
    x.insert(i);
    x_orig.insert(i);
  }
  is_equal(x, x_orig);

  auto ret_x = x.insert(1);
  auto ret_x_orig = x_orig.insert(1);
  ASSERT_EQ(ret_x.second, ret_x_orig.second);

  ret_x = x.insert(11);
  ret_x_orig = x_orig.insert(11);
  ASSERT_EQ(ret_x.second, ret_x_orig.second);
}

TEST(s21_set, erase) {
  set<int> x{6, 2, 1,    0,  78, 0,  7,  -1,  90,
             3, 8, -234, 98, 33, -0, 11, -99, 1234};
  std::set<int> x_orig{6, 2, 1,    0,  78, 0,  7,  -1,  90,
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

TEST(s21_set, swap) {
  set<int> x{1, 2, 3};
  set<int> y;
  std::set<int> x_orig{1, 2, 3};
  std::set<int> y_orig;
  y.swap(x);
  y_orig.swap(x_orig);
  is_equal(y, y_orig);
  is_equal(x, x_orig);

  x.swap(x);
  x_orig.swap(x_orig);
  is_equal(x, x_orig);
}

TEST(s21_set, merge) {
  set<int> x{1, 2, 3};
  set<int> y{6, 5, 4, 3};
  std::set<int> x_orig{1, 2, 3};
  std::set<int> y_orig{6, 5, 4, 3};

  y.merge(x);
  y_orig.merge(x_orig);
  is_equal(y, y_orig);
}

TEST(s21_set, find) {
  set<int> x{1, 2, 3};
  std::set<int> x_orig{1, 2, 3};
  auto it = x.find(2);
  auto it_orig = x_orig.find(2);
  ASSERT_EQ(*it, *it_orig);

  it = x.find(4);
  it_orig = x_orig.find(4);
  ASSERT_EQ(it, x.end());
  ASSERT_EQ(it_orig, x_orig.end());
}

TEST(s21_set, contains) {
  set<int> x;
  ASSERT_EQ(x.contains(4), false);

  x = {1, 2, 3};
  ASSERT_EQ(x.contains(4), false);

  set<double> y{-0.8563859, 1.9473646};
  ASSERT_EQ(y.contains(-0.8563855), false);
  ASSERT_EQ(y.contains(1.9473646), true);
}

TEST(s21_set, insert_many) {
  set<double> x{-0.14};
  auto ret_x = x.insert_many(-0.15);
  auto ret_x_it = ret_x.begin();
  std::set<double> x_orig{-0.14};
  auto ret_orig_x = x_orig.emplace(-0.15);
  ASSERT_EQ((*ret_x_it).second, ret_orig_x.second);

  ret_x = x.insert_many(-0.15);
  ret_x_it = ret_x.begin();
  ret_orig_x = x_orig.emplace(-0.15);
  ASSERT_EQ((*ret_x_it).second, ret_orig_x.second);
  is_equal(x, x_orig);

  ret_x = x.insert_many(1.1);
  ret_orig_x = x_orig.emplace(1.1);
  is_equal(x, x_orig);
}