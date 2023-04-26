#include "./s21_matrix_oop.h"

S21Matrix::S21Matrix() {}

S21Matrix::S21Matrix(int rows, int cols) {
  InvalidArgumentRows(rows);
  InvalidArgumentCols(cols);

  SetPrivateFields_(rows, cols, nullptr);
}

S21Matrix::S21Matrix(const S21Matrix& other) { *this = other; }

S21Matrix::S21Matrix(S21Matrix&& other) noexcept { *this = std::move(other); }

S21Matrix::~S21Matrix() { DeleteMatrix_(); }

void S21Matrix::SetRows(const int rows) {
  InvalidArgumentRows(rows);

  if (rows == 0)
    DeleteMatrix_();
  else if (rows_ != rows)
    SetAnotherRows_(rows);
}

void S21Matrix::SetColumns(const int cols) {
  InvalidArgumentCols(cols);

  if (cols == 0)
    DeleteMatrix_();
  else if (cols_ != cols)
    SetAnotherColumns_(cols);
}

int S21Matrix::GetRows() const noexcept { return rows_; }
int S21Matrix::GetColumns() const noexcept { return cols_; }

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  bool ret;

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    ret = false;
  } else {
    ret = true;
    for (auto i = 0; ret && i < rows_; i++)
      for (auto j = 0; ret && j < cols_; j++)
        if (__builtin_isfinite(matrix_[i][j]) &&
            __builtin_isfinite(other.matrix_[i][j])) {
          ret = EqDouble(matrix_[i][j], other.matrix_[i][j]);
        } else if (__builtin_isnan(matrix_[i][j]) ||
                   __builtin_isnan(other.matrix_[i][j])) {
          if (!__builtin_isnan(matrix_[i][j]))
            ret = false;
          else if (!__builtin_isnan(other.matrix_[i][j]))
            ret = false;
          else if (__builtin_signbit(matrix_[i][j]) !=
                   __builtin_signbit(other.matrix_[i][j]))
            ret = false;
        } else {
          if (matrix_[i][j] != other.matrix_[i][j]) ret = false;
        }
  }

  return ret;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  DifferentMatrixDimensions_(other);

  for (auto i = 0; i < rows_; i++)
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
      CheckNull_(matrix_[i][j]);
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  DifferentMatrixDimensions_(other);

  for (auto i = 0; i < rows_; i++)
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
      CheckNull_(matrix_[i][j]);
    }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (auto i = 0; i < rows_; i++)
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
      CheckNull_(matrix_[i][j]);
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  S21Matrix res(rows_, other.cols_);

  if (cols_ != other.rows_)
    throw std::logic_error(
        "Incorrect input, the number of columns of the first matrix does not "
        "equal the number of rows of the second matrix");

  for (auto i = 0; i < res.rows_; i++)
    for (auto j = 0; j < res.cols_; j++) {
      for (auto k = 0; k < cols_; k++)
        res.matrix_[i][j] =
            res.matrix_[i][j] + matrix_[i][k] * other.matrix_[k][j];
      CheckNull_(res.matrix_[i][j]);
    }

  *this = std::move(res);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix ret(cols_, rows_);

  for (auto i = 0; i < ret.rows_; i++)
    for (auto j = 0; j < ret.cols_; j++) ret.matrix_[i][j] = matrix_[j][i];

  return ret;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix ret(rows_, cols_);

  MatrixIsNotSquare_();

  if (rows_ == 1) {
    ret.matrix_[0][0] = matrix_[0][0];
  } else {
    for (auto i = 0; i < rows_; i++)
      for (auto j = 0; j < cols_; j++) {
        ret.matrix_[i][j] = Minor_(i, j).Determinant();
        if (ret.matrix_[i][j] != 0.0 && (i + j) % 2 != 0)
          ret.matrix_[i][j] = -ret.matrix_[i][j];
      }
  }

  return ret;
}

double S21Matrix::Determinant() const {
  S21Matrix temp(*this);
  double ret;

  MatrixIsNotSquare_();

  if (rows_ == 1) {
    ret = matrix_[0][0];
  } else if (temp.Gauss_(ret) == -1) {
    ret = 0.0;
  } else {
    for (auto i = 0; i < rows_; i++) ret *= temp.matrix_[i][i];
    CheckNull_(ret);
  }

  return ret;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det;
  S21Matrix ret(rows_, cols_);

  det = Determinant();
  if (det == 0.0) throw std::logic_error("matrix determinant is 0");

  ret = CalcComplements().Transpose() * (1.0 / det);

  return ret;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix ret(*this);

  ret.SumMatrix(other);

  return ret;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix ret(*this);

  ret.SubMatrix(other);

  return ret;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix ret(*this);

  ret.MulMatrix(other);

  return ret;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix ret(*this);

  ret.MulNumber(num);

  return ret;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix ret(other);

  ret.MulNumber(num);

  return ret;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  bool ret;

  ret = EqMatrix(other);

  return ret;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    DeleteMatrix_();
    SetPrivateFields_(other.rows_, other.cols_, nullptr);
    CopyMatrix_(other);
  }

  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    DeleteMatrix_();
    SetPrivateFields_(other.rows_, other.cols_, other.matrix_);
    other.SetPrivateFields_(0, 0, nullptr);
  }

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) noexcept {
  MulNumber(num);

  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  IndexIsOutsideTheMatrix_(i, j);

  return matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
  IndexIsOutsideTheMatrix_(i, j);

  return matrix_[i][j];
}

// private
// ----------------------------------------------------------------------------

void S21Matrix::InvalidArgumentRows(const int rows) const {
  if (rows < 0)
    throw std::invalid_argument(
        "Incorrect input, value of rows is less than zero");
}

void S21Matrix::InvalidArgumentCols(const int cols) const {
  if (cols < 0)
    throw std::invalid_argument(
        "Incorrect input, value of columns is less than zero");
}

void S21Matrix::SetPrivateFields_(const int rows, const int cols,
                                  double** matrix) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = matrix;
  if (!matrix && rows > 0 && cols > 0) {
    matrix_ = new double* [rows] {};
    if (matrix_)
      for (auto i = 0; i < rows; i++) matrix_[i] = new double[cols]{};
  }
}

void S21Matrix::CopyMatrix_(const S21Matrix& other) noexcept {
  int n;
  int m;

  n = std::min(rows_, other.rows_);
  m = std::min(cols_, other.cols_);
  if (matrix_) {
    for (auto i = 0; i < n; i++) {
      if (matrix_[i])
        for (auto j = 0; j < m; j++) matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::DeleteMatrix_() noexcept {
  if (matrix_) {
    for (auto i = 0; i < rows_; i++)
      if (matrix_[i]) delete[] matrix_[i];
    delete[] matrix_;
  }
  SetPrivateFields_(0, 0, nullptr);
}

void S21Matrix::SetAnotherRows_(const int rows) {
  S21Matrix matrix(rows, cols_);

  matrix.CopyMatrix_(*this);

  *this = std::move(matrix);
}

void S21Matrix::SetAnotherColumns_(const int cols) {
  S21Matrix matrix(rows_, cols);

  matrix.CopyMatrix_(*this);

  *this = std::move(matrix);
}

bool S21Matrix::EqDouble(double x, double y) const noexcept {
  double tmp;
  bool ret;

  tmp = x - y;
  if (std::abs(tmp) >= EPS)
    ret = false;
  else
    ret = true;

  return ret;
}

void S21Matrix::DifferentMatrixDimensions_(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Incorrect input, different matrix dimensions");
}

void S21Matrix::CheckNull_(double& value) const noexcept {
  if (std::abs(value) < EPS) value = 0.0;
}

void S21Matrix::MatrixIsNotSquare_() const {
  if (rows_ < 1 || rows_ != cols_)
    throw std::logic_error("Incorrect input, the matrix is not square");
}

S21Matrix S21Matrix::Minor_(const int row, const int column) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (auto i = 0, ii = 0; i < minor.rows_; i++, ii++) {
    if (ii == row) ii++;
    for (auto j = 0, jj = 0; j < minor.cols_; j++, jj++) {
      if (jj == column) jj++;
      minor.matrix_[i][j] = matrix_[ii][jj];
    }
  }

  return minor;
}

int S21Matrix::Gauss_(double& res) noexcept {
  double tmp;
  int ret;

  ret = 0;
  res = 1.0;
  for (int k = 0; ret != -1 && k < rows_ - 1; k++) {
    if ((ret = GaussMaxRow_(k)) != -1) {
      if (ret != k) {
        res = -res;
        std::swap(matrix_[ret], matrix_[k]);
      }
      for (int i = k + 1; i < rows_; i++) {
        tmp = -matrix_[i][k] / matrix_[k][k];
        matrix_[i][k] = 0.0;
        for (int j = k + 1; j < rows_; j++)
          matrix_[i][j] = matrix_[i][j] + tmp * matrix_[k][j];
      }
    }
  }

  return ret;
}

int S21Matrix::GaussMaxRow_(const int j) noexcept {
  double tmp;
  double max;
  int ret;

  tmp = std::abs(matrix_[j][j]);
  max = tmp;
  ret = j;
  for (int i = j + 1; i < rows_; i++) {
    tmp = std::abs(matrix_[i][j]);
    if (max < tmp) {
      max = tmp;
      ret = i;
    }
  }
  CheckNull_(max);
  if (max == 0.0) ret = -1;

  return ret;
}

void S21Matrix::IndexIsOutsideTheMatrix_(const int i, const int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::out_of_range("Incorrect input, index is outside the matrix");
}
