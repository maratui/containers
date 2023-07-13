#include "./tests.h"

template <class T>
void test_queue(std::initializer_list<T> const &items) {
  T temp;
  //---------------------------------------------------------------------------

  std::queue<T> std_default_constructor;
  s21::Queue<T> s21_default_constructor;
  EXPECT_TRUE(
      ExpectEqualQueues(&std_default_constructor, &s21_default_constructor));

  std::queue<T> const std_const_default_constructor;
  s21::Queue<T> const s21_const_default_constructor;
  EXPECT_TRUE(ExpectEqualQueues(&std_const_default_constructor,
                                &s21_const_default_constructor));

  //---------------------------------------------------------------------------

  std::queue<T> std_initializer_queue_constructor(items);
  s21::Queue<T> s21_initializer_queue_constructor(items);
  EXPECT_TRUE(ExpectEqualQueues(&std_initializer_queue_constructor,
                                &s21_initializer_queue_constructor));

  std::queue<T> const std_const_initializer_queue_constructor(items);
  s21::Queue<T> const s21_const_initializer_queue_constructor(items);
  EXPECT_TRUE(ExpectEqualQueues(&std_const_initializer_queue_constructor,
                                &s21_const_initializer_queue_constructor));

  //---------------------------------------------------------------------------

  std::queue<T> std_copy_constructor(std_initializer_queue_constructor);
  s21::Queue<T> s21_copy_constructor(s21_initializer_queue_constructor);
  EXPECT_TRUE(ExpectEqualQueues(&std_initializer_queue_constructor,
                                &s21_initializer_queue_constructor));
  EXPECT_TRUE(ExpectEqualQueues(&std_copy_constructor, &s21_copy_constructor));

  std::queue<T> const std_const_copy_constructor(
      std_const_initializer_queue_constructor);
  s21::Queue<T> const s21_const_copy_constructor(
      s21_const_initializer_queue_constructor);
  EXPECT_TRUE(ExpectEqualQueues(&std_const_initializer_queue_constructor,
                                &s21_const_initializer_queue_constructor));
  EXPECT_TRUE(ExpectEqualQueues(&std_const_copy_constructor,
                                &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  std::queue<T> std_move_constructor(
      std::move(std_initializer_queue_constructor));
  s21::Queue<T> s21_move_constructor(
      std::move(s21_initializer_queue_constructor));
  EXPECT_TRUE(ExpectEqualQueues(&std_initializer_queue_constructor,
                                &s21_initializer_queue_constructor));
  EXPECT_TRUE(ExpectEqualQueues(&std_move_constructor, &s21_move_constructor));

  std::queue<T> const std_const_move_constructor(
      std::move(std_const_initializer_queue_constructor));
  s21::Queue<T> const s21_const_move_constructor(
      std::move(s21_const_initializer_queue_constructor));
  EXPECT_TRUE(ExpectEqualQueues(&std_const_initializer_queue_constructor,
                                &s21_const_initializer_queue_constructor));
  EXPECT_TRUE(ExpectEqualQueues(&std_const_move_constructor,
                                &s21_const_move_constructor));

  //---------------------------------------------------------------------------

  std::queue<T> std_operator_overload = std::move(std_move_constructor);
  s21::Queue<T> s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_TRUE(
      ExpectEqualQueues(&std_operator_overload, &s21_operator_overload));
  EXPECT_TRUE(ExpectEqualQueues(&std_move_constructor, &s21_move_constructor));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_TRUE(
      ExpectEqualQueues(&std_operator_overload, &s21_operator_overload));

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
    EXPECT_TRUE(
        ExpectEqualQueues(&std_copy_constructor, &s21_copy_constructor));
  } while (!std_copy_constructor.empty() || !s21_copy_constructor.empty());
  s21_copy_constructor.pop();
  EXPECT_TRUE(ExpectEqualQueues(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(std_copy_constructor.empty());
  EXPECT_TRUE(s21_copy_constructor.empty());

  //---------------------------------------------------------------------------
  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.push(temp);
    s21_copy_constructor.push(temp);
    EXPECT_TRUE(
        ExpectEqualQueues(&std_copy_constructor, &s21_copy_constructor));
  }

  //---------------------------------------------------------------------------

  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualQueues(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualQueues(&std_move_constructor, &s21_move_constructor));

  //---------------------------------------------------------------------------
}

TEST(TestS21Containers, Queue) {
  test_queue<char>({0, 1, 0, 4, 127});
  test_queue<int>({0, 1, -2147483647, 4, 2147483647});
  test_queue<double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
  test_queue<A>({A(""), A("one"), A("two"), A("three"), A("four")});
}
