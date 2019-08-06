#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>

enum Price
{
    COFFEE = 100,
    TEA = 150,
    COKE = 200
};

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    buttons.push_back(ui->pbCoffee);
    buttons.push_back(ui->pbTea);
    buttons.push_back(ui->pbCoke);

    updateButtons();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateButtons(void)
{
    ui->pbCoffee->setEnabled(money >= COFFEE);
    ui->pbTea->setEnabled(money >= TEA);
    ui->pbCoke->setEnabled(money >= COKE);
}

void Widget::setMoney(int n)
{
    if (n < 0) {
        QMessageBox msg;
        msg.information(nullptr,
            QString("Error"), QString("Not enough money!"));
        return;
    }
    money = n;
    // Update display
    displayMoney();
    updateButtons();
}

int Widget::getMoney(void)
{
    return money;
}

void Widget::displayMoney(void)
{
    ui->lcdNumber->display(money);
}

void Widget::changeMoney(int n)
{
    setMoney(getMoney() + n);
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-COFFEE);
}

void Widget::on_pbTea_clicked()
{
    changeMoney(-TEA);
}

void Widget::on_pbCoke_clicked()
{
    changeMoney(-COKE);
}

void Widget::on_pbReset_clicked()
{
    int money_500 = (!getMoney()) ? 0 : getMoney() / 500;
    changeMoney(money_500*500*-1);
    int money_100 = (!getMoney()) ? 0 : getMoney() / 100;
    changeMoney(money_100*100*-1);
    int money_50 = (!getMoney()) ? 0 : getMoney() / 50;
    changeMoney(money_50*50*-1);
    int money_10 = (!getMoney()) ? 0 : getMoney() / 10;
    changeMoney(money_10*10*-1);

    QMessageBox msg;
    msg.information(nullptr,
        QString("Result"),
        QString("500 won: %1\n"
                "100 won: %2\n"
                " 50 won: %3\n"
                " 10 won: %4\n")
                    .arg(money_500)
                    .arg(money_100)
                    .arg(money_50)
                    .arg(money_10));

    setMoney(0);
}
