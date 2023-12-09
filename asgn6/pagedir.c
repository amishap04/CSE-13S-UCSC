#include "pagedir.h"
#include <string.h>


bool pagedir_init(const char *pageDirectory) {
	// Fill in with your implementation
// printf("hello");   
 struct stat st = {0};

    // Check if directory exists
    if (stat(pageDirectory, &st) == -1) {
	// printf("hello 1");
        // Directory does not exist, attempt to create it
        if (mkdir(pageDirectory, 0700) == -1) { // 0700 permissions allow read, write, & execute for the owner
            perror("Error creating directory");
        // printf("hello 2");    
	return false;
        }
    } else {
	// printf("hello 3");
        printf("Directory Exists");
        // The directory exists. Additional checks can be added here if necessary
        // For example, checking if the directory is writable
    }

    return true;
}






void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {

	// creating filename first
	char str2[200];

        // Concatenate str2 onto result
        sprintf(str2, "%d", documentID);

        // Since str1 points to a read-only location, we can't directly concatenate str2 to it.
        // We need a writable array that is large enough for both strings.
        char filename[500];

        // Copy str1 into result
        strcpy(filename, pageDirectory);
        strcat(filename, str2);


FILE *file = fopen(filename, "w");  // Open the file for writing
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", page->html);  // Write the data to the file
    fclose(file);  // Close the file
}

void saveToFile(const char *filename, const char *data) {
printf("hello");
printf("%s", filename);    
FILE *file = fopen(filename, "w");  // Open the file for writing
printf("open");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
printf("write");
    fprintf(file, "%s", data);  // Write the data to the file
printf("written");
    fclose(file);  // Close the file
}
