export module math.linear_algebra:matrix;

import std;

export {
    template <std::size_t Elements, typename Type = int>
    struct Row {
        std::array<Type, Elements> row;

        /// Default constructor is explicitly removed from the public API
        Row<Elements, Type>() = delete;

        /// Constructs a {@link Row} from {@link std::array}
        constexpr Row<Elements, Type>(std::array<Type, Elements> data): row {data} {}

        /// Constructor acts as if its argument were an std::initializer list
        template <typename... Args>
        constexpr Row<Elements, Type>(Args... args) : row {args...} {}

        // TODO Same as hidden friend?
        template <std::size_t ColumnIndex>
        [[nodiscard]] constexpr auto column() -> decltype(std::get<ColumnIndex>(row)) {
            return std::get<ColumnIndex>(row);
        }
    };

    template <std::size_t Elements, typename Type = int>
    struct Column {
        std::array<Type, Elements> column;

        /// Default constructor is explicitly removed from the public API
        Column() = delete;

        /// Constructs a {@link Column} from {@link std::array}
        constexpr Column<Elements, Type>(std::array<Type, Elements> data): column {data} {}

        /// Constructor acts as if its argument were an std::initializer list
        template <typename... Args>
        constexpr Column<Elements, Type>(Args... args) : column {args...} {}

        template <std::size_t RowIndex>
        [[nodiscard]] constexpr auto row() -> decltype(std::get<RowIndex>(column)) {
            return std::get<RowIndex>(column);
        }
    };

    /// Tag type for dispatch row based matrices
    struct RowOrientation {};
    /// Tag type for dispatch column based matrices
    struct ColumnOrientation {};

    template <typename T>
    concept MatrixOrientation =
        std::is_same_v<T, RowOrientation> || std::is_same_v<T, ColumnOrientation>;

    template <typename T>
    concept RowMatrix = std::is_same_v<T, RowOrientation>;

    template <typename T>
    concept ColumnMatrix = std::is_same_v<T, ColumnOrientation>;

    template <std::size_t Rows, std::size_t Cols, typename T = int, MatrixOrientation Orientation = RowOrientation>
    class Matrix {
        // BIG TODO the names for Rows and Cols size are non worth. Better MxN, so we can play with the orientation
    private:
        using DataRow = Row<Cols, T>;
        using DataCol = Column<Rows, T>;

        std::variant<
            std::vector<DataRow>, // Row Orientation
            std::vector<DataCol>  // Column Orientation
        > data;

    public:
        /// Default constructor is explicitly removed from the public API
        Matrix() = delete;

        /// Row Matrix constructor
        constexpr Matrix<Rows, Cols, T>(
            std::initializer_list<DataRow> rows
        ) requires RowMatrix<Orientation> : data {rows} {}
        /// Column Matrix constructor
        constexpr Matrix<Cols, Rows, T>(
            std::initializer_list<DataCol> columns
        ) requires ColumnMatrix<Orientation> : data {columns} {}
        // TODO orientation must be guide deduced, so there's no explicit
        //  need to declare it at call site (just optional)

        template <std::size_t RowIndex>
        [[nodiscard]] constexpr auto row() -> Row<Cols, T> requires (RowMatrix<Orientation>) {
            return Row<Cols, T> { std::get<std::vector<DataRow>>(data)[RowIndex] };
        }

        template <std::size_t ColIndex>
        [[nodiscard]] constexpr auto column() -> Column<Rows, T> requires (ColumnMatrix<Orientation>) {
            return Column<Rows, T> { std::get<std::vector<DataCol>>(data)[ColIndex] };
        }
    };
}
