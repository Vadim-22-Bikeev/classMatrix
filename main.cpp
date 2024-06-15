#include <sstream>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include "mat.h"


/**
* \brief Prompts the user to enter several matrices 
* This function asks the user to specify the number of matrices, then for each matrix, it requests
* the dimensions (rows and columns) and the elements.
* \param matrices A map to store the matrices with char keys and unique_ptr values.
*/
void getMatricesFromUser(std::map<char, std::unique_ptr<Matrix>>& matrices) {
    int numMatrices;
    std::cout << "Enter the number of matrices: ";
    std::cin >> numMatrices;

    for (int i = 0; i < numMatrices; ++i) {
        char matrixName = 'A' + i;
        int rows, cols;
        std::cout << "Enter the number of rows for matrix " << matrixName << ": ";
        std::cin >> rows;
        std::cout << "Enter the number of columns for matrix " << matrixName << ": ";
        std::cin >> cols;

        std::vector<std::vector<double>> data(rows, std::vector<double>(cols));
        std::cout << "Enter the elements of matrix " << matrixName << " row by row:\n";
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                std::cin >> data[r][c];
            }
        }
        matrices[matrixName] = std::make_unique<Matrix>(Matrix(data));
    }
}

/**
* \brief Requests the operation chain from the user.
* This function prompts the user to enter a chain of operations to be performed on the matrices.
* The operations should be in the format of a mathematical expression involving matrix names, 
* such as "A*B+C".
* \return A string representing the chain of operations.
*/
std::string getOperationChain() {
    std::string operations;
    std::cout << "Enter the chain of operations (e.g., A*B+C): ";
    std::cin >> operations;
    return operations;
}

/**
* \brief Evaluates a chain of matrix operations.
* \param chain A string representing the chain of operations.
* \param matrices A,B,C...
* \return A Matrix object representing the result of the operations.
* \throw std::invalid_argument if an invalid operation is encountered.
*/
Matrix evaluateOperationChain(const std::string& chain, const std::map<char, std::unique_ptr<Matrix>>& matrices) {
    std::vector<Matrix> operands;
    std::vector<char> operators;

    for (char ch : chain) {
        if (isalpha(ch)) {
            operands.push_back(*matrices.at(ch));
        } else {
            operators.push_back(ch);
        }
    }

    while (!operators.empty()) {
        char op = operators.back();
        operators.pop_back();

        if (op == '*') {
            Matrix right = operands.back();
            operands.pop_back();
            Matrix left = operands.back();
            operands.pop_back();
            auto result = left * right;
            operands.push_back(result);
        } else if (op == '+') {
            Matrix right = operands.back();
            operands.pop_back();
            Matrix left = operands.back();
            operands.pop_back();
            auto result = left + right;
            operands.push_back(result);
        } else if (op == '-') {
            Matrix right = operands.back();
            operands.pop_back();
            Matrix left = operands.back();
            operands.pop_back();
            auto result = left - right;
            operands.push_back(result);
        }
        
    }

    return operands.back();
}

int main() {
    try {
        std::map<char, std::unique_ptr<Matrix>> matrices;
        getMatricesFromUser(matrices);

        std::string operations = getOperationChain();

        Matrix result = evaluateOperationChain(operations, matrices);

        std::cout << "Result:\n" << result;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}