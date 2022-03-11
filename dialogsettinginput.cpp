#include "dialogsettinginput.h"
#include "ui_dialogsettinginput.h"

DialogSettingInput::DialogSettingInput(MainWindow* m, DialogSettingsMode mode, int v, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettingInput)
{
    ui->setupUi(this);
    setWindowTitle("Settings");
    this->m = m;
    this->mode = mode;

    ui->spinBox_amount->setValue(v);

    switch(mode)
    {
    case AmountInstanceMode:
        ui->label->setText("Set amount Instances, attempts:");
        ui->spinBox_amount->setMinimum(1);
        ui->spinBox_amount->setMaximum(100);
        break;
    case LowestNoMode:
        ui->label->setText("Set lowest number which can be used in attempts:");
        ui->spinBox_amount->setMinimum(1);
        ui->spinBox_amount->setMaximum(32456);
        break;
    case HighestNoMode:
        ui->label->setText("Set highest number which can be used in attempts:");
        ui->spinBox_amount->setMinimum(1);
        ui->spinBox_amount->setMaximum(32456);
        break;
    case AfterDecimalMode:
        ui->label->setText("Set places after the decimal:");
        ui->spinBox_amount->setMinimum(1);
        ui->spinBox_amount->setMaximum(10);
        break;
    }
}

DialogSettingInput::~DialogSettingInput()
{
    delete ui;
}

void DialogSettingInput::on_dbox_accepted()
{
    m->SetAmountProperty(ui->spinBox_amount->value(), mode);
}
