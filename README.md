This is a simple example of emscripten exposing a couple functions to C, from JS, in mjs-mode. You could add `browser_sound.h` your project, and it should work to manage sounds.

It's an extremely light way to play sounds, if you are using emscripten.

```
# build it
make

# test it
make web
```

## TODO

- Test `browser_sound_mime` and `browser_sound_load_from_memory`
- Use [this technique](https://github.com/veltman/loopify/blob/master/loopify.js) to make gapless looping (AudioContext)
- Provide more AudioContext-related functions
