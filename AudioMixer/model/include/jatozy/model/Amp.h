#pragma once

#include <QObject>
#include <QUuid>

namespace jatozy::model {
class Amp : public QObject
{
    Q_OBJECT

public:
    using IdType = QUuid;

public:
    Q_PROPERTY(float gain READ gain NOTIFY gainChanged)
    Q_PROPERTY(bool mute READ mute NOTIFY muteChanged)
    Q_PROPERTY(float inputLevel READ inputLevel NOTIFY inputLevelChanged)
    Q_PROPERTY(float outputLevel READ outputLevel NOTIFY outputLevelChanged)
    Q_PROPERTY(QUuid id READ id NOTIFY idChanged)

public:
    struct PersistentData
    {
        IdType id;
        float gain;
        bool mute;
    };

public:
    explicit Amp(QObject *parent = nullptr);
    ~Amp() override = default;

    virtual auto gain() const -> float = 0;
    virtual auto setGain(float value) -> void = 0;
    virtual auto mute() const -> bool = 0;
    virtual auto setMute(bool const value) -> void = 0;
    virtual auto inputLevel() const -> float = 0;
    virtual auto outputLevel() const -> float = 0;
    virtual auto id() const -> IdType = 0;

signals:
    void gainChanged();
    void muteChanged();
    void inputLevelChanged();
    void outputLevelChanged();
    void idChanged();
};
} // namespace jatozy::model