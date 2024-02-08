#include "./tests.h"

template <class Key>
void CoutMultisets(const std::multiset<Key> *std_multiset,
                   const s21::multiset<Key> *s21_multiset) {
  for (auto std_iter = std_multiset->begin(), end = std_multiset->end();
       std_iter != end; ++std_iter)
    std::cout << (*std_iter) << " ";
  std::cout << "\n";

  for (auto s21_iter = s21_multiset->begin(), end = s21_multiset->end();
       s21_iter != end; ++s21_iter)
    std::cout << (*s21_iter) << " ";
  std::cout << "\n";
}

template <class Key, class... Args>
void TestMultiset(Args... args) {
  std::initializer_list<Key> const &items = {(Key)args...};
  //---------------------------------------------------------------------------

  std::multiset<Key> std_default_constructor;
  s21::multiset<Key> s21_default_constructor;
  EXPECT_TRUE(ExpectEqualMultisetBeginEnd(&std_default_constructor,
                                          &s21_default_constructor));

  std::multiset<Key> const std_const_default_constructor;
  s21::multiset<Key> const s21_const_default_constructor;
  EXPECT_TRUE(ExpectEqualMultisetBeginEnd(&std_const_default_constructor,
                                          &s21_const_default_constructor));

  //---------------------------------------------------------------------------

  std::multiset<Key> std_initializer_list_constructor(items);
  s21::multiset<Key> s21_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualMultisets(&std_initializer_list_constructor,
                                   &s21_initializer_list_constructor));

  std::multiset<Key> const std_const_initializer_list_constructor(items);
  s21::multiset<Key> const s21_const_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualMultisets(&std_const_initializer_list_constructor,
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

  std::multiset<Key> std_copy_constructor(std_initializer_list_constructor);
  s21::multiset<Key> s21_copy_constructor(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualMultisets(&std_initializer_list_constructor,
                                   &s21_initializer_list_constructor));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

  std::multiset<Key> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  s21::multiset<Key> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualMultisets(&std_const_initializer_list_constructor,
                                   &s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualMultisets(&std_const_copy_constructor,
                                   &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  std::multiset<Key> std_move_constructor(
      std::move(std_initializer_list_constructor));
  s21::multiset<Key> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_move_constructor, &s21_move_constructor));
  EXPECT_TRUE(ExpectEqualMultisets(&std_initializer_list_constructor,
                                   &s21_initializer_list_constructor));

  std::multiset<Key> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  s21::multiset<Key> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualMultisets(&std_const_move_constructor,
                                   &s21_const_move_constructor));
  EXPECT_TRUE(ExpectEqualMultisets(&std_const_initializer_list_constructor,
                                   &s21_const_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std_default_constructor = std_move_constructor;
  s21_default_constructor = s21_move_constructor;
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_move_constructor, &s21_move_constructor));

  std_default_constructor = std_const_move_constructor;
  s21_default_constructor = s21_const_move_constructor;
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(ExpectEqualMultisets(&std_const_move_constructor,
                                   &s21_const_move_constructor));

  std::multiset<Key> std_operator_overload;
  s21::multiset<Key> s21_operator_overload;
  std_operator_overload = std::move(std_move_constructor);
  s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_operator_overload, &s21_operator_overload));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_move_constructor, &s21_move_constructor));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_operator_overload, &s21_operator_overload));

  //---------------------------------------------------------------------------

  EXPECT_EQ(*std_copy_constructor.begin(), *s21_copy_constructor.begin());
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.begin());
  EXPECT_TRUE(ExpectNotEqualMultisetBeginEnd(&std_copy_constructor,
                                             &s21_copy_constructor));
  EXPECT_TRUE(ExpectNotEqualMultisetBeginEnd(&std_const_copy_constructor,
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
  EXPECT_TRUE(ExpectEqualMultisetBeginEnd(&std_copy_constructor,
                                          &s21_copy_constructor));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  auto item = items.end();
  --item;

  EXPECT_EQ(*(std_copy_constructor.insert(*item)),
            *(s21_copy_constructor.insert(*item)));
  EXPECT_EQ(*(std_copy_constructor.insert(*item)),
            *(s21_copy_constructor.insert(*item)));
  EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  EXPECT_EQ(*(std_copy_constructor.insert(*item)),
            *(s21_copy_constructor.insert(*item)));
  EXPECT_EQ(*(std_copy_constructor.insert(*item)),
            *(s21_copy_constructor.insert(*item)));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

  std_default_constructor = std_copy_constructor;
  s21_default_constructor = s21_copy_constructor;
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_default_constructor, &s21_default_constructor));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

  std_default_constructor = std_default_constructor;
  s21_default_constructor = s21_default_constructor;
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_default_constructor, &s21_default_constructor));

  for (auto item = items.begin(); item != items.end(); ++item) {
    std_copy_constructor.insert(*item);
    s21_copy_constructor.insert(*item);
  }
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_copy_constructor.count(*item),
            s21_copy_constructor.count(*item));

  //---------------------------------------------------------------------------

  EXPECT_EQ(*(std_copy_constructor.lower_bound(*item)),
            *(s21_copy_constructor.lower_bound(*item)));

  EXPECT_EQ(*((std_copy_constructor.equal_range(*item)).first),
            *((s21_copy_constructor.equal_range(*item)).first));

  //---------------------------------------------------------------------------

  std_copy_constructor.erase(std_copy_constructor.begin());
  s21_copy_constructor.erase(s21_copy_constructor.begin());
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

  auto std_pos = std_copy_constructor.begin();
  ++std_pos;
  std_copy_constructor.erase(std_pos);
  auto s21_pos = s21_copy_constructor.begin();
  ++s21_pos;
  s21_copy_constructor.erase(s21_pos);
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

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
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

  for (; !std_copy_constructor.empty() && !s21_copy_constructor.empty();) {
    ;
    std_pos = std_copy_constructor.begin();
    s21_pos = s21_copy_constructor.begin();
    std_copy_constructor.erase(std_pos);
    s21_copy_constructor.erase(s21_pos);
    EXPECT_TRUE(
        ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));
  }
  EXPECT_TRUE(std_copy_constructor.empty());
  EXPECT_TRUE(s21_copy_constructor.empty());

  //---------------------------------------------------------------------------

  for (auto item = items.begin(); item != items.end(); ++item) {
    std_copy_constructor.insert(*item);
    s21_copy_constructor.insert(*item);
  }
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_move_constructor, &s21_move_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor = std::multiset<Key>(std_move_constructor);
  s21_copy_constructor = s21::multiset<Key>(s21_move_constructor);

  std_initializer_list_constructor.merge(std_move_constructor);
  s21_initializer_list_constructor.merge(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualMultisets(&std_initializer_list_constructor,
                                   &s21_initializer_list_constructor));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_move_constructor, &s21_move_constructor));

  std_initializer_list_constructor.merge(std_move_constructor);
  s21_initializer_list_constructor.merge(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualMultisets(&std_initializer_list_constructor,
                                   &s21_initializer_list_constructor));
  EXPECT_TRUE(
      ExpectEqualMultisets(&std_move_constructor, &s21_move_constructor));

  //---------------------------------------------------------------------------

  EXPECT_EQ(*std_copy_constructor.find(*(items.begin())),
            *s21_copy_constructor.find(*(items.begin())));

  //---------------------------------------------------------------------------

  EXPECT_TRUE(s21_copy_constructor.contains(*(items.begin())));

  //---------------------------------------------------------------------------

  {
    using multiset_t = typename s21::multiset<Key>::item_type;

    //---------------------------------------------------------------------------

    std::multiset<Key> std_multiset;
    s21::multiset<Key> s21_multiset;

    std_multiset.emplace();
    s21_multiset.insert_many();
    std_multiset.emplace();
    s21_multiset.insert_many();
    EXPECT_TRUE(ExpectEqualMultisets(&std_multiset, &s21_multiset));

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
        std_multiset.emplace(item);
        if (--j <= 0) break;
      }
      typename multiset_t::RBTPtrs *ptrs[5];
      for (int i = 0; i < 5; i++) {
        ptrs[i] = new typename multiset_t::RBTPtrs(nullptr, nullptr, nullptr);
      }
      auto ress =
          s21_multiset.insert_many(multiset_t(args[0], s21::Red, ptrs[0]),
                                   multiset_t(args[1], s21::Red, ptrs[1]),
                                   multiset_t(args[2], s21::Red, ptrs[2]),
                                   multiset_t(args[3], s21::Red, ptrs[3]),
                                   multiset_t(args[4], s21::Red, ptrs[4]));
      EXPECT_TRUE(ExpectEqualMultisets(&std_multiset, &s21_multiset));
      for (auto res : ress) {
        EXPECT_TRUE(s21_multiset.contains(*(res.first)));
      }
    }

    //---------------------------------------------------------------------------
  }
}

TEST(TestS21Containers, Multiset) {
  TestMultiset<char>('a', 'b', 'c', 'd', 'e');
  TestMultiset<int>(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 19, 18, 17, 16, 15, 14,
                    13, 12, 11);
  TestMultiset<int>(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                    17, 18, 19);
  TestMultiset<double>(0, 1, DBL_MIN, -DBL_MAX, DBL_MAX);
  TestMultiset<A>(A(""), A("one"), A("two"), A("three"), A("four"));
}
