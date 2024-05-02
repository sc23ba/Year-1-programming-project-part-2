#include <stdio.h>

#include <string.h>

#include <stdlib.h>


//structures and subroutines

struct Cell {

    int row;

    int column;

    char type;

};

//file handling and techniques used are attributed to resources at https://www.geeksforgeeks.org/error-handling-during-file-operations-in-c-c/
//and previous coding experience 
int* ValidateMaze(const char* filename) { 

    //Memory allocation of size needs to be dynamic otherwise the return will return the address of size, not the array itself
    int* size = malloc(2 * sizeof(int));
    if (size == NULL) {
        perror("Memory allocation failed\n");
        return NULL;
    }
    size[0] = 1;
    

    char line_buffer[50];       

    int height = 0;

    int width = 0;

    int startCheck = 0;

    int endCheck = 0;


    FILE* file = fopen(filename, "r");


    if (file == NULL) {

        perror("Invalid file, please try again\n");

        return size;

    }

    else {

        while (fgets(line_buffer, line_buffer[50], file) != NULL) {

            if (ferror(file)) {
                perror("Error reading file");
                fclose(file); 
                return size;     
            }

            height++;

        }

    }

    rewind(file);

    //this initial section is influenced from code I made for coursework in a previous university module "Procedural programming"


    while (fgets(line_buffer, line_buffer[50], file) != NULL)

    {

        for (int i = 0; i < strlen(line_buffer); i++) {

            if (line_buffer[i] == '#' || line_buffer[i] == ' ') {


            }

            else if (line_buffer[i] == 'E' && endCheck == 0) {

                endCheck = 1;

            }

            else if (line_buffer[i] == 'S' && startCheck == 0) {

                startCheck = 1;

            }

            else {

                return size;

            }


        }

        if (width != strlen(line_buffer) && width != 0) {

            return size;

        }

    }

    fclose(file);
    //if the size is returned before this point then the file is counted as invalid, the error check
    //occurs outside of this subroutine in main where as height will be 1 it will loop back for the user to reinput the filename
    size[0] = height;
    size[1] = width;

    return size;

}


char** LoadMaze(const int count, char* filename) { //is the user's input is valid and the maze itself is valid it will

    char line_buffer[50];                        

    char** maze = (char**)malloc(count * sizeof(char*));

    int j = 0;


    for (int i = 0; i < count; i++) {

        maze[i] = (char*)malloc(count * sizeof(char));

    }

    FILE* file = fopen(filename, "r");


    if (file == NULL) {

        perror("");

        return NULL;

    }

    while (fgets(line_buffer, line_buffer[50], file) != NULL)

    {

        for (int i = 0; i < strlen(line_buffer); i++) {

            maze[j][i] = line_buffer[i];

        }

        j++;

    }

    fclose(file);

    return maze;

}



struct Cell LoadStartPosition(char** maze, int height, int width) {
    //the maze is read until the cell 'S' is found and then the coordinates are returned
    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (maze[i][j] == 'S') {

                struct Cell currentLocation;

                currentLocation.row = i;

                currentLocation.column = j;

                currentLocation.type = 'S';

                return currentLocation;

            }

        }

    }

}


int GetInput() {

    int errorCheck = 0;

    char option;

    while (errorCheck == 0) {

        printf("\n");

        printf("Please enter your movement(W/A/S/D): ");

        scanf(" %c", &option);

        printf("\n");

        if (option == 'A' || option == 'a') {

            return 1;

        }

        else if (option == 'W' || option == 'w') {

            return 2;

        }

        else if (option == 'D' || option == 'd') {

            return 3;

        }

        else if (option == 'S' || option == 's') {

            return 4;

        }

        else {

            printf("Invalid Input, please try again. ");

        }



    };

}



struct Cell Move(struct Cell currentLocation, char** maze, int height, int width, int option) {

    if (option == 1) {

        if (currentLocation.row - 1 == -1) {

            printf("Invalid movement, please try again.\n");

        }

        else if (maze[currentLocation.row - 1][currentLocation.column] == '#') {

            printf("Invalid movement, please try again.\n");

        }

        else {

            currentLocation.type = maze[currentLocation.row - 1][currentLocation.column];

            currentLocation.row += -1;

        }

        return currentLocation;

    }

    else if (option == 2) {

        if (currentLocation.column - 1 == -1) {

            printf("Invalid movement, please try again.\n");

        }

        else if (maze[currentLocation.row][currentLocation.column - 1] == '#') {

            printf("Invalid movement, please try again.\n");

        }

        else {

            currentLocation.type = maze[currentLocation.row][currentLocation.column - 1];

            currentLocation.column += -1;

        }

        return currentLocation;

    }

    else if (option == 3) {

        if (currentLocation.row + 1 == height) {

            printf("Invalid movement, please try again.\n");

        }

        else if (maze[currentLocation.row + 1][currentLocation.column] == '#') {

            printf("Invalid movement, please try again.\n");

        }

        else {

            currentLocation.type = maze[currentLocation.row + 1][currentLocation.column];

            currentLocation.row += 1;

        }

        return currentLocation;

    }

    else if (option == 4) {

        if (currentLocation.column + 1 == width) {

            printf("Invalid movement, please try again.\n");

        }

        else if (maze[currentLocation.row][currentLocation.column + 1] == '#') {

            printf("Invalid movement, please try again.\n");

        }

        else {

            currentLocation.type = maze[currentLocation.row][currentLocation.column + 1];

            currentLocation.column += 1;

        }

        return currentLocation;

    }

}


int Wincheck(struct Cell currentPosition)

{

    if (currentPosition.type == 'E') {

        printf("Well done, you won!");

        return 1;

    }

    else {

        return 0;

    }

}


void showMap(char** maze, struct Cell currentPosition, int height, int width) {

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (currentPosition.row == i && currentPosition.column == j) {

                printf("X");

            }
            else
            {
                printf("%c ", maze[i][j]);
            }

        }

        printf("\n");

    }

}






//


int main() {

    int wingame = 0;

    int option;

    int height = 1;

    int width;

    int movement;

    char* fileName = (char*)malloc(50 * sizeof(char));

    while (height == 1)

    {

        printf("Please enter your Maze file name\n");

        scanf(" %s", fileName);

        if (ValidateMaze(fileName)[0] != 1){
            height = ValidateMaze(fileName)[0];
            width = ValidateMaze(fileName)[1];
        }

        

    }

    char** maze = LoadMaze(height, fileName);

    struct Cell currentPosition;
    currentPosition = LoadStartPosition(maze, height, width);


    //the loading phase has ended and the game will then begin

    while (wingame == 0) {

        printf("Select Option\n");

        printf("1. Move\n");

        printf("2. See Map\n");

        printf("3. Exit program\n");

        printf("(enter number option)\n");

        scanf(" %d", &option);

        if (option == 1) {

            movement = GetInput();

            currentPosition = Move(currentPosition, maze, height, width, option);
        }

        else if (option == 2) {

            showMap(maze, currentPosition, height, width);

        }

        else if (option == 3) {

            return 0;

        }

        else {

            printf("Invalid input, please try again");

        }

        wingame = Wincheck(currentPosition);

    }
    
    free(fileName);
    for (int i = 0; i < height; i++) {
        free(maze[i]);
    }
    free(maze);
    


    return 0;

}
