#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include "gates/gateand.h"
#include "gates/gatexor.h"
#include "gates/gateor.h"

using namespace std;

const unsigned int NBIT = 8;


MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent),
      registerA({}),
      registerB({}),
      registerS({}),
      C(nullptr),
      carry(nullptr)
{
    createNBitFullAdder();
    createView();
}


void MainWindow::createView(void)
{
    this->setWindowTitle("N-Bit Full Adder");

    QHBoxLayout * hBox = new QHBoxLayout(this);
    hBox->setDirection(QBoxLayout::RightToLeft);

    for(unsigned nbit = 0; nbit < registerA.size(); nbit++)
    {
        QVBoxLayout * vBox = new QVBoxLayout(this);
        hBox->addItem(vBox);
        vBox->addWidget(new QLabel(to_string(nbit).c_str()));

        QCheckBox * A = new QCheckBox(this);
        QCheckBox * B = new QCheckBox(this);
        QCheckBox * S = new QCheckBox(this);
        vBox->addWidget(A);
        vBox->addWidget(B);
        vBox->addWidget(new QLabel("---"));
        vBox->addWidget(S);

        S->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        sum.push_back(S);

        QObject::connect(A, &QCheckBox::stateChanged, [=] ()
        {
            if(A->isChecked())
            {
                registerA.at(nbit)->setState(Signal::HIGH);
            }
            else
            {
                registerA.at(nbit)->setState(Signal::LOW);
            }

            updateSum();
        });

        QObject::connect(B, &QCheckBox::stateChanged, [=] ()
        {
            if(B->isChecked())
            {
                registerB.at(nbit)->setState(Signal::HIGH);
            }
            else
            {
                registerB.at(nbit)->setState(Signal::LOW);
            }

            updateSum();
        });
    }

    QVBoxLayout * vBox = new QVBoxLayout(this);
    hBox->addItem(vBox);
    C = new QCheckBox(this);
    C->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    vBox->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    vBox->addWidget(C);

    QWidget * widget = new QWidget(this);
    widget->setLayout(hBox);
    this->setCentralWidget(widget);
    this->resize(0, 0);
}


void MainWindow::updateSum()
{
    for(unsigned nbit = 0; nbit < registerS.size(); nbit++)
    {
        if(registerS.at(nbit)->getState() == Signal::HIGH)
        {
            sum.at(nbit)->setCheckState(Qt::Checked);
        }
        else
        {
            sum.at(nbit)->setCheckState(Qt::Unchecked);
        }
    }

    if(carry->getState() == Signal::HIGH)
    {
        C->setCheckState(Qt::Checked);
    }
    else
    {
        C->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::createNBitFullAdder(void)
{
    SignalSource * A = new SignalSource;
    SignalSource * B = new SignalSource;
    Indicator * S = new Indicator;

    GateAND * and1 = new GateAND;
    GateAND * and2 = new GateAND;
    GateXOR * xor1 = new GateXOR;
    GateXOR * xor2 = new GateXOR;
    GateOR * or1 = new GateOR;
    GateOR * or1_old = or1;

    registerA.push_back(A);
    registerB.push_back(B);
    registerS.push_back(S);

    A->connect(xor1, 1);
    A->connect(and2, 1);
    B->connect(xor1, 0);
    B->connect(and2, 0);
    xor1->connect(xor2, 1);
    xor1->connect(and1, 1);
    xor2->connect(S);
    and1->connect(or1, 1);
    and2->connect(or1, 0);

    for(unsigned int nbit = 1; nbit < NBIT; nbit++)
    {
        and1 = new GateAND;
        and2 = new GateAND;
        xor1 = new GateXOR;
        xor2 = new GateXOR;
        or1 = new GateOR;

        A = new SignalSource;
        B = new SignalSource;
        S = new Indicator;

        registerA.push_back(A);
        registerB.push_back(B);
        registerS.push_back(S);

        A->connect(xor1, 1);
        A->connect(and2, 1);
        B->connect(xor1, 0);
        B->connect(and2, 0);
        or1_old->connect(xor2, 0);
        or1_old->connect(and1, 0);
        xor1->connect(xor2, 1);
        xor1->connect(and1, 1);
        xor2->connect(S);
        and1->connect(or1, 1);
        and2->connect(or1, 0);

        or1_old = or1;
    }

    carry = new Indicator;
    or1->connect(carry);
}



