#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void changeMoney(int n);
    void displayMoney(void);
    void setMoney(int n);
    int getMoney(void);

    void disableAllButtons(void);
    void enableButton(QPushButton* button);
    void disableButton(QPushButton* button);
    void updateButtons(void);

private slots:
    void on_pb10_clicked();

    void on_pb50_clicked();

    void on_pb100_clicked();

    void on_pb500_clicked();

    void on_pbCoffee_clicked();

    void on_pbTea_clicked();

    void on_pbCoke_clicked();

private:
    Ui::Widget *ui;
    std::vector<QPushButton*> buttons;

    int money {0};
};

#endif // WIDGET_H
