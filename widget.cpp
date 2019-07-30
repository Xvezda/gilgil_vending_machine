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
    if (money < COFFEE) {  // If money not enough for all items
        disableAllButtons();  // Disable all buttons
    } else if (COFFEE <= money && money < TEA) {
        enableButton(ui->pbCoffee);
        disableButton(ui->pbTea);
        disableButton(ui->pbCoke);
    } else if (TEA <= money && money < COKE) {
        enableButton(ui->pbCoffee);
        enableButton(ui->pbTea);
        disableButton(ui->pbCoke);
    } else {
        enableButton(ui->pbCoffee);
        enableButton(ui->pbTea);
        enableButton(ui->pbCoke);
    }
}

void Widget::disableAllButtons(void)
{
    for (std::vector<QPushButton*>::iterator it = buttons.begin();
         it != buttons.end(); it++) {
        disableButton(*it);
    }
}

void Widget::disableButton(QPushButton* button)
{
    button->setEnabled(false);
}

void Widget::enableButton(QPushButton* button)
{
    button->setEnabled(true);
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
    ui->pbCoke->setEnabled(false);
    QMessageBox msg;
    msg.information(nullptr, QString("Error"), QString("XXX"));
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
