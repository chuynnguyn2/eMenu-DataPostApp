#include "FileManager.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QStandardPaths>
#include <QJsonDocument>

FileManager::FileManager()
{

}

bool FileManager::saveFile()
{
    QString fileName = QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation))+"drinklist.json";
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
        return false;
    QJsonObject drinkListObject;
    write (drinkListObject);
    file.write(QJsonDocument(drinkListObject).toJson());
    return true;
}

bool FileManager::loadFile()
{
    QString fileName = QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation))+"drinklist.json";
    QFile file (fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    read(loadDoc.object());
    return true;
}

void FileManager::write(QJsonObject &json)
{
    QJsonArray drinkArray;
    int index=0;
    for (Drink& drink : mdrinkList)
    {
        drink.setId(index);
        QJsonObject drinkObject;
        drink.write(drinkObject);
        drinkArray.append(drinkObject);
        index++;
    }
    json["drinklist"] = drinkArray;
}

void FileManager::read(const QJsonObject &json)
{
    if (json.contains("drinklist") && json["drinklist"].isArray()) {
        QJsonArray drinkArray = json["drinklist"].toArray();
        mdrinkList.clear();
        mdrinkList.reserve(drinkArray.size());
        for (int drinkIndex = 0; drinkIndex < drinkArray.size(); ++drinkIndex)
        {
            QJsonObject drinkObject = drinkArray[drinkIndex].toObject();
            Drink drink;
            drink.read(drinkObject);
            mdrinkList.append(drink);
        }
    }
}

QVector<Drink> FileManager::drinkList()
{
    loadFile();
    return mdrinkList;
}
