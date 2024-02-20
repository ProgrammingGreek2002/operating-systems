#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main(){

    char str; 

    do
    {
        printf("Select the option(s) appropriately by entering the number: \n");
        printf("Enter 1 for creating a directory \n");
        printf("Enter 2 for removing directory \n");
        printf("Enter 3 for printing working directory \n");
        printf("Enter 4 for changing directory one level up \n");
        printf("Enter 5 for reading the contents of the directory \n");
        printf("Enter 6 for closing the current directory \n");
        printf("Enter q to exit the program \n");


        scanf(" %c", &str);

        //declaration of another variable
        char name[500];

        switch (str)
        {
        case '1':
            printf("Enter the Directory name you want to create: \n");
            scanf("%s", name);
            if (mkdir(name,0777) == -1)
            {
                perror("Error: ");
            }else
            {
                printf("Directory is Created Successfully \n");
            }
            break;

        case '2':
            printf("Enter the Directory name you want to remove: \n");
            scanf("%s", name);
            if (rmdir(name) == -1)
            {
                perror("Error: ");
            }else
            {
                printf("Directory is removed Successfully \n");
            }
            break;

        case '3':
            if(getcwd(name, sizeof(name)) == NULL)
            {
                perror("Error: ");
            }
            else
            {
                printf("Current Working Directory is: %s \n", name);
            }
            break;
        
        case '4':
            //before
            if(getcwd(name, sizeof(name)) == NULL)
            {
                perror("Error: ");
            }
            else
            {
                printf("Working Directory Before Operation: %s \n", name);
            }
            
            //after
            if(chdir("..") == -1)
            {
                perror("Error: ");
            }
            else
            {
                printf("Directory Changed Successfully. \n");
                if(getcwd(name, sizeof(name)) == NULL)
                {
                    perror("Error: ");
                }
                else
                {
                    printf("Current Directory After Operation: %s \n", name);
                }
            }
            break;

        case '5':
            DIR *directory;
            struct dirent *start;

            //opens the dir stream
            directory = opendir(".");

            if(directory == NULL){
                perror("Error: ");
                
            }
            else
            {
                //reads the content
                while ((start = readdir(directory)) != NULL)
                {
                    printf("%s \n", start -> d_name);
                }

                

            }
            break;

        case '6':
            //assuming dir already open
            if(closedir(directory) == -1){
                perror("Error: ");
            }
            else
            {
                printf("Directory Closed Successfully. \n");
            }
            
            break;
        
        default:
            break;
        }
    } while (str != 'q');

    return 0;

}


