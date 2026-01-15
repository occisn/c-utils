# c-utils

Personal utilities for C.

This project is a kind of shelf providing many functions. With a few clearly indicated exceptions, these functions are self-supporting. They do not require any dependency, or to be built/integrated in any specific way. Because "the truly reusable code is the one that you can simply copy-paste".

A test suite is proposed.

When relevant, functions are illustrated with associated `SHOW_xxx` functions.

File **durations.c**  
   - function `SHOW_measure_duration`  
   - functions `SHOW_benchmark_5_times_A` and `SHOW_benchmark_5_times_B`
 
File **files.c**  
   - function `ensure_directory_exists`

File **images.c**  
   - function `save_bmp`  
   - function `save_png`  
   - function `stb_save_image` using [STB library](https://github.com/nothings/stb)  
   - function `draw_heatmap_from_values` using [STB library](https://github.com/nothings/stb)
   
File **integers.c**  
   - functions `lcm_int` and `gcd_int`

File **integers_digits.c**  
   - function `reverse_number_int`

File **integer_primes.c**  
   - function `largest_prime_factor_uint64`  
   - function `factorize_uint64`   
   - function `is_prime_uint64`  
   - functions `sieve_eratosthenes_simple_uint64` and `sieve_eratosthenes_odd_bit_uint64`  
   - function `list_of_primes_below_uint64`   
   - function `nth_prime_uint64`

File **parallelism_with_openmp.c**  
   - function `SHOW_parallelism_with_openmp_1` (with reduction)  
   - function `SHOW_parallelism_with_openmp_2` (without reduction)  
   - function `SHOW_parallelism_with_openmp_3` (task)
   
File **parallelism_with_threads.c**  
   - function `SHOW_parallelism_with_threads`

File **progress.c**  
   - function `progress_number`  
   - function `progress_bar`
  
Any comment? Open an [issue](https://github.com/occisn/c-utils/issues), or start a discussion [here](https://github.com/occisn/c-utils/discussions) or [at profile level](https://github.com/occisn/occisn/discussions).

(end of README)
