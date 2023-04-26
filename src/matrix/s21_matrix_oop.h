#ifndef SRC_S21_MATRIX_OOP_H
#define SRC_S21_MATRIX_OOP_H

#include <stdexcept>

constexpr double EPS = 1e-15;

class S21Matrix {
 public:
  S21Matrix();
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  void SetRows(const int rows);
  void SetColumns(const int columns);
  int GetRows() const noexcept;
  int GetColumns() const noexcept;

  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  friend S21Matrix operator*(const double num, const S21Matrix& other);
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num) noexcept;
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;

 private:
  int rows_ = 0;
  int cols_ = 0;
  double** matrix_ = nullptr;

  void InvalidArgumentRows(const int rows) const;
  void InvalidArgumentCols(const int cols) const;
  void SetPrivateFields_(const int rows, const int cols, double** matrix);
  void CopyMatrix_(const S21Matrix& other) noexcept;
  void DeleteMatrix_() noexcept;
  void SetAnotherRows_(const int rows);
  void SetAnotherColumns_(const int columns);
  bool EqDouble(const double x, const double y) const noexcept;
  void DifferentMatrixDimensions_(const S21Matrix& other) const;
  void CheckNull_(double& value) const noexcept;
  void MatrixIsNotSquare_() const;
  S21Matrix Minor_(const int row, const int column) const;
  int Gauss_(double& res) noexcept;
  int GaussMaxRow_(const int j) noexcept;
  void IndexIsOutsideTheMatrix_(const int i, const int j) const;
};

#endif  // SRC_S21_MATRIX_OOP_H
