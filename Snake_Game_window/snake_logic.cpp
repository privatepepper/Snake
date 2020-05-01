#include "snake_logic.h"

#define head 5
#define head_y whole_snake[0].first
#define head_x whole_snake[0].second

Snake_Logic::Snake_Logic()
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
}

void Snake_Logic::intialize_board()
{

    snake_lenght = 1;

    whole_snake.clear();
    board.clear();
    board.resize(board_height * board_width);
    for (int y = 0; y < board_height; y++){
        for (int x = 0; x < board_width; x++){
           board[y].push_back(0);
        }
    }

    // sets fruit random position
    set_fruit_random_pos();

    // sets head position to the middle
    board[snake_head_y][snake_head_x] = head;
    whole_snake.push_back({snake_head_y, snake_head_x});

}

void Snake_Logic::set_fruit_random_pos()
{
    board[fruit_y][fruit_x] = 0;
    fruit_y = (qrand() % (board_height)) + 0;
    fruit_x = (qrand() % (board_width)) + 0;
    while (board[fruit_y][fruit_x] != 0){
        fruit_y = (qrand() % (board_height)) + 0;
        fruit_x = (qrand() % (board_width)) + 0;
    }
    board[fruit_y][fruit_x] = -1;
    fruit_count++;

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

void Snake_Logic::move_head()
{


    // delete current head position
    board[head_y][head_x] = 0;

    // if, snake ate fruit, add new square for memorization
    if (whole_snake.size() == snake_lenght - 1){
        int element = whole_snake.size() - 1;
        whole_snake.push_back({whole_snake[element].first, whole_snake[element].second});
    }

    //check_collision(direction);

    // if snake size is at least = 2, delete current snake squares, and update to the new ones
    if (whole_snake.size() > 1){
        for (int i = whole_snake.size() - 1; i > 0; i--){
            board[whole_snake[i].first][whole_snake[i].second] = 0;
            whole_snake[i] = {whole_snake[i - 1].first, whole_snake[i - 1].second};
        }
    }

    // up
    if (direction == north_direction){

        if (head_y == 0) {

            head_y = board_height - 1;

        } else
            head_y--;
    }

    // down
    if (direction == south_direction){

        if (head_y == board_height - 1){

            head_y = 0;

        } else
            head_y++;

    }

    // left
    if (direction == west_direction){
        if(head_x == 0){

            head_x = board_width - 1;

        } else
            head_x--;

    }

    // right
    if (direction == east_direction){
        if (head_x == board_width - 1){

            head_x = 0;

        } else
            head_x++;

    }

    move_body();

    // if snake eats the fruit, niam niam:),  renew fruit coordinates
    if (head_y == fruit_y && head_x == fruit_x){
        set_fruit_random_pos();
        snake_lenght++;
    }

    // update snake head position
    board[head_y][head_x] = head;

}

void Snake_Logic::check_collision(int Direction)
{
    for (int i = 1; i < whole_snake.size(); i++){
        if (head_y == whole_snake[i].first && head_x == whole_snake[i].second){
            board[0][0] = -99;
        }
    }
}

void Snake_Logic::move_body()
{
    if (snake_lenght > 1){
        for (int i = 1; i < whole_snake.size(); i++){
            board[whole_snake[i].first][whole_snake[i].second] = 1;
        }
    }
}

