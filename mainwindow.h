#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct globalData
{
    public:
        QStringList username;
        QStringList systemUsers;
        QStringList monLoginStart;
        QStringList monLoginEnd;
        QStringList tueLoginStart;
        QStringList tueLoginEnd;
        QStringList wedLoginStart;
        QStringList wedLoginEnd;
        QStringList thuLoginStart;
        QStringList thuLoginEnd;
        QStringList friLoginStart;
        QStringList friLoginEnd;
        QStringList satLoginStart;
        QStringList satLoginEnd;
        QStringList sunLoginStart;
        QStringList sunLoginEnd;
        int loginTimeLeft;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_selectUserName_currentIndexChanged();

    void on_buttonAccountState_toggled(bool checked);

    void on_limitTimeAccess_toggled(bool checked);

    void on_setLoginTimes_toggled(bool checked);

    void on_LimitDailyLoginTime_toggled(bool checked);

    void on_setTimePerDay_toggled(bool checked);

    void on_limitLoginTimes_toggled(bool checked);

    void on_refresh_clicked();

    void on_apply_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void getStartAndEndTimes(QString listTime, QString& startTime, QString& endTime);
    void changeUserDetails();
    void loadPamFileRestrictions();
    void loadSystemUsers();
    void loadUserTimeRestrictions();
    void addUserDetails();
    void getTimeLeft();
    bool isAccountLocked();
    void setTimeBoxesEnabled();
    void setTimeBoxesDisabled();
    void setPeriodBoxesEnabled();
    void setPeriodBoxesDisabled();
    void refreshPamUserDetails();
};

#endif // MAINWINDOW_H
