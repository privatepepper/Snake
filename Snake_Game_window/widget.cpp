#include "widget.h"
#include "ui_widget.h"
#include "snake_logic.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);





    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    this->setStyleSheet("background-color: rgb(39, 35, 36) ");
    scene->setBackgroundBrush(QColor(39, 35, 36));

    rect = new QGraphicsRectItem(0, 0,800, 600);
    scene->addItem(rect);

    QPen rect_borders = QPen(Qt::black);
    rect_borders.setWidth(5);
    rect->setPen(rect_borders);

    initialize_rectangles();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_rectangles()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::reset_rectangles()
{
    snake.intialize_board();

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
        for (int x = 0; x < inner_rectangles_width; x++){
            if (snake.board[y][x] == 1){
                inner_rectangles[y][x]->setBrush(QColor(131, 183, 153));
            }
            if (snake.board[y][x] == 0){
                inner_rectangles[y][x]->setBrush(QColor(39, 35, 36));
            }
            if (snake.board[y][x] == -1){
                inner_rectangles[y][x]->setBrush(Qt::red);
            }
        }
    }

    snake.move();

}


void Widget::on_PlayButton_clicked()
{
    timer->start(80);
    // time overtime increases!!!
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
