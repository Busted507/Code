#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef unsigned int board_t[8][8];
#define SIZE 8      
#define MOVE_COUNT 8
const int MOVES_X[MOVE_COUNT] = {2, 1, -1, -2, -2, -1, 1, 2};
const int MOVES_Y[MOVE_COUNT] = {1, 2, 2, 1, -1, -2, -2, -1};

bool is_move_legal(size_t current_x,size_t current_y, int move_x, int move_y)
{
    bool retValue=true;

    if (current_x + move_x > SIZE || current_x + move_x < 1)
    retValue=false;

    if (current_y + move_y > SIZE || current_y + move_y < 1)
    retValue=false;

    return retValue;
}

bool move_is_possible(size_t move_id, size_t current_x, size_t current_y, board_t visited)
{
return false;
}

int visited_count(int x, int y, board_t visited)
{
    return visited[x-1][y-1];
}

bool check_all_squares_visited(board_t board)
{
    bool retValue = true;
    
        for x = 1 - 8
        { 
               


            
            for y = 1 - 8
            { int check_all_squares_visited = true
                if (visited_count(x, y) == 0)
                {
                    retValue = false;
                    break;
                }
            }
        }

    */
    return retValue;
}

int main()
{
    int current_x = 1;
    int current_y = 1;
    board_t board = {0};

    for (int i = 1; i <= 100000; i++)
    {
        int least_visited = -1;
        int possible_move_x = 0;
        int possible_move_y = 0;

        for (int move = 0; move <= SIZE-1; ++move) 
        {
            int move_x = MOVES_X[move];
            int move_y = MOVES_Y[move];

            if (is_move_legal(current_x, current_y, move_x, move_y)) 
            {
                int visitCount = visited_count(current_x + move_x, current_y + move_y, board);

                if (least_visited == -1 || visitCount < least_visited)
                {
                    possible_move_x = move_x;
                    possible_move_y = move_y;
                    least_visited = visitCount;
                }
            }
        }

        current_x += + possible_move_x;
        current_y += + possible_move_y;
        board[current_x -1][current_y-1] +=1; 
    }

}


