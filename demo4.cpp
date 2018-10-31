// Demo 4 - Branch Prediction
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

#include <vector>
#include <list>
#include <algorithm>

void unsorted(picobench::state& s)
{
    std::vector<double> v;
    srand(s.iterations());
    v.reserve(s.iterations());

    for (int i = 0; i<s.iterations(); ++i) {
        v.push_back(double(rand()) / RAND_MAX);
    }

    double prod = 1;

    {
        picobench::scope scope(s);
        for (auto elem : v) {
            if (elem < 0.5) prod *= elem;
        }
    }

    s.set_result(*reinterpret_cast<picobench::result_t*>(&prod));
}

void sorted(picobench::state& s)
{
    std::vector<double> v;
    srand(s.iterations());
    v.reserve(s.iterations());

    for (int i = 0; i<s.iterations(); ++i) {
        v.push_back(double(rand()) / RAND_MAX);
    }

    std::sort(v.begin(), v.end());

    double prod = 1;

    {
        picobench::scope scope(s);
        for (auto elem : v) {
            if (elem < 0.5) prod *= elem;
        }
    }

    s.set_result(*reinterpret_cast<picobench::result_t*>(&prod));
}

#define ITERATIONS .iterations({ 100000, 200000 })

PICOBENCH(unsorted) ITERATIONS;
PICOBENCH(sorted) ITERATIONS;
