#ifndef __T_MATRIX_C___
#define __T_MATRIX_C___
#include "Matrix.h"

template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0), rows(0) {
}

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  rows.resize(r);
  for (size_t i = 0; i < rows.size(); ++i)
    rows[i].resize(c);
  //for (auto & row : rows)
  //  row.resize(c);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(rhs.rows) {
}

template<typename T>
Matrix<T>::~Matrix() {
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  if (this != &rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
  }
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  return (rows == rhs.rows);
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  Matrix ans(numRows, numColumns);
  for (ssize_t i = 0; i < numRows; ++i)
    for (ssize_t j = 0; j < numColumns; ++j)
      ans.rows[i][j] = rows[i][j] + rhs.rows[i][j];
  return ans;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & vec) {
  s << "{";
  for (size_t i = 0; i < vec.size(); ++i) {
    if (i > 0)
      s << ", ";
    s << vec[i];
  }
  s << "}";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (ssize_t i = 0; i < rhs.getRows(); ++i) {
    if (i != 0)
      s << ",\n";
    s << rhs[i];
  }
  s << " ]";
  return s;
}
#endif
