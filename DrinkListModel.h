#ifndef DRINKLISTMODEL_H
#define DRINKLISTMODEL_H

#include "FileManager.h"
#include "drink.h"
#include <QAbstractTableModel>

class DrinkListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    DrinkListModel(QObject* parent =0);

    void addDrink(const Drink& drink);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data (const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData (const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    FileManager mFile;
    QVector<Drink> mDrinkList;
};

#endif // DRINKLISTMODEL_H
