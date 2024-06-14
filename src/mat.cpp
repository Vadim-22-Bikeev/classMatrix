#include <iostream>
#include <vector>
#include <stdexcept>

#include "mat.h"




    void Matrix::check_dimensions(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must agree.");
        }
    }

    Matrix Matrix::get_cofactor(size_t p, size_t q) const {
        Matrix cofactor(rows - 1, cols - 1);
        size_t i = 0, j = 0;
        for (size_t row = 0; row < rows; row++) {
            for (size_t col = 0; col < cols; col++) {
                if (row != p && col != q) {
                    cofactor.data[i][j++] = data[row][col];
                    if (j == cols - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
        return cofactor;
    }

    double Matrix::determinant(const Matrix& mat) const {
        if (mat.rows != mat.cols) {
            throw std::invalid_argument("Matrix must be square to compute determinant.");
        }
        if (mat.rows == 1) {
            return mat.data[0][0];
        }
        if (mat.rows == 2) {
            return mat.data[0][0] * mat.data[1][1] - mat.data[0][1] * mat.data[1][0];
        }
        double det = 0;
        int sign{1};
        for (size_t f = 0; f < mat.cols; f++) {
            Matrix cofactor = mat.get_cofactor(0, f);
            det += sign * mat.data[0][f] * determinant(cofactor);
            sign = -sign;
        }
        return det;
    }

    Matrix Matrix::adjoint() const {
       
        Matrix adj(rows, cols);
        int sign = 1;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                Matrix cofactor = get_cofactor(i, j);
                sign = ((i + j) % 2 == 0) ? 1 : -1;
                adj.data[j][i] = sign * determinant(cofactor);
            }
        }
        return adj;
    }

   
    Matrix Matrix::operator+(const Matrix& other) const {
        check_dimensions(other);
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
    Matrix::Matrix(const std::vector<std::vector<double>>& data) : data(data), rows(data.size()), cols(data[0].size()) {
        if(data.size() == 0) 
            throw std::runtime_error{"data cannot be empty"};
    }

    Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows, std::vector<double>(cols)) {
        if((rows == 0) || (cols == 0))
            throw std::runtime_error{"rows or cols cannot be 0"};
    }

    Matrix Matrix::operator-(const Matrix& other) const {
        check_dimensions(other);
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
        
    bool Matrix::operator==(const Matrix& other) const {
        check_dimensions(other);

        for (size_t i{}; i < rows; ++i) {
            for (size_t j{}; j < cols; ++j) {
                if(data[i][j] != other.data[i][j])
                    return false;
            }
        }
        return true;
    }


    Matrix Matrix::operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix multiplication dimensions must agree.");
        }
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix Matrix::operator*(const double scalar) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix Matrix::operator!() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    double Matrix::operator*() const {
        return determinant(*this);
    }

    Matrix Matrix::operator~() const {
        double det = determinant(*this);
        if (det == 0) {
            throw std::runtime_error("Matrix is singular and cannot be inverted.");
        }
        Matrix adj = adjoint();
        Matrix inv = adj * (1.0 / det);
        return inv;
    }

     std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (const auto& row : matrix.data) {
            for (double val : row) {
                os << val << " ";
            }
            os << std::endl;
        }
        return os;
    }



