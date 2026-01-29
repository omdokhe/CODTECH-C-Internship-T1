/*
=========================================================
   CODTECH Internship Task-4  
   Data Compression Tool using RLE Algorithm
   Language: C
=========================================================

   Features:
   - Compress text file using Run-Length Encoding
   - Decompress back to original text
   - File-based tool (real compression utility)
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Function Prototypes */
void compressFile(const char *inputFile, const char *outputFile);
void decompressFile(const char *inputFile, const char *outputFile);
void menu();

/* Main Function */
int main() {
    menu();
    return 0;
}

/* Menu Driven Tool */
void menu() {
    int choice;
    char inputFile[100], outputFile[100];

    printf("\n=============================================\n");
    printf("   CODTECH Internship Task-4 (PRO)\n");
    printf("   DATA COMPRESSION TOOL (RLE Algorithm)\n");
    printf("=============================================\n");

    while (1) {
        printf("\n1. Compress File");
        printf("\n2. Decompress File");
        printf("\n3. Exit");
        printf("\n---------------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("\nEnter input text file name: ");
                scanf("%s", inputFile);

                printf("Enter output compressed file name: ");
                scanf("%s", outputFile);

                compressFile(inputFile, outputFile);
                break;

            case 2:
                printf("\nEnter compressed file name: ");
                scanf("%s", inputFile);

                printf("Enter output decompressed file name: ");
                scanf("%s", outputFile);

                decompressFile(inputFile, outputFile);
                break;

            case 3:
                printf("\n✅ Exiting Tool. Internship Task Completed!\n");
                exit(0);

            default:
                printf("\n❌ Invalid Choice! Try Again.\n");
        }
    }
}

/* Compression using Run Length Encoding */
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *fpIn = fopen(inputFile, "r");
    FILE *fpOut = fopen(outputFile, "w");

    if (fpIn == NULL || fpOut == NULL) {
        printf("\n❌ Error opening file!\n");
        return;
    }

    char current, prev;
    int count = 1;

    prev = fgetc(fpIn);

    while ((current = fgetc(fpIn)) != EOF) {
        if (current == prev) {
            count++;
        } else {
            fprintf(fpOut, "%c%d", prev, count);
            prev = current;
            count = 1;
        }
    }

    /* Write last sequence */
    fprintf(fpOut, "%c%d", prev, count);

    fclose(fpIn);
    fclose(fpOut);

    printf("\n✅ File Compressed Successfully!");
    printf("\nOutput Saved in: %s\n", outputFile);
}

/* Decompression */
void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *fpIn = fopen(inputFile, "r");
    FILE *fpOut = fopen(outputFile, "w");

    if (fpIn == NULL || fpOut == NULL) {
        printf("\n❌ Error opening file!\n");
        return;
    }

    char ch;
    int count;

    while ((ch = fgetc(fpIn)) != EOF) {

        if (isdigit(ch)) {
            continue; // skip unexpected digits
        }

        fscanf(fpIn, "%d", &count);

        for (int i = 0; i < count; i++) {
            fputc(ch, fpOut);
        }
    }

    fclose(fpIn);
    fclose(fpOut);

    printf("\n✅ File Decompressed Successfully!");
    printf("\nOutput Saved in: %s\n", outputFile);
}


