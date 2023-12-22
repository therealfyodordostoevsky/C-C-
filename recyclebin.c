#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

// Function prototypes
void clearScreen();
void printHeader();
void printMenu();
void createRecycleBin();
void moveFileToRecycleBin(const char *filename);
void restoreFileFromRecycleBin(const char *filename);
void listFilesInRecycleBin();
void emptyRecycleBin();
void viewFileDetails(const char *filename);
void printColorizedMessage(const char *message, const char *color);
void printProgressBar(int progress);
void sortByExtension();
void deleteFileFromRecycleBin(const char *filename);
int isConfirmationYes();
const char *getFileType(const char *filename);

// Colors for console output
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_RESET "\033[0m"

#define MAX_FILENAME_LENGTH 256
#define RECYCLE_BIN_PATH "recycle_bin"

int main() {
    createRecycleBin();

    int choice;
    char filename[MAX_FILENAME_LENGTH];

    do {
        clearScreen();
        printHeader();
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the filename to move to the recycle bin: ");
                scanf("%s", filename);
                moveFileToRecycleBin(filename);
                break;
            case 2:
                printf("Enter the filename to restore from the recycle bin: ");
                scanf("%s", filename);
                restoreFileFromRecycleBin(filename);
                break;
            case 3:
                listFilesInRecycleBin();
                break;
            case 4:
                if (isConfirmationYes()) {
                    emptyRecycleBin();
                } else {
                    printColorizedMessage("Operation canceled.", COLOR_YELLOW);
                }
                break;
            case 5:
                sortByExtension();
                break;
            case 6:
                printf("Enter the filename to view details: ");
                scanf("%s", filename);
                viewFileDetails(filename);
                break;
            case 7:
                printf("Enter the filename to permanently delete: ");
                scanf("%s", filename);
                deleteFileFromRecycleBin(filename);
                break;
            case 8:
                printf("Exiting program.\n");
                break;
            default:
                printColorizedMessage("Invalid choice. Please enter a number between 1 and 8.", COLOR_RED);
        }

        // Pause the program after each operation
        printf("\nPress Enter to continue...");
        while (getchar() != '\n');
        getchar();

    } while (choice != 8);

    return 0;
}

void clearScreen() {
    system("clear");
}

void printHeader() {
    printf("\n");
    printf("  _____           _     _             _____ _           _   \n");
    printf(" |  __ \\         | |   | |           / ____| |         | |  \n");
    printf(" | |__) |___  ___| |_  | |_   _  ___| (___ | |__   __ _| |_ \n");
    printf(" |  _  // _ \\/ __| __| | | | | |/ __|\\___ \\| '_ \\ / _` | __|\n");
    printf(" | | \\ \\  __/\\__ \\ |_  | | |_| | (__ ____) | | | | (_| | |_ \n");
    printf(" |_|  \\_\\___||___/\\__|  \\__\\__,_|\\___|_____/|_| |_|\\__,_|\\__|\n");
    printf("\n");
}

void printMenu() {
    printf("Recycle Bin Menu:\n");
    printf("1. Move file to recycle bin\n");
    printf("2. Restore file from recycle bin\n");
    printf("3. List files in recycle bin\n");
    printf("4. Empty recycle bin\n");
    printf("5. Sort files by extension\n");
    printf("6. View file details\n");
    printf("7. Permanently delete file\n");
    printf("8. Exit\n");
}

void createRecycleBin() {
    // Create the recycle bin directory if it doesn't exist
    mkdir(RECYCLE_BIN_PATH, 0777);
}

void moveFileToRecycleBin(const char *filename) {
    char recycledFilePath[MAX_FILENAME_LENGTH];
    snprintf(recycledFilePath, sizeof(recycledFilePath), "%s/%s", RECYCLE_BIN_PATH, filename);

    // Move the file to the recycle bin
    if (rename(filename, recycledFilePath) != 0) {
        printColorizedMessage("Error moving file to recycle bin", COLOR_RED);
    } else {
        printColorizedMessage("File moved to recycle bin successfully.", COLOR_GREEN);
    }
}

void restoreFileFromRecycleBin(const char *filename) {
    char recycledFilePath[MAX_FILENAME_LENGTH];
    snprintf(recycledFilePath, sizeof(recycledFilePath), "%s/%s", RECYCLE_BIN_PATH, filename);

    // Move the file back from the recycle bin
    if (rename(recycledFilePath, filename) != 0) {
        printColorizedMessage("Error restoring file from recycle bin", COLOR_RED);
    } else {
        printColorizedMessage("File restored from recycle bin successfully.", COLOR_GREEN);
    }
}

void listFilesInRecycleBin() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(RECYCLE_BIN_PATH);
    if (dir == NULL) {
        printColorizedMessage("Error opening recycle bin directory", COLOR_RED);
        return;
    }

    printf("Files in the recycle bin:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Regular file
            printf("- %s (%s)\n", entry->d_name, getFileType(entry->d_name));
        }
    }

    closedir(dir);
}

void emptyRecycleBin() {
    DIR *dir;
    struct dirent *entry;
    int fileCount = 0;

    dir = opendir(RECYCLE_BIN_PATH);
    if (dir == NULL) {
        printColorizedMessage("Error opening recycle bin directory", COLOR_RED);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Regular file
            fileCount++;
        }
    }

    closedir(dir);

    printf("Emptying recycle bin:\n");
    for (int i = 0; i <= 100; i += 10) {
        printProgressBar(i);
        usleep(200000); // Introduce a delay for a smoother animation
    }

    dir = opendir(RECYCLE_BIN_PATH);
    if (dir == NULL) {
        printColorizedMessage("Error opening recycle bin directory", COLOR_RED);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Regular file
            char filePath[MAX_FILENAME_LENGTH];
            snprintf(filePath, sizeof(filePath), "%s/%s", RECYCLE_BIN_PATH, entry->d_name);
            remove(filePath);
        }
    }

    closedir(dir);

    printf("\nRecycle bin emptied successfully. %d file(s) deleted.\n", fileCount);
}

void viewFileDetails(const char *filename) {
    char filePath[MAX_FILENAME_LENGTH];
    snprintf(filePath, sizeof(filePath), "%s/%s", RECYCLE_BIN_PATH, filename);

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printColorizedMessage("Error opening file for details", COLOR_RED);
        return;
    }

    char ch;
    printf("File details for '%s':\n", filename);

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

void printColorizedMessage(const char *message, const char *color) {
    printf("%s%s%s\n", color, message, COLOR_RESET);
}

void printProgressBar(int progress) {
    printf("\r[");
    int pos = progress / 2;
    for (int i = 0; i < 50; ++i) {
        if (i < pos) printf("%c", '=');
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d%%", progress);
    fflush(stdout);
}

void sortByExtension() {
    // Sorting files in the recycle bin based on their extensions

    DIR *dir;
    struct dirent *entry;
    char filenames[100][MAX_FILENAME_LENGTH];
    int count = 0;

    dir = opendir(RECYCLE_BIN_PATH);
    if (dir == NULL) {
        printColorizedMessage("Error opening recycle bin directory", COLOR_RED);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Regular file
            snprintf(filenames[count], sizeof(filenames[count]), "%s", entry->d_name);
            count++;
        }
    }

    closedir(dir);

    // Bubble sort based on file extensions
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            char *ext1 = strrchr(filenames[j], '.');
            char *ext2 = strrchr(filenames[j + 1], '.');

            if (ext1 != NULL && ext2 != NULL && strcasecmp(ext1, ext2) > 0) {
                // Swap filenames
                char temp[MAX_FILENAME_LENGTH];
                strcpy(temp, filenames[j]);
                strcpy(filenames[j], filenames[j + 1]);
                strcpy(filenames[j + 1], temp);
            }
        }
    }

    // Display sorted files
    printf("Sorted files in the recycle bin:\n");
    for (int i = 0; i < count; i++) {
        printf("- %s\n", filenames[i]);
    }
}

void deleteFileFromRecycleBin(const char *filename) {
    char filePath[MAX_FILENAME_LENGTH];
    snprintf(filePath, sizeof(filePath), "%s/%s", RECYCLE_BIN_PATH, filename);

    if (remove(filePath) == 0) {
        printColorizedMessage("File permanently deleted.", COLOR_GREEN);
    } else {
        printColorizedMessage("Error deleting file.", COLOR_RED);
    }
}

int isConfirmationYes() {
    char response;
    printf("Are you sure? (y/n): ");
    scanf(" %c", &response);
    return (response == 'y' || response == 'Y');
}

const char *getFileType(const char *filename) {
    // Simple file type detection based on file extension

    char *extension = strrchr(filename, '.');

    if (extension != NULL) {
        if (strcasecmp(extension, ".txt") == 0) {
            return "Text";
        } else if (strcasecmp(extension, ".c") == 0 || strcasecmp(extension, ".h") == 0) {
            return "C Source Code";
        } else if (strcasecmp(extension, ".jpg") == 0 || strcasecmp(extension, ".jpeg") == 0 ||
                   strcasecmp(extension, ".png") == 0 || strcasecmp(extension, ".gif") == 0) {
            return "Image";
        } else {
            return "Unknown";
        }
    }

    return "Unknown";
}
