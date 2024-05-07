---
layout: default
title: Performance
nav_order: 3
permalink: /performance/
---
<a id="top"></a>

## Performance

Large numbers, due to their nature, requires more computational power to work with. However, because of my lack of algorithmic and programming knowledge and skill as well as the fact that this is the first library for C++ that I've written, I have thus far been unable to get very good results. This page will serve as a rough breakdown of the performance that you will get out of using various features in this library.

Additionally, although it may not be a fair comparison, the majority of this page will feature comparisons between the performance of this library and the performance of Python's implementation of [arbitrary precision integers](https://peps.python.org/pep-0237/), since this library is inspired by Python.

## Addition Performance

In the following performance test, we are repeatedly adding a variable to itself n times, effectively achieving exponential growth (2<sup>n</sup>). We can then test the performance of the addition operator using the code snippets below (demonstrated in both Python and C++):

```cpp
int main() {
    int N = 1000;

    vint::Int a = 1;
    std::chrono::steady_clock::time_point add_beg = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++) { a += a; }
    std::chrono::steady_clock::time_point add_end = std::chrono::steady_clock::now();

    std::cout << "Addition took " <<
        std::chrono::duration_cast<std::chrono::milliseconds> (add_end - add_beg).count() << "ms";
}
```

```py
N = 1000

a = 1
add_beg = time.perf_counter_ns()
for i in range(N): a += a
add_end = time.perf_counter_ns()
print(f"Addition took {(add_end - add_beg) / 1000:.0f}ms")
```

The following chart shows the performance difference between the vint library and Python's int object when N grows. To ensure that no performance has been lost from real time interpreting, the Python script has been saved on disk and therefore compiled into bytecode before it's run. The right most column showcases the performance difference between vint library and Python in percentage (e.g. `+55%` means that the vint library is 55% faster than Python, and `-6.4x` means that vint is 6400% slower than Python). Note the time shown is a winsorized average of 5 test runs.

| N         |    Vint addition |    Python addition |   Difference |
|:----------|-----------------:|-------------------:|-------------:|
| 1,000     |            131μs |               82μs |         -59% |
| 10,000    |          3,264µs |            2,517µs |         -29% |
| 100,000   |            158ms |              177ms |         +11% |
| 1,000,000 |         14,188ms |           17,474ms |         +23% |

Of course, smaller values of N (and time) should always be taken with a grain of salt, since the overhead from the various operating system processes as well as the timer itself would cause the end result to be unreliable. 

## Conversion Performance

Because conversion to string is the only way to print without integer overflow in c++, the conversion performance will be focused on only integer to string conversion. We can use the `to_string()` methods for vint or the `str()` function for Python. The following chart shows the performance differences between vint and Python in conversion from integer to string type. The leftmost column depicts the numbers of digits in base-10 that the number has:

| Digits    |    Vint addition |    Python addition |   Difference |
|:----------|-----------------:|-------------------:|-------------:|
| 300       |             54μs |                2μs |      -27.00x |
| 3,000     |          3,314μs |              123μs |      -26.94x |
| 30,000    |            309ms |                8ms |      -38.62x |
| 300,000   |         34,641ms |               29ms |    -1194.52x |

As one can tell, vint's integer to string conversion function is exponentially slower than Python's implementation. This is one area (who knew) that vint could improve.
