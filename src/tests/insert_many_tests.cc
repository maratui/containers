#include "./tests.h"

template <class T>
void test_insert_many(std::initializer_list<T> const &items) {
  {
    using vi_t = typename s21::vector<T>::item_type;

    //---------------------------------------------------------------------------

    std::vector<T> std_vector;
    s21::vector<T> s21_vector;

    auto std_ret = std_vector.emplace(std_vector.begin());
    EXPECT_TRUE(std_ret == std_vector.begin());
    auto s21_ret = s21_vector.insert_many(s21_vector.begin());
    EXPECT_TRUE(s21_ret == s21_vector.begin());
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    T args[items.size()];
    {
      int i = 0;
      for (auto item : items) args[i++] = item;
    }

    for (auto i = 0; i < 21; i++) {
      for (auto item : items) {
        std_ret = std_vector.emplace(std_vector.begin(), item);
        EXPECT_TRUE(std_ret == std_vector.begin());
      }
      s21_ret = s21_vector.insert_many(s21_vector.begin(), vi_t(args[0]),
                                       vi_t(args[1]), vi_t(args[2]),
                                       vi_t(args[3]), vi_t(args[4]));
      EXPECT_TRUE(s21_ret == s21_vector.begin());
      EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));
    }

    auto std_pos = std_vector.begin();
    ++std_pos;
    std_vector.emplace(std_pos, args[4]);
    auto s21_pos = s21_vector.begin();
    ++s21_pos;
    s21_vector.insert_many(s21_pos, vi_t(args[4]));
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    std_ret = std_vector.emplace(std_pos);
    EXPECT_TRUE(std_ret == std_pos);
    s21_ret = s21_vector.insert_many(s21_pos);
    EXPECT_TRUE(s21_ret == s21_pos);
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    std_vector.emplace(std_vector.begin(), args[4]);
    s21_vector.insert_many(s21_vector.begin(), vi_t(args[4]));
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    std_vector.emplace(std_vector.end(), args[4]);
    s21_vector.insert_many(s21_vector.end(), vi_t(args[4]));
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    std_vector.shrink_to_fit();
    s21_vector.shrink_to_fit();
    std_vector.emplace(std_vector.end(), args[4]);
    s21_vector.insert_many(s21_vector.end(), vi_t(args[4]));
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    //---------------------------------------------------------------------------

    std_vector.clear();
    s21_vector.clear();
    std_vector.shrink_to_fit();
    s21_vector.shrink_to_fit();

    std_vector.emplace_back();
    s21_vector.insert_many_back();
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    for (auto i = 0; i < 21; i++) {
      for (auto item : items) std_vector.emplace_back(item);
      s21_vector.insert_many_back(vi_t(args[0]), vi_t(args[1]), vi_t(args[2]),
                                  vi_t(args[3]), vi_t(args[4]));
      EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));
    }

    std_vector.emplace_back();
    s21_vector.insert_many_back();
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    std_vector.shrink_to_fit();
    s21_vector.shrink_to_fit();
    std_vector.emplace_back(args[0]);
    s21_vector.insert_many_back(vi_t(args[0]));
    EXPECT_TRUE(ExpectEqualVectors(&std_vector, &s21_vector));

    //---------------------------------------------------------------------------
  }
  {
    using li_t = typename s21::list<T>::item_type;

    //---------------------------------------------------------------------------

    std::list<T> std_list;
    s21::list<T> s21_list;

    auto std_ret = std_list.emplace(std_list.begin());
    EXPECT_TRUE(std_ret == std_list.begin());
    auto s21_ret = s21_list.insert_many(s21_list.begin());
    EXPECT_TRUE(s21_ret == s21_list.begin());
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    T args[items.size()];
    {
      int i = 0;
      for (auto item : items) args[i++] = item;
    }

    for (auto i = 0; i < 21; i++) {
      for (auto item : items) {
        std_ret = std_list.emplace(std_list.begin(), item);
        EXPECT_TRUE(std_ret == std_list.begin());
      }
      s21_ret =
          s21_list.insert_many(s21_list.begin(), li_t(args[0]), li_t(args[1]),
                               li_t(args[2]), li_t(args[3]), li_t(args[4]));
      EXPECT_TRUE(s21_ret == s21_list.begin());
      EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));
    }

    auto std_pos = std_list.begin();
    ++std_pos;
    std_list.emplace(std_pos, args[4]);
    auto s21_pos = s21_list.begin();
    ++s21_pos;
    s21_list.insert_many(s21_pos, li_t(args[4]));
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    std_ret = std_list.emplace(std_pos);
    EXPECT_FALSE(std_ret == std_pos);
    s21_ret = s21_list.insert_many(s21_pos);
    EXPECT_FALSE(s21_ret == s21_pos);
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    std_list.emplace(std_list.begin(), args[4]);
    s21_list.insert_many(s21_list.begin(), li_t(args[4]));
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    std_list.emplace(std_list.end(), args[4]);
    s21_list.insert_many(s21_list.end(), li_t(args[4]));
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    std_list.emplace(std_list.end(), args[4]);
    s21_list.insert_many(s21_list.end(), li_t(args[4]));
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    //---------------------------------------------------------------------------

    std_list.clear();
    s21_list.clear();

    std_list.emplace_back();
    s21_list.insert_many_back();
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    for (auto i = 0; i < 21; i++) {
      for (auto item : items) std_list.emplace_back(item);
      s21_list.insert_many_back(li_t(args[0]), li_t(args[1]), li_t(args[2]),
                                li_t(args[3]), li_t(args[4]));
      EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));
    }

    std_list.emplace_back();
    s21_list.insert_many_back();
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    std_list.emplace_back(args[0]);
    s21_list.insert_many_back(li_t(args[0]));
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    //---------------------------------------------------------------------------

    std_list.clear();
    s21_list.clear();

    std_list.emplace_front();
    s21_list.insert_many_front();
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    for (auto i = 0; i < 21; i++) {
      for (auto item : items) std_list.emplace_front(item);
      s21_list.insert_many_front(li_t(args[0]), li_t(args[1]), li_t(args[2]),
                                 li_t(args[3]), li_t(args[4]));
      EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));
    }

    std_list.emplace_front();
    s21_list.insert_many_front();
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    std_list.emplace_front(args[0]);
    s21_list.insert_many_front(li_t(args[0]));
    EXPECT_TRUE(ExpectEqualLists(&std_list, &s21_list));

    //---------------------------------------------------------------------------
  }
  {
    using qi_t = typename s21::queue<T>::item_type;

    //---------------------------------------------------------------------------

    std::list<T> std_list;
    s21::queue<T> s21_queue;

    T args[items.size()];
    {
      int i = 0;
      for (auto item : items) args[i++] = item;
    }

    //---------------------------------------------------------------------------

    std_list.emplace_back();
    s21_queue.insert_many_back();
    EXPECT_TRUE(ExpectEqualListQueue(&std_list, &s21_queue));

    for (auto i = 0; i < 21; i++) {
      for (auto item : items) std_list.emplace_back(item);
      s21_queue.insert_many_back(qi_t(args[0]), qi_t(args[1]), qi_t(args[2]),
                                 qi_t(args[3]), qi_t(args[4]));
      EXPECT_TRUE(ExpectEqualListQueue(&std_list, &s21_queue));
    }

    std_list.emplace_back();
    s21_queue.insert_many_back();
    EXPECT_TRUE(ExpectEqualListQueue(&std_list, &s21_queue));

    std_list.emplace_back(args[0]);
    s21_queue.insert_many_back(qi_t(args[0]));
    EXPECT_TRUE(ExpectEqualListQueue(&std_list, &s21_queue));

    //---------------------------------------------------------------------------
  }
  {
    using si_t = typename s21::stack<T>::item_type;

    //---------------------------------------------------------------------------

    std::list<T> std_list;
    s21::stack<T> s21_stack;

    T args[items.size()];
    {
      int i = 0;
      for (auto item : items) args[i++] = item;
    }

    //---------------------------------------------------------------------------

    std_list.emplace_front();
    s21_stack.insert_many_front();
    EXPECT_TRUE(ExpectEqualListStack(std_list, s21_stack));

    for (auto i = 0; i < 21; i++) {
      for (auto item : items) std_list.emplace_front(item);
      s21_stack.insert_many_front(si_t(args[0]), si_t(args[1]), si_t(args[2]),
                                  si_t(args[3]), si_t(args[4]));
      EXPECT_TRUE(ExpectEqualListStack(std_list, s21_stack));
    }

    std_list.emplace_front();
    s21_stack.insert_many_front();
    EXPECT_TRUE(ExpectEqualListStack(std_list, s21_stack));

    std_list.emplace_front(args[0]);
    s21_stack.insert_many_front(si_t(args[0]));
    EXPECT_TRUE(ExpectEqualListStack(std_list, s21_stack));

    //---------------------------------------------------------------------------
  }
}

TEST(TestS21Containers, insert_many) {
  test_insert_many<char>({0, 1, 0, 4, 127});
  test_insert_many<int>({0, 1, -2147483647, 4, 2147483647});
  test_insert_many<double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
  test_insert_many<A>({A(""), A("one"), A("two"), A("three"), A("four")});
}
