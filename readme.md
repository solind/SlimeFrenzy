# Slime Frenzy

## macOS build

The Makefile needs a lot of work. In the meantime...

Install raylib using homebrew:

```brew install raylib```

Then, run the command:

```
clang++ -std=c++11 -Wall -I/opt/homebrew/include -L/opt/homebrew/lib \
  gameWindow.cpp -lraylib -framework OpenGL -framework OpenAL \
  -framework Cocoa -framework IOKit -o SlimeFrenzy
```
