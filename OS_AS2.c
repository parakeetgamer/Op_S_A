#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[256];
    
    while(1){
    printf("\n1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2:  ");
    int main_menu = atoi(fgets(input, 256, stdin));
    
    if (main_menu == 2) break;//exit the program 
    
    if (main_menu != 1){
      printf("Incorrect choice. Try again.\n");
      continue; //jumps back to the top of the loop 

    } 

 }
       while(1){
       
         printf("\nWhich file you want to process?/n);
         printf("Enter 1 to pick the largest file\nEnter 2 to pick the smallest file\n");
         printf("Enter 3 to specify the name of a file\nEnter a choice from 1 to 3:  ");


}





       }  
   


}












}
