#ifndef FRAMES_H
#define FRAMES_H

#include <stddef.h>

#define MAX_FRAMES 100
#define MAX_FRAME_SIZE 1024
#define COLORS_COUNT 7
#define FRAME_DELAY 100000

extern const char *COLORS[COLORS_COUNT];
extern const char *COLORS[];
extern char **original_frames;
extern char **flipped_frames;
extern int frame_count;

void load_frames();
int select_color(int previous_color);
void stream_frames(int flip);

#endif // FRAMES_H