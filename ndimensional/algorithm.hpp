#pragma once

#include "ndimensional/config.hpp"
#include "ndimensional/iterate.hpp"
#include "ndimensional/array.hpp"

namespace nd::detail {

    template<class To, class From>
    struct swap_type;

    template<class To, class From, class Dimensions>
    struct swap_type<To, array<From, Dimensions>> {
        using type = array<To, Dimensions>;
    };

    template<class To, class Container>
    using swap_type_t = typename swap_type<To, Container>::type;

    template<size_t To, class From>
    struct swap_size;

    template<size_t To, class T, size_t From, size_t... Sizes>
    struct swap_size<To, array<T, dimension_pack<From, Sizes...>>> {
        using type = array<T, dimension_pack<To, Sizes...>>;
    };

    template<size_t To, class Container>
    using swap_size_t = typename swap_size<To, Container>::type;

    template<bool Expected, class T, class Func>
    constexpr bool all_of(T items, Func func) noexcept {
        for (auto it = iterate(items); it; ++it) {
            if constexpr (is_single_dimension<T>) {
                if (func(*it) == Expected) return Expected;
            }
            else {
                if (all_of<Expected>(*it, func) == Expected) return Expected;
            }
        }
        return !Expected;
    }
}

namespace nd {

    template<class T, class Func>
    constexpr bool all_of(T items, Func func) noexcept {
        return detail::all_of<false>(items, func);
    }

    template<class T, class Func>
    constexpr bool any_of(T items, Func func) noexcept {
        return detail::all_of<true>(items, func);
    }

    template<class T, class Func>
    constexpr bool none_of(T items, Func func) noexcept {
        return !(any_of(items, func));
    }

    template<class T, class V>
    constexpr auto accumulate(T items, V initial) noexcept -> root_type<T> {
        auto result = static_cast<root_type<T>>(initial);
        for (auto it = iterate(items); it; ++it) {
            if constexpr (is_single_dimension<T>) {
                result *= (*it);
            }
            else {
                result *= sum(*it, result);
            }
        }
        return result;
    }

    template<class T>
    constexpr auto sum(T items) noexcept -> root_type<T> {
        auto result = root_type<T>{ 0 };
        for (auto it = iterate(items); it; ++it) {
            if constexpr (is_single_dimension<T>) {
                result += *it;
            }
            else {
                result += sum(*it);
            }
        }
        return result;
    }

    template<class T, class V>
    constexpr auto assign(T items, V value) noexcept {
        for (auto it = iterate(items); it; ++it) {
            if constexpr (is_single_dimension<T>) {
                *it = value;
            }
            else {
                *it = assign(*it, value);
            }
        }
        return items;
    }

    template<class T, class Func>
    constexpr auto transform(T items, Func func) noexcept {
        using func_result_t = std::decay_t<decltype(func(root_type<T>{}))>;
        using result_type = detail::swap_type_t<func_result_t, T>;
        auto result = result_type{};
        for (auto it = iterate(result); it; ++it) {
            auto index = distance(it);
            auto& rhs = items[index];
            if constexpr (is_single_dimension<T>) {
                *it = func(rhs);
            }
            else {
                *it = transform(rhs, func);
            }
        }
        return result;
    }

    template<size_t Offset, size_t Count, class T>
    constexpr auto range(T items) noexcept {
        static_assert((Count + Offset) < size_v<T>);
        using result_type = detail::swap_size_t<Count, T>;
        auto result = result_type{};
        for (auto it = iterate(items, Offset, Count); it; ++it) {
            auto& current = result[distance(it)];
            if constexpr (is_single_dimension<T>) {
                current = *it;
            }
            else {
                current = sum(*it);
            }
        }
        return result;
    }

    template<size_t Offset, class T>
    constexpr auto range(T items) noexcept {
        static_assert(Offset < size_v<T>);
        constexpr auto count = size_v<T> - Offset;
        return range<Offset, count>(items);
    }

    template<class T, class Pred>
    constexpr auto adjacent_find(T items, Pred pred) {
        auto first = iterate(items);
        auto last = first + size_v<T>;
        for (auto next = first; ++next != last; first = next) {
            if (is_single_dimension<T>){
                if (pred(*first, *next)) {
                    last = first;
                    break;
                }
            }
            else {
                auto it = adjacent_find(*next, pred);
                if (!it) continue;
                return it;
            }
        }
        return last;
    }

    template<class T, class V, class IndexPack>
    static constexpr auto set(T items, V value, IndexPack) noexcept {
        constexpr size_t index = first_v<IndexPack>;
        if constexpr (is_single_dimension<T>) {
            items[index] = value;
        }
        else {
            using remaining_t = remaining_t<IndexPack>;
            items[index] = set(items[index], value, remaining_t{});
        }
        return items;
    }
}