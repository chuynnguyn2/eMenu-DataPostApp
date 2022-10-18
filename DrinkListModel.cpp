#include "DrinkListModel.h"
#include <QPixmap>
#include <QDebug>

DrinkListModel::DrinkListModel(QObject *parent):
    mFile(FileManager()),
    mDrinkList(mFile.drinkList())
{

}

void DrinkListModel::addDrink(const Drink &drink)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(),rowIndex,rowIndex);
    mDrinkList.append(drink);
    mFile.mdrinkList = mDrinkList;
    mFile.saveFile();
    endInsertRows();
}

int DrinkListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mDrinkList.size();
}

int DrinkListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant DrinkListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()|| role!=Qt::DisplayRole)
        return QVariant();
    const Drink& drink = mDrinkList.at(index.row());
    switch(index.column())
    {
    case 0: return drink.getId();
    case 1: return drink.getName();
    case 2: return drink.getUrl();
    case 3: return drink.getDescription();
    default: return QVariant();
    }
}

bool DrinkListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return false;
    Drink drink = mDrinkList.at(index.row());
    switch(index.column())
    {
    case 1: drink.setName(value.toString());break;
    case 2: drink.setUrl(value.toString());break;
    case 3: drink.setDescription(value.toString()); break;
    }
    return true;
    mDrinkList.replace(index.row(),drink);
    mFile.mdrinkList = mDrinkList;
    mFile.saveFile();
    emit dataChanged(index, index);
    return true;
}

bool DrinkListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    int countLeft = count;
    while (countLeft--)
    {
        mDrinkList.removeAt(row+countLeft);
        mFile.mdrinkList = mDrinkList;
        mFile.saveFile();
    }
    endRemoveRows();
    return true;
}
