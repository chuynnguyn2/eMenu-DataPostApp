#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drink.h"

#include <QItemSelectionModel>

class DrinkListModel;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initEvent();

    void addDrink();
    void getFileUrl();
    void deleteDrink();
    void updateDrink();

    void clearUi();

private:
    Ui::MainWindow *ui;
    Drink mDrink;
    DrinkListModel* mDrinkListModel;
    QItemSelectionModel* mSelectionModel;
};
#endif // MAINWINDOW_H
