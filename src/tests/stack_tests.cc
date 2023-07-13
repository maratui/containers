#include "./tests.h"

template <class T>
void test_stack(std::initializer_list<T> const &items) {
  T temp;
  //---------------------------------------------------------------------------

  std::stack<T> std_default_constructor;
  s21::Stack<T> s21_default_constructor;
  EXPECT_TRUE(
      ExpectEqualStacks(std_default_constructor, s21_default_constructor));

  std::stack<T> const std_const_default_constructor;
  s21::Stack<T> const s21_const_default_constructor;
  EXPECT_TRUE(ExpectEqualStacks(std_const_default_constructor,
                                s21_const_default_constructor));

  //---------------------------------------------------------------------------

  std::stack<T> std_initializer_list_constructor(items);
  s21::Stack<T> s21_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualStacks(std_initializer_list_constructor,
                                s21_initializer_list_constructor));

  std::stack<T> const std_const_initializer_list_constructor(items);
  s21::Stack<T> const s21_const_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualStacks(std_const_initializer_list_constructor,
                                s21_const_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std::stack<T> std_copy_constructor(std_initializer_list_constructor);
  s21::Stack<T> s21_copy_constructor(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualStacks(std_initializer_list_constructor,
                                s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualStacks(std_copy_constructor, s21_copy_constructor));

  std::stack<T> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  s21::Stack<T> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualStacks(std_const_initializer_list_constructor,
                                s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualStacks(std_const_copy_constructor,
                                s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  std::stack<T> std_move_constructor(
      std::move(std_initializer_list_constructor));
  s21::Stack<T> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualStacks(std_initializer_list_constructor,
                                s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualStacks(std_move_constructor, s21_move_constructor));

  std::stack<T> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  s21::Stack<T> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualStacks(std_const_initializer_list_constructor,
                                s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualStacks(std_const_move_constructor,
                                s21_const_move_constructor));

  //---------------------------------------------------------------------------

  std::stack<T> std_operator_overload = std::move(std_move_constructor);
  s21::Stack<T> s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualStacks(std_operator_overload, s21_operator_overload));
  EXPECT_TRUE(ExpectEqualStacks(std_move_constructor, s21_move_constructor));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_TRUE(ExpectEqualStacks(std_operator_overload, s21_operator_overload));

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.top();
  std_copy_constructor.top() = temp;
  temp = s21_copy_constructor.top();
  s21_copy_constructor.top() = temp;
  EXPECT_EQ(std_copy_constructor.top(), s21_copy_constructor.top());

  temp = std_const_copy_constructor.top();
  temp = s21_const_copy_constructor.top();
  EXPECT_EQ(std_const_copy_constructor.top(), s21_const_copy_constructor.top());

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

  do {
    std_copy_constructor.pop();
    s21_copy_constructor.pop();
    EXPECT_TRUE(ExpectEqualStacks(std_copy_constructor, s21_copy_constructor));
  } while (!std_copy_constructor.empty() && !s21_copy_constructor.empty());
  s21_copy_constructor.pop();
  EXPECT_TRUE(ExpectEqualStacks(std_copy_constructor, s21_copy_constructor));
  EXPECT_TRUE(std_copy_constructor.empty());
  EXPECT_TRUE(s21_copy_constructor.empty());

  //---------------------------------------------------------------------------

  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.push(temp);
    s21_copy_constructor.push(temp);
    EXPECT_TRUE(ExpectEqualStacks(std_copy_constructor, s21_copy_constructor));
  }

  //---------------------------------------------------------------------------

  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualStacks(std_copy_constructor, s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualStacks(std_move_constructor, s21_move_constructor));

  //---------------------------------------------------------------------------
}

TEST(TestS21Containers, Stack) {
  test_stack<char>({0, 1, 0, 4, 127});
  test_stack<int>({0, 1, -2147483647, 4, 2147483647});
  test_stack<double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
  test_stack<A>({A(""), A("one"), A("two"), A("three"), A("four")});
}
