<!-- omit in toc-->
# Lab 4

In this lab, you'll gain experience working with MIPS instructions by coding a MIPS VM/simulator. Your simulator will

1. convert an integer value into a 32-bit machine (i.e., binary) instruction,
2. determine the type of instruction (R or I),
3. identify the field values (i.e., opcode, rs, rt, rd, sa, func, immediate, etc.), and
4. execute the instruction using a simulated set of registers.  

In particular, this lab has four goals:

In this lab, you will apply the `bit_select` function in Lab 3 (the code is given here, in case you need it) to identify the fields in a binary instruction. You will develop a program that closely simulates a real problem and gain experience with C structs, enums, pointers, and `malloc`.

<details open>
    <summary>Contents</summary>

- [Lab 4](#lab-4)
    - [Pre-lab knowledge](#pre-lab-knowledge)
        - [Background reading](#background-reading)
        - [Fixed-width integer types](#fixed-width-integer-types)
    - [Lab structure](#lab-structure)
    - [Part 0](#part-0)
    - [Part 1](#part-1)
    - [Part 2](#part-2)
    - [Examples/testing](#examplestesting)
    - [Submit your assignment](#submit-your-assignment)

</details>

## Pre-lab knowledge

### Background reading

* [MIPS cheat sheet](https://uncch.instructure.com/users/9947/files/4534610?verifier=0lJburrtzSqIT791v3YyAlhY3ZBq0MykyBPR1nY6&wrap=1) and other [reference material](https://inst.eecs.berkeley.edu/~cs61c/resources/MIPS_help.html)
* [MIPS Instruction Set Architecture lecture slides](https://uncch.instructure.com/users/9947/files/5281339?verifier=TFMoH6zJsSK35Vd4cCoxOXtTsHnUk9duDuBXABCj&wrap=1) (pg. 8)

The MIPS cheat sheet and lecture slides will be invaluable for this lab, so please be sure to understand those.

### Fixed-width integer types

Throughout the lab, you will see `uint8_t`, `uint16_t`, or `uint32_t` being used as types. These are unsigned data types that are used to represent an integer in an explicit number of `N` bits.

* `uint8_t` represents an `unsigned char` with a size of 8 bits.
* `uint16_t` represents an `unsigned short` with a size of 16 bits.
* `uint32_t` represents an `unsigned int` with a size of 32 bits.

We choose not to use `unsigned char`, `unsigned short`, and `unsigned int` because those are not guaranteed to be 8, 16, and 32 bits on every system.

The values of these types range from `0` to <code>2<sup>N</sup> - 1</code> since they are unsigned. You can read more about these types in this [article](https://www.badprog.com/c-type-what-are-uint8-t-uint16-t-uint32-t-and-uint64-t) or this [manual](https://www.gnu.org/software/libc/manual/html_node/Integers.html).

## Lab structure

```text
.
├── Makefile
├── README.md
├── bit_utils.c - Do not modify (functions from previous lab).
├── bit_utils.h - Do not modify (from previous lab).
├── instructions.c - Contains functions to be implemented in Part 1. 
├── instructions.h - Do not modify and please read carefully comments (important definitions and information).
└── lab04.c - Contains functions to be implemented in Part 2.
```

There are comments in the `lab04.c` and `instructions.c` source files as well as in the `instructions.h` header file. Read the comments carefully, as they provide information needed to complete this assignment.

## Part 0

Take a look through each source file and read the comments to have a better understanding of the assignment and the functions you will need to implement.

## Part 1

In this part, you will edit `instructions.c`.

First, implement `get_type_of_instruction`. This function determines the instruction type given an unsigned 32-bit integer by returning an `instruction_type` enum value. For example, if the input is the following 32-bit integer:

```text
00000001000000110001000000100010
```

the function should be able to recognize it as an R-type instruction and return `R_TYPE`. Although J-type instructions also exist in MIPS, you need only distinguish between R-type or I-type in this lab.

Then, implement `create_r_instruction`, `create_i_instruction`, which serve as "constructors" for the `r_instruction` and `i_instruction` structs, which are defined as follows in `instructions.h`:

```c
typedef struct {
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t shamt;
    uint8_t func;
} r_instruction;

typedef struct { 
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint16_t immediate;
} i_instruction;
```

`create_r_instruction` and `create_i_instruction` are given the instruction as a 32-bit integer and return a pointer to a `malloc`'d `r_instruction`/`i_instruction` with all fields initialized.

In the next part of this lab, these structures will be used for execution.

To complete this part, reference the top left of the MIPS cheat sheet, which details the position of the fields that each instruction type has:

<p align="center">
    <img src="https://i.imgur.com/MmoOTgo.png">
</p>
<p align="center"><em>MIPS instruction format</em></p>

`instructions.h` has several constants that you should use to implement these functions. Specifically, once you have identified whether the instruction is R-type or I-type, you need only extract the bits at the correct positions to initialize the instruction struct. For example, bits 5-0 are the funct bits for an R-type instruction, so the constants `FUNC_START_BIT` and `FUNC_END_BIT` are defined as 5 and 0 and given in `instructions.h`.

## Part 2

In `lab04.c`, implement `execute_r_instruction` and `execute_i_instruction`. `execute_r_instruction` accepts a pointer to an `r_instruction`, while `execute_i_instruction` accepts a pointer to an `i_instruction`. Each function first determines the specific instruction to execute (e.g., if R-type, is the instruction `add`, `sub`, etc.) and then executes it.

Each instruction modifies a register, so update the `registers` global array variable as appropriate. For example, for the MIPS instruction

```asm
and $4, $1, $2
```

Register 4 would be updated with the contents of the bitwise AND of register #1 and register #2, as follows:

```c
registers[4] = registers[1] & registers[2];
```

The following MIPS instructions need to be implemented: `sll`, `sra`, `add`, `sub`, `and`, `or`, `nor`, `addi`, `andi`, `ori`.

**Note**: There are some nuances in MIPS architecture that we will ignore in this lab. For example, `$0`/`$zero` (the "zero register") is usually read-only and always contains the value 0. However, for this lab, all 32 registers can be considered general registers. Further, do not need to consider the signed extension of immediate values. Each update to a register should be fairly straightforward, similar to above.

## Examples/testing

Consider the following sequence of MIPS instructions:

```asm
addi $0, $0, 21834		# r[0] = r[0] + 21834
add $1, $0, $0			# r[1] = r[0] + r[0]
sub $2, $1, $0			# r[2] = r[1] - r[0]
ori $3, $2, 1			# r[3] = r[2] | 1
```

In order to execute this series of instructions, each instruction will need to be translated to its binary equivalent by using an assembler. Using your [MIPS cheatsheet](https://sakai.unc.edu/access/content/group/167842e9-e6e0-4d16-81bd-842fcf59831e/Supplemental/mips_cheat_sheet.pdf), you can do this translation yourself.

```text
00100000000000000101010101001010
00000000000000000000100000100000
00000000001000000001000000100010
00110100010000110000000000000001
```

For this lab, each instruction is accepted as an integer through standard input, so each binary instruction will need to undergo another conversion:

```text
536892746
2080
2101282
876806145
```

You can then enter each integer into the simulator. To exit the simulator, you can enter the integer `4294967295`. The `main` method handles this special instruction, so you don't need to implement it.

```text
Please enter your instruction as a 32-bit integer: 536892746
Current register status:
[21834, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
Please enter your instruction as a 32-bit integer: 2080
Current register status:
[21834, 43668, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
Please enter your instruction as a 32-bit integer: 2101282
Current register status:
[21834, 43668, 21834, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
Please enter your instruction as a 32-bit integer: 876806145
Current register status:
[21834, 43668, 21834, 21835, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
Please enter your instruction as a 32-bit integer: 4294967295
```

## Submit your assignment

1. Use git to push your finished code to this GitHub repository.
2. Go to the COMP 211 course in Gradescope and click on the assignment called **Lab 04**.
3. Click on the option to **Submit Assignment** and choose GitHub as the submission method.
4. You should see a list of your public repositories. Select the one named **lab-04-yourname** and submit it.
5. Your assignment should be autograded within a few seconds, and you will receive feedback for the autograded portion.
6. If you receive all the points, then you have completed this lab! Otherwise, you are free to keep pushing commits to your GitHub repository and submit for regrading up until the deadline of the lab.
