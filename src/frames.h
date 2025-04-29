#ifndef FRAMES_H
#define FRAMES_H

#include <stddef.h>

#define FRAME_COUNT 10
#define MAX_FRAMES 100
#define MAX_FRAME_SIZE 1024
#define COLORS_COUNT 7
#define FRAME_DELAY 70000

extern const char *COLORS[COLORS_COUNT];
extern const char *COLORS[];
static char **original_frames;
static char **flipped_frames;
static int frame_count;

void load_frames(int flip);
int select_color(int previous_color);
void stream_frames(int flip);

char **get_original_frames();
char **get_flipped_frames();
int get_frame_count();

#endif  // FRAMES_H