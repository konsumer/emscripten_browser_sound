docs/browser_sound.mjs: tester.c browser_sound.h
	emcc -O3 -o docs/browser_sound.mjs tester.c

web: docs/browser_sound.mjs
	emrun docs/index.html