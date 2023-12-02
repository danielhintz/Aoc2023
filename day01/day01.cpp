#include <cstdint>
#include <iostream>
#include <optional>

constexpr bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}
constexpr std::string_view nums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

constexpr uint64_t doIt()
{
    char* c =
#include "input.txt"
        ;
    std::optional<uint8_t> first{};
    uint8_t last = 0;
    uint64_t sum = 0;
    while (*c)
    {
        if (*c == '\n')
        {
            sum += (*first * 10 + last);
            first.reset();
        }
        {
            if (isDigit(*c))
            {
                if (!first)
                    first = *c - '0';
                last = *c - '0';
            }
            else
            {
                for (int i = 0; i < std::size(nums); ++i)
                {
                    const auto num = nums[i];
                    if (num == std::string_view{c, num.size()})
                    {
                        if (!first)
                            first = i + 1;
                        last = i + 1;
                    }
                }
            }
        }
        ++c;
    }
    return sum;
}

int main()
{
    std::cout << doIt();
}
