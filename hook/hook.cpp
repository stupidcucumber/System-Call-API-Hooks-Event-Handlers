#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main() {
    int fd;
    struct input_event ev;

    // Open the input device
    fd = open("/dev/input/event4", O_RDONLY);
    if (fd == -1) {
        perror("Unable to open input device");
        exit(EXIT_FAILURE);
    }

    // Read input events
    while (1) {
        if (read(fd, &ev, sizeof(struct input_event)) < sizeof(struct input_event)) {
            perror("Error reading input event");
            exit(EXIT_FAILURE);
        }

        // Check if it's a key event
        if (ev.type == EV_KEY) {
            // Print the key code
            printf("Key code: %d\n", ev.code);
        }
    }

    // Close the input device
    close(fd);

    return 0;
}