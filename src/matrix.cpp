#include "matrix.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <optional>
#include <ctype.h>

/**
 * Translated from python:
 * Input:
 *  input can be delimited by either by spaces (' ') or commas (',') or both
 *  for example:
 *      1,0,1,0
 *      1 0 1 0
 *      1, 0, 1, 0
 *  and when input is done put in a blank line, should be just like python
 *
 * Creates a matrix in standard matrix notation:
 * M[x][y] is row x, (top to bottom, starting at 0)
 * and column y (left to right, starting at 0)
 * for example, a 3x3 matrix is
 * |(0,0) (0,1) (0,2)|
 * |(1,0) (1,1) (1,2)|
 * |(2,0) (2,1) (2,2)|
 */
void Matrix::getMatrix() {
    /**
     * Takes a matrix of numbers from the user. Each row can be
     * seperated by commas and/or spaces. A blank line ends the input
     */
    std::cout << "Enter your matrix:" << std::endl;
    std::string x{}; // the string to write to
    std::getline(std::cin, x); // need to getline because by default c++ splits on a space

    // `cleanup()` takes the string input and parses it into a row_t
    row_t items = cleanup(x);
    auto length = items.size(); // store how many columns the first row is

    // loop only until we take in as many rows as there are columns;
    // we already have 1 row so `i` starts at `1` and we want an equal number of rows and cols;
    //  this is techincally the same as if `i = 0` and `i < length` but its clearer this way
    for (int i = 1; i <= (int)length; i++) {
        if (i > 1) { // we only wany to ask if this isnt the first loop
            x = ""; // reset input string
            std::getline(std::cin, x); // need to getline because by default c++ splits on a space
        }

        items = cleanup(x);
        // ensure that all of the next rows are the same length as first
        if (items.size() != length) {
            // if not then we tell the user the error and ask them to try again
            std::cerr << "ERROR: row lengths are mismatched! Try again:" << std::endl;
            // we want them to try again and so we remove one from the iterator;
            // so that we still get the correct number of rows
            i--;
        } else {
            // if the length is the same then add the row_t to the matrix
            mat.push_back(items);
        }
    }
}

// look at matrix.h to see these comments
int Matrix::getHeight() const { return static_cast<int>(mat.size()); }
int Matrix::getWidth() const { return static_cast<int>(mat[0].size()); }
const row_t& Matrix::operator[](size_t i) const { return mat[i]; }

// cleanup the input string and return it as a row_t (i.e. a std::vector of unsigned bytes)
row_t Matrix::cleanup(std::string& input) {
    // Source: https://stackoverflow.com/a/83538/16902023
    // this will erase all unwanted characters from `input` using the `removeUnwanted()`
    // it will remove "," and spaces
    input.erase(remove_if(input.begin(), input.end(), removeUnwanted), input.end());

    // make the new matrix row
    row_t items{};
    // for every character in the input string
    for (char c : input) {
        // add the input number to the back
        // c - '0' => '6' - '0' =(ASCII)=> 54 - 48 = 6
        items.push_back(c - '0');
    }

    // return the row, I don't love returning the row like this since copying a
    //  vector is not the best but its good enough
    return items;
}

// This is an overloaded multiplication operator that will find the boolean product
Matrix Matrix::operator*(const Matrix& other) const {
    int th = this->getHeight(),
        tw = this->getWidth(),
        oh = other.getHeight(),
        ow = other.getWidth();
    // first we make sure that we can multiply the matrices together at all
    // an m x n size matrix and a i x j size matrix can be multiplied together iff n==i
    if (tw != oh) {
        // if we find out matrices don't fit this size requirement then we tell the user and return a blank matrix
        std::cerr << "Boolean Product not defined for matrix sizes\n";
        return Matrix{};
    }
    Matrix prodMat{};

    // formula Source: https://en.wikipedia.org/wiki/Boolean_matrix
    // latex version:
    //      c_{ij} = \lor^{n-1}_{k=0}(a_{ik}\land b_{kj})

    // resize the product matrix to the size it should be
    prodMat.mat.resize(th, row_t(ow, 0));
    // this is essentially a direct translation of the formula listed above
    // first two for loops will loop though all entries that will be in the product matrix
    for (int i = 0; i < th; i++) {
        for (int j = 0; j < ow; j++) {

            // this handles the or loop that is in the equation:
            //  goes from 0 to how many entires are in the length of the first matrix being multiplied
            for (int k = 0; k < tw; k++) {
                // then we or-equal all the and-ed entries described in the formula
                // this would unravel to something like (latex formula):
                //      c_{00}=(a_{00}\land b_{00})\lor(a_{01}\land b_{10})\lor\cdots\lor(a_{0(k-1)}\land b_{(k-1)0})\lor(a_{0k}\land b_{k0})
                prodMat.mat[i][j] |=  (*this)[i][k] & other[k][j];
            }
        }
    }

    // return the created and populated product matrix
    return prodMat;
}

Matrix Matrix::operator|(const Matrix& other) const {
    int h = this->getHeight();
    int w = this->getWidth();
    // first we make sure that we can add the matrices together at all
    // an m x n size matrix and a i x j size matrix can be added together iff n==i and m==j
    if (w != other.getWidth() || h != other.getHeight()) {
        // if we find out matrices don't fit this size requirement then we tell the user and return a blank matrix
        std::cerr << "Boolean Sum not defined for matrix sizes\n";
        return Matrix{};
    }
    Matrix sumMat{};

    // resize the sum matrix to the size it should be
    sumMat.mat.resize(h, row_t(w, 0));
    // loop though all entries that will be in the sum matrix
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // do the boolean addition by or-ing the corresponding entries
            sumMat.mat[i][j] = (*this)[i][j] | other[i][j];
        }
    }

    // return the created and populated sum matrix
    return sumMat;
}

// compound assignment versions of the above
Matrix& Matrix::operator*=(const Matrix& other) {
    *this = (*this) * other;
    return *this;
}

Matrix& Matrix::operator|=(const Matrix& other) {
    *this = (*this) | other;
    return *this;
}

// Source: https://en.cppreference.com/w/cpp/language/operators.html#Stream_extraction_and_insertion
// allows for the class object to 'play nice' with `std::cout` printing
std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    for (const row_t& row : m.mat) {
        for (int item : row) {
            out << item << ' ';
        }
        out << '\n';
    }

    return out;
}