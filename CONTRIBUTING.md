# Contributing
We recommend that you read this document over if you are interested in
contributing to Arkade.

## Style Guide
Arkade is written in C, to keep things portable, compatible, and easy
to read, we need to maintain a consistent code style. 

### Brace Style
The first brace should be on the same line as the declaration:

    int main() { // good!

    }

### Naming Style
We use snake case for variables, functions, and structures. Constants
and macros should be in capital snake case:

    int hi_there = 10;
    #define BREAD_SIZE "big"
    const int NUM_OF_BREADS = 21;

We also suffix structures with `_t`, this makes usage more obvious in
combination with the naming style:

    // good
    typedef struct {

    } lexer_t;

    ... {
        lexer_t *lexer = ...
    }

    // bad
    typedef struct {

    } lexer;

    ... {
        lexer *lexer = ... // what?
    }

### Miscellaneous
Arkade runs with _all_ compilation warnings, we try to make sure there
are no warnings whatsoever before merging with the repository. Make
sure you have your text editor insert a newline at EOF, 4 spaces in a
tab is a must.

## How do I contribute?
There are a few ways to contribute:

### Sending Pull Requests
One of the best ways to help would be sending pull requests, i.e.
contributing to the code or the documentation, etc. You will --
most likely -- find some bugs/features in the issue handler that
you can implement and send a PR! Please note that when you do
send a PR, we would appreciate if you rebase on master before
submitting.

### Finding Bugs
If you find a bug, report it in the issue handler! Try and give
as much information as possible, including a descriptive (but concise)
title, and a description that contains at the minimum:

* a summary of the bug
* include any logs, make sure you run in verbose mode (set `verbose =
true in your project configuration file)
* how we could reproduce the issue (if it's not obvious)

Before posting your issue, ensure that it has not already been reported
before. It might be tricky to find a duplicate, so if you are unsure 
submit it anyway and the developers will close it if it's an issue, and
they should also link the issue it is duplicating.

### Issues
Being active on the issues is a great help, commenting on issues with
ideas on the problem, giving your feedback on a particular RFC (request
for comment), or helping others in the comments is always appreciated.
