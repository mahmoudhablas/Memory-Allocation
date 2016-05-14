#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <process.h>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsScene *scene;
   void setFree( QVector <QPair < double,double > > );


private slots:
    void on_insert_clicked();
    void on_Show_clicked();

    void on_Add_clicked();
    void firstfit(double si);
    void bestfit(double s);
    void updateview();
    void on_Delete_clicked();
    void worstfit(double s);
    QVector <QPair < double,double > > getFree();
     void know();

private:
    Ui::MainWindow *ui;
    QVector <QPair < double,double > > FreeSpace;
    QVector <process> AllocateSpace;
    static int id;
   // QVector<QPair<double,double > > initial;
};

#endif // MAINWINDOW_H
