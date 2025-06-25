#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "model.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Model model;
    Controller controller(&model);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("model", &model);
    engine.rootContext()->setContextProperty("controller", &controller);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("TicTacToe", "Main");

    return app.exec();
}
