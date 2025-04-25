#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "frames.h"

char **allocate_frames() {
    char **frames = malloc(MAX_FRAMES * sizeof(char *));
    if (frames == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for frames.\n");
    }
    return frames;
}

void free_frames(char **frames, int count) {
    if (frames != NULL) {
        for (int i = 0; i < count; i++) {
            if (frames[i] != NULL) {
                free(frames[i]);
            }
        }
        free(frames);
    }
}

int handle_error(const char *message, char **frames1, char **frames2) {
    fprintf(stderr, "%s\n", message);
    free_frames(frames1, frame_count);
    free_frames(frames2, frame_count);
    return EXIT_FAILURE;
}

int main(int argc, char *argv[]) {
    int flip = 0;
    if (argc > 1 && strcmp(argv[1], "flip") == 0) {
        flip = 1;
    }

    load_frames(flip);
    stream_frames(flip);

    return 0;
}