#include <iostream>
#include <ranges>
#include <px/bitbuf.hpp>

consteval /*constexpr*/ size_t bit_index_of_first_bit(int64_t val)
{
    using px::bitbuf;
    bitbuf buf;
    buf << val;

    const auto iter = buf.read_iterator(0, buf.write_get());
    for (auto it = iter.begin(); it != iter.end(); it++)
    {
        if (*it == px::bit_type::one)
            return it.bit_index();
    }
    return -1;
}

consteval /*constexpr*/ size_t index_of_first_bit(int64_t val)
{
    using px::bitbuf;
    bitbuf buf;
    buf << val;

    const auto iter = buf.read_iterator(0, buf.write_get());
    for (auto it = iter.begin(); it != iter.end(); it++)
    {
        if (*it == px::bit_type::one)
            return it.index();
    }
    return -1;
}

consteval /*constexpr*/ size_t bits_left_of_first_bit(int64_t val)
{
    using px::bitbuf;
    bitbuf buf;
    buf << val;

    const auto iter = buf.read_iterator(0, buf.write_get());
    for (auto it = iter.begin(); it != iter.end(); it++)
    {
        if (*it == px::bit_type::one)
            return it.bit_left();
    }
    return -1;
}


template<size_t _Size>
consteval /*constexpr*/ int64_t bits_combine(
    /*const std::array<px::bit_type, _Size>&*/ 
    const std::array<int, _Size>
    bits
)
{
    using px::bitbuf;
    bitbuf buf(sizeof(int64_t));

    for (auto bit : bits | std::views::reverse)
        buf << (bit == 1 ? px::bit_type::one : px::bit_type::zero);

    return buf.read<int64_t>();
}



int constexpr_main()
{
    static_assert(bit_index_of_first_bit(0b01'000'000'000) == 9);
    static_assert(bit_index_of_first_bit(0b01'000'000'000) == 1 + (1 * px::bitbuf::bits_per_block));

    static_assert(bit_index_of_first_bit(0b01'000'000'001) == 0);
    static_assert(bit_index_of_first_bit(0b01'000'000'001) == 0 + (0 * px::bitbuf::bits_per_block));

    static_assert(bit_index_of_first_bit(0b00'000'000'010) == 1);
    static_assert(bit_index_of_first_bit(0b00'000'000'010) == 1 + (0 * px::bitbuf::bits_per_block));

    static_assert(bit_index_of_first_bit(0b00'000'000'000) == px::bitbuf::npos);


    static_assert(index_of_first_bit(0b01'000'000'000) == 1);
    static_assert(index_of_first_bit(0b01'000'000'000) == (9 / px::bitbuf::bits_per_block));

    static_assert(index_of_first_bit(0b01'000'000'001) == 0);
    static_assert(index_of_first_bit(0b01'000'000'001) == (0 / px::bitbuf::bits_per_block));

    static_assert(index_of_first_bit(0b00'000'000'010) == 0);
    static_assert(index_of_first_bit(0b00'000'000'010) == (1 / px::bitbuf::bits_per_block));

    static_assert(index_of_first_bit(0b00'000'000'000) == px::bitbuf::npos);


    static_assert(bits_left_of_first_bit(0b01'000'000'000) == 1);
    static_assert(bits_left_of_first_bit(0b01'000'000'000) == 9 - (1 * px::bitbuf::bits_per_block));

    static_assert(bits_left_of_first_bit(0b01'000'000'001) == 0);
    static_assert(bits_left_of_first_bit(0b01'000'000'001) == 0 - (0 * px::bitbuf::bits_per_block));

    static_assert(bits_left_of_first_bit(0b00'000'000'010) == 1);
    static_assert(bits_left_of_first_bit(0b00'000'000'010) == 1 - (0 % px::bitbuf::bits_per_block));

    static_assert(bits_left_of_first_bit(0b00'000'000'000) == px::bitbuf::npos);


    using namespace px::literals;
    {
        constexpr int64_t bits = bits_combine(std::array{ 0,1, 0,0,0, 0,0,0, 0,0,0 });
        static_assert(0b01'000'000'000 == bits);
    }
    {
        constexpr int64_t bits = bits_combine(std::array{ 0, 1, 0 });
        static_assert(0b00'000'000'010 == bits);
    }

    return 0;
}
