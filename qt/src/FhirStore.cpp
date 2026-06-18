#include "FhirStore.h"

FhirStore::FhirStore(QObject *parent)
    : QObject(parent)
    , m_client(new FhirClient(this))
{
}

void FhirStore::search(const QString &family)
{
    if (m_isLoading)
        return;

    setError(QString());
    setIsLoading(true);

    m_client->searchPatients(family,
        [this](QList<Patient> patients, QString error) {
            if (error.isEmpty()) {
                setPatients(std::move(patients));
            } else {
                setPatients({});
                setError(std::move(error));
            }
            setIsLoading(false);
        });
}

void FhirStore::setPatients(QList<Patient> next)
{
    if (m_patients == next)
        return;
    m_patients = std::move(next);
    emit patientsChanged();
}

void FhirStore::setIsLoading(bool next)
{
    if (m_isLoading == next)
        return;
    m_isLoading = next;
    emit isLoadingChanged();
}

void FhirStore::setError(QString next)
{
    if (m_error == next)
        return;
    m_error = std::move(next);
    emit errorChanged();
}
