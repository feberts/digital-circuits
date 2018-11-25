#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QCheckBox>
#include "devices/indicator.h"
#include "devices/signalsource.h"


class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:

        explicit MainWindow(QWidget * parent = nullptr);

    protected:

        void createNBitFullAdder(void);
        void createView(void);
        void updateSum(void);

        std::vector<SignalSource *> registerA;
        std::vector<SignalSource *> registerB;
        std::vector<Indicator *> registerS;

        std::vector<QCheckBox *> sum;
        QCheckBox * C;

        Indicator * carry;
};

#endif // MAINWINDOW_H
