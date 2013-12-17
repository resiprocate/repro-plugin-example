

To checkout and build this project:

  git clone https://github.com/resiprocate/repro-plugin-example.git
  cd repro-plugin-example
  cmake .
  make

Using this as a skeleton for building your own plugin module project:

  Fork the project in github

  Clone your fork (git clone ...)

  Replace the word Example in all the code, rename the source file:

    sed -i -e 's/example/something/g' *
    sed -i -e 's/Example/Something/g' *
    git mv ExamplePlugin.cxx SomethingPlugin.cxx
    commit -m 'Adapt from Example to Something'

  Now insert your own code in the SomethingPlugin::process(...) method


Copyright (C) 2013 Daniel Pocock http://danielpocock.com

