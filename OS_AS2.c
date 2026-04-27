#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_largest_file();
void find_smallest_file();
void process_the_file(char *filename);

int main() {  
    char input[256];
        
    while (1) {
        printf("\n1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2: ");
        int main_menu = atoi(fgets(input, 256, stdin));
          
        if (main_menu == 2) break;

        if (main_menu != 1) {
            printf("Incorrect choice. Try again.\n");
            continue;
        }

        while (1) {
            printf("\nWhich file do you want to process?\n");
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
                strtok(fgets(input, 256, stdin), "\n");
                
                if(file_exists(input)){
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











}
