// Demo 2 - Intro push_back
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

template <typename C>
void push_back(C& c, int i)
{
    c.push_back(i);
}

template <typename C>
void push_front(C& c, int i)
{
    c.insert(c.begin(), i);
}

#define add_elem push_back

void vector(picobench::state& s)
{
    std::vector<int> v;
    srand(s.iterations());

    for(auto _ : s) {
        add_elem(v, rand());
    }

    int sum = 0;
    for (auto elem : v) sum += elem;
    s.set_result(sum);
}

void list(picobench::state& s)
{
    std::list<int> l;
    srand(s.iterations());

    for (auto _ : s) {
        add_elem(l, rand());
    }

    int sum = 0;
    for (auto elem : l) sum += elem;
    s.set_result(sum);
}

PICOBENCH(vector);
PICOBENCH(list);
