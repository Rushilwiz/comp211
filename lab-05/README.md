<!-- omit in toc -->
# Lab 5

Caches are implemented in computing systems because they mitigate the lengthy time that it takes to retrieve data from memory. This serves as the primary motivation for this lab, in which you will implement a cache simulator that supports the direct mapping (DM) and fully associative (FA) cache mapping techniques.

This lab reinforces the following concepts:

* Old
  * Structs
  * Interfaces (headers)
  * Pointers (passing values by reference)
  * Bit manipulation (`bit_utils.c` from a previous lab is included here)
* New
  * Caches and cache algorithms
  * Addressing physical memory

To simplify the lab, the size of the cache and physical memory in this simulator will be much smaller than they would be in practice. In particular, you will be working with 8 cache lines and physical memory with 256 addresses, each of which stores a byte.

<details open>
<summary>Contents</summary>

- [Pre-lab knowledge](#pre-lab-knowledge)
  - [Background reading](#background-reading)
  - [Lab structure](#lab-structure)
  - [Running code](#running-code)
- [Part 0. number\_of\_blocks](#part-0-number_of_blocks)
  - [Testing](#testing)
- [Part 1. Direct mapping](#part-1-direct-mapping)
  - [Testing](#testing-1)
- [Part 2. Fully associative mapping](#part-2-fully-associative-mapping)
  - [Testing](#testing-2)
- [Submit your assignment](#submit-your-assignment)

</details>

## Pre-lab knowledge

### Background reading

Refer to the following for a review of caches and the differences between the direct mapping and fully associative cache mapping techniques. As mentioned earlier, you will implement both techniques.

* (Required) [System concepts, Main Memory and Memory Hierarchy](https://uncch.instructure.com/users/9947/files/5587554?verifier=5pVYCbHJeS551teiKVw1IJezkRZ2uGCeTdpQ1bdu&wrap=1).
* (Required) [Cache Memory, Mapping Algorithms, and the Principle of Locality](https://uncch.instructure.com/users/9947/files/5661387?verifier=FLrrKMVo00veF13U7m7Newwf4c52dBHJB4FWz7iq&wrap=1)
* (Optional) [CSApp Section 6.2](https://uncch.instructure.com/users/9947/files/4526297?verifier=GsaGSp6QkNQvZGMOCCiuAT4eyRWq70bxIKOgxjZr&wrap=1)
* (Optional) If you need to review the relationship between pointers and arrays, see [Chapter 5 of The C Programming Language](https://uncch.instructure.com/users/9947/files/4526297?verifier=GsaGSp6QkNQvZGMOCCiuAT4eyRWq70bxIKOgxjZr&wrap=1).

### Lab structure

```text
.
├── Makefile
├── README.md
├── bit_utils.c - Do not modify (functions from Lab 3)
├── bit_utils.h - Do not modify
├── cache.c - Implement the cread function (DM and FA)
├── cache.h - Do not modify
├── main.c - Do not modify. Contains main function
├── memory.c - Implement number_of_blocks
├── memory.h - Do not modify
├── memory.txt - Do not modify. Contains sample memory values to be read by memory.c. Each line represents a distinct memory address, and each byte is the value stored at that address.
└── tests - Contains files for testing
    ├── directmapping_input0.txt
    ├── directmapping_input1.txt
    ├── directmapping_output0.txt
    ├── directmapping_output1.txt
    ├── fullyassociative_input0.txt
    ├── fullyassociative_input1.txt
    ├── fullyassociative_output0.txt
    └── fullyassociative_output1.txt
```

Please familiarize yourself with these files. You can open all the `.c` and `.h` files in the current working directory in vim tabs with the command `vim -p *.c *.h`, and you can navigate the tabs with `gt` and `gT`.

In particular, pay attention to the following:

* The defined constants and function prototypes in the `.h` files and how they correspond with the cache mapping algorithms and the size of blocks, address length, cache size, etc.
* The control flow of the main function in `main.c`
* The `cache_line` struct, defined as follows. You should also view the `initialize_cache` function in `cache.c` to see how this struct is used.

```c
typedef struct {
    int tag;
    int hit_count;
    unsigned int* block;
} cache_line;
```

While there are a lot of moving parts in this lab, there are only two functions you need to implement!

### Running code

Similarly to previous labs, you are provided a `Makefile` for running the code.

## Part 0. number_of_blocks

In `memory.c`, implement `number_of_blocks`. There is a docstring for this function in `memory.h`.

The specification for this function is simple. Given the number of bits it takes to represent the number of addresses used in the simulation and the number of offset bits used in the cache, how many blocks can the address space be divided into?

`number_of_blocks` should return the `FAIL` constant (defined in `memory.h`) if either of the arguments is not positive or if `addr_bits` is less than `num_block_offset_bits`.

For example, if the number of addresses is 256 and the number of offset bits is 2 (resulting in a block size of 2<sup>2</sup> = 4), then our address space can be divided into 64 blocks of 4 addresses each.

In our simulation, the number of addresses is always 256, but this function should work for any address space size and number of offset bits.

**Note**: You have access to functions such as `exp2` because this file includes `math.h`.

### Testing

To test your `number_of_blocks` function, you may write some sample function calls with print statements at the beginning of the `main` function in `main.c`. Once you are convinced you are calculating the correct number of blocks, delete your debug code and submit to Gradescope to confirm. Note that you'll get some warnings from gcc because not all the functions have been implemented. You can ignore these for now.

## Part 1. Direct mapping

In `cache.c`, implement the direct mapping mode of the `cread` function, which reads a value from the cache. There is a docstring for this function in `cache.h`.

This function performs either direct mapping or fully associative mapping based on the value of the `cmf` parameter. Note that in `cache.h`, we have defined the constants `DM` and `FA`. If `cmf` is equal to `DM`, then `cread` should apply the direct mapping algorithm; else, if it is equal to `FA`, then it should apply the fully associative algorithm.

For this part, you need only implement the direct mapping algorithm. A paraphrased version of the algorithm is supplied here (for complete details, see [Background reading](#background-reading)), but some details (such as dealing with the `hit` and `replace` parameters and modifying some properties of `cache_line` structs) are omitted and are left for you to figure out.

* Use `bit_select` from `bit_utils.c` to extract the block offset, line, and tag bits (derived from `NUM_BLOCK_OFFSET_BITS`, `NUM_LINE_BITS` and `NUM_TAG_BITS_DM`) from `hex_addr`.
* Check if the cache line corresponding to the line bits has tag bits that match with the tag you are searching for. You may want to review the definition of the `cache_line` struct.
   	* If the tag bits match, then you have found the address you are searching for in the cache. You do not need to replace anything, and that cache line's `hit_count` should be incremented.
   	* Else, if the tag bits do not match, there is a cache miss (i.e., the address we are searching for is not in the cache). In this case, either the cache line is empty (i.e., the tag is equal to the `EMPTY` constant in `cache.h`) or not empty.
	* Whether empty or not empty, we are now going to set this cache line's memory `block` and `tag` to those of the block we are searching for. We will also set `hit_count` to 1.
		* To set `block` correctly, you will want to use `NUM_BLOCK_OFFSET_BITS` from `memory.h`. You will also need to use `block_location` and `phy_memory`, both `unsigned int*`.
* Set `hit` and `replace` to appropriate boolean values (`true | false`) based on whether there was a cache hit and whether an existing value in the cache line was replaced.
	* If the tag bits did not match and the cache line was empty, this is not considered a replacement (rather, it is an initialization).
* Set `ret_val` to be the value in memory corresponding to the requested `hex_addr`.

### Testing

To test your code, you will run the executable generated by the `main.c` file, which takes in `memory.txt` as a command line argument to initialize the simulator's physical memory. The command to run your program in this manner after compiling is `./main memory.txt`. Or you can simply run `make run`, which maps to that command.

Your testing of the algorithm will consist of entering hexadecimal addresses into the simulator and seeing if the output of the cache acts as you would expect. In particular, look out for the following:

* Does the tag referenced in the cache correspond to the appropriate hexadecimal address from `memory.txt`?
* Is the return value the same as what is present in the corresponding hexadecimal address in `memory.txt`?
* If a block of addresses is already stored in the cache, does entering an address from that block result in a cache hit (and vice versa)?
* Does a particular hexadecimal address always map to the same cache line?

Like previous labs, you are given sample input and output files. However, you will not be able to simply output your result and compare with `diff`. This is partly because the main loop of `main.c` loops infinitely without keyboard intervention and because we want you to carefully sample the examples to understand the cache behavior. Thus, the input files include a sequence of values that you should enter manually and the output files contain everything that should be output to the console.

For example, examine `directmapping_input0.txt`:

```text
1  
00
01
02
03
09
0A
0B
10
20
20
40
```

The 1 indicates that we have chosen 1 (direct mapping) as our cache mapping function. Every subsequent number is a hexadecimal address in physical memory that the cache attempts to read. The expected results are in `directmapping_output1.txt`. The following snippet from this file demonstrates expected I/O:

```text
------------------------
[STEP 1] Setting up physical memory
------------------------
Physical memory addressable bits = 8, total number of blocks = 64

------------------------
[STEP 2] Determining physical memory block locations
------------------------

------------------------
[STEP 3] Select cache mapping function (CMF)
------------------------
1 = Direct mapping
2 = Fully associative
------------------------
Please enter 1 or 2: 1 				           // Input on this line.
------------------------
[STEP 4] initializing cache
------------------------

------------------------
[STEP 5] Starting simulation
------------------------
CMF is Direct Mapping
To exit simulation, press Ctrl+C

Please enter 8-bit hexadecimal address: 00                 // Input on this line.

Entered Hexadecimal (Base-16) address 00 (Base-10 value 0)

---------------------------------------------
line	tag	num of hits
---------------------------------------------
0	00	1
1	-1	0
2	-1	0
3	-1	0
4	-1	0
5	-1	0
6	-1	0
7	-1	0
[MISS:No Replacement] The byte value at memory address 00 is 7F
```

The way to interpret this sequence is that the user entered `1` to choose the direct mapping cache algorithm. Then, the user entered the hexadecimal address `00` as the address whose value should be read from the cache. Since the cache was empty, this was a cache miss and the block of physical memory corresponding to address `00` was loaded into cache line 0. If you examine `memory.txt`, you will see that the value stored in the first line is indeed `7F`.

## Part 2. Fully associative mapping

You will now implement the second component of the `cread` function, which uses the fully associative mapping algorithm when the user supplies a `cmf` parameter of `FA`. As was the case in the previous part, you can find more details about the algorithm in [Background reading](#background-reading), but here is a paraphrased version of the algorithm:

* Use `bit_select` from `bit_utils.c` to extract the block offset and tag bits (derived from `NUM_BLOCK_OFFSET_BITS` and `NUM_TAG_BITS_FA`) from `hex_addr`. Note that because this is fully associative, we do not have line bits.
* Loop through each of the cache lines and determine which, if any, needs to be replaced.
	* If the tag of any cache line matches the tag you are searching for, then this is a cache hit (i.e., the address you are searching for has already been cached), and you do not need to replace anything. Increment that cache line's `hit_count`.
	* Otherwise, if there are cache lines that have not been used yet (i.e., empty `tag`), cache the value in the first available open line (i.e. the one of lowest index in the array of cache lines). To do so, set the cache line's `block` and `tag` appropriately (similar to the way you did it for [DM](#part-1-direct-mapping)). Also, set `hit_count` to 1.
	* If every cache line has been used (i.e., cache full), use the Least Frequently Used replacement strategy to determine which cache line to replace. That is, replace the cache line with the fewest number of hits. In the event of a tie, use the cache line with a lower index in the array of cache lines.
		* Note that this means that in the above cases, you must update the relevant cache lines' `hit_count` accordingly and keep track of a minimum `hit_count`.
* Set `hit` and `replace` to appropriate boolean values, similar to the way you did it for [DM](#part-1-direct-mapping).
	* As before, if an empty cache line is initialized, this is not considered a replacement.
* Set `ret_val` to be the value in memory corresponding to the requested `hex_addr`.

### Testing

Testing for this part works the same way as in the previous part. You just need to use the appropriate sample files. However, since the fully associative algorithm differs from direct mapping, it will not be the case that a particular hexadecimal address always maps to the same cache line.

## Submit your assignment

1. Use git to push your finished code to this GitHub repository.
2. Go to the COMP 211 course in Gradescope and click on the assignment called **Lab 5**.
3. Click on the option to **Submit Assignment** and choose GitHub as the submission method.
4. You should see a list of your public repositories. Select the one named **lab-05-yourname** and submit it.
5. Your assignment should be autograded within a few seconds and you will receive feedback for the autograded portion.
6. If you receive all the points, then you have completed this lab! Otherwise, you are free to keep pushing commits to your GitHub repository and submit for regrading up until the deadline of the lab.
