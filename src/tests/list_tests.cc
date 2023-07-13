#include "./tests.h"

template <class T>
void CoutLists(const std::list<T> *std_list, const s21::List<T> *s21_list) {
  for (auto std_iter = std_list->begin(), end = std_list->end();
       std_iter != end; ++std_iter)
    std::cout << *std_iter << " ";
  std::cout << "\n";

  for (auto s21_iter = s21_list->begin(), end = s21_list->end();
       s21_iter != end; ++s21_iter)
    std::cout << *s21_iter << " ";
  std::cout << "\n";
}

template <class T>
void test_list(std::initializer_list<T> const &items) {
  T temp;
  //---------------------------------------------------------------------------

  std::list<T> std_default_constructor;
  s21::List<T> s21_default_constructor;
  EXPECT_TRUE(
      ExpectEqualLists(&std_default_constructor, &s21_default_constructor));

  std::list<T> const std_const_default_constructor;
  s21::List<T> const s21_const_default_constructor;
  EXPECT_TRUE(ExpectEqualLists(&std_const_default_constructor,
                               &s21_const_default_constructor));

  //---------------------------------------------------------------------------

  std::list<T> std_parameterized_constructor(100);
  s21::List<T> s21_parameterized_constructor(100);
  EXPECT_TRUE(ExpectEqualLists(&std_parameterized_constructor,
                               &s21_parameterized_constructor));

  {
    EXPECT_THROW(s21::List<T> s21_parameterized_constructor(
                     s21_parameterized_constructor.max_size() + 1),
                 std::length_error);
    try {
      s21::List<T> s21_parameterized_constructor(
          s21_parameterized_constructor.max_size() + 1);
    } catch (const std::length_error &e) {
      EXPECT_STREQ(
          "Incorrect input, cannot create s21::List larger than max_size()",
          e.what());
    }
  }

  std::list<T> const std_const_parameterized_constructor(100);
  s21::List<T> const s21_const_parameterized_constructor(100);
  EXPECT_TRUE(ExpectEqualLists(&std_const_parameterized_constructor,
                               &s21_const_parameterized_constructor));

  //---------------------------------------------------------------------------

  std::list<T> std_initializer_list_constructor(items);
  s21::List<T> s21_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));

  std::list<T> const std_const_initializer_list_constructor(items);
  s21::List<T> const s21_const_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualLists(&std_const_initializer_list_constructor,
                               &s21_const_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std::list<T> std_copy_constructor(std_initializer_list_constructor);
  s21::List<T> s21_copy_constructor(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std::list<T> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  s21::List<T> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_const_initializer_list_constructor,
                               &s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_const_copy_constructor,
                               &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  std::list<T> std_move_constructor(
      std::move(std_initializer_list_constructor));
  s21::List<T> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_move_constructor, &s21_move_constructor));

  std::list<T> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  s21::List<T> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_const_initializer_list_constructor,
                               &s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_const_move_constructor,
                               &s21_const_move_constructor));

  //---------------------------------------------------------------------------

  std::list<T> std_operator_overload = std::move(std_move_constructor);
  s21::List<T> s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_operator_overload, &s21_operator_overload));
  EXPECT_TRUE(ExpectEqualLists(&std_move_constructor, &s21_move_constructor));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_TRUE(ExpectEqualLists(&std_operator_overload, &s21_operator_overload));

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

  temp = *std_copy_constructor.begin();
  *std_copy_constructor.begin() = temp;
  temp = *s21_copy_constructor.begin();
  *s21_copy_constructor.begin() = temp;
  EXPECT_TRUE(
      ExpectNotEqualListBeginEnd(&std_copy_constructor, &s21_copy_constructor));

  temp = *std_const_copy_constructor.begin();
  temp = *s21_const_copy_constructor.begin();
  EXPECT_TRUE(ExpectNotEqualListBeginEnd(&std_const_copy_constructor,
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

  std_copy_constructor.clear();
  s21_copy_constructor.clear();
  EXPECT_TRUE(
      ExpectEqualListBeginEnd(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  {
    auto item = items.end();
    temp = *(--item);
  }
  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.insert(std_copy_constructor.begin(), temp);
    auto begin =
        s21_copy_constructor.insert(s21_copy_constructor.begin(), temp);
    EXPECT_TRUE(begin == s21_copy_constructor.begin());
    EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));
  }

  auto std_pos = std_copy_constructor.begin();
  ++std_pos;
  std_copy_constructor.insert(std_pos, temp);
  auto s21_pos = s21_copy_constructor.begin();
  ++s21_pos;
  s21_copy_constructor.insert(s21_pos, temp);
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.insert(std_copy_constructor.begin(), temp);
  s21_copy_constructor.insert(s21_copy_constructor.begin(), temp);
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.insert(std_copy_constructor.end(), temp);
  s21_copy_constructor.insert(s21_copy_constructor.end(), temp);
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.insert(std_copy_constructor.end(), temp);
  s21_copy_constructor.insert(s21_copy_constructor.end(), temp);
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.erase(std_copy_constructor.begin());
  s21_copy_constructor.erace(s21_copy_constructor.begin());
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std_pos = std_copy_constructor.begin();
  ++std_pos;
  std_copy_constructor.erase(std_pos);
  s21_pos = s21_copy_constructor.begin();
  ++s21_pos;
  s21_copy_constructor.erace(s21_pos);
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std_pos = std_copy_constructor.end();
  --std_pos;
  std_copy_constructor.erase(std_pos);
  s21_pos = s21_copy_constructor.end();
  --s21_pos;
  s21_copy_constructor.erace(s21_pos);
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.clear();
  s21_copy_constructor.clear();
  for (auto i = 0; i < 21; i++) {
    std_copy_constructor.push_back(temp);
    s21_copy_constructor.push_back(temp);
    EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));
  }

  std_copy_constructor.push_front(temp);
  s21_copy_constructor.push_front(temp);
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.pop_back();
  s21_copy_constructor.pop_back();
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.pop_front();
  s21_copy_constructor.pop_front();
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_move_constructor, &s21_move_constructor));

  //---------------------------------------------------------------------------

  std_initializer_list_constructor = std::list<T>(items);
  s21_initializer_list_constructor = s21::List<T>(items);
  std_initializer_list_constructor.reverse();
  s21_initializer_list_constructor.reverse();
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));

  std_initializer_list_constructor.push_front(temp);
  s21_initializer_list_constructor.push_front(temp);
  std_initializer_list_constructor.reverse();
  s21_initializer_list_constructor.reverse();
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std_initializer_list_constructor.push_front(temp);
  s21_initializer_list_constructor.push_front(temp);
  std_initializer_list_constructor.push_front(temp);
  s21_initializer_list_constructor.push_front(temp);
  std_initializer_list_constructor.unique();
  s21_initializer_list_constructor.unique();
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std_initializer_list_constructor.sort();
  s21_initializer_list_constructor.sort();
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));

  //---------------------------------------------------------------------------
  std_copy_constructor = std::list<T>(std_move_constructor);
  s21_copy_constructor = s21::List<T>(s21_move_constructor);
  std_initializer_list_constructor.merge(std_move_constructor);
  s21_initializer_list_constructor.merge(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_move_constructor, &s21_move_constructor));

  std_initializer_list_constructor.merge(std_move_constructor);
  s21_initializer_list_constructor.merge(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_move_constructor, &s21_move_constructor));

  std_initializer_list_constructor.merge(std_initializer_list_constructor);
  s21_initializer_list_constructor.merge(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std_pos = std_initializer_list_constructor.begin();
  ++std_pos;
  std_initializer_list_constructor.splice(std_pos, std_copy_constructor);
  s21_pos = s21_initializer_list_constructor.begin();
  ++s21_pos;
  s21_initializer_list_constructor.splice(s21_pos, s21_copy_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std_initializer_list_constructor.splice(
      std_initializer_list_constructor.begin(), std_copy_constructor);
  s21_initializer_list_constructor.splice(
      s21_initializer_list_constructor.begin(), s21_copy_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor = std::list<T>(std_initializer_list_constructor);
  s21_copy_constructor = s21::List<T>(s21_initializer_list_constructor);
  std_initializer_list_constructor.splice(
      std_initializer_list_constructor.begin(), std_copy_constructor);
  s21_initializer_list_constructor.splice(
      s21_initializer_list_constructor.begin(), s21_copy_constructor);
  EXPECT_TRUE(ExpectEqualLists(&std_initializer_list_constructor,
                               &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualLists(&std_copy_constructor, &s21_copy_constructor));
}

TEST(TestS21Containers, List) {
  test_list<char>({0, 1, 0, 4, 127});
  test_list<int>({0, 1, -2147483647, 4, 2147483647});
  test_list<double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
  test_list<A>({A(""), A("one"), A("two"), A("three"), A("four")});
}
