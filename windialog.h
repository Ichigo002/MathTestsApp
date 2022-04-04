#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>
#include <QString>
#include <QtMath>

namespace Ui {
class WinDialog;
}

class WinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinDialog(int mistakes, int good, int total_time, int amount, QWidget *parent = nullptr);
    ~WinDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WinDialog *ui;
};

#endif // WINDIALOG_H
