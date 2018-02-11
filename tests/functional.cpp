#include "tests/common.hpp"
#include "ndimensional/functional.hpp"

using namespace nd::tests;

template<class Func, class Tuple, size_t... Indices>
constexpr bool test_types_impl(Func& func, Tuple tuple, std::index_sequence<Indices...>) {
    return ( ... && func(std::get<Indices>(tuple)));
}

template<class Func, class... Types>
constexpr bool test_types(Func& func, std::tuple<Types...> values) {
    return test_types_impl(func, values, std::make_index_sequence<sizeof...(Types)>{});
}

template<class... Types>
struct test_types_tuple {
    constexpr auto operator()(int value) const noexcept {
        return std::make_tuple(static_cast<Types>(value)...);
    }
};

constexpr auto for_each_type = test_types_tuple<double, int, size_t, float, long>{};

TEST_METHOD(equal_to) {
    static_assert(nd::equal_to(2.5)(2.5));
    constexpr auto func = nd::equal_to(2);
    static_assert(test_types(func, for_each_type(2)));
    static_assert(!test_types(func, for_each_type(1)));
    static_assert(!test_types(func, for_each_type(3)));
}

TEST_METHOD(not_equal_to) {
    static_assert(nd::not_equal_to(2.5)(3.5));
    constexpr auto func = nd::not_equal_to(2);
    static_assert(test_types(func, for_each_type(1)));
    static_assert(!test_types(func, for_each_type(2)));
    static_assert(test_types(func, for_each_type(3)));
}

TEST_METHOD(greater) {
    static_assert(nd::greater(2.5)(3.5));
    static_assert(!nd::greater(2.5)(2.5));
    constexpr auto func = nd::greater(2);
    static_assert(!test_types(func, for_each_type(2)));
    static_assert(!test_types(func, for_each_type(1)));
    static_assert(test_types(func, for_each_type(3)));
}

TEST_METHOD(greater_equal) {
    static_assert(nd::greater_equal(2.5)(3.5));
    static_assert(nd::greater_equal(2.5)(2.5));
    constexpr auto func = nd::greater_equal(2);
    static_assert(test_types(func, for_each_type(2)));
    static_assert(!test_types(func, for_each_type(1)));
    static_assert(test_types(func, for_each_type(3)));
}

TEST_METHOD(less) {
    static_assert(nd::less(3.5)(2.5));
    static_assert(!nd::less(2.5)(2.5));
    constexpr auto func = nd::less(2);
    static_assert(!test_types(func, for_each_type(2)));
    static_assert(test_types(func, for_each_type(1)));
    static_assert(!test_types(func, for_each_type(3)));
}

TEST_METHOD(less_equal) {
    static_assert(nd::less_equal(3.5)(2.5));
    static_assert(nd::less_equal(2.5)(2.5));
    constexpr auto func = nd::less_equal(2);
    static_assert(test_types(func, for_each_type(2)));
    static_assert(test_types(func, for_each_type(1)));
    static_assert(!test_types(func, for_each_type(3)));
}

TEST_METHOD(plus) {
    static_assert(nd::plus(3)(2) == 5);
    constexpr auto func = nd::plus(2);
    static_assert(func(1.0) == 3);
}

TEST_METHOD(minus) {
    static_assert(nd::minus(2)(3) == 1);
    constexpr auto func = nd::minus(2);
    static_assert(func(2) == 0);
}

TEST_METHOD(multiplies) {
    static_assert(nd::multiplies(2)(3) == 6);
    constexpr auto func = nd::multiplies(2.2);
    static_assert(func(4) == 8.8);
}

TEST_METHOD(divides) {
    static_assert(nd::divides(3)(6) == 2);
    static_assert(nd::divides(2.0)(3) == 1.5);
    static_assert(nd::divides(2)(3) != 1.5);
}

using namespace nd::operators;

TEST_METHOD(operator_equal_to) {
    constexpr auto ones = make_ones();
    static_assert(ones == 1);
}

TEST_METHOD(operator_not_equal_to) {
    constexpr auto ones = make_ones();
    static_assert(ones != 0);
    constexpr auto zeros = make_zeros();
    static_assert(zeros == 0);
}

TEST_METHOD(operator_less) {
    constexpr auto ones = make_ones();
    static_assert(ones < 2);
    constexpr auto zeros = make_zeros();
    static_assert(zeros < 1);
}

TEST_METHOD(operator_less_equal) {
    constexpr auto ones = make_ones();
    static_assert(ones < 2);
    constexpr auto zeros = make_zeros();
    static_assert(zeros <= 0);
}

TEST_METHOD(operator_greater) {
    constexpr auto ones = make_ones();
    static_assert(ones > 0);
    constexpr auto zeros = make_zeros();
    static_assert(zeros > -1);
}

TEST_METHOD(operator_greater_equal) {
    constexpr auto ones = make_ones();
    static_assert(ones > 0);
    constexpr auto zeros = make_zeros();
    static_assert(zeros >= 0);
}

TEST_METHOD(operator_plus) {
    static_assert(nd::plus(3)(2) == 5);
    constexpr auto func = nd::plus(2);
    static_assert(func(1.0) == 3);
}

TEST_METHOD(operator_minus) {
    static_assert(nd::minus(2)(3) == 1);
    constexpr auto func = nd::minus(2);
    static_assert(func(2) == 0);
}

TEST_METHOD(operator_multiplies) {
    static_assert(nd::multiplies(2)(3) == 6);
    constexpr auto func = nd::multiplies(2.2);
    static_assert(func(4) == 8.8);
}

TEST_METHOD(operator_divides) {
    static_assert(nd::divides(3)(6) == 2);
    static_assert(nd::divides(2.0)(3) == 1.5);
    static_assert(nd::divides(2)(3) != 1.5);
}