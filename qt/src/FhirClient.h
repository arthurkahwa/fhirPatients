#pragma once

#include "Patient.h"

#include <QList>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>

#include <functional>

class FhirClient : public QObject
{
    Q_OBJECT

public:
    using ResultCallback = std::function<void(QList<Patient>, QString /*error*/)>;

    explicit FhirClient(QObject *parent = nullptr,
                        QString baseUrl = QStringLiteral("https://hapi.fhir.org/baseR4"));

    void searchPatients(const QString &family, ResultCallback done);

private:
    QNetworkAccessManager *m_nam;
    QString m_base;
};
