# Sorting

## Overview

The **Sorting** repository provides an implementation for sorting records from a CSV file based on various fields and sorting algorithms. It includes functionality for processing input/output files, profiling sorting performance, and running unit tests. The repository is built in C and designed for flexibility and high performance.

### Features
- **Sorting algorithms**: Merge Sort, Quick Sort, Binary Insertion Sort and Merge Binary Insertion Sort.
- **Field types**: String, Integer, and Float.
- **Profiling support**: Measure and analyze sorting performance.
- **Unit tests**: Comprehensive tests implemented using Unity.

## Requirements

### Build Tools
- CMake (3.20 or later)
- C99-compatible C compiler (tested with GCC and MSVC)

### Dependencies
- [Unity](https://github.com/ThrowTheSwitch/Unity) (for unit testing, included as a git submodule)

## Building the Project

### Steps to Build
1. Clone the repository and initialize submodules:
   ```sh
   git clone https://github.com/marco-orru/sorting.git
   cd sorting
   git submodule update --init --recursive
   ```

2. Create a build directory and configure the project:
    ```sh
    mkdir build
    cd build
    cmake ..
    ```

3. Build the executables:
    ```sh
    cmake --build .
    ```

### Output

+ `sorting`: CLI tool for sorting records in a file.
+ `sorting_profiler`: CLI tool for profiling sorting algorithms on a specified records file.
+ `sorting_tests`: Unit tests executable.

### Records

A record must have the following format:
```csv
id,int_field,string_field,float_field
```
An example of a CSV file content:

```csv
1,42,example,3.14
2,10,test,1.23
```

**The CSV file must not have an header row.**

## Usage

### Sorting Tool
Sort records in a CSV file by a specified field and algorithm:

```sh
./sorting <input_file> <output_file> <field_id> <algorithm_id> <threshold?>
```

+ `field_id`:
    + `1` or `STRING` or `FIELD_STRING`
    + `2` or `INTEGER` or `FIELD_INTEGER`
    + `3` or `FLOAT` or `FIELD_FLOAT`

+ `algorithm_id`:
    + `1` or `MERGESORT` or `ALGORITHM_MERGESORT`
    + `2` or `QUICKSORT` or `ALGORITHM_QUICKSORT`
    + `3` or `BININSSORT` or `ALGORITHM_BININSSORT`
    + `4` or `MERGEBININSSORT` or `ALGORITHM_MERGEBININSSORT`

+ `threshold`: specifies the threshold of the merge binary insertion sort algorithm (in other algorithms, this parameter is optional).

### Profiling Tool
Measure the performance of sorting algorithms over a csv file:

```sh
./sorting_profiler <input_file> <thresholds...?>
```

Thresholds list is optional.

You can disable certain algorithms by recompiling the source defining:

+ `DISABLE_QUICKSORT`: disable quick sort profiling.
+ `DISABLE_MERGESORT`: disable merge sort profiling.
+ `DISABLE_BININSSORT`: disable binary insertion sort profiling.
+ `DISABLE_MERGEBININSSORT`: disable merge binary insertion sort profiling.

### Running Unit Tests
Execute the unit tests:

```sh
./sorting_tests
```

You can disable certain algorithms by recompiling the source defining:

+ `DISABLE_QUICKSORT`: disable quick sort unit testing.
+ `DISABLE_MERGESORT`: disable merge sort unit testing.
+ `DISABLE_BININSSORT`: disable binary insertion sort unit testing.
+ `DISABLE_MERGEBININSSORT`: disable merge binary insertion sort unit testing.

## Sorting Algorithms

Here’s the completion for the sorting algorithm descriptions:

## Sorting Algorithms

+ **`merge_sort` (O(N log N))**: Stable and efficient for large datasets. It divides the array into two halves, recursively sorts them, and merges the sorted halves. It is particularly useful when stability is required (i.e., equal elements retain their relative order).

+ **`quick_sort` (O(N log N))**: Fast with small overhead, but unstable. It uses a divide-and-conquer approach by selecting a "pivot" element and partitioning the array into two sub-arrays: one with elements smaller than the pivot and one with elements greater than the pivot. It then recursively sorts the sub-arrays. It’s often faster than merge sort for practical input sizes but can perform poorly on certain datasets (e.g., already sorted or reversed).

+ **`binary_insertion_sort` (O(N^2))**: An optimized version of the insertion sort algorithm. It uses binary search to find the correct position of each element in the sorted portion of the array, reducing the number of comparisons needed. However, the time complexity remains O(N^2) due to the shifting of elements. It’s efficient for nearly sorted or small datasets.

+ **`merge_binary_insertion_sort` (O(N^2) worst-case)**: Combines the merge sort algorithm with binary insertion sort. It first applies binary insertion sort to smaller segments of the array (often used as a threshold for merge sort), and then uses merge sort to combine those segments. This hybrid approach can reduce overhead for certain types of data but still has the worst-case complexity of O(N^2).