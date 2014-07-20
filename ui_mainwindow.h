/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Jul 20 21:24:03 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QComboBox *selectUserName;
    QSpinBox *timeLeft;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_11;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonAccountState;
    QSpacerItem *horizontalSpacer;
    QLabel *label_userName;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout_4;
    QLabel *labelMonday;
    QSpinBox *sunTime;
    QSpinBox *satTime;
    QSpinBox *monTime;
    QSpinBox *tueTime;
    QCheckBox *limitTimeAccess;
    QLabel *labelFri;
    QTimeEdit *startTimeSat;
    QTimeEdit *startTimeMon;
    QSpinBox *wedTime;
    QLabel *labelThu;
    QLabel *labelSat;
    QCheckBox *setLoginTimes;
    QCheckBox *limitLoginTimes;
    QTimeEdit *endTimeWed;
    QSpinBox *friTime;
    QLabel *label;
    QTimeEdit *endTimeTue;
    QTimeEdit *startTimeTue;
    QLabel *label_2;
    QLabel *labelTuesday;
    QTimeEdit *endTimeMon;
    QSpinBox *thuTime;
    QTimeEdit *startTimeSun;
    QTimeEdit *startTimeThu;
    QLabel *labelSun;
    QCheckBox *setTimePerDay;
    QTimeEdit *endTimeSun;
    QTimeEdit *endTimeFri;
    QTimeEdit *startTimeWed;
    QLabel *labelWed;
    QTimeEdit *startTimeFri;
    QTimeEdit *endTimeSat;
    QTimeEdit *endTimeThu;
    QGridLayout *gridLayout_5;
    QPushButton *close;
    QPushButton *refresh;
    QPushButton *apply;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(916, 257);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        selectUserName = new QComboBox(centralWidget);
        selectUserName->setObjectName(QString::fromUtf8("selectUserName"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selectUserName->sizePolicy().hasHeightForWidth());
        selectUserName->setSizePolicy(sizePolicy);

        gridLayout->addWidget(selectUserName, 1, 0, 1, 1);

        timeLeft = new QSpinBox(centralWidget);
        timeLeft->setObjectName(QString::fromUtf8("timeLeft"));
        timeLeft->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(timeLeft->sizePolicy().hasHeightForWidth());
        timeLeft->setSizePolicy(sizePolicy1);
        timeLeft->setButtonSymbols(QAbstractSpinBox::PlusMinus);

        gridLayout->addWidget(timeLeft, 1, 3, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 1, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 2, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 1, 5, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        buttonAccountState = new QPushButton(centralWidget);
        buttonAccountState->setObjectName(QString::fromUtf8("buttonAccountState"));
        buttonAccountState->setCheckable(true);

        gridLayout_2->addWidget(buttonAccountState, 1, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 7, 1, 1);

        label_userName = new QLabel(centralWidget);
        label_userName->setObjectName(QString::fromUtf8("label_userName"));

        gridLayout_2->addWidget(label_userName, 1, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(6);
        labelMonday = new QLabel(centralWidget);
        labelMonday->setObjectName(QString::fromUtf8("labelMonday"));

        gridLayout_4->addWidget(labelMonday, 0, 3, 1, 1);

        sunTime = new QSpinBox(centralWidget);
        sunTime->setObjectName(QString::fromUtf8("sunTime"));
        sunTime->setEnabled(false);
        sunTime->setValue(60);

        gridLayout_4->addWidget(sunTime, 1, 9, 1, 1);

        satTime = new QSpinBox(centralWidget);
        satTime->setObjectName(QString::fromUtf8("satTime"));
        satTime->setEnabled(false);
        satTime->setValue(60);

        gridLayout_4->addWidget(satTime, 1, 8, 1, 1);

        monTime = new QSpinBox(centralWidget);
        monTime->setObjectName(QString::fromUtf8("monTime"));
        monTime->setEnabled(false);
        monTime->setValue(60);

        gridLayout_4->addWidget(monTime, 1, 3, 1, 1);

        tueTime = new QSpinBox(centralWidget);
        tueTime->setObjectName(QString::fromUtf8("tueTime"));
        tueTime->setEnabled(false);
        tueTime->setValue(60);

        gridLayout_4->addWidget(tueTime, 1, 4, 1, 1);

        limitTimeAccess = new QCheckBox(centralWidget);
        limitTimeAccess->setObjectName(QString::fromUtf8("limitTimeAccess"));

        gridLayout_4->addWidget(limitTimeAccess, 0, 1, 1, 1);

        labelFri = new QLabel(centralWidget);
        labelFri->setObjectName(QString::fromUtf8("labelFri"));

        gridLayout_4->addWidget(labelFri, 0, 7, 1, 1);

        startTimeSat = new QTimeEdit(centralWidget);
        startTimeSat->setObjectName(QString::fromUtf8("startTimeSat"));
        startTimeSat->setEnabled(false);
        startTimeSat->setTime(QTime(8, 0, 0));

        gridLayout_4->addWidget(startTimeSat, 2, 8, 1, 1);

        startTimeMon = new QTimeEdit(centralWidget);
        startTimeMon->setObjectName(QString::fromUtf8("startTimeMon"));
        startTimeMon->setEnabled(false);
        startTimeMon->setTime(QTime(8, 0, 0));

        gridLayout_4->addWidget(startTimeMon, 2, 3, 1, 1);

        wedTime = new QSpinBox(centralWidget);
        wedTime->setObjectName(QString::fromUtf8("wedTime"));
        wedTime->setEnabled(false);
        wedTime->setValue(60);

        gridLayout_4->addWidget(wedTime, 1, 5, 1, 1);

        labelThu = new QLabel(centralWidget);
        labelThu->setObjectName(QString::fromUtf8("labelThu"));

        gridLayout_4->addWidget(labelThu, 0, 6, 1, 1);

        labelSat = new QLabel(centralWidget);
        labelSat->setObjectName(QString::fromUtf8("labelSat"));

        gridLayout_4->addWidget(labelSat, 0, 8, 1, 1);

        setLoginTimes = new QCheckBox(centralWidget);
        setLoginTimes->setObjectName(QString::fromUtf8("setLoginTimes"));

        gridLayout_4->addWidget(setLoginTimes, 4, 1, 1, 1);

        limitLoginTimes = new QCheckBox(centralWidget);
        limitLoginTimes->setObjectName(QString::fromUtf8("limitLoginTimes"));

        gridLayout_4->addWidget(limitLoginTimes, 2, 1, 1, 1);

        endTimeWed = new QTimeEdit(centralWidget);
        endTimeWed->setObjectName(QString::fromUtf8("endTimeWed"));
        endTimeWed->setEnabled(false);
        endTimeWed->setTime(QTime(22, 0, 0));

        gridLayout_4->addWidget(endTimeWed, 4, 5, 1, 1);

        friTime = new QSpinBox(centralWidget);
        friTime->setObjectName(QString::fromUtf8("friTime"));
        friTime->setEnabled(false);
        friTime->setValue(60);

        gridLayout_4->addWidget(friTime, 1, 7, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 2, 2, 1, 1);

        endTimeTue = new QTimeEdit(centralWidget);
        endTimeTue->setObjectName(QString::fromUtf8("endTimeTue"));
        endTimeTue->setEnabled(false);
        endTimeTue->setTime(QTime(22, 0, 0));

        gridLayout_4->addWidget(endTimeTue, 4, 4, 1, 1);

        startTimeTue = new QTimeEdit(centralWidget);
        startTimeTue->setObjectName(QString::fromUtf8("startTimeTue"));
        startTimeTue->setEnabled(false);
        startTimeTue->setTime(QTime(8, 0, 0));

        gridLayout_4->addWidget(startTimeTue, 2, 4, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 4, 2, 1, 1);

        labelTuesday = new QLabel(centralWidget);
        labelTuesday->setObjectName(QString::fromUtf8("labelTuesday"));

        gridLayout_4->addWidget(labelTuesday, 0, 4, 1, 1);

        endTimeMon = new QTimeEdit(centralWidget);
        endTimeMon->setObjectName(QString::fromUtf8("endTimeMon"));
        endTimeMon->setEnabled(false);
        endTimeMon->setTime(QTime(22, 0, 0));

        gridLayout_4->addWidget(endTimeMon, 4, 3, 1, 1);

        thuTime = new QSpinBox(centralWidget);
        thuTime->setObjectName(QString::fromUtf8("thuTime"));
        thuTime->setEnabled(false);
        thuTime->setValue(60);

        gridLayout_4->addWidget(thuTime, 1, 6, 1, 1);

        startTimeSun = new QTimeEdit(centralWidget);
        startTimeSun->setObjectName(QString::fromUtf8("startTimeSun"));
        startTimeSun->setEnabled(false);
        startTimeSun->setTime(QTime(8, 0, 0));

        gridLayout_4->addWidget(startTimeSun, 2, 9, 1, 1);

        startTimeThu = new QTimeEdit(centralWidget);
        startTimeThu->setObjectName(QString::fromUtf8("startTimeThu"));
        startTimeThu->setEnabled(false);
        startTimeThu->setTime(QTime(8, 0, 0));

        gridLayout_4->addWidget(startTimeThu, 2, 6, 1, 1);

        labelSun = new QLabel(centralWidget);
        labelSun->setObjectName(QString::fromUtf8("labelSun"));

        gridLayout_4->addWidget(labelSun, 0, 9, 1, 1);

        setTimePerDay = new QCheckBox(centralWidget);
        setTimePerDay->setObjectName(QString::fromUtf8("setTimePerDay"));

        gridLayout_4->addWidget(setTimePerDay, 1, 1, 1, 1);

        endTimeSun = new QTimeEdit(centralWidget);
        endTimeSun->setObjectName(QString::fromUtf8("endTimeSun"));
        endTimeSun->setEnabled(false);
        endTimeSun->setTime(QTime(22, 0, 0));

        gridLayout_4->addWidget(endTimeSun, 4, 9, 1, 1);

        endTimeFri = new QTimeEdit(centralWidget);
        endTimeFri->setObjectName(QString::fromUtf8("endTimeFri"));
        endTimeFri->setEnabled(false);
        endTimeFri->setTime(QTime(22, 0, 0));

        gridLayout_4->addWidget(endTimeFri, 4, 7, 1, 1);

        startTimeWed = new QTimeEdit(centralWidget);
        startTimeWed->setObjectName(QString::fromUtf8("startTimeWed"));
        startTimeWed->setEnabled(false);
        startTimeWed->setTime(QTime(8, 0, 0));

        gridLayout_4->addWidget(startTimeWed, 2, 5, 1, 1);

        labelWed = new QLabel(centralWidget);
        labelWed->setObjectName(QString::fromUtf8("labelWed"));

        gridLayout_4->addWidget(labelWed, 0, 5, 1, 1);

        startTimeFri = new QTimeEdit(centralWidget);
        startTimeFri->setObjectName(QString::fromUtf8("startTimeFri"));
        startTimeFri->setEnabled(false);
        startTimeFri->setTime(QTime(8, 0, 0));

        gridLayout_4->addWidget(startTimeFri, 2, 7, 1, 1);

        endTimeSat = new QTimeEdit(centralWidget);
        endTimeSat->setObjectName(QString::fromUtf8("endTimeSat"));
        endTimeSat->setEnabled(false);
        endTimeSat->setTime(QTime(22, 0, 0));

        gridLayout_4->addWidget(endTimeSat, 4, 8, 1, 1);

        endTimeThu = new QTimeEdit(centralWidget);
        endTimeThu->setObjectName(QString::fromUtf8("endTimeThu"));
        endTimeThu->setEnabled(false);
        endTimeThu->setTime(QTime(22, 0, 0));

        gridLayout_4->addWidget(endTimeThu, 4, 6, 1, 1);


        verticalLayout_4->addLayout(gridLayout_4);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        close = new QPushButton(centralWidget);
        close->setObjectName(QString::fromUtf8("close"));

        gridLayout_5->addWidget(close, 1, 2, 1, 1);

        refresh = new QPushButton(centralWidget);
        refresh->setObjectName(QString::fromUtf8("refresh"));

        gridLayout_5->addWidget(refresh, 1, 1, 1, 1);

        apply = new QPushButton(centralWidget);
        apply->setObjectName(QString::fromUtf8("apply"));

        gridLayout_5->addWidget(apply, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 0, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(buttonAccountState, limitTimeAccess);
        QWidget::setTabOrder(limitTimeAccess, setTimePerDay);
        QWidget::setTabOrder(setTimePerDay, monTime);
        QWidget::setTabOrder(monTime, tueTime);
        QWidget::setTabOrder(tueTime, wedTime);
        QWidget::setTabOrder(wedTime, thuTime);
        QWidget::setTabOrder(thuTime, friTime);
        QWidget::setTabOrder(friTime, satTime);
        QWidget::setTabOrder(satTime, sunTime);
        QWidget::setTabOrder(sunTime, startTimeMon);
        QWidget::setTabOrder(startTimeMon, startTimeTue);
        QWidget::setTabOrder(startTimeTue, startTimeWed);
        QWidget::setTabOrder(startTimeWed, startTimeThu);
        QWidget::setTabOrder(startTimeThu, startTimeFri);
        QWidget::setTabOrder(startTimeFri, startTimeSat);
        QWidget::setTabOrder(startTimeSat, startTimeSun);
        QWidget::setTabOrder(startTimeSun, endTimeMon);
        QWidget::setTabOrder(endTimeMon, endTimeTue);
        QWidget::setTabOrder(endTimeTue, endTimeWed);
        QWidget::setTabOrder(endTimeWed, endTimeThu);
        QWidget::setTabOrder(endTimeThu, endTimeFri);
        QWidget::setTabOrder(endTimeFri, endTimeSat);
        QWidget::setTabOrder(endTimeSat, endTimeSun);
        QWidget::setTabOrder(endTimeSun, apply);
        QWidget::setTabOrder(apply, refresh);
        QWidget::setTabOrder(refresh, close);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Time Watcher", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Time Left for today", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "User Account is", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Apply New Time", 0, QApplication::UnicodeUTF8));
        buttonAccountState->setText(QApplication::translate("MainWindow", "UnLocked", 0, QApplication::UnicodeUTF8));
        label_userName->setText(QApplication::translate("MainWindow", "Current User", 0, QApplication::UnicodeUTF8));
        labelMonday->setText(QApplication::translate("MainWindow", "Monday", 0, QApplication::UnicodeUTF8));
        limitTimeAccess->setText(QApplication::translate("MainWindow", "Limit Daily Access", 0, QApplication::UnicodeUTF8));
        labelFri->setText(QApplication::translate("MainWindow", "Friday", 0, QApplication::UnicodeUTF8));
        labelThu->setText(QApplication::translate("MainWindow", "Thursday", 0, QApplication::UnicodeUTF8));
        labelSat->setText(QApplication::translate("MainWindow", "Saturday", 0, QApplication::UnicodeUTF8));
        setLoginTimes->setText(QApplication::translate("MainWindow", "Set Login Times Per Day", 0, QApplication::UnicodeUTF8));
        limitLoginTimes->setText(QApplication::translate("MainWindow", "Limit Login Times", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "End", 0, QApplication::UnicodeUTF8));
        labelTuesday->setText(QApplication::translate("MainWindow", "Tuesday", 0, QApplication::UnicodeUTF8));
        labelSun->setText(QApplication::translate("MainWindow", "Sunday", 0, QApplication::UnicodeUTF8));
        setTimePerDay->setText(QApplication::translate("MainWindow", "Set Allowed Time Per Day", 0, QApplication::UnicodeUTF8));
        labelWed->setText(QApplication::translate("MainWindow", "Wednesday", 0, QApplication::UnicodeUTF8));
        close->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        refresh->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        apply->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
