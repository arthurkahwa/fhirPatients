#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QtQml/qqmlregistration.h>

class HumanName
{
    Q_GADGET
    QML_VALUE_TYPE(humanName)

    Q_PROPERTY(QStringList given MEMBER given)
    Q_PROPERTY(QString family MEMBER family)
    Q_PROPERTY(QString display READ display)

public:
    QStringList given;
    QString family;

    bool operator==(const HumanName &other) const
    {
        return given == other.given && family == other.family;
    }

    QString display() const
    {
        QStringList parts = given;
        if (!family.isEmpty())
            parts << family;
        const QString joined = parts.join(QLatin1Char(' '));
        return joined.isEmpty() ? QStringLiteral("—") : joined;
    }

    static HumanName fromJson(const QJsonObject &obj)
    {
        HumanName out;
        const QJsonArray givenArr = obj.value(QStringLiteral("given")).toArray();
        out.given.reserve(givenArr.size());
        for (const QJsonValue &v : givenArr)
            out.given.append(v.toString());
        out.family = obj.value(QStringLiteral("family")).toString();
        return out;
    }
};

Q_DECLARE_METATYPE(HumanName)
