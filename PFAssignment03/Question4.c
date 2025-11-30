#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int popularity;
    int time_stamp;
} Book;

int global_time = 0;

int main() {
    int capacity, Q;
    
    if (scanf("%d %d", &capacity, &Q) != 2) return 0;
    
    if (capacity <= 0) {
        return 0; 
    }

    Book* shelf = (Book*)malloc(capacity * sizeof(Book));
    if (shelf == NULL) {
        return 1; 
    }
    int count = 0;

    char command[10];
    int x, y;

    for (int i = 0; i < Q; i++) {
        scanf("%s", command);
        global_time++;

        if (strcmp(command, "ADD") == 0) {
            scanf("%d %d", &x, &y);
            int foundIndex = -1;
            for (int j = 0; j < count; j++) {
                if (shelf[j].id == x) {
                    foundIndex = j;
                    break;
                }
            }

            if (foundIndex != -1) {
                shelf[foundIndex].popularity = y; 
                shelf[foundIndex].time_stamp = global_time;
            } else {
                if (count < capacity) {
                    shelf[count].id = x;
                    shelf[count].popularity = y;
                    shelf[count].time_stamp = global_time;
                    count++;
                } else {
                    int lruIndex = 0;
                    for (int j = 1; j < count; j++) {
                        if (shelf[j].time_stamp < shelf[lruIndex].time_stamp) {
                            lruIndex = j;
                        }
                    }
                    shelf[lruIndex].id = x;
                    shelf[lruIndex].popularity = y;
                    shelf[lruIndex].time_stamp = global_time;
                }
            }
        } 
        else if (strcmp(command, "ACCESS") == 0) {
            scanf("%d", &x); 

            int foundIndex = -1;
            for (int j = 0; j < count; j++) {
                if (shelf[j].id == x) {
                    foundIndex = j;
                    break;
                }
            }

            if (foundIndex != -1) {
                shelf[foundIndex].time_stamp = global_time;
                printf("%d\n", shelf[foundIndex].popularity);
            } else {
                printf("-1\n");
            }
        }
    }

    free(shelf);
    return 0;
}