export module iterator:legacy_output_iterator;

import :legacy_iterator;
import std;
import type_info;

template <typename T>
using base_it = zero::iterator::legacy::iterator<
    std::output_iterator_tag, T
>;

export namespace zero::iterator::legacy {
    /**
     * @brief A generic implementation of an output_iterator
     */
    template <typename T>
    struct output_iter: base_it<T> {
        private:
            typename base_it<T>::pointer _elem;

        public:
            output_iter<T>() = default;
            explicit output_iter<T>(T& elem = nullptr)
                : _elem(std::addressof(elem)) {}
            ~output_iter<T>() = default;
            constexpr output_iter<T>(const output_iter<T>& other) = default;
            constexpr output_iter<T>(output_iter<T>&& other) noexcept = default;

constexpr auto operator=(const output_iter&) -> output_iter& = default;
// template <typename U>
// constexpr auto operator=(const U& val) -> output_iter& {
//     // if constexpr (std::is_same_v<T, std::ostream>)
//     // if constexpr (requires { typename T::ostream_type; } ) {
//         // if constexpr (std::is_same_v<T, std::ostream_iterator<U>>) {    
//             *_elem << val;
//         // } 
//     // } else {
//     //     _elem->push_back(val);
//     // }
//     return *this;
// }

// template <typename U>
// constexpr auto operator=(const U& val) -> output_iter& {
//     // if constexpr (std::is_same_v<std::decay_t<decltype(*_elem)>, std::ostream_iterator<U>>) {
//         *_elem = val;
//     // } 
//     // else {
//     //     _elem->push_back(val);
//     // }
//     return *this;
// }

// template <typename U>
// constexpr auto operator=(const U& val) -> output_iter& {
//     if constexpr (std::is_same<T, std::ostream_iterator<int>>::value) {
//         *_elem << val;
//         return *this;
//     } else {
//         _elem->push_back(val);
//         return *this;
//     }
// }




            // TODO move to the details namespace
            /** 
             * @details proxy-object to constrain operator*() to writing only
             * The proxy object is a temporary object returned by the operator*() overload.
             * When the user tries to dereference the iterator using *it, the operator*() overload
             * returns this proxy object instead of the value stored at the iterator's current position. 
             *
             *  The proxy object has a member function operator= that takes a value to be written to the
             * iterator. This function is called when the user tries to write a value to the iterator using *it = value.
             * 
             * By using this proxy object, we can ensure that the output iterator only allows the user to write
             * values, and not to read them. If the user tries to read the value at the iterator's current position,
             * the proxy object will not have a member function to allow this, preventing the user from doing so.
            */
            struct output_proxy {
                output_iter<T>& iter;
                explicit output_proxy(output_iter<T>& it) : iter(it) {}
                auto operator=(const T& value) -> output_proxy& {
                    iter = value;
                    return *this;
                }
                /**
                 * @brief By deleting the conversion operator that would convert the output iterator to a
                 * reference to the underlying type, we are preventing the user from inadvertently reading
                 * the value at the iterator's current position
                 */
                operator T&() = delete;
            };

            constexpr auto operator*() -> output_proxy {
                return output_proxy(*this);
            }

            // constexpr auto operator->() const -> output_iter* = delete;

            constexpr auto operator++() -> output_iter<T>& {
                return *this;
            }

            constexpr auto operator++(int) -> output_iter<T> {
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