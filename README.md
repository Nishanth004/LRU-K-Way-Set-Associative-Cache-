# K-Way Set Associative Cache Mapping

In a k-way set associative cache, main memory block mapping range:

Number of sets in cache = v. So, main memory block j will be mapped to set (j mod v), which will be any one of the cache lines from (j mod v) * k to (j mod v) * k + (k-1). (Associativity plays no role in mapping- k-way associativity means there are k spaces for a block and hence reduces the chances of replacement.)

This is a simple concept of k-way set associate mapping.

To understand it better, let's take an example:

## Example:

- 2-way set associative
- 4 blocks
- Lines of a set are placed in sequence one after another (as in the question)
- The main memory blocks are numbered 0 onwards (as in the question)

### Empty 2-way set associative Cache Memory:

| | |Cache |
|---|:---:|:---:|
| | Set 1 | Set 2 |
| 0 | - | - |
| 1 | - | - |
| 2 | - | - |
| 3 | - | - |

Memory reference (data asked for processing) in the order:

4, 5, 9, 7

### Reference 4:

4 % 4 = 0 (goes to Block 0 Set 1) Cache miss as it doesn't already present in the cache

As it had 4 blocks, we mod it the reference address to know which location of cache should I put it.

| | |Cache |
|---|:---:|:---:|
| | Set 1 | Set 2 |
| 0 | 4 | - |
| 1 | - | - |
| 2 | - | - |
| 3 | - | - |

### Reference 5:

4 % 5 = 1 (goes to Block 1 Set 1) Cache miss

| || Cache |
|---|:---:|:---:|
| | Set 1 | Set 2 |
| 0 | 4 | - |
| 1 | 5 | - |
| 2 | - | - |
| 3 | - | - |

### Reference 9:

4 % 9 = 1 (goes to Block 1 Set 2) Cache miss

| | |Cache |
|---|:---:|:---:|
| | Set 1 | Set 2 |
| 0 | 4 | - |
| 1 | 5 | 9 |
| 2 | - | - |
| 3 | - | - |

### Reference 7:

4 % 7 = 3 (goes to Block 3 Set 1) Cache miss

| | | Cache |
|---|:---:|:---:|
| | Set 1 | Set 2 |
| 0 | 4 | - |
| 1 | 5 | 9 |
| 2 | - | - |
| 3 | 7 | - |

### Visualization of Cache memory for your understanding:

| Memory address | References | |
|:--------------:|:----------:|:------------------------:|
| 0 | 4 | |
| 1 | - | Cache line 0 elements |
| 2 | 5 | |
| 3 | 9 | Cache line 1 elements |
| 4 | - | |
| 5 | - | Cache line 2 elements |
| 6 | 7 | |
| 7 | - | Cache line 3 elements |

Both of the two set of cache line 1 is full, therefore calculating the location of first and last element of line gives us the answer.

Let's now check if the answer is option (1) as mentioned:

(j mod v) ∗ k to (j mod v) ∗ k + (k − 1)

Given:
- v = 4 (four blocks)
- k = 2 (two-way)

First element of cache line 1 = (j mod v) ∗ k = (5 mod 4) ∗ 2 = 2 yes, it's located at memory location 2.

Last element of cache line 1 = (j mod v) ∗ k + (k − 1) = (9 mod 4) ∗ 2 + (2 - 1) = 3 yes, it's located at memory location 3.

Done.

Answer: (j mod v) ∗ k to (j mod v) ∗ k + (k − 1)
