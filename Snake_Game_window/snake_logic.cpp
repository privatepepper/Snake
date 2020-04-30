#include "snake_logic.h"

Snake_Logic::Snake_Logic()
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
}

void Snake_Logic::intialize_board()
{
    board.resize(board_height * board_width);
    for (int y = 0; y < board_height; y++){
        for (int x = 0; x < board_width; x++){
           board[y].push_back(0);
        }
    }

    // sets fruit random position
    set_fruit_random_pos();

    // sets head position to the middle
    board[snake_head_y][snake_head_x] = 1;

}

void Snake_Logic::set_fruit_random_pos()
{
    board[fruit_y][fruit_x] = 0;
    fruit_y = (qrand() % board_height - 1) + 0;
    fruit_x = (qrand() % board_width - 1) + 0;
    board[fruit_y][fruit_x] = -1;
}

void Snake_Logic::change_direction(int x)
{
    if (x == 0){
        direction = north_direction;
    }
    if (x == 1){
        direction = west_direction;
    }
    if (x == 2){
        direction = east_direction;
    }
    if (x == 3){
        direction = south_direction;
    }
}

void Snake_Logic::move()
{
    // up
    if (direction == north_direction && snake_head_y != 0){
        board[snake_head_y][snake_head_x] = 0;
        snake_head_y--;
        board[snake_head_y][snake_head_x] = 1;
    }
    // down
    if (direction == south_direction && snake_head_y != board_height - 1){
        board[snake_head_y][snake_head_x] = 0;
        snake_head_y++;
        board[snake_head_y][snake_head_x] = 1;
    }
    // left
    if (direction == west_direction && snake_head_x != 0){
        board[snake_head_y][snake_head_x] = 0;
        snake_head_x--;
        board[snake_head_y][snake_head_x] = 1;
    }
    // right
    if (direction == east_direction && snake_head_x != board_width - 1){
        board[snake_head_y][snake_head_x] = 0;
        snake_head_x++;
        board[snake_head_y][snake_head_x] = 1;
    }
    if (snake_head_y == fruit_y && snake_head_x == fruit_x){
        set_fruit_random_pos();
    }
}



