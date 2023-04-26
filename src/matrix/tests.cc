#include <gtest/gtest.h>

#include "./s21_matrix_oop.h"

using namespace std;

void ExpectConst(S21Matrix const const_matrix0, S21Matrix const const_matrix1) {
  for (auto i = 0; i < const_matrix0.GetRows(); i++) {
    for (auto j = 0; j < const_matrix0.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(const_matrix0(i, j), const_matrix1(i, j));
    }
  }
}

TEST(TestS21Matrix, S21Matrix) {
  S21Matrix matrix0;
  EXPECT_EQ(0, matrix0.GetRows());
  EXPECT_EQ(0, matrix0.GetColumns());

  S21Matrix const const_matrix0;
  EXPECT_EQ(0, const_matrix0.GetRows());
  EXPECT_EQ(0, const_matrix0.GetColumns());

  S21Matrix matrix1(2, 3);
  EXPECT_EQ(2, matrix1.GetRows());
  EXPECT_EQ(3, matrix1.GetColumns());
  matrix1(0, 0) = 0.1;
  matrix1(0, 1) = 0.2;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 0.4;
  matrix1(1, 1) = 0.5;
  matrix1(1, 2) = 0.6;
  EXPECT_EQ(0.1, matrix1(0, 0));
  EXPECT_EQ(0.2, matrix1(0, 1));
  EXPECT_EQ(0.3, matrix1(0, 2));
  EXPECT_EQ(0.4, matrix1(1, 0));
  EXPECT_EQ(0.5, matrix1(1, 1));
  EXPECT_EQ(0.6, matrix1(1, 2));

  S21Matrix const const_matrix1(2, 3);
  EXPECT_EQ(2, const_matrix1.GetRows());
  EXPECT_EQ(3, const_matrix1.GetColumns());
  EXPECT_EQ(0.0, const_matrix1(0, 0));
  EXPECT_EQ(0.0, const_matrix1(0, 1));
  EXPECT_EQ(0.0, const_matrix1(0, 2));
  EXPECT_EQ(0.0, const_matrix1(1, 0));
  EXPECT_EQ(0.0, const_matrix1(1, 1));
  EXPECT_EQ(0.0, const_matrix1(1, 2));

  S21Matrix matrix2(matrix1);
  EXPECT_EQ(2, matrix1.GetRows());
  EXPECT_EQ(3, matrix1.GetColumns());
  EXPECT_EQ(0.1, matrix1(0, 0));
  EXPECT_EQ(0.2, matrix1(0, 1));
  EXPECT_EQ(0.3, matrix1(0, 2));
  EXPECT_EQ(0.4, matrix1(1, 0));
  EXPECT_EQ(0.5, matrix1(1, 1));
  EXPECT_EQ(0.6, matrix1(1, 2));
  EXPECT_EQ(2, matrix2.GetRows());
  EXPECT_EQ(3, matrix2.GetColumns());
  EXPECT_EQ(0.1, matrix2(0, 0));
  EXPECT_EQ(0.2, matrix2(0, 1));
  EXPECT_EQ(0.3, matrix2(0, 2));
  EXPECT_EQ(0.4, matrix2(1, 0));
  EXPECT_EQ(0.5, matrix2(1, 1));
  EXPECT_EQ(0.6, matrix2(1, 2));

  S21Matrix const const_matrix2(matrix1);
  EXPECT_EQ(2, const_matrix2.GetRows());
  EXPECT_EQ(3, const_matrix2.GetColumns());
  EXPECT_EQ(0.1, const_matrix2(0, 0));
  EXPECT_EQ(0.2, const_matrix2(0, 1));
  EXPECT_EQ(0.3, const_matrix2(0, 2));
  EXPECT_EQ(0.4, const_matrix2(1, 0));
  EXPECT_EQ(0.5, const_matrix2(1, 1));
  EXPECT_EQ(0.6, const_matrix2(1, 2));
  S21Matrix const const_matrix22(const_matrix2);

  S21Matrix matrix3(move(matrix2));
  EXPECT_EQ(0, matrix2.GetRows());
  EXPECT_EQ(0, matrix2.GetColumns());
  EXPECT_EQ(2, matrix3.GetRows());
  EXPECT_EQ(3, matrix3.GetColumns());
  EXPECT_EQ(0.1, matrix3(0, 0));
  EXPECT_EQ(0.2, matrix3(0, 1));
  EXPECT_EQ(0.3, matrix3(0, 2));
  EXPECT_EQ(0.4, matrix3(1, 0));
  EXPECT_EQ(0.5, matrix3(1, 1));
  EXPECT_EQ(0.6, matrix3(1, 2));

  S21Matrix const const_matrix3(move(matrix3));
  EXPECT_EQ(2, const_matrix3.GetRows());
  EXPECT_EQ(3, const_matrix3.GetColumns());
  EXPECT_EQ(0.1, const_matrix3(0, 0));
  EXPECT_EQ(0.2, const_matrix3(0, 1));
  EXPECT_EQ(0.3, const_matrix3(0, 2));
  EXPECT_EQ(0.4, const_matrix3(1, 0));
  EXPECT_EQ(0.5, const_matrix3(1, 1));
  EXPECT_EQ(0.6, const_matrix3(1, 2));

  EXPECT_THROW(S21Matrix matrix4(-2, 3), invalid_argument);
  try {
    S21Matrix matrix4(-2, 3);
  } catch (const invalid_argument &e) {
    EXPECT_STREQ("Incorrect input, value of rows is less than zero", e.what());
  }
  EXPECT_THROW(S21Matrix matrix4(2, -3), invalid_argument);
  try {
    S21Matrix matrix4(2, -3);
  } catch (const invalid_argument &e) {
    EXPECT_STREQ("Incorrect input, value of columns is less than zero",
                 e.what());
  }
}

TEST(TestS21Matrix, Mutators) {
  S21Matrix matrix;

  matrix.SetRows(1);
  EXPECT_EQ(1, matrix.GetRows());
  matrix.SetRows(0);
  EXPECT_EQ(0, matrix.GetRows());
  matrix.SetColumns(1);
  EXPECT_EQ(1, matrix.GetColumns());
  matrix.SetColumns(0);
  EXPECT_EQ(0, matrix.GetColumns());
  matrix.SetRows(1);
  EXPECT_EQ(1, matrix.GetRows());
  matrix.SetColumns(2);
  EXPECT_EQ(2, matrix.GetColumns());
  EXPECT_EQ(0.0, matrix(0, 0));
  EXPECT_EQ(0.0, matrix(0, 1));

  matrix(0, 0) = 0.1;
  matrix(0, 1) = 0.2;
  matrix.SetRows(2);
  EXPECT_EQ(2, matrix.GetRows());
  EXPECT_EQ(0.0, matrix(1, 0));
  EXPECT_EQ(0.0, matrix(1, 1));
  matrix.SetColumns(3);
  EXPECT_EQ(3, matrix.GetColumns());
  EXPECT_EQ(0.1, matrix(0, 0));
  EXPECT_EQ(0.2, matrix(0, 1));
  EXPECT_EQ(0.0, matrix(0, 2));
  EXPECT_EQ(0.0, matrix(1, 0));
  EXPECT_EQ(0.0, matrix(1, 1));
  EXPECT_EQ(0.0, matrix(1, 2));
  matrix(0, 2) = 0.3;
  matrix(1, 0) = 0.4;
  matrix(1, 1) = 0.5;
  matrix(1, 2) = 0.6;

  matrix.SetColumns(2);
  EXPECT_EQ(2, matrix.GetColumns());
  EXPECT_EQ(0.1, matrix(0, 0));
  EXPECT_EQ(0.2, matrix(0, 1));
  EXPECT_EQ(0.4, matrix(1, 0));
  EXPECT_EQ(0.5, matrix(1, 1));

  matrix.SetRows(1);
  EXPECT_EQ(1, matrix.GetRows());
  matrix(0, 0) = 0.1;
  matrix(0, 1) = 0.2;

  matrix.SetRows(100);
  EXPECT_EQ(100, matrix.GetRows());
  matrix.SetColumns(20);
  EXPECT_EQ(20, matrix.GetColumns());
  matrix.SetRows(0);
  EXPECT_EQ(0, matrix.GetRows());
  EXPECT_EQ(0, matrix.GetColumns());

  matrix.SetRows(100);
  EXPECT_EQ(100, matrix.GetRows());
  matrix.SetColumns(20);
  EXPECT_EQ(20, matrix.GetColumns());
  matrix.SetColumns(0);
  EXPECT_EQ(0, matrix.GetColumns());
  EXPECT_EQ(0, matrix.GetRows());

  EXPECT_THROW(matrix.SetRows(-1), invalid_argument);
  try {
    matrix.SetRows(-1);
  } catch (const invalid_argument &e) {
    EXPECT_STREQ("Incorrect input, value of rows is less than zero", e.what());
  }
  EXPECT_THROW(matrix.SetColumns(-1), invalid_argument);
  try {
    matrix.SetColumns(-1);
  } catch (const invalid_argument &e) {
    EXPECT_STREQ("Incorrect input, value of columns is less than zero",
                 e.what());
  }
}

TEST(TestS21Matrix, EqMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 0.1;
  matrix1(0, 1) = 0.2;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 0.4;
  matrix1(1, 1) = 0.5;
  matrix1(1, 2) = 0.6;
  S21Matrix matrix2(matrix1);

  S21Matrix const const_matrix0(matrix1);
  S21Matrix const const_matrix1(matrix1);
  S21Matrix const const_matrix2(matrix1);

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
  EXPECT_TRUE(const_matrix1.EqMatrix(const_matrix2));
  ExpectConst(const_matrix0, const_matrix1);
  ExpectConst(const_matrix0, const_matrix2);

  matrix2.SetColumns(2);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));

  matrix2.SetColumns(3);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  matrix2(0, 2) = 0.3;
  matrix2(1, 2) = 0.6;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));

  matrix2.SetRows(1);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  matrix2.SetRows(2);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  matrix2(1, 0) = 0.4;
  matrix2(1, 1) = 0.5;
  matrix2(1, 2) = 0.6;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));

  matrix1(0, 0) = __builtin_nan("");
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  matrix2(0, 0) = __builtin_nan("");
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
  matrix1(0, 0) = -__builtin_nan("");
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  matrix2(0, 0) = -__builtin_nan("");
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
  matrix1(0, 0) = __builtin_inf();
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  matrix2(0, 0) = __builtin_inf();
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
  matrix1(0, 0) = -__builtin_inf();
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
  matrix2(0, 0) = -__builtin_inf();
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(TestS21Matrix, SumMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 0.1;
  matrix1(0, 1) = 0.2;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 0.4;
  matrix1(1, 1) = 0.5;
  matrix1(1, 2) = 0.6;
  S21Matrix matrix2(matrix1);

  S21Matrix const const_matrix0(matrix1);
  S21Matrix const const_matrix1(matrix1);

  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(0.2, matrix1(0, 0));
  EXPECT_EQ(0.4, matrix1(0, 1));
  EXPECT_EQ(0.6, matrix1(0, 2));
  EXPECT_EQ(0.8, matrix1(1, 0));
  EXPECT_EQ(1.0, matrix1(1, 1));
  EXPECT_EQ(1.2, matrix1(1, 2));
  EXPECT_EQ(0.1, matrix2(0, 0));
  EXPECT_EQ(0.2, matrix2(0, 1));
  EXPECT_EQ(0.3, matrix2(0, 2));
  EXPECT_EQ(0.4, matrix2(1, 0));
  EXPECT_EQ(0.5, matrix2(1, 1));
  EXPECT_EQ(0.6, matrix2(1, 2));

  matrix1.SumMatrix(const_matrix1);
  ExpectConst(const_matrix0, const_matrix1);

  matrix1(0, 0) = __builtin_nan("");
  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isnan(matrix1(0, 0)));
  EXPECT_EQ(false, __builtin_signbit(matrix1(0, 0)));
  matrix1(0, 0) = -__builtin_nan("");
  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isnan(matrix1(0, 0)));
  EXPECT_EQ(true, __builtin_signbit(matrix1(0, 0)));
  matrix1(0, 0) = __builtin_inf();
  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isinf(matrix1(0, 0)));
  EXPECT_EQ(false, __builtin_signbit(matrix1(0, 0)));
  matrix1(0, 0) = -__builtin_inf();
  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isinf(matrix1(0, 0)));
  EXPECT_EQ(true, __builtin_signbit(matrix1(0, 0)));

  matrix1(0, 0) = 0.2;
  matrix1(0, 1) = 0.4;
  matrix1(0, 2) = 0.6;
  matrix1(1, 0) = 0.8;
  matrix1(1, 1) = 1.0;
  matrix1(1, 2) = 1.2;

  S21Matrix matrix3(3, 3);
  EXPECT_THROW(matrix1.SumMatrix(matrix3), logic_error);
  try {
    matrix1.SumMatrix(matrix3);
  } catch (const logic_error &e) {
    EXPECT_STREQ("Incorrect input, different matrix dimensions", e.what());
  }
  EXPECT_EQ(0.2, matrix1(0, 0));
  EXPECT_EQ(0.4, matrix1(0, 1));
  EXPECT_EQ(0.6, matrix1(0, 2));
  EXPECT_EQ(0.8, matrix1(1, 0));
  EXPECT_EQ(1.0, matrix1(1, 1));
  EXPECT_EQ(1.2, matrix1(1, 2));

  S21Matrix matrix4(2, 2);
  EXPECT_THROW(matrix1.SumMatrix(matrix4), logic_error);
  try {
    matrix1.SumMatrix(matrix4);
  } catch (const logic_error &e) {
    EXPECT_STREQ("Incorrect input, different matrix dimensions", e.what());
  }
  EXPECT_EQ(0.2, matrix1(0, 0));
  EXPECT_EQ(0.4, matrix1(0, 1));
  EXPECT_EQ(0.6, matrix1(0, 2));
  EXPECT_EQ(0.8, matrix1(1, 0));
  EXPECT_EQ(1.0, matrix1(1, 1));
  EXPECT_EQ(1.2, matrix1(1, 2));
}

TEST(TestS21Matrix, SubMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 0.1;
  matrix1(0, 1) = 0.2;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 0.4;
  matrix1(1, 1) = 0.5;
  matrix1(1, 2) = 0.6;
  S21Matrix matrix2(matrix1);

  S21Matrix const const_matrix0(matrix1);
  S21Matrix const const_matrix1(matrix1);

  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(0.0, matrix1(0, 0));
  EXPECT_EQ(0.0, matrix1(0, 1));
  EXPECT_EQ(0.0, matrix1(0, 2));
  EXPECT_EQ(0.0, matrix1(1, 0));
  EXPECT_EQ(0.0, matrix1(1, 1));
  EXPECT_EQ(0.0, matrix1(1, 2));
  EXPECT_EQ(0.1, matrix2(0, 0));
  EXPECT_EQ(0.2, matrix2(0, 1));
  EXPECT_EQ(0.3, matrix2(0, 2));
  EXPECT_EQ(0.4, matrix2(1, 0));
  EXPECT_EQ(0.5, matrix2(1, 1));
  EXPECT_EQ(0.6, matrix2(1, 2));

  matrix1.SubMatrix(const_matrix1);
  ExpectConst(const_matrix0, const_matrix1);

  matrix1(0, 0) = __builtin_nan("");
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isnan(matrix1(0, 0)));
  EXPECT_EQ(false, __builtin_signbit(matrix1(0, 0)));
  matrix1(0, 0) = -__builtin_nan("");
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isnan(matrix1(0, 0)));
  EXPECT_EQ(true, __builtin_signbit(matrix1(0, 0)));
  matrix1(0, 0) = __builtin_inf();
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isinf(matrix1(0, 0)));
  EXPECT_EQ(false, __builtin_signbit(matrix1(0, 0)));
  matrix1(0, 0) = -__builtin_inf();
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isinf(matrix1(0, 0)));
  EXPECT_EQ(true, __builtin_signbit(matrix1(0, 0)));

  matrix1(0, 0) = 0.0;
  matrix1(0, 1) = 0.0;
  matrix1(0, 2) = 0.0;
  matrix1(1, 0) = 0.0;
  matrix1(1, 1) = 0.0;
  matrix1(1, 2) = 0.0;

  matrix2(0, 0) = __builtin_nan("");
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isnan(matrix1(0, 0)));
  EXPECT_EQ(false, __builtin_signbit(matrix1(0, 0)));
  matrix2(0, 0) = -__builtin_nan("");
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isnan(matrix1(0, 0)));
  EXPECT_EQ(false, __builtin_signbit(matrix1(0, 0)));
  matrix2(0, 0) = __builtin_inf();
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isnan(matrix1(0, 0)));
  EXPECT_EQ(false, __builtin_signbit(matrix1(0, 0)));
  matrix2(0, 0) = -__builtin_inf();
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(true, __builtin_isnan(matrix1(0, 0)));
  EXPECT_EQ(false, __builtin_signbit(matrix1(0, 0)));

  matrix1(0, 0) = 0.0;
  matrix1(0, 1) = 0.0;
  matrix1(0, 2) = 0.0;
  matrix1(1, 0) = 0.0;
  matrix1(1, 1) = 0.0;
  matrix1(1, 2) = 0.0;
  matrix2(0, 0) = 0.1;

  S21Matrix matrix3(3, 3);
  EXPECT_THROW(matrix1.SubMatrix(matrix3), logic_error);
  try {
    matrix1.SubMatrix(matrix3);
  } catch (const logic_error &e) {
    EXPECT_STREQ("Incorrect input, different matrix dimensions", e.what());
  }
  EXPECT_EQ(0.0, matrix1(0, 0));
  EXPECT_EQ(0.0, matrix1(0, 1));
  EXPECT_EQ(0.0, matrix1(0, 2));
  EXPECT_EQ(0.0, matrix1(1, 0));
  EXPECT_EQ(0.0, matrix1(1, 1));
  EXPECT_EQ(0.0, matrix1(1, 2));

  S21Matrix matrix4(2, 2);
  EXPECT_THROW(matrix1.SubMatrix(matrix4), logic_error);
  try {
    matrix1.SubMatrix(matrix4);
  } catch (const logic_error &e) {
    EXPECT_STREQ("Incorrect input, different matrix dimensions", e.what());
  }
  EXPECT_EQ(0.0, matrix1(0, 0));
  EXPECT_EQ(0.0, matrix1(0, 1));
  EXPECT_EQ(0.0, matrix1(0, 2));
  EXPECT_EQ(0.0, matrix1(1, 0));
  EXPECT_EQ(0.0, matrix1(1, 1));
  EXPECT_EQ(0.0, matrix1(1, 2));
}

TEST(TestS21Matrix, MulNumber) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 0.1;
  matrix1(0, 1) = 0.2;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 0.4;
  matrix1(1, 1) = 0.5;
  matrix1(1, 2) = 0.6;

  matrix1.MulNumber(2);
  EXPECT_EQ(0.2, matrix1(0, 0));
  EXPECT_EQ(0.4, matrix1(0, 1));
  EXPECT_EQ(0.6, matrix1(0, 2));
  EXPECT_EQ(0.8, matrix1(1, 0));
  EXPECT_EQ(1.0, matrix1(1, 1));
  EXPECT_EQ(1.2, matrix1(1, 2));

  matrix1.MulNumber(__builtin_nan(""));
  for (auto i = 0; i < matrix1.GetRows(); i++)
    for (auto j = 0; j < matrix1.GetColumns(); j++) {
      EXPECT_EQ(true, __builtin_isnan(matrix1(i, j)));
      EXPECT_EQ(false, __builtin_signbit(matrix1(i, j)));
    }
  matrix1(0, 0) = 0.1;
  matrix1(0, 1) = 0.2;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 0.4;
  matrix1(1, 1) = 0.5;
  matrix1(1, 2) = 0.6;

  matrix1.MulNumber(-__builtin_nan(""));
  for (auto i = 0; i < matrix1.GetRows(); i++)
    for (auto j = 0; j < matrix1.GetColumns(); j++) {
      EXPECT_EQ(true, __builtin_isnan(matrix1(i, j)));
      EXPECT_EQ(true, __builtin_signbit(matrix1(i, j)));
    }
  matrix1(0, 0) = 0.1;
  matrix1(0, 1) = 0.2;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 0.4;
  matrix1(1, 1) = 0.5;
  matrix1(1, 2) = 0.6;

  matrix1.MulNumber(__builtin_inf());
  for (auto i = 0; i < matrix1.GetRows(); i++)
    for (auto j = 0; j < matrix1.GetColumns(); j++) {
      EXPECT_EQ(true, __builtin_isinf(matrix1(i, j)));
      EXPECT_EQ(false, __builtin_signbit(matrix1(i, j)));
    }
  matrix1(0, 0) = 0.1;
  matrix1(0, 1) = 0.2;
  matrix1(0, 2) = 0.3;
  matrix1(1, 0) = 0.4;
  matrix1(1, 1) = 0.5;
  matrix1(1, 2) = 0.6;

  matrix1.MulNumber(-__builtin_inf());
  for (auto i = 0; i < matrix1.GetRows(); i++)
    for (auto j = 0; j < matrix1.GetColumns(); j++) {
      EXPECT_EQ(true, __builtin_isinf(matrix1(i, j)));
      EXPECT_EQ(true, __builtin_signbit(matrix1(i, j)));
    }
}

TEST(TestS21Matrix, MulMatrix) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 5.474748;
  matrix1(0, 1) = -23.365346;
  matrix1(0, 2) = 7.464645;
  matrix1(1, 0) = 13.235363;
  matrix1(1, 1) = -17.326774;
  matrix1(1, 2) = -0.000034;
  matrix1(2, 0) = -12.235567;
  matrix1(2, 1) = 11.124526;
  matrix1(2, 2) = 5.325634;

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 15.352534;
  matrix2(0, 1) = 143.532636;
  matrix2(0, 2) = 345.35356;
  matrix2(1, 0) = 124.523552;
  matrix2(1, 1) = -654.234562;
  matrix2(1, 2) = 123.353578;
  matrix2(2, 0) = -245.636465;
  matrix2(2, 1) = 6324.235523;
  matrix2(2, 2) = -2353.632542;

  S21Matrix const const_matrix0(matrix1);
  S21Matrix const const_matrix1(matrix1);

  matrix1.MulMatrix(matrix2);
  matrix2(0, 0) = -4659.073633097;
  matrix2(0, 1) = 63280.394993749;
  matrix2(0, 2) = -18560.506704883;
  matrix2(1, 0) = -1954.386731082;
  matrix2(1, 1) = 13235.265914562;
  matrix2(1, 2) = 2433.640185351;
  matrix2(2, 0) = -110.751376184;
  matrix2(2, 1) = 24646.311145764;
  matrix2(2, 2) = -15387.932025596;
  for (int i = 0; i < matrix2.GetRows(); i++)
    for (int j = 0; j < matrix2.GetColumns(); j++)
      EXPECT_NEAR(matrix1(i, j), matrix2(i, j), 1.0e-7);

  matrix1.MulMatrix(const_matrix1);
  ExpectConst(const_matrix0, const_matrix1);

  matrix1.SetRows(2);
  matrix1.SetColumns(5);
  matrix1(0, 0) = 0.0;
  matrix1(0, 1) = 1.123456;
  matrix1(0, 2) = 2.469134;
  matrix1(0, 3) = 3.703701;
  matrix1(0, 4) = 4.938268;
  matrix1(1, 0) = 6.172835;
  matrix1(1, 1) = 7.407402;
  matrix1(1, 2) = 8.641969;
  matrix1(1, 3) = 9.876536;
  matrix1(1, 4) = 11.11110;

  matrix2.SetRows(5);
  matrix2.SetColumns(2);
  matrix2(0, 0) = 0.0;
  matrix2(0, 1) = 1.123456;
  matrix2(1, 0) = 2.469134;
  matrix2(1, 1) = 3.703701;
  matrix2(2, 0) = 4.938268;
  matrix2(2, 1) = 6.172835;
  matrix2(3, 0) = 7.407402;
  matrix2(3, 1) = 8.641969;
  matrix2(4, 0) = 9.876536;
  matrix2(4, 1) = 11.11110;

  matrix1.MulMatrix(matrix2);
  EXPECT_NEAR(matrix1(0, 0), 91.174992, 1.0e-6);
  EXPECT_NEAR(matrix1(0, 1), 106.279360, 1.0e-6);
  EXPECT_NEAR(matrix1(1, 0), 243.864878, 1.0e-6);
  EXPECT_NEAR(matrix1(1, 1), 296.524420, 1.0e-6);

  matrix1.SetRows(2);
  matrix1.SetColumns(5);
  matrix1(0, 0) = 0.0;
  matrix1(0, 1) = 1.123456;
  matrix1(0, 2) = 2.469134;
  matrix1(0, 3) = 3.703701;
  matrix1(0, 4) = 4.938268;
  matrix1(1, 0) = 6.172835;
  matrix1(1, 1) = 7.407402;
  matrix1(1, 2) = 8.641969;
  matrix1(1, 3) = 9.876536;
  matrix1(1, 4) = 11.11110;

  matrix2.SetRows(5);
  matrix2.SetColumns(1);
  matrix2(0, 0) = 0.0;
  matrix2(1, 0) = 2.469134;
  matrix2(2, 0) = 4.938268;
  matrix2(3, 0) = 7.407402;
  matrix2(4, 0) = 9.876536;

  matrix1.MulMatrix(matrix2);
  EXPECT_NEAR(matrix1(0, 0), 91.174992, 1.0e-6);
  EXPECT_NEAR(matrix1(1, 0), 243.864878, 1.0e-6);

  matrix1.SetColumns(4);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), logic_error);
  try {
    matrix1.MulMatrix(matrix2);
  } catch (const logic_error &e) {
    EXPECT_STREQ(
        "Incorrect input, the number of columns of the first matrix does not "
        "equal the number of rows of the second matrix",
        e.what());
  }

  matrix1.SetColumns(5);
  matrix2.SetRows(4);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), logic_error);
  try {
    matrix1.MulMatrix(matrix2);
  } catch (const logic_error &e) {
    EXPECT_STREQ(
        "Incorrect input, the number of columns of the first matrix does not "
        "equal the number of rows of the second matrix",
        e.what());
  }
}

TEST(TestS21Matrix, Transpose) {
  S21Matrix matrix1;
  S21Matrix matrix2 = S21Matrix(3, 3);

  matrix1 = matrix2;
  for (auto i = 0, k = 0; i < matrix1.GetRows(); i++)
    for (auto j = 0; j < matrix1.GetColumns(); j++) matrix1(i, j) = k++;
  matrix2(0, 0) = 0.0;
  matrix2(0, 1) = 3.0;
  matrix2(0, 2) = 6.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 4.0;
  matrix2(1, 2) = 7.0;
  matrix2(2, 0) = 2.0;
  matrix2(2, 1) = 5.0;
  matrix2(2, 2) = 8.0;

  S21Matrix const const_matrix0(matrix1);
  S21Matrix const const_matrix1(matrix1);

  matrix1 = matrix1.Transpose();
  for (auto i = 0; i < matrix2.GetRows(); i++) {
    for (auto j = 0; j < matrix2.GetColumns(); j++) {
      EXPECT_NEAR(matrix1(i, j), matrix2(i, j), 1.0e-7);
    }
  }

  matrix1 = const_matrix1.Transpose();
  ExpectConst(const_matrix0, const_matrix1);

  matrix1.SetRows(2);
  matrix1.SetColumns(5);
  matrix2.SetRows(5);
  matrix2.SetColumns(2);
  for (auto i = 0, k = 0; i < matrix1.GetRows(); i++)
    for (auto j = 0; j < matrix1.GetColumns(); j++) matrix1(i, j) = k++ / 10.0;
  matrix2(0, 0) = 0.0;
  matrix2(0, 1) = 0.5;
  matrix2(1, 0) = 0.1;
  matrix2(1, 1) = 0.6;
  matrix2(2, 0) = 0.2;
  matrix2(2, 1) = 0.7;
  matrix2(3, 0) = 0.3;
  matrix2(3, 1) = 0.8;
  matrix2(4, 0) = 0.4;
  matrix2(4, 1) = 0.9;
  matrix1 = matrix1.Transpose();
  for (auto i = 0; i < matrix2.GetRows(); i++) {
    for (auto j = 0; j < matrix2.GetColumns(); j++) {
      EXPECT_NEAR(matrix1(i, j), matrix2(i, j), 1.0e-7);
    }
  }
}

TEST(TestS21Matrix, CalcComplements) {
  S21Matrix result;
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 4.0;
  matrix(1, 2) = 2.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = 2.0;
  matrix(2, 2) = 1.0;

  S21Matrix const const_matrix0(matrix);
  S21Matrix const const_matrix1(matrix);

  result = matrix.CalcComplements();
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 10.0;
  matrix(0, 2) = -20.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = -14.0;
  matrix(1, 2) = 8.0;
  matrix(2, 0) = -8.0;
  matrix(2, 1) = -2.0;
  matrix(2, 2) = 4.0;
  for (auto i = 0; i < matrix.GetRows(); i++) {
    for (auto j = 0; j < matrix.GetColumns(); j++) {
      EXPECT_NEAR(result(i, j), matrix(i, j), 1.0e-7);
    }
  }

  result = const_matrix1.CalcComplements();
  ExpectConst(const_matrix0, const_matrix1);

  matrix(0, 0) = __builtin_nan("");
  matrix.CalcComplements();
  matrix(0, 0) = __builtin_inf();
  matrix.CalcComplements();
  matrix(0, 0) = -__builtin_nan("");
  matrix.CalcComplements();
  matrix(0, 0) = -__builtin_inf();
  matrix.CalcComplements();

  matrix.SetRows(2);
  EXPECT_THROW(matrix.CalcComplements(), logic_error);
  try {
    matrix.CalcComplements();
  } catch (const logic_error &e) {
    EXPECT_STREQ("Incorrect input, the matrix is not square", e.what());
  }
  matrix.SetRows(0);
  EXPECT_THROW(matrix.CalcComplements(), logic_error);
  try {
    matrix.CalcComplements();
  } catch (const logic_error &e) {
    EXPECT_STREQ("Incorrect input, the matrix is not square", e.what());
  }

  matrix.SetRows(1);
  matrix.SetColumns(1);
  result = matrix.CalcComplements();
  for (auto i = 0; i < matrix.GetRows(); i++) {
    for (auto j = 0; j < matrix.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), 0.0);
    }
  }
}

TEST(TestS21Matrix, Determinant) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 0.0;
  matrix(0, 1) = 9.0;
  matrix(0, 2) = 5.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 3.0;
  matrix(1, 2) = -5.0;
  matrix(2, 0) = -1.0;
  matrix(2, 1) = 6.0;
  matrix(2, 2) = -4.0;

  S21Matrix const const_matrix0(matrix);
  S21Matrix const const_matrix1(matrix);

  EXPECT_DOUBLE_EQ(324.0, matrix.Determinant());

  EXPECT_DOUBLE_EQ(324.0, const_matrix1.Determinant());
  ExpectConst(const_matrix0, const_matrix1);

  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(0, 2) = 5.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 0.0;
  matrix(1, 2) = -5.0;
  matrix(2, 0) = -1.0;
  matrix(2, 1) = 0.0;
  matrix(2, 2) = -4.0;
  EXPECT_DOUBLE_EQ(0.0, matrix.Determinant());

  matrix(0, 0) = 0.0;
  matrix(0, 1) = 0.0;
  matrix(0, 2) = 0.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 3.0;
  matrix(1, 2) = -5.0;
  matrix(2, 0) = -1.0;
  matrix(2, 1) = 6.0;
  matrix(2, 2) = -4.0;
  EXPECT_DOUBLE_EQ(0.0, matrix.Determinant());

  matrix(0, 0) = __builtin_nan("");
  matrix.Determinant();
  matrix(0, 0) = __builtin_inf();
  matrix.Determinant();
  matrix(0, 0) = -__builtin_nan("");
  matrix.Determinant();
  matrix(0, 0) = -__builtin_inf();
  matrix.Determinant();

  matrix.SetRows(2);
  EXPECT_THROW(matrix.Determinant(), logic_error);
  try {
    matrix.Determinant();
  } catch (const logic_error &e) {
    EXPECT_STREQ("Incorrect input, the matrix is not square", e.what());
  }
  matrix.SetRows(0);
  EXPECT_THROW(matrix.Determinant(), logic_error);
  try {
    matrix.Determinant();
  } catch (const logic_error &e) {
    EXPECT_STREQ("Incorrect input, the matrix is not square", e.what());
  }

  matrix.SetRows(1);
  matrix.SetColumns(1);
  matrix(0, 0) = 10.0;
  EXPECT_DOUBLE_EQ(10.0, matrix.Determinant());
}

TEST(TestS21Matrix, InverseMatrix) {
  S21Matrix result;
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 5.0;
  matrix(0, 2) = 7.0;
  matrix(1, 0) = 6.0;
  matrix(1, 1) = 3.0;
  matrix(1, 2) = 4.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = -2.0;
  matrix(2, 2) = -3.0;

  S21Matrix const const_matrix0(matrix);
  S21Matrix const const_matrix1(matrix);

  result = matrix.InverseMatrix();
  matrix(0, 0) = 1.0;
  matrix(0, 1) = -1.0;
  matrix(0, 2) = 1.0;
  matrix(1, 0) = -38.0;
  matrix(1, 1) = 41.0;
  matrix(1, 2) = -34.0;
  matrix(2, 0) = 27.0;
  matrix(2, 1) = -29.0;
  matrix(2, 2) = 24.0;
  for (auto i = 0; i < matrix.GetRows(); i++)
    for (auto j = 0; j < matrix.GetColumns(); j++)
      EXPECT_NEAR(matrix(i, j), result(i, j), 1.0e-7);

  result = const_matrix1.InverseMatrix();
  ExpectConst(const_matrix0, const_matrix1);

  matrix(0, 0) = 0.0;
  matrix(0, 1) = 5.0;
  matrix(0, 2) = 7.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 3.0;
  matrix(1, 2) = 4.0;
  matrix(2, 0) = 0.0;
  matrix(2, 1) = -2.0;
  matrix(2, 2) = -3.0;
  EXPECT_THROW(matrix.InverseMatrix(), logic_error);
  try {
    matrix.InverseMatrix();
  } catch (const logic_error &e) {
    EXPECT_STREQ("matrix determinant is 0", e.what());
  }

  matrix(0, 0) = 1.23;
  matrix(0, 1) = -57.123;
  matrix(0, 2) = 234.89;
  matrix(1, 0) = 1.123456;
  matrix(1, 1) = 0.32;
  matrix(1, 2) = 1234.78;
  matrix(2, 0) = -90;
  matrix(2, 1) = 120.1;
  matrix(2, 2) = 0.0;
  result = matrix.InverseMatrix();
  result.MulMatrix(matrix);
  for (auto i = 0; i < matrix.GetRows(); i++)
    for (auto j = 0; j < matrix.GetColumns(); j++) {
      if (i == j)
        EXPECT_NEAR(1.0, result(i, j), 1.0e-7);
      else
        EXPECT_NEAR(0.0, result(i, j), 1.0e-7);
    }

  matrix(0, 0) = __builtin_nan("");
  matrix.InverseMatrix();
  matrix(0, 0) = __builtin_inf();
  matrix.InverseMatrix();
  matrix(0, 0) = -__builtin_nan("");
  matrix.InverseMatrix();
  matrix(0, 0) = -__builtin_inf();
  matrix.InverseMatrix();
}

TEST(TestS21Matrix, Operators) {
  S21Matrix result(2, 5);

  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 5.474748;
  matrix1(0, 1) = -23.365346;
  matrix1(0, 2) = 7.464645;
  matrix1(1, 0) = 13.235363;
  matrix1(1, 1) = -17.326774;
  matrix1(1, 2) = -0.000034;
  matrix1(2, 0) = -12.235567;
  matrix1(2, 1) = 11.124526;
  matrix1(2, 2) = 5.325634;

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 15.352534;
  matrix2(0, 1) = 143.532636;
  matrix2(0, 2) = 345.35356;
  matrix2(1, 0) = 124.523552;
  matrix2(1, 1) = -654.234562;
  matrix2(1, 2) = 123.353578;
  matrix2(2, 0) = -245.636465;
  matrix2(2, 1) = 6324.235523;
  matrix2(2, 2) = -2353.632542;

  S21Matrix const const_matrix01(matrix1);
  S21Matrix const const_matrix02(matrix2);
  S21Matrix const const_matrix1(matrix1);
  S21Matrix const const_matrix2(matrix2);

  result = matrix1 + matrix2;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), matrix1(i, j) + matrix2(i, j));
    }
  }

  result = const_matrix1 + const_matrix2;
  ExpectConst(const_matrix01, const_matrix1);
  ExpectConst(const_matrix02, const_matrix2);

  result = matrix1 - matrix2;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), matrix1(i, j) - matrix2(i, j));
    }
  }

  result = const_matrix1 - const_matrix2;
  ExpectConst(const_matrix01, const_matrix1);
  ExpectConst(const_matrix02, const_matrix2);

  result = matrix1 * matrix2;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), (matrix1 * matrix2)(i, j));
    }
  }

  result = const_matrix1 * const_matrix2;
  ExpectConst(const_matrix01, const_matrix1);
  ExpectConst(const_matrix02, const_matrix2);

  result = matrix1 * 2.5;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), matrix1(i, j) * 2.5);
    }
  }

  result = const_matrix1 * 2.5;
  ExpectConst(const_matrix01, const_matrix1);

  result = 2.5 * matrix1;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), 2.5 * matrix1(i, j));
    }
  }

  result = 2.5 * const_matrix1;
  ExpectConst(const_matrix01, const_matrix1);

  EXPECT_FALSE(matrix1 == matrix2);

  EXPECT_FALSE(const_matrix1 == const_matrix2);
  ExpectConst(const_matrix01, const_matrix1);
  ExpectConst(const_matrix02, const_matrix2);

  matrix1 = result;
  result += matrix2;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), matrix1(i, j) + matrix2(i, j));
    }
  }

  result += const_matrix1;
  ExpectConst(const_matrix01, const_matrix1);

  matrix1 = result;
  result -= matrix2;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), matrix1(i, j) - matrix2(i, j));
    }
  }

  result -= const_matrix1;
  ExpectConst(const_matrix01, const_matrix1);

  matrix1 = result;
  result *= matrix2;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), (matrix1 * matrix2)(i, j));
    }
  }

  result *= const_matrix1;
  ExpectConst(const_matrix01, const_matrix1);

  matrix1 = result;
  result *= 2.5;
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(result(i, j), matrix1(i, j) * 2.5);
    }
  }

  result(0, 0) = 21.11;
  EXPECT_DOUBLE_EQ(21.11, result(0, 0));
  double dbl = result(0, 0);
  EXPECT_DOUBLE_EQ(21.11, dbl);
  double const const_dbl = result(0, 0);
  EXPECT_DOUBLE_EQ(21.11, const_dbl);

  dbl = const_matrix1(0, 0);
  EXPECT_DOUBLE_EQ(const_matrix1(0, 0), dbl);
  double const const_dbl_ = const_matrix1(0, 0);
  EXPECT_DOUBLE_EQ(const_matrix1(0, 0), const_dbl_);
  ExpectConst(const_matrix01, const_matrix1);

  matrix1.SetColumns(5);
  EXPECT_THROW(matrix1 + matrix2, logic_error);
  EXPECT_THROW(matrix1 - matrix2, logic_error);
  EXPECT_THROW(matrix1 * matrix2, logic_error);
  EXPECT_NO_THROW(1.23 * matrix2);
  EXPECT_NO_THROW(matrix1 * 4.56);
  EXPECT_THROW(matrix1 += matrix2, logic_error);
  EXPECT_THROW(matrix1 -= matrix2, logic_error);
  EXPECT_THROW(matrix1 *= matrix2, logic_error);
  EXPECT_NO_THROW(matrix1 *= 4.56);

  EXPECT_THROW(result(-1, 0), out_of_range);
  try {
    result(-1, 0);
  } catch (const out_of_range &e) {
    EXPECT_STREQ("Incorrect input, index is outside the matrix", e.what());
  }
  EXPECT_THROW(result(0, -1), out_of_range);
  try {
    result(0, -1);
  } catch (const out_of_range &e) {
    EXPECT_STREQ("Incorrect input, index is outside the matrix", e.what());
  }
  EXPECT_THROW(result(5, 0), out_of_range);
  try {
    result(5, 0);
  } catch (const out_of_range &e) {
    EXPECT_STREQ("Incorrect input, index is outside the matrix", e.what());
  }
  EXPECT_THROW(result(1, 10), out_of_range);
  try {
    result(1, 10);
  } catch (const out_of_range &e) {
    EXPECT_STREQ("Incorrect input, index is outside the matrix", e.what());
  }

  result = const_matrix1;
  ExpectConst(const_matrix01, const_matrix1);

  matrix1 = result;
  matrix2 = move(result);
  EXPECT_GT(matrix1.GetRows(), 0);
  EXPECT_GT(matrix1.GetColumns(), 0);
  for (auto i = 0; i < matrix1.GetRows(); i++) {
    for (auto j = 0; j < matrix1.GetColumns(); j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), matrix2(i, j));
    }
  }
  EXPECT_EQ(0, result.GetRows());
  EXPECT_EQ(0, result.GetColumns());
}
