#include "FhirClient.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

FhirClient::FhirClient(QObject *parent, QString baseUrl)
    : QObject(parent)
    , m_nam(new QNetworkAccessManager(this))
    , m_base(std::move(baseUrl))
{
    while (m_base.endsWith(QLatin1Char('/')))
        m_base.chop(1);
}

void FhirClient::searchPatients(const QString &family, ResultCallback done)
{
    QUrl url(m_base + QStringLiteral("/Patient"));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("family"), family);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader("Accept", "application/fhir+json");

    QNetworkReply *reply = m_nam->get(request);

    QObject::connect(reply, &QNetworkReply::finished, this,
        [reply, done = std::move(done)]() mutable {
            QList<Patient> result;
            QString error;

            if (reply->error() != QNetworkReply::NoError) {
                error = reply->errorString();
            } else {
                QJsonParseError parseError;
                const QJsonDocument doc =
                    QJsonDocument::fromJson(reply->readAll(), &parseError);
                if (parseError.error != QJsonParseError::NoError) {
                    error = parseError.errorString();
                } else {
                    const QJsonObject bundle = doc.object();
                    const QJsonArray entries =
                        bundle.value(QStringLiteral("entry")).toArray();
                    result.reserve(entries.size());
                    for (const QJsonValue &v : entries) {
                        const QJsonObject resource =
                            v.toObject().value(QStringLiteral("resource")).toObject();
                        result.append(Patient::fromJson(resource));
                    }
                }
            }

            reply->deleteLater();
            done(std::move(result), std::move(error));
        });
}
