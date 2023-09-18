This is a simple example of emscripten exposing a couple functions to C, from JS, in mjs-mode. You could add `browser_sound.h` your project, and it should work to manage sounds.

It's an extremely light way to play sounds, if you are using emscripten.

```
# build it
make

# test it
make web
```