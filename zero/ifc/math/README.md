# The Math library

This library aims to provide mathematical operations, operators and symbols, for being used
in standalone mathematical operations or in more complex environments, like solving problems
in diverse science fields.

##  Numbers
This module brings certain types for represents and operate with some sets of numbers that exists in maths.
 - Natural Numbers (ℕ)
 - Integers (ℤ)
 - Rationals (ℚ)
 - Irrationals ( /* Not yet implemented */ )
 - Reals (ℝ)
 - ComplexNumbers (ℂ)
 - Quaternions (ℍ)
 - Primes (ℙ)

## Ops
TODO

## Linear Algebra
TODO

## Symbols

This module provides the most useful mathematical symbols to be used in string representations.
Here is the list of the ones that are implemented as the variants of the enum `MathSymbol`:

```c++
    // Basic Math Operators
    Plus = 0x002B,                  // +
    Minus = 0x2212,                 // -
    Multiply = 0x00D7,              // ×
    Divide = 0x00F7,                // ÷

    // General
    Implies = 0x21D2,               // ⇒
    NotImplies = 0x21CF,            // ⇏
    IfAndOnlyIf = 0x21CF,           // ⇔
    Increment = 0x2206,             // ∆

    // Relation
    Equals = 0x003D,                // =
    NotEquals = 0x2260,             // ≠
    AlmostEqualsTo = 0x2248,        // ≈
    PlusMinus = 0x00B1,             // ±
    LessThan = 0x003C,              // <
    GreaterThan = 0x003E,           // >
    LessThanOrEqual = 0x2264,       // ≤
    GreaterThanOrEqual = 0x2265,    // ≥
    ProportionalTo = 0x221D,        // ∝
    ApproximatelyEqual = 0x2248,    // ≈

    // Geometry
    Parallel = 0x2225,              // ∥
    NotParallel = 0x2226,           // ∦

    // Root Symbols
    SquareRoot = 0x221A,            // √
    CubeRoot = 0x221B,              // ∛
    FourthRoot = 0x221C,            // ∜

    // Summation and Integral
    Summation = 0x2211,             // ∑
    Integral = 0x222B,              // ∫
    DoubleIntegral = 0x222C,        // ∬
    TripleIntegral = 0x222D,        // ∭
    ContourIntegral = 0x222E,       // ∮
    SurfaceIntegral = 0x222F,       // ∯
    VolumeIntegral = 0x2230,        // ∰

    // Miscellaneous
    Tilde = 0x223C,                 // ∼
    RingOperator = 0x2218,          // ∘
    SineWave = 0x223F,              // ∿

    // Number Sets
    NaturalNumbers = 0x2115,        // ℕ
    Integers = 0x2124,              // ℤ
    Rationals = 0x211A,             // ℚ
    Reals = 0x211D,                 // ℝ
    ComplexNumbers = 0x2102,        // ℂ

    // Set Notation
    OpenCurlyBrace2 = 0x007B,       // {
    CloseCurlyBrace2 = 0x007D,      // }
    Exists = 0x2203,                // ∃ (Exists)
    ForAll = 0x2200,                // ∀ (For All)
    ElementOf = 0x2208,             // ∈
    NotElementOf = 0x2209,          // ∉
    ContainsAsMember = 0x220B,      // ∋ (As member)
    NotContainsAsMember = 0x220C,   // ∌ (As member)
    Subset = 0x2282,                // ⊂
    SubsetOrEqualTo = 0x2286,       // ⊆
    NotASubset = 0x2284,            // ⊄
    Superset = 0x2285,              // ⊃
    SupersetOrEqualTo = 0x2287,     // ⊇
    NotASuperset = 0x2285,          // ⊅
    EmptySet = 0x2205,              // ∅
    Therefore = 0x2234,             // ∴
    Because = 0x2235,               // ∵
    Intersection = 0x2229,          // ∩
    Union = 0x222A,                 // ∪
    SuchThat = 0x2223,              // ∣
    DivisionSlash = 0x2044,         // ⁄ (Division Slash)
    OpenSquareBrace = 0x005B,       // [
    CloseSquareBrace = 0x005D,      // ]

    // Logical Operators
    LogicalAnd = 0x2227,            // ∧
    LogicalOr = 0x2228,             // ∨
    LogicalNot = 0x00AC,            // ¬

    // Infinity and Special Symbols
    Infinity = 0x221E,              // ∞
    MinusInfinity = 0x2212,         // -∞

    // Aleph and Parentheses
    Aleph = 0x2135,                 // ℵ
    OpenParenthesis = 0x0028,       // (
    CloseParenthesis = 0x0029,      // )

    // Superscript and Subscript
    SuperscriptN = 0x207F,          // ⁿ (Superscript n)
    Superscript1 = 0x00B9,          // ¹ (Superscript 1)
    Superscript2 = 0x00B2,          // ² (Superscript 2)
    Superscript3 = 0x00B3,          // ³ (Superscript 3)
    SuperscriptPlus = 0x207A,       // ⁺ (Superscript Plus)
    SuperscriptMinus = 0x207B,      // ⁻ (Superscript Minus)
    Subscript1 = 0x2081,            // ₁ (Subscript 1)
    Subscript2 = 0x2082,            // ₂ (Subscript 2)
    Subscript3 = 0x2083,            // ₃ (Subscript 3)

    // Derivative Symbols
    Derivative = 0x2146,            // ⅆ (Derivative of)
    PartialDerivative = 0x2202,     // ∂ (Partial Derivative)
    Nabla = 0x2207,                 // ∇ (Nabla)
    DelSquared = 0x2207,            // ∇² (Del Squared)
    VectorDiv = 0x2207,             // ∇ · (Divergence)
    Laplace = 0x2207,               // ∇² (Laplace Operator)

    // Vector Symbols
    VectorArrow = 0x2192,           // → (Vector Arrow)
    CrossProduct = 0x00D7,          // × (Cross Product)
    DotProduct = 0x22C5,            // ⋅ (Dot Product)

    // Matrices Symbols // TODO complete
    Matrix = 0x23A0,                // ⎠ (Matrix)
    MatrixTranspose = 0x22A4,       // ⊤ (Matrix Transpose)
    MatrixHermitian = 0x22B2,       // ⊲ (Matrix Hermitian)

    // Degree and Greek Letters
    Degree = 0x00B0,                // °
    Pi = 0x03C0,                    // π
    Sigma = 0x03A3,                 // Σ
    Delta = 0x2206,                 // ∆
    Alpha = 0x03B1,                 // α
    Beta = 0x03B2,                  // β
    Gamma = 0x03B3,                 // γ
    Epsilon = 0x03B5,               // ε
    Zeta = 0x03B6,                  // ζ
    Eta = 0x03B7,                   // η
    Mu = 0x03BC,                    // μ
    Nu = 0x03BD,                    // ν
    Xi = 0x039E,                    // Ξ
    Rho = 0x03C1,                   // ρ
    Tau = 0x03C4,                   // τ
    Phi = 0x03A6,                   // Φ
    Psi = 0x03A8,                   // Ψ
    Omega = 0x03A9,                 // Ω
```

> Please, everytime that a new symbol is added to the enumerated type, remember to add
> it to this documentation for having the complete reference of the symbols implemented in the library.