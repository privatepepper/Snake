#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class Snake_Logic
{
public:
    Snake_Logic();

    int board_width = 20;
    int board_height = 15;

    // moving logic
    void change_direction(int x);
    void move_head();
    void move_body();

    // board
    void intialize_board();
    QVector < QVector < int > > board;

    // for tests
    int fruit_count = 0;

private:

    int direction = 2;
    const int north_direction = 0;
    const int south_direction = 3;
    const int west_direction = 1;
    const int east_direction = 2;

    // snake
    int snake_head_y = board_height / 2;
    int snake_head_x = board_width / 2;
    int snake_lenght = 1;
    QVector < QPair <int, int> > whole_snake;
    void check_collision(int x);

    // fruit
    void set_fruit_random_pos();
    int fruit_y = 0;
    int fruit_x = 0;

};

#endif // SNAKE_LOGIC_H
