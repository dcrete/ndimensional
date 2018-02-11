#include "tests/common.hpp"

using namespace nd::tests;
using namespace nd::operators;

TEST_METHOD(operator_plus) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}

TEST_METHOD(operator_minus) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}

TEST_METHOD(operator_multiplies) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}

TEST_METHOD(operator_divides) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}

TEST_METHOD(operator_equal_to) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}

TEST_METHOD(operator_less) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}

TEST_METHOD(operator_less_equal) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}

TEST_METHOD(operator_greater) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}

TEST_METHOD(operator_greater_equal) {
    constexpr auto threes = make_ones() + 2;
    static_assert(nd::all_of(threes, nd::equal_to(3)));
    static_assert(nd::none_of(threes, nd::less(3)));
    static_assert(nd::none_of(threes, nd::greater(3)));
}