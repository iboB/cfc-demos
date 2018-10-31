// Demo 6 - Intrinsics
//
// MIT License
//
// Copyright(c) 2018 Borislav Stanimirov
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "picobench/picobench.hpp"
#include <cstdlib>
#include <vector>

#ifdef _MSC_VER

#include <intrin.h>

#pragma intrinsic(_BitScanForward)

inline uint32_t count_bits(uint32_t a) {
    unsigned long bit = 0;
    _BitScanReverse(&bit, a);
    return uint32_t(bit + 1);
}

#else

inline uint32_t count_bits(uint32_t a) {
    return 32 - uint32_t(__builtin_clz(a));
}

#endif

inline uint32_t lame_count_bits(uint32_t a) {
    int bits = 0;
    while (a)
    {
        ++bits;
        a >>= 1;
    }
    return bits;
}

void no_intrin(picobench::state& s)
{
    std::vector<uint32_t> v;
    srand(s.iterations());
    v.reserve(s.iterations());

    for (int i = 0; i<s.iterations(); ++i) {
        int n = rand() + 1;
        v.push_back(n);
    }

    int sum = 0;

    {
        picobench::scope scope(s);
        for (const auto& elem : v) {
            sum += lame_count_bits(elem);
        }
    }

    s.set_result(sum);
}

void intrin(picobench::state& s)
{
    std::vector<uint32_t> v;
    srand(s.iterations());
    v.reserve(s.iterations());

    for (int i = 0; i<s.iterations(); ++i) {
        v.push_back(rand() + 1);
    }

    int sum = 0;

    {
        picobench::scope scope(s);
        for (const auto& elem : v) {
            sum += count_bits(elem);
        }
    }

    s.set_result(sum);
}

#define ITERATIONS .iterations({ 50000, 100000 })

PICOBENCH(no_intrin) ITERATIONS;
PICOBENCH(intrin) ITERATIONS;
