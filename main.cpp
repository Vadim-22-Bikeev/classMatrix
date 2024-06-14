#include <sstream>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include "mat.h"

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

// Function to request the operation chain from the user
std::string getOperationChain() {
    std::string operations;
    std::cout << "Enter the chain of operations (e.g., A*B+C): ";
    std::cin >> operations;
    return operations;
}

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