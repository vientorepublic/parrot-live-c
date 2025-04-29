#include "frames.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "parrot_frames.h"

static char **original_frames = NULL;
static char **flipped_frames = NULL;

const char *COLORS[] = {
    "\033[31m",  // Red
    "\033[32m",  // Green
    "\033[33m",  // Yellow
    "\033[34m",  // Blue
    "\033[35m",  // Magenta
    "\033[36m",  // Cyan
    "\033[0m"    // Reset
};

int numeric_filename_comparator(const void *a, const void *b) {
  const char *file_a = *(const char **)a;
  const char *file_b = *(const char **)b;
  int num_a = atoi(file_a);
  int num_b = atoi(file_b);
  return num_a - num_b;
}

void load_frames(int flip) {
  if (original_frames) {
    for (int i = 0; i < FRAME_COUNT; i++) {
      free(original_frames[i]);
    }
    free(original_frames);
  }
  if (flipped_frames) {
    for (int i = 0; i < FRAME_COUNT; i++) {
      free(flipped_frames[i]);
    }
    free(flipped_frames);
  }

  original_frames = malloc(FRAME_COUNT * sizeof(char *));
  flipped_frames = malloc(FRAME_COUNT * sizeof(char *));

  unsigned char *frames[] = {
      frames_0_txt, frames_1_txt, frames_2_txt, frames_3_txt, frames_4_txt,
      frames_5_txt, frames_6_txt, frames_7_txt, frames_8_txt, frames_9_txt};
  size_t frame_sizes[] = {sizeof(frames_0_txt), sizeof(frames_1_txt),
                          sizeof(frames_2_txt), sizeof(frames_3_txt),
                          sizeof(frames_4_txt), sizeof(frames_5_txt),
                          sizeof(frames_6_txt), sizeof(frames_7_txt),
                          sizeof(frames_8_txt), sizeof(frames_9_txt)};

  for (int i = 0; i < FRAME_COUNT; i++) {
    original_frames[i] = malloc(frame_sizes[i] + 1);
    memcpy(original_frames[i], frames[i], frame_sizes[i]);
    original_frames[i][frame_sizes[i]] = '\0';

    if (flip) {
      flipped_frames[i] = malloc(frame_sizes[i] + 1);
      for (size_t j = 0; j < frame_sizes[i]; j++) {
        flipped_frames[i][j] = frames[i][frame_sizes[i] - j - 1];
      }
      flipped_frames[i][frame_sizes[i]] = '\0';
    } else {
      flipped_frames[i] = NULL;
    }
  }
}

char **get_original_frames() { return original_frames; }

char **get_flipped_frames() { return flipped_frames; }

int get_FRAME_COUNT() { return FRAME_COUNT; }

int select_color(int previous_color) {
  int color;
  do {
    color = rand() % COLORS_COUNT;
  } while (color == previous_color);
  return color;
}

void stream_frames(int flip) {
  int index = 0;
  int last_color = -1;

  while (1) {
    printf("\033[2J\033[3J\033[H");
    int new_color = select_color(last_color);
    printf("%s%s\033[0m", COLORS[new_color],
           flip ? flipped_frames[index] : original_frames[index]);
    fflush(stdout);
    index = (index + 1) % FRAME_COUNT;
    last_color = new_color;
    usleep(FRAME_DELAY);
  }
}