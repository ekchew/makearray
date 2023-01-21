#ifndef MAKEARRAY_HPP
#define MAKEARRAY_HPP

#include "concepts_check.hpp"

#include <array>
#include <utility>

/*---- MakeArray function template --------------------------------------------
 *
 *  MakeArray returns a std::array of explicit type T and inferred size.
 *  It takes a parameter pack of arguments that must be implicitly convertible
 *  to T, and the array size is taken from the number of arguments.
 *
 *  Example:
 *
 *     auto arr = MakeArray<std::string>("foo", "bar", "baz");
 *
 *  This returns a std::array<std::string,3> containing the 3 string literals
 *  copied into std::string objects.
 */

#if CONCEPTS_AVAILABLE
  template<typename T, std::convertible_to<T>... Args>
#else
  template<typename T, typename... Args>
#endif
    constexpr auto MakeArray(Args&&... args) {
        return std::array<T, sizeof...(Args)>{std::forward<Args>(args)...};
    }

/*---- MakeArrayWithCast ------------------------------------------------------
 *
 *  This variation on MakeArray explicitly casts each argument to type T.
 *  
 *  Example:
 *      auto arr = MakeArrayWithCast<float>(1, 2, 3.5);
 * 
 *  The regular MakeArray would likely fail to convert int or double to float
 *  implicitly due to narrowing errors.
 */

template<typename T, typename... Args>
    constexpr auto MakeArrayWithCast(Args&&... args) {
        return std::array<T, sizeof...(Args)>{
            static_cast<T>(std::forward<Args>(args))...
            };
    }

#endif
