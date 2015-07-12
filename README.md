## Arkade
The package manager for Ark.

## Requirements
* CMake
* GNU Make
* A C compiler like Clang or GCC
* Curl

## Warning
This is a prototype-ish, it's very messy.

The TOML parser is written by me, and it **doesn't** support UTF-8 and it probably won't till it is re-written in Ark.

## Why are we writing this in C?
We're planning to write the package manager *in* Ark, but, because the language doesn't work good enough yet to suit the needs of a package manager, we're using C.

It is also easier to convert C to Ark than for example Go to Ark. We are also writing
most of the utilities we need for this, e.g. a TOML parser, JSON builder, etc. from scratch.
This will also make the port a lot more easier, since we wont have to port any huge libraries
over (e.g. a TOML parser that uses some huge parser/lexer generator), and this will keep the package manager more lightweight.

## Building

```bash
$ git clone git@github.com:ark-lang/arkade
$ cd arkade
$ cmake CMakeLists.txt
$ make
$ export PATH=$PATH:~/path/to/arkade/bin
$ arkade new project_name # create a new project
```

## License
[MIT](/LICENSE)