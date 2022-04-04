#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator>
#include <math.h>
#include <QSettings>
#include <vector>
#include <QTimer>
#include "EnumsStructs.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetAmountProperty(int prop, DialogSettingsMode m);

private slots:
    void on_actionNew_Game_triggered();

    void on_actionPause_Game_triggered();

    void on_actionEnd_Game_triggered();

    void on_actionReturn_Default_Settings_triggered();

    void on_actionAlways_triggered();

    void on_actionSometimes_triggered();

    void on_actionNever_triggered();

    void on_actionAmount_Instances_triggered();

    void on_actionLowest_Number_triggered();

    void on_actionHighest_Number_triggered();

    void on_actionDigits_After_The_Decimal_triggered();

    void on_btn_done_clicked();

    void on_btn_giveUp_clicked();

    void on_actionFloating_numbers_2_triggered();

    void on_actionmultiplication_triggered(bool checked);

    void on_actionDivision_triggered(bool checked);

    void on_actionAddition_triggered(bool checked);

    void on_actionSubtraction_triggered(bool checked);

    void CountTime();

    void on_actionResume_triggered();

    void on_actionAbout_triggered();

private:
    void SetSettingsForMenu();
    void CheckNegFreqMenu(NegativeFreq nf);
    void SaveSettings();
    void LoadSettings();
    bool RandomNegNumber();
    void NextTurn();
    int RandomAction(int av_flags);
    void SetTimeCounter(int time);
    void SetQuestionTime(int time);


    Ui::MainWindow *ui;

    // Settings //
    int amount_ins;
    float min_no;
    float max_no;

    bool floating;
    int places_after_dec;

    NegativeFreq neg_freq;
    // SYSTEM VALUES //
    bool pause;

    QTimer* timer;
    int time;
    int each_time;
    float correct_result;
    int ins_left;
    int mistakes;
    int action_flags;
    const QString start_label_css = "<p style='font-size:28pt; font-weight:700; text-align: center;'>";

};
#endif // MAINWINDOW_H
