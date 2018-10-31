#define PICOBENCH_IMPLEMENT
#include "picobench.hpp"
#include <iostream>

using namespace picobench;

int main()
{
    runner run;

#if defined(NDEBUG)
    run.set_default_state_iterations({ 20, 50, 100, 1000, 10000 });
    run.set_default_samples(10);
#else
    run.set_default_state_iterations({ 100, 1000 });
    run.set_default_samples(3);
#endif

    run.set_compare_results_across_benchmarks(true);
    run.set_compare_results_across_samples(true);

    run.run_benchmarks(123);
    
    auto rep = run.generate_report();

    rep.to_text(std::cout);

    return run.error();
}
