#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <regex.h>

int main() {
    char directory[256];
    char file_regex[256];
    DIR *dir;
    struct dirent *entry;
    regex_t regex;
    int reti;
    
    while(1){
    // prompt the user to input the directory path and the regular expression for the file name
    printf("Enter the directory path: ");
    scanf("%s", directory);
    printf("Enter the file name regular expression: ");
    scanf("%s", file_regex);

    // compile the regular expression
    reti = regcomp(&regex, file_regex, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regular expression.\n");
        exit(1);
    }

    // open the directory and iterate through all files
    dir = opendir(directory);
    if (dir) {
        printf("Matching files found:\n");
        while ((entry = readdir(dir)) != NULL) {
            // check if the file name matches the regular expression
            reti = regexec(&regex, entry->d_name, 0, NULL, 0);
            if (!reti) {
                // if the file name matches, print the full path of the file
                printf("%s/%s\n", directory, entry->d_name);
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Could not open directory.\n");
        exit(1);
    }

    
    }
    // free the regular expression
    regfree(&regex);

    return 0;
}
