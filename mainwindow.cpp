#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialogsettinginput.h>
#include <windialog.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName("Horisan");
    QCoreApplication::setOrganizationDomain("naomi03.ga");
    QCoreApplication::setApplicationName("Math Operations Tester");

    ui->setupUi(this);
    action_flags = Multiplication + Addition + Subtraction + Division;
    LoadSettings();
    on_actionEnd_Game_triggered();
    SetTimeCounter(0);
    SetQuestionTime(0);
    pause = true;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(CountTime()));
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
    sett.setValue("op", action_flags);
}

void MainWindow::LoadSettings()
{
    // return default in case if user has no saved settings
    on_actionReturn_Default_Settings_triggered();


    QSettings sett;
    amount_ins = sett.value("amount").toInt();
    min_no = sett.value("min").toInt();
    max_no = sett.value("max").toInt();
    places_after_dec = sett.value("dec").toInt();
    floating = sett.value("fltg").toBool();
    action_flags = sett.value("op").toInt();

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
    if(action_flags == 0)
    {
        QMessageBox::critical(this, "Chosen no operations", "You didn't choose the operations math.");
        return;
    }
    ins_left = amount_ins;
    mistakes = 0;
    time = 0;
    each_time = 0;
    pause = false;

    NextTurn();
    timer->start(1000);
}

void MainWindow::on_actionPause_Game_triggered()
{
    timer->stop();
    pause = true;
    ui->edit_input->setDisabled(true);
    ui->edit_input->clear();
}

void MainWindow::on_actionResume_triggered()
{
    if(ins_left > 0)
    {
        pause = false;
        timer->start(1000);
        ui->edit_input->setDisabled(false);
    }
}

void MainWindow::on_actionEnd_Game_triggered()
{
    if(time != 0)
        timer->stop();
    time = 0;
    SetTimeCounter(0);
    SetQuestionTime(0);
    ins_left = 0;
    pause = true;
    ui->label_Output->setText(start_label_css + "Start A New Game</p>");
    ui->edit_input->setText("");
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

    action_flags = Multiplication + Division + Addition + Subtraction;

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
    if(pause)
    {
        ui->edit_input->setText("");
        return;
    }
    if(ins_left <= 0)
    {
        if(time != 0)
            timer->stop();
        WinDialog dialog(mistakes, amount_ins - mistakes, time, amount_ins);
        dialog.exec();
        time = 0;
        on_actionEnd_Game_triggered();
    }

    if(QString::number(correct_result) == ui->edit_input->text())
    {
        each_time = 0;
        if(ins_left <= 0)
        {
            if(time != 0)
                timer->stop();
            WinDialog dialog(mistakes, amount_ins - mistakes, time, amount_ins);
            dialog.exec();
            time = 0;
            on_actionEnd_Game_triggered();
        }
        else
        {
            NextTurn();
            ui->edit_input->setText("");
        }
    }
    else if (ins_left > 0)
    {
        mistakes++;
        QMessageBox::information(this, "Info!", "You are wrong! Correct result is " + QString::number(correct_result));
        each_time = 0;
        NextTurn();
        ui->edit_input->setText("");
    }
    else
    {
        ui->edit_input->setText("");
    }
}


void MainWindow::on_btn_giveUp_clicked()
{
    if(ins_left <= 0 || pause)
        return;

    QMessageBox::critical(this, "LOOOOOOOOSER!", "You losed looser... I don't wanna see you bitch!");
    on_actionEnd_Game_triggered();
}

// GAME
void MainWindow::NextTurn()
{
    if(ins_left <= 0)
        return;

    float rand_a = QRandomGenerator::global()->generateDouble() * (max_no - min_no + 1) + min_no;
    float rand_b = QRandomGenerator::global()->generateDouble() * (max_no - min_no + 1) + min_no;
    float rand_c = QRandomGenerator::global()->generateDouble() * (max_no - min_no + 1) + min_no;
    float a, b, c;

    if(floating)
    {
        int factor = pow(10, places_after_dec);
        a = round(rand_a * factor) / factor;
        b = round(rand_b * factor) / factor;
        c = round(rand_c * factor) / factor;
    }
    else
    {
        a = trunc(rand_a);
        b = trunc(rand_b);
        c = trunc(rand_c);
    }

    if(RandomNegNumber())
        a *= -1;
    if(RandomNegNumber())
        b *= -1;
    if(RandomNegNumber())
        c *= -1;

    QChar sign = '#';

    switch(RandomAction(action_flags))
    {
    case Multiplication:
        sign = '*';
        correct_result = a * b;
        break;
    case Division:
        sign = '/';
        correct_result = c;
        a = correct_result * b;
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
        QMessageBox::information(this,"Error", "Raw value");
        break;
    }

    ui->label_Output->setText(start_label_css + QString::number(a) + " " + sign + " " + QString::number(b) + " = </p>");

    ins_left--;
}

int MainWindow::RandomAction(int av_flags)
{
    QVector<int> rand_flags;

    if(av_flags & Multiplication)
    {
        rand_flags.push_back(Multiplication);
    }
    if(av_flags & Division)
    {
        rand_flags.push_back(Division);
    }
    if(av_flags & Subtraction)
    {
        rand_flags.push_back(Subtraction);
    }
    if(av_flags & Addition)
    {
        rand_flags.push_back(Addition);
    }

    int rand = QRandomGenerator::global()->generateDouble() * rand_flags.count();

    return rand_flags.at(rand);
}

void MainWindow::SetTimeCounter(int time)
{
    ui->line_time->setText("Total Time: " + QString::number(time));
}

void MainWindow::SetQuestionTime(int time)
{
    ui->line_time_2->setText("Question Time: " + QString::number(time));
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

void MainWindow::CountTime()
{
    time++;
    each_time++;
    SetTimeCounter(time);
    SetQuestionTime(each_time);
}


void MainWindow::on_actionAbout_triggered()
{
    QString c = "Desktop App created by Wiktor B. at March 2022.\n"
                "All rights are reserved because are reserved.\n"
                "\n"
                "You can check your math skills!\n"
                "Good luck!";

    QMessageBox::about(this, "About...", c);
}

