# Reference
This document serves as an informal overview of the Arkade package 
manager. It exists to give a brief overview of how to use the package 
manager, a birds-eye view on how it works, and planned features in the
package manager.

## Arkade
Arkade is a package manager primarily for the 
[Ark programming language](//github.com/ark-lang/ark), however it is built
so that it can be used with just about any language. Arkade (currently)
works with GitHub, this means that any package you create and publish
will be pushed to a GitHub repository. In the future, we will most likely
build a freestanding platform for projects.

### Configuration Files
Configuration files use TOML (Toms Obvious, Minimal Language), in which
the specification can be found [here](//github.com/toml-lang/toml). Every
project has it's own configuration file, as well as the package manager
itself. This can be found in your root directory under the `.arkade` folder,
which should contain a configuration file (`config.toml`) for the package
manager itself.

#### Arkade Configuration
Currently, the configuration for Arkade is very minimal. Arkade expects
_at least_ a GitHub token, and a GitHub username. Note that these settings
*should* not have to be set manually, the `arkade login` command exists
for this purpose.

Here is an example arkade configuration file:

```toml
[config]
github_username = "felixangell"
token = "da39a3ee5e6b4b0d3255bfef95601890afd80709"
```

```toml
# note this is subject to change
# probably to the following

[config]
# specify verbose for every project
verbose = true

[github]
# token
auth = [ "token", ["felixangell", "da39a3ee5e6b4b0d3255bfef95601890afd80709"] ]

# ssh
auth = [ "ssh", ["felixangell", "/path/to/id_rsa", "/path/to/id_rsa.pub"] ]
```

#### Project Configuration
