#ifdef EMSCRIPTEN
#include "emscripten.h"
#include "stdbool.h"

typedef void browser_sound;

// get the mime-type from the first bytes of a sound file
char* browser_sound_mime(unsigned char* bytesPtr);

// pull sound from bytes in memory
browser_sound* browser_sound_load_from_memory(unsigned char* bytes, int byteSize);

// pull sound from a URL
browser_sound* browser_sound_load_from_url(char* url);

// play a sound
void browser_sound_play(browser_sound* sound);

// stop a sound
void browser_sound_stop(browser_sound* sound);

// pause a sound
void browser_sound_pause(browser_sound* sound) {}

// seek to a specific position
void browser_sound_seek(browser_sound* sound, int position);

// enable/disable looping
void browser_sound_loop(browser_sound* sound, bool loop);

// set a sound's volume
void browser_sound_volume(browser_sound* sound, float volume);

// get the volume of a sound
float browser_sound_get_volume(browser_sound* sound);

// get the seek-position of a sound
int browser_sound_get_position(browser_sound* sound);


EM_JS(char*, browser_sound_mime, (unsigned char* bytesPtr), {
  printf("browser_sound_mime: not implemented\n");

  return NULL;
});


EM_JS(browser_sound*, browser_sound_load_from_memory, (unsigned char* bytesPtr, int byteSize), {
  Module.browser_sounds = Module.browser_sounds || [];
  const mimeType = Module._browser_sound_mime(bytesPtr);
  const a = new Audio();
  a.src = URL.createObjectURL(new Blob([HEAPU8.subarray(bytesPtr, bytesPtr+byteSize)]));
  Module.browser_sounds.push(a);
  return Module.browser_sounds.length - 1;
});

EM_JS(browser_sound*, browser_sound_load_from_url, (char* UrlPtr), {
  Module.browser_sounds = Module.browser_sounds || [];
  const a = new Audio();
  a.src = UTF8ToString(UrlPtr);
  Module.browser_sounds.push(a);
  return Module.browser_sounds.length - 1;
});

EM_JS(void, browser_sound_play, (browser_sound* sound), {
  if (Module.browser_sounds && Module.browser_sounds[sound]) {
    Module.browser_sounds[sound].play();
  }
});

EM_JS(void, browser_sound_stop, (browser_sound* sound), {
  if (Module.browser_sounds && Module.browser_sounds[sound]) {
    Module.browser_sounds[sound].pause();
    Module.browser_sounds[sound].currentTime = 0
  }
});

EM_JS(void, browser_sound_pause, (browser_sound* sound), {
  if (Module.browser_sounds && Module.browser_sounds[sound]) {
    Module.browser_sounds[sound].pause();
  }
});

EM_JS(void, browser_sound_seek, (browser_sound* sound, int position), {
  if (Module.browser_sounds && Module.browser_sounds[sound]) {
    Module.browser_sounds[sound].currentTime = position;
  }
});

EM_JS(void, browser_sound_loop, (browser_sound* sound, bool loop), {
  if (Module.browser_sounds && Module.browser_sounds[sound]) {
    Module.browser_sounds[sound].loop = !!loop;
  }
});

EM_JS(void, browser_sound_volume, (browser_sound* sound, float volume), {
  if (Module.browser_sounds && Module.browser_sounds[sound]) {
    Module.browser_sounds[sound].volume = volume;
  }
});

EM_JS(float, browser_sound_get_volume, (browser_sound* sound), {
  if (Module.browser_sounds && Module.browser_sounds[sound]) {
    return Module.browser_sounds[sound].volume;
  }
  return -1;
});

EM_JS(int, browser_sound_get_position, (browser_sound* sound), {
  if (Module.browser_sounds && Module.browser_sounds[sound]) {
    return Module.browser_sounds[sound].currentTime;
  }
  return -1;
});

#else
#error "Emscripten must be available for browser_sound to work."
#endif  // EMSCRIPTEN