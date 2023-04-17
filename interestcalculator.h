#ifndef INTERESTCALCULATOR_H
#define INTERESTCALCULATOR_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QSpinBox; // discrete sets of values
class QComboBox; // list of options to the user
class QPushButton;

class interestCalculator : public QWidget
{
    Q_OBJECT

    // options
    QLabel *lblPrincipal;
    QLineEdit *editPrincipal;

    QLabel *lblDeposit;
    QLineEdit *editDeposit;

    QLabel *lblRate;
    QLineEdit *editRate;

    QLabel *lblTimePeriod;
    QSpinBox *spinTimePeriod;

    QLabel *lblFrequency;
    QComboBox *comboFrequency;

    // buttons
    QPushButton *btnCalculate;
    QPushButton *btnQuit;
    QPushButton *btnReset;

    void setupLayout();
    double frequencyToDouble(const QString &s);
public:
    interestCalculator(QWidget *parent = nullptr);
    ~interestCalculator();
public slots:
    void calculate();
    void reset();
};
#endif // INTERESTCALCULATOR_H
