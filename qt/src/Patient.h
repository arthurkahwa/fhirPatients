#pragma once

#include "HumanName.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QString>
#include <QtQml/qqmlregistration.h>

class Patient
{
    Q_GADGET
    QML_VALUE_TYPE(patient)

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QList<HumanName> name MEMBER name)
    Q_PROPERTY(QString birthDate MEMBER birthDate)
    Q_PROPERTY(QString gender MEMBER gender)
    Q_PROPERTY(QString displayName READ displayName)

public:
    QString id;
    QList<HumanName> name;
    QString birthDate;
    QString gender;

    bool operator==(const Patient &other) const
    {
        return id == other.id
            && name == other.name
            && birthDate == other.birthDate
            && gender == other.gender;
    }

    QString displayName() const
    {
        return name.isEmpty() ? QStringLiteral("—") : name.first().display();
    }

    static Patient fromJson(const QJsonObject &obj)
    {
        Patient out;
        out.id = obj.value(QStringLiteral("id")).toString();
        out.birthDate = obj.value(QStringLiteral("birthDate")).toString();
        out.gender = obj.value(QStringLiteral("gender")).toString();

        const QJsonArray names = obj.value(QStringLiteral("name")).toArray();
        out.name.reserve(names.size());
        for (const QJsonValue &v : names)
            out.name.append(HumanName::fromJson(v.toObject()));

        return out;
    }
};

Q_DECLARE_METATYPE(Patient)
