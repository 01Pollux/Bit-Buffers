#include <iostream>
#include <px/bitbuf.hpp>


int inout_buffer_main()
{
    using px::bitbuf;
    using px::obitbuf;
    using px::ibitbuf;

    obitbuf obuf;
    obuf << 10;
    obuf << static_cast<double>(11);
    obuf << 12ull;
    obuf << "Hello ";
    obuf << std::wstring(L"World!");

    // size of array
    // optional
    obuf.write<size_t>(4);
    obuf << std::array{ 1, 2, 3, 4 };

    obuf << px::bit_type::one;

    // COPY of obuf's storage!
    //ibitbuf ibuf = obuf;

    ibitbuf ibuf(std::move(obuf));

    std::cout << ibuf.read<int>() << '\n';
    std::cout << ibuf.read<double>() << '\n';
    std::cout << ibuf.read<unsigned long long>() << '\n';
    std::cout << ibuf.read<std::string>() << '\n';
    std::wcout << ibuf.read<std::wstring>() << '\n';

    {
        for (
            const auto vec = ibuf.read<std::vector<int>>(ibuf.read<size_t>());
            const auto v : vec
            )
        {
            std::cout << v << '\n';
        }
    }
    return 0;
}
