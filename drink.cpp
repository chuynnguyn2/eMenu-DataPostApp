#include "drink.h"

Drink::Drink(const QString &name):
    mName(name),
    mUrl("qrc:/images/Res/istockphoto-1276735653-612x612.jpg"),
    mDescription(""),
    mId(-1)
{

}

void Drink::setName(const QString &name)
{
    mName = name;
}

QString Drink::getName() const
{
    return mName;
}

void Drink::setUrl(const QString &url)
{
    mUrl = url;
}

QString Drink::getUrl() const
{
    return mUrl;
}

void Drink::setDescription(const QString &description)
{
    mDescription = description;
}

QString Drink::getDescription() const
{
    return mDescription;
}

void Drink::setId(int id)
{
    mId = id;
}

int Drink::getId() const
{
    return mId;
}

void Drink::write(QJsonObject &json) const
{
    json["id"] = mId;
    json["name"] = mName;
    json["url"] = mUrl;
    json["description"] = mDescription;

}

void Drink::read(const QJsonObject &json)
{
    if (json.contains("id"))
    {
        mName = json["name"].toInt();
    }
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
    if (json.contains("url") && json["url"].isString())
    {
        mUrl = json["url"].toString();
    }
    if (json.contains("description")&&json["description"].isString())
    {
        mDescription = json["description"].toString();
    }
}
