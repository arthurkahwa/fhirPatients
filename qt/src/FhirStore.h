#pragma once

#include "FhirClient.h"
#include "Patient.h"

#include <QList>
#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

class FhirStore : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QList<Patient> patients READ patients NOTIFY patientsChanged)
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY isLoadingChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

public:
    explicit FhirStore(QObject *parent = nullptr);

    QList<Patient> patients() const { return m_patients; }
    bool isLoading() const { return m_isLoading; }
    QString error() const { return m_error; }

    Q_INVOKABLE void search(const QString &family);

signals:
    void patientsChanged();
    void isLoadingChanged();
    void errorChanged();

private:
    void setPatients(QList<Patient> next);
    void setIsLoading(bool next);
    void setError(QString next);

    FhirClient *m_client;
    QList<Patient> m_patients;
    bool m_isLoading = false;
    QString m_error;
};
