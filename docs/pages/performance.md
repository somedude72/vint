---
layout: default
title: Performance
nav_order: 3
permalink: /performance/
---
<a id="top"></a>

## Performance

Large numbers, due to their nature, requires more computational power to work
with. This page will attempt to detail some empirical performance comparisons
with this library. If you are interested in theoretical performance, see the
[api reference](/api_reference/) page for details. 

## Addition Performance

In the following performance test, we are repeatedly adding a variable to itself
n times, effectively achieving exponential growth ($ 2^n $). We will compare the
performance of addition between this library and Python using the code snippets below:

```cpp
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main() {
    int N = 1000;
    vint::Int a = 1;

    auto add_beg = steady_clock::now();
    for (int i = 0; i < N; i++) { a += a; }
    auto add_end = steady_clock::now();

    cout << "Addition took "
         << duration_cast<milliseconds> (add_end - add_beg).count() << " ms";
}
```

```py
N = 1000
a = 1

add_beg = time.perf_counter_ns()
for i in range(N): a += a
add_end = time.perf_counter_ns()

print(f"Addition took {(add_end - add_beg) / 1000:.0f} ms")
```

The following chart shows the performance difference between the vint library and Python's int object when N grows. The right most column showcases the performance difference between vint library and Python in percentage (e.g. `+55%` means that the vint library is 55% faster than Python, and `-6.4x` means that vint is 6400% slower than Python). Note the time shown is a winsorized average of 5 test runs.

| N         |    Vint addition |    Python addition |   Difference |
|:----------|-----------------:|-------------------:|-------------:|
| 1,000     |            131μs |               82μs |         -59% |
| 10,000    |          3,264µs |            2,517µs |         -29% |
| 100,000   |            158ms |              177ms |         +11% |
| 1,000,000 |         14,188ms |           17,474ms |         +23% |

[This section is under construction]