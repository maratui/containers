#include <gtest/gtest.h>

#include "./s21_containers.h"

TEST(TestS21Containers, Vector) {
  std::vector<int> std_default_constructor;
  s21::vector<int> s21_default_constructor;
  ASSERT_EQ(std_default_constructor.size(), s21_default_constructor.size());
  ASSERT_EQ(std_default_constructor.capacity(), s21_default_constructor.capacity());

  std::vector<int> std_parameterized_constructor(100);
  s21::vector<int> s21_parameterized_constructor(100);
  ASSERT_EQ(std_parameterized_constructor.size(), s21_parameterized_constructor.size());
  ASSERT_EQ(std_parameterized_constructor.capacity(), s21_parameterized_constructor.capacity());

  std::vector<int> std_initializer_list_constructor{1, 2, 3, 4, 5};
  s21::vector<int> s21_initializer_list_constructor{1, 2, 3, 4, 5};
  ASSERT_EQ(std_initializer_list_constructor.size(), s21_initializer_list_constructor.size());
  ASSERT_EQ(std_initializer_list_constructor.capacity(), s21_initializer_list_constructor.capacity());
  for (size_t i = 0; i < std_initializer_list_constructor.size(); i++)
    ASSERT_EQ(std_initializer_list_constructor.at(i), s21_initializer_list_constructor.at(i));

  std::vector<int> std_copy_constructor(std_initializer_list_constructor);
  s21::vector<int> s21_copy_constructor(s21_initializer_list_constructor);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(s21_initializer_list_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(s21_initializer_list_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));
  for (size_t i = 0; i < s21_initializer_list_constructor.size(); i++)
    ASSERT_EQ(s21_initializer_list_constructor.at(i), s21_copy_constructor.at(i));

  std::vector<int> std_move_constructor(std::move(std_initializer_list_constructor));
  s21::vector<int> s21_move_constructor(std::move(s21_initializer_list_constructor));
  ASSERT_EQ(std_move_constructor.size(), s21_move_constructor.size());
  ASSERT_EQ(std_move_constructor.capacity(), s21_move_constructor.capacity());
  ASSERT_EQ(s21_copy_constructor.size(), s21_move_constructor.size());
  ASSERT_EQ(s21_copy_constructor.capacity(), s21_move_constructor.capacity());
  for (size_t i = 0; i < std_move_constructor.size(); i++)
    ASSERT_EQ(std_move_constructor.at(i), s21_move_constructor.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(s21_copy_constructor.at(i), s21_move_constructor.at(i));
  ASSERT_EQ(0, std_initializer_list_constructor.size());
  ASSERT_EQ(0, std_initializer_list_constructor.capacity());
  ASSERT_EQ(0, s21_initializer_list_constructor.size());
  ASSERT_EQ(0, s21_initializer_list_constructor.capacity());

  std::vector<int> std_operator_overload;
  s21::vector<int> s21_operator_overload;
  std_operator_overload = std_move_constructor;
  s21_operator_overload = s21_move_constructor;
  ASSERT_EQ(std_operator_overload.size(), s21_operator_overload.size());
  ASSERT_EQ(std_operator_overload.capacity(), s21_operator_overload.capacity());
  ASSERT_EQ(s21_move_constructor.size(), s21_operator_overload.size());
  ASSERT_EQ(s21_move_constructor.capacity(), s21_operator_overload.capacity());
  for (size_t i = 0; i < std_operator_overload.size(); i++)
    ASSERT_EQ(std_operator_overload.at(i), s21_operator_overload.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(s21_move_constructor.at(i), s21_operator_overload.at(i));

  std_operator_overload = std::move(std_move_constructor);
  s21_operator_overload = std::move(s21_move_constructor);
  ASSERT_EQ(std_operator_overload.size(), s21_operator_overload.size());
  ASSERT_EQ(std_operator_overload.capacity(), s21_operator_overload.capacity());
  ASSERT_EQ(s21_copy_constructor.size(), s21_operator_overload.size());
  ASSERT_EQ(s21_copy_constructor.capacity(), s21_operator_overload.capacity());
  for (size_t i = 0; i < std_operator_overload.size(); i++)
    ASSERT_EQ(std_operator_overload.at(i), s21_operator_overload.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(s21_copy_constructor.at(i), s21_operator_overload.at(i));
  ASSERT_EQ(0, std_move_constructor.size());
  ASSERT_EQ(0, std_move_constructor.capacity());
  ASSERT_EQ(0, s21_move_constructor.size());
  ASSERT_EQ(0, s21_move_constructor.capacity());

  s21_operator_overload = s21_operator_overload;
  ASSERT_EQ(std_copy_constructor.size(), s21_operator_overload.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_operator_overload.capacity());
  for (size_t i = 0; i < std_operator_overload.size(); i++)
    ASSERT_EQ(std_operator_overload.at(i), s21_operator_overload.at(i));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  ASSERT_EQ(0, std_operator_overload.size());
  ASSERT_EQ(0, std_operator_overload.capacity());
  ASSERT_EQ(0, s21_operator_overload.size());
  ASSERT_EQ(0, s21_operator_overload.capacity());

  ASSERT_NO_THROW(std_copy_constructor.at(4));
  ASSERT_NO_THROW(s21_copy_constructor.at(4));
  ASSERT_THROW(std_copy_constructor.at(5), std::out_of_range);
  ASSERT_THROW(s21_copy_constructor.at(5), std::out_of_range);
  try {
    s21_operator_overload.at(5);
  } catch (const std::out_of_range &e) {
    ASSERT_STREQ("Incorrect input, index is outside the vector", e.what());
  }

  std::vector<int> const std_const_vector{1};
  s21::vector<int> const s21_const_vector{1};
  ASSERT_NO_THROW(std_const_vector.at(0));
  ASSERT_NO_THROW(s21_const_vector.at(0));
  ASSERT_THROW(std_const_vector.at(1), std::out_of_range);
  ASSERT_THROW(s21_const_vector.at(1), std::out_of_range);
  ASSERT_EQ(std_const_vector.at(0), s21_const_vector.at(0));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

