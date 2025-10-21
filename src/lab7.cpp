#include <iostream>
#include <vector>

#include "matrix.h"

/**
 * procedure transitive closure (M_R : zero-one n x n matrix)
 *  A := M_R
 *  B := A
 *  for i := 2 to n
 *      A := A ⊙ M_R
 *      B := B v A
 *  return B{B is the zero-one matrix for R*}
 */
Matrix transitiveClosure(const Matrix& mat) {
    Matrix A = mat; // initialize A to M_R
    Matrix B = A; // initialize B to A
    // find n
    int n = mat.getWidth(); // expects width and height to be equal
    for (int i = 2; i <= n; i++) { // loop from 2 to n
        A *= mat; // A := A ⊙ M_R
        B |= A; // B := B v A
    }
    // Id rather not copy the matrix in the return but oh well
    return B; // return B{B is the zero-one matrix for R*}
}

int main() {
    Matrix M{}; // initialize empty matrix M

    M.getMatrix(); // get user input to populate M
    Matrix A = transitiveClosure(M); // find the transitive closure of M

    std::cout << '\n' << A << std::endl; // print the resulting matrix
}