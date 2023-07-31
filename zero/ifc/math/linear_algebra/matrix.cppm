export module math.linear_algebra:matrix;

import std;

export {
    enum class Orientation {
        ROW,
        COLUMN
    };

    template <std::size_t Elements, typename Type>
    struct Row {
        std::array<Type, Elements> row {};
        template <std::size_t ColumnIndex>
        // Same as hidden friend
        [[nodiscard]] constexpr auto column() -> decltype(std::get<ColumnIndex>(row)) {
            return std::get<ColumnIndex>(row);
        }
    };

    template <std::size_t Elements, typename Type>
    struct Column {
        std::array<Type, Elements> column {};
        template <std::size_t RowIndex>
        [[nodiscard]] constexpr auto row() -> decltype(std::get<RowIndex>(column)) {
            return std::get<RowIndex>(column);
        }
    };

    template <std::size_t Rows, std::size_t Cols, typename T = int, Orientation = Orientation::ROW>
    class Matrix {
    private:
        // TODO std::variant for enable members that holds the data if they are row-column or vice-versa
//        std::array<std::array<T, Cols>, Rows> data {};
        // TODO std::initializer_list constructor

        // Let's see how the todo works
        using DataRow = std::array<T, Cols>;
        using DataCol = std::array<T, Rows>;

        std::variant<
            std::array<DataRow, Rows>, // Orientation::ROW
            std::array<DataCol, Cols>  // Orientation::COLUMN
        > data;

    public:
        Matrix() = delete;
        /// Raw constructor for std::array
        constexpr Matrix(const std::array<std::array<T, Cols>, Rows>& data) : data(data) {}
        // TODO constructor from raw array?
        // TODO constructor from vector?
        // TODO constructor from row
        // TODO constructor from vector (row_vector)
        // TODO constructor from vector (column_vector)

        template <std::size_t RowIndex>
        [[nodiscard]] constexpr auto row() -> Row<Rows, T> {
            return Row<Rows, T> { std::get<RowIndex>(data) };
        }

        // template for get, with std::conditional_t based on orientation?
    };
}