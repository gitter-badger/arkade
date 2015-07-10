## arkade
The package manager for Ark

## requirements
Not much is required:

* GNU Make
* Clang/GCC
* Git

## warning
This is a prototype-ish, it's very messy. Also, because of this
it probably only works on Unix/Linux based systems.

## building

```bash
$ git clone git@github.com:ark-lang/arkade
$ cd arkade
$ make
$ export PATH=$PATH:~/path/to/arkade/bin
$ arkade new project_name # create a new project
```

## license
[MIT](/LICENSE)