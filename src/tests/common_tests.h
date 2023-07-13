#include <set>

#include "../s21_set_containers/s21_set.h"

using namespace s21;

template <class T>
void is_equal(set<T> &x, std::set<T> &x_orig) {
  ASSERT_EQ(x.size(), x_orig.size());
  for (std::pair<typename std::set<T>::iterator, typename s21::set<T>::iterator>
           i(x_orig.begin(), x.begin());
       (i.first != x_orig.end() && i.second != x.end()); ++i.first, ++i.second)
    ASSERT_EQ((*i.first), (*i.second));
}
