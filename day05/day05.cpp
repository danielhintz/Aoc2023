#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "absl/strings/numbers.h"
#include "absl/strings/str_split.h"

struct range
{
    uint64_t dst, src, n;
};
auto doIt()
{
    std::ifstream file{"input.txt"};
    std::vector<range> seeds;
    std::vector<range> seed_to_soil;
    std::vector<range> soil_to_fertilizer;
    std::vector<range> fertilizer_to_water;
    std::vector<range> water_to_light;
    std::vector<range> light_to_temperature;
    std::vector<range> temperature_to_humidity;
    std::vector<range> humidity_to_location;

    std::string line;

    auto consume = [&](int n) {
        for (int i = 0; i < n; i++)
            std::getline(file, line);
    };
    consume(1);

    std::vector<std::string_view> split = absl::StrSplit(line, ' ');
    for (int i = 1; i < split.size(); i += 2)
    {
        range r;
        if (!absl::SimpleAtoi(split[i], &r.src))
            throw;
        if (!absl::SimpleAtoi(split[i + 1], &r.n))
            throw;
        seeds.push_back(r);
    }
    consume(3);

    auto consume_block = [&](auto& arr) {
        int x = 0;
        do
        {
            range r;
            std::vector<std::string_view> split = absl::StrSplit(line, ' ');
            if (!(absl::SimpleAtoi(split[0], &r.dst) & absl::SimpleAtoi(split[1], &r.src) &
                  absl::SimpleAtoi(split[2], &r.n)))
                throw;
            arr.push_back(r);
            consume(1);
        } while (line.size());
    };
    consume_block(seed_to_soil);
    consume(2);
    consume_block(soil_to_fertilizer);
    consume(2);
    consume_block(fertilizer_to_water);
    consume(2);
    consume_block(water_to_light);
    consume(2);
    consume_block(light_to_temperature);
    consume(2);
    consume_block(temperature_to_humidity);
    consume(2);
    consume_block(humidity_to_location);


    auto traverse = [](auto& arr, auto seed, bool reverse) {
        for (int i = 0; i < arr.size(); ++i)
            if (!reverse)
            {
                if (seed >= arr[i].src && seed < arr[i].src + arr[i].n)
                {
                    seed = arr[i].dst + (seed - arr[i].src);
                    break;
                }
            }
            else
            {
                if (seed >= arr[i].dst && seed < arr[i].dst + arr[i].n)
                {
                    seed = arr[i].src + (seed - arr[i].dst);
                    break;
                }
            }
        return seed;
    };

    uint64_t lowest_p1 = std::numeric_limits<uint64_t>::max();
    uint64_t lowest_p2 = std::numeric_limits<uint64_t>::max();
    for (int i = 0; i < seeds.size(); i++)
    {
        uint64_t seed = seeds[i].src;
        seed = traverse(seed_to_soil, seed, false);
        seed = traverse(soil_to_fertilizer, seed, false);
        seed = traverse(fertilizer_to_water, seed, false);
        seed = traverse(water_to_light, seed, false);
        seed = traverse(light_to_temperature, seed, false);
        seed = traverse(temperature_to_humidity, seed, false);
        seed = traverse(humidity_to_location, seed, false);
        lowest_p1 = std::min(lowest_p1, seed);

        seed = seeds[i].n;
        seed = traverse(seed_to_soil, seed, false);
        seed = traverse(soil_to_fertilizer, seed, false);
        seed = traverse(fertilizer_to_water, seed, false);
        seed = traverse(water_to_light, seed, false);
        seed = traverse(light_to_temperature, seed, false);
        seed = traverse(temperature_to_humidity, seed, false);
        seed = traverse(humidity_to_location, seed, false);
        lowest_p1 = std::min(lowest_p1, seed);
    }
    bool stop = false;
    for (uint64_t i = 0; !stop && i < 6000000000ull; ++i)
    {
        uint64_t seed = i;
        seed = traverse(humidity_to_location, seed, true);
        seed = traverse(temperature_to_humidity, seed, true);
        seed = traverse(light_to_temperature, seed, true);
        seed = traverse(water_to_light, seed, true);
        seed = traverse(fertilizer_to_water, seed, true);
        seed = traverse(soil_to_fertilizer, seed, true);
        seed = traverse(seed_to_soil, seed, true);
        for (const auto& seed_range : seeds)
        {
            if (seed > seed_range.src && seed < seed_range.src + seed_range.n)
            {
                lowest_p2 = i;
                stop = true;
                break;
            }
        }
    }
    return std::make_pair(lowest_p1, lowest_p2);
}

int main()
{
    auto pair = doIt();
    std::cout << "Part1: " << pair.first << "\nPart2: " << pair.second << std::endl;
}
