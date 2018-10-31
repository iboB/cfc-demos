// Demo 3 - Cache Misses
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
#include <map>
#include "chobo/flat_map.hpp"

static const int TESTS = 100;

int find_func(int iters)
{
    //return (iters - 1 - (rand() % (iters/2))) * 2;
    return (rand() % iters) * 2;
}

void vector(picobench::state& s)
{
    srand(s.iterations());
    std::vector<std::vector<int>> vecs(TESTS);
    std::vector<int> finds(TESTS);
    for (int t = 0; t < TESTS; ++t)
    {
        vecs.reserve(s.iterations());
        finds[t] = find_func(s.iterations());
    }

    for (int i = 0; i < s.iterations(); ++i)
    {
        for (int t = 0; t < TESTS; ++t)
        {
            vecs[t].push_back(i * 2);
        }
    }


    int sum = 0;
    {
        picobench::scope scope(s);
        for (int t = 0; t < TESTS; ++t)
        {
            auto& vec = vecs[t];
            auto to_find = finds[t];
            int i = 0;
            for (auto elem : vec)
            {
                if (elem == to_find)
                {
                    sum += i;
                    break;
                }

                ++i;
            }
        }
    }

    s.set_result(sum);
}

void map(picobench::state& s)
{
    srand(s.iterations());
    std::vector<std::map<int, int>> maps(TESTS);
    std::vector<int> finds(TESTS);
    for (int t = 0; t < TESTS; ++t)
    {
        finds[t] = find_func(s.iterations());
    }

    for (int i = 0; i < s.iterations(); ++i)
    {
        for (int t = 0; t < TESTS; ++t)
        {
            maps[t][i * 2] = i;
        }
    }

    int sum = 0;
    {
        picobench::scope scope(s);
        for (int t = 0; t < TESTS; ++t)
        {
            auto to_find = finds[t];
            auto& m = maps[t];
            auto found = m.find(to_find);
            sum += found->second;
        }
    }

    s.set_result(sum);
}


void flat_map(picobench::state& s)
{
    srand(s.iterations());
    std::vector<chobo::flat_map<int, int>> maps(TESTS);
    std::vector<int> finds(TESTS);
    for (int t = 0; t < TESTS; ++t)
    {
        finds[t] = find_func(s.iterations());
    }

    for (int i = 0; i < s.iterations(); ++i)
    {
        for (int t = 0; t < TESTS; ++t)
        {
            maps[t][i * 2] = i;
        }
    }

    int sum = 0;
    {
        picobench::scope scope(s);
        for (int t = 0; t < TESTS; ++t)
        {
            auto to_find = finds[t];
            auto& m = maps[t];
            auto found = m.find(to_find);
            sum += found->second;
        }
    }

    s.set_result(sum);
}

PICOBENCH(vector);
PICOBENCH(map);
//PICOBENCH(flat_map);
