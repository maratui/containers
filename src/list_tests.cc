#include <gtest/gtest.h>

#include <list>
#include <type_traits>

#include "./s21_containers.h"

template <class T>
void CoutLists(const std::list<T> *std_list, const S21::List<T> *s21_list) {
  for (auto std_iter = std_list->begin(), end = std_list->end();
       std_iter != end; ++std_iter)
    std::cout << *std_iter << " ";
  std::cout << "\n";

  for (auto s21_iter = s21_list->Begin(), end = s21_list->End();
       s21_iter != end; ++s21_iter)
    std::cout << *s21_iter << " ";
  std::cout << "\n";
}

template <class T>
void ExpectEqualLists(const std::list<T> *std_list,
                      const S21::List<T> *s21_list) {
  EXPECT_EQ(std_list->size(), s21_list->Size());

  auto s21_iter = s21_list->Begin();
  for (auto std_iter = std_list->begin(), end = std_list->end();
       std_iter != end; ++std_iter, ++s21_iter)
    EXPECT_EQ(*std_iter, *s21_iter);

  auto std_iter = std_list->begin();
  for (auto s21_iter = s21_list->Begin(), end = s21_list->End();
       s21_iter != end; ++std_iter, ++s21_iter)
    EXPECT_EQ(*std_iter, *s21_iter);
}

template <class T>
void ExpectEqualBeginEnd(const std::list<T> *std_list,
                         const S21::List<T> *s21_list) {
  EXPECT_TRUE(std_list->begin() == std_list->end());
  EXPECT_TRUE(s21_list->Begin() == s21_list->End());
}

template <class T>
void ExpectNotEqualBeginEnd(const std::list<T> *std_list,
                            const S21::List<T> *s21_list) {
  EXPECT_TRUE(std_list->begin() != std_list->end());
  EXPECT_TRUE(s21_list->Begin() != s21_list->End());
}

template <class T>
void test_list(std::initializer_list<T> const &items) {
  T temp;
  //---------------------------------------------------------------------------

  std::list<T> std_default_constructor;
  S21::List<T> s21_default_constructor;
  ExpectEqualLists(&std_default_constructor, &s21_default_constructor);
  ExpectEqualBeginEnd(&std_default_constructor, &s21_default_constructor);
  //  EXPECT_EQ(sizeof(std_default_constructor),
  //  sizeof(s21_default_constructor));

  std::list<T> const std_const_default_constructor;
  S21::List<T> const s21_const_default_constructor;
  ExpectEqualLists(&std_const_default_constructor,
                   &s21_const_default_constructor);
  ExpectEqualBeginEnd(&std_const_default_constructor,
                      &s21_const_default_constructor);

  //---------------------------------------------------------------------------

  std::list<T> std_parameterized_constructor(100);
  S21::List<T> s21_parameterized_constructor(100);
  ExpectEqualLists(&std_parameterized_constructor,
                   &s21_parameterized_constructor);
  ExpectNotEqualBeginEnd(&std_parameterized_constructor,
                         &s21_parameterized_constructor);

  std::list<T> const std_const_parameterized_constructor(100);
  S21::List<T> const s21_const_parameterized_constructor(100);
  ExpectEqualLists(&std_const_parameterized_constructor,
                   &s21_const_parameterized_constructor);
  ExpectNotEqualBeginEnd(&std_const_parameterized_constructor,
                         &s21_const_parameterized_constructor);

  //---------------------------------------------------------------------------

  std::list<T> std_initializer_list_constructor(items);
  S21::List<T> s21_initializer_list_constructor(items);
  ExpectEqualLists(&std_initializer_list_constructor,
                   &s21_initializer_list_constructor);

  std::list<T> const std_const_initializer_list_constructor(items);
  S21::List<T> const s21_const_initializer_list_constructor(items);
  ExpectEqualLists(&std_const_initializer_list_constructor,
                   &s21_const_initializer_list_constructor);

  //---------------------------------------------------------------------------

  std::list<T> std_copy_constructor(std_initializer_list_constructor);
  S21::List<T> s21_copy_constructor(s21_initializer_list_constructor);
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  std::list<T> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  S21::List<T> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  ExpectEqualLists(&std_const_copy_constructor, &s21_const_copy_constructor);

  //---------------------------------------------------------------------------

  std::list<T> std_move_constructor(
      std::move(std_initializer_list_constructor));
  S21::List<T> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  ExpectEqualLists(&std_move_constructor, &s21_move_constructor);
  ExpectEqualLists(&std_initializer_list_constructor,
                   &s21_initializer_list_constructor);
  ExpectEqualBeginEnd(&std_initializer_list_constructor,
                      &s21_initializer_list_constructor);

  std::list<T> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  S21::List<T> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  ExpectEqualLists(&std_const_move_constructor, &s21_const_move_constructor);
  ExpectEqualLists(&std_const_initializer_list_constructor,
                   &s21_const_initializer_list_constructor);
  ExpectNotEqualBeginEnd(&std_const_initializer_list_constructor,
                         &s21_const_initializer_list_constructor);

  EXPECT_EQ(5, std_const_initializer_list_constructor.size());
  EXPECT_EQ(5, s21_const_initializer_list_constructor.Size());

  //---------------------------------------------------------------------------

  std::list<T> std_operator_overload;
  S21::List<T> s21_operator_overload;
  std_operator_overload = std_move_constructor;
  s21_operator_overload = s21_move_constructor;
  ExpectEqualLists(&std_operator_overload, &s21_operator_overload);
  EXPECT_NO_THROW(std_operator_overload = std_const_move_constructor);
  EXPECT_NO_THROW(s21_operator_overload = s21_const_move_constructor);

  std_operator_overload = std::move(std_move_constructor);
  s21_operator_overload = std::move(s21_move_constructor);
  ExpectEqualLists(&std_operator_overload, &s21_operator_overload);
  ExpectEqualLists(&std_move_constructor, &s21_move_constructor);
  ExpectEqualBeginEnd(&std_move_constructor, &s21_move_constructor);

  std_operator_overload = std::move(std_const_move_constructor);
  s21_operator_overload = std::move(s21_const_move_constructor);
  ExpectEqualLists(&std_operator_overload, &s21_operator_overload);
  ExpectEqualLists(&std_const_move_constructor, &s21_const_move_constructor);
  ExpectNotEqualBeginEnd(&std_const_move_constructor,
                         &s21_const_move_constructor);

  EXPECT_EQ(5, std_const_move_constructor.size());
  EXPECT_EQ(5, s21_const_move_constructor.Size());

  s21_operator_overload = s21_operator_overload;
  ExpectEqualLists(&std_operator_overload, &s21_operator_overload);

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  ExpectEqualLists(&std_operator_overload, &s21_operator_overload);
  ExpectEqualBeginEnd(&std_operator_overload, &s21_operator_overload);

  EXPECT_EQ(0, std_operator_overload.size());
  EXPECT_EQ(0, s21_operator_overload.Size());

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.front();
  std_copy_constructor.front() = temp;
  temp = s21_copy_constructor.Front();
  s21_copy_constructor.Front() = temp;
  EXPECT_EQ(std_copy_constructor.front(), s21_copy_constructor.Front());

  temp = std_const_copy_constructor.front();
  temp = s21_const_copy_constructor.Front();
  EXPECT_EQ(std_const_copy_constructor.front(),
            s21_const_copy_constructor.Front());

  //---------------------------------------------------------------------------

  temp = std_copy_constructor.back();
  std_copy_constructor.back() = temp;
  temp = s21_copy_constructor.Back();
  s21_copy_constructor.Back() = temp;
  EXPECT_EQ(std_copy_constructor.back(), s21_copy_constructor.Back());

  temp = std_const_copy_constructor.back();
  temp = s21_const_copy_constructor.Back();
  EXPECT_EQ(std_const_copy_constructor.back(),
            s21_const_copy_constructor.Back());

  //---------------------------------------------------------------------------

  temp = *std_copy_constructor.begin();
  *std_copy_constructor.begin() = temp;
  temp = *s21_copy_constructor.Begin();
  *s21_copy_constructor.Begin() = temp;
  temp = *std_copy_constructor.end();
  *std_copy_constructor.end() = temp;
  temp = *s21_copy_constructor.End();
  *s21_copy_constructor.End() = temp;
  EXPECT_EQ(*std_copy_constructor.begin(), *s21_copy_constructor.Begin());
  EXPECT_EQ(*--std_copy_constructor.end(), *--s21_copy_constructor.End());

  temp = *std_const_copy_constructor.begin();
  temp = *s21_const_copy_constructor.Begin();
  temp = *std_const_copy_constructor.end();
  temp = *s21_const_copy_constructor.End();
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.Begin());
  EXPECT_EQ(*--std_const_copy_constructor.end(),
            *--s21_const_copy_constructor.End());

  //---------------------------------------------------------------------------

  EXPECT_FALSE(std_copy_constructor.empty());
  EXPECT_FALSE(s21_copy_constructor.Empty());
  EXPECT_FALSE(std_const_copy_constructor.empty());
  EXPECT_FALSE(s21_const_copy_constructor.Empty());
  EXPECT_TRUE(std_move_constructor.empty());
  EXPECT_TRUE(s21_move_constructor.Empty());

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_const_copy_constructor.size(),
            s21_const_copy_constructor.Size());
  EXPECT_EQ(std_move_constructor.size(), s21_move_constructor.Size());

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_copy_constructor.max_size(), s21_copy_constructor.MaxSize());
  EXPECT_EQ(std_const_copy_constructor.max_size(),
            s21_const_copy_constructor.MaxSize());

  //---------------------------------------------------------------------------

  std_copy_constructor.clear();
  s21_copy_constructor.Clear();
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);
  ExpectEqualBeginEnd(&std_copy_constructor, &s21_copy_constructor);

  EXPECT_EQ(0, s21_copy_constructor.Size());

  //---------------------------------------------------------------------------

  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.insert(std_copy_constructor.begin(), i + 1);
    auto begin =
        s21_copy_constructor.Insert(s21_copy_constructor.Begin(), i + 1);
    EXPECT_TRUE(begin == s21_copy_constructor.Begin());
    ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);
  }

  std_copy_constructor.insert(++ ++ ++ ++ ++std_copy_constructor.begin(), 105);
  s21_copy_constructor.Insert(++ ++ ++ ++ ++s21_copy_constructor.Begin(), 105);
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  std_copy_constructor.insert(std_copy_constructor.begin(), 101);
  s21_copy_constructor.Insert(s21_copy_constructor.Begin(), 101);
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  std_copy_constructor.insert(std_copy_constructor.end(), 111);
  s21_copy_constructor.Insert(s21_copy_constructor.End(), 111);
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  std_copy_constructor.insert(std_copy_constructor.end(), 222);
  s21_copy_constructor.Insert(s21_copy_constructor.End(), 222);
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  //---------------------------------------------------------------------------

  std_copy_constructor.erase(std_copy_constructor.begin());
  s21_copy_constructor.Erase(s21_copy_constructor.Begin());
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  std_copy_constructor.erase(++ ++ ++ ++ ++std_copy_constructor.begin());
  s21_copy_constructor.Erase(++ ++ ++ ++ ++s21_copy_constructor.Begin());
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  std_copy_constructor.erase(--std_copy_constructor.end());
  s21_copy_constructor.Erase(--s21_copy_constructor.End());
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  //---------------------------------------------------------------------------

  std_copy_constructor.clear();
  s21_copy_constructor.Clear();
  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.push_back(i + 1);
    s21_copy_constructor.PushBack(i + 1);
    ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);
  }

  std_copy_constructor.push_front(222);
  s21_copy_constructor.PushFront(222);
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  //---------------------------------------------------------------------------

  std_copy_constructor.pop_back();
  s21_copy_constructor.PopBack();
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  std_copy_constructor.pop_front();
  s21_copy_constructor.PopFront();
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);

  //---------------------------------------------------------------------------

  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.Swap(s21_move_constructor);
  ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor);
  ExpectEqualLists(&std_move_constructor, &s21_move_constructor);

  //---------------------------------------------------------------------------

  std_initializer_list_constructor = std::list<T>(items);
  s21_initializer_list_constructor = S21::List<T>(items);
  std_initializer_list_constructor.reverse();
  s21_initializer_list_constructor.reverse();
  ExpectEqualLists(&std_initializer_list_constructor,
                   &s21_initializer_list_constructor);

  std_initializer_list_constructor.push_front(222);
  s21_initializer_list_constructor.PushFront(222);
  std_initializer_list_constructor.reverse();
  s21_initializer_list_constructor.reverse();
  ExpectEqualLists(&std_initializer_list_constructor,
                   &s21_initializer_list_constructor);

  //---------------------------------------------------------------------------

  std_initializer_list_constructor.push_front(222);
  s21_initializer_list_constructor.PushFront(222);
  std_initializer_list_constructor.push_front(222);
  s21_initializer_list_constructor.PushFront(222);
  std_initializer_list_constructor.unique();
  s21_initializer_list_constructor.Unique();
  ExpectEqualLists(&std_initializer_list_constructor,
                   &s21_initializer_list_constructor);

  //---------------------------------------------------------------------------

  std_initializer_list_constructor.sort();
  s21_initializer_list_constructor.Sort();
  ExpectEqualLists(&std_initializer_list_constructor,
                   &s21_initializer_list_constructor);
}

TEST(TestS21Containers, List) {
  // test_list<bool>({0, 1, 0, 1, 1});
  // test_list<signed char>({0, 1, -128, 4, 127});
  // test_list<unsigned char>({0, 1, 0, 4, 255});
  // test_list<char>({0, 1, 0, 4, 127});
  // test_list<short>({0, 1, -32768, 4, 32767});
  // test_list<unsigned short>({0, 1, 0, 4, 65535});
  test_list<int>({0, 1, -2147483648, 4, 2147483647});
  // test_list<unsigned int>({0, 1, 0, 4, 4294967295});
  // test_list<long>({0, 1, -2147483648, 4, 2147483647});
  // test_list<unsigned long>({0, 1, 0, 4, 4294967295});
  // test_list<long long>({0, 1, -2147483648, 4, 2147483647});
  // test_list<unsigned long long>({0, 1, 0, 4, 4294967295});
  // test_list<float>({0, 1, FLT_MIN, -FLT_MAX, FLT_MAX});
  // test_list<double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
  // test_list<long double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
}
