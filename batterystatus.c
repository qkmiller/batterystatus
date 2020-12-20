#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <unistd.h>

char *
getstring(char *filepath) {
    size_t size = 513;
    char *contents = malloc(size);

    FILE *fd;

    fd = fopen(filepath, "r");
    if (fd == NULL)
        return NULL;
    if (fgets(contents, size - 1, fd) == NULL)
        return NULL;
    fclose(fd);
    for(unsigned int i = 0; i != size; i++) {
        if (contents[i] == '\n')
            contents[i] = '\0';
    }
    return contents;
}

void
updatexwindow(Display *d, char *str) {
    XStoreName(d, DefaultRootWindow(d), str);
    XSync(d, 0);
}

char *
concat(char *a, char *b) {
    size_t size = 513;
    char *c = malloc(size);
    strcpy(c, a);
    strcat(c, b);
    return c;
}

int
run(Display *display) {
    char *bat;
    char *status;
    while(1) {
        bat = getstring("/sys/class/power_supply/BAT0/capacity");
        status = concat("Battery: ", concat(bat, "%"));
        if (!bat)
            return 1;
        updatexwindow(display, status);
        free(bat);
        free(status);
        sleep(90);
    }
    return 0;
}

int main() {
    Display *display;
    if (!(display = XOpenDisplay(NULL))) {
        fprintf(stderr, "Batterystatus Error: cannot open display\n");
        return 1;
    }
    return run(display);
}

