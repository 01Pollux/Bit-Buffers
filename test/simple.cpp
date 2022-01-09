#include <iostream>
#include <px/bitbuf.hpp>
#include <px/bitbuf/iostream.hpp>

/*
10
11
12
Hello
World!
1
2
3
4
1


Bits:

0       1       0       1       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       1       1       0       0       1       0       0
0       0       0       0       0       0       1       0
0       0       1       1       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       1       0       0       1       0
1       0       1       0       0       1       1       0
0       0       1       1       0       1       1       0
0       0       1       1       0       1       1       0
1       1       1       1       0       1       1       0
0       0       0       0       0       1       0       0
0       0       0       0       0       0       0       0
1       1       1       0       1       0       1       0
0       0       0       0       0       0       0       0
1       1       1       1       0       1       1       0
0       0       0       0       0       0       0       0
0       1       0       0       1       1       1       0
0       0       0       0       0       0       0       0
0       0       1       1       0       1       1       0
0       0       0       0       0       0       0       0
0       0       1       0       0       1       1       0
0       0       0       0       0       0       0       0
1       0       0       0       0       1       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       1       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
1       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       1       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
1       1       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       1       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
0       0       0       0       0       0       0       0
1
*/
int simple_main()
{
    using px::bitbuf;

    bitbuf buf;
    buf << 10;
    buf << static_cast<double>(11);
    buf << 12ull;
    buf << "Hello ";
    buf << std::wstring(L"World!");

    // size of array
    // optional
    buf.write<size_t>(4);
    buf << std::array{ 1, 2, 3, 4 };

    buf << px::bit_type::one;

    std::cout << buf.read<int>() << '\n';
    std::cout << buf.read<double>() << '\n';
    std::cout << buf.read<unsigned long long>() << '\n';
    std::cout << buf.read<std::string>() << '\n';
    std::wcout<< buf.read<std::wstring>() << '\n';

    {
        for (
            const auto vec = buf.read<std::vector<int>>(buf.read<size_t>());
            const auto v : vec
        )
        {
            std::cout << v << '\n';
        }
    }

    px::bit_type bit;
    buf >> bit;
    std::cout << bit << '\n';

    std::cout << "\n\nBits:\n\n";

    {
        size_t new_line = 0;
        // print out bits [0, last_write( 
        for (const auto bit : buf.read_iterator(0, buf.write_get()))
        {
            if (new_line >= 8)
            {
                std::cout << '\n';
                new_line = 0;
            }
            std::cout << bit << "  ";
            ++new_line;
        }
    }
    return 0;
}
