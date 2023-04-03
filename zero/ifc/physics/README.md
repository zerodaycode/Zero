# The Physics library

The `Physics Library` inside `Zero` born out of the idea of *are we able to code a Physics degree in C++?*

For that, we designed here a full set of tools that allows the user to naturally work with concepts related
with a job of a physicist. This includes a library for handling physical quantities, a set of predefined
constant values (typically known as physical constants), tools for make problems solving, based on
the ecuations, systems of ecuations and the other tools provided by the `math library of Zero`... 

## Sub-libraries

### Quantities
This library contains types and operations to reflect the natural measurement and calculations of physics quantities,
in the same terms that are defined by the `SI`.

- The library is designed to be completely `compile-time` usable, providing a high-efficient, type safe
API.

- Provides a whole set of basic arithmetic operations (`+`, `-`, `*`, `/`), that are usable between
quantities that holds magnitudes with the same dimension (for bases) or the same dimensionality (for derived)
- Provides convenient member functions to retrieve data about the types that made any of the entities. i.e:
print the dimensions of a speed, or the units of Kilogram.
- Provides convenient member functions to `convert` between units with the same `dimension` or `dimensionality`

- Provides all the `SI` defined `base dimensions` and `base units`
  - Length [L] - meter [m]
  - Time [T] - second [s]
  - Mass [M] kilogram [kg]
  - Temperature [θ] - kelvin [K]
  - Electric Current [I] - ampere [A]
  - Amount of Substance [N]- mole [mol]
  - Luminous Intensity [J] - candela [cd]
  - Dimensionless [l] - unitless []
  
- Provides in addition, some of the "equivalent by ratio" units, for example `Kilometer (m³)`, `Hour (s²)` and so on.
- Provides a set of well known `derived dimensions` and `derived units`, like `MetersPerSecond`,
`Newton` or `KilometersPerHour`.

- Provides an *easy-to-extend* client API. This means, that you, as user, can define a new whole entity,
like a `base unit` or a `derived unit`, by simply **tag** your types with the correct base types that
we provide, making your entities completely interoperable with the ones already defined in the library

### Types by categories

Almost everything in the library is defined as a (strong) type. We can categorize it as:

- `quantity` - The aggregate type that holds the value for a certain physical quantity, and provides the
the convenient operations to manipulate them
- `Units`
  - `base_unit` - Defines what a base unit is, given a `base_dimension`, a ratio` and a `symbol`
  - `derived_unit` - Defines what a derived unit is, given an already defined `derived dimension`
- `Dimensions`
  - `base_dimension` - A CRTP base class that defines the base dimensions of the `SI`. Depends on an
  scalar value, called `dimension exponent`, that serves to indicate whenever a unit is a numerator
  or a denominator in the units declared for a `quantity`, ie: `MetersPerSecond` implies `m¹ / s¹` or, as we use it
  in our code, `m¹ * s⁻¹`
  - `derived_dimension` - Defines a derived dimension by taking a variadic pack or `BaseUnit...`
- `ratio` - Predefined declarations for the ratios of every `SI` unit. Basically, is a power, represented
as a template that takes a type for determine the value type of the other two template arguments, which are
the relevant ones here: `Base` and `Exponent`. Given these, we defined a set of `type alias` for representing
the ratio of a `SI` unit. ie: `using kilo = ratio<short, 10, 3>;` gives us a ratio for use in a `base_unit`, declaring
that the target `base_unit` is a unit with the dimension specified by the other mandatory dimension tag and with a ratio of kilo.
For example:
`struct Kilogram: public mass<1>, public base_unit<kilo, kg> {};`
- `unit_symbol` - A CRTP base type for define strong types for the units. As seen above, `kg` in the strong type
for define the symbol of kilogram, according to the `SI`

## Conversion

We provide in the API an easy way to convert quantities of the same dimension (for the bases) or with the
same dimensionality (for derived) with a simple template member function called `to<Magnitude Target>`.
Here's an example:

```
constexpr auto velocity = quantity<MetersPerSecond>(300'000);

quantity<KilometersPerHour> kmph = velocity.to<KilometersPerHour>();
quantity<MetersPerSecond> mps = kmph.to<MetersPerSecond>();

std::cout << "Converting meters per second to kilometers per hour: " << kmph << "\n"; // Prints 1'080'000
std::cout << "Converting kilometers per hour to meters per second: " << mps << "\n";  // Prints 300'000
```