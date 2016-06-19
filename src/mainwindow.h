#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <building.h>
#include <enemy.h>
#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <bird2.h>
#include <bird3.h>
#include <bird4.h>
#include <bg.h>
#include <QPushButton>
#include <QApplication>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    int presstime=0;
    int ox;
    int oy;
    int rx;
    int ry;
    int xx;
    int yy;
    enemy *pig;
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void QUIT();
    void NEW();
    void vanish();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QTimer *timer1;
    QPushButton *m_button;
    QPushButton *n_button;
    Bird *birdie;
    building *build;
    building *build2;
    building *build3;
    bird2 *birdie2;
    bird3 *birdie3;
    bird4 *birdie4;
};

#endif // MAINWINDOW_H

