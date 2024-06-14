#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include "doctest.h"

#include "mat.h"

TEST_CASE("тест сложения") {
    Matrix A({{1,2}, {3,4}}), B({{1,2}, {3,4}});
    auto C {A+B};

    Matrix result({{2,4}, {6,8}});

    CHECK(result == C);
}

TEST_CASE("тест исключения") {
    Matrix A(2,2);
    Matrix B(3,3);
    CHECK_THROWS_AS(A * B, std::invalid_argument);
}

TEST_CASE("тест вычитания") {
    Matrix A({{5,7}, {9,11}}), B({{1,2}, {3,4}});
    auto C {A-B};

    Matrix result({{4,5}, {6,7}});

    CHECK(result == C);
}

TEST_CASE("тест умножения на скаляр") {
    Matrix A({{1,2}, {3,4}});
    double scalar = 2.0;
    auto C {A*scalar};

    Matrix result({{2,4}, {6,8}});

    CHECK(result == C);
}

TEST_CASE("тест умножения матриц") {
    Matrix A({{1,2}, {3,4}});
    Matrix B({{2,0}, {1,2}});
    auto C {A*B};

    Matrix result({{4,4}, {10,8}});

    CHECK(result == C);
}

TEST_CASE("тест транспонирования") {
    Matrix A({{1,2}, {3,4}});
    auto C = !A;

    Matrix result({{1,3}, {2,4}});

    CHECK(result == C);
}

TEST_CASE("тест определителя") {
    Matrix A({{1,2}, {3,4}});
    double det = *A;

    double result = -2.0;

    CHECK(result == det);
}

TEST_CASE("тест присоединенной матрицы") {
    Matrix A({{1,2}, {3,4}});
    auto adj = A.adjoint();

    Matrix result({{4,-2}, {-3,1}});

    CHECK(result == adj);
}

TEST_CASE("тест присоединенной матрицы exception") {
    Matrix A({{2,4}, {3,6}});
   
   CHECK_THROWS_AS(~A, std::runtime_error);
}




TEST_CASE("тест обратной матрицы") {
    Matrix A({{1,3}, {2,7}});
    auto inv = ~A;

    Matrix result({{7, -3}, {-2, 1}});

    CHECK(result == inv);
}

TEST_CASE("тест исключения при сложении") {
    Matrix A({{1,2}, {3,4}});
    Matrix B({{1,2,3}, {4,5,6}});
    CHECK_THROWS_AS(A + B, std::invalid_argument);
}

TEST_CASE("тест исключения при вычитании") {
    Matrix A({{1,2}, {3,4}});
    Matrix B({{1,2,3}, {4,5,6}});
    CHECK_THROWS_AS(A - B, std::invalid_argument);
}

TEST_CASE("тест исключения при умножении несогласованных матриц") {
    Matrix A({{1,2}, {3,4}});
    Matrix B({{1,2,3}, {4,5,6}, {7,8,9}}); // 3x3 , not 3x2 !
    CHECK_THROWS_AS(A * B, std::invalid_argument);
}

TEST_CASE("тест исключения при вычислении детерминанта несогласованной матрицы") {
    Matrix A({{1,2,3}, {4,5,6}});
    CHECK_THROWS_AS(*A, std::invalid_argument);
}

TEST_CASE("тест исключения при вычислении обратной матрицы для вырожденной матрицы") {
    Matrix A({{1,2}, {2,4}});
    CHECK_THROWS_AS(~A, std::runtime_error);
}

TEST_CASE("тест исключения при создании матрицы с некорректными размерами") {
    CHECK_THROWS_AS(Matrix(0, 0), std::runtime_error);
}