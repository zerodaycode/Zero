/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 * 
 * A physical quantity can be undestand as a real world magnitude, related with
 * their units in the international system
 */

export module physics:quantities;
import :ratios;
import std;

namespace __details {
    // TODO Move this to the concepts module
    template<class T, class U>
    struct same_template {
        static auto test(...) -> std::false_type;

        template<template<class...> class C, class... R1s, class... R2s>
        static auto test(C<R1s...>, C<R2s...>) -> std::true_type;

        static constexpr bool value = decltype(test(std::declval<T>(), std::declval<U>()))::value;
    };

    template<class T, class U>
    inline constexpr bool same_template_v = same_template<T, U>::value;

    template<class T, class U>
    concept SameTemplate = same_template_v<T, U>;
}

export namespace zero::physics {
    template<typename T>
    struct unit_symbol {
        using symbol = T;
    };

    template<typename T>
    concept Symbol = requires {
        typename T::symbol;
    };
    
    struct kg: unit_symbol<kg> {};
    struct hg: unit_symbol<hg> {};
    struct m: unit_symbol<m> {};


    template<Ratio prefix, Symbol S>
    struct base_unit {};

    template<Ratio prefix, Symbol S>
    class base_magnitude {};


    template <Ratio R, Symbol S>
    class mass: public base_magnitude<R, S> {};
    template<Ratio R, Symbol S>
    class length : public base_magnitude<R, S> {};

    template <typename T>
    concept Magnitude = requires {
        typename T::dimension;
        typename T::ratio;
    };

    template <typename T, typename R>
    concept SameDimension = requires {
        requires Magnitude<T> && Magnitude<R>;
        requires __details::SameTemplate<typename T::dimension, typename R::dimension>;
    };

    struct Kilogram: public mass<Kilo, kg> {
        using dimension = mass;
        using ratio = Kilo;
    };
    struct Hectogram: public mass<Hecto, hg> {
        using dimension = mass;
        using ratio = Hecto;
    };

    struct Meter: public length<Root, m> {
        using dimension = length;
        using ratio = Hecto;
    };

    
    template <typename T>
    concept ValidAmountType = (std::is_integral_v<T> || std::is_floating_point_v<T>)
        && !std::is_same_v<T, char>;

    template <Magnitude M, ValidAmountType T = double>
    struct quantity {
        T amount;
        constexpr quantity<M, T>() noexcept = default;
        constexpr explicit quantity<M, T>(T val) noexcept : amount(val) {}
    };

    template<Magnitude M1, Magnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
        requires SameDimension<M1, M2>
    [[nodiscard]] 
    constexpr auto operator+(const quantity<M1, T1>& lhs, const quantity<M2, T2>& other) 
        -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>>
    {
        if constexpr (M1::ratio::value > M2::ratio::value)
            return quantity<M1, T1>(lhs.amount + other.amount);
        else
            return quantity<M2, T2>(lhs.amount + other.amount);
    }

    template<typename M>
    constexpr std::ostream& operator<<(std::ostream& os, const quantity<M>& q) {
        os << q.amount;
        return os;
    }
}

static_assert(zero::physics::Symbol<zero::physics::kg>);