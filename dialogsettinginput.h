#ifndef DIALOGSETTINGINPUT_H
#define DIALOGSETTINGINPUT_H

#include <QDialog>
#include <mainwindow.h>
#include "EnumsStructs.h"

namespace Ui {
class DialogSettingInput;
}

class DialogSettingInput : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettingInput(MainWindow* m, DialogSettingsMode mode, int v, QWidget *parent = nullptr);
    ~DialogSettingInput();

private slots:
    void on_dbox_accepted();

private:
    Ui::DialogSettingInput *ui;
    MainWindow* m;
    DialogSettingsMode mode;
};

#endif // DIALOGSETTINGINPUT_H
