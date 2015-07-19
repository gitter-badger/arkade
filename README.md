## Arkade  ![Travis status](https://travis-ci.org/ark-lang/arkade.svg?branch=master)

[![Join the chat at https://gitter.im/ark-lang/arkade](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/ark-lang/arkade?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
A package manager for Ark. It includes a hand-written TOML parser,
which will eventually be its own project (and written in Ark).

## Requirements
* GNU Make
* A C compiler like Clang or GCC
* Curl

## Building

```bash
$ git clone https://www.github.com:ark-lang/arkade
$ cd arkade
$ make
```

It is recommended that you place `arkade` somethwhere in your `$PATH`. For example, to add `arkade` to your path for your current terminal session:

```bash
$ export PATH=$PATH:~/path/to/arkade/bin
```

## Using
Note that we assume you have arkade added to your `$PATH`.

### Makefile
If you are using gcc instead of clang, make sure you change `CC` in the Makefile from `CC = clang` to `CC = gcc`
<sup>or better yet, install clang ;)</sup>

### Initial Setup
Arkade works alongside GitHub, you need to generate a token key that it can use to create repositories, etc. on your 
account. GitHub has a good [article on this](https://help.github.com/articles/creating-an-access-token-for-command-line-use/). Once you have acquired your token, you need to set this up with Arkade. To do so, you use the login command followed by the token you have just created:

```bash
$ arkade login a50f1f263819f9609fa9aab845d2b336a543c0be
```

This will create a configuration file in `~/.arkade/config.toml`, if this fails for some reason please report the bug on the issue handler, and in the mean time you can edit the config manually:

```toml
[config]
token = "a50f1f263819f9609fa9aab845d2b336a543c0be"
```

After this is all done, you should be ready to roll.

### Creating an Arkade project
To create an arkade project, you use the new command:

```bash
$ arkade new name
$ cd name
```

This will create a directory name, with all the necessary files and directories that Arkade needs to work correctly. Note it will also initialize a Git repository. You will also need to setup the minimum requirements in the configuration file. It should include (at minimum) the name of the project, you can also give a few extra keys:

_todo make this a table with examples:_

* name
* version
* verbose
* website
* desc
* private

### Downloading dependencies
If your project has any dependencies, you can specify them in your `arkade.toml` file under the `[dependencies]` directory, in a format like the one given below.

```toml
[dependencies]

custom_dependency_name = [ "url_to_github_repo_of_dependency", "version" ]
```
This causes Arkade to download the given dependency into a folder with the same name as `custom_dependency_name`, inside the `_deps` directory. As of right now, Arkade can only fetch dependencies from GitHub. You can specify multiple dependencies, as well as the version that you want. And that's it!

### Publishing an Arkade project
Once you've written up your project and you want to publish it, you use the publish command. Currently, this will publish the repository to your GitHub. Eventually, this will take an argument (major|minor|patch) and it will create a patch and a release on your GitHub repository accordingly.

```bash
$ arkade publish
```

And that's it!

## License
This project is licensed under the [MIT](/LICENSE) license.
