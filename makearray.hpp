#ifndef MAKEARRAY_HPP
#define MAKEARRAY_HPP

#include "concepts_check.hpp"

#include <array>
#include <utility>

namespace details {
    // Each arg passed to MakeArray() gets wrapped in a struct with an
    // overloaded << operator that assigns it to a std::array iterator.
    // This allows MakeArray() to build a C++17 fold expression around <<.
    template<typename T> struct MakeArrayArg{ T&& v; };
    template<typename It, typename T> constexpr
        auto operator << (It it, MakeArrayArg<T> arg) -> It {
            *it = std::forward<T>(arg.v);
            return ++it;
        }
}

/*---- MakeArray function template --------------------------------------------
 *
 *  MakeArray returns a std::array of explicit type T and inferred size.
 *  It takes a parameter pack of arguments that must be convertible to T, and
 *  the array size is taken from the number of arguments. The array is
 *  initially default-constructed before the arguments get copy/move-assigned
 *  to their corresponding array elements, meaning T must be
 *  default-constructible.
 *
 *  Example:
 *
 *     auto arr = MakeArray<float>(1, 2, 3.5);
 *
 *  This returns a std::array<float,3> containing {1.0f, 2.0f, 3.5f} as arr.
 */

#if CONCEPTS_AVAILABLE
    template<std::default_initializable T, std::convertible_to<T>... Args>
#else
    template<typename T, typename... Args>
#endif
    constexpr auto MakeArray(Args&&... args) {
        static_assert(
            __cplusplus > 201402L, "MakeArray() requires C++17 or later"
            );
        std::array<T, sizeof...(Args)> arr;
        auto it = arr.begin();
        (it << ... << details::MakeArrayArg<T>{std::forward<T>(args)});
        return arr;
    }


#endif
