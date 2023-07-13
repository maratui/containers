#include "./tests.h"

template <class K, class T>
void CoutMaps(const std::map<K, T> *std_map, const s21::map<K, T> *s21_map) {
  for (auto std_iter = std_map->begin(), end = std_map->end(); std_iter != end;
       ++std_iter)
    std::cout << (*std_iter).first << " " << (*std_iter).second << " ";
  std::cout << "\n";

  for (auto s21_iter = s21_map->begin(), end = s21_map->end(); s21_iter != end;
       ++s21_iter)
    std::cout << (*s21_iter).first << " " << (*s21_iter).second << " ";
  std::cout << "\n";
}

template <class K, class T, class... Args>
void test_map(Args... args) {
  std::initializer_list<std::pair<const K, T>> const &items = {
      (std::pair<const K, T>)args...};
  T temp;
  //---------------------------------------------------------------------------

  std::map<K, T> std_default_constructor;
  s21::map<K, T> s21_default_constructor;
  EXPECT_TRUE(ExpectEqualMapBeginEnd(&std_default_constructor,
                                     &s21_default_constructor));

  std::map<K, T> const std_const_default_constructor;
  s21::map<K, T> const s21_const_default_constructor;
  EXPECT_TRUE(ExpectEqualMapBeginEnd(&std_const_default_constructor,
                                     &s21_const_default_constructor));

  //---------------------------------------------------------------------------

  std::map<K, T> std_initializer_list_constructor(items);
  s21::map<K, T> s21_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualMaps(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));

  std::map<K, T> const std_const_initializer_list_constructor(items);
  s21::map<K, T> const s21_const_initializer_list_constructor(items);
  EXPECT_TRUE(ExpectEqualMaps(&std_const_initializer_list_constructor,
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

  std::map<K, T> std_copy_constructor(std_initializer_list_constructor);
  s21::map<K, T> s21_copy_constructor(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualMaps(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

  std::map<K, T> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  s21::map<K, T> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualMaps(&std_const_initializer_list_constructor,
                              &s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_const_copy_constructor,
                              &s21_const_copy_constructor));

  //---------------------------------------------------------------------------

  std::map<K, T> std_move_constructor(
      std::move(std_initializer_list_constructor));
  s21::map<K, T> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_move_constructor, &s21_move_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));

  std::map<K, T> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  s21::map<K, T> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_const_move_constructor,
                              &s21_const_move_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_const_initializer_list_constructor,
                              &s21_const_initializer_list_constructor));

  //---------------------------------------------------------------------------

  std::map<K, T> std_operator_overload = std::move(std_move_constructor);
  s21::map<K, T> s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualMaps(&std_operator_overload, &s21_operator_overload));
  EXPECT_TRUE(ExpectEqualMaps(&std_move_constructor, &s21_move_constructor));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_TRUE(ExpectEqualMaps(&std_operator_overload, &s21_operator_overload));

  //---------------------------------------------------------------------------

  auto item = items.begin();
  ++item;
  ++item;
  ++item;
  temp = std_copy_constructor.at((*item).first);
  std_copy_constructor.at((*item).first) = temp;
  temp = s21_copy_constructor.at((*item).first);
  s21_copy_constructor.at((*item).first) = temp;

  EXPECT_EQ(std_copy_constructor.at((*item).first),
            s21_copy_constructor.at((*item).first));
  ++item;
  EXPECT_NO_THROW(std_copy_constructor.at((*item).first));
  EXPECT_NO_THROW(s21_copy_constructor.at((*item).first));

  item = items.begin();
  ++item;
  ++item;
  ++item;
  temp = std_const_copy_constructor.at((*item).first);
  temp = s21_const_copy_constructor.at((*item).first);
  ++item;
  EXPECT_NO_THROW(std_const_copy_constructor.at((*item).first));
  EXPECT_NO_THROW(s21_const_copy_constructor.at((*item).first));
  item = items.begin();
  EXPECT_EQ(std_const_copy_constructor.at((*item).first),
            s21_const_copy_constructor.at((*item).first));

  //---------------------------------------------------------------------------

  item = items.begin();
  ++item;
  ++item;
  ++item;
  temp = std_copy_constructor[(*item).first];
  std_copy_constructor[(*item).first] = temp;
  temp = s21_copy_constructor[(*item).first];
  s21_copy_constructor[(*item).first] = temp;
  for (auto item = items.begin(); item != items.end(); ++item)
    EXPECT_EQ(std_copy_constructor[(*item).first],
              s21_copy_constructor[(*item).first]);
  item = items.begin();
  ++item;
  ++item;
  ++item;
  ++item;
  EXPECT_NO_THROW(std_copy_constructor[(*item).first]);
  EXPECT_NO_THROW(s21_copy_constructor[(*item).first]);

  item = items.begin();
  ++item;
  ++item;
  ++item;
  temp = s21_const_copy_constructor[(*item).first];
  for (auto item = items.begin(); item != items.end(); ++item)
    EXPECT_EQ(s21_copy_constructor[(*item).first],
              s21_const_copy_constructor[(*item).first]);
  item = items.begin();
  ++item;
  ++item;
  ++item;
  ++item;
  EXPECT_NO_THROW(s21_const_copy_constructor[(*item).first]);

  //---------------------------------------------------------------------------

  EXPECT_EQ(*std_copy_constructor.begin(), *s21_copy_constructor.begin());
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.begin());
  EXPECT_TRUE(
      ExpectNotEqualMapBeginEnd(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectNotEqualMapBeginEnd(&std_const_copy_constructor,
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
      ExpectEqualMapBeginEnd(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  item = items.end();
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
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

  --item;

  EXPECT_TRUE(
      (std_copy_constructor.insert_or_assign((*item).first, (*item).second))
          .second);
  EXPECT_TRUE(
      (s21_copy_constructor.insert_or_assign((*item).first, (*item).second))
          .second);
  EXPECT_FALSE(
      (std_copy_constructor.insert_or_assign((*item).first, (*item).second))
          .second);
  EXPECT_FALSE(
      (s21_copy_constructor.insert_or_assign((*item).first, (*item).second))
          .second);
  EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.size());
  EXPECT_EQ(
      (std_copy_constructor.insert_or_assign((*item).first, (*item).second))
          .second,
      (s21_copy_constructor.insert_or_assign((*item).first, (*item).second))
          .second);
  EXPECT_EQ(
      *((std_copy_constructor.insert_or_assign((*item).first, (*item).second))
            .first),
      *((s21_copy_constructor.insert_or_assign((*item).first, (*item).second))
            .first));
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

  for (auto item = items.begin(); item != items.end(); ++item) {
    std_copy_constructor.insert(*item);
    s21_copy_constructor.insert(*item);
  }
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor.erase(std_copy_constructor.begin());
  s21_copy_constructor.erase(s21_copy_constructor.begin());
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

  auto std_pos = std_copy_constructor.begin();
  ++std_pos;
  std_copy_constructor.erase(std_pos);
  auto s21_pos = s21_copy_constructor.begin();
  ++s21_pos;
  s21_copy_constructor.erase(s21_pos);
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

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
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

  for (; !std_copy_constructor.empty() && !s21_copy_constructor.empty();) {
    ;
    std_pos = std_copy_constructor.begin();
    s21_pos = s21_copy_constructor.begin();
    std_copy_constructor.erase(std_pos);
    s21_copy_constructor.erase(s21_pos);
    EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));
  }
  EXPECT_TRUE(std_copy_constructor.empty());
  EXPECT_TRUE(s21_copy_constructor.empty());

  //---------------------------------------------------------------------------

  for (auto item = items.begin(); item != items.end(); ++item) {
    std_copy_constructor.insert(*item);
    s21_copy_constructor.insert(*item);
  }
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));

  std_copy_constructor.swap(std_move_constructor);
  s21_copy_constructor.swap(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualMaps(&std_copy_constructor, &s21_copy_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_move_constructor, &s21_move_constructor));

  //---------------------------------------------------------------------------

  std_copy_constructor = std::map<K, T>(std_move_constructor);
  s21_copy_constructor = s21::map<K, T>(s21_move_constructor);

  std_initializer_list_constructor.merge(std_move_constructor);
  s21_initializer_list_constructor.merge(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualMaps(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_move_constructor, &s21_move_constructor));

  std_initializer_list_constructor.merge(std_move_constructor);
  s21_initializer_list_constructor.merge(s21_move_constructor);
  EXPECT_TRUE(ExpectEqualMaps(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));
  EXPECT_TRUE(ExpectEqualMaps(&std_move_constructor, &s21_move_constructor));

  std_initializer_list_constructor.merge(std_initializer_list_constructor);
  s21_initializer_list_constructor.merge(s21_initializer_list_constructor);
  EXPECT_TRUE(ExpectEqualMaps(&std_initializer_list_constructor,
                              &s21_initializer_list_constructor));

  //---------------------------------------------------------------------------

  EXPECT_TRUE(s21_copy_constructor.contains((*(items.begin())).first));

  //---------------------------------------------------------------------------

  {
    using map_t = typename s21::map<K, T>::item_type;

    //---------------------------------------------------------------------------

    std::map<K, T> std_map;
    s21::map<K, T> s21_map;

    std_map.emplace();
    s21_map.insert_many();
    std_map.emplace();
    s21_map.insert_many();
    EXPECT_TRUE(ExpectEqualMaps(&std_map, &s21_map));

    std::pair<K, T> args[items.size()];
    {
      int i = 0;
      for (auto item : items) {
        args[i].first = item.first;
        args[i++].second = item.second;
      }
    }

    for (auto i = 0; i < 3; i++) {
      int j = 5;
      for (std::pair<K, T> item : items) {
        std_map.emplace(item);
        if (--j <= 0) break;
      }
      typename map_t::RBTPtrs *ptrs[5];
      for (int i = 0; i < 5; i++) {
        ptrs[i] = new typename map_t::RBTPtrs(nullptr, nullptr, nullptr);
      }
      auto ress = s21_map.insert_many(
          map_t(args[0], s21::Red, ptrs[0]), map_t(args[1], s21::Red, ptrs[1]),
          map_t(args[2], s21::Red, ptrs[2]), map_t(args[3], s21::Red, ptrs[3]),
          map_t(args[4], s21::Red, ptrs[4]));
      EXPECT_TRUE(ExpectEqualMaps(&std_map, &s21_map));
      for (auto res : ress) {
        EXPECT_TRUE(s21_map.contains((*(res.first)).first));
      }
    }

    //---------------------------------------------------------------------------
  }
}

TEST(TestS21Containers, Map) {
  test_map<char, char>(std::pair(0, 0), std::pair(1, 1), std::pair(2, 0),
                       std::pair(3, 4), std::pair(4, 127));
  test_map<int, int>(
      std::pair(0, 0), std::pair(1, 1), std::pair(2, -2147483647),
      std::pair(3, 4), std::pair(4, 2147483647), std::pair(5, 2147483647),
      std::pair(6, 2147483647), std::pair(7, 2147483647),
      std::pair(8, 2147483647), std::pair(9, 2147483647), std::pair(10, 0),
      std::pair(19, 1), std::pair(18, -2147483647), std::pair(17, 4),
      std::pair(16, 2147483647), std::pair(15, 2147483647),
      std::pair(14, 2147483647), std::pair(13, 2147483647),
      std::pair(12, 2147483647), std::pair(11, 2147483647));
  test_map<int, int>(
      std::pair(0, 0), std::pair(1, 1), std::pair(2, -2147483647),
      std::pair(3, 4), std::pair(4, 2147483647), std::pair(5, 2147483647),
      std::pair(6, 2147483647), std::pair(7, 2147483647),
      std::pair(8, 2147483647), std::pair(9, 2147483647), std::pair(10, 0),
      std::pair(11, 1), std::pair(12, -2147483647), std::pair(13, 4),
      std::pair(14, 2147483647), std::pair(15, 2147483647),
      std::pair(16, 2147483647), std::pair(17, 2147483647),
      std::pair(18, 2147483647), std::pair(19, 2147483647));
  test_map<double, double>(std::pair(0, 0), std::pair(1, 1),
                           std::pair(2, DBL_MIN), std::pair(3, -DBL_MAX),
                           std::pair(4, DBL_MAX));
  test_map<A, A>(std::pair(A(""), A(" ")), std::pair(A("one"), A("one ")),
                 std::pair(A("two"), A("two ")),
                 std::pair(A("three"), A("three ")),
                 std::pair(A("four"), A("four ")));
}
