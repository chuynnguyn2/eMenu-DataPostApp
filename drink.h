#ifndef DRINK_H
#define DRINK_H
#include <QString>
#include <QJsonObject>

class Drink
{
public:
    explicit Drink(const QString& name = "");

    void setName (const QString& name);
    QString getName()const;
    void setUrl(const QString& url);
    QString getUrl()const;
    void setDescription(const QString& description);
    QString getDescription()const;
    void setId(int id);
    int getId()const;

    void write(QJsonObject& json)const;
    void read (const QJsonObject& json);

private:
    QString mName;
    QString mUrl;
    QString mDescription;
    int mId;
};

#endif // DRINK_H
