#include <QApplication>
#include "MyGame.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyGame window;
    window.show();

    return app.exec();
}
