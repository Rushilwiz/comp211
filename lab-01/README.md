<!-- omit in toc -->
# Lab 1

In this lab, you will write two string-based exercises in C and use the Linux file redirection and pipe operators. You should be able to do the string exercises with knowledge only from **chapter 1** in the [C Programming Language](https://uncch.instructure.com/users/9947/files/4526296?verifier=bzWbUsKclOVAAJ7MfuwOyS5v8DDILep0R7HtGh7t&wrap=1). Specifically, carefully study the code examples in sections 1.5 and 1.6.

In this assignment, you may only use the `stdlib.h`, `stdio.h`, and `stdbool.h` headers. That is, you **may not** include the `string.h` header. If you use the string library in your program, then the autograder will abort and assign no points to your submission. If you have any questions, ask!

<details open>
  <summary>Contents</summary>

- [Linux tips](#linux-tips)
  - [GCC](#gcc)
  - [tldr](#tldr)
  - [Exiting program](#exiting-program)
- [Part 1: Lower](#part-1-lower)
  - [Testing](#testing)
  - [Pipe](#pipe)
- [Part 2: I/O redirection and piping](#part-2-io-redirection-and-piping)
  - [Task 0: Setup](#task-0-setup)
  - [Task 1: Redirection](#task-1-redirection)
  - [Task 2: Pipe](#task-2-pipe)
    - [Usefulness](#usefulness)
- [Part 3: Truncator](#part-3-truncator)
  - [Notes](#notes)
- [Code style](#code-style)
  - [Grading note](#grading-note)
- [Submit your assignment](#submit-your-assignment)

</details>

## Linux tips

The workflow to write, compile, and run C programs is identical to that of the previous lab. If you need to refamiliarize yourself with `git` (cloning and pushing to GitHub), navigating with `cd`, or using vim, then refer to the previous lab. Below is some more useful information about using your Linux environment.

### GCC

When you use `gcc <prog>.c` to compile a C program, GCC compiles the program and stores the binary in `a.out`. `./a.out` runs the program (in Linux, typing `./` before the filename attempts to find and execute that file). To store the binary in a different file, use the `-o` flag. For example, `gcc hello.c -o hello` stores the binary in a file named `hello` that can be run with `./hello`.

### tldr

There are plenty of Linux commands that you will encounter and need in your career, each with their own flags, and it's impossible to remember them all (much less for us to explain them all). Recall from Chapter 1 of [The Sorcerer's Shell](https://uncch.instructure.com/users/9947/files/4534606?verifier=OtzqqS8AJ9vtBgYkQDnjzhdQCkb6fk4YT47bMMXA&wrap=1) that we can get information about a program by running it in help mode, reading the `man` pages, and/or searching online for plain English explanations. We can combine the latter two approaches by using [tldr](https://github.com/tldr-pages/tldr), which is installed in your container.

Usage of `tldr` is identical to that of `man`. For example, `tldr gcc` displays the following 25 lines:

```text
learncli$ tldr gcc

  gcc

  Preprocess and compile C and C++ source files, then assemble and link them together.
  More information: https://gcc.gnu.org.

  - Compile multiple source files into an executable:
    gcc path/to/source1.c path/to/source2.c ... -o path/to/output_executable

  - Show common warnings, debug symbols in output, and optimize without affecting debugging:
    gcc path/to/source.c -Wall -g -Og -o path/to/output_executable

  - Include libraries from a different path:
    gcc path/to/source.c -o path/to/output_executable -Ipath/to/header -Lpath/to/library -llibrary_name

  - Compile source code into Assembler instructions:
    gcc -S path/to/source.c

  - Compile source code into an object file without linking:
    gcc -c path/to/source.c

  - Optimize the compiled program for performance:
    gcc path/to/source.c -O1|2|3|fast -o path/to/output_executable

```

Contrast this with `man gcc`, which displays 18131 lines, sacrificing readability for completeness. Specifically, the `man` pages begin with all possible flags, not just the commonly used ones, and explain edge use cases instead of showing common use cases. The `man` pages are encyclopedic (and explain core C functions, such as `malloc`, whereas `tldr` doesn't), but `tldr` is more practical for most use cases.

From now on, we will expect that you should be able to use `tldr` (or other web resources) to learn how to use commands. Note that `tldr` is not limited to just Linux commands. For example, `tldr` has pages for `pip`, `git`, `npm`, etc.

### Exiting program

Suppose a program we're running is not halting, and we would like to exit. We can simulate this by running `cat` with no arguments, which then blocks and waits for user input. How do we exit early? Type Ctrl+C (Windows or macOS keyboard).

```text
learncli$ cat
^C
learncli$
```

Ctrl+C sends the terminate signal SIGINT to the current process running in the foreground. Occasionally, this may not work, and you should also try Ctrl+D, which sends an EOF (end-of-file) character. For example, Ctrl+D can be used to exit the Docker container.

## Part 1: Lower

Go into the directory named `1-lower` (using `cd`).

A recent Reddit thread you made regarding code style has caused a heated debate online. After spending 30 minutes reading many all-caps comments, your eyes are strained. Rather than leave the debate unfinished, you decided to write a new C program in a file named `lower.c` that converts all characters from the standard input to lowercase. For example,

```text
learncli$ gcc lower.c -o lower
learncli$ ./lower
TAR HEELS
tar heels
learncli$ 
```

**Note**: In the above, the user typed "TAR HEELS" and pressed enter, and then "tar heels" was printed. At that point, the program was still running. The user then typed Ctrl+D to send an EOF, which ended the program.

Non-alphabetical characters (such as digits and punctuation) should be preserved in the output.

*Hint: Please do not write 26 `if` statements. Think about how to use ASCII codes to your advantage, and remember that the `char` type can be treated like an unsigned number (similar to `int`, `short`, etc.).*

### Testing

Some test inputs and outputs are included for you to test your program. Instead of running the program and manually typing the input yourself, you should test your program by running (in directory `1-lower`)

```text
learncli$ ./lower < test0.txt > myresult.txt
learncli$ diff myresult.txt test0-result.txt
```

The first command runs the `lower` program with its input and output streams redirected. Programs always have two primary streams open: standard input (stdin) and standard output (stdout). Normally, stdin and stdout are both your terminal. That is, your keyboard is the input, and the screen is the output. The `<` operator redirects stdin to the file `test0.txt`. It is as if we had run `./lower` and typed the contents of `test0.txt` ourselves. The `>` operator redirects stdout to the file `myresult.txt`. With redirection, the output that would normally be printed in the terminal is instead written to `myresult.txt` (if the file doesn't exist, it is created; otherwise, the file is overwritten).

The second command runs the `diff` program on `myresult` and `test0-result.txt`, which shows any differences between the output from your program and the correct output. If nothing prints after running `diff`, then your output matches the expected output.

Recall that when we ran the program with `./lower` and manually typed the input, we had to specify in the **Note** which strings were input and which were output (because in the terminal, input and output strings are indistinguishable). We also had to specify behavior regarding newlines and EOF. However, when running the program with redirection, these specifications become unnecessary.

### Pipe

In the first command above, we used `./lower < test0.txt` to send input from a file to the program. This is equivalent to `cat test0.txt | ./lower`. Try it!

Notice that we used the pipe operator `|` instead of a `<` redirection operator. Note the fundamental difference between the two operators. `<` expects a program and a file, whereas `|` expects two programs. `|` connects the stdout of the program on the left to the stdin of the program on the right. For example, the standard output of `cat test0.txt` is the contents of `test0.txt`, which is sent to the stdin of the `lower` program. This is exactly what occurs when running the command with `<`. Thus, `|` can be used to emulate `<`. However, `|` can be considered more powerful because it allows us to **compose** programs.

## Part 2: I/O redirection and piping

In this part, you'll apply and compose the operators `>`, `<`, and `|` that were discussed above.

### Task 0: Setup

To learn more about redirection and piping, including more code examples, read the section "Connecting programs" in the page [Course overview + the shell](https://missing.csail.mit.edu/2020/course-shell/). Then, for a more formal description of stdin, stdout, and stderr (such as the fact that the three are actually files), read the first section of this [page](https://sites.ualberta.ca/dept/chemeng/AIX-43/share/man/info/C/a_doc_lib/aixuser/usrosdev/std_input_output.htm). If necessary, this page also has plenty more code examples and other (optional) information.

In the directory `2-bash`, you'll find some `.sh` files, which are shell scripts. These are written in the same language as that of your terminal. For example, you can type and use `ls`, `grep`, `cat`, etc., just like in your terminal. You can run a shell script with `./<filename>.sh`, as with the `learncli.sh` script (if using macOS or Linux) or the `learncli.ps1` script (if using Windows). When running a script, if you encounter a "permission denied" error, use `chmod u+x <file>` to make it executable for the owner of the file.

We are writing our shell scripts in Bash. Bash is the Unix shell you are currently using (check with `echo $SHELL`), and Bash is also considered a language when written in a script. At the top of each `.sh` file, you'll see the Bash shebang `#!/bin/bash`, which tells the shell to interpret the commands as Bash commands.

### Task 1: Redirection

Recall that we used the following two commands to test our `lower` program.

```text
learncli$ ./lower < test0.txt > myresult.txt
learncli$ diff myresult.txt test0-result.txt
```

In `redirection.sh`, write a *one-line* command that accomplishes the same as the above. Do not add a newline at the end of the file; there should be only one newline. You may not use `;`, `&&`, or `||` to run multiple commands on a single line, though anything else is allowed.

It should work like so:

```text
learncli$ pwd  # current working directory is 1-lower when running script
/mnt/learncli/workdir/lab-1-template/1-lower
learncli$ ../2-bash/redirection.sh  # program output and test0-result.txt match, diff will print nothing
learncli$ echo "wrong result" >> test0-result.txt  # append text to test0-result.txt
learncli$ ../2-bash/redirection.sh  # program output and test0-result.txt do not match, diff will be shown
1a2
> wrong result
```

This script requires 3 file paths, and we will use relative file paths. These are relative to the current working directory, so the current working directory matters when running the script. As shown above, **when the autograder runs your script, its current working directory will be `1-lower`**. Thus, the 3 relative paths to use when writing the script are `lower`, `test0.txt`, and `test0-result.txt`. Your `lower` binary should still exist from the previous part, but if not, recompile with `gcc`. *Any other paths will not work in the autograder.*

To implement this, it would be logical to want to use a pipe, such as by running `./lower < test0.txt | diff test0-result.txt`. We know `diff` requires two inputs, so it would seem logical to provide 1. a file and 2. the output of `lower` via piping. However, run this and see the error message you get. Why does this approach not work?

An approach that solves this problem involves the `<()` operator, which is used like so: `<(COMMAND)`. This process substitution operator evaluates to a pseudo-file that contains the output of `COMMAND`.

For example,

```text
learncli$ cat <(ls)  # store ls output in pseudo-file and cat the file
redirection.sh
lower
test0-result.txt
test0.txt
learncli$ echo <(echo) # shows that <(COMMAND) evaluates to a pseudo-file
/dev/fd/63
```

The order of `diff`'s two operands matter. In your command, the first operand should be the output of `lower`, and the second operand should be `test0-result.txt`.

### Task 2: Pipe

Suppose we want to count the number of times we have used the `cd` command in our shell.

To do so, we will compose 3 commands using the pipe operator `|`: `cat`, `awk`, and `wc`. This should also be a *one-line* command, same as the previous command.

The strategy is to print our shell history, use `awk` to filter that to contain only the commands that begin with `cd`, and use `wc` to count the number of lines. Count only the commands that begin with `cd`. That is, assume the user would never use `cd` like so: `echo "" | cd`.

To print shell history, use `cat "$HISTFILE"`. You may use `tldr` to learn how to use `awk` and `wc` and which flags you may need. It may also be useful to test these commands on simple examples.

`pipe.sh` should behave like this (depending on how many times `cd` was used, of course):

```text
learncli$ cd lab-1-template/2-bash/
learncli$ ./pipe.sh
108
learncli$ cd ..
learncli$ cd -  # cd to previous directory
/mnt/learncli/workdir/lab-1-template/2-bash
learncli$ exit  # exit container to refresh $HISTFILE
exit
❯ ./learncli.sh  # use ./learncli.ps1 if on Windows
[+] Pulling 1/1
 ✔ comp211 Pulled                                                                                             0.5s
[+] Building 0.0s (0/0)
[+] Building 0.0s (0/0)



    ██╗   ██╗███╗   ██╗ ██████╗     ██████╗███████╗
    ██║   ██║████╗  ██║██╔════╝    ██╔════╝██╔════╝
    ██║   ██║██╔██╗ ██║██║         ██║     ███████╗
    ██║   ██║██║╚██╗██║██║         ██║     ╚════██║
    ╚██████╔╝██║ ╚████║╚██████╗    ╚██████╗███████║
     ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝     ╚═════╝╚══════╝



learncli$ cd lab-1-template/2-bash
learncli$ ./pipe.sh
111
```

Note that `$HISTFILE` does not change until you exit the container, so the container needs to be exited and re-entered to see a different number. Additionally, `$HISTFILE` looks different across shells, but as long as your command works for the `$HISTFILE` in the container, it should pass the autograder.

#### Usefulness

The pipe operator is useful for composing programs, as you can see. Its existence also makes it easier to write programs - because programs can be composed, each Unix program is written to do only one thing and do it well. Additionally, `awk`'s code does not need to know nor care that its input comes from `history` and its output goes to `wc` in our use case. Similarly, our `lower.c` and `truncator.c` are unaware whether their input comes from the user keyboard or a file. The code simply accepts input from stdin and outputs to stdout. If the user wants to change these, the user can redirect those streams, but the program does not have to written to be aware of this.

## Part 3: Truncator

Go into the directory `3-truncator`.

Your friend's monitor is too small and can display only up to 50 characters on a line before they run off the screen. They aren't good with computers, so you decide to write a C program in a file named `truncator.c` that reprints input so that no line is longer than 50 characters. Specifically, for lines less than or equal to 50 characters, simply reprint the line. For lines greater than 50 characters, insert a newline at each 50-character interval.

***Tip**: Write your own file with test input for the case where the 51st character is a newline. In the bottom-right corner of Vim, you can see the line and column number of your cursor and plan your 51-character input accordingly.*

Furthermore, to give developers feedback on their programs for 50-character-displays, you decide to add additional functionality to your program by displaying the line numbers of all lines over 50 characters long and the total number of these offending lines.

For example,

```text
learncli$ cat test0.txt
This line is under 50 characters long
This line is just over 50 characters long, you see?
This line is soooooooooooooooooo looooouoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong!
learncli$ ./truncator < test0.txt
This line is under 50 characters long
This line is just over 50 characters long, you see
?
This line is soooooooooooooooooo looooouoooooooooo
oooooooooooooooooooooooooooooooooooooooooooooooooo
oooooong!

Total lines over 50 chars: 2
Offending lines: 1, 2,
learncli$
```

### Notes

- The first line is the 0th line.
- Assume that none of the test input will contain over 100 illegal lines, so you can use an array of length 100 to store the line numbers.
- If the 51st character of a line in the input is a newline `\n`, then you should not print it (to avoid unnatural double newlines in the text). Depending on your solution, you may not need extra code for this, so worry about this case last.
    - If you think this may be causing issues, write your own file with test input for this case. In the bottom-right corner of vim, you can see the line and column number of your cursor and plan your 51-character input accordingly.
- There should be a newline `\n` after the reformatted output and a newline after the line that says "Offending lines..."
- The test input does not contain any tabs, which generally take up as much space as multiple characters.
- Windows uses [carriage return](https://www.easytechjunkie.com/what-is-carriage-return.htm), so if a new file is created in Windows, for each new line character, there will be a carriage return (`'\r'`) before it. Also, sometimes certain bad editors on Windows will insert carriage returns when editing or opening a file. This can be avoided by doing all work inside of the container, using the `dos2unix` command (after installing it with `apt install dos2unix`), or ignoring that character.

## Code style

You may have noticed the 2 style points in the autograder. Do not fret - these are easy to get. In your container, we provide a C autoformatter called [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) that you can use by running the alias `format-c <directory>`, where `directory` is the directory containing C files you want to format. You may also just run `format-c` without arguments to format all C files in the current directory. Lastly, inside Vim, you can press Space + c + f to format the current file (using a ClangFormat plugin for Vim).

We emphasize that formatting is only a small facet of code style. Although the formatting points are essentially free, they are there to remind you that code style is important. It is to your benefit to write code that is easy to understand and to avoid hardcoding, etc. You may read COMP 530's [Lab Style Guide](https://www.cs.unc.edu/~porter/courses/comp530/f22/style.html) for more facets of code style and examples of C code with good and bad style.

### Grading note

For C source files in all labs, if any libraries are included that weren't provided in the starter code or mentioned in the README, the autograder will assign no points to your submission. Additionally, we reserve the right to deduct points from the autograder if we notice that you have hardcoded any test cases and not actually fully implemented the program. Specifically for this lab, we may do so if your solution for `lower.c` uses 26 (or more) `if` statements. Anything egregious is subject to this policy. For any questions about this, ask your cohort leader.

## Submit your assignment

Submit the assignment to Gradescope the same way you did for Lab 0. Don't forget to add your PID and honor code to each `.c` file! Do not do so for the `.sh` files.

1. Navigate to the base folder of the repository within Docker using `cd`.
2. Type `git status`. You should see a list of changes that have been made to the repository.
3. Type `git add -A`. This signals that you want to place all modified / new files on the "stage" so that their changes can take effect.
4. Type `git commit -m "Your Message Here"`. This shows that you are "committing" to the changes you put on the stage. Instead of Your Message Here, you should write a meaningful message about what changes you have made.
5. Type `git push`. This takes the commit that was made locally on your machine and "pushes" it to GitHub. Now, when you view this repository on GitHub you should be able to see the changes you've made, namely the addition of your source files!
6. Go to the COMP 211 course in Gradescope and click on the assignment called **Lab 01**.
7. Click on the option to **Submit Assignment** and choose GitHub as the submission method.
8. You should see a list of your public repositories. Select the one named **COMP211-SP24/lab01-yourname** and submit it.
9. Your assignment should be autograded within a few seconds and you will receive feedback for the autograded portion.
10. If you receive all the autograder points, then you have completed this lab! Otherwise, you are free to keep pushing commits to your GitHub repository and submit for regrading up until the deadline of the lab.
