#include <jatozy/event_handler/EventHandler.h>
#include <jatozy/hardware/RandomTimeFactory.h>
#include <jatozy/model/AmpD10Model.h>
#include <jatozy/model/UndoStackModel.h>
#include <jatozy/persistency_filesystem/Factory.h>
#include <jatozy/store/Store.h>
#include <memory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Q_INIT_RESOURCE(qml);
    qRegisterMetaType<jatozy::model::AmpD10Model *>("jatozy::model::AmpD10Model*");
    qRegisterMetaType<jatozy::model::UndoStackModel *>("jatozy::model::UndoStackModel*");

    auto hardwareFactory = std::make_shared<jatozy::hardware::RandomTimeFactory>();
    auto persistencyFactory = std::make_shared<jatozy::persistency_filesystem::Factory>(
        "amps.json");
    auto store = std::make_shared<jatozy::store::Store>(hardwareFactory, persistencyFactory);
    auto eventHandler = std::make_shared<jatozy::event_handler::EventHandler>(store);

    store->load();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationState", store->stateRaw());
    engine.rootContext()->setContextProperty("eventHandler", eventHandler.get());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
