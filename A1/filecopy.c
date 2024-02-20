#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]){

    char a;
    FILE *inputFile, *outputFile;
    
    //file names
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    //arguments
    if (argc < 3)
    {
        printf("Insufficient parameters passed. \n");
        return 1;
    }

    //input file error
    if(inputFile == NULL)
    {
        printf("Error: No input files \n");
        return 1;
    }

    //copy file
    while ((a = fgetc(inputFile)) != EOF)
    {
        fputc(a, outputFile);
    }
    
    fclose(inputFile);
    fclose(outputFile);

    //ouput file error
    if(outputFile == NULL)
    {
        printf("Error: Output File is Null \n");
        return 1;
    }

    printf("The contents of file %s have successfully copied into the %s file. \n", argv[1], argv[2]);

    return 0;
}
