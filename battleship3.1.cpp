#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

int grid[5][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
int *arry = grid[0];
bool win = false, replay = false; //near = false;
unsigned int sunkCount = 0;
unsigned int guessX, guessY; //lastX, lastY;

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
        //near = false;
    }
    else if(grid[y][x-1] == 1 || grid[y-2][x-1] == 1 || grid[y-1][x-2] == 1 || grid[y-1][x] == 1  ) //checks adjacent coordinates
    {
        std::cout << "\n\tNEAR MISS!\n" << std::endl;
        //near = true;
        //lastX = x;
        //lastY = y;
    }
    else{
        std::cout << "\n\tMISS!\n" << std::endl;
    }
}

void guess()
{
         while(!win){
            std::cout << "\n\tThe AI guessed the coordinates:";
            /* 
            if(near){ //if near miss
                guessX = 
            }     
            else{*/
                guessX = rand() % 5 + 1;
                guessY = rand() % 5 + 1;
            //} 

            std::cout << "\t(" << guessX << "," << guessY << ")" << std::endl;

            detectHit(guessY, guessX);
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); //wait 0.5 sec
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
    std::cout << "\n\tPlay simulation again?\n\t1. Yes\n\t2. No" << std::endl;
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

