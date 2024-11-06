# FileSystem simulator
[![Points badge](../../blob/badges/.github/badges/points.svg)](../../actions)

## Objective:
This project is meant to provide you with hands-on experience on implementation
of trees. In particular, you will be implementing a file system simulator. Files
and directories will be represented by nodes forming a binary tree.

## Learning Outcomes:
Develop a program that uses:

- Trees

## Preparation:
To complete this project, you need to make sure that you have read the following:

- Strings
- Array and Vector Basics
- Objects and Classes Basics
- Modular Design and Makefiles
- Memory Management
- Recursion
- Trees

## Problem Description:

This project implements a simulator for a Linux file system. A file system
consists of files and directories. The top directory is the root. A directory
in the file system may contain other files and directories.

Since a single directory may contain a variable number of files and directories,
there are multiple options for representing a file system. One option is to
build a tree where each node of the tree is a file or directory, where each
directory could have links to children (other files and directories).

Using a vector for children then allows for an arbitrary number of children.
You can see this type of structure in 17.2 of your Zybook.

For simplicity, we will use the same node structure for files and directories.
Nodes will contain an indicator (a character) to indicate whether the node is a
file (f) or a directory (d). Additionally, a node will maintain a pointer to its
parent for easy reference to the parent from the child.

Using this structure, we will simulate a number of Linux commands that interact
with this (simulated) file system. The commands that are supported are the
following:

```bash
ls                    # lists all files and directories in the current directory.
mkdir <dirname>       # creates a new directory within the current directory if it does not already exist
cd <dirname>          # changes the current working directory to the given dirname.
                      # We will assume that dirname, if exists, should be located in the current working directory.
                      # Also "cd .." changes to the parent directory.
pwd                   # prints the current working directory. ex;  /root/nextdir/etc
touch <filename>      # adds a file to the current directory
mv <fname1> <fname2>  # change the name of the file or directory to the specified file/directory name
                      # unlike in linux, this command is a simple rename and should not actually move anything
rm <filename/dirname> # locate and remove the file or directory.
                      # If the directory has files/directories inside, they also need to be removed (similar to the `-r` flag in linux.
                      # note that we will assume that the file or directory to remove is within the current directory
exit                  # ends the session
```

Error checking is required for this assignment. For example, you should not
create a file or a directory with a name that already exists in the current
directory. You should not switch to a directory that does not exist. The root
has no parent, and therefore, you should not switch to the parent directory if
you are currently in the root.

The data structure will be available in the background and will grow as we add
subdirectories and files, or shrink as we remove them. However, real files and
directories are not going to be created on your computer (hence, why we say this
is simulated).

## Overview of the Interface:

Once the program is started, a root node is automatically created with the name
/root. The user is given a "$" prompt just like a Linux Terminal. The user can
then type the commands. Your terminal should provide error messages when
incorrect commands are entered (refer to the test suite files in [test/](test/)
to see what these error messages should be). The following sample run will
demonstrate these commands.

### Sample run of program

Takes a second or so to start.
You can ignore the cd command.

![Sample execution of program](demo.gif)

## Code Organization:

You will need to make sure that your code meets the following specifications.
Note that there is some room for interpretation, but a general code outline is
given below.

### The Main File
The main file will create an instance of the terminal and start up the program.

### The Node class
![UML of Node class](http://www.plantuml.com/plantuml/png/XP5DYiCm38NtFeMMdf-vG1Y6mEp3BEO2RYpSW6C7MmsKqhjNjgbhsfJkfFUaJm-xZwG27MOhHgjYXC5hX9FuWd6l0j1nGQuZwQwB52PdmAcvIYkEvCDtsdd_uOt9we2EtQp0ehWZ8JvoB-yfdxSRRzUPLAn-qg2q_aqyML2P_MY-GEwyjn1mzYjkprTYHFhBQMKRlRN_cIahlNK61csI2yeWFJs-yOnrdWF8Xb839YtdC2LK5bgsAP5OFuiUdURFlG00)

```
class Node {
- char type
- std::string name
- std::vector<Node*> children
- Node* parent

+ Node(std::string name, char type)
+ Node()
+ void addChild(Node* child)
+ void addChild(std::string name, char type)
+ bool removeChild(std::string name)
+ void setParent(Node* parent)
+ void setType(char type)
+ void setName(std::string name)
+ Node* getChild(std::string name)
+ std::vector<Node*> getChildren()
+ Node* getParent()
+ char getType()
+ std::string getName()
}
```

- This class class represents a file or directory within the file system.
- Each node contains information for the name of the file or directory, the type
  ('**f**' for file and '**d**' for directory), and information on a node's
  children and parent.
- The methods provided allow you to modify each of these values or to retrieve
  values based on the name of a file or directory.
- Note, that `getChildren` allows you to retrieve all the children that a node
  has.

Special attention should be paid to `removeChild` and `removeHelper`.
`removeChild` finds a child based on the name and removes it from the vector of
children, however, before it can be erased, you need to take care of any
children that it has. Notice that we are talking about removing the children of
a child node, and that those can in turn also have children. This means that the
removal must be done recursively. `removeHelper` is a recursive method that you
will use to recursively remove children during a delete.

### The FileSystem Class
![UML of FileSystem class](http://www.plantuml.com/plantuml/png/XOuzpi8m44Hxdy9bylrS85KAH4d32Iol0nPU6-skWo84PoSeKfGuHShnl7dUbiMGP0pA1iEiZpwuyy3YK3_LlpubSFg7Kf8vs4paeXmyEIk9Xh7eamTj0Bv0DL7rp7S-JWKBD0qB-NZHqQ2hbVfT_5VLOtmNURd16tZQMWfAKhRNNUh-W8q_yEQ9SDU4_GhfAE5VSL0viR2QWAT9_5AjYv0nV000)

```
class FileSystem {
- Node *root
- Node *currentDirectory
- void addNode(Node *)
- Node *findNode(std::string name)

+ FileSystem()
+ ~FileSystem()
+ std::string mkdir(std::string name)
+ std::string touch(std::string name)
+ std::string pwd()
+ std::string ls()
+ std::string rm(std::string name)
+ std::string mv(std::string from, std::string to)
+ std::string cd(std::string dirname)
}
```

This class is responsible for storing the filesystem and carrying out the
commands that manipulate it from the terminal. The majority of the methods shown
in this UML are described in the table above. The string return values are what
should be printed to the screen as a result of carrying out the operation. For
the two helper methods:

* `addNode()`
  * Adds a new file or directory within the current directory (can be used by
    `mkdir` and `touch`).

* `findNode()`
  * Looks for the file or directory within the current directory and returns it
    if it exists.

### The Terminal Class
![UML of Terminal class](http://www.plantuml.com/plantuml/png/SoWkIImgAStDuKhEIImkLWX9BShDp4lCKQZcqbLmoyn93QuiBadDLKWhvkBIXijgQ08vPVcPAGf5fNb0JYsNGsfU2j0K0000)

```
class Terminal {
- FileSystem fs
+ Terminal()
+ void run()
}
```

The responsibility of this class is to interact with the user. It takes in
commands and user input and calls the corresponding methods on the
**FileSystem** to get the results.

## Implementation Notes:

Your application must function as described below:

1. Create a project that is object oriented, therefore there should be several
   classes.
1. Your program must adhere to the class diagrams provided in this description.
1. You must use the data structures listed in this description for building your
   file system. Inappropriate use of other data structures or using data
   structures ways not discussed in this description can result in a large
   deduction of points.
1. **You must implement the removal recursively.**
1. Your program must compile and pass a tests listed above.

    - This application must be compiled by running `make main` and shall create
        an executable file called `main`.
    - All tests must pass by running together with `make test-all`. You can run
        individual test during development.
    - You can test sample run using `make test-run`

1. You classes must be memory leak free. Memory leakage will be checked and
   graded in autograding.

## Important Notes:

- Projects will be graded on whether they correctly solve the problem, and
  whether they adhere to good programming practices.
- Projects must be received by the time specified on the due date. Projects
  received after that time will get a grade of zero.
- Do not change the test files! The results you get will be pointless as they
  will not align with our grading.
- Please review the academic honesty policy.
  - Note that viewing another student's solution, whether in whole or in part,
    is considered academic dishonesty.
  - Also note that submitting code obtained through the Internet or other
    sources, whether in whole or in part, is considered academic dishonesty.
    **All programs submitted will be reviewed for evidence of academic
    dishonesty, and all violations will be handled accordingly**.

## Submission Requirements:
1. All code must be added and committed to your local git repository.
2. All code must be pushed to the GitHub repository created when you "accepted"
   the assignment.
    1. After pushing, with `git push origin main`, visit the web URL of your
       repository to verify that your code is there. If you don't see the code
       there, then we can't see it either.
3. Your code must compile and run. The auto-grading tests will indicate your
   score for your submission.
    1. The auto-grading build should begin automatically when you push your code
       to GitHub.
    2. If your program will not compile, the graders will not be responsible for
       trying to test it.
    3. You should get an email regarding the status of your build, if it does
       not pass, keep trying.

## Grading Information:
- Breakdown
    + 80% GitHub Auto-grading
    + 10% Coding style (naming convention, neatness of code, etc)
    + 10% Code organization (modular design, separate files, headers, etc.)
- Auto-grading results can be checked at the top of this document like as a
  badge ***40/80***.
- View details:
    1. On your GitHub repo page, Click the :arrow_forward: **Actions** tab to
       see your graded results.
    1. If it isn't a green check mark (:heavy_check_mark:) then at least part of
       the testing failed.
    1. Click the commit message for the failing version then click "Autograding"
       on the left side of the page.
    1. Follow the :x: path and expand things to see what errors exist.
    1. It is usually **education/autograding@v1** and you can expend this path to
       view the detail.
