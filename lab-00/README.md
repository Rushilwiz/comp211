<!-- omit in toc -->
# Lab 00

<details open>
    <summary>Contents</summary>

- [Part 0. Setup](#part-0-setup)
    - [Set up your environment](#set-up-your-environment)
    - [Learn the CLI](#learn-the-cli)
    - [Learn Vim](#learn-vim)
    - [workdir](#workdir)
    - [Setting up SSH authentication](#setting-up-ssh-authentication)
        - [Locally](#locally)
        - [GitHub](#github)
- [Part 1. Hello World](#part-1-hello-world)
    - [`hello.c` requirements](#helloc-requirements)
    - [Compiling and executing](#compiling-and-executing)
- [Submit your assignment](#submit-your-assignment)
- [Check your understanding](#check-your-understanding)

</details>

## Part 0. Setup

### Set up your environment

To complete the labs for this course, you will need to learn how to work inside a Linux command-line interface. If you haven't already, please carefully read the [Linux Programming Environment](https://uncch.instructure.com/courses/48862/pages/linux-programming-environment) page on Canvas, and complete the Docker installation steps on your computer. Having everyone use the same Linux environment simplifies the coding and grading process.

### Learn the CLI

Read Chapters 1 and 2 of *Learn a Command-line Interface* by Kris Jordan: [The Sorcerer's Shell](https://uncch.instructure.com/users/9947/files/4534606?verifier=OtzqqS8AJ9vtBgYkQDnjzhdQCkb6fk4YT47bMMXA&wrap=1) and [Directories, Files, and Paths](https://uncch.instructure.com/users/9947/files/4534607?verifier=Ay7tjnpmx7Cdhg7TzNXg7zfPD6wbBhBJOy8NqWXK&wrap=1). This will teach you everything you need to know about running programs and navigating directories in your Linux environment. Make sure you practice running the commands in the environment! The shell will be your playground for the semester, so gain familiarity with it.

### Learn Vim

Vim is an extensible text-editor program that is included in most Linux systems. It is designed to make changing any kind of text very efficient, though it may not seem so at first. Start your Linux environment that you set up earlier and enter the `vimtutor` command. When you press enter, a tutorial document will be opened with `vim` explaining how to use it. If you touch-type and normally have your right hand in home row position (that is, index finger on J, middle finger on K, ring finger on L, and pinky on ;), then we recommend that you do so for vim use as well.

Most likely, you will not remember everything from the tutor. We recommend you just learn enough from `vimtutor` to be comfortable enough to complete Part 1 of the assignment in vim, then later you can go back to `vimtutor` or look at online guides to learn more as you go.

The following labs will assume that you are using vim, and we encourage you to take the opportunity to get a basic familiarity with vim during this class. A basic understanding can help you in later courses and in life, even outside of the domain of systems development.

The `vim` in your Docker image has been customized for the C programming language and may look different from `vim` on your home computer. Specifically, to view the customizations, run `vim ~/.vimrc` in your container. The commands in this file are automatically run every time the container is started. The `rc` at the end of the file name stands for "run commands". Another example of such a file is `~/.bashrc`, which contains, on lines 101-112, the `echo` commands that display the "UNC CS" ASCII art on startup.

### workdir

In case the environment is compromised, all files are in `learncli211/workdir` (relative path in your native file system). In the container, this directory is **m**ou**nt**ed at `/mnt/learncli/workdir` (absolute path).

When you run the start script (`learncli.ps1` or `learncli.sh`) and start the Docker image, Docker will create the `workdir` directory that is bridged between the image and your native operating system, where you can copy and move files between the two.

Running `exit` in the Docker container will exit that container.

### Setting up SSH authentication

In order to interact with GitHub from the command line, SSH authentication must be set up. This is a standard procedure and should only need to be done once. There is a nice [YouTube video](https://www.youtube.com/watch?v=1fR0BHzzgOI) created by Ryan Good (former 211 LA) that walks through the three steps provided below.

#### Locally

1. Navigate to the `learncli211` directory that contains the `learncli.sh` and `learncli.ps1`files, but do not execute them! This must be done outside of the container. If you are not sure whether or not you are in a container, then restart your terminal, and `cd` into `learncli211`.
2. Type `ssh-keygen`, type `.ssh/id_rsa` as the location to save the key, and press enter twice for no passphrase at the password prompt.

```text
$ ssh-keygen
Generating public/private rsa key pair.
Enter file in which to save the key (/home/root/.ssh/id_rsa): .ssh/id_rsa
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in .ssh/id_rsa.
Your public key has been saved in .ssh/id_rsa.pub.
The key fingerprint is:
SHA256:4yheFb7P2rzq/fJ71+AKPssyEQq7+bI0YcnK8+rzfr8 ceclia@topkek
The key's randomart image is:
+---[RSA 2048]----+
|                 |
|                 |
|        .        |
|   ... ...       |
|    =o .S.       |
| . o...+.o    .  |
|  + +oo o..  . ..|
|  .=++. oOo.  o o|
| .o=*=.oE*@B=+ . |
+----[SHA256]-----+
```

3. Inside of your `learncli211` folder, a folder called `.ssh` should now exist. Running `cat .ssh/id_rsa.pub` should output the needed key as text to the console, which you should copy for the next part. For the macOS Terminal, highlighting the key and then pressing `CTRL` + `C` should copy it; on Windows Terminal, you must highlight it and then *right-click* the highlighted text to copy it. If nothing is highlighted in Windows Terminal, a right-click will paste.

#### GitHub

1. Click your profile in the top right corner.
2. Click Settings -> SSH and GPG keys -> New SSH Key.
3. Paste the contents of `.ssh/id_rsa.pub` into the "Key" section.
4. Give it a title and click "Add SSH Key".

## Part 1. Hello World

After SSH authentication is set up, return to the container environment. Then, clone this Git repository within your container with the command `git clone <repository>`. In place of where `<repository>` is, you should enter the SSH-based URL of your repository; e.g. `git clone git@github.com:Comp211-SP24/lab-00-username.git`. You can get this URL by going to the GitHub page and clicking Code -> SSH.

In your repository, use `mkdir` to make a new directory named `0-hello-world`. Use `cd` to change your working directory to be this subdirectory. For reference on how to carry out either of these tasks, please refer to Chapter 2: [Directories, Files, and Paths](https://uncch.instructure.com/users/9947/files/4534607?verifier=Ay7tjnpmx7Cdhg7TzNXg7zfPD6wbBhBJOy8NqWXK&wrap=1).

Next, you’ll want to edit a new file named `hello.c`. To begin editing this file in vim, simply run the command:

```sh
vim hello.c
```

Each source file in COMP 211 will begin with the standard header comment below. The format of this header is checked by the autograder for an exact match. To avoid having the autograder fail, please ensure you:

- format your PID as a single 9-digit number with no spaces nor dashes, and
- your capitalization and punctuation of the honor code pledge are correct.

```c
// PID: 9DigitPidNoSpacesOrDashes
// I pledge the COMP 211 honor code.
```

Now refer to section 1.1 of *C Programming Language* to complete the rest of the assignment.

### `hello.c` requirements

The purpose of `hello.c` is to slightly extend the book's (*C Programming Language*) implementation of the same program on Page 9. Your implementation should print `Hello, world.` on one line and `Welcome to C!` on another line. This is case and punctuation-sensitive. It should then return `EXIT_SUCCESS`. To return `EXIT_SUCCESS`, you will need to import `stdlib.h`, the header file which defines this constant. When `main` returns `EXIT_SUCCESS`, it indicates the program completed successfully via a success exit status. We will explore the idea of exit statuses later this semester. Additionally, we expect all function return types to be defined, and `main` should return an `int`, a signed integer value.

### Compiling and executing

Compile and execute your program with the following shell commands:

```sh
gcc -Wall hello.c
./a.out
```

The `-Wall` flag tells `gcc` to print out all warnings.

Once your program compiles without warnings and meets the requirements, you should submit your assignment.

## Submit your assignment

Assignment submissions will be made through [Gradescope](https://www.gradescope.com).

You should already be enrolled in the COMP 211 course on Gradescope. If you are not, please self-enroll with entry code listed on the Canvas home page. If you're unable to self-enroll, please contact your cohort leader and we'll manually add you.

To submit your assignment, you must commit and push your work to this repository using git.

1. Navigate to the base folder of the repository within your container. Enter the command `ls` to confirm that it contains the directory named `0-hello-world`, and ensure that your `hello.c` file is in the `0-hello-world` directory.
2. Type `git status`. You should see a list of changes that have been made to the repository.
3. Type `git add -A`. This signals that you want to place all modified/new files on the "stage" so that their changes can take effect.
4. Type `git commit -m "Your Message Here"`. This shows that you are "committing" the changes you put on the stage. Instead of Your Message Here, you should write a meaningful message about what changes you have made.
5. Type `git push`. This takes the commit that was made locally on your machine and "pushes" it to GitHub. Now, when you view this repository on GitHub, you should be able to see the changes you've made.
6. Go to the COMP 211 course in Gradescope, and click on the assignment called **Lab 0**.
7. Click on the option to **Submit Assignment**, and choose GitHub as the submission method. You may be prompted to sign in to your GitHub account to grant access to Gradescope. If this occurs, **make sure to grant access to the Comp211-SP24 organization**.
8. You should see a list of your public repositories. Select the one named **lab-00-yourname** and submit it.
9. Your assignment should be autograded within a few seconds and you will receive feedback.
10. If you receive all the points, then you have completed this preliminary lab! Otherwise, you are free to keep pushing commits to your GitHub repository and submit for regrading up until the deadline of the lab.

## Check your understanding

The purpose of this lab is to make sure you have some basic familiarity with the tools of this course: your Ubuntu environment, vim, and git. You will earn full credit for this lab simply by submitting the short `hello.c` program, but it would be a good idea for you to spend some extra time learning the shell commands, vim keystrokes and understanding git. If you would like to learn more beyond what was included in the lab writeup, here are some additional resources created by Kris Jordan:

* [vim Tutorial - A beginner's guide to vim, a powerful text editor with a grammar.](https://www.youtube.com/playlist?list=PLKUb7MEve0Tj3MLYDIyYpIZtnJehmlR0s)
* [What is a version control system? What is git?](https://www.youtube.com/watch?v=h2xylPqXO8M&list=PLKUb7MEve0TjHQSKUWChAWyJPCpYMRovO&index=4)
* [git Fundamentals - add, commit, branch, checkout, merge](https://www.youtube.com/watch?v=R8E29zB8tMc&list=PLKUb7MEve0TjHQSKUWChAWyJPCpYMRovO&index=5)
