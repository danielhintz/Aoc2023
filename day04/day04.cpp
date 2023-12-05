#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

constexpr auto doIt()
{
    constexpr std::array<std::pair<std::array<int, 10>, std::array<int, 25>>, 214> input =
#include "input.txt" // Required formatting the input slightly
        ;
    uint8_t counts[0xffff] = {};
    uint64_t copies[std::size(input)] = {};
    std::fill(std::begin(copies), std::end(copies), 1);

    uint64_t sum = 0;
    for (unsigned i = 0; i < std::size(input); ++i)
    {
        const auto& card = input[i];
        for (const auto winner : card.first)
            counts[winner] = 1;
        for (const auto mine : card.second)
            counts[mine]++;
        uint64_t new_copies = 0;
        for (auto num : counts)
            if (num == 2)
                ++new_copies;
        if (new_copies)
            sum += std::pow(2, new_copies - 1);
        for (unsigned x = 0; x < new_copies; ++x)
            copies[x + i + 1] += copies[i];
        std::fill(std::begin(counts), std::end(counts), 0);
    }
    return std::make_pair(sum, std::accumulate(std::begin(copies), std::end(copies), 0ull));
}

int main()
{
    auto [p1, p2] = doIt();
    std::cout << "Part1: " << p1 << "\nPart2: " << p2 << std::endl;
}
