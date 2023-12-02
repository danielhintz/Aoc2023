#include <cmath>
#include <cstdint>
#include <iostream>


constexpr uint64_t doit()
{
    char* input =
#include "input.txt"
        ;
    uint64_t sum = 0;
    auto consume_number = [&input]() {
        int arr[10] = {};
        int i = 0;
        while (*input != ' ')
        {
            arr[i++] = *input - '0';
            input++;
        }
        i--;

        int num = 0;
        for (int x = i; x >= 0; x--)
            num += arr[x] * std::pow(10, i - x);
        return num;
    };
    for (unsigned game = 0; game < 100; game++)
    {
        while (*input != ':')
            ++input;
        input += 2;
        int r = 0;
        int g = 0;
        int b = 0;
        while (*input != '\n')
        {
            auto num = consume_number();
            input++;
            if (*input == 'r')
                r = std::max(r, num);
            if (*input == 'g')
                g = std::max(g, num);
            if (*input == 'b')
                b = std::max(b, num);

            while (*input != ',' && *input != ';' && *input != '\n')
                input++;
            if (*input == ';' || *input == ',')
                input += 2;
        }
        sum += r * g * b;
    }

    return sum;
}


int main()
{
    std::cout << doit();
}
