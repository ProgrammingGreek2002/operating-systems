#include <stdio.h>

struct threadInfo
{
    int p_id;
    int arr_time;
    int brust_time;
    int waiting_time;
    int completion_time;
    int turn_around_time;
};


int main()
{
     //declarations
    struct threadInfo currThread[50];
    int row = 0;
    //int complete_time = 0;
    float average_waiting = 0.0;
    float average_turn_around = 0.0;


    //open file
    FILE *file;

    //choose file
    file = fopen("sample_in_schedule.txt", "r");

    //file opening error
    if(file == NULL)
    {
        printf("Error opening file \n");
    }

    //reading the file
    while(fscanf(file, "%d, %d, %d", &currThread[row].p_id, &currThread[row].arr_time, 
            &currThread[row].brust_time) == 3)
    {
        row = row + 1;
    }

    //close file
    fclose(file);


    //getting tt and wt
    //i = row
    for (int i = 0; i < row; i++)
    {
        currThread[i].completion_time = currThread[i].brust_time;

        //threads tht came before the i
        //j = colmn
        for (int  j = 0; j < i; j++)
        {
            currThread[i].completion_time = currThread[i].completion_time + currThread[j].brust_time;
        }

        currThread[i].turn_around_time = currThread[i].completion_time - currThread[i].arr_time;
        currThread[i].waiting_time = currThread[i].turn_around_time - currThread[i].brust_time;
        
    }

    //getting the average of tt and wt
    for (int i = 0; i < row; i++)
    {
        average_waiting = average_waiting + currThread[i].waiting_time;
        average_turn_around = average_turn_around + currThread[i].turn_around_time;
    }
    average_waiting = average_waiting/row;
    average_turn_around = average_turn_around/row;
    


    //print statements
    printf("Thread ID\t Arrival Time\t Burst Time\t Completion Time\t Turn-Around Time\t Waiting time\n");

    for (int i = 0; i < row; i++)
    {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t\t %d\n", currThread[i].p_id, currThread[i].arr_time, 
        currThread[i].brust_time, currThread[i].completion_time, 
        currThread[i].turn_around_time, currThread[i].waiting_time);
    }

    printf("The average waiting time: %0.2f\n", average_waiting);
    printf("The average turn-around time: %0.2f\n", average_turn_around);
    
    //return statement
    return 0;
}