#include <gtest/gtest.h>

#include <list>
#include <type_traits>

#include "./s21_containers.h"

template <typename T>
void test_list(std::initializer_list<T> const& items) {
  T temp;
  //---------------------------------------------------------------------------

  std::list<T> std_default_constructor;
  S21::List<T> s21_default_constructor;
  EXPECT_EQ(std_default_constructor.size(), s21_default_constructor.Size());
  EXPECT_EQ(0, s21_default_constructor.Size());
  //  EXPECT_EQ(sizeof(std_default_constructor),
  //  sizeof(s21_default_constructor)); EXPECT_EQ(std_default_constructor.end()
  //  - std_default_constructor.begin(),
  //            s21_default_constructor.End() -
  //            s21_default_constructor.Begin());
  // EXPECT_EQ(0, s21_default_constructor.End() -
  // s21_default_constructor.Begin());
  // std::cout << sizeof(std_default_constructor) << "\n";
  // std::cout << sizeof(s21_default_constructor) << "\n\n";
  std::list<T> const std_const_default_constructor;
  S21::List<T> const s21_const_default_constructor;
  EXPECT_EQ(std_const_default_constructor.size(),
            s21_const_default_constructor.Size());
  //  EXPECT_EQ(std_const_default_constructor.end() -
  //                std_const_default_constructor.begin(),
  //            s21_const_default_constructor.End() -
  //                s21_const_default_constructor.Begin());
  // EXPECT_EQ(0, s21_const_default_constructor.End() -
  //                 s21_const_default_constructor.Begin());

  //---------------------------------------------------------------------------

  std::list<T> std_parameterized_constructor(100);
  S21::List<T> s21_parameterized_constructor(100);
  EXPECT_EQ(std_parameterized_constructor.size(),
            s21_parameterized_constructor.Size());
  //  EXPECT_EQ(sizeof(std_parameterized_constructor),
  //  sizeof(s21_parameterized_constructor));
  // std::cout << sizeof(std_parameterized_constructor) << "\n";
  // std::cout << sizeof(s21_parameterized_constructor) << "\n\n";
  //  for (size_t i = 0; i < std_parameterized_constructor.size(); i++)
  //    EXPECT_EQ(std_parameterized_constructor[i],
  //              s21_parameterized_constructor.At(i));

  std::list<T> const std_const_parameterized_constructor(100);
  S21::List<T> const s21_const_parameterized_constructor(100);
  EXPECT_EQ(std_const_parameterized_constructor.size(),
            s21_const_parameterized_constructor.Size());
  //  for (size_t i = 0; i < std_const_parameterized_constructor.size(); i++)
  //    EXPECT_EQ(std_const_parameterized_constructor[i],
  //              s21_const_parameterized_constructor.At(i));

  //---------------------------------------------------------------------------

  std::list<T> std_initializer_list_constructor(items);
  S21::List<T> s21_initializer_list_constructor(items);
  EXPECT_EQ(std_initializer_list_constructor.size(),
            s21_initializer_list_constructor.Size());
  //  for (size_t i = 0; i < std_initializer_list_constructor.size(); i++)
  //    EXPECT_EQ(std_initializer_list_constructor[i],
  //              s21_initializer_list_constructor.At(i));

  std::list<T> const std_const_initializer_list_constructor(items);
  S21::List<T> const s21_const_initializer_list_constructor(items);
  EXPECT_EQ(std_const_initializer_list_constructor.size(),
            s21_const_initializer_list_constructor.Size());
  //  for (size_t i = 0; i < std_const_initializer_list_constructor.size(); i++)
  //    EXPECT_EQ(std_const_initializer_list_constructor[i],
  //              s21_const_initializer_list_constructor.At(i));

  //---------------------------------------------------------------------------

  std::list<T> std_copy_constructor(std_initializer_list_constructor);
  S21::List<T> s21_copy_constructor(s21_initializer_list_constructor);
  EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.Size());
  EXPECT_EQ(s21_initializer_list_constructor.Size(),
            s21_copy_constructor.Size());
  //      for (size_t i = 0; i < std_copy_constructor.size(); i++)
  //        EXPECT_EQ(std_copy_constructor.at(i), s21_copy_constructor.At(i));
  //      for (size_t i = 0; i < s21_initializer_list_constructor.Size(); i++)
  //        EXPECT_EQ(s21_initializer_list_constructor.At(i),
  //                  s21_copy_constructor.At(i));

  std::list<T> const std_const_copy_constructor(
      std_const_initializer_list_constructor);
  S21::List<T> const s21_const_copy_constructor(
      s21_const_initializer_list_constructor);
  EXPECT_EQ(std_const_copy_constructor.size(),
            s21_const_copy_constructor.Size());
  EXPECT_EQ(s21_const_initializer_list_constructor.Size(),
            s21_const_copy_constructor.Size());
  //      for (size_t i = 0; i < std_const_copy_constructor.size(); i++)
  //        EXPECT_EQ(std_const_copy_constructor.at(i),
  //                  s21_const_copy_constructor.At(i));
  //      for (size_t i = 0; i < s21_initializer_list_constructor.Size(); i++)
  //        EXPECT_EQ(s21_const_initializer_list_constructor.At(i),
  //                  s21_const_copy_constructor.At(i));

  //---------------------------------------------------------------------------

  std::list<T> std_move_constructor(
      std::move(std_initializer_list_constructor));
  S21::List<T> s21_move_constructor(
      std::move(s21_initializer_list_constructor));
  EXPECT_EQ(std_move_constructor.size(), s21_move_constructor.Size());
  EXPECT_EQ(s21_copy_constructor.Size(), s21_move_constructor.Size());
  //  for (size_t i = 0; i < std_move_constructor.size(); i++)
  //    EXPECT_EQ(std_move_constructor.at(i), s21_move_constructor.At(i));
  //  for (size_t i = 0; i < s21_copy_constructor.Size(); i++)
  //    EXPECT_EQ(s21_copy_constructor.At(i), s21_move_constructor.At(i));
  EXPECT_EQ(0, std_initializer_list_constructor.size());
  EXPECT_EQ(0, s21_initializer_list_constructor.Size());
  //  EXPECT_EQ(std_initializer_list_constructor.end() -
  //                std_initializer_list_constructor.begin(),
  //            s21_initializer_list_constructor.End() -
  //                s21_initializer_list_constructor.Begin());
  EXPECT_EQ(0, s21_initializer_list_constructor.End() -
                   s21_initializer_list_constructor.Begin());

  std::list<T> const std_const_move_constructor(
      std::move(std_const_initializer_list_constructor));
  S21::List<T> const s21_const_move_constructor(
      std::move(s21_const_initializer_list_constructor));
  EXPECT_EQ(std_const_move_constructor.size(),
            s21_const_move_constructor.Size());
  EXPECT_EQ(s21_const_copy_constructor.Size(),
            s21_const_move_constructor.Size());
  //  for (size_t i = 0; i < std_const_move_constructor.size(); i++)
  //    EXPECT_EQ(std_const_move_constructor.at(i),
  //              s21_const_move_constructor.At(i));
  //  for (size_t i = 0; i < s21_const_copy_constructor.Size(); i++)
  //    EXPECT_EQ(s21_const_copy_constructor.At(i),
  //              s21_const_move_constructor.At(i));

  EXPECT_EQ(5, std_const_initializer_list_constructor.size());
  EXPECT_EQ(5, s21_const_initializer_list_constructor.Size());
  //  for (size_t i = 0; i < s21_const_initializer_list_constructor.Size(); i++)
  //    EXPECT_EQ(s21_const_initializer_list_constructor.At(i),
  //              std_const_initializer_list_constructor.at(i));

  //---------------------------------------------------------------------------

  std::list<T> std_operator_overload;
  S21::List<T> s21_operator_overload;
  std_operator_overload = std_move_constructor;
  s21_operator_overload = s21_move_constructor;
  EXPECT_EQ(std_operator_overload.size(), s21_operator_overload.Size());
  EXPECT_EQ(s21_move_constructor.Size(), s21_operator_overload.Size());
  //  for (size_t i = 0; i < std_operator_overload.size(); i++)
  //    EXPECT_EQ(std_operator_overload.at(i), s21_operator_overload.At(i));
  //  for (size_t i = 0; i < s21_copy_constructor.Size(); i++)
  //    EXPECT_EQ(s21_move_constructor.At(i), s21_operator_overload.At(i));

  EXPECT_NO_THROW(std_operator_overload = std_const_move_constructor);
  EXPECT_NO_THROW(s21_operator_overload = s21_const_move_constructor);
  EXPECT_EQ(std_operator_overload.size(), s21_operator_overload.Size());
  EXPECT_EQ(s21_const_move_constructor.Size(), s21_operator_overload.Size());
  //  for (size_t i = 0; i < std_operator_overload.size(); i++)
  //    EXPECT_EQ(std_operator_overload.at(i), s21_operator_overload.At(i));
  //  for (size_t i = 0; i < s21_copy_constructor.Size(); i++)
  //    EXPECT_EQ(s21_const_move_constructor.At(i),
  //    s21_operator_overload.At(i));

  std_operator_overload = std::move(std_move_constructor);
  s21_operator_overload = std::move(s21_move_constructor);
  EXPECT_EQ(std_operator_overload.size(), s21_operator_overload.Size());
  EXPECT_EQ(s21_copy_constructor.Size(), s21_operator_overload.Size());
  //  for (size_t i = 0; i < std_operator_overload.size(); i++)
  //    EXPECT_EQ(std_operator_overload.at(i), s21_operator_overload.At(i));
  //  for (size_t i = 0; i < s21_copy_constructor.Size(); i++)
  //    EXPECT_EQ(s21_copy_constructor.At(i), s21_operator_overload.At(i));
  EXPECT_EQ(0, std_move_constructor.size());
  EXPECT_EQ(0, s21_move_constructor.Size());
  //  EXPECT_EQ(std_move_constructor.end() - std_move_constructor.begin(),
  //            s21_move_constructor.End() - s21_move_constructor.Begin());
  //  EXPECT_EQ(0, s21_move_constructor.End() - s21_move_constructor.Begin());

  std_operator_overload = std::move(std_const_move_constructor);
  s21_operator_overload = std::move(s21_const_move_constructor);
  EXPECT_EQ(std_operator_overload.size(), s21_operator_overload.Size());
  EXPECT_EQ(s21_copy_constructor.Size(), s21_operator_overload.Size());
  //  for (size_t i = 0; i < std_operator_overload.size(); i++)
  //    EXPECT_EQ(std_operator_overload.at(i), s21_operator_overload.At(i));
  //  for (size_t i = 0; i < s21_copy_constructor.Size(); i++)
  //    EXPECT_EQ(s21_copy_constructor.At(i), s21_operator_overload.At(i));
  EXPECT_EQ(5, std_const_move_constructor.size());
  EXPECT_EQ(5, s21_const_move_constructor.Size());

  s21_operator_overload = s21_operator_overload;
  EXPECT_EQ(std_copy_constructor.size(), s21_operator_overload.Size());
  //  for (size_t i = 0; i < std_operator_overload.size(); i++)
  //    EXPECT_EQ(std_operator_overload.at(i), s21_operator_overload.At(i));

  std_operator_overload = std::move(std_operator_overload);
  s21_operator_overload = std::move(s21_operator_overload);
  EXPECT_EQ(0, std_operator_overload.size());
  EXPECT_EQ(0, s21_operator_overload.Size());
  //  EXPECT_EQ(std_operator_overload.end() - std_operator_overload.begin(),
  //            s21_operator_overload.End() - s21_operator_overload.Begin());
  //  EXPECT_EQ(0, s21_operator_overload.End() - s21_operator_overload.Begin());

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
  //  temp = (std_copy_constructor.end() - 1)[0];
  //  (std_copy_constructor.end() - 1)[0] = temp;
  //  temp = (s21_copy_constructor.End() - 1)[0];
  //  (s21_copy_constructor.End() - 1)[0] = temp;
  //  for (size_t i = 0; i < std_copy_constructor.size(); i++)
  //    EXPECT_EQ(std_copy_constructor.begin()[i],
  //    s21_copy_constructor.Begin()[i]);
  //  for (size_t i = 1; i <= std_copy_constructor.size(); i++)
  //    EXPECT_EQ((std_copy_constructor.end() - i)[i - 1],
  //              (s21_copy_constructor.End() - i)[i - 1]);
  EXPECT_EQ(*std_copy_constructor.begin(), *s21_copy_constructor.Begin());
  //  EXPECT_EQ((std_copy_constructor.end() - std_copy_constructor.begin()),
  //            (s21_copy_constructor.End() - s21_copy_constructor.Begin()));

  temp = *std_const_copy_constructor.begin();
  temp = *s21_const_copy_constructor.Begin();
  //  temp = (std_const_copy_constructor.end() - 1)[0];
  //  temp = (s21_const_copy_constructor.End() - 1)[0];
  EXPECT_EQ(*std_const_copy_constructor.begin(),
            *s21_const_copy_constructor.Begin());
  //  EXPECT_EQ(
  //      (std_const_copy_constructor.end() -
  //      std_const_copy_constructor.begin()), (s21_const_copy_constructor.End()
  //      - s21_const_copy_constructor.Begin()));

  //---------------------------------------------------------------------------

  EXPECT_FALSE(std_copy_constructor.empty());
  EXPECT_FALSE(s21_copy_constructor.Empty());
  EXPECT_FALSE(std_const_copy_constructor.empty());
  EXPECT_FALSE(s21_const_copy_constructor.Empty());
  EXPECT_TRUE(std_move_constructor.empty());
  EXPECT_TRUE(s21_move_constructor.Empty());

  //---------------------------------------------------------------------------

  EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.Size());
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
  EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.Size());
  EXPECT_EQ(0, s21_copy_constructor.Size());
  EXPECT_TRUE(std_copy_constructor.begin() == std_copy_constructor.end());
  EXPECT_TRUE(s21_copy_constructor.Begin() == s21_copy_constructor.End());
  EXPECT_EQ(*std_copy_constructor.begin(), *s21_copy_constructor.Begin());
  EXPECT_EQ(*std_copy_constructor.end(), *s21_copy_constructor.Begin());
  //  for (size_t i = 0; i < std_copy_constructor.capacity(); i++)
  //    EXPECT_EQ(std_copy_constructor[i], s21_copy_constructor[i]);
  //  EXPECT_EQ((std_copy_constructor.end() - std_copy_constructor.begin()),
  //            (s21_copy_constructor.End() - s21_copy_constructor.Begin()));
  //  EXPECT_EQ(0, (s21_copy_constructor.End() - s21_copy_constructor.Begin()));

  //---------------------------------------------------------------------------
  /*
                        std_copy_constructor.shrink_to_fit();
                        s21_copy_constructor.ShrinkToFit();
                        for (auto i = 0; i < 21; i++) {
                          std_copy_constructor.insert(std_copy_constructor.begin(),
         i
           + 1); s21_copy_constructor.Insert(s21_copy_constructor.Begin(), i +
     1); EXPECT_EQ(std_copy_constructor.size(), s21_copy_constructor.Size());
             EXPECT_EQ(std_copy_constructor.capacity(),
                        s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                        std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
                        }
                        EXPECT_EQ((std_copy_constructor.end() -
                 std_copy_constructor.begin()), (s21_copy_constructor.End() -
                   s21_copy_constructor.Begin()));

                        std_copy_constructor.insert(std_copy_constructor.begin()
     + 5, 105); s21_copy_constructor.Insert(s21_copy_constructor.Begin() + 5,
           105); EXPECT_EQ(std_copy_constructor.size(),
         s21_copy_constructor.Size());
     EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));

                        std_copy_constructor.insert(std_copy_constructor.begin(),
           101); s21_copy_constructor.Insert(s21_copy_constructor.Begin(), 101);
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));

                        std_copy_constructor.insert(std_copy_constructor.end(),
         111); s21_copy_constructor.Insert(s21_copy_constructor.End(), 111);
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));

                        std_copy_constructor.shrink_to_fit();
                        s21_copy_constructor.ShrinkToFit();
                        std_copy_constructor.insert(std_copy_constructor.end(),
         222); s21_copy_constructor.Insert(s21_copy_constructor.End(), 222);
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));

                        //---------------------------------------------------------------------------

                        std_copy_constructor.erase(std_copy_constructor.begin());
                        s21_copy_constructor.Erase(s21_copy_constructor.Begin());
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));
                        std_copy_constructor.erase(std_copy_constructor.begin()
     + 5); s21_copy_constructor.Erase(s21_copy_constructor.Begin() + 5);
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));

                        std_copy_constructor.erase(std_copy_constructor.end() -
       1); s21_copy_constructor.Erase(s21_copy_constructor.End() - 1);
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));

                        //---------------------------------------------------------------------------

                        std_copy_constructor.clear();
                        s21_copy_constructor.Clear();
                        std_copy_constructor.shrink_to_fit();
                        s21_copy_constructor.ShrinkToFit();
                        for (auto i = 0; i < 21; i++) {
                          std_copy_constructor.push_back(i + 1);
                          s21_copy_constructor.PushBack(i + 1);
                          EXPECT_EQ(std_copy_constructor.size(),
                 s21_copy_constructor.Size());
             EXPECT_EQ(std_copy_constructor.capacity(),
                        s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                        std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));
                        }
                        std_copy_constructor.shrink_to_fit();
                        s21_copy_constructor.ShrinkToFit();
                        std_copy_constructor.push_back(222);
                        s21_copy_constructor.PushBack(222);
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));

                        //---------------------------------------------------------------------------

                        std_copy_constructor.pop_back();
                        s21_copy_constructor.PopBack();
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin()));

                        //---------------------------------------------------------------------------

                        std_copy_constructor.swap(std_move_constructor);
                        s21_copy_constructor.Swap(s21_move_constructor);
                        EXPECT_EQ(std_copy_constructor.size(),
               s21_copy_constructor.Size());
           EXPECT_EQ(std_copy_constructor.capacity(),
                       s21_copy_constructor.Capacity()); for (size_t j = 0; j <
                       std_copy_constructor.size(); j++)
               EXPECT_EQ(std_copy_constructor[j], s21_copy_constructor[j]);
               EXPECT_EQ((std_copy_constructor.end() -
         std_copy_constructor.begin()), (s21_copy_constructor.End() -
         s21_copy_constructor.Begin())); EXPECT_EQ(std_move_constructor.size(),
         s21_move_constructor.Size());
     EXPECT_EQ(std_move_constructor.capacity(),
                       s21_move_constructor.Capacity()); for (size_t j = 0; j <
                       std_move_constructor.size(); j++)
               EXPECT_EQ(std_move_constructor[j], s21_move_constructor[j]);
               EXPECT_EQ((std_move_constructor.end() -
         std_move_constructor.begin()), (s21_move_constructor.End() -
         s21_move_constructor.Begin()));
                      */
}

TEST(TestS21Containers, List) {
  //   test_list<bool>({0, 1, 0, 1, 1});
  // test_list<signed char>({0, 1, -128, 4, 127});
  // test_list<unsigned char>({0, 1, 0, 4, 255});
  // test_list<char>({0, 1, 0, 4, 127});
  // test_list<short>({0, 1, -32768, 4, 32767});
  // test_list<unsigned short>({0, 1, 0, 4, 65535});
  test_list<int>({0, 1, -2147483648, 4, 2147483647});
  //  test_list<unsigned int>({0, 1, 0, 4, 4294967295});
  //  test_list<long>({0, 1, -2147483648, 4, 2147483647});
  //  test_list<unsigned long>({0, 1, 0, 4, 4294967295});
  //  test_list<long long>({0, 1, -2147483648, 4, 2147483647});
  //  test_list<unsigned long long>({0, 1, 0, 4, 4294967295});
  //  test_list<float>({0, 1, FLT_MIN, -FLT_MAX, FLT_MAX});
  //  test_list<double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
  //  test_list<long double>({0, 1, DBL_MIN, -DBL_MAX, DBL_MAX});
}
