<!-- omit in toc -->
# Lab 3

This lab explores C's bitwise logic and shift operations.

In `bit_utils.c`, implement the functions specified in the header file `bit_utils.h`. Don't add additional include statements in `bit_utils.c`. By including `bit_utils.h`, your `bit_utils.c` will have access to all the necessary libraries.

<details open>
	<summary>Contents</summary>

- [Pre-lab knowledge](#pre-lab-knowledge)
	- [Background reading](#background-reading)
	- [Vim tips](#vim-tips)
	- [Testing](#testing)
	- [Debugging with GDB](#debugging-with-gdb)
	- [Integer representation](#integer-representation)
- [Part 1: Bitwise operators](#part-1-bitwise-operators)
- [Part 2: Shift operator](#part-2-shift-operator)
	- [bit\_select](#bit_select)
	- [barrel\_shift](#barrel_shift)
- [Submit your assignment](#submit-your-assignment)

</details>

## Pre-lab knowledge

To review bitwise operators and shift operations, see the lecture about [Integer Overflow and Casting, Bitwise Operations (logic and shift)](https://uncch.instructure.com/users/9947/files/6721201?verifier=ul42p7etinDLvO14yQ2qIxY8zSFXAyQS0T4o0ch5&wrap=1) ([videos](https://uncch.hosted.panopto.com/Panopto/Pages/Sessions/List.aspx#folderID=%225592a969-2ec3-485d-b26e-b0f100e6dde6%22)).

### Background reading

- [C Programming Language](https://uncch.instructure.com/users/9947/files/4526296?verifier=bzWbUsKclOVAAJ7MfuwOyS5v8DDILep0R7HtGh7t&wrap=1) Section 2.9 - Bitwise Operators

### Vim tips

If you have decided to stick with Vim, you are cooler and have a greater potential power level than everyone that isn't. Hopefully, you have gone over `vimtutor` a few times and are comfortable navigating with Vim, and maybe you're familiar enough to edit as fast as you would with a regular text editor.

With more practice, you can use Vim's powerful features to easily exceed your editing speed in a regular text editor. For Vim tips, see [Editors (Vim)](https://missing.csail.mit.edu/2020/editors/) (you may have to refresh the page) from the MIT Missing Semester course (their shell article was linked in a previous lab). We would recommend reading the article and/or watching the video and **practicing** the new Vim features that are shown. In particular, view [37:33](https://youtu.be/a6Q8Na575qc?t=2253) to 44:38 for a demo of advanced Vim features.

We recommend exercise 5, reproduced here:

> Use Vim for all your text editing for the next month. Whenever something seems inefficient, or when you think “there must be a better way”, try Googling it, there probably is.

<!-- Specifically, note that most IDE's have Vim plugins, such as [VSCodeVim](https://marketplace.visualstudio.com/items?itemName=vscodevim.vim) and [IdeaVim](https://www.jetbrains.com/help/idea/using-product-as-the-vim-editor.html) (IntelliJ). -->

Lastly, if you intend to customize Vim via `.vimrc`, note that changes you make to `.vimrc` in the container will not persist when you exit the container. So, if you would like to do so, you will need to install Vim locally (not in the container).

### Testing

`bit_utils.c` is a mini library rather than a program. `test.c` is the runner program that is used to test the functions. `test.c` defines a `main` function, so `bit_utils.c` cannot define a `main` function (e.g., to test the functions).

To test your functions, you may use the provided tests in `test.c`. This should be done with the [Makefile](Makefile), similar to the previous lab. Specifically, there are targets `test_mask`, `test_set`, `test_inverse`, `test_bit_select`, and `test_barrel_shift`. For example, to run the tests for the `mask` function, run `make test_mask`. To run tests for all functions, run `make test_all`. Similar to the previous lab, since the test cases are given in `test.c`, we will not specify expected input and output for each function in this writeup since that information is in `test.c`.

Finally, you may write additional tests in `test.c`, if you wish. However, all changes you make to `test.c` will be overwritten when submitting.

### Debugging with GDB

GDB is a command line debugger for C. Hopefully, you have already encountered debuggers for other languages, such as Python or Java, and have seen that they offer greater utility than debugging just with print statements, such as the ability to set breakpoints, run the program until the next breakpoint, and examine program state (variables and expressions) at any point in the program easily. The page [GDB and Debugging](https://web.stanford.edu/class/archive/cs/cs107/cs107.1194/resources/gdb) provides a brief introduction to GDB, and we strongly recommend using GDB for debugging in this lab and future labs. The section [gdb Commands Reference](https://web.stanford.edu/class/archive/cs/cs107/cs107.1194/resources/gdb#gdb-commands-reference) is particularly useful.

To use GDB, the program has to be compiled with `-g` to include debugging information. This is done in all of our Makefiles.

### Integer representation

Integers in C can be declared as decimal, hexadecimal or octal numbers. The following three lines of code are equivalent:

``` c
int n = 0x05; int i = 0xa2; // hex
int n = 5;    int i = 162;  // decimal
int n = 05;   int i = 0242; // octal
```

The underlying representation in binary for `162` and `0xa2` is the same. You may use the `"%d"`, `"%x"`, and `"%o"` format specifiers to print integers in decimal, hex, or octal format, respectively.

In this lab, you will probably want to use `"%x"` when debugging because we want to look directly at the bit representation (see the test cases in `test.c`), not the decimal representation. We could display in binary format, but hex is more concise and readable because each hexit corresponds to four bits. For example, `0x7 = 0b0111`, `0x07 = 0b00000111`, `0xE = 0b1110`, and `0xE7 = 0b11100111`. It is usually easier to read the hex representation than the binary representation.

Lastly, in this assignment, all functions operate on and return `unsigned int`s, which are 32 bits or 4 bytes on our machines. This is to prevent arithmetic shifting, which does not make sense in the context of this lab. If a number can be represented in fewer than 32 bits, then it is zero-padded to 32 bits. For example, `0xF` is `0x0000000F`.

## Part 1: Bitwise operators

In `bit_utils.c`, write 3 functions: `mask`, `set`, and `inverse`. These functions each take two integer parameters: a number to be operated on and the bits that will be masked, set, or inversed. Each function should return the number with the applied mask, set, or inverse.

For examples, see [`test.c`](test.c). For each function, the first test is basic and should be easily understandable, and the rest of the tests are more verbose.

These functions should each take only one or two lines of code.

## Part 2: Shift operator

### bit_select

Write a function called `bit_select` that takes three integer parameters: a number, the most significant bit to select, and the least significant. The function should return the bits between the starting bit and the ending bit of the number (including the starting and the ending bit).

For examples, see `test.c`. The first 3 tests are basic, and the rest of the tests are more verbose.

Remember the difference between shift right logical and shift right arithmetic. C has only one right shift operator `>>`. When the left operand is `unsigned`, as in this lab, a logical shift will be performed. Otherwise, when the left operand is signed, most machines will perform an arithmetic shift.

### barrel_shift

Write a function called `barrel_shift` that takes two integer parameters: a number and a shift amount (shamt). The function should return the value of the number circularly shifted to the right by shamt bits (i.e., the bits that are shifted out of the right end are put back in at the left end).

`barrel_shift` examples are provided in `test.c`.

## Submit your assignment

1. Use git to push your finished code to this GitHub repository.
2. Go to the COMP 211 course in Gradescope and click on the assignment called **Lab 3**.
3. Click on the option to **Submit Assignment** and choose GitHub as the submission method.
4. You should see a list of your public repositories. Select the one named **lab-03-yourname** and submit it.
5. Your assignment should be autograded within a few seconds and you will receive feedback for the autograded portion.
6. If you receive all the points, then you have completed this lab! Otherwise, you are free to keep pushing commits to your GitHub repository and submit for regrading up until the deadline of the lab.
