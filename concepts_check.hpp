#ifndef CONCEPTS_CHECK_HPP
#define CONCEPTS_CHECK_HPP

/*---- CONCEPTS_AVAILABLE Macro -----------------------------------------------
 *
 *  This header defines a CONCEPTS_AVAILABLE macro which evaluates true if and
 *  only if C++20 concepts are available as a language feature, together with
 *  the expected standard library of pre-defined concepts.
 *
 *  If available, the <concepts> header will also be included automatically.
 */

#if __cplusplus > 201703L
    #if __has_include(<version>)
        #include <version>
    #else
        #include <concepts>
    #endif
    #if defined(__cpp_concepts) && defined(__cpp_lib_concepts)
        #define CONCEPTS_AVAILABLE 1
        #if __has_include(<version>)
            #include <concepts>
        #endif
    #endif
#endif
#ifndef CONCEPTS_AVAILABLE
    #define CONCEPTS_AVAILABLE 0
#endif

#endif
