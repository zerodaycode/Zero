export module math.linear_algebra:matrix;

import std;

export {
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

    /// Tag type for dispatch row based matrices
    struct RowOrientation;
    /// Tag type for dispatch column based matrices
    struct ColumnOrientation;

    template <typename T>
    concept MatrixOrientation =
        std::is_same_v<T, RowOrientation> || std::is_same_v<T, ColumnOrientation>;

    template <typename T>
    concept RowMatrix = std::is_same_v<T, RowOrientation>;

    template <typename T>
    concept ColumnMatrix = std::is_same_v<T, ColumnOrientation>;

    template <std::size_t Rows, std::size_t Cols, typename T = int, MatrixOrientation Orientation = RowOrientation>
    class Matrix {
    private:
        using DataRow = Row<Cols, T>;
        using DataCol = Column<Rows, T>;

        std::variant<
            std::vector<DataRow>, // Row Orientation
            std::vector<DataCol>  // Column Orientation
        > data;

    public:
        Matrix() = delete;
        /// Raw constructor for std::array for Orientation::ROW // Every pair of them must be SFINAED
        // because they override the same signature
        constexpr Matrix<Rows, Cols, T, Orientation>(
            const std::array<std::array<T, Cols>, Rows>& data
        ) requires (MatrixOrientation<RowOrientation>) { // TODO Convert this ctr in one of the row ctrs -> Row(std::array...)
                                                            // and add it to the varags missed constructors from the underlying type T
            std::vector<Row<Cols, T>> row_wrappers;
            for (auto row : data)
                row_wrappers.push_back(Row<Cols, T>{row});
            this->data = row_wrappers;
        }
        // From the TODO above, if the user enters Row(s) or Column(s) in the future only Row-Column constructor, the
        // orientation must be guide deduced, so there's no explicit need to declare it at call site (just optional)
        /// Raw constructor for std::array for Orientation::COLUMN
//        constexpr Matrix(const std::array<std::array<T, Rows>, Cols>& data) : data(data) {}

        /// Constructor from zero::Row<Cols, T>
//        constexpr explicit Matrix(const std::array<Row<Cols, T>, Rows>& data) : data(data) {}
        // TODO std::initializer_list constructor
        // TODO constructor from raw array?
        // TODO constructor from vector?
        // TODO constructor from row
        // TODO constructor from vector (row_vector)
        // TODO constructor from vector (column_vector)

        template <std::size_t RowIndex>
        [[nodiscard]] constexpr auto row() -> Row<Rows, T> {
            return Row<Rows, T>{std::get<std::vector<DataRow>>(data)[RowIndex]};
        }

        // template for get, with std::conditional_t based on orientation?
    };
}