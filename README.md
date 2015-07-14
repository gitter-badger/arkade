## Arkade
A package manager for Ark. It includes a hand-written TOML parser,
which will eventually be its own project (and written in Ark).

## Requirements
* CMake
* GNU Make
* A C compiler like Clang or GCC
* Curl

## Warning
This is a prototype-ish, it's very messy.

The TOML parser is written by me. It **doesn't** support UTF-8 and it probably won't until it is re-written in Ark.

## Why are we writing this in C?
We're planning to write Arkade package manager *in* Ark, but, because the language doesn't work well enough to suit the needs of a package manager yet, we're using C.

It is also easier to convert C to Ark than, for example, Go to Ark. We are also writing
most of the utilities we need for this, e.g. a TOML parser, JSON builder, etc. from scratch.
This will also make the port a lot more easier, since we won't have to port any huge libraries
over (e.g. a TOML parser that uses some huge parser/lexer generator), and this will keep the package manager more lightweight.

## Building

```bash
$ git clone git@github.com:ark-lang/arkade
$ cd arkade
$ cmake CMakeLists.txt
$ make
```

It is recommended that you place `arkade` somethwhere in your `$PATH`. For example, to add `arkade` to your path for your current terminal session:
```
$ export PATH=$PATH:~/path/to/arkade/bin
```

## Using
```
$ arkade new project_name
$ cd project_name
$ arkade build
```

## License
[MIT](/LICENSE)
