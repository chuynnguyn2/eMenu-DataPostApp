#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <drink.h>

class QJsonObject;

class FileManager
{
public:    

    FileManager();
    bool saveFile();
    bool loadFile();

    void write(QJsonObject& json);
    void read(const QJsonObject& json);
    QVector<Drink> drinkList();

public:
    QVector<Drink> mdrinkList;
};

#endif // FILEMANAGER_H
