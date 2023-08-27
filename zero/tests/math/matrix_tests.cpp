#include "matrix_tests.h"

TestSuite matrix_suite {"Matrix TS"};

void matrix_tests() {
    TEST_CASE(matrix_suite, "Row Matrix construction and retrieve element", [] {
        auto a = Row<3, int> {{3, 5, 8}}; // Note the double braces. It's the constructor from std::array
        auto b = Row {4, 7, 9};
        auto c = Row {9, 1, 15};

        // Constructs a Row matrix of integers
        Matrix<3, 3> row_matrix { a, b, c };
        // Checks if the A0,0 element is equals to some value
        assertEquals(row_matrix.row<0>().column<0>(), 3);
    });
    TEST_CASE(matrix_suite, "Column Matrix construction and retrieve element", [] {
        /// Column Matrix directly constructed from the std::initializer list parameter constructor
        Matrix<3, 3, int, ColumnOrientation> column_matrix {
            Column {5, 7, 9},
            Column {32, 25, 10},
            Column {65, 1, 12}
        };
        /* Tempting to retrieve a column from a RowMatrix or a row from
         * a column Matrix will made the concepts constrains fail like:
         *
         * ...Zero/zero/ifc/math/linear_algebra/matrix.cppm:line:col: note:
         * because 'ColumnOrientation' does not satisfy 'RowMatrix'
         * [[nodiscard]] constexpr auto row() -> Row<Cols, T> requires (RowMatrix<Orientation>) { ...
         *
         * assertEquals(column_matrix.row<0>().column<0>(), 7); // This won't compile
         */
        // Checks if the column_matrix 3,2 element is equals to some value
        assertEquals(column_matrix.column<3>().row<2>(), 10);
    });
}
