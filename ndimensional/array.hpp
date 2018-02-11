#pragma once

#include <array>
#include "ndimensional/config.hpp"
#include "ndimensional/iterate.hpp"

namespace nd::detail {

    template<class T, class Dimensions>
    class array;

    template<class T, class Dimensions>
    struct base;

    template<class T, class Dimensions>
    using base_type = typename base<T, Dimensions>::type;

    template<class T, size_t Size>
    struct base<T, dimension_pack<Size>> {
        using type = std::array<T, Size>;
    };

    template<class T, class Dimensions>
    struct base {
        using type = std::array<array<T, remaining_t<Dimensions>>, first_v<Dimensions>>;
    };

    template<class T, class Dimensions>
    class array : public base_type<T, Dimensions> {
        static_assert(!std::is_same_v<Dimensions, dimension_pack<>>);
        using base_t = base_type<T, Dimensions>;

    public:
        using dim_pack = Dimensions;
        constexpr auto sizes() const noexcept {
            return dim_pack::values();
        }

        template<class... Args>
        constexpr array(Args&&... args) noexcept
            : base_t{ std::forward<Args>(args)... } {
            constexpr size_t arg_count = sizeof...(Args);
            constexpr bool is_default = (arg_count == 0);
            constexpr bool is_move = (arg_count == 1);
            constexpr bool is_initializer_list = (arg_count == first_v<Dimensions>);
            static_assert(is_default || is_move || is_initializer_list);
            if constexpr (is_initializer_list) {
                using std::is_constructible_v;
                static_assert(all_v<is_convertible_v<Args, inner_type<array>>...>);
                static_assert(all_v<is_convertible_v<root_type<Args>, T>...>);
            }
        }
    };
}

namespace nd::detail {

    // immediate (n-1) inner type for n-dimensional array
    template<class T, class Dimensions>
    struct inner<array<T, Dimensions>> {
        using type = array<T, remaining_t<Dimensions>>;
    };

    // "decay" to the inner-most (root) type
    template<class T, class Dimensions>
    struct root<array<T, Dimensions>> {
        using type = T;
    };

    // number of sizes (dimensions) in a given array
    template<class T, class Dimensions>
    struct dimension<array<T, Dimensions>>
        : size_constant<Dimensions::values().size()> { };

    // size of current dimension
    template<class T, class Dimensions>
    struct size<array<T, Dimensions>>
        : size_constant<first_v<Dimensions>> { };


    // immediate (n-1) inner type for n-dimensional array
    template<class T, size_t Size>
    struct inner<std::array<T, Size>> {
        using type = root_type<T>;
    };

    // "decay" to the inner-most (root) type
    template<class T, size_t Size>
    struct root<std::array<T, Size>> {
        using type = T;
    };

    // number of sizes (dimensions) in a given array
    template<class T, size_t Size>
    struct dimension<std::array<T, Size>>
        : size_constant<1> { };

    // size of current dimension
    template<class T, size_t Size>
    struct size<std::array<T, Size>>
        : size_constant<Size> { };
}

namespace nd {

    // n-dimensional array type
    template<class T, size_t... Sizes>
    using array = detail::array<T, dimension_pack<Sizes...>>;
}