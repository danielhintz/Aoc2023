#include <cmath>
#include <cstdint>
#include <iostream>


constexpr uint64_t doit()
{
    char* input =
#include "input.txt"
        ;
    const int R = 12;
    const int G = 13;
    const int B = 14;
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
        bool possible = true;
        while (*input != '\n')
        {
            if (!possible)
            {
                input++;
                continue;
            }
            auto num = consume_number();
            input++;
            if (*input == 'r')
                r = num;
            if (*input == 'g')
                g = num;
            if (*input == 'b')
                b = num;

            while (*input != ',' && *input != ';' && *input != '\n')
                input++;
            if (*input == ';')
            {
                if (r > R || g > G || b > B)
                    possible = false;
                r = g = b = 0;
                input += 2;
            }
            if (*input == ',')
                input += 2;
            if (*input == '\n')
            {
                if (r > R || g > G || b > B)
                    possible = false;
            }
        }
        if (possible)
            sum += game + 1;
    }

    return sum;
}


int main()
{
    std::cout << doit();
}
