#include <iostream>
#include <cstdlib>
#include <ctime>

int grid[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
int *arry = grid[0];
bool win = false, replay = false;
unsigned int sunkCount = 0;
unsigned int guessX, guessY;

void printGrid(int *arry, const int rows, const int columns)
{
    for(int i = 0; i < rows; i++){
        std::cout << "\t";
        for(int j = 0; j < columns; j++){
            std::cout << arry[i * columns + j] << " ";
        }
        std::cout << std::endl;
    }
}

void randomizeGrid()
{
    srand(time(NULL));
    int rand1 = rand() % 5;
    srand(time(NULL));
    int rand2 = rand() % 5;

    for(int i = 0; i < 3; i++){ //will place 3 ships
        if(grid[rand1][rand2] == 0){ //if the slot is empty
          grid[rand1][rand2] = 1; //fill it 
        }
        else{
            while(grid[rand1][rand2] != 0){ //if the slot isnt empty move somewhere else until it is
                srand(time(NULL));
                rand2 = rand() % 5;
                rand1 = rand() % 5;
            }
            grid[rand1][rand2] = 1; //assign empty slot to full
        }
    }
}

void detectHit(int y, int x)
{
    int target = grid[y-1][x-1]; //locates exact target
    if(target == 1){
        std::cout << "\n\tHIT!\n" << std::endl;
        grid[y-1][x-1] = 0;
        sunkCount++;
    }
    else if(grid[y][x-1] == 1 || grid[y-2][x-1] == 1 || grid[y-1][x-2] == 1 || grid[y-1][x] == 1  ) //checks adjacent coordinates
    {
        std::cout << "\n\tNEAR MISS!\n" << std::endl;
    }
    else{
        std::cout << "\n\tMISS!\n" << std::endl;
    }
}

void guess()
{
         while(!win){
            std::cout << "\n\tEnter an X coordinate guess from the left (1 2 3 4 or 5): " << std::endl;
            std::cin >> guessX;
            std::cout << "\n\tEnter an Y coordinate guess from the top (1 2 3 4 or 5):" << std::endl;
            std::cin >> guessY;

            detectHit(guessY, guessX);
            printGrid(arry, 5, 5);

            if(sunkCount >= 3){ //if all 3 ships hit you win
                win = true;  
                std::cout << "\n\tYou Win!" << std::endl;
            }
                
         }
}

void playAgain()
{
    int play;
    std::cout << "\n\tPlay again?\n\t1. Yes\n\t2. No" << std::endl;
    std::cin >> play;

    if(play == 1){
        replay = true;
        win = false;
        sunkCount = 0;
    }
        
}

int main()
{
    do{
    
        randomizeGrid();
        printGrid(arry, 5, 5);
        guess();
        playAgain();

    }while(replay);
   
}

