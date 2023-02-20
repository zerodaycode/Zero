export module iterator:legacy_output_iterator;

import concepts;
import :legacy_iterator;
import std;

template <typename T>
using base_it = zero::iterator::legacy::iterator<
    std::output_iterator_tag, void, void, void>;

export namespace zero::iterator::legacy
{
    /**
     * @brief A generic implementation of an output_iterator
     */
    template <typename T>
    struct output_iter : base_it<T> {
    private:
        T *_elem;

        // TODO move this to the details partition
        /** 
         * @details A proxy helper class for the output_iter class.
        *
        * The output_iter_proxy class is used to facilitate assignment operations with an
        * output iterator while preventing the user from reading from it
        */
        template <typename Z>
        struct output_iter_proxy {
            output_iter<Z> &_iter;

            constexpr output_iter_proxy(output_iter<Z> &iter) noexcept : _iter(iter) {}

            template <typename U>
            constexpr auto operator=(const U &val) -> output_iter_proxy& {
                _iter = val;
                return *this;
            }

            /**
             * @brief Assigns a value to the output iterator.
             *
             * @tparam U The type of the value being assigned.
             * @param val The value being assigned to the output iterator.
             * @return output_iter_proxy& A reference to the output_iter_proxy object.
             */
            template <typename U>
            operator const U&() const = delete;
        };

    public:
        constexpr output_iter<T>() noexcept = default;
        constexpr output_iter(T &elem) noexcept : _elem(&elem) {}

        constexpr output_iter<T>(const output_iter<T> &other) = default;
        constexpr output_iter<T>(output_iter<T> &&other) noexcept = default;

        template <typename U>
        constexpr auto operator=(const U &val) -> output_iter & {
            if constexpr (std::is_base_of_v<std::ostream, std::remove_reference_t<T>>)
                *_elem << val;
            else if constexpr (zero::concepts::has_push_back<std::remove_reference_t<T>, const U &>)
                _elem->push_back(val);
            else
                *_elem++ = val;
            return *this;
        }

        [[nodiscard]]
        constexpr auto operator*() -> output_iter_proxy<T> {
            return output_iter_proxy<T>(*this);
        }

        constexpr auto operator->() const -> output_iter* = delete;

        constexpr auto operator++() noexcept -> output_iter<T>& {
            return *this;
        }

        constexpr auto operator++(int) noexcept -> output_iter<T> {
            return *this;
        }

        [[nodiscard]]
        constexpr friend auto operator==(const output_iter& lhs, const output_iter& rhs) noexcept -> bool {
            return lhs._ptr == rhs._ptr;
        }

        [[nodiscard]]
        constexpr friend auto operator!=(const output_iter& lhs, const output_iter& rhs) noexcept -> bool {
            return not (lhs == rhs);
        }
    };

}