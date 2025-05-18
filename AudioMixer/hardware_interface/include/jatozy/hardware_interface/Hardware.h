#pragma once

#include <QObject>

namespace jatozy::hardware_interface {
class Hardware : public QObject
{
    Q_OBJECT

public:
    explicit Hardware(QObject *parent = nullptr);
    ~Hardware() override = default;

    virtual auto setGain(float const value) -> void = 0;
    virtual auto gain() -> float = 0;
    virtual auto setMute(bool const value) -> void = 0;
    virtual auto mute() -> bool = 0;

signals:
    auto gainChanged(float value) -> void;
    auto inputLevelChanged(float value) -> void;
    auto outputLevelChanged(float value) -> void;
    auto muteChanged(bool value) -> void;
};
} // namespace jatozy::hardware_interface