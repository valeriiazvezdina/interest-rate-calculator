#include "interestcalculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interestCalculator w;
    w.show();
    return a.exec();
}
