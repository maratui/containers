#include "./tests.h"

template <class T, std::size_t N>
void CoutArrays(const std::array<T, N> *std_array,
                const s21::array<T, N> *s21_array) {
  for (auto std_iter = std_array->begin(), end = std_array->end();
       std_iter != end; ++std_iter)
    std::cout << (*std_iter).s << " ";
  std::cout << "\n";

  for (auto s21_iter = s21_array->begin(), end = s21_array->end();
       s21_iter != end; ++s21_iter)
    std::cout << (*s21_iter).s << " ";
  std::cout << "\n";
}

template <class T, class... Args>
void test_array(Args... args) {
  std::initializer_list<T> const &items = {(T)args...};
  T temp;
  //---------------------------------------------------------------------------

  std::array<T, 5> std_default_constructor;
  s21::array<T, 5> s21_default_constructor;
  EXPECT_TRUE(ExpectNotEqualArrayBeginEnd(&std_default_constructor,
                                          &s21_default_constructor));
  {
    std::array<T, std_default_constructor.max_size()> std_default_constructor;
    s21::array<T, s21_default_constructor.max_size()> s21_default_constructor;
    EXPECT_TRUE(ExpectNotEqualArrayBeginEnd(&std_default_constructor,
                                            &s21_default_constructor));
  }

  std::array<T, 0> const std_const_default_constructor;
  s21::array<T, 0> const s21_const_default_constructor;
  EXPECT_TRUE(ExpectEqualArrayBeginEnd(&std_const_default_constructor,
                                       &s21_const_default_constructor));

  //---------------------------------------------------------------------------

  std::array<T, 10> std_initializer_list_constructor{(T)args...};
  s21::array<T, 10> s21_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualArrays(&std_initializer_list_constructor,
                                &s21_initializer_list_constructor));
  {
    T init_args[5]{(T)args...};
    std::array<T, 3> std_initializer_list_constructor{
        init_args[0], init_args[1], init_args[2]};
    s21::array<T, 3> s21_initializer_list_constructor(items);
    EXPECT_TRUE(ExpectEqualArrays(&std_initializer_list_constructor,
                                  &s21_initializer_list_constructor));
  }

  std::array<T, 10> const std_const_initializer_list_constructor{(T)args...};
  s21::array<T, 10> const s21_const_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualArrays(&std_const_initializer_list_constructor,
                                &s21_const_initializer_list_constructor));
  {
    T init_args[5]{(T)args...};
    std::array<T, 3> const std_const_initializer_list_constructor{
        init_args[0], init_args[1], init_args[2]};
    s21::array<T, 3> const s21_const_initializer_list_constructor(items);
    EXPECT_TRUE(ExpectEqualArrays(&std_const_initializer_list_constructor,
                                  &s21_const_initializer_list_constructor));
  }

  //---------------------------------------------------------------------------

  std::array<T, 10> std_copy_constructor(std_initializer_list_constructor);
  s21::array<T, 10> s21_copy_constructor(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualArrays(&std_initializer_list_constructor,
                                &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualArrays(&std_copy_constructor, &s21_copy_constructor));

  std::array<T, 10> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  s21::array<T, 10> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualArrays(&std_const_initializer_list_constructor,
                                &s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualArrays(&std_const_copy_constructor,
                                &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  std::array<T, 10> std_move_constructor(
      std::move(std_initializer_list_constructor));
  s21::array<T, 10> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualArrays(&std_move_constructor, &s21_move_constructor));
  EXPECT_TRUE(ExpectEqualArrays(&std_initializer_list_constructor,
                                &s21_initializer_list_constructor));

  std::array<T, 10> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  s21::array<T, 10> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualArrays(&std_const_move_constructor,
                                &s21_const_move_constructor));
  EXPECT_TRUE(ExpectEqualArrays(&std_const_initializer_list_constructor,
                                &s21_const_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std::array<T, 10> std_operator_overload = std::move(std_move_constructor);
  s21::array<T, 10> s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_TRUE(
      ExpectEqualArrays(&std_operator_overload, &s21_operator_overload));
  EXPECT_TRUE(ExpectEqualArrays(&std_move_constructor, &s21_move_constructor));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_TRUE(
      ExpectEqualArrays(&std_operator_overload, &s21_operator_overload));

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.at(3);
  std_copy_constructor.at(3) = temp;
  temp = s21_copy_constructor.at(3);
  s21_copy_constructor.at(3) = temp;
  EXPECT_EQ(std_copy_constructor.at(3), s21_copy_constructor.at(3));
  EXPECT_NO_THROW(std_copy_constructor.at(9));
  EXPECT_NO_THROW(s21_copy_constructor.at(9));
  EXPECT_THROW(std_copy_constructor.at(10), std::out_of_range);
  EXPECT_THROW(s21_copy_constructor.at(10), std::out_of_range);
  try {
    s21_operator_overload.at(10);
  } catch (const std::out_of_range &e) {
    EXPECT_STREQ("Incorrect input, index is outside the array size", e.what());
  }

  temp = std_const_copy_constructor.at(3);
  temp = s21_const_copy_constructor.at(3);
  EXPECT_NO_THROW(std_const_copy_constructor.at(9));
  EXPECT_NO_THROW(s21_const_copy_constructor.at(9));
  EXPECT_THROW(std_const_copy_constructor.at(10), std::out_of_range);
  EXPECT_THROW(s21_const_copy_constructor.at(10), std::out_of_range);
  EXPECT_EQ(std_const_copy_constructor.at(0), s21_const_copy_constructor.at(0));

  //---------------------------------------------------------------------------

  temp = std_copy_constructor[3];
  std_copy_constructor[3] = temp;
  temp = s21_copy_constructor[3];
  s21_copy_constructor[3] = temp;
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    EXPECT_EQ(std_copy_constructor[i], s21_copy_constructor[i]);
  EXPECT_NO_THROW(std_copy_constructor[9]);
  EXPECT_NO_THROW(s21_copy_constructor[9]);
  EXPECT_NO_THROW(std_copy_constructor[10]);
  EXPECT_NO_THROW(s21_copy_constructor[10]);

  temp = std_const_copy_constructor[3];
  temp = s21_const_copy_constructor[3];
  for (size_t i = 0; i < std_copy_constructor.size(); i++)
    EXPECT_EQ(std_const_copy_constructor[i], s21_const_copy_constructor[i]);
  EXPECT_NO_THROW(std_const_copy_constructor[9]);
  EXPECT_NO_THROW(s21_const_copy_constructor[9]);
  EXPECT_NO_THROW(std_const_copy_constructor[10]);
  EXPECT_NO_THROW(s21_const_copy_constructor[10]);

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
  temp = *std_copy_constructor.end();
  *std_copy_constructor.end() = temp;
  temp = *s21_copy_constructor.end();
  *s21_copy_constructor.end() = temp;
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.begin());
  EXPECT_TRUE(ExpectNotEqualArrayBeginEnd(&std_copy_constructor,
                                          &s21_copy_constructor));

  temp = *std_const_copy_constructor.begin();
  temp = *s21_const_copy_constructor.begin();
  temp = *std_const_copy_constructor.end();
  temp = *s21_const_copy_constructor.end();
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.begin());
  EXPECT_TRUE(ExpectNotEqualArrayBeginEnd(&std_const_copy_constructor,
                                          &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  EXPECT_FALSE(std_copy_constructor.empty());
  EXPECT_FALSE(s21_copy_constructor.empty());
  EXPECT_FALSE(std_const_copy_constructor.empty());
  EXPECT_FALSE(s21_const_copy_constructor.empty());
  EXPECT_TRUE(std_const_default_constructor.empty());
  EXPECT_TRUE(s21_const_default_constructor.empty());

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  EXPECT_EQ(std_const_copy_constructor.size(),
            s21_const_copy_constructor.size());
  EXPECT_EQ(std_const_default_constructor.size(),
            s21_const_default_constructor.size());

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_copy_constructor.max_size(), s21_copy_constructor.max_size());
  EXPECT_EQ(std_const_copy_constructor.max_size(),
            s21_const_copy_constructor.max_size());

  //---------------------------------------------------------------------------

  std_move_constructor.fill(*(items.begin()));
  s21_move_constructor.fill(*(items.begin()));
  EXPECT_TRUE(ExpectEqualArrays(&std_move_constructor, &s21_move_constructor));
  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualArrays(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualArrays(&std_move_constructor, &s21_move_constructor));
}

TEST(TestS21Containers, Array) {
  test_array<char>(0, 1, 0, 4, 127);
  test_array<int>(0, 1, -2147483647, 4, 2147483647);
  test_array<double>(0, 1, DBL_MIN, -DBL_MAX, DBL_MAX);
  test_array<A>(A(""), A("one"), A("two"), A("three"), A("four"));
}
