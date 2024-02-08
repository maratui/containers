#include "./tests.h"

template <typename T>
void TestVector(std::initializer_list<T> const &items) {
  T temp;
  //---------------------------------------------------------------------------

  std::vector<T> std_default_constructor;
  s21::vector<T> s21_default_constructor;
  EXPECT_TRUE(ExpectEqualVectorBeginEnd(&std_default_constructor,
                                        &s21_default_constructor));

  std::vector<T> const std_const_default_constructor;
  s21::vector<T> const s21_const_default_constructor;
  EXPECT_TRUE(ExpectEqualVectorBeginEnd(&std_const_default_constructor,
                                        &s21_const_default_constructor));

  //---------------------------------------------------------------------------

  std::vector<T> std_parameterized_constructor(100);
  s21::vector<T> s21_parameterized_constructor(100);
  EXPECT_TRUE(ExpectEqualVectors(&std_parameterized_constructor,
                                 &s21_parameterized_constructor));

  std::vector<T> const std_const_parameterized_constructor(100);
  s21::vector<T> const s21_const_parameterized_constructor(100);
  EXPECT_TRUE(ExpectEqualVectors(&std_const_parameterized_constructor,
                                 &s21_const_parameterized_constructor));

  //---------------------------------------------------------------------------

  std::vector<T> std_initializer_list_constructor(items);
  s21::vector<T> s21_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualVectors(&std_initializer_list_constructor,
                                 &s21_initializer_list_constructor));

  std::vector<T> const std_const_initializer_list_constructor(items);
  s21::vector<T> const s21_const_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualVectors(&std_const_initializer_list_constructor,
                                 &s21_const_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std::vector<T> std_copy_constructor(std_initializer_list_constructor);
  s21::vector<T> s21_copy_constructor(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualVectors(&std_initializer_list_constructor,
                                 &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std::vector<T> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  s21::vector<T> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualVectors(&std_const_initializer_list_constructor,
                                 &s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_const_copy_constructor,
                                 &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  std::vector<T> std_move_constructor(
      std::move(std_initializer_list_constructor));
  s21::vector<T> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_initializer_list_constructor,
                                 &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_move_constructor, &s21_move_constructor));

  std::vector<T> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  s21::vector<T> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_const_initializer_list_constructor,
                                 &s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_const_move_constructor,
                                 &s21_const_move_constructor));

  //---------------------------------------------------------------------------
  std_default_constructor = std_move_constructor;
  s21_default_constructor = s21_move_constructor;
  EXPECT_TRUE(
      ExpectEqualVectors(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_move_constructor, &s21_move_constructor));

  std_default_constructor = std_const_move_constructor;
  s21_default_constructor = s21_const_move_constructor;
  EXPECT_TRUE(
      ExpectEqualVectors(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_const_move_constructor,
                                 &s21_const_move_constructor));

  std::vector<T> std_operator_overload;
  s21::vector<T> s21_operator_overload;
  std_operator_overload = std::move(std_move_constructor);
  s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_TRUE(
      ExpectEqualVectors(&std_operator_overload, &s21_operator_overload));
  EXPECT_TRUE(ExpectEqualVectors(&std_move_constructor, &s21_move_constructor));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_TRUE(
      ExpectEqualVectors(&std_operator_overload, &s21_operator_overload));

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.at(3);
  std_copy_constructor.at(3) = temp;
  temp = s21_copy_constructor.at(3);
  s21_copy_constructor.at(3) = temp;
  EXPECT_NO_THROW(std_copy_constructor.at(4));
  EXPECT_NO_THROW(s21_copy_constructor.at(4));

  temp = std_const_copy_constructor.at(3);
  temp = s21_const_copy_constructor.at(3);
  EXPECT_NO_THROW(std_const_copy_constructor.at(0));
  EXPECT_NO_THROW(s21_const_copy_constructor.at(0));
  EXPECT_EQ(std_const_copy_constructor.at(0), s21_const_copy_constructor.at(0));

  //---------------------------------------------------------------------------

  temp = std_copy_constructor[3];
  std_copy_constructor[3] = temp;
  temp = s21_copy_constructor[3];
  s21_copy_constructor[3] = temp;
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    EXPECT_EQ(std_copy_constructor[i], s21_copy_constructor[i]);
  EXPECT_NO_THROW(std_copy_constructor[4]);
  EXPECT_NO_THROW(s21_copy_constructor[4]);
  EXPECT_NO_THROW(std_copy_constructor[5]);
  EXPECT_NO_THROW(s21_copy_constructor[5]);

  temp = std_const_copy_constructor[3];
  temp = s21_const_copy_constructor[3];
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    EXPECT_EQ(std_const_copy_constructor[i], s21_const_copy_constructor[i]);
  EXPECT_NO_THROW(std_const_copy_constructor[4]);
  EXPECT_NO_THROW(s21_const_copy_constructor[4]);
  EXPECT_NO_THROW(std_const_copy_constructor[5]);
  EXPECT_NO_THROW(s21_const_copy_constructor[5]);

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.front();
  std_copy_constructor.front() = temp;
  temp = s21_copy_constructor.front();
  s21_copy_constructor.front() = temp;
  EXPECT_EQ(std_copy_constructor.front(), s21_copy_constructor.front());

  temp = std_const_copy_constructor.front();
  temp = s21_const_copy_constructor.front();
  EXPECT_EQ(std_const_copy_constructor.front(),
            s21_const_copy_constructor.front());

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.back();
  std_copy_constructor.back() = temp;
  temp = s21_copy_constructor.back();
  s21_copy_constructor.back() = temp;
  EXPECT_EQ(std_copy_constructor.back(), s21_copy_constructor.back());

  temp = std_const_copy_constructor.back();
  temp = s21_const_copy_constructor.back();
  EXPECT_EQ(std_const_copy_constructor.back(),
            s21_const_copy_constructor.back());

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.data()[0];
  std_copy_constructor.data()[0] = temp;
  temp = s21_copy_constructor.data()[0];
  s21_copy_constructor.data()[0] = temp;
  for (std::size_t i = 0; i < std_copy_constructor.size(); ++i)
    EXPECT_EQ(std_copy_constructor.data()[i], s21_copy_constructor.data()[i]);
  for (std::size_t i = 0; i < std_copy_constructor.size(); ++i)
    EXPECT_EQ(*(std_copy_constructor.data() + i),
              *(s21_copy_constructor.data() + i));
  EXPECT_NE(std_copy_constructor.data(), s21_copy_constructor.data());

  temp = *(std_const_copy_constructor.data() + 1);
  temp = *(s21_const_copy_constructor.data() + 1);
  for (std::size_t i = 0; i < std_const_copy_constructor.size(); ++i)
    EXPECT_EQ(std_const_copy_constructor.data()[i],
              s21_const_copy_constructor.data()[i]);
  for (std::size_t i = 0; i < std_const_copy_constructor.size(); ++i)
    EXPECT_EQ(*(std_const_copy_constructor.data() + i),
              *(s21_const_copy_constructor.data() + i));
  EXPECT_NE(std_const_copy_constructor.data(),
            s21_const_copy_constructor.data());

  //---------------------------------------------------------------------------

  temp = *std_copy_constructor.begin();
  *std_copy_constructor.begin() = temp;
  temp = *s21_copy_constructor.begin();
  *s21_copy_constructor.begin() = temp;
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.begin());
  EXPECT_TRUE(ExpectNotEqualVectorBeginEnd(&std_copy_constructor,
                                           &s21_copy_constructor));

  temp = *std_const_copy_constructor.begin();
  temp = *s21_const_copy_constructor.begin();
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.begin());
  EXPECT_TRUE(ExpectNotEqualVectorBeginEnd(&std_const_copy_constructor,
                                           &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  EXPECT_FALSE(std_copy_constructor.empty());
  EXPECT_FALSE(s21_copy_constructor.empty());
  EXPECT_FALSE(std_const_copy_constructor.empty());
  EXPECT_FALSE(s21_const_copy_constructor.empty());
  EXPECT_TRUE(std_move_constructor.empty());
  EXPECT_TRUE(s21_move_constructor.empty());

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  EXPECT_EQ(std_const_copy_constructor.size(),
            s21_const_copy_constructor.size());
  EXPECT_EQ(std_move_constructor.size(), s21_move_constructor.size());

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_copy_constructor.max_size(), s21_copy_constructor.max_size());
  EXPECT_EQ(std_const_copy_constructor.max_size(),
            s21_const_copy_constructor.max_size());

  //---------------------------------------------------------------------------

  std_copy_constructor.reserve(5);
  s21_copy_constructor.reserve(5);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.reserve(4);
  s21_copy_constructor.reserve(4);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.reserve(7);
  s21_copy_constructor.reserve(7);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.reserve(6);
  s21_copy_constructor.reserve(6);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_copy_constructor.capacity(), s21_copy_constructor.capacity());
  EXPECT_EQ(std_const_copy_constructor.capacity(),
            s21_const_copy_constructor.capacity());

  //---------------------------------------------------------------------------

  EXPECT_EQ(5, std_copy_constructor.size());
  EXPECT_EQ(7, std_copy_constructor.capacity());
  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.clear();
  s21_copy_constructor.clear();
  EXPECT_TRUE(
      ExpectEqualVectorBeginEnd(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------
  {
    auto item = items.end();
    temp = *(--item);
  }
  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.insert(std_copy_constructor.begin(), temp);
    auto begin =
        s21_copy_constructor.insert(s21_copy_constructor.begin(), temp);
    EXPECT_TRUE(begin == s21_copy_constructor.begin());
    EXPECT_TRUE(
        ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));
  }

  std_default_constructor = std_copy_constructor;
  s21_default_constructor = s21_copy_constructor;
  EXPECT_TRUE(
      ExpectEqualVectors(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_default_constructor = std_default_constructor;
  s21_default_constructor = s21_default_constructor;
  EXPECT_TRUE(
      ExpectEqualVectors(&std_default_constructor, &s21_default_constructor));

  auto std_pos = std_copy_constructor.begin();
  ++std_pos;
  std_copy_constructor.insert(std_pos, temp);
  auto s21_pos = s21_copy_constructor.begin();
  ++s21_pos;
  s21_copy_constructor.insert(s21_pos, temp);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.insert(std_copy_constructor.begin(), temp);
  s21_copy_constructor.insert(s21_copy_constructor.begin(), temp);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.insert(std_copy_constructor.end(), temp);
  s21_copy_constructor.insert(s21_copy_constructor.end(), temp);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  std_copy_constructor.insert(std_copy_constructor.end(), temp);
  s21_copy_constructor.insert(s21_copy_constructor.end(), temp);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.erase(std_copy_constructor.begin());
  s21_copy_constructor.erase(s21_copy_constructor.begin());
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_pos = std_copy_constructor.begin();
  ++std_pos;
  std_copy_constructor.erase(std_pos);
  s21_pos = s21_copy_constructor.begin();
  ++s21_pos;
  s21_copy_constructor.erase(s21_pos);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_pos = std_copy_constructor.end();
  --std_pos;
  std_copy_constructor.erase(std_pos);
  s21_pos = s21_copy_constructor.end();
  --s21_pos;
  s21_copy_constructor.erase(s21_pos);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.clear();
  s21_copy_constructor.clear();
  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.push_back(temp);
    s21_copy_constructor.push_back(temp);
    EXPECT_TRUE(
        ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));
  }
  std_copy_constructor.shrink_to_fit();
  s21_copy_constructor.shrink_to_fit();
  std_copy_constructor.push_back(temp);
  s21_copy_constructor.push_back(temp);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.pop_back();
  s21_copy_constructor.pop_back();
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.pop_back();
  s21_copy_constructor.pop_back();
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualVectors(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualVectors(&std_move_constructor, &s21_move_constructor));
}

TEST(TestS21Containers, Vector) {
  TestVector<char>({0, 1, 0, 4, 127});
  TestVector<int>({0, 1, -2147483647, 4, 2147483647});
  TestVector<double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
  TestVector<A>({A(""), A("one"), A("two"), A("three"), A("four")});
}
