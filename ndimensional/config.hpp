#pragma once

#include <type_traits>
#include <tuple>
#include <utility>

namespace nd {

    using size_t = std::size_t;

    template<size_t N>
    using size_constant = std::integral_constant<size_t, N>;
}

namespace nd::detail {
    template<class T> struct inner;
    template<class T> struct root { using type = T; };
    template<class T> struct dimension;
    template<class T> struct size;

    template<bool... Tests>
    constexpr bool all_v = (... && Tests);
}

// INTERFACES
namespace nd {

    template<size_t... Sizes>
    struct dimension_pack : size_constant<sizeof...(Sizes)> {
        static constexpr auto sizes = std::array<size_t, sizeof...(Sizes)>{ Sizes... };
        static constexpr auto values() noexcept {
            return sizes;
        }
    };

    template<class T> struct first;
    template<class T> constexpr size_t first_v = first<std::decay_t<T>>::value;

    template<size_t Size, size_t... Sizes>
    struct first<dimension_pack<Size, Sizes...>> : size_constant<Size> { };

    template<class T> struct remaining;
    template<class T> using remaining_t = typename remaining<std::decay_t<T>>::type;

    template<size_t Size, size_t... Sizes>
    struct remaining<dimension_pack<Size, Sizes...>> { using type = dimension_pack<Sizes...>; };

    template<class Array>
    using inner_type = typename detail::inner<std::decay_t<Array>>::type;

    template<class Array>
    using root_type = typename detail::root<std::decay_t<Array>>::type;

    template<class T>
    constexpr size_t dimension_v = detail::dimension<std::decay_t<T>>::value;

    template<class Array>
    constexpr size_t size_v = detail::size<std::decay_t<Array>>::value;

    template<class Array>
    constexpr bool is_single_dimension = (dimension_v<Array> == 1);

    template<class Array, class Value>
    constexpr bool is_convertible_root_type = std::is_convertible_v<Value, root_type<Array>>;
}