/**
* Tests related with the Matrix algebraic type and its related operations
*/

import tsuite;
import math;
import std;

TestSuite matrix_suite {"Matrix TS"};

void matrix_tests() {
    TEST_CASE(matrix_suite, "Test Matrix construction", [] {
//        Matrix m {  // ctr for std::initializer_list
//            std::array {3, 5, 8},
//            std::array {4, 7, 9},
//            std::array {9, 1, 15}
//        };
        Matrix<3, 3, int> m {
            std::array{
                std::array {3, 5, 8},
                std::array {4, 7, 9},
                std::array {9, 1, 15}
            }
        };

        /*
         * 3, 5, 8 / 4, 7, 9, / 9, 1, 15
         * 3, 4, 9 / 5, 7, 1 / 8, 9 15
         */

        assertEquals(m.row<0>().column<0>(), 7);
    });
}