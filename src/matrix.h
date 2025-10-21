#pragma once

#include <vector>
#include <ostream>
#include <cstdint>

// these basically make long way of writing a row/matrix shorter and more readable
typedef std::vector<uint8_t> row_t;    // typedef for an individual matrix row
typedef std::vector<row_t> matrix_t;   // typedef for the matrix storage

class Matrix {
public:
    // default constructor, we dont do anything in our constructor so it is just the default
    Matrix() = default;

    // gets user input and populates the matrix
    void getMatrix();

    // helper functions:
    int getHeight() const;  // returns the height of the matrix
    int getWidth() const;   // returns the width of the matrix

    // allows for indexing of the object
    const row_t& operator[](size_t i) const;
    // does the boolean multiplication
    Matrix operator*(const Matrix& other) const;
    // does the boolean addition
    Matrix operator|(const Matrix& other) const;

    // compound assignment versions of the above
    Matrix& operator*=(const Matrix& other);
    Matrix& operator|=(const Matrix& other);

    // makes the class friendly to being printed
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

private:
    // used to parse user input
    row_t cleanup(std::string& input);

    // returns true if `c` is a character we dont want in our matrix (e.g. "," " " etc.)
    // make this static so it can be passed in as a function pointer to `remove_if()`
    static bool removeUnwanted(char c) { return (c == ',') || std::isspace(c); }

    // the underlying storage for the matrix
    matrix_t mat;
};