#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->la->setText("Address \t Size \n");
    scene =new QGraphicsScene();
    ui->view->setScene(scene);
    know();
   }
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow:: know()
{
    QBrush a(Qt::blue);
    QBrush b(Qt::green);
    QBrush c(Qt::red);
    QGraphicsRectItem *l1 = new QGraphicsRectItem();
    QGraphicsRectItem *l2= new QGraphicsRectItem();
    QGraphicsRectItem *l3 = new QGraphicsRectItem();
    QGraphicsTextItem *p1  = new QGraphicsTextItem();
    QGraphicsTextItem *p2  = new QGraphicsTextItem();
    QGraphicsTextItem *p3  = new QGraphicsTextItem();
    p1->setPos(15,0-5);
    p2->setPos(15,15-5);
    p3->setPos(15,30-5);
    p1->setPlainText("blocked");
    p2->setPlainText("process");
    p3->setPlainText("free holes");
    l1->setRect(0,0,10,10);
    l1->setBrush(a);
    l2->setRect(0,15,10,10);
    l2->setBrush(b);
    l3->setRect(0,30,10,10);
    l3->setBrush(c);
    QGraphicsScene *s=new QGraphicsScene();
    ui->toknow->setScene(s);
    s->addItem(l1);
    s->addItem(l2);
    s->addItem(l3);
    s->addItem(p1);
    s->addItem(p2);
    s->addItem(p3);

}

void MainWindow::on_insert_clicked()
{
    double x= ui->add->text().toDouble();
    double y = ui->siz->text().toDouble();
    FreeSpace.push_back(qMakePair(x,y));
    QString temp = ui->la->text();
    temp.append(ui->add->text()+"\t"+ui->siz->text()+"\n");
    ui->la->setText(temp);
    ui->add->setText("");
    ui->siz->setText("");
}

void MainWindow:: setFree(QVector <QPair < double,double > >x)
{
    FreeSpace =x;
}
void MainWindow::on_Show_clicked()
{
    updateview();
    ui->view->show();
}
// to sort  as Size in ascend
bool compare(const QPair<double, double>&i, const QPair<double, double>&j)
{
    return i.second < j.second;
}
// to sort as Size descend
bool compare2(const QPair<double, double>&i, const QPair<double, double>&j)
{
    return i.second > j.second;
}
QVector <QPair < double,double > > MainWindow:: getFree()
{
    return FreeSpace;
}

void MainWindow::on_Add_clicked()
{
     double s = ui->lineEdit_3->text().toDouble();
     ui->lineEdit_3->setText("");
    if(ui->first_2->isChecked())
    {
        ui->error->setText("");
        qSort(FreeSpace.begin(),FreeSpace.end());
        firstfit(s);
    }else if(ui->best_2->isChecked())
    {
        ui->error->setText("");
        bestfit(s);
    }else if(ui->worst_2->isChecked())
    {
        ui->error->setText("");
        worstfit(s);
    }
    else
    {
            QMessageBox m ;
            m.setText("You should determine algorithm");
            m.exec();
       // ui->error->setText("You should determine algorithm");
    }
}
void MainWindow ::worstfit(double x)
{
    qSort(FreeSpace.begin(),FreeSpace.end(),compare2); //sort large then small
    firstfit(x);
}

int MainWindow::id=0;
void MainWindow::firstfit(double si)
{
    double tempAdd;
    double siz;
    int fl=0;
    for(QVector < QPair<double,double> >::iterator i=FreeSpace.begin();i!=FreeSpace.end();i++)
    {
        if(i->second >= si)
        {
            tempAdd = i->first;
            siz = si;
            i->first += si;
            i->second -=si;
            fl=1;
            break;
        }
    }
    if(fl==1){
    process p(tempAdd,siz,id);
    id++;
    AllocateSpace.push_back(p);
    //ui->expec->setText(" ");
    updateview();
    }else
    {
        QMessageBox m ;
        m.setText("memoery doesnot have space");
        m.exec();
       // ui->expec->setText("memoery doesnot have space");
    }
}
void MainWindow:: bestfit(double s)
{
 qSort(FreeSpace.begin(),FreeSpace.end(),compare);
 firstfit(s);
}
void MainWindow::updateview()
{
    //Delete preveious scene
    QList<QGraphicsItem*> items = scene->items();
        for (int i = 0; i < items.size(); i++) {
            scene->removeItem(items[i]);
            delete items[i];
        }
        QBrush a(Qt::blue);
        qSort(FreeSpace.begin(),FreeSpace.end());
        for(QVector < QPair<double,double> >::iterator i=FreeSpace.begin();i!=FreeSpace.end();i++)
        {
            QVector < QPair<double,double> >::iterator k=i;
            k--;

            if(i!=FreeSpace.begin()&&(i->first > (k->first +k->second)))
            {
                QBrush a(Qt::blue);
                QGraphicsRectItem *tak = new QGraphicsRectItem();
                tak->setRect(k->first+k->second,0,i->first-k->first- k->second,100);
                tak->setBrush(a);
                scene->addItem(tak);
            }
         QGraphicsRectItem *l = new QGraphicsRectItem();
         l->setRect(i->first,0,i->second,100);
         QBrush fr(Qt::red);
         l->setBrush(fr);
         scene->addItem(l);
         QGraphicsTextItem * io = new QGraphicsTextItem();
         QGraphicsTextItem *ii = new QGraphicsTextItem();
         io->setRotation(-90);
         ii->setRotation(-90);
         QString s = QString::number(i->second);
         QString addressofhole = QString::number(i->first);
         if(i->second !=0)
         {

                 io->setPos(i->first+i->second/2-10,65);
                 io->setPlainText(s+"k");
                 scene->addItem(io);
              ii->setPos(i->first,150);
             ii->setPlainText(addressofhole+"k");
             scene->addItem(ii);
         }
        }
    for(QVector <process>::iterator i = AllocateSpace.begin();i!=AllocateSpace.end();i++)

    {
        if(i->getSize()!=0)
        {
        QGraphicsRectItem *l = new QGraphicsRectItem();
        QBrush all(Qt::green);
        QGraphicsTextItem * processName = new QGraphicsTextItem();
         QGraphicsTextItem *ProcessSize  = new QGraphicsTextItem();
         QGraphicsTextItem *Processadd  = new QGraphicsTextItem();
         ProcessSize->setRotation(-90);
         processName->setRotation(-90);
         Processadd->setRotation(-90);
        l->setRect(i->getAdd(),0,i->getSize(),100);
        double mid= i->getAdd()+i->getSize()/2-10;
        processName->setPos(mid,70);
        ProcessSize->setPos(mid,40);
        Processadd->setPos(i->getAdd(),150);
         QString s1 = QString::number(i->getId());
        processName->setPlainText("p"+s1);
        QString s2 = QString::number(i->getSize());
        QString s3 = QString::number(i->getAdd());
        ProcessSize->setPlainText(s2+"k");
        Processadd->setPlainText(s3+"k");
        l->setBrush(all);
        scene->addItem(l);
        scene->addItem(processName);
        scene->addItem(Processadd);
        scene->addItem(ProcessSize);
        }
    }

}
void MainWindow::on_Delete_clicked() //delete process
{
    int y = ui->lineEdit_4->text().toInt(); //get index
    ui->lineEdit_4->setText("");
    int fla =0;
    int x=0;//index
    int check =0;//check if there are ID or not
    for(QVector<process>::iterator i=AllocateSpace.begin();i!=AllocateSpace.end();i++)
    {
        if(i->getId()==y)
        {
            check=1;
            break;
        }else {
            x++;
        }
    }
    if(check==1)
    {

    for(QVector < QPair<double,double> >::iterator i=FreeSpace.begin();i!=FreeSpace.end();)
    {
        if(i!=FreeSpace.end())
        {
            QVector < QPair<double,double> >::iterator temp = i;
            temp++;
            //if befor this process  free and after it free
            if(((i->first + i->second) == AllocateSpace[x].getAdd()) &&
               (temp->first ==AllocateSpace[x].getAdd()+AllocateSpace[x].getSize()))
            {
                fla =1;
                i->second +=temp->second + AllocateSpace[x].getSize();
                FreeSpace.erase(temp);
                break;
            }
        }
        if(i->first ==AllocateSpace[x].getAdd()+AllocateSpace[x].getSize())
        {
            fla =1;
            i->first = AllocateSpace[x].getAdd();
            i->second +=AllocateSpace[x].getSize();
            break;
        }
        if((i->first +i->second) == AllocateSpace[x].getAdd())
        {
            fla =1;
            i->second +=AllocateSpace[x].getSize();
            break;
        }
        i++;
    }
    if(fla==0)
    {
        double neAddres= AllocateSpace[x].getAdd();
        double neSize= AllocateSpace[x].getSize();
        FreeSpace.push_back(qMakePair(neAddres,neSize));
        qSort(FreeSpace.begin(),FreeSpace.end());
    }
    AllocateSpace.remove(x);
    updateview();
    }else{

        QMessageBox m ;
        m.setText("ID not founded");
        m.exec();
    }
}




