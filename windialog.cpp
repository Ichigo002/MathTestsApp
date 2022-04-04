#include "windialog.h"
#include "ui_windialog.h"

WinDialog::WinDialog(int mistakes, int good, int total_time, int amount, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinDialog)
{
    ui->setupUi(this);

    float avg = total_time / amount;
    avg *= 100;
    avg = round(avg);
    avg /= 100;

    ui->line_mistake->setText("Mistakes: " + QString::number(mistakes));
    ui->line_good->setText("Good: " + QString::number(good));
    ui->line_total->setText("Total Time: " + QString::number(total_time));
    ui->line_avg->setText("Avg Time: " + QString::number(avg));
}

WinDialog::~WinDialog()
{
    delete ui;
}

void WinDialog::on_pushButton_clicked()
{
    accept();
}

