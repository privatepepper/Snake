#include "widget.h"
#include "ui_widget.h"
#include "snake_logic.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFocusPolicy(Qt::StrongFocus);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    this->setStyleSheet("background-color: rgb(39, 35, 36) ");
    scene->setBackgroundBrush(QColor(39, 35, 36));

    initialize_scene();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_rectangles()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initialize_scene()
{
    rect = new QGraphicsRectItem(0, 0,800, 600);
    scene->addItem(rect);

    QPen rect_borders = QPen(Qt::black);
    rect_borders.setWidth(5);
    rect->setPen(rect_borders);

    initialize_rectangles();
}

void Widget::reset_rectangles()
{
    snake.intialize_board();
    inner_rectangles.clear();
    inner_rectangles.resize(inner_rectangles_width * inner_rectangles_height);
    for (int y = 0; y < inner_rectangles_height; y++){
        QGraphicsRectItem *nothing;
        for (int x = 0; x < inner_rectangles_width; x++){
            inner_rectangles[y].push_back(nothing);
        }
    }
}

void Widget::initialize_rectangles()
{
    reset_rectangles();

    for (int y = 0; y < inner_rectangles_height; y++){
        for (int x = 0; x < inner_rectangles_width; x++){
            QGraphicsRectItem *inner_rectangle = new QGraphicsRectItem(x * inner_rectangle_width, y * inner_rectangle_height, inner_rectangle_width, inner_rectangle_height, rect);
            inner_rectangle->setPen(Qt::NoPen);
            inner_rectangles[y][x] = inner_rectangle;
        }
    }
}

void Widget::update_rectangles()
{
    for (int y = 0; y < inner_rectangles_height; y++){
        if (game_is_not_lost){

            for (int x = 0; x < inner_rectangles_width; x++){

                // collision
                if (snake.board[y][x] == -99){
                    QMessageBox::about(this, "t", "You lost!!!!");
                    game_is_not_lost = false;
                    break;
                }

                // fruit
                if (snake.board[y][x] == -1){
                    inner_rectangles[y][x]->setBrush(QColor(232, 111, 104));
                }

                // body
                if (snake.board[y][x] == 1){
                    inner_rectangles[y][x]->setBrush(QColor(131, 183, 153));
                }

                // empty
                if (snake.board[y][x] == 0){
                    inner_rectangles[y][x]->setBrush(QColor(39, 35, 36));
                }



                // head
                if (snake.board[y][x] == 5){
                    inner_rectangles[y][x]->setBrush(QColor(226, 205, 109));
                }

            }
        }
    }

    if (game_is_not_lost){

        snake.move_head();

    } else
        on_ResetButton_clicked();
}


void Widget::on_PlayButton_clicked()
{
    timer->start(100);
}

void Widget::on_StopButton_clicked()
{
    timer->stop();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_W:
            snake.change_direction(0);
            break;

        case Qt::Key_S:
            snake.change_direction(3);
            break;

        case Qt::Key_A:
            snake.change_direction(1);
            break;

        case Qt::Key_D:
            snake.change_direction(2);
            break;
    }

}

void Widget::on_ResetButton_clicked()
{
    snake.fruit_count = 0;
    game_is_not_lost = true;
    scene->clear();
    timer->stop();
    initialize_scene();
    snake.change_direction(2);

}
