#include "Storage.h"
#include <jatozy/model/AmpD10.h>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace jatozy::persistency_filesystem {
Storage::Storage(QString filePath)
    : m_filePath(std::move(filePath))
{}

auto Storage::load() -> void
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << m_filePath;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "Invalid data format in file:" << m_filePath;
    }

    QJsonArray ampsArray = doc.array();

    for (const auto &value : ampsArray) {
        if (!value.isObject())
            continue;

        QJsonObject obj = value.toObject();

        auto const id = obj.value("id").toString();
        auto const gain = static_cast<float>(obj.value("gain").toDouble());
        auto const mute = obj.value("mute").toBool();

        auto const amp = jatozy::model::AmpD10::PersistentData{id, gain, mute};

        m_snapshotD10.append(amp);
    }
}

auto Storage::store() const -> void
{
    QJsonArray ampsArray;

    for (const auto &amp : m_snapshotD10) {
        QJsonObject ampObject;
        ampObject["id"] = amp.id.toString();
        ampObject["gain"] = amp.gain;
        ampObject["mute"] = amp.mute;
        ampsArray.append(ampObject);
    }

    QJsonDocument doc(ampsArray);

    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Could not open file for writing:" << m_filePath;
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

auto Storage::getAmpsD10Snapshot() const -> SnapshotType const &
{
    return m_snapshotD10;
}

auto Storage::createSnapshot(jatozy::model::AmpD10Model const *const amps) -> void
{
    m_snapshotD10.clear();
    auto const &allAmps = amps->getAllAmps();

    m_snapshotD10.reserve(allAmps.size());

    for (auto const &amp : allAmps) {
        m_snapshotD10.append(
            jatozy::model::AmpD10::PersistentData{amp->id(), amp->gain(), amp->mute()});
    }
}
} // namespace jatozy::persistency_filesystem