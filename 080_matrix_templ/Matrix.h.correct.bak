#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;  // instead of std::vector<std::vector<T> >

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}

  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]()) {
    for (int i = 0; i < numRows; ++i)
      rows[i] = new std::vector<T>(c);
  }

  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new std::vector<T> *[rhs.numRows]()) {
    for (int i = 0; i < rhs.numRows; ++i)
      rows[i] = new std::vector<T>(*rhs.rows[i]);
  }

  ~Matrix() {
    for (int i = 0; i < numRows; ++i)
      delete rows[i];
    delete[] rows;
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<T> ** temp = new std::vector<T> *[rhs.numRows]();
      for (int i = 0; i < rhs.numRows; ++i)
        temp[i] = new std::vector<T>(*rhs.rows[i]);
      for (int i = 0; i < numRows; ++i)
        delete rows[i];
      delete[] rows;
      rows = temp;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
    }
    return *this;
  }

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return *rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (numColumns != rhs.numColumns || numRows != rhs.numRows)
      return 0;
    for (int i = 0; i < numRows; ++i)
      if (*rows[i] != rhs[i])
        return 0;
    return 1;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numColumns == rhs.numColumns && numRows == rhs.numRows);
    Matrix ans(rhs);
    for (int i = 0; i < numRows; ++i)
      for (int j = 0; j < numColumns; ++j)
        ans[i][j] = (*this)[i][j] + rhs[i][j];
    return ans;
  }

  template<typename T2>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<T2> & rhs);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & vec) {
  if (vec.size() == 0) {
    s << "{}";
  }
  else {
    s << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
      if (i > 0)
        s << ", ";
      s << vec[i];
    }
    s << "}";
  }
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0)
    s << "[  ]";
  else {
    s << "[ ";
    for (int i = 0; i < rhs.getRows() - 1; ++i) {
      s << rhs[i] << ",\n";
    }
    s << rhs[rhs.getRows() - 1] << " ]";
  }
  return s;
}

#endif
