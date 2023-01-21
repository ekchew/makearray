#ifndef MAKEARRAY_HPP
#define MAKEARRAY_HPP

#include <array>
#include <utility>

/*---- MakeArray function template --------------------------------------------
 *
 *  MakeArray returns a std::array of explicit type T and inferred size.
 *  It takes a parameter pack of arguments that must be convertible to T, and
 *  the array size is taken from the number of arguments.
 *
 *  Example:
 *
 *     auto arr = MakeArray<float>(1, 2, 3.5);
 *
 *  This returns a std::array<float,3> containing {1.0f, 2.0f, 3.5f} as arr.
 */

template<typename T, typename... Args>
    constexpr auto MakeArray(Args&&... args){
        return std::array<T, sizeof...(Args)>{std::forward<T>(args)...};
    }

#endif
