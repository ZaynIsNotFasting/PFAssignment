#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 2
#define BUFFER_SIZE 4096

typedef struct {
    char **lines;
    int count;
    int capacity;
} EditorBuffer;

void initBuffer(EditorBuffer *editor);
void resizeBuffer(EditorBuffer *editor, int newCapacity);
void insertLine(EditorBuffer *editor, int index, const char *text);
void deleteLine(EditorBuffer *editor, int index);
void printAllLines(const EditorBuffer *editor);
void shrinkToFit(EditorBuffer *editor);
void saveToFile(const EditorBuffer *editor, const char *filename);
void loadFromFile(EditorBuffer *editor, const char *filename);
void freeAll(EditorBuffer *editor);
void handle_error(const char *msg);
char* read_dynamic_input();

int main() {
    EditorBuffer editor;
    initBuffer(&editor);

    int choice, index;
    char filename[100];
    char *input = NULL;

    printf("=== Minimal Line-Based Text Editor ===\n");

    while (1) {
        printf("\n1. Append Line\n2. Insert Line at Index\n3. Delete Line\n");
        printf("4. Print All\n5. Shrink Memory\n6. Save to File\n7. Load from File\n8. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Enter text: ");
                input = read_dynamic_input();
                insertLine(&editor, editor.count, input);
                free(input);
                break;
            case 2:
                printf("Enter index (0 to %d): ", editor.count);
                scanf("%d", &index);
                getchar();
                if (index < 0 || index > editor.count) {
                    printf("Error: Index out of bounds.\n");
                } else {
                    printf("Enter text: ");
                    input = read_dynamic_input();
                    insertLine(&editor, index, input);
                    free(input);
                }
                break;
            case 3:
                printf("Enter index to delete (0 to %d): ", editor.count - 1);
                scanf("%d", &index);
                deleteLine(&editor, index);
                break;
            case 4:
                printAllLines(&editor);
                break;
            case 5:
                shrinkToFit(&editor);
                break;
            case 6:
                printf("Enter filename to save: ");
                if (scanf("%99s", filename) == 1) {
                    saveToFile(&editor, filename);
                }
                break;
            case 7:
                printf("Enter filename to load: ");
                if (scanf("%99s", filename) == 1) {
                    loadFromFile(&editor, filename);
                }
                break;
            case 8:
                freeAll(&editor);
                printf("Exiting... Memory freed.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void initBuffer(EditorBuffer *editor) {
    editor->count = 0;
    editor->capacity = INITIAL_CAPACITY;
    editor->lines = (char **)malloc(editor->capacity * sizeof(char *));
    
    if (editor->lines == NULL) {
        handle_error("Initial allocation failed");
    }
    printf("[Info] Buffer initialized. Capacity: %d\n", editor->capacity);
}

void resizeBuffer(EditorBuffer *editor, int newCapacity) {
    if (newCapacity < INITIAL_CAPACITY) newCapacity = INITIAL_CAPACITY;
    if (newCapacity < editor->count) return;
    char **temp = (char **)realloc(editor->lines, newCapacity * sizeof(char *));
    
    if (temp == NULL && newCapacity > 0) {
        handle_error("Realloc failed");
    }
    
    editor->lines = temp;
    editor->capacity = newCapacity;
    printf("[Debug] Buffer resized. New Capacity: %d\n", editor->capacity);
}

void insertLine(EditorBuffer *editor, int index, const char *text) {
    if (editor->count == editor->capacity) {
        resizeBuffer(editor, editor->capacity * 2);
    }
    if (index < editor->count) {
        memmove(&editor->lines[index + 1], &editor->lines[index], 
                (editor->count - index) * sizeof(char *));
    }
    editor->lines[index] = (char *)malloc(strlen(text) + 1);
    if (editor->lines[index] == NULL) {
        handle_error("String allocation failed");
    }
    strcpy(editor->lines[index], text);
    editor->count++;
    printf("[Success] Line inserted at index %d.\n", index);
}

void deleteLine(EditorBuffer *editor, int index) {
    if (index < 0 || index >= editor->count) {
        printf("Error: Invalid index.\n");
        return;
    }
    free(editor->lines[index]);
    if (index < editor->count - 1) {
        memmove(&editor->lines[index], &editor->lines[index + 1], 
                (editor->count - index - 1) * sizeof(char *));
    }
    editor->count--;
    printf("[Success] Line deleted at index %d.\n", index);
}
void printAllLines(const EditorBuffer *editor) {
    printf("\n--- File Content (%d lines) ---\n", editor->count);
    if (editor->count == 0) {
        printf("(Empty)\n");
    }
    for (int i = 0; i < editor->count; i++) {
        printf("%3d | %s\n", i, editor->lines[i]);
    }
    printf("-------------------------------\n");
}

void shrinkToFit(EditorBuffer *editor) {
    if (editor->count == 0) {
        resizeBuffer(editor, INITIAL_CAPACITY);
    } else {
        resizeBuffer(editor, editor->count);
    }
    printf("[Info] Memory compacted to fit data.\n");
}

void saveToFile(const EditorBuffer *editor, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < editor->count; i++) {
        fprintf(fp, "%s\n", editor->lines[i]);
    }

    fclose(fp);
    printf("[Success] Saved to %s\n", filename);
}

void loadFromFile(EditorBuffer *editor, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return;
    }
    freeAll(editor);
    initBuffer(editor);

    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        
        insertLine(editor, editor->count, buffer);
    }

    fclose(fp);
    printf("[Success] Loaded from %s\n", filename);
}

void freeAll(EditorBuffer *editor) {
    for (int i = 0; i < editor->count; i++) {
        free(editor->lines[i]);
    }
    free(editor->lines);
    editor->lines = NULL;
    editor->count = 0;
    editor->capacity = 0;
}

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

char* read_dynamic_input() {
    int size = 64;
    int len = 0;
    char *str = malloc(size);
    if (!str) handle_error("Input allocation failed");

    int c;
    while(1) {
        c = getchar();
        if (c == '\n' || c == EOF) {
            str[len] = '\0';
            break;
        }

        str[len++] = c;
        
        if (len == size) {
            size *= 2;
            char *temp = realloc(str, size);
            if (!temp) {
                free(str);
                handle_error("Input realloc failed");
            }
            str = temp;
        }
    }
    return str;
}