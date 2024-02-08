#include "./tests.h"

template <class Key>
void CoutMaps(const std::set<Key> *std_set, const s21::set<Key> *s21_set) {
  for (auto std_iter = std_set->begin(), end = std_set->end(); std_iter != end;
       ++std_iter)
    std::cout << (*std_iter).first << " " << (*std_iter).second << " ";
  std::cout << "\n";

  for (auto s21_iter = s21_set->begin(), end = s21_set->end(); s21_iter != end;
       ++s21_iter)
    std::cout << (*s21_iter).first << " " << (*s21_iter).second << " ";
  std::cout << "\n";
}

template <class Key, class... Args>
void TestSet(Args... args) {
  std::initializer_list<Key> const &items = {(Key)args...};
  //---------------------------------------------------------------------------

  std::set<Key> std_default_constructor;
  s21::set<Key> s21_default_constructor;
  EXPECT_TRUE(ExpectEqualSetBeginEnd(&std_default_constructor,
                                     &s21_default_constructor));

  std::set<Key> const std_const_default_constructor;
  s21::set<Key> const s21_const_default_constructor;
  EXPECT_TRUE(ExpectEqualSetBeginEnd(&std_const_default_constructor,
                                     &s21_const_default_constructor));

  //---------------------------------------------------------------------------

  std::set<Key> std_initializer_list_constructor(items);
  s21::set<Key> s21_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualSets(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));

  std::set<Key> const std_const_initializer_list_constructor(items);
  s21::set<Key> const s21_const_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualSets(&std_const_initializer_list_constructor,
                              &s21_const_initializer_list_constructor));

  auto std_const_prev_iter = std_const_initializer_list_constructor.end();
  auto s21_const_prev_iter = s21_const_initializer_list_constructor.end();
  --std_const_prev_iter;
  --s21_const_prev_iter;
  EXPECT_EQ(*std_const_prev_iter, *s21_const_prev_iter);
  --std_const_prev_iter;
  --s21_const_prev_iter;
  EXPECT_EQ(*std_const_prev_iter, *s21_const_prev_iter);

  //---------------------------------------------------------------------------

  std::set<Key> std_copy_constructor(std_initializer_list_constructor);
  s21::set<Key> s21_copy_constructor(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualSets(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  std::set<Key> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  s21::set<Key> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualSets(&std_const_initializer_list_constructor,
                              &s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_const_copy_constructor,
                              &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  std::set<Key> std_move_constructor(
      std::move(std_initializer_list_constructor));
  s21::set<Key> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_move_constructor, &s21_move_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));

  std::set<Key> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  s21::set<Key> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_const_move_constructor,
                              &s21_const_move_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_const_initializer_list_constructor,
                              &s21_const_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std_default_constructor = std_move_constructor;
  s21_default_constructor = s21_move_constructor;
  EXPECT_TRUE(
      ExpectEqualSets(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_move_constructor, &s21_move_constructor));

  std_default_constructor = std_const_move_constructor;
  s21_default_constructor = s21_const_move_constructor;
  EXPECT_TRUE(
      ExpectEqualSets(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_const_move_constructor,
                              &s21_const_move_constructor));

  std::set<Key> std_operator_overload;
  s21::set<Key> s21_operator_overload;
  std_operator_overload = std::move(std_move_constructor);
  s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualSets(&std_operator_overload, &s21_operator_overload));
  EXPECT_TRUE(ExpectEqualSets(&std_move_constructor, &s21_move_constructor));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_TRUE(ExpectEqualSets(&std_operator_overload, &s21_operator_overload));

  //---------------------------------------------------------------------------

  EXPECT_EQ(*std_copy_constructor.begin(), *s21_copy_constructor.begin());
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.begin());
  EXPECT_TRUE(
      ExpectNotEqualSetBeginEnd(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectNotEqualSetBeginEnd(&std_const_copy_constructor,
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

  std_copy_constructor.clear();
  s21_copy_constructor.clear();
  EXPECT_TRUE(
      ExpectEqualSetBeginEnd(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  auto item = items.end();
  --item;

  EXPECT_TRUE((std_copy_constructor.insert(*item)).second);
  EXPECT_TRUE((s21_copy_constructor.insert(*item)).second);
  EXPECT_FALSE((std_copy_constructor.insert(*item)).second);
  EXPECT_FALSE((s21_copy_constructor.insert(*item)).second);
  EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  EXPECT_EQ((std_copy_constructor.insert(*item)).second,
            (s21_copy_constructor.insert(*item)).second);
  EXPECT_EQ(*((std_copy_constructor.insert(*item)).first),
            *((s21_copy_constructor.insert(*item)).first));
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  std_default_constructor = std_copy_constructor;
  s21_default_constructor = s21_copy_constructor;
  EXPECT_TRUE(
      ExpectEqualSets(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  std_default_constructor = std_default_constructor;
  s21_default_constructor = s21_default_constructor;
  EXPECT_TRUE(
      ExpectEqualSets(&std_default_constructor, &s21_default_constructor));

  for (auto item = items.begin(); item != items.end(); ++item) {
    std_copy_constructor.insert(*item);
    s21_copy_constructor.insert(*item);
  }
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.erase(std_copy_constructor.begin());
  s21_copy_constructor.erase(s21_copy_constructor.begin());
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  auto std_pos = std_copy_constructor.begin();
  ++std_pos;
  std_copy_constructor.erase(std_pos);
  auto s21_pos = s21_copy_constructor.begin();
  ++s21_pos;
  s21_copy_constructor.erase(s21_pos);
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  std_pos = std_copy_constructor.end();
  --std_pos;
  std_copy_constructor.erase(std_pos);
  std_pos = std_copy_constructor.end();
  --std_pos;
  --std_pos;
  std_copy_constructor.erase(std_pos);
  s21_pos = s21_copy_constructor.end();
  --s21_pos;
  s21_copy_constructor.erase(s21_pos);
  s21_pos = s21_copy_constructor.end();
  --s21_pos;
  --s21_pos;
  s21_copy_constructor.erase(s21_pos);
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  for (; !std_copy_constructor.empty() && !s21_copy_constructor.empty();) {
    ;
    std_pos = std_copy_constructor.begin();
    s21_pos = s21_copy_constructor.begin();
    std_copy_constructor.erase(std_pos);
    s21_copy_constructor.erase(s21_pos);
    EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));
  }
  EXPECT_TRUE(std_copy_constructor.empty());
  EXPECT_TRUE(s21_copy_constructor.empty());

  //---------------------------------------------------------------------------

  for (auto item = items.begin(); item != items.end(); ++item) {
    std_copy_constructor.insert(*item);
    s21_copy_constructor.insert(*item);
  }
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualSets(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_move_constructor, &s21_move_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor = std::set<Key>(std_move_constructor);
  s21_copy_constructor = s21::set<Key>(s21_move_constructor);

  std_initializer_list_constructor.merge(std_move_constructor);
  s21_initializer_list_constructor.merge(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualSets(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_move_constructor, &s21_move_constructor));

  std_initializer_list_constructor.merge(std_move_constructor);
  s21_initializer_list_constructor.merge(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualSets(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualSets(&std_move_constructor, &s21_move_constructor));

  std_initializer_list_constructor.merge(std_initializer_list_constructor);
  s21_initializer_list_constructor.merge(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualSets(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));

  //---------------------------------------------------------------------------

  EXPECT_EQ(*std_copy_constructor.find(*(items.begin())),
            *s21_copy_constructor.find(*(items.begin())));

  //---------------------------------------------------------------------------

  EXPECT_TRUE(s21_copy_constructor.contains(*(items.begin())));

  //---------------------------------------------------------------------------

  {
    using set_t = typename s21::set<Key>::item_type;

    //---------------------------------------------------------------------------

    std::set<Key> std_set;
    s21::set<Key> s21_set;

    std_set.emplace();
    s21_set.insert_many();
    std_set.emplace();
    s21_set.insert_many();
    EXPECT_TRUE(ExpectEqualSets(&std_set, &s21_set));

    std::pair<Key, Key> args[items.size()];
    {
      int i = 0;
      for (auto item : items) {
        args[i].first = item;
        args[i++].second = item;
      }
    }

    for (auto i = 0; i < 3; i++) {
      int j = 5;
      for (Key item : items) {
        std_set.emplace(item);
        if (--j <= 0) break;
      }
      typename set_t::RBTPtrs *ptrs[5];
      for (int i = 0; i < 5; i++) {
        ptrs[i] = new typename set_t::RBTPtrs(nullptr, nullptr, nullptr);
      }
      auto ress = s21_set.insert_many(
          set_t(args[0], s21::Red, ptrs[0]), set_t(args[1], s21::Red, ptrs[1]),
          set_t(args[2], s21::Red, ptrs[2]), set_t(args[3], s21::Red, ptrs[3]),
          set_t(args[4], s21::Red, ptrs[4]));
      EXPECT_TRUE(ExpectEqualSets(&std_set, &s21_set));
      for (auto res : ress) {
        EXPECT_TRUE(s21_set.contains(*(res.first)));
      }
    }

    //---------------------------------------------------------------------------
  }
}

TEST(TestS21Containers, Set) {
  TestSet<char>(0, 1, 2, 3, 4);
  TestSet<int>(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 19, 18, 17, 16, 15, 14, 13, 12,
               11);
  TestSet<int>(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
               19);
  TestSet<double>(0, 1, DBL_MIN, -DBL_MAX, DBL_MAX);
  TestSet<A>(A(""), A("one"), A("two"), A("three"), A("four"));
}
