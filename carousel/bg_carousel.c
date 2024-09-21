#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define verbose 0
#define DBG(cmd) if (verbose) {cmd;}

#define DEFAULT_CAROUSEL_DIR "/home/shaozewxy/Pictures/wukong_selected/"
#define CUR_DIR "."
#define PREV_DIR ".."
#define SET_BG_CMD_TEMPLATE "pcmanfm --set-wallpaper=\"%s\""

#define MAX_NUM_SLIDES 50
#define MAX_CMD_LENGTH 256
#define SLIDE_DURATION 90

char * slide_show[MAX_NUM_SLIDES];
int num_of_slides = 0;

// The kernel for automatically changing the wallpaper.
void* thread_kernel() {
    while (1) {
        int idx = rand() % num_of_slides;
        char * TEST_CMD = (char *)malloc(MAX_CMD_LENGTH);
        sprintf(TEST_CMD, SET_BG_CMD_TEMPLATE, slide_show[idx]);
        DBG(printf("Testing command: %s\n", TEST_CMD))
        system(TEST_CMD);
        sleep(SLIDE_DURATION);
    }

}

int main() {
    srand(time(NULL));

    DIR *d;
    struct dirent *dir;
    d = opendir(DEFAULT_CAROUSEL_DIR);
    if (d) {
        while ((dir = readdir(d)) != NULL && num_of_slides < MAX_NUM_SLIDES) {
            if (strcmp(dir->d_name, CUR_DIR) && strcmp(dir->d_name, PREV_DIR)) {
                char * full_name = (char *)malloc(strlen(dir->d_name) + strlen(DEFAULT_CAROUSEL_DIR) + 1);
                strcpy(full_name, DEFAULT_CAROUSEL_DIR);
                strcat(full_name, dir->d_name);
                DBG(printf("Found slide: %s\n", full_name))
                slide_show[num_of_slides++] = full_name;
            }
        }
        closedir(d);
    }
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_kernel, NULL);
    pthread_join(thread_id, NULL);

    return 0;
}