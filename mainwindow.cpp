#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gtbuffers_udp_d2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GtBuffers_UDP_D2 *udp=new GtBuffers_UDP_D2();
    CMD=new GtCommandInterface(this,udp);
    CMD->echo=true;
    connect(CMD,&GtCommandInterface::recv_cmd,this,&MainWindow::recv_cmd);
    connect(CMD,&GtCommandInterface::recv_accept,this,&MainWindow::recv_cmd);

    QTableWidgetItem *newItem = new QTableWidgetItem;
    newItem->setText("DEST");
    ui->tableWidget->setItem(0,0,newItem);
    newItem = new QTableWidgetItem;
    newItem->setText("UVK");
    ui->tableWidget->setItem(0,1,newItem);
    newItem = new QTableWidgetItem;
    newItem->setText("CMD");
    ui->tableWidget->setItem(1,0,newItem);
    newItem = new QTableWidgetItem;
    newItem->setText("SET_OTCEP_STATE");
    ui->tableWidget->setItem(1,1,newItem);
    newItem = new QTableWidgetItem;
    newItem->setText("N");
    ui->tableWidget->setItem(2,0,newItem);
    newItem = new QTableWidgetItem;
    newItem->setText("1");
    ui->tableWidget->setItem(2,1,newItem);
    newItem = new QTableWidgetItem;
    newItem->setText("MAR");
    ui->tableWidget->setItem(3,0,newItem);
    newItem = new QTableWidgetItem;
    newItem->setText("7");
    ui->tableWidget->setItem(3,1,newItem);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recv_cmd(QMap<QString, QString> m)
{
    QString S;
    foreach (QString key, m.keys()) {
        S=S+key+"="+m[key]+";";
    }
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(S);
    ui->listWidget->insertItem(0, newItem);

}

void MainWindow::on_pushButton_clicked()
{
    QMap<QString, QString> m;
    for (int i=0;i<ui->tableWidget->rowCount();i++){
        if (ui->tableWidget->item(i,0)==nullptr) continue;
        if (ui->tableWidget->item(i,0)->text().isEmpty()) continue;
        m[ui->tableWidget->item(i,0)->text()]=ui->tableWidget->item(i,1)->text();
    }
    CMD->send_cmd(m);

}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current!=nullptr){
        QMap<QString, QString> m=CMD->str2map(current->text());
        ui->tableWidget->clear();
        int r=0;
        ui->tableWidget->setRowCount( m.keys().size());
        foreach (QString key, m.keys()) {
            QTableWidgetItem *newItem = new QTableWidgetItem;
            newItem->setText(key);
            ui->tableWidget->setItem(r,0,newItem);
            newItem = new QTableWidgetItem;
            newItem->setText(m[key]);
            ui->tableWidget->setItem(r,1,newItem);
            r++;
        }

    }
}
