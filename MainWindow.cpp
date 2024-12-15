#include "DataProcessor.h"
#include "ErrorHandler.h"
#include "FileParser.h"
#include "GraphRenderer.h"
#include "MainWindow.h"

#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , engine(new QQmlApplicationEngine(this))
{
    auto* fileParser = new FileParser(this);
    auto *errorHandler = new ErrorHandler(this);

    engine->rootContext()->setContextProperty("fileParser", fileParser);
    engine->rootContext()->setContextProperty("errorHandler", errorHandler);

    connect(fileParser, &FileParser::errorOccurred, errorHandler, &ErrorHandler::handleError);

    qmlRegisterType<GraphRenderer>("GraphRenderer", 1, 0, "GraphRenderer");

    engine->load(QUrl(QStringLiteral("qrc:/MainView.qml")));

    if (engine->rootObjects().isEmpty())
        qFatal("Не удалось загрузить QML файл.");
}

MainWindow::~MainWindow()
{
    delete engine;
}
