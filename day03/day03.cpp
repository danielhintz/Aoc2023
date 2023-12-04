#include <cmath>
#include <cstdint>
#include <iostream>
#include <utility>

constexpr bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}
constexpr bool isSymbol(char c)
{
    return !isDigit(c) && c != '.' && c != '\0' && c != '\n';
}

struct Gear
{
    int numbers = 0;
    uint64_t val = 1;
};

constexpr auto doIt()
{
    const char c[][141] =
#include "input.txt"
        ;

    Gear gears[std::size(c)][std::size(c[0])] = {};

    auto get_num = [](std::string_view str) {
        int arr[256] = {};
        int i = 0;
        int num = 0;
        for (i = 0; i < str.size() && isDigit(str[i]);)
            arr[i++] = str[i] - '0';

        for (int x = i; x >= 0; --x)
            num += arr[x] * std::pow(10, i - x - 1);

        return std::make_pair(num, i);
    };
    uint64_t sum = 0;
    for (int y = 0; y < std::size(c); y++)
    {
        for (int x = 0; x < std::size(c[0]); x++)
        {
            bool adjacent = false;
            auto [num, len] = get_num({c[y] + x, std::size(c[0]) - x});
            if (len == 0)
                continue;
            for (int y0 = y - 1; y0 <= y + 1; y0++)
            {
                for (int x0 = x - 1; x0 <= x + len; x0++)
                {
                    if (y0 < 0 || y0 >= std::size(c) || x0 < 0 || x0 >= std::size(c[0]))
                        continue;
                    if (c[y0][x0] == '*')
                    {
                        gears[y0][x0].val *= num;
                        ++gears[y0][x0].numbers;
                    }
                    if (isSymbol(c[y0][x0]))
                        adjacent = true;
                }
            }
            if (adjacent)
                sum += num;

            x += (len - 1);
        }
    }

    uint64_t gear_ratios = 0;

    for (int y = 0; y < std::size(c); ++y)
        for (int x = 0; x < std::size(c[0]); ++x)
            if (gears[y][x].numbers == 2)
                gear_ratios += gears[y][x].val;


    return std::make_pair(sum, gear_ratios);
}

int main()
{
    auto [p1, p2] = doIt();
    std::cout << "Part1: " << p1 << "\nPart2: " << p2 << std::endl;
}
