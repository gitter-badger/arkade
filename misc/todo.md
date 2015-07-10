toml parser
    - should be easy to extract stuff from the config
      file

json builder
    - easily create json to pass to send via
      github api

cleaner curl
    - this needs to auth with github
    - i dont think github allows ssh so it will
      have to use auth tokens or raw login details
      perhaps support for both would be good

cleaner way of concatenating strings (very very messy)
    - i can probably use variadic functions

publish:
    publish should probably create a tag and a release
    for the version specified in the configuration file?

features    
    - publish: something to github
        - set where to publish, i.e. organisation/user
        - publish privately
        - set github description
    - update: this will redownload all of the deps
    - build: compiles the project
    - run: compiles and runs the project
    - test: runs tests

    [project]
    name = "Name"
    version = "0.0.1"
    authors = [
        "Full Name <email@address.tld>"
        "Full Name <email@address.tld>"
    ]

    [dependencies]
    // note that I've given it an alias,
    // this means in ark code it's used as

        dependency mysql;                       

    // and a version is specified
    mysql = [
        "github.com/mysql/lib-mysql", 
        "5.6.25"
    ]
    // optional formatting, i like the one below
    mysql = ["github.com/mysql/lib-mysql", "5.6.25"]
