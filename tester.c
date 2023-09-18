// this is a simple test of the lib

#include "browser_sound.h"
#include "stdio.h"

browser_sound* sound;

void print_info() {
  printf("Position: %f/%f\n", browser_sound_get_position(sound), browser_sound_get_duration(sound));
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  printf("loading sound: %s\n", argv[1]);

  sound = browser_sound_load_from_url(argv[1]);
  browser_sound_loop(sound, true);
  browser_sound_play(sound);

  printf("Volume: %f\n", browser_sound_get_volume(sound));

  emscripten_set_main_loop(print_info, 0, false);
  return 0;
}