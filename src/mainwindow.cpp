#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    m_button = new QPushButton("END", this);
    m_button->setGeometry(QRect(QPoint(0, 0), QSize(50, 50)));
    connect(m_button, SIGNAL(released()), this, SLOT(QUIT()));
    n_button = new QPushButton("NEW", this);
    n_button->setGeometry(QRect(QPoint(0, 50), QSize(50, 50)));
    connect(n_button, SIGNAL(released()), this, SLOT(NEW()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(vanish()));
    timer1->start(1000);
    std::cout<<timer1<<std::endl;
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    itemList.push_back(new Land(16,22,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    itemList.push_back(new Land(-1.5,9,3,18,QPixmap(":/ground.png").scaled(width()/32*3,height()/18*18),world,scene));
    itemList.push_back(new Land(33.5,9,3,18,QPixmap(":/ground.png").scaled(width()/32*3,height()/18*18),world,scene));
    itemList.push_back(new bg(-1,18.5,QPixmap(":/image/bg.jpg").scaled(width(),height()/1.001),world,scene));
    // Create bird (You can edit here)
    pig = new enemy(23.5f,4.0f,0.5f,&timer,QPixmap("://image/pig.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    itemList.push_back(pig);
    birdie = new Bird(4.0f,4.5f,0.5f,&timer,QPixmap(":/bird.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    itemList.push_back(birdie);
    birdie2 = new bird2(3.0f,4.5f,0.5f,&timer,QPixmap("://image/blue.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    itemList.push_back(birdie2);
    birdie3 = new bird3(2.0f,4.5f,0.5f,&timer,QPixmap("://image/black.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    itemList.push_back(birdie3);
    birdie4 = new bird4(1.0f,4.5f,0.5f,&timer,QPixmap("://image/yellow.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    itemList.push_back(birdie4);
    build = new building(24.5f,3.0f,0.5f,1.5f,&timer,QPixmap("://image/wood.png").scaled(width()*0.5/32,height()*1.5/18),world,scene);
    itemList.push_back(build);
    build2 = new building(22.5f,3.0f,0.5f,1.5f,&timer,QPixmap("://image/wood.png").scaled(width()*0.5/32,height()*1.5/18),world,scene);
    itemList.push_back(build2);
    build3 = new building(23.5f,5.0f,2.25f,0.5f,&timer,QPixmap("://image/wood.png").scaled(width()*2.25/32,height()*0.5/18),world,scene);
    itemList.push_back(build3);

    //slingshot *shooter = new slingshot(4.0f,6.0f,1.0f,2.5f,&timer,QPixmap("://image/shooter.png").scaled(960*1/32,540*3/18),world,scene);
    //itemList.push_back(shooter);
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {

        QMouseEvent *ke = static_cast<QMouseEvent *>(event);
        ox = ke->globalX();
        oy = ke->globalY();
        if (presstime==4)
        {
        birdie2->skill();
        }
        if (presstime==8)
        {
        birdie3->skill();
        }
        if (presstime==12)
        {
        birdie4->skill();
        }
    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;

    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        presstime++;
        if (presstime==2){
        QMouseEvent *ke = static_cast<QMouseEvent *>(event);
        rx = ke->globalX();
        ry = ke->globalY();
        birdie->setLinearVelocity(b2Vec2((ox-rx)/50,(ry-oy)/50));
        }
        if (presstime==4){
        QMouseEvent *ke = static_cast<QMouseEvent *>(event);
        rx = ke->globalX();
        ry = ke->globalY();
        birdie2->setLinearVelocity(b2Vec2((ox-rx)/50,(ry-oy)/50));

       // presstime ++;
        }
        if (presstime==8){
        QMouseEvent *ke = static_cast<QMouseEvent *>(event);
        rx = ke->globalX();
        ry = ke->globalY();
        birdie3->setLinearVelocity(b2Vec2((ox-rx)/50,(ry-oy)/50));

       // presstime++;
        }
        if (presstime==12){
        QMouseEvent *ke = static_cast<QMouseEvent *>(event);
        rx = ke->globalX();
        ry = ke->globalY();
        birdie4->setLinearVelocity(b2Vec2((ox-rx)/50,(ry-oy)/50));

       // presstime++;
    }
        //std::cout << "Release !" << std::endl ;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();


}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
    exit(0);
}
void MainWindow::QUIT()
{
    emit quitGame();
}
void MainWindow::NEW()
{
    delete birdie;
    delete birdie2;
    delete birdie3;
    delete birdie4;
    delete build;
    delete build2;
    delete build3;
    pig = new enemy(23.5f,4.0f,0.5f,&timer,QPixmap("://image/pig.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    birdie = new Bird(4.0f,4.5f,0.5f,&timer,QPixmap(":/bird.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    build = new building(24.5f,3.0f,0.5f,1.5f,&timer,QPixmap("://image/wood.png").scaled(width()*0.5/32,height()*1.5/18),world,scene);
    build2 = new building(22.5f,3.0f,0.5f,1.5f,&timer,QPixmap("://image/wood.png").scaled(width()*0.5/32,height()*1.5/18),world,scene);
    build3 = new building(23.5f,4.0f,2.25f,0.5f,&timer,QPixmap("://image/wood.png").scaled(width()*2.25/32,height()*0.5/18),world,scene);
    birdie2 = new bird2(3.0f,4.5f,0.5f,&timer,QPixmap("://image/blue.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    birdie3 = new bird3(2.0f,4.5f,0.5f,&timer,QPixmap("://image/black.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    birdie4 = new bird4(1.0f,4.5f,0.5f,&timer,QPixmap("://image/yellow.png").scaled(width()/32.0*1.0,height()/18.0*1.0),world,scene);
    presstime=0;
    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(vanish()));
    timer1->start(1000);
}
void MainWindow::vanish()
{
  if (pig -> get())
  {
   delete pig;
   delete timer1;
  }
}
