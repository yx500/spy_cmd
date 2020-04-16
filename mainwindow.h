#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gtcommandinterface.h"

namespace Ui {
class MainWindow;
}
class QListWidgetItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    GtCommandInterface *CMD;
public slots:
     void recv_cmd(QMap<QString,QString> m);

private slots:
     void on_pushButton_clicked();

     void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
