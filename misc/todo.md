toml parser
    - should be easy to extract stuff from the config
      file

json builder
    - easily create json to pass to send via
      github api

cleaner curl
    - this needs to auth with github

cleaner way of concatenating strings (very very messy)
    - i can probably use variadic functions

features    
    - publish: something to github
        - set where to publish, i.e. organisation/user
        - publish privately
        - set github description
    - update: this will redownload all of the deps
    - build: compiles the project
    - run: compiles and runs the project
    - test: runs tests