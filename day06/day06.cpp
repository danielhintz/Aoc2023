#include <omp.h>

#include <cstdint>
#include <iostream>
#include <utility>

#include "absl/numeric/int128.h"

auto doIt()
{
    uint64_t times[] = {54, 94, 65, 92};
    uint64_t distances[] = {302, 1476, 1029, 1404};

    uint64_t p1 = 1;
    for (int i = 0; i < std::size(times); i++)
    {
        uint64_t wins = 0;
        for (int x = 1; x < times[i]; x++)
            if (x * (times[i] - x) > distances[i])
                wins++;
        p1 *= wins;
    }

    absl::uint128 time = 54946592;
    absl::uint128 distance = 302147610291404;

    uint64_t p2 = 0;
    for (absl::uint128 x = 1; x <= time; x++)
        if (x * (time - x) > distance)
            p2++;


    return std::make_pair(p1, p2);
}

int main()
{
    auto pair = doIt();
    std::cout << "Part1: " << pair.first << "\nPart2: " << pair.second << std::endl;
}
