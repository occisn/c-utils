# c-utils

Personal utilities for C.

This project is a kind of shelf providing many functions. With a few clearly indicated exceptions, these functions are self-supporting. They do not require any dependency, or to be built/integrated in any specific way. Because "the truly reusable code is the one that you can simply copy-paste".

A test suite is proposed.

When relevant, functions are illustrated with associated `SHOW_xxx` functions.

File **durations.c**  
   - function `SHOW__measure_duration`  
   - functions `SHOW__benchmark_5_times_A` and `SHOW__benchmark_5_times_B`
   
File **integers.c**  
   - functions `lcm__int` and `gcd__int`

File **integers_digits.c**  
   - function `reverse_number`

File **integer_primes.c**  
   - function `largest_prime_factor__uint64`  
   - function `factorize__uint64`   
   - function `is_prime__uint64`  
   - functions `sieve_eratosthenes__simple__uint64` and `sieve_eratosthenes__odd_bit__uint64`  
   - function `list_of_primes_below__uint64`   
   - function `nth_prime__uint64`

File **parallelism.c**  
   - function `SHOW_parallelism_with_openmp`

Any comment? Open an [issue](https://github.com/occisn/c-utils/issues), or start a discussion [here](https://github.com/occisn/c-utils/discussions) or [at profile level](https://github.com/occisn/occisn/discussions).

(end of README)
