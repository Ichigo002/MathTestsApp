#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialogsettinginput.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName("Horisan");
    QCoreApplication::setOrganizationDomain("naomi03.ga");
    QCoreApplication::setApplicationName("Math Operations Tester");

    ui->setupUi(this);
    action_flags = Multiplication | Addition | Subtraction;
    ins_left = 0;

    LoadSettings();
    EndGame();
}

MainWindow::~MainWindow()
{
    SaveSettings();
    delete ui;
}

void MainWindow::SaveSettings()
{
    QSettings sett;
    sett.setValue("amount", amount_ins);
    sett.setValue("min", min_no);
    sett.setValue("max", max_no);
    sett.setValue("dec", places_after_dec);
    sett.setValue("fltg", floating);
    sett.setValue("neg-freq", neg_freq);
}

void MainWindow::LoadSettings()
{
    QSettings sett;
    amount_ins = sett.value("amount").toInt();
    min_no = sett.value("min").toInt();
    max_no = sett.value("max").toInt();
    places_after_dec = sett.value("dec").toInt();
    floating = sett.value("fltg").toBool();

    int v = sett.value("neg-freq").toInt();
    switch(v)
    {
    case 1:
        neg_freq = Always;
        break;
    case 0:
        neg_freq = Sometimes;
        break;
    case -1:
        neg_freq = Never;
        break;
    default:
        QMessageBox::critical(this, "Error Load Settings", "Loading value 'neg-freq' from 'fltg' failed.");
        break;
    }

    SetSettingsForMenu();
}

// GAME MENU
void MainWindow::on_actionNew_Game_triggered()
{
    ins_left = amount_ins;
    NextTurn();
}

void MainWindow::on_actionPause_Game_triggered()
{

}

void MainWindow::on_actionEnd_Game_triggered()
{
    EndGame();
}

// SET SETTINGGS
void MainWindow::on_actionReturn_Default_Settings_triggered()
{
    //Set defaults settings
    amount_ins = 8;
    min_no = 1;
    max_no = 10;
    floating = false;
    places_after_dec = 1;
    neg_freq = Never;

    SetSettingsForMenu();
}

void MainWindow::SetSettingsForMenu()
{
    ui->actionmultiplication->setChecked(action_flags & Multiplication);
    ui->actionDivision->setChecked(action_flags & Division);
    ui->actionAddition->setChecked(action_flags & Addition);
    ui->actionSubtraction->setChecked(action_flags & Subtraction);

    ui->actionFloating_numbers_2->setChecked(floating);
    CheckNegFreqMenu(neg_freq);
}

void MainWindow::SetAmountProperty(int prop, DialogSettingsMode m)
{
    switch(m)
    {
    case AmountInstanceMode:
            amount_ins = prop;
        break;
    case LowestNoMode:
        min_no = prop;
        break;
    case HighestNoMode:
        max_no = prop;
        break;
    case AfterDecimalMode:
        places_after_dec = prop;
        break;
    }
}

// NEGATIVE NUMBERS MENU
void MainWindow::CheckNegFreqMenu(NegativeFreq nf)
{
    ui->actionAlways->setChecked(nf == Always);
    ui->actionSometimes->setChecked(nf == Sometimes);
    ui->actionNever->setChecked(nf == Never);
    neg_freq = nf;
}

void MainWindow::on_actionAlways_triggered()
{
    CheckNegFreqMenu(Always);
}

void MainWindow::on_actionSometimes_triggered()
{
    CheckNegFreqMenu(Sometimes);
}

void MainWindow::on_actionNever_triggered()
{
    CheckNegFreqMenu(Never);
}

//AMOUNT INSTANCES BUTTON
void MainWindow::on_actionAmount_Instances_triggered()
{
    DialogSettingInput dialog(this, AmountInstanceMode, amount_ins);
    dialog.exec();
}

// LIMITS MENU
void MainWindow::on_actionLowest_Number_triggered()
{
    DialogSettingInput dialog(this, LowestNoMode, min_no);
    dialog.exec();
}

void MainWindow::on_actionHighest_Number_triggered()
{
    DialogSettingInput dialog(this, HighestNoMode, max_no);
    dialog.exec();
}

//FLOATING NUMBERS MENU
void MainWindow::on_actionDigits_After_The_Decimal_triggered()
{
    DialogSettingInput dialog(this, AfterDecimalMode, places_after_dec);
    dialog.exec();
}

void MainWindow::on_actionFloating_numbers_2_triggered()
{
    floating = ui->actionFloating_numbers_2->isChecked();
}

//ACTIONS MENU

void MainWindow::on_actionmultiplication_triggered(bool checked)
{
    if(checked)
        action_flags += Multiplication;
    else
        action_flags -= Multiplication;
}


void MainWindow::on_actionDivision_triggered(bool checked)
{
    if(checked)
        action_flags += Division;
    else
        action_flags -= Division;
}


void MainWindow::on_actionAddition_triggered(bool checked)
{
    if(checked)
        action_flags += Addition;
    else
        action_flags -= Addition;
}


void MainWindow::on_actionSubtraction_triggered(bool checked)
{
    if(checked)
        action_flags += Subtraction;
    else
        action_flags -= Subtraction;
}

//GUI
void MainWindow::on_btn_done_clicked()
{
    if(ins_left <= 0)
    {
        EndGame();
        return;
    }
    qDebug() << " Correct: " + QString::number(correct_result) << ". Input: " + ui->edit_input->text();
    if(QString::number(correct_result) == ui->edit_input->text())
    {
        NextTurn();
        ui->edit_input->setText("");
    }
    else
    {
        QMessageBox::information(this, "Info!", "You are wrong! Correct result is " + QString::number(correct_result));
        NextTurn();
        ui->edit_input->setText("");
    }
}


void MainWindow::on_btn_giveUp_clicked()
{
    QMessageBox::critical(this, "LOOOOOOOOSER!", "You losed looser... I don't wanna see you bitch!");
    EndGame();
}

// GAME
void MainWindow::NextTurn()
{
    if(ins_left <= 0)
        return;

    float rand_a = QRandomGenerator::global()->generateDouble() * (max_no - min_no + 1) + min_no;
    float rand_b = QRandomGenerator::global()->generateDouble() * (max_no - min_no + 1) + min_no;
    float a, b;

    if(floating)
    {
        int factor = pow(10, places_after_dec);
        a = round(rand_a * factor) / factor;
        b = round(rand_b * factor) / factor;
    }
    else
    {
        a = trunc(rand_a);
        b = trunc(rand_b);
    }

    if(RandomNegNumber())
        a *= -1;
    if(RandomNegNumber())
        b *= -1;

    QChar sign = '#';

    switch(RandomAction(action_flags))
    {
    case Multiplication:
        sign = '*';
        correct_result = a * b;
        break;
    case Division:
        sign = '/';
        correct_result = a / b;
        break;
    case Addition:
        sign ='+';
        correct_result = a + b;
        break;
    case Subtraction:
        sign = '-';
        correct_result = a - b;
        break;
    default:
        sign = '#';
        correct_result = -1;
        break;
    }

    ui->label_Output->setText(start_label_css + QString::number(a) + " " + sign + " " + QString::number(b) + " = </p>");

    ins_left--;
}

int MainWindow::RandomAction(int av_flags)
{
    int c = 0, i = 0, bc_av = av_flags;
    while(bc_av!=0)
    {
        if(bc_av % 2 != 0)
            i++;
        bc_av/=2;
    }

    if(i == -1)
        return -1;

    int* avail = new int[i];
    int j = i - 1;
    if(av_flags & Multiplication) { avail[j] = Multiplication; j--; }
    if(av_flags & Division) { avail[j] = Division; j--; }
    if(av_flags & Addition) { avail[j] = Addition; j--; }
    if(av_flags & Subtraction) { avail[j] = Subtraction; j--; }

    int rand = QRandomGenerator::global()->generateDouble() * (i+1);

    c = avail[rand];
    delete [] avail;
    return c;
}

void MainWindow::EndGame()
{
    ui->edit_input->setText("");
    ui->label_Output->setText(start_label_css + "*Start A New Game*</p>");
}

bool MainWindow::RandomNegNumber()
{
    switch(neg_freq)
    {
    case Always:
        return true;
    case Never:
        return false;
    case Sometimes:
        int r = QRandomGenerator::global()->generateDouble() * (2);
        return r == 1 ? true : false;
        break;
    }
    return false;
}
