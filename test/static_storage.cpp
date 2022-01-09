#include <iostream>
#include <px/bitbuf.hpp>
#include <px/bitbuf/iostream.hpp>


int static_buffer_main()
{
    using px::static_bitbuf;
    using namespace px::literals;

    // reserving storage for (int + char[250] + bit)
    constexpr size_t storage_size = sizeof(int) + sizeof(char) * 250 + 1;
    static_bitbuf<storage_size> buf;
    static_assert(buf.size() == storage_size);

    buf << 10;
    buf << "Hello World";
    buf << "1"_bit;

    std::cout << buf.read<int>() << '\n';
    char str[250]{ };
    buf >> str;
    std::cout << str << '\n';
    std::cout << buf.read<px::bit_type>();

    return 0;
}
