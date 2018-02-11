#include "tests/common.hpp"

using namespace nd::tests;

TEST_METHOD(range) {
    constexpr auto range = nd::range<1, 2>(make_zeros());
    using range_type = std::decay_t<decltype(range)>;
    static_assert(is_same_root_type<range_type>);
    static_assert(nd::dimension_v<range_type> == 3);
    static_assert(nd::size_v<range_type> == 2);
}

TEST_METHOD(set) {
    using index_pack = nd::dimension_pack<0, 0, 0>;
    constexpr auto values = nd::set(make_ones(), 2.0, index_pack{});
    static_assert(values[0][0][0] == 2);
    static_assert(values[0][0][1] != 2);
    static_assert(values[0][0][0] != 1);
}

TEST_METHOD(all_of) {
    using index_pack = nd::dimension_pack<0, 0, 0>;
    constexpr auto values = nd::set(make_ones(), 2.0, index_pack{});
    static_assert(nd::all_of(values, nd::greater(0)));
    static_assert(!nd::all_of(values, nd::greater(1)));
}

TEST_METHOD(none_of) {
    using index_pack = nd::dimension_pack<0, 0, 0>;
    constexpr auto values = nd::set(make_ones(), 2.0, index_pack{});
    static_assert(nd::none_of(values, nd::less(1)));
    static_assert(!nd::none_of(values, nd::greater(1)));
}

TEST_METHOD(any_of) {
    using index_pack = nd::dimension_pack<0, 0, 0>;
    constexpr auto values = nd::set(make_ones(), 2.0, index_pack{});
    static_assert(nd::any_of(values, nd::greater(1)));
    static_assert(!nd::any_of(values, nd::less(1)));
}

TEST_METHOD(assign) {
    constexpr auto ones = nd::assign(make_zeros(), 1.0);
    static_assert(nd::all_of(ones, nd::equal_to(1)));
}

TEST_METHOD(sum_accumulate) {
    constexpr auto ones = make_ones();
    constexpr auto summed = nd::sum(ones);
    constexpr auto sizes = ones.sizes();
    constexpr auto magnitude = nd::accumulate(sizes, 1);
    static_assert(summed == magnitude);
}

TEST_METHOD(transform) {
    constexpr auto twos = nd::transform(make_ones(), nd::multiplies(2.0));
    static_assert(nd::all_of(twos, nd::equal_to(2)));
    static_assert(nd::none_of(twos, nd::less(2)));
    static_assert(nd::none_of(twos, nd::greater(2)));
}