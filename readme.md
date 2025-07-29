# Slime Frenzy

## macOS build

The Makefile needs a lot of work. In the meantime...

### Open a Terminal window

&lt;Command&gt;&lt;Space&gt;Terminal&lt;Enter&gt;

### Install raylib using Homebrew:

If you don't have Homebrew installed already, [download the latest release](https://github.com/Homebrew/brew/releases/) (look for the .pkg file) and install it.

From the terminal prompt, type:
```brew install raylib```

### Compile and run SlimeFrenzy

Run the command:
```
clang++ -std=c++11 -Wall -I/opt/homebrew/include -L/opt/homebrew/lib \
  gameWindow.cpp -lraylib -framework OpenGL -framework OpenAL \
  -framework Cocoa -framework IOKit -o SlimeFrenzy
```

Then, run the compiled binary:

`./SlimeFrenzy`
