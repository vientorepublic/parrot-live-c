#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "frames.h"

#define FRAME_INTERVAL 70

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int flip = 0;
    if (argc > 1 && strcmp(argv[1], "flip") == 0) {
        flip = 1;
    }

    original_frames = NULL;
    flipped_frames = NULL;

    original_frames = malloc(MAX_FRAMES * sizeof(char *));
    flipped_frames = malloc(MAX_FRAMES * sizeof(char *));
    if (original_frames == NULL || flipped_frames == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for frames.\n");
        return EXIT_FAILURE;
    }

    load_frames();

    if (original_frames == NULL || flipped_frames == NULL || frame_count == 0) {
        fprintf(stderr, "Error: Failed to load frames.\n");
        free(original_frames);
        free(flipped_frames);
        return EXIT_FAILURE;
    }

    stream_frames(flip);

    if (original_frames != NULL && flipped_frames != NULL) {
        for (int i = 0; i < frame_count; i++) {
            if (original_frames[i] != NULL) {
                free(original_frames[i]);
            }
            if (flipped_frames[i] != NULL) {
                free(flipped_frames[i]);
            }
        }
        free(original_frames);
        free(flipped_frames);
    }

    return 0;
}