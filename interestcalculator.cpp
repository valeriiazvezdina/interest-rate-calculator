#include "interestcalculator.h"

#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

interestCalculator::interestCalculator(QWidget *parent)
    : QWidget(parent)
{
    // settings the main window
    setStyleSheet("background-color:gray;");
    setFixedSize(270,250);
    setWindowTitle(tr("interest calculator"));
    setupLayout();
}

interestCalculator::~interestCalculator()
{
}

void interestCalculator::setupLayout()
{
    // two main box layout
    QVBoxLayout *lMain = new QVBoxLayout;
    QVBoxLayout *lTop = new QVBoxLayout;

    // principal amount
    QHBoxLayout *lPrincipal = new QHBoxLayout;
    lblPrincipal = new QLabel(tr("principal amount: "));
    editPrincipal = new QLineEdit;

    editPrincipal->setPlaceholderText("0");

    // validation
    editPrincipal->setValidator(new QRegExpValidator(QRegExp("^(0|([1-9][0-9]*))(\\.[0-9]+)"), this));

    lPrincipal->addWidget(lblPrincipal);
    lPrincipal->addWidget(editPrincipal);

    // deposit
    QHBoxLayout *lDeposit = new QHBoxLayout;
    lblDeposit = new QLabel(tr("deposit: "));
    editDeposit = new QLineEdit;

    editDeposit->setPlaceholderText("0");

    //validation
    editDeposit->setValidator(new QRegExpValidator(QRegExp("^(0|([1-9][0-9]*))(\\.[0-9]+)"), this));

    lDeposit->addWidget(lblDeposit);
    lDeposit->addWidget(editDeposit);

    // interest rate
    QHBoxLayout *lRate = new QHBoxLayout;
    lblRate = new QLabel(tr("interest rate (in %): "));
    editRate = new QLineEdit;

    editRate->setPlaceholderText("0");

    // validation
    editRate->setValidator(new QRegExpValidator(QRegExp("^(0|([1-9][0-9]*))(\\.[0-9]+)"), this));
    lRate->addWidget(lblRate);
    lRate->addWidget(editRate);

    // frequency
    QHBoxLayout *lFrequency = new QHBoxLayout;
    lblFrequency = new QLabel(tr("frequency: "));
    comboFrequency = new QComboBox;

    comboFrequency->addItem(tr("---"));
    comboFrequency->addItem(tr("monthly"));
    comboFrequency->addItem(tr("quarterly"));
    comboFrequency->addItem(tr("yearly"));

    lFrequency->addWidget(lblFrequency);
    lFrequency->addWidget(comboFrequency);

    // time period
    QHBoxLayout *lTimePeriod = new QHBoxLayout;
    lblTimePeriod = new QLabel(tr("time period (in years): "));
    spinTimePeriod = new QSpinBox;

    spinTimePeriod->setRange(1,10);

    lTimePeriod->addWidget(lblTimePeriod);
    lTimePeriod->addWidget(spinTimePeriod);

    // buttons
    QHBoxLayout *lButtons = new QHBoxLayout;
    btnCalculate = new QPushButton(tr("calc"));
    btnReset = new QPushButton(tr("reset"));
    btnQuit = new QPushButton(tr("quit"));

    lButtons->addWidget(btnCalculate);
    lButtons->addWidget(btnReset);
    lButtons->addWidget(btnQuit);

    // adding to lTop
    lTop->addLayout(lPrincipal);
    lTop->addLayout(lDeposit);
    lTop->addLayout(lRate);
    lTop->addLayout(lFrequency);
    lTop->addLayout(lTimePeriod);

    // adding to lMain
    lMain->addLayout(lTop);
    lMain->addLayout(lButtons);

    setLayout(lMain);

    // connecting tle slots for the buttons
    connect(btnCalculate, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(btnQuit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btnReset, SIGNAL(clicked()), this, SLOT(reset()));

}

double interestCalculator::frequencyToDouble(const QString &s)
{
    if (s == "monthly") return 12.0;
    if (s == "quarterly") return 3.0;
    if (s == "yearly") return 1.0;
    return 0.0;
}

void interestCalculator::calculate()
{
    bool ok;
    double result = 0.0;

    double principal = editPrincipal->text().toDouble(&ok);
    if (!ok || !principal)
    {
        QMessageBox::warning(this, tr("wrong input"), tr("please enter the principal amount"));
        return;
    }

    double deposit = editDeposit->text().toDouble(&ok);
    if (!ok || !deposit)
    {
        QMessageBox::warning(this, tr("wrong input"), tr("if you do not enter the deposit, it will be automatically equal to 0"));
        deposit = 0;
    }

    double rate = editRate->text().toDouble(&ok);
    if (!ok || !rate)
    {
        QMessageBox::warning(this, tr("wrong input"), tr("please enter the rate"));
        return;
    }

    double frequency = frequencyToDouble(comboFrequency->currentText());
    if (!frequency)
    {
        QMessageBox::warning(this, tr("wrong input"), tr("please select the frequency"));
        return;
    }

    double period = spinTimePeriod->value();

    for (int i = 1; i <= (period * frequency); i++)
    {
        result = principal * pow((1 + ((rate / 100) / frequency)), i);
        result += deposit * i;
    }

    QMessageBox::information(this, tr("result"), tr("interest amount is: %1").arg(result));
}

void interestCalculator::reset()
{
    // all options are zero
    editPrincipal->setText("0");
    editDeposit->setText("0");
    editRate->setText("0");
    comboFrequency->setCurrentIndex(0);
    spinTimePeriod->setValue(0);
}
