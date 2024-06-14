#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include "doctest.h"

#include "mat.h"

TEST_CASE("Addition test") {
    Matrix A({{1,2}, {3,4}}), B({{1,2}, {3,4}});
    auto C {A+B};

    Matrix result({{2,4}, {6,8}});

    CHECK(result == C);
}

TEST_CASE("Exception test") {
    Matrix A(2,2);
    Matrix B(3,3);
    CHECK_THROWS_AS(A * B, std::invalid_argument);
}

TEST_CASE("Subtraction test") {
    Matrix A({{5,7}, {9,11}}), B({{1,2}, {3,4}});
    auto C {A-B};

    Matrix result({{4,5}, {6,7}});

    CHECK(result == C);
}

TEST_CASE("Number multiplication test") {
    Matrix A({{1,2}, {3,4}});
    double scalar = 2.0;
    auto C {A*scalar};

    Matrix result({{2,4}, {6,8}});

    CHECK(result == C);
}

TEST_CASE("Matrix multiplication test") {
    Matrix A({{1,2}, {3,4}});
    Matrix B({{2,0}, {1,2}});
    auto C {A*B};

    Matrix result({{4,4}, {10,8}});

    CHECK(result == C);
}

TEST_CASE("Test transposition") {
    Matrix A({{1,2}, {3,4}});
    auto C = !A;

    Matrix result({{1,3}, {2,4}});

    CHECK(result == C);
}

TEST_CASE("Determinant test") {
    Matrix A({{1,2}, {3,4}});
    double det = *A;

    double result = -2.0;

    CHECK(result == det);
}

TEST_CASE("Test adj matrix") {
    Matrix A({{1,2}, {3,4}});
    auto adj = A.adjoint();

    Matrix result({{4,-2}, {-3,1}});

    CHECK(result == adj);
}

TEST_CASE("Test exception adj matrix") {
    Matrix A({{2,4}, {3,6}});
   
   CHECK_THROWS_AS(~A, std::runtime_error);
}


TEST_CASE("Inverse matrix test") {
    Matrix A({{1,3}, {2,7}});
    auto inv = ~A;

    Matrix result({{7, -3}, {-2, 1}});

    CHECK(result == inv);
}

TEST_CASE("addition exception test") {
    Matrix A({{1,2}, {3,4}});
    Matrix B({{1,2,3}, {4,5,6}});
    CHECK_THROWS_AS(A + B, std::invalid_argument);
}

TEST_CASE("Subtraction exclusion test") {
    Matrix A({{1,2}, {3,4}});
    Matrix B({{1,2,3}, {4,5,6}});
    CHECK_THROWS_AS(A - B, std::invalid_argument);
}

TEST_CASE("Exclusion test for multiplying matrices of different sizes") {
    Matrix A({{1,2}, {3,4}});
    Matrix B({{1,2,3}, {4,5,6}, {7,8,9}}); // 3x3 , not 3x2 !
    CHECK_THROWS_AS(A * B, std::invalid_argument);
}

TEST_CASE("Exclusion test when calculating the determinant of an inconsistent matrix") {
    Matrix A({{1,2,3}, {4,5,6}});
    CHECK_THROWS_AS(*A, std::invalid_argument);
}

TEST_CASE("Exclusion test when calculating the inverse matrix for a degenerate matrix") {
    Matrix A({{1,2}, {2,4}});
    CHECK_THROWS_AS(~A, std::runtime_error);
}

TEST_CASE("Exclusion test when creating a matrix with incorrect dimensions") {
    CHECK_THROWS_AS(Matrix(0, 0), std::runtime_error);
}