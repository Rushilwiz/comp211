<!-- omit in toc -->
# Lab 2

In this lab, you will implement several methods of representing numbers (integer and real) in binary.

<details open>
	<summary>Contents</summary>

- [Pre-lab knowledge](#pre-lab-knowledge)
    - [Number representation](#number-representation)
    - [I/O](#io)
    - [Makefile](#makefile)
    - [Autograder](#autograder)
- [Part 1. Signed integers](#part-1-signed-integers)
- [Part 2. Two's complement](#part-2-twos-complement)
- [Part 3. Negation of two's complement](#part-3-negation-of-twos-complement)
- [Part 4. IEEE754 float 32](#part-4-ieee754-float-32)
- [Submit your assignment](#submit-your-assignment)

</details>

## Pre-lab knowledge

### Number representation

To review number representation, see the lecture about [information encoding, number systems, and integer representation and floating point representation](https://uncch.instructure.com/users/9947/files/6721199?verifier=oUYyOKAiD0sBCNKBB8XHXrx67hqTg3L8nBfIlSKU&wrap=1) ([video](https://uncch.hosted.panopto.com/Panopto/Pages/Sessions/List.aspx?folderID=bb31c498-8a66-4d21-92aa-b0f100e6ddda)).

Although lecture material should suffice, you may also refer to the following sources:

* [Supplement: Binary Math and Signed Representations](https://uncch.instructure.com/users/9947/files/4534602?verifier=V0fp04VZnOi0ytrumtvCTbL2Xnz1zR5AUmj2H2S3&wrap=1)
* Sections 2.1, 2.2, and 2.3 of [Computer Systems: A Programmer's Perspective](https://uncch.instructure.com/users/9947/files/4526297?verifier=GsaGSp6QkNQvZGMOCCiuAT4eyRWq70bxIKOgxjZr&wrap=1).

### I/O

Similarly, you may refer to the following sources for information about I/O that will be needed:

* Section 5.10 Command-line Arguments in [The C Programming Language](https://uncch.instructure.com/users/9947/files/4526296?verifier=bzWbUsKclOVAAJ7MfuwOyS5v8DDILep0R7HtGh7t&wrap=1)
* Section 7.2 Formatted Output - Printf in The C Programming Language

In particular, you should not use `getchar`, `fgets`, or `scanf`; instead, you should work with `argv`.

### Makefile

See the file [Makefile](Makefile) in your repository. Makefiles are used by the command `make`, which is a build automation tool.

To try it out, run `make` from the root of your repo. You'll see some output, and you'll also notice that 4 new executables were created. This command automates the `gcc` steps that we would normally repeatedly execute!

We will also use this Makefile to run tests, both locally and in the autograder, so now we'll discuss its contents.

First, see the target called `signed`:

```make
signed: signed.c
	$(CC) $(CFLAGS) signed.c -o signed
```

The second line is exactly what we would write to compile `signed.c` into the executable `signed`. `CC` and `CFLAGS` are variables defined at the top of the file.

The first line follows the syntax `target: dependencies`. Because `signed` is the target, we can run `make signed` to perform only the action above (i.e., compile `signed.c`). Try it, and you should see the output

```text
learncli$ make signed
make: 'signed' is up to date.
```

Because we specified that the target `signed` depends on `signed.c`, `make` knows it doesn't need to do anything for `signed` since we had already run that target when we previously ran `make`, and we didn't modify `signed.c` since then. However, if you modify `signed.c` (e.g., change `EXIT_SUCCESS` to `EXIT_FAILURE`), then `make signed` will recompile `signed.c`.

You'll also notice the target `all` at the top, which depends on `signed`, `twos`, `negate2s`, and `f32`. When you ran `make` without arguments, `all` ran because it is the first target.

Lastly, the `test` target depends on `test_signed`, `test_twos`, `test_negate2s`, and `testf32`. Thus, you can run `make test_signed` to run the tests for `signed.c` or `make test` to run local tests for all files.

For example, if you run `make test_signed` now (without implementing `signed.c`), you should see

```text
learncli$ make test_signed
gcc -Wall -Werror -g signed.c -o signed
diff --ignore-blank-lines <(echo 0000000011010011) <(./signed +211)
1d0
< 0000000011010011
make: *** [Makefile:24: test_signed] Error 1
learncli$ echo $?  # print exit status of previous command
2
```

When the program is done and works properly, you should instead see

```text
learncli$ make test_signed
gcc -Wall -Werror -g signed.c -o signed
diff --ignore-blank-lines <(echo 0000000011010011) <(./signed +211)
diff --ignore-blank-lines <(echo 1000000011010011) <(./signed -211)
diff --ignore-blank-lines <(echo not possible) <(./signed +100000)
diff --ignore-blank-lines <(echo 0000000000000000) <(./signed +0)
diff --ignore-blank-lines <(echo 1000000000000000) <(./signed -0)
learncli$ echo $?
0
```

The Makefile tests are comprised of `diff` commands using the `<()` operator, which you should be familiar with from the previous lab. So, we will not specify expected input and output for your programs in this writeup since that information is already in the Makefile.

### Autograder

The autograder will run the tests in our Makefile and, in addition, some tests using random inputs.

Note that all programs for this lab expect input from command-line arguments, **not standard input**, unlike the previous lab. Additionally, assume that any random inputs from the autograder are always syntactically valid (i.e., follow the examples in the Makefile), so you do not need to worry about syntactically invalid inputs. However, as shown in the tests for `signed.c` and `twos.c`, if a number cannot be represented, print `not possible`.

## Part 1. Signed integers

In `signed.c`, write a program that takes a base-10 integer preceded by a plus or minus sign as a command-line argument and outputs a 16-bit string of 1's and 0's corresponding to the integer's 16-bit signed magnitude representation. For example,

```text
learncli$ ./signed +211
0000000011010011
learncli$ ./signed +100000
not possible
```

For more I/O examples, see the [Makefile](Makefile). To run local tests, see the section [above](#makefile).

Use the `stdlib.h` function [`atoi`](https://cplusplus.com/reference/cstdlib/atoi/) [^atoi] to convert a string to integer. The syntax of inputs in the test cases matches the syntax that `atoi` expects. Specifically, `atoi` accepts an optional initial `+` or `-`, followed by as many base-10 digits as possible.

[^atoi]: `atoi` is short for "ASCII to integer".

Note that +0 and -0 have different signed magnitude representations, so your program should output the correct representations for these two inputs. Is this property of signed magnitude desirable or undesirable?

## Part 2. Two's complement

In `twos.c`, write a program that takes a base-10 integer preceded by a plus or minus sign as a command-line argument and outputs the 16-bit string of 1's and 0's corresponding to the integer's 16-bit two's complement representation. See I/O examples in the Makefile.

Note that 0 has only one representation in two's complement, unlike signed magnitude.

## Part 3. Negation of two's complement

In `negate2s.c`, write a program that takes **32-bit** two's complement representation of an integer as a command-line argument and outputs a 32-bit two's complement bitstring corresponding to the negated version of the number. See I/O examples in the Makefile.

## Part 4. IEEE754 float 32

In `f32.c`, write a program that takes a **32-bit** IEEE754 representation of a float as a command-line argument and outputs the `float` it represents in base-10. See I/O examples in the Makefile.

To account for floating-point error, when printing the float, use `printf("%.4f\n", float_value)` to print to 4 decimal places. These autograder will check these digits for an exact match.

These libraries should be useful:

* `string.h`
    * `argv[1]` is a string. You are now allowed to use `string.h` to make working with strings easier (unlike the previous lab).
        * When creating a new string, you must null-terminate it by putting the null terminator `'\0'` in the last position. If you are using a `char[]`, allocate one extra character than what you expect to use. Most string functions will not work correctly if the string is not null-terminated.
    * **You do not have to convert the exponent bits to a base-10 integer yourself**. Please use [`strtol`](https://www.tutorialspoint.com/c_standard_library/c_function_strtol.htm) to convert the exponent bits (`const char*`) to `long`. Pass `NULL` as the second argument.
    * You may use `strlen` to get the length of a string.
    * You may use [`strncpy`](https://www.tutorialspoint.com/c_standard_library/c_function_strncpy.htm) to extract the exponent bits and mantissa bits from the 32-bit string. It can be used similarly to slicing in Python (`str[start:end]`) or Java's `substring(begIndex, endIndex)` method.
* `math.h`
    * **Please do not implement exponentiation yourself**. For exponentiation, use `pow`, which takes two `double`s and returns a `double`.
    * As done in the Makefile, the program must be compiled with the `-lm` flag to link the math library. For example, `gcc f32.c -lm -o f32`. `-lm` must go after the objects to be linked.

## Submit your assignment

Assignment submissions will be made through [Gradescope](https://www.gradescope.com).

To submit your assignment, you must commit and push your work to this repository using git. You are likely unfamiliar with git at this point, so just follow these steps:

1. Navigate to the base folder of the repository within Docker using the `cd` commmand.
2. Type `git status`. You should see a list of changes that have been made to the repository.
3. Type `git add -A`. This signals that you want to place all modified / new files on the "stage" so that their changes can take effect.
4. Type `git commit -m "Your Message Here"`. This shows that you are "committing" to the changes you put on the stage. Instead of Your Message Here, you should write a meaningful message about what changes you have made.
5. Type `git push`. This takes the commit that was made locally on your machine and "pushes" it to GitHub. Now, when you view this repository on GitHub you should be able to see the changes you've made, namely the addition of your source files!
6. Go to the COMP 211 course in Gradescope and click on the assignment called **Lab 2**.
7. Click on the option to **Submit Assignment** and choose GitHub as the submission method.
8. You should see a list of your public repositories. Select the one named **lab-02-yourname** and submit it.
9. Your assignment should be autograded within a few seconds and you will receive feedback for the autograded portion.
10. If you receive all the points, then you have completed this lab! Otherwise, you are free to keep pushing commits to your GitHub repository and submit for regrading up until the deadline of the lab.
