#include <gtest/gtest.h>

#include "./s21_containers.h"

TEST(TestS21Containers, Vector) {
  std::vector<int> std_default_constructor;
  s21::vector<int> s21_default_constructor;
  ASSERT_EQ(std_default_constructor.size(), s21_default_constructor.size());
  ASSERT_EQ(std_default_constructor.capacity(), s21_default_constructor.capacity());
//  ASSERT_THROW(std_default_constructor.at(0), std::out_of_range);
//  ASSERT_THROW(s21_default_constructor.at(0), std::out_of_range);

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

  s21::vector<int> s21_copy_constructor(s21_initializer_list_constructor);
  ASSERT_EQ(s21_initializer_list_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(s21_initializer_list_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t i = 0; i < s21_initializer_list_constructor.size(); i++)
    ASSERT_EQ(s21_initializer_list_constructor.at(i), s21_copy_constructor.at(i));

  s21::vector<int> s21_move_constructor(std::move(s21_initializer_list_constructor));
  ASSERT_EQ(s21_copy_constructor.size(), s21_move_constructor.size());
  ASSERT_EQ(s21_copy_constructor.capacity(), s21_move_constructor.capacity());
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(s21_copy_constructor.at(i), s21_move_constructor.at(i));
  ASSERT_EQ(0, s21_initializer_list_constructor.size());
  ASSERT_EQ(0, s21_initializer_list_constructor.capacity());
/* 
  s21::vector<int> operator_overload;
  operator_overload = std::move(s21_move_constructor);
  ASSERT_EQ(s21_copy_constructor.size(), s21_operator_overload.size());
  ASSERT_EQ(s21_copy_constructor.capacity(), s21_operator_overload.capacity());
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(s21_copy_constructor.at(i), s21_operator_overload.at(i));
  ASSERT_EQ(0, s21_move_constructor.size());
  ASSERT_EQ(0, s21_move_constructor.capacity());
*/ 

}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

