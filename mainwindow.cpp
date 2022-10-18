#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QPixmap>
#include <QItemSelectionModel>
#include <QFileDialog>

#include "DrinkListModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mDrinkListModel(new DrinkListModel(this)),
      mSelectionModel(new QItemSelectionModel(mDrinkListModel,this))
{
    ui->setupUi(this);
    ui->tableView->setModel(mDrinkListModel);
    ui->tableView->setSelectionModel(mSelectionModel);
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    initEvent();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initEvent()
{
    connect (ui->pb_Add, &QPushButton::clicked, this, &MainWindow::addDrink);
    connect (ui->pb_FileUrl, &QPushButton::clicked, this, &MainWindow::getFileUrl);
    connect (ui->pb_Delete, &QPushButton::clicked, this, &MainWindow::deleteDrink);
    connect (ui->pb_Add, &QPushButton::clicked, this, &MainWindow::clearUi);
}

void MainWindow::addDrink()
{
    Drink drink;
    mDrink.setName(ui->le_Name->text());
    mDrink.setDescription(ui->le_description->toPlainText());
    mDrinkListModel->addDrink(mDrink);
}

void MainWindow::getFileUrl()
{
    QString picturesFolder = (QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    QString fileUrl = QFileDialog::getOpenFileName(this, tr("Select Image"),
                                                   picturesFolder,
                                                   "Picture files (*.jpg *.png)");
    mDrink.setUrl(fileUrl);
    QPixmap pixmap(fileUrl);
    ui->lb_Picture->setPixmap(pixmap.scaled(ui->lb_Picture->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::deleteDrink()
{
    QModelIndex index = mSelectionModel->currentIndex();
    mDrinkListModel->removeRows(index.row(),1,QModelIndex());
}

void MainWindow::clearUi()
{
    ui->le_Name->clear();
    ui->le_description->clear();
}


