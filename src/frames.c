#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "frames.h"

static char **original_frames = NULL;
static char **flipped_frames = NULL;
static int frame_count = 0;

const char *COLORS[] = {
    "\033[31m", // Red
    "\033[32m", // Green
    "\033[33m", // Yellow
    "\033[34m", // Blue
    "\033[35m", // Magenta
    "\033[36m", // Cyan
    "\033[0m"   // Reset
};

void load_frames() {
    struct dirent *entry;
    DIR *dp = opendir(FRAMES_PATH);
    if (dp == NULL) {
        perror("Error opening frames directory");
        return;
    }

    original_frames = malloc(MAX_FRAMES * sizeof(char *));
    flipped_frames = malloc(MAX_FRAMES * sizeof(char *));
    if (original_frames == NULL || flipped_frames == NULL) {
        perror("Error allocating memory for frame pointers");
        closedir(dp);
        return;
    }

    char *file_names[MAX_FRAMES];
    int file_count = 0;
    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_REG && file_count < MAX_FRAMES) {
            file_names[file_count] = strdup(entry->d_name);
            if (file_names[file_count] == NULL) {
                perror("Error duplicating file name");
                continue;
            }
            file_count++;
        }
    }
    closedir(dp);

    qsort(file_names, file_count, sizeof(char *), (int (*)(const void *, const void *))strcmp);

    for (int i = 0; i < file_count; i++) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", FRAMES_PATH, file_names[i]);
        FILE *file = fopen(filepath, "r");
        if (file) {
            original_frames[frame_count] = malloc(MAX_FRAME_SIZE);
            if (original_frames[frame_count] == NULL) {
                perror("Error allocating memory for original frame");
                fclose(file);
                continue;
            }
            size_t read_size = fread(original_frames[frame_count], sizeof(char), MAX_FRAME_SIZE - 1, file);
            original_frames[frame_count][read_size] = '\0';
            fclose(file);

            size_t len = strlen(original_frames[frame_count]);
            flipped_frames[frame_count] = malloc(len + 1);
            if (flipped_frames[frame_count] == NULL) {
                perror("Error allocating memory for flipped frame");
                free(original_frames[frame_count]);
                continue;
            }
            for (size_t j = 0; j < len; j++) {
                flipped_frames[frame_count][j] = original_frames[frame_count][len - 1 - j];
            }
            flipped_frames[frame_count][len] = '\0';
            frame_count++;
        }
        free(file_names[i]);
    }
}

char **get_original_frames() {
    return original_frames;
}

char **get_flipped_frames() {
    return flipped_frames;
}

int get_frame_count() {
    return frame_count;
}

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
        printf("%s%s\033[0m", COLORS[new_color], flip ? flipped_frames[index] : original_frames[index]);
        fflush(stdout);
        index = (index + 1) % frame_count;
        last_color = new_color;
        usleep(FRAME_DELAY);
    }
}