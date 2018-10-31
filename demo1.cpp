// Demo 1 - Intro iteration
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
#define NOMINMAX

#include "picobench/picobench.hpp"

#include <vector>
#include <list>
#include <cstddef>
#include <algorithm>

struct vec
{
    double x, y;
    double manhattan_length() const {
        return x + y;
    }
};

double drand() { return rand(); }

void vector(picobench::state& s)
{
    std::vector<vec> v;
    srand(s.iterations());
    v.reserve(s.iterations());

    for (int i=0; i<s.iterations(); ++i) {
        v.push_back({drand(), drand()});
    }

    double sum = 0;

    {
        picobench::scope scope(s);
        for(const auto& elem : v) {
            sum += elem.manhattan_length();
        }
    }

    s.set_result(*reinterpret_cast<picobench::result_t*>(&sum));
}

void list(picobench::state& s)
{
    std::list<vec> l;
    srand(s.iterations());

    for (int i=0; i<s.iterations(); ++i) {
        l.push_back({drand(), drand()});
    }

    double sum = 0;

    {
        picobench::scope scope(s);
        for(const auto& elem : l) {
            sum += elem.manhattan_length();
        }
    }

    s.set_result(*reinterpret_cast<picobench::result_t*>(&sum));
}

PICOBENCH(vector);
PICOBENCH(list);

//////////////////////////////////////////////////////////////
#include "pool_alloc.inl"

void list_alloc(picobench::state& s)
{
    pool_aloc_scope _scope;

    std::list<vec, pool_alloc<vec>> l;
    srand(s.iterations());

    for (int i = 0; i<s.iterations(); ++i) {
        l.push_back({ drand(), drand() });
    }

    double sum = 0;

    {
        picobench::scope scope(s);
        for (const auto& elem : l) {
            sum += elem.manhattan_length();
        }
    }

    s.set_result(*reinterpret_cast<picobench::result_t*>(&sum));
}

// PICOBENCH(list_alloc);
