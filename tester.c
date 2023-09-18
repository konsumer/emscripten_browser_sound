// this is a simple test of the lib

#include "browser_sound.h"
#include "stdio.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  printf("loading sound: %s\n", argv[1]);

  browser_sound* sound = browser_sound_load_from_url(argv[1]);
  browser_sound_loop(sound, true);
  browser_sound_play(sound);
}