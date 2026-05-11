#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFont>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    qputenv("QT_SCALE_FACTOR", "1.5");

    QFont defaultFont("Segoe UI", 11);
    QApplication::setFont(defaultFont);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QApplication a(argc, argv);

    /*QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "dmti_project_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }*/

    MainWindow w;
    w.show();
    return a.exec();
}
