#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>

//declarations
#define ROWS 10
#define COLUMNS 6
int grades[ROWS][COLUMNS];


void calculate();

int main(){
    
    
    //open file 
    FILE *fh;
    fh = fopen("sample_in_grades.txt", "r");
    //error case if file does not open
    if(fh == NULL)
    {
        printf("Error opening file \n");
    }


    //teacher process loop for reading the file
    int count = 0;
    while ((!feof(fh)))
    {
        for (int i = 0; i < COLUMNS; i++)
        {   
            //reads and stores it in the array grades tht we created
            if(fscanf(fh,"%d", &grades[count][i]) == EOF)
            {
            break;
            }
        }
        count++;
        if(count == ROWS)
        {
            break;
        }

    }
    fclose(fh);
    
    
    //to check if array has correct array
    //loops and prints through the grades array with stored info from file
    // for (int i = 0; i < ROWS; i++)
    // {
    //     for (int j = 0; j < COLUMNS; j++)
    //     {
    //         //prints the grades array
    //         printf("%d ", grades[i][j]);
            

    //     }
    //     printf("\n");
        
    // }


    

    //pid(process id) declarations
    int GradTA_pid;
    int TA_pid;

    //creating GradTA processes
    for (int i = 0; i < COLUMNS/6; i++)
    {
        GradTA_pid = fork();

        if(GradTA_pid == 0)
        {
            //creating TA process for each GradTA processes
            for (int j = 0; j < COLUMNS/6; j++)
            {
                TA_pid = fork();
                
                if(TA_pid == 0)
                {
                    calculate();
                    exit(EXIT_SUCCESS);
                }
            }

            for (int k = 0; k < COLUMNS/6; k++)
            {
                wait(NULL);
            }
            exit(EXIT_SUCCESS);
            
        }
        
    }
    
    for (int l = 0; l < COLUMNS/6; l++)
    {
        wait(NULL);
    }
    
    
    return 0;

}

void calculate(){
    float average = 0;
    float sum = 0;

    for (int i = 0; i < 6; i++)
    {
        sum = 0;
        for (int j = 0; j < 10; j++)
        {
            //add the array[0][0] and so on into the sum
            sum += grades[j][i];
        }

        
        average = sum/10;
        
        printf("Assignment %d - Average = %.6f\n", i+1 , average);

    }
    
}