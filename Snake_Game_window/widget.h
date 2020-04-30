#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "snake_logic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    Snake_Logic snake;

    QTimer *timer;

    int inner_rectangles_width = snake.board_width;
    int inner_rectangles_height = snake.board_height;

    int inner_rectangle_width = 800 / inner_rectangles_width;
    int inner_rectangle_height = 600 / inner_rectangles_height;

    QGraphicsScene *scene;
    QGraphicsRectItem *rect;

    QVector < QVector < QGraphicsRectItem* > > inner_rectangles;
    void reset_rectangles();
    void initialize_rectangles();

    QVector <QPair <int,int> > snake_coordinates;


private slots:

    void update_rectangles();
    void on_PlayButton_clicked();
    void on_StopButton_clicked();


protected:
    void keyPressEvent(QKeyEvent *event);

};
#endif // WIDGET_H
