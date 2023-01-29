#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMenuBar"
#include "QDialog"
#include "QPushButton"
#include "pcb.h"
#include "vector"
#include "time.h"
#include "algorithm"
#include "QDebug"
#include "QFont"
#include "QBrush"
using namespace std;

static vector<PCB*> readyQueue;
static vector<PCB*> runningQueue;
static vector<PCB*> finishQueue;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(850,666);
    setWindowTitle("模拟操作系统");


    //创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);    //菜单栏放入窗口
    QMenu *processMenu = bar->addMenu("进程管理"); //创建菜单
    processMenu->addSeparator(); //添加分隔符
    QMenu *memoryMenu = bar->addMenu("内存管理");

    //进程表格
    ui->processtable->setColumnCount(5);
    QStringList tableheader;
    tableheader<<"进程标识码"<<"优先级"<<"占用CPU时间"<<"还需CPU时间"<<"进程状态";
    ui->processtable->horizontalHeader()->setMinimumHeight(50);
    ui->processtable->setHorizontalHeaderLabels(tableheader);
    ui->processtable->verticalHeader()->setVisible(false);
    ui->processtable->setAlternatingRowColors(true);
    ui->processtable->setSelectionBehavior(QAbstractItemView::SelectRows);      //设置选择每行且单元不可编辑
    ui->processtable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->processtable->setEditTriggers(QAbstractItemView::NoEditTriggers);



    srand(time(nullptr));
    Random_Create_PCB();
    showProcess();




}

MainWindow::~MainWindow()
{
    delete ui;
}



//展示进程
void MainWindow::showProcess(){
    for(int i=0;i<readyQueue.size();i++){
        int nCount = ui->processtable->rowCount();
        ui->processtable->insertRow(nCount);
        ui->processtable->setItem(i,0,new QTableWidgetItem(QString("%1").arg(readyQueue[i]->name)));
        ui->processtable->setItem(i,1,new QTableWidgetItem(QString("%1").arg(readyQueue[i]->prio)));
        ui->processtable->setItem(i,2,new QTableWidgetItem(QString("%1").arg(readyQueue[i]->cpuTime)));
        ui->processtable->setItem(i,3,new QTableWidgetItem(QString("%1").arg(readyQueue[i]->needTime)));
        ui->processtable->setItem(i,4,new QTableWidgetItem(QString("%1").arg(readyQueue[i]->state)));
        for(int j=0;j<5;j++){
            ui->processtable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->processtable->item(i,j)->setBackground(QBrush(QColor(255,244,196)));
        }
    }
}

void MainWindow::Random_Create_PCB(){
    for(int i=0;i<8;i++){
        PCB* p = nullptr;
        insertReadyQueue(p,i);
    }
}

//按照优先级从大到小排序
bool MainWindow::compare(PCB* a,PCB* b){
    return a->prio > b->prio;
}

void MainWindow::insertReadyQueue(PCB* process,int name){
    process = (PCB *) malloc(sizeof(PCB));

    process->name = name;
    process->needTime = rand()%50;
    process->prio = maxPrio - process->needTime;
    process->round = 5;
    process->cpuTime = 0;
    strcpy(process->state, "ready");    //默认创建的新进程是就绪状态
    //根据优先级排序，放入就绪队列
    readyQueue.push_back(process);
    sort(readyQueue.begin(),readyQueue.end(),compare);
}


//创建进程按钮槽
void MainWindow::on_createprocess_clicked()
{
    int currentRow = ui->processtable->currentRow();
    ui->processtable->insertRow(currentRow+1);
//    QDialog *newProcessDialog = new QDialog();
//    newProcessDialog->setFixedSize(500,400);
//    newProcessDialog->setAttribute(Qt::WA_DeleteOnClose);
//    newProcessDialog->setWindowTitle("创建进程");

//    newProcessDialog->show();
}

void MainWindow::on_deleteprocess_clicked()
{
    int currentRow = ui->processtable->currentRow();
    ui->processtable->removeRow(currentRow);
}

void MainWindow::on_start_clicked()
{
    ui->processtable->setRowCount(0);
    readyQueue.clear();
    Random_Create_PCB();
    showProcess();
}
