/*
===========================================================
 CODTECH Internship Task-1  
 File Handling Program in C

 Features:
 1. Create/Write File
 2. Append Data
 3. Read File
 4. Search Text in File
 5. File Statistics (Lines, Words, Characters, Size)
 6. Copy File Content
 7. Delete File
===========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 500

/* Function Prototypes */
void writeFile();
void appendFile();
void readFile();
void searchInFile();
void fileStatistics();
void copyFile();
void deleteFile();

/* Utility Function */
void clearBuffer() {
    while (getchar() != '\n');
}

/* Main Program */
int main() {
    int choice;

    printf("\n========================================\n");
    printf("   CODTECH Internship Task-1 (PRO)\n");
    printf("      Advanced File Handling System\n");
    printf("========================================\n");

    while (1) {
        printf("\n----------- MENU -----------\n");
        printf("1. Write/Create File\n");
        printf("2. Append Data to File\n");
        printf("3. Read File Content\n");
        printf("4. Search Text in File\n");
        printf("5. File Statistics Report\n");
        printf("6. Copy File Content\n");
        printf("7. Delete File\n");
        printf("8. Exit\n");
        printf("----------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
            case 1: writeFile(); break;
            case 2: appendFile(); break;
            case 3: readFile(); break;
            case 4: searchInFile(); break;
            case 5: fileStatistics(); break;
            case 6: copyFile(); break;
            case 7: deleteFile(); break;
            case 8:
                printf("\nExiting Program... Thank You!\n");
                exit(0);

            default:
                printf("\n❌ Invalid Choice! Try Again.\n");
        }
    }
    return 0;
}

/* 1. Write/Create File */
void writeFile() {
    FILE *fp;
    char filename[100], text[MAX_TEXT];

    printf("\nEnter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("❌ Error: File cannot be created!\n");
        return;
    }

    printf("Enter text to write (single line): ");
    fgets(text, sizeof(text), stdin);

    fputs(text, fp);
    fclose(fp);

    printf("✅ File written successfully!\n");
}

/* 2. Append Data */
void appendFile() {
    FILE *fp;
    char filename[100], text[MAX_TEXT];

    printf("\nEnter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "a");

    if (fp == NULL) {
        printf("❌ Error: File cannot be opened!\n");
        return;
    }

    printf("Enter text to append: ");
    fgets(text, sizeof(text), stdin);

    fputs(text, fp);
    fclose(fp);

    printf("✅ Data appended successfully!\n");
}

/* 3. Read File */
void readFile() {
    FILE *fp;
    char filename[100], ch;

    printf("\nEnter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("❌ Error: File not found!\n");
        return;
    }

    printf("\n----- File Content -----\n");

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
    printf("\n------------------------\n");
}

/* 4. Search Text */
void searchInFile() {
    FILE *fp;
    char filename[100], word[100], line[MAX_TEXT];
    int found = 0, lineNo = 1;

    printf("\nEnter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("❌ Error: File not found!\n");
        return;
    }

    printf("Enter word/text to search: ");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0';

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, word)) {
            printf("✅ Found at line %d: %s", lineNo, line);
            found = 1;
        }
        lineNo++;
    }

    if (!found)
        printf("❌ Text not found in file.\n");

    fclose(fp);
}

/* 5. File Statistics */
void fileStatistics() {
    FILE *fp;
    char filename[100], ch;
    int lines = 0, words = 0, chars = 0;
    long size;

    printf("\nEnter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("❌ Error: File not found!\n");
        return;
    }

    while ((ch = fgetc(fp)) != EOF) {
        chars++;

        if (ch == '\n') lines++;
        if (ch == ' ' || ch == '\n' || ch == '\t') words++;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    fclose(fp);

    printf("\n------ File Statistics ------\n");
    printf("Total Characters : %d\n", chars);
    printf("Total Words      : %d\n", words);
    printf("Total Lines      : %d\n", lines);
    printf("File Size        : %ld bytes\n", size);
    printf("-----------------------------\n");
}

/* 6. Copy File */
void copyFile() {
    FILE *source, *target;
    char srcName[100], tgtName[100], ch;

    printf("\nEnter source file name: ");
    fgets(srcName, sizeof(srcName), stdin);
    srcName[strcspn(srcName, "\n")] = '\0';

    source = fopen(srcName, "r");

    if (source == NULL) {
        printf("❌ Error: Source file not found!\n");
        return;
    }

    printf("Enter target file name: ");
    fgets(tgtName, sizeof(tgtName), stdin);
    tgtName[strcspn(tgtName, "\n")] = '\0';

    target = fopen(tgtName, "w");

    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, target);
    }

    fclose(source);
    fclose(target);

    printf("✅ File copied successfully!\n");
}

/* 7. Delete File */
void deleteFile() {
    char filename[100];

    printf("\nEnter file name to delete: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    if (remove(filename) == 0)
        printf("✅ File deleted successfully!\n");
    else
        printf("❌ Error: Unable to delete file.\n");
}

