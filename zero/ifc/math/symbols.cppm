export module math.symbols;

import std;

export enum class MathSymbol {
    // Basic Math Operators
    Plus,                  // +
    Minus,                 // -
    Multiply,              // ×
    Divide,                // ÷

    // General
    Implies,               // ⇒
    NotImplies,            // ⇏
    IfAndOnlyIf,           // ⇔
    Increment,             // ∆

    // Relation
    Equals,                // =
    NotEquals,             // ≠
    AlmostEqualsTo,        // ≈
    PlusMinus,             // ±
    LessThan,              // <
    GreaterThan,           // >
    LessThanOrEqual,       // ≤
    GreaterThanOrEqual,    // ≥
    ProportionalTo,        // ∝
    ApproximatelyEqual,    // ≈

    // Geometry
    Parallel,              // ∥
    NotParallel,           // ∦

    // Root Symbols
    SquareRoot,            // √
    CubeRoot,              // ∛
    FourthRoot,            // ∜

    // Summation and Integral
    Summation,             // ∑
    Integral,              // ∫
    DoubleIntegral,        // ∬
    TripleIntegral,        // ∭
    ContourIntegral,       // ∮
    SurfaceIntegral,       // ∯
    VolumeIntegral,        // ∰

    // Miscellaneous
    Tilde,                 // ∼
    RingOperator,          // ∘
    SineWave,              // ∿

    // Number Sets
    Naturals,              // ℕ
    Integers,              // ℤ
    Rationals,             // ℚ
    Reals,                 // ℝ
    Complex,               // ℂ
        ImaginaryPart,     // ℑ
        RealPart,          // ℜ
    Quaternions,          // ℍ
    Primes,                // ℙ

    // Set Notation
    OpenCurlyBrace2,       // {
    CloseCurlyBrace2,      // }
    Exists,                // ∃ (Exists)
    ForAll,                // ∀ (For All)
    ElementOf,             // ∈
    NotElementOf,          // ∉
    ContainsAsMember,      // ∋ (As member)
    NotContainsAsMember,   // ∌ (As member)
    Subset,                // ⊂
    SubsetOrEqualTo,       // ⊆
    NotASubset,            // ⊄
    Superset,              // ⊃
    SupersetOrEqualTo,     // ⊇
    NotASuperset,          // ⊅
    EmptySet,              // ∅
    Therefore,             // ∴
    Because,               // ∵
    Intersection,          // ∩
    Union,                 // ∪
    SuchThat,              // ∣
    DivisionSlash,         // ⁄ (Division Slash)
    OpenSquareBrace,       // [
    CloseSquareBrace,      // ]

    // Logical Operators
    LogicalAnd,            // ∧
    LogicalOr,             // ∨
    LogicalNot,            // ¬

    // Infinity and Special Symbols
    Infinity,              // ∞
    MinusInfinity,         // -∞

    // Aleph and Parentheses
    Aleph,                 // ℵ
    OpenParenthesis,       // (
    CloseParenthesis,      // )

    // Superscript and Subscript
    SuperscriptN,          // ⁿ (Superscript n)
    Superscript1,          // ¹ (Superscript 1)
    Superscript2,          // ² (Superscript 2)
    Superscript3,          // ³ (Superscript 3)
    SuperscriptPlus,       // ⁺ (Superscript Plus)
    SuperscriptMinus,      // ⁻ (Superscript Minus)
    Subscript1,            // ₁ (Subscript 1)
    Subscript2,            // ₂ (Subscript 2)
    Subscript3,            // ₃ (Subscript 3)

    // Derivative Symbols
    Derivative,            // ⅆ (Derivative of)
    PartialDerivative,     // ∂ (Partial Derivative)
    Nabla,                 // ∇ (Nabla)
    DelSquared,            // ∇² (Del Squared)
    VectorDiv,             // ∇ · (Divergence)
    Laplace,               // ∇² (Laplace Operator)

    // Vector Symbols
    VectorArrow,           // → (Vector Arrow)
    CrossProduct,          // × (Cross Product)
    DotProduct,            // ⋅ (Dot Product)

    // Matrices Symbols // TODO complete
    Matrix,                // ⎠ (Matrix)
    MatrixTranspose,       // ⊤ (Matrix Transpose)
    MatrixHermitian,       // ⊲ (Matrix Hermitian)

    // Like Letters
    Degree,                // °
    EulerNumber,           // ℯ
    Pi,                    // π
    Sigma,                 // Σ
    Delta,                 // ∆
    Alpha,                 // α
    Beta,                  // β
    Gamma,                 // γ
    Epsilon,               // ε
    Zeta,                  // ζ
    Eta,                   // η
    Mu,                    // μ
    Nu,                    // ν
    Xi,                    // Ξ
    Rho,                   // ρ
    Tau,                   // τ
    Phi,                   // Φ
    Psi,                   // Ψ
    Omega                  // Ω
};

constexpr const char* to_string(const MathSymbol symbol) {
    switch (symbol) {
            // Basic Math Operators
        case MathSymbol::Plus: return "+";
        case MathSymbol::Minus: return "-";
        case MathSymbol::Multiply: return "×";
        case MathSymbol::Divide: return "÷";

            // General
        case MathSymbol::Implies: return "⇒";
        case MathSymbol::NotImplies: return "⇏";
        case MathSymbol::IfAndOnlyIf: return "⇔";
        case MathSymbol::Increment: return "∆";

            // Relation
        case MathSymbol::Equals: return "=";
        case MathSymbol::NotEquals: return "≠";
        case MathSymbol::AlmostEqualsTo: return "≈";
        case MathSymbol::PlusMinus: return "±";
        case MathSymbol::LessThan: return "<";
        case MathSymbol::GreaterThan: return ">";
        case MathSymbol::LessThanOrEqual: return "≤";
        case MathSymbol::GreaterThanOrEqual: return "≥";
        case MathSymbol::ProportionalTo: return "∝";
        case MathSymbol::ApproximatelyEqual: return "≈";

            // Geometry
        case MathSymbol::Parallel: return "∥";
        case MathSymbol::NotParallel: return "∦";

            // Root Symbols
        case MathSymbol::SquareRoot: return "√";
        case MathSymbol::CubeRoot: return "∛";
        case MathSymbol::FourthRoot: return "∜";

            // Summation and Integral
        case MathSymbol::Summation: return "∑";
        case MathSymbol::Integral: return "∫";
        case MathSymbol::DoubleIntegral: return "∬";
        case MathSymbol::TripleIntegral: return "∭";
        case MathSymbol::ContourIntegral: return "∮";
        case MathSymbol::SurfaceIntegral: return "∯";
        case MathSymbol::VolumeIntegral: return "∰";

            // Miscellaneous
        case MathSymbol::Tilde: return "∼";
        case MathSymbol::RingOperator: return "∘";
        case MathSymbol::SineWave: return "∿";

            // Number Sets
        case MathSymbol::Naturals: return "ℕ";
        case MathSymbol::Integers: return "ℤ";
        case MathSymbol::Rationals: return "ℚ";
        case MathSymbol::Reals: return "ℝ";
        case MathSymbol::Complex: return "ℂ";
        case MathSymbol::ImaginaryPart: return "ℑ";
        case MathSymbol::RealPart: return "ℜ";
        case MathSymbol::Quaternions: return "ℍ";
        case MathSymbol::Primes: return "ℙ";

            // Set Notation
        case MathSymbol::OpenCurlyBrace2: return "{";
        case MathSymbol::CloseCurlyBrace2: return "}";
        case MathSymbol::Exists: return "∃";
        case MathSymbol::ForAll: return "∀";
        case MathSymbol::ElementOf: return "∈";
        case MathSymbol::NotElementOf: return "∉";
        case MathSymbol::ContainsAsMember: return "∋";
        case MathSymbol::NotContainsAsMember: return "∌";
        case MathSymbol::Subset: return "⊂";
        case MathSymbol::SubsetOrEqualTo: return "⊆";
        case MathSymbol::NotASubset: return "⊄";
        case MathSymbol::Superset: return "⊃";
        case MathSymbol::SupersetOrEqualTo: return "⊇";
        case MathSymbol::NotASuperset: return "⊅";
        case MathSymbol::EmptySet: return "∅";
        case MathSymbol::Therefore: return "∴";
        case MathSymbol::Because: return "∵";
        case MathSymbol::Intersection: return "∩";
        case MathSymbol::Union: return "∪";
        case MathSymbol::SuchThat: return "∣";
        case MathSymbol::DivisionSlash: return "⁄";
        case MathSymbol::OpenSquareBrace: return "[";
        case MathSymbol::CloseSquareBrace: return "]";

            // Logical Operators
        case MathSymbol::LogicalAnd: return "∧";
        case MathSymbol::LogicalOr: return "∨";
        case MathSymbol::LogicalNot: return "¬";

            // Infinity and Special Symbols
        case MathSymbol::Infinity: return "∞";
        case MathSymbol::MinusInfinity: return "-∞";

            // Aleph and Parentheses
        case MathSymbol::Aleph: return "ℵ";
        case MathSymbol::OpenParenthesis: return "(";
        case MathSymbol::CloseParenthesis: return ")";

            // Superscript and Subscript
        case MathSymbol::SuperscriptN: return "ⁿ";
        case MathSymbol::Superscript1: return "¹";
        case MathSymbol::Superscript2: return "²";
        case MathSymbol::Superscript3: return "³";
        case MathSymbol::SuperscriptPlus: return "⁺";
        case MathSymbol::SuperscriptMinus: return "⁻";
        case MathSymbol::Subscript1: return "₁";
        case MathSymbol::Subscript2: return "₂";
        case MathSymbol::Subscript3: return "₃";

            // Derivative Symbols
        case MathSymbol::Derivative: return "ⅆ";
        case MathSymbol::PartialDerivative: return "∂";
        case MathSymbol::Nabla: return "∇";
        case MathSymbol::DelSquared: return "∇²";
        case MathSymbol::VectorDiv: return "∇ ·";
        case MathSymbol::Laplace: return "∇²";

            // Vector Symbols
        case MathSymbol::VectorArrow: return "→";
        case MathSymbol::CrossProduct: return "×";
        case MathSymbol::DotProduct: return "⋅";

            // Matrices Symbols // TODO complete
        case MathSymbol::Matrix: return "⎠";
        case MathSymbol::MatrixTranspose: return "⊤";
        case MathSymbol::MatrixHermitian: return "⊲";

            // Like Letters
        case MathSymbol::Degree: return "°";
        case MathSymbol::EulerNumber: return "ℯ";
        case MathSymbol::Pi: return "π";
        case MathSymbol::Sigma: return "Σ";
        case MathSymbol::Delta: return "∆";
        case MathSymbol::Alpha: return "α";
        case MathSymbol::Beta: return "β";
        case MathSymbol::Gamma: return "γ";
        case MathSymbol::Epsilon: return "ε";
        case MathSymbol::Zeta: return "ζ";
        case MathSymbol::Eta: return "η";
        case MathSymbol::Mu: return "μ";
        case MathSymbol::Nu: return "ν";
        case MathSymbol::Xi: return "Ξ";
        case MathSymbol::Rho: return "ρ";
        case MathSymbol::Tau: return "τ";
        case MathSymbol::Phi: return "Φ";
        case MathSymbol::Psi: return "Ψ";
        case MathSymbol::Omega: return "Ω";
    }

    return "Unknown";
}



export inline std::ostream& operator<<(std::ostream& os, const MathSymbol& symbol) {
    os << to_string(symbol);
    return os;
}