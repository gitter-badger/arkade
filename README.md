## arkade
The package manager for Ark

## requirements
Not much is required:

* CMake
* GNU Make
* Clang/GCC
* Git

## warning
This is a prototype-ish, it's very messy. Also, because of this
it probably only works on Unix/Linux based systems.

### also...
the TOML parser is written by me, and it **doesn't** support UTF-8
and it probably wont till it is re-written in Ark.

## building

```bash
$ git clone git@github.com:ark-lang/arkade
$ cd arkade
$ cmake CMakeLists.txt
$ make
$ export PATH=$PATH:~/path/to/arkade/bin
$ arkade new project_name # create a new project
```

## license
[MIT](/LICENSE)