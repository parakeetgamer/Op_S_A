#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[256];
    
    while(1){
    printf("\n1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2:  ");
    int main_menu = atoi(fgets(input, 256, stdin));
    
    if (main_menu == 2) break;
    
    if (main_menu != 1){
      printf("Incorrect choice. Try again.\n");
      continue; //jumps back to the top of the loop 

    }
    
    printf("Proceed to file selection... \n"); 


 }
return 0;
}












}
