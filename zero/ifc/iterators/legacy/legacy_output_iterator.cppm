export module iterator:legacy_output_iterator;

import :legacy_iterator;
import std;
import type_info;

template <typename T>
using base_it = zero::iterator::legacy::iterator<
    std::output_iterator_tag, void, void, void
>;

export namespace zero::iterator::legacy {
    /**
     * @brief A generic implementation of an output_iterator
     */
    template <typename T>
    struct output_iter: base_it<T> {
        private:
            T* _elem;

        public:
            output_iter<T>() = default;
            output_iter(T& elem) : _elem(&elem) {}

            constexpr output_iter<T>(const output_iter<T>& other) = default;
            constexpr output_iter<T>(output_iter<T>&& other) noexcept = default;

            constexpr auto operator=(const output_iter&) -> output_iter& = default;
            
            template <typename U>
            constexpr auto operator=(const U& val) -> output_iter& {
                if constexpr (std::is_base_of_v<std::ostream, std::remove_reference_t<T>>) {
                    *_elem << val;
                } else {
                    if constexpr (std::is_same_v<decltype(_elem->push_back(val)), void>) {
                        _elem->push_back(val);
                    } else {
                        *_elem++ = val;
                    }
                }
                return *this;
            }

            [[nodiscard]]
            constexpr auto operator*() -> output_iter<T>& {
                return *this;
            }

            constexpr auto operator->() const -> output_iter* = delete;

            constexpr auto operator++() -> output_iter<T>& {
                return *this;
            }

            constexpr auto operator++(int) -> output_iter<T> {
                return *this;
            }

            [[nodiscard]]
            constexpr friend auto operator==(const output_iter& lhs, const output_iter& rhs) noexcept -> bool {
                return lhs._elem == rhs._elem;
            }

            [[nodiscard]]
            constexpr friend auto operator!=(const output_iter& lhs, const output_iter& rhs) noexcept -> bool {
                return not (lhs == rhs);
            }
    };
}