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

    int board_width = 80;
    int board_height = 60;

    // moving logic
    void change_direction(int x);
    void move();

    // board
    void intialize_board();
    QVector < QVector < int > > board;


private:

    int direction = 1;
    const int north_direction = 0;
    const int south_direction = 3;
    const int west_direction = 1;
    const int east_direction = 2;

    int snake_head_y = board_height / 2;
    int snake_head_x = board_width / 2;

   // int fruit_y;
   // int fruit_x;

};

#endif // SNAKE_LOGIC_H
