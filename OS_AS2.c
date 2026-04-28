// Author: Luke Edwards
// Description: Assignment 2 - Files & Directories
// Finds and processes movie CSV files, categorizing titles into yearly text files.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define ONID "edwarluk"

// The Function Prototypes
void create_output_dir(char *folder_name);
void write_movie_to_year(char *movie_title, char *release_year, char *folder_name);
int file_exists(char *filename);
void process_the_file(char *filename);
void find_largest_file();
void find_smallest_file();

int main() {
    srandom(time(NULL)); // Seed for random dir naming
    char input[256];

    // Main menu loop
    while (1) {
        printf("\n1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2: ");
                        //translate string to int with atoi 
        int main_menu = atoi(fgets(input, 256, stdin));
        
        if (main_menu == 2) break;
        
        if (main_menu != 1) {
            printf("Incorrect choice. Try again.\n");
            continue; 
        }

        // File selection sub-menu
        while (1) {
            printf("\nWhich file you want to process?\n");
            printf("Enter 1 to pick the largest file\nEnter 2 to pick the smallest file\n");
            printf("Enter 3 to specify the name of a file\nEnter a choice from 1 to 3: ");
                                
            int search_choice = atoi(fgets(input, 256, stdin));
            
            if (search_choice == 1) { 
                find_largest_file(); 
                break; 
            } else if (search_choice == 2) {
                find_smallest_file();
                break;
            } else if (search_choice == 3) {
                printf("Enter the complete file name: ");
                strtok(fgets(input, 256, stdin), "\n"); // Strip newline character
                
                if (file_exists(input)) { 
                    process_the_file(input); 
                    break; 
                }
                 printf("The file %s was not found. Try again\n", input);
            } else {
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
            }
        }
    }
    return 0;
}

// Creates a named directory 
void create_output_dir(char *folder_name) {
    snprintf(folder_name, 64, "%s.movies.%d", ONID, (int)(random() % 100000));
    
    if (mkdir(folder_name, 0750) == -1) {
        printf("Error: Could not create directory %s\n", folder_name);
    } else {
        printf("Created directory with name %s\n\n", folder_name);
    }
}

// Appends a movie title to its release year file 
void write_movie_to_year(char *movie_title, char *release_year, char *folder_name) {
    char path[128];
    snprintf(path, 128, "%s/%s.txt", folder_name, release_year);
    
    int year_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0640);
    if (year_fd != -1) {
        write(year_fd, movie_title, strlen(movie_title)); 
        write(year_fd, "\n", 1); 
        close(year_fd);
    }
}

// Checks if a file exists with the access() system call
int file_exists(char *filename) {
    if (access(filename, F_OK) == 0) {
        return 1;
    }
    return 0;
}

// Loads the CSV into memory, parses titles and years, and writes to the output files
void process_the_file(char *filename) {
    printf("Now processing the chosen file named %s\n", filename);
    char folder_name[64];
    
    create_output_dir(folder_name);

    FILE *movie_ptr = fopen(filename, "r");
    if (movie_ptr == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    
    getline(&line, &len, movie_ptr); // Skip header row
    
    // Parse each line for title and year
    while (getline(&line, &len, movie_ptr) != -1) {
        char *movie_title = strtok(line, ",");
        char *release_year = strtok(NULL, ",\r\n"); 
        
        if (movie_title && release_year) {
            write_movie_to_year(movie_title, release_year, folder_name);
        }
    }
    
    free(line);
    fclose(movie_ptr);
}

// Scans current dir for the largest file matching "movies_*.csv"
void find_largest_file() {
    DIR *folder = opendir(".");
    if (folder == NULL) {
        printf("Could not open current directory.\n");
        return;
    }

    struct dirent *item;
    struct stat file_info;
    char target_file[256] = "";
    off_t file_size = 0; 

    while ((item = readdir(folder))) {
        if (!strncmp(item->d_name, "movies_", 7) && strstr(item->d_name, ".csv")) {
            stat(item->d_name, &file_info);
            if (file_info.st_size >= file_size) {
                file_size = file_info.st_size;
                strcpy(target_file, item->d_name);
            }
        }
    }
    closedir(folder);
    
    if (*target_file) process_the_file(target_file);
    else printf("No matching files found.\n");
}

// Scans current dir for the smallest file matching "movies_*.csv"
void find_smallest_file() {
    DIR *folder = opendir(".");
    if (folder == NULL) {
        printf("Could not open current directory.\n");
        return;
    }

    struct dirent *item;
    struct stat file_info;
    char target_file[256] = "";
    off_t file_size = LONG_MAX; // The Max Integer

    while ((item = readdir(folder))) {
        if (!strncmp(item->d_name, "movies_", 7) && strstr(item->d_name, ".csv")) {
            stat(item->d_name, &file_info);
            if (file_info.st_size <= file_size) {
                file_size = file_info.st_size;
                strcpy(target_file, item->d_name);
            }
        }
    }
    closedir(folder);
    
    if (*target_file) process_the_file(target_file);
    else printf("No matching files found.\n");
}