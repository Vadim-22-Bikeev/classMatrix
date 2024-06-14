#ifndef MAT_H
#define MAT_H   

#include <iostream>
#include <vector>
#include <stdexcept>

/**
* A class for operations on matrices.
* 1 Addition/Subtraction (+/-)
* 2 Multiplication (*)
* 3 Transposition (!)
* 4 Determinant (*)
* 5 Obtaining the inverse matrix (~)
* 6 Multiplication by a number (*)
* 7 The ability to combine operations into chains
*/
class Matrix {
private:
    std::vector<std::vector<double>> data; //< Matrix data stored in a 2D vector
    size_t rows, cols; //< Number of rows and columns in the matrix

    /**
    * \brief Checks if the dimensions of the matrices match.
    * \param other The matrix to compare dimensions with.
    * \throw std::invalid_argument if the dimensions do not match.
    */
    void check_dimensions(const Matrix& other) const;
    /**
    * \brief Returns the cofactor matrix for a given element.
    * \param p Row index of the element.
    * \param q Column index of the element.
    * \return The cofactor matrix.
    */
    Matrix get_cofactor(size_t p, size_t q) const;
    /**
    * \brief Calculates the determinant of the matrix.
    * \param mat The matrix for which to calculate the determinant.
    * \return The determinant of the matrix.
    */
    double determinant(const Matrix& mat) const;
    /**
    * \brief Calculates the adjoint of the matrix.
    * \return The adjoint matrix.
    */
public:
    Matrix adjoint() const;
    /**
    * \brief Constructs a matrix with specified number of rows and columns.
    * \param rows Number of rows.
    * \param cols Number of columns
    */
    explicit Matrix(size_t rows, size_t cols);
    /**
    * \brief Constructs a matrix from a 2D vector of data.
    * \param data 2D vector containing the matrix data.
    */
    Matrix(const std::vector<std::vector<double>>& data);
    /**
    * \brief Adds two matrices.
    * \param other The matrix to add.
    * \return The resulting matrix after addition.
    * \throw std::invalid_argument if the dimensions do not match.
    */
    Matrix operator+(const Matrix& other) const;
    /**
    * \brief Subtracts one matrix from another.
    * \param other The matrix to subtract.
    * \return The resulting matrix after subtraction.
    * \throw std::invalid_argument if the dimensions do not match.
    */
    Matrix operator-(const Matrix& other) const;
    /**
    * \brief Multiplies two matrices.
    * \param other The matrix to multiply with.
    * \return The resulting matrix after multiplication.
    * \throw std::invalid_argument if the dimensions do not match for multiplication.
    */
    Matrix operator*(const Matrix& other) const;
    /**
    * \brief Checks if two matrices are equal.
    * \param other The matrix to compare with.
    * \return True if the matrices are equal, false otherwise.
    */
    bool operator==(const Matrix& other) const;
    /**
    * \brief Multiplies the matrix by a scalar.
    * \param scalar The scalar to multiply with.
    * \return The resulting matrix after multiplication by the scalar.
    */
    Matrix operator*(const double scalar) const;
    /**
    * \brief Returns the transpose of the matrix.
    * \return The transposed matrix.
    */
    Matrix operator!() const;
    /**
    * \brief Calculates the determinant of the matrix.
    * \return The determinant of the matrix.
    */
    double operator*() const;
    /**
    * \brief Returns the inverse of the matrix.
    * \return The inverse matrix.
    * \throw std::runtime_error if the matrix is singular (determinant is zero).
    */
    Matrix operator~() const;
    /**
    * \brief Outputs the matrix to an output stream.
    * \param os The output stream to write to.
    * \param matrix The matrix to output.
    * \return The output stream after writing the matrix.
    */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};


#endif