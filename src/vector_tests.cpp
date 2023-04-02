#include <gtest/gtest.h>

#include <type_traits>

#include "./s21_containers.h"

template <typename T>
void test_vector(std::initializer_list<T> const& items) {
  T temp;

  //---------------------------------------------------------------------------

  std::vector<T> std_default_constructor;
  s21::vector<T> s21_default_constructor;
  ASSERT_EQ(std_default_constructor.size(), s21_default_constructor.size());
  ASSERT_EQ(std_default_constructor.capacity(),
            s21_default_constructor.capacity());

  std::vector<T> const std_const_default_constructor;
  s21::vector<T> const s21_const_default_constructor;
  ASSERT_EQ(std_const_default_constructor.size(),
            s21_const_default_constructor.size());
  ASSERT_EQ(std_const_default_constructor.capacity(),
            s21_const_default_constructor.capacity());

  //---------------------------------------------------------------------------

  std::vector<T> std_parameterized_constructor(100);
  s21::vector<T> s21_parameterized_constructor(100);
  ASSERT_EQ(std_parameterized_constructor.size(),
            s21_parameterized_constructor.size());
  ASSERT_EQ(std_parameterized_constructor.capacity(),
            s21_parameterized_constructor.capacity());

  std::vector<T> const std_const_parameterized_constructor(100);
  s21::vector<T> const s21_const_parameterized_constructor(100);
  ASSERT_EQ(std_const_parameterized_constructor.size(),
            s21_const_parameterized_constructor.size());
  ASSERT_EQ(std_const_parameterized_constructor.capacity(),
            s21_const_parameterized_constructor.capacity());

  //---------------------------------------------------------------------------

  std::vector<T> std_initializer_list_constructor(items);
  s21::vector<T> s21_initializer_list_constructor(items);
  ASSERT_EQ(std_initializer_list_constructor.size(),
            s21_initializer_list_constructor.size());
  ASSERT_EQ(std_initializer_list_constructor.capacity(),
            s21_initializer_list_constructor.capacity());
  for (size_t i = 0; i < std_initializer_list_constructor.size(); i++)
    ASSERT_EQ(std_initializer_list_constructor.at(i),
              s21_initializer_list_constructor.at(i));

  std::vector<T> const std_const_initializer_list_constructor(items);
  s21::vector<T> const s21_const_initializer_list_constructor(items);
  ASSERT_EQ(std_const_initializer_list_constructor.size(),
            s21_const_initializer_list_constructor.size());
  ASSERT_EQ(std_const_initializer_list_constructor.capacity(),
            s21_const_initializer_list_constructor.capacity());
  for (size_t i = 0; i < std_const_initializer_list_constructor.size(); i++)
    ASSERT_EQ(std_const_initializer_list_constructor.at(i),
              s21_const_initializer_list_constructor.at(i));

  //---------------------------------------------------------------------------

  std::vector<T> std_copy_constructor(std_initializer_list_constructor);
  s21::vector<T> s21_copy_constructor(s21_initializer_list_constructor);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(s21_initializer_list_constructor.size(),
            s21_copy_constructor.size());
  ASSERT_EQ(s21_initializer_list_constructor.capacity(),
            s21_copy_constructor.capacity());
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));
  for (size_t i = 0; i < s21_initializer_list_constructor.size(); i++)
    ASSERT_EQ(s21_initializer_list_constructor.at(i),
              s21_copy_constructor.at(i));

  std::vector<T> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  s21::vector<T> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  ASSERT_EQ(std_const_copy_constructor.size(),
            s21_const_copy_constructor.size());
  ASSERT_EQ(std_const_copy_constructor.capacity(),
            s21_const_copy_constructor.capacity());
  ASSERT_EQ(s21_const_initializer_list_constructor.size(),
            s21_const_copy_constructor.size());
  ASSERT_EQ(s21_const_initializer_list_constructor.capacity(),
            s21_const_copy_constructor.capacity());
  for (size_t i = 0; i < std_const_copy_constructor.size(); i++)
    ASSERT_EQ(std_const_copy_constructor.at(i),
              s21_const_copy_constructor.at(i));
  for (size_t i = 0; i < s21_initializer_list_constructor.size(); i++)
    ASSERT_EQ(s21_const_initializer_list_constructor.at(i),
              s21_const_copy_constructor.at(i));

  //---------------------------------------------------------------------------

  std::vector<T> std_move_constructor(
      std::move(std_initializer_list_constructor));
  s21::vector<T> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
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

  std::vector<T> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  s21::vector<T> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  ASSERT_EQ(std_const_move_constructor.size(),
            s21_const_move_constructor.size());
  ASSERT_EQ(std_const_move_constructor.capacity(),
            s21_const_move_constructor.capacity());
  ASSERT_EQ(s21_const_copy_constructor.size(),
            s21_const_move_constructor.size());
  ASSERT_EQ(s21_const_copy_constructor.capacity(),
            s21_const_move_constructor.capacity());
  for (size_t i = 0; i < std_const_move_constructor.size(); i++)
    ASSERT_EQ(std_const_move_constructor.at(i),
              s21_const_move_constructor.at(i));
  for (size_t i = 0; i < s21_const_copy_constructor.size(); i++)
    ASSERT_EQ(s21_const_copy_constructor.at(i),
              s21_const_move_constructor.at(i));
  ASSERT_EQ(5, std_const_initializer_list_constructor.size());
  ASSERT_EQ(5, std_const_initializer_list_constructor.capacity());
  ASSERT_EQ(5, s21_const_initializer_list_constructor.size());
  ASSERT_EQ(5, s21_const_initializer_list_constructor.capacity());

  //---------------------------------------------------------------------------

  std::vector<T> std_operator_overload;
  s21::vector<T> s21_operator_overload;
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

  ASSERT_NO_THROW(std_operator_overload = std_const_move_constructor);
  ASSERT_NO_THROW(s21_operator_overload = s21_const_move_constructor);
  ASSERT_EQ(std_operator_overload.size(), s21_operator_overload.size());
  ASSERT_EQ(std_operator_overload.capacity(), s21_operator_overload.capacity());
  ASSERT_EQ(s21_const_move_constructor.size(), s21_operator_overload.size());
  ASSERT_EQ(s21_const_move_constructor.capacity(),
            s21_operator_overload.capacity());
  for (size_t i = 0; i < std_operator_overload.size(); i++)
    ASSERT_EQ(std_operator_overload.at(i), s21_operator_overload.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(s21_const_move_constructor.at(i), s21_operator_overload.at(i));

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

  std_operator_overload = std::move(std_const_move_constructor);
  s21_operator_overload = std::move(s21_const_move_constructor);
  ASSERT_EQ(std_operator_overload.size(), s21_operator_overload.size());
  ASSERT_EQ(std_operator_overload.capacity(), s21_operator_overload.capacity());
  ASSERT_EQ(s21_copy_constructor.size(), s21_operator_overload.size());
  ASSERT_EQ(s21_copy_constructor.capacity(), s21_operator_overload.capacity());
  for (size_t i = 0; i < std_operator_overload.size(); i++)
    ASSERT_EQ(std_operator_overload.at(i), s21_operator_overload.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(s21_copy_constructor.at(i), s21_operator_overload.at(i));
  ASSERT_EQ(5, std_const_move_constructor.size());
  ASSERT_EQ(5, std_const_move_constructor.capacity());
  ASSERT_EQ(5, s21_const_move_constructor.size());
  ASSERT_EQ(5, s21_const_move_constructor.capacity());

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

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.at(3);
  std_copy_constructor.at(3) = temp;
  temp = s21_copy_constructor.at(3);
  s21_copy_constructor.at(3) = temp;
  ASSERT_NO_THROW(std_copy_constructor.at(4));
  ASSERT_NO_THROW(s21_copy_constructor.at(4));
  ASSERT_THROW(std_copy_constructor.at(5), std::out_of_range);
  ASSERT_THROW(s21_copy_constructor.at(5), std::out_of_range);
  try {
    s21_operator_overload.at(5);
  } catch (const std::out_of_range& e) {
    ASSERT_STREQ("Incorrect input, index is outside the vector", e.what());
  }

  temp = std_const_copy_constructor.at(3);
  temp = s21_const_copy_constructor.at(3);
  ASSERT_NO_THROW(std_const_copy_constructor.at(0));
  ASSERT_NO_THROW(s21_const_copy_constructor.at(0));
  ASSERT_THROW(std_const_copy_constructor.at(5), std::out_of_range);
  ASSERT_THROW(s21_const_copy_constructor.at(5), std::out_of_range);
  ASSERT_EQ(std_const_copy_constructor.at(0), s21_const_copy_constructor.at(0));

  //---------------------------------------------------------------------------

  temp = std_copy_constructor[3];
  std_copy_constructor[3] = temp;
  temp = s21_copy_constructor[3];
  s21_copy_constructor[3] = temp;
  ASSERT_NO_THROW(std_copy_constructor[4]);
  ASSERT_NO_THROW(s21_copy_constructor[4]);
  ASSERT_EQ(std_copy_constructor[4], s21_copy_constructor[4]);
  ASSERT_NO_THROW(std_copy_constructor[5]);
  ASSERT_NO_THROW(s21_copy_constructor[5]);

  temp = std_const_copy_constructor[3];
  temp = s21_const_copy_constructor[3];
  ASSERT_NO_THROW(std_const_copy_constructor[0]);
  ASSERT_NO_THROW(s21_const_copy_constructor[0]);
  ASSERT_EQ(std_const_copy_constructor[0], s21_const_copy_constructor[0]);
  ASSERT_NO_THROW(std_const_copy_constructor[5]);
  ASSERT_NO_THROW(s21_const_copy_constructor[5]);

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.front();
  std_copy_constructor.front() = temp;
  temp = s21_copy_constructor.front();
  s21_copy_constructor.front() = temp;
  ASSERT_EQ(std_copy_constructor.front(), s21_copy_constructor.front());

  temp = std_const_copy_constructor.front();
  temp = s21_const_copy_constructor.front();
  ASSERT_EQ(std_const_copy_constructor.front(),
            s21_const_copy_constructor.front());

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.back();
  std_copy_constructor.back() = temp;
  temp = s21_copy_constructor.back();
  s21_copy_constructor.back() = temp;
  ASSERT_EQ(std_copy_constructor.back(), s21_copy_constructor.back());

  temp = std_const_copy_constructor.back();
  temp = s21_const_copy_constructor.back();
  ASSERT_EQ(std_const_copy_constructor.back(),
            s21_const_copy_constructor.back());

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.data()[0];
  std_copy_constructor.data()[0] = temp;
  temp = s21_copy_constructor.data()[0];
  s21_copy_constructor.data()[0] = temp;
  ASSERT_EQ(*std_copy_constructor.data(), *s21_copy_constructor.data());
  ASSERT_NE(std_copy_constructor.data(), s21_copy_constructor.data());

  temp = (std_const_copy_constructor.data() + 1)[0];
  temp = (s21_const_copy_constructor.data() + 1)[0];
  ASSERT_EQ(*std_const_copy_constructor.data(),
            *s21_const_copy_constructor.data());
  ASSERT_NE(std_const_copy_constructor.data(),
            s21_const_copy_constructor.data());

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.begin()[0];
  std_copy_constructor.begin()[0] = temp;
  temp = s21_copy_constructor.begin()[0];
  s21_copy_constructor.begin()[0] = temp;
  temp = (std_copy_constructor.end() - 1)[0];
  (std_copy_constructor.end() - 1)[0] = temp;
  temp = (s21_copy_constructor.end() - 1)[0];
  (s21_copy_constructor.end() - 1)[0] = temp;
  ASSERT_EQ(*std_copy_constructor.begin(), *s21_copy_constructor.begin());
  ASSERT_EQ((std_copy_constructor.end() - std_copy_constructor.begin()),
            (s21_copy_constructor.end() - s21_copy_constructor.begin()));

  temp = std_const_copy_constructor.begin()[0];
  temp = s21_const_copy_constructor.begin()[0];
  temp = (std_const_copy_constructor.end() - 1)[0];
  temp = (s21_const_copy_constructor.end() - 1)[0];
  ASSERT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.begin());
  ASSERT_EQ(
      (std_const_copy_constructor.end() - std_const_copy_constructor.begin()),
      (s21_const_copy_constructor.end() - s21_const_copy_constructor.begin()));

  //---------------------------------------------------------------------------

  ASSERT_FALSE(std_copy_constructor.empty());
  ASSERT_FALSE(s21_copy_constructor.empty());
  ASSERT_FALSE(std_const_copy_constructor.empty());
  ASSERT_FALSE(s21_const_copy_constructor.empty());
  ASSERT_TRUE(std_move_constructor.empty());
  ASSERT_TRUE(s21_move_constructor.empty());

  //---------------------------------------------------------------------------

  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_const_copy_constructor.size(),
            s21_const_copy_constructor.size());
  ASSERT_EQ(std_move_constructor.size(), s21_move_constructor.size());

  //---------------------------------------------------------------------------

  ASSERT_EQ(std_copy_constructor.max_size(), s21_copy_constructor.max_size());
  ASSERT_EQ(std_const_copy_constructor.max_size(),
            s21_const_copy_constructor.max_size());

  //---------------------------------------------------------------------------

  std_copy_constructor.reserve(5);
  s21_copy_constructor.reserve(5);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(5, std_copy_constructor.size());
  ASSERT_EQ(5, std_copy_constructor.capacity());
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));

  std_copy_constructor.reserve(4);
  s21_copy_constructor.reserve(4);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(5, std_copy_constructor.size());
  ASSERT_EQ(5, std_copy_constructor.capacity());
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));

  std_copy_constructor.reserve(7);
  s21_copy_constructor.reserve(7);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(5, std_copy_constructor.size());
  ASSERT_EQ(7, std_copy_constructor.capacity());
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));

  std_copy_constructor.reserve(6);
  s21_copy_constructor.reserve(6);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(5, std_copy_constructor.size());
  ASSERT_EQ(7, std_copy_constructor.capacity());
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));

  //---------------------------------------------------------------------------

  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(std_const_copy_constructor.capacity(),
            s21_const_copy_constructor.capacity());

  //---------------------------------------------------------------------------

  ASSERT_EQ(5, std_copy_constructor.size());
  ASSERT_EQ(7, std_copy_constructor.capacity());
  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(5, std_copy_constructor.size());
  ASSERT_EQ(5, std_copy_constructor.capacity());
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));
  for (size_t i = 0; i < s21_copy_constructor.size(); i++)
    ASSERT_EQ(std_copy_constructor.at(i), s21_copy_constructor.at(i));

  //---------------------------------------------------------------------------

  std_copy_constructor.clear();
  s21_copy_constructor.clear();
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  ASSERT_EQ(0, s21_copy_constructor.size());
  ASSERT_EQ(5, s21_copy_constructor.capacity());
  for (size_t i = 0; i < std_copy_constructor.capacity(); i++)
    ASSERT_EQ(std_copy_constructor[i], s21_copy_constructor[i]);
  ASSERT_EQ(*std_copy_constructor.begin(), *s21_copy_constructor.begin());
  ASSERT_EQ((std_copy_constructor.end() - std_copy_constructor.begin()),
            (s21_copy_constructor.end() - s21_copy_constructor.begin()));
  ASSERT_EQ(0, (s21_copy_constructor.end() - s21_copy_constructor.begin()));

  //---------------------------------------------------------------------------

  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.insert(std_copy_constructor.begin(), i + 1);
    s21_copy_constructor.insert(s21_copy_constructor.begin(), i + 1);
    ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
    ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
    for (size_t j = 0; j < std_copy_constructor.size(); j++)
      ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
  }
  std_copy_constructor.insert(std_copy_constructor.begin() + 5, 105);
  s21_copy_constructor.insert(s21_copy_constructor.begin() + 5, 105);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);

  std_copy_constructor.insert(std_copy_constructor.begin(), 101);
  s21_copy_constructor.insert(s21_copy_constructor.begin(), 101);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);

  std_copy_constructor.insert(std_copy_constructor.end(), 111);
  s21_copy_constructor.insert(s21_copy_constructor.end(), 111);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);

  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  std_copy_constructor.insert(std_copy_constructor.end(), 222);
  s21_copy_constructor.insert(s21_copy_constructor.end(), 222);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);

  //---------------------------------------------------------------------------

  //  std::cout << std_copy_constructor.capacity() << " ; " <<
  //  std_copy_constructor.size() << std::endl; for (size_t j = 0; j <
  //  std_copy_constructor.capacity(); j++) std::cout << std_copy_constructor[j]
  //  << " ";
  std_copy_constructor.erase(std_copy_constructor.begin());
  s21_copy_constructor.erase(s21_copy_constructor.begin());
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
  //  std::cout << std::endl;
  //  std::cout << std_copy_constructor.capacity() << " ; " <<
  //  std_copy_constructor.size() << std::endl; for (size_t j = 0; j <
  //  std_copy_constructor.capacity(); j++) std::cout << std_copy_constructor[j]
  //  << " "; std::cout << std::endl;
  std_copy_constructor.erase(std_copy_constructor.begin() + 5);
  s21_copy_constructor.erase(s21_copy_constructor.begin() + 5);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);

  //  std::cout << std::endl;
  //  std::cout << std_copy_constructor.capacity() << " ; " <<
  //  std_copy_constructor.size() << std::endl; for (size_t j = 0; j <
  //  std_copy_constructor.size(); j++) std::cout << std_copy_constructor[j] <<
  //  " "; std::cout << std::endl;
  std_copy_constructor.erase(std_copy_constructor.end() - 1);
  s21_copy_constructor.erase(s21_copy_constructor.end() - 1);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);

  //  std::cout << std::endl;
  //  std::cout << std_copy_constructor.capacity() << " ; " <<
  //  std_copy_constructor.size() << std::endl; for (size_t j = 0; j <
  //  std_copy_constructor.capacity(); j++) std::cout << std_copy_constructor[j]
  //  << " "; std::cout << std::endl; std::cout <<
  //  std_copy_constructor.capacity() << " ; " << std_copy_constructor.size() <<
  //  std::endl; for (size_t j = 0; j < std_copy_constructor.size(); j++)
  //  std::cout << std_copy_constructor[j] << " "; std::cout << std::endl;

  //-------------------------

  std_copy_constructor.clear();
  s21_copy_constructor.clear();
  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.push_back(i + 1);
    s21_copy_constructor.push_back(i + 1);
    ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
    ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
    for (size_t j = 0; j < std_copy_constructor.size(); j++)
      ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
  }
  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  std_copy_constructor.push_back(222);
  s21_copy_constructor.push_back(222);
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);

  //---------------

  std_copy_constructor.pop_back();
  s21_copy_constructor.pop_back();
  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);

  //-----------------
  /*
    std::cout << std_copy_constructor.capacity() << " ; " <<
    std_copy_constructor.size() << std::endl; for (size_t j = 0; j <
    std_copy_constructor.size(); j++) std::cout << std_copy_constructor[j] << "
    "; std::cout << std::endl;

     std::cout << std_move_constructor.capacity() << " ; " <<
    std_move_constructor.size() << std::endl; for (size_t j = 0; j <
    std_move_constructor.size(); j++) std::cout << std_move_constructor[j] << "
    "; std::cout << std::endl << std::endl;
  */
  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);

  ASSERT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  ASSERT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  for (size_t j = 0; j < std_copy_constructor.size(); j++)
    ASSERT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
  /*
    std::cout << std_move_constructor.capacity() << " ; " <<
    std_move_constructor.size() << std::endl; for (size_t j = 0; j <
    std_move_constructor.size(); j++) std::cout << std_move_constructor[j] << "
    "; std::cout << std::endl << std::endl; std::cout <<
    s21_move_constructor.capacity() << " ; " << s21_move_constructor.size() <<
    std::endl; for (size_t j = 0; j < s21_move_constructor.size(); j++)
      std::cout << s21_move_constructor[j] << " ";
    std::cout << std::endl << std::endl;
  */
  ASSERT_EQ(std_move_constructor.size(), s21_move_constructor.size());
  ASSERT_EQ(std_move_constructor.capacity(), s21_move_constructor.capacity());
  for (size_t j = 0; j < std_move_constructor.size(); j++)
    ASSERT_EQ(std_move_constructor[j], s21_move_constructor[j]);

  /*
    std::cout << std_copy_constructor.capacity() << " ; " <<
    std_copy_constructor.size() << std::endl; for (size_t j = 0; j <
    std_copy_constructor.size(); j++) std::cout << std_copy_constructor[j] << "
    "; std::cout << std::endl;

    std::cout << std_move_constructor.capacity() << " ; " <<
    std_move_constructor.size() << std::endl; for (size_t j = 0; j <
    std_move_constructor.size(); j++) std::cout << std_move_constructor[j] << "
    "; std::cout << std::endl << std::endl;
  */
}

TEST(TestS21Containers, Vector) {
  //   test_vector<bool>({0, 1, 0, 1, 1});
    test_vector<signed char>({0, 1, -128, 4, 127});
    test_vector<unsigned char>({0, 1, 0, 4, 255});
    test_vector<char>({0, 1, 0, 4, 255});
    test_vector<short>({0, 1, -32768, 4, 32767});
    test_vector<unsigned short>({0, 1, 0, 4, 65535});
  test_vector<int>({0, 1, -2147483648, 4, 2147483647});
//  test_vector<unsigned int>({0, 1, 0, 4, 4294967295});
//  test_vector<long>({0, 1, -2147483648, 4, 2147483647});
//  test_vector<unsigned long>({0, 1, 0, 4, 4294967295});
//  test_vector<long long>({0, 1, -2147483648, 4, 2147483647});
//  test_vector<unsigned long long>({0, 1, 0, 4, 4294967295});
//  test_vector<float>({0, 1, FLT_MIN, -FLT_MAX, FLT_MAX});
//  test_vector<double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
//  test_vector<long double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}