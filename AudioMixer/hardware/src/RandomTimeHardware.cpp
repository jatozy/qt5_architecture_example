#include "jatozy/hardware/RandomTimeHardware.h"
#include <QRandomGenerator>
#include <QTimer>

namespace jatozy::hardware {

RandomTimeHardware::RandomTimeHardware(QObject *parent)
    : jatozy::hardware_interface::Hardware(parent)
    , m_timer(std::make_shared<QTimer>())
{
    connect(m_timer.get(), &QTimer::timeout, this, [this]() {
        auto constexpr lower_border = 0;
        auto constexpr upper_border = 100;
        auto const input = QRandomGenerator::global()->bounded(lower_border, upper_border)
                           / static_cast<float>(upper_border);
        float const output = (m_mute) ? 0.0f : input * m_gain;
        emit inputLevelChanged(input);
        emit outputLevelChanged(output);
    });
    auto const inputChangeTime = QRandomGenerator::global()->bounded(100, 200);
    m_timer->start(inputChangeTime);
}

auto RandomTimeHardware::setGain(float const value) -> void
{
    m_gain = value;
}

auto RandomTimeHardware::gain() -> float
{
    return m_gain;
}

auto RandomTimeHardware::setMute(bool const value) -> void
{
    m_mute = value;
}

auto RandomTimeHardware::mute() -> bool
{
    return m_mute;
}

} // namespace jatozy::hardware