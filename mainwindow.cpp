#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h> // getuid
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>


globalData user;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Check to see if user is running this as Root
    if (getuid() !=0)
    {
        qDebug() << "you are not running this program as root";
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You must be root to run this program!");
        messageBox.setFixedSize(500,200);
        exit(0);
    }
    else
    {
        qDebug() << "You are running this as root";
    }


    // load system users into the program
    loadSystemUsers();

    // Load the pam file daily time restrictions into the user struct
    loadPamFileRestrictions();

    // if the system users don't match the pam restricted users
    // add default details to the user
    if(user.systemUsers.count() != user.username.count())
    {
        addUserDetails();
    }

    ui->selectUserName->addItems(user.username);

    // load amount of time user gets for today
    loadUserTimeRestrictions();

    changeUserDetails();

    getTimeLeft();

    isAccountLocked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getStartAndEndTimes(QString listTime, QString& startTime, QString& endTime)
{
    startTime = listTime.simplified();
    startTime.chop(5);
    startTime.remove(0,2);

    endTime = listTime.simplified();
    endTime.remove(0,7);
}

void MainWindow::changeUserDetails()
{
   // int currentUserIndex = ui->selectUserName->currentIndex();

    // check if the user is new to our program?
    if(user.monLoginStart.value(ui->selectUserName->currentIndex()) == "NEW")
    {
        setTimeBoxesDisabled();
        ui->startTimeMon->setTime(QTime::fromString("0800","hhmm"));
        ui->endTimeMon->setTime(QTime::fromString("2200","hhmm"));
        ui->setLoginTimes->setChecked(Qt::Unchecked);
        ui->limitLoginTimes->setChecked(Qt::Unchecked);
    }
    else
    {
        // if we only need to load the general access times
        if(user.sunLoginStart.value(ui->selectUserName->currentIndex()) == "GEN")
        {
            ui->limitLoginTimes->setChecked(Qt::Checked);
            ui->startTimeSun->setTime(QTime::fromString("0800","hhmm"));
            ui->endTimeSun->setTime(QTime::fromString("2200","hhmm"));
            ui->startTimeMon->setTime(QTime::fromString(user.monLoginStart.value(ui->selectUserName->currentIndex()),"hhmm"));
            ui->endTimeMon->setTime(QTime::fromString(user.monLoginEnd.value(ui->selectUserName->currentIndex()),"hhmm"));
        }
        else
        {
            ui->setLoginTimes->setChecked(Qt::Checked);
        }
    }

    // Load the start times into their spin boxes
//    ui->startTimeMon->setTime(QTime::fromString(user.monLoginStart.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->startTimeTue->setTime(QTime::fromString(user.tueLoginStart.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->startTimeWed->setTime(QTime::fromString(user.wedLoginStart.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->startTimeThu->setTime(QTime::fromString(user.thuLoginStart.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->startTimeFri->setTime(QTime::fromString(user.friLoginStart.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->startTimeSat->setTime(QTime::fromString(user.satLoginStart.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->startTimeSun->setTime(QTime::fromString(user.sunLoginStart.value(ui->selectUserName->currentIndex()),"hhmm"));

//    ui->endTimeMon->setTime(QTime::fromString(user.monLoginEnd.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->endTimeTue->setTime(QTime::fromString(user.tueLoginEnd.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->endTimeWed->setTime(QTime::fromString(user.wedLoginEnd.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->endTimeThu->setTime(QTime::fromString(user.thuLoginEnd.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->endTimeFri->setTime(QTime::fromString(user.friLoginEnd.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->endTimeSat->setTime(QTime::fromString(user.satLoginEnd.value(ui->selectUserName->currentIndex()),"hhmm"));
    ui->endTimeSun->setTime(QTime::fromString(user.sunLoginEnd.value(ui->selectUserName->currentIndex()),"hhmm"));

}

void MainWindow::on_selectUserName_currentIndexChanged()
{
    getTimeLeft();

    isAccountLocked();

    loadUserTimeRestrictions();

    refreshPamUserDetails();

    changeUserDetails();

}

void MainWindow::loadPamFileRestrictions()
{
    QFile pamTimeFile("/etc/security/time.conf");

    if(!pamTimeFile.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Cannot open /etc/security/time.conf");
        messageBox.setFixedSize(500,200);
    }

    QRegExp rx(";|[|]");

    while(!pamTimeFile.atEnd())
    {
        QString pamFileLine = pamTimeFile.readLine();

        if(pamFileLine.contains("TIMEWATCHER START", Qt::CaseInsensitive))
        {
            pamFileLine = pamTimeFile.readLine();

            while(!pamFileLine.contains("TIMEWATCHER END", Qt::CaseInsensitive))
            {
                if(!pamFileLine.startsWith("#"))
                {
                    pamFileLine.simplified();

                    QStringList tempSplit;

                    tempSplit = pamFileLine.split(rx);

                    if(tempSplit.count() > 4)
                    {
                        user.username.append(tempSplit.value(2));

                        QString startTime, endTime;

                        getStartAndEndTimes(tempSplit.value(3), startTime, endTime);

                        user.sunLoginStart.append(startTime);
                        user.sunLoginEnd.append(endTime);

                        getStartAndEndTimes(tempSplit.value(4), startTime, endTime);

                        user.monLoginStart.append(startTime);
                        user.monLoginEnd.append(endTime);

                        getStartAndEndTimes(tempSplit.value(5), startTime, endTime);

                        user.tueLoginStart.append(startTime);
                        user.tueLoginEnd.append(endTime);

                        getStartAndEndTimes(tempSplit.value(6), startTime, endTime);

                        user.wedLoginStart.append(startTime);
                        user.wedLoginEnd.append(endTime);

                        getStartAndEndTimes(tempSplit.value(7), startTime, endTime);

                        user.thuLoginStart.append(startTime);
                        user.thuLoginEnd.append(endTime);

                        getStartAndEndTimes(tempSplit.value(8), startTime, endTime);

                        user.friLoginStart.append(startTime);
                        user.friLoginEnd.append(endTime);

                        getStartAndEndTimes(tempSplit.value(9), startTime, endTime);

                        user.satLoginStart.append(startTime);
                        user.satLoginEnd.append(endTime);
                    }
                    else
                    {
                        user.username.append(tempSplit.value(2));

                        QString startTime, endTime, time;

                        time = tempSplit.value(3).remove(0,2);

                        getStartAndEndTimes(time, startTime, endTime);

                        // Append to say it's a General time
                        user.sunLoginStart.append("GEN");
                        user.sunLoginEnd.append("GEN");

                        user.monLoginStart.append(startTime);
                        user.monLoginEnd.append(endTime);

                        user.tueLoginStart.append(time);
                        user.tueLoginEnd.append(time);

                        user.wedLoginStart.append(time);
                        user.wedLoginEnd.append(time);

                        user.thuLoginStart.append(time);
                        user.thuLoginEnd.append(time);

                        user.friLoginStart.append(time);
                        user.friLoginEnd.append(time);

                        user.satLoginStart.append(time);
                        user.satLoginEnd.append(time);


                    }
                }
                pamFileLine = pamTimeFile.readLine();
            }
        }
    }

    pamTimeFile.close();
}

void MainWindow::loadSystemUsers()
{
    QFile passwdFileHandle("/etc/passwd");

    if(!passwdFileHandle.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Cannot open /etc/passwd");
        messageBox.setFixedSize(500,200);
    }

    QString line;

    while(!passwdFileHandle.atEnd())
    {
        line = passwdFileHandle.readLine();

        QStringList systemUserDetails;

        systemUserDetails = line.split(":");

        // check to see if the group ID is over 1000, generally all users are over 1000
        if(systemUserDetails.value(2).toInt() >= 1000)
        {
            if(QString::compare(systemUserDetails.value(0), "nobody", Qt::CaseInsensitive))
            {
                user.systemUsers.append(systemUserDetails.value(0));
            }
        }
    }

    passwdFileHandle.close();
}

void MainWindow::addUserDetails()
{
    QString startTime = "0800";
    QString endTime = "2200";

    // search the names
    // if name doesn't exist
    // add default details

    for(int needle = 0; needle < user.systemUsers.count(); needle++)
    {
        // if not found, add details
        if(!user.username.contains(user.systemUsers.value(needle)))
        {
            user.username.append(user.systemUsers.value(needle));
            user.sunLoginStart.append(startTime);
            user.sunLoginEnd.append(endTime);

            user.monLoginStart.append("NEW");
            user.monLoginEnd.append("NEW");

            user.tueLoginStart.append(startTime);
            user.tueLoginEnd.append(endTime);

            user.wedLoginStart.append(startTime);
            user.wedLoginEnd.append(endTime);

            user.thuLoginStart.append(startTime);
            user.thuLoginEnd.append(endTime);

            user.friLoginStart.append(startTime);
            user.friLoginEnd.append(endTime);

            user.satLoginStart.append(startTime);
            user.satLoginEnd.append(endTime);
        }
    }
}

void MainWindow::getTimeLeft()
{
    QFile timeFileHandle("/var/lib/timeWatcher/" + ui->selectUserName->currentText());

    if(!timeFileHandle.open(QIODevice::ReadOnly))
    {
        ui->timeLeft->setValue(0);
    }

    QString time = timeFileHandle.readLine();

    ui->timeLeft->setValue(time.toInt());

    timeFileHandle.close();

}


bool MainWindow::isAccountLocked()
{
    QString externalProgram = "passwd";

    QStringList arguments;

    arguments << "-S" << ui->selectUserName->currentText();

    QProcess checkPasswdLocked;

    checkPasswdLocked.setProcessChannelMode(QProcess::MergedChannels);

    checkPasswdLocked.start(externalProgram, arguments);

    checkPasswdLocked.waitForFinished(3000);

    QString output;

    QStringList passwdOutputList;

    output = checkPasswdLocked.readAllStandardOutput();

    passwdOutputList = output.split(' ');

    qDebug() << "output of command " << output;

    if(passwdOutputList.value(1) == "L")
    {
        qDebug() << "User account is locked";
        ui->buttonAccountState->setText("Locked");
        ui->buttonAccountState->setDown(true);
        ui->buttonAccountState->setChecked(true);
        return true;
    }
    else
    {
        qDebug() << "User Account not locked";
        ui->buttonAccountState->setText("UnLocked");
        ui->buttonAccountState->setDown(false);
        ui->buttonAccountState->setChecked(false);
        return false;
    }
}

void MainWindow::on_buttonAccountState_toggled(bool checked)
{
    QProcess accountState;

    QString command = "passwd";

    QStringList args;

    accountState.setProcessChannelMode(QProcess::MergedChannels);

    if(checked)
    {
        ui->buttonAccountState->setText("Locked");

        args << "-l" << ui->selectUserName->currentText();

        accountState.start(command,args);

        accountState.waitForFinished(1000);

        qDebug() << "passwd output " << accountState.readAllStandardOutput();

    }
    else
    {
        ui->buttonAccountState->setText("UnLocked");

        args << "-u" << ui->selectUserName->currentText();

        accountState.start(command,args);

        accountState.waitForFinished(1000);

        qDebug() << "passwd output " << accountState.readAllStandardOutput();
    }

    args.clear();

    args << "-S" << ui->selectUserName->currentText();

    accountState.start(command,args);

    accountState.waitForFinished(1000);

    qDebug() << "passwd state " << accountState.readAllStandardOutput();

}

void MainWindow::setTimeBoxesEnabled()
{
    ui->startTimeMon->setEnabled(true);
    ui->startTimeTue->setEnabled(true);
    ui->startTimeWed->setEnabled(true);
    ui->startTimeThu->setEnabled(true);
    ui->startTimeFri->setEnabled(true);
    ui->startTimeSat->setEnabled(true);
    ui->startTimeSun->setEnabled(true);

    ui->endTimeMon->setEnabled(true);
    ui->endTimeTue->setEnabled(true);
    ui->endTimeWed->setEnabled(true);
    ui->endTimeThu->setEnabled(true);
    ui->endTimeFri->setEnabled(true);
    ui->endTimeSat->setEnabled(true);
    ui->endTimeSun->setEnabled(true);

}

void MainWindow::setTimeBoxesDisabled()
{
    ui->startTimeMon->setEnabled(false);
    ui->startTimeTue->setEnabled(false);
    ui->startTimeWed->setEnabled(false);
    ui->startTimeThu->setEnabled(false);
    ui->startTimeFri->setEnabled(false);
    ui->startTimeSat->setEnabled(false);
    ui->startTimeSun->setEnabled(false);

    ui->endTimeMon->setEnabled(false);
    ui->endTimeTue->setEnabled(false);
    ui->endTimeWed->setEnabled(false);
    ui->endTimeThu->setEnabled(false);
    ui->endTimeFri->setEnabled(false);
    ui->endTimeSat->setEnabled(false);
    ui->endTimeSun->setEnabled(false);

}

void MainWindow::on_limitTimeAccess_toggled(bool checked)
{
    if(checked == true)
    {
        ui->monTime->setEnabled(true);
    }
    else
    {
        ui->monTime->setEnabled(false);
        ui->limitTimeAccess->setCheckState(Qt::Unchecked);
        ui->setTimePerDay->setCheckState(Qt::Unchecked);
        setPeriodBoxesDisabled();
    }
}

void MainWindow::on_setLoginTimes_toggled(bool checked)
{
    if(checked == true)
    {
        setTimeBoxesEnabled();
    }
    else
    {
        setTimeBoxesDisabled();
        ui->startTimeMon->setEnabled(true);
        ui->endTimeMon->setEnabled(true);
    }

}

void MainWindow::on_LimitDailyLoginTime_toggled(bool checked)
{
    if(checked)
    {
        ui->startTimeMon->setEnabled(true);
        ui->endTimeMon->setEnabled(true);
    }
    else
    {
        ui->startTimeMon->setEnabled(false);
        ui->endTimeMon->setEnabled(false);
    }
}

void MainWindow::on_setTimePerDay_toggled(bool checked)
{
    if(checked)
    {
        setPeriodBoxesEnabled();
    }
    else
    {
        setPeriodBoxesDisabled();
        ui->monTime->setEnabled(true);
    }
}

void MainWindow::setPeriodBoxesEnabled()
{
    ui->monTime->setEnabled(true);
    ui->tueTime->setEnabled(true);
    ui->wedTime->setEnabled(true);
    ui->thuTime->setEnabled(true);
    ui->friTime->setEnabled(true);
    ui->satTime->setEnabled(true);
    ui->sunTime->setEnabled(true);

}

void MainWindow::setPeriodBoxesDisabled()
{

    ui->monTime->setEnabled(false);
    ui->tueTime->setEnabled(false);
    ui->wedTime->setEnabled(false);
    ui->thuTime->setEnabled(false);
    ui->friTime->setEnabled(false);
    ui->satTime->setEnabled(false);
    ui->sunTime->setEnabled(false);
}

void MainWindow::on_limitLoginTimes_toggled(bool checked)
{
    if(checked)
    {
        ui->startTimeMon->setEnabled(true);
        ui->endTimeMon->setEnabled(true);
    }
    else
    {
        setTimeBoxesDisabled();
        ui->setLoginTimes->setCheckState(Qt::Unchecked);
        ui->startTimeMon->setEnabled(false);
        ui->endTimeMon->setEnabled(false);
    }
}

void MainWindow::loadUserTimeRestrictions()
{
    QFile timeFileHandle("/etc/timeWatcher/" + ui->selectUserName->currentText() + ".time");

    if(!timeFileHandle.open(QIODevice::ReadOnly))
    {
        qDebug() << QString("Cannot open /etc/timeWatcher/%1.time").arg(ui->selectUserName->currentText());
        qDebug() << "Creating new file";

        timeFileHandle.open(QIODevice::ReadWrite);

        timeFileHandle.write(QString("none").toAscii());

        timeFileHandle.seek(0);
    }

    QString line;

    line = timeFileHandle.readLine();

    if(!line.contains("none", Qt::CaseInsensitive))
    {
        QStringList lineParts;

        lineParts = line.split(',');

        ui->limitTimeAccess->setChecked(Qt::Checked);

        if(lineParts.count() < 4)
        {
            setPeriodBoxesDisabled();
            ui->setTimePerDay->setChecked(Qt::Unchecked);
            ui->monTime->setEnabled(true);
            ui->monTime->setValue(lineParts.value(2).toInt());
        }
        else
        {
            ui->setTimePerDay->setChecked(Qt::Checked);
            setPeriodBoxesEnabled();
            ui->sunTime->setValue(lineParts.value(1).toInt());
            ui->monTime->setValue(lineParts.value(3).toInt());
            ui->tueTime->setValue(lineParts.value(5).toInt());
            ui->wedTime->setValue(lineParts.value(7).toInt());
            ui->thuTime->setValue(lineParts.value(9).toInt());
            ui->friTime->setValue(lineParts.value(11).toInt());
            ui->satTime->setValue(lineParts.value(13).toInt());
        }
    }
    else
    {
        ui->setTimePerDay->setChecked(Qt::Unchecked);
        ui->limitTimeAccess->setChecked(Qt::Unchecked);
        setPeriodBoxesDisabled();
    }
}

void MainWindow::on_refresh_clicked()
{
    // load system users into the program
    qDebug() << "Refreshing variables";

    qDebug() << "Refreshing users avaliable time for today";

    getTimeLeft();

    qDebug() << "Reloading lock status on account";

    isAccountLocked();

    qDebug() << "Refreshing the users daily time limit";

    loadUserTimeRestrictions();

    qDebug() << "Refreshing the pam file time limits";

    refreshPamUserDetails();

    qDebug() << "Refreshing screen variables";

    changeUserDetails();
}

void MainWindow::on_apply_clicked()
{
    QFile fileHandle("/etc/timeWatcher/" + ui->selectUserName->currentText() + ".time");

    // open the file for read write access
    qDebug() << "Opening the time restriction file for writing";

    if(!fileHandle.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QMessageBox messageBox;
        QString errorMessage = "Cannot write to /etc/timeWatcher/%1.time\n";
        errorMessage.append(fileHandle.errorString());
        messageBox.critical(0,"Error", errorMessage.arg(ui->selectUserName->currentText()));
        messageBox.setFixedSize(500,200);
    }

    QTextStream timeText(&fileHandle);

    QString fileText = "";

    if(ui->limitTimeAccess->isChecked())
    {
        fileText = QString("Su, Sa, %1").arg(ui->monTime->text());
    }

    if(ui->setTimePerDay->isChecked())
    {
        fileText = QString("Su, %1, Mo, %2, Tu, %3, We, %4, Th, %5, Fr, %6, Sa, %7")
                    .arg(ui->sunTime->text())
                    .arg(ui->monTime->text())
                    .arg(ui->tueTime->text())
                    .arg(ui->wedTime->text())
                    .arg(ui->thuTime->text())
                    .arg(ui->friTime->text())
                    .arg(ui->satTime->text());
    }

    if(fileText.isEmpty())
    {
        timeText << "none";
    }
    else
    {
        timeText << fileText;
    }

    qDebug() << "Written data to the file - now closing";

    fileHandle.close();

    qDebug() << "Opening the time.conf file for writing";

    QFile readfileLocation("/etc/security/time.conf");

    QFile writeFileLocation("/etc/security/time.conf~");

    // open the file for read access
    if(!readfileLocation.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        QString errorMessage = "Cannot open /etc/security/time.conf\n";
        errorMessage.append(fileHandle.errorString());
        messageBox.critical(0,"Error", errorMessage);
        messageBox.setFixedSize(500,200);
    }

    // open the file for write access
    if(!writeFileLocation.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QMessageBox messageBox;
        QString errorMessage = "Cannot create temp file /etc/security/time.conf~\n";
        errorMessage.append(fileHandle.errorString());
        messageBox.critical(0,"Error", errorMessage);
        messageBox.setFixedSize(500,200);
    }

    QTextStream output(&writeFileLocation);

    bool foundEnd = 0;
    bool foundUser = 0;

    while(!readfileLocation.atEnd())
    {
        QString text = readfileLocation.readLine();

        // Check to see if we have reach the end of the time watcher chunk
        if(text.contains("## TIMEWATCHER END", Qt::CaseInsensitive))
        {
            qDebug() << "found the end of the Timewatcher section";
            if(!foundUser)
            {
                qDebug() << "User wasn't found, entering in now";

                foundEnd = 1;
            }
        }

        if(text.contains(ui->selectUserName->currentText()) || foundEnd)
        {
            if(ui->limitLoginTimes->isChecked())
            {
                if(ui->setLoginTimes->isChecked())
                {
                    foundUser = 1;

                    output << QString("*;*;%1;Su%2-%3 | Mo%4-%5 | Tu%6-%7 | We%8-%9 | Th%10-%11 | " \
                                      "Fr%12-%13 | Sa%14-%15\n")
                              .arg(ui->selectUserName->currentText())
                              .arg(ui->startTimeSun->time().toString("hhmm"))
                              .arg(ui->endTimeSun->time().toString("hhmm"))
                              .arg(ui->startTimeMon->time().toString("hhmm"))
                              .arg(ui->endTimeMon->time().toString("hhmm"))
                              .arg(ui->startTimeTue->time().toString("hhmm"))
                              .arg(ui->endTimeTue->time().toString("hhmm"))
                              .arg(ui->startTimeWed->time().toString("hhmm"))
                              .arg(ui->endTimeWed->time().toString("hhmm"))
                              .arg(ui->startTimeThu->time().toString("hhmm"))
                              .arg(ui->endTimeThu->time().toString("hhmm"))
                              .arg(ui->startTimeFri->time().toString("hhmm"))
                              .arg(ui->endTimeFri->time().toString("hhmm"))
                              .arg(ui->startTimeSat->time().toString("hhmm"))
                              .arg(ui->endTimeSat->time().toString("hhmm"));
                }
                else
                {
                    foundUser = 1;
                    output << QString("*;*;%1;SuSa%2-%3\n")
                              .arg(ui->selectUserName->currentText())
                              .arg(ui->startTimeMon->time().toString("hhmm"))
                              .arg(ui->endTimeMon->time().toString("hhmm"));
                }
            }

            if(foundEnd)
            {
                output << "## TIMEWATCHER END";
            }
        }
        else
        {
            output << text;
        }
    }

    qDebug() << "Written data to the file - now closing";

    writeFileLocation.close();
    readfileLocation.close();

    readfileLocation.remove();

    if(QFile::rename("/etc/security/time.conf~","/etc/security/time.conf"))
    {
        qDebug() << "rename successful";
    }
    else
    {
        qDebug() << "rename not successful";
    }

}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Writing new time left for today";

    QFile fileHandle("/var/lib/timeWatcher/" + ui->selectUserName->currentText());

    // open the file for read write access
    qDebug() << "Opening the time restriction file for writing";

    if(!fileHandle.open(QIODevice::WriteOnly))
    {
        QMessageBox messageBox;
        QString errorMessage = "Cannot open /var/lib/timeWatcher/%1\n";
        errorMessage.append(fileHandle.errorString());
        messageBox.critical(0,"Error", errorMessage.arg(ui->selectUserName->currentText()));
        messageBox.setFixedSize(500,200);
    }

    fileHandle.seek(0);

    fileHandle.write(ui->timeLeft->text().toAscii());

    fileHandle.close();

}

void MainWindow::refreshPamUserDetails()
{
    QFile pamTimeFile("/etc/security/time.conf");

    if(!pamTimeFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open /etc/security/time.conf";
        return;
    }

    bool userFound = 0;

    while(!pamTimeFile.atEnd())
    {
        QString text = pamTimeFile.readLine();

        if(text.contains(ui->selectUserName->currentText()))
        {
            int currentIndex = ui->selectUserName->currentIndex();

            // User is found
            userFound = 1;

            text.simplified();

            QRegExp rx(";|[|]");

            QStringList tempSplit;

            tempSplit = text.split(rx);

            if(tempSplit.count() > 4)
            {
//                user.username.append(tempSplit.value(2));

                QString startTime, endTime;

                getStartAndEndTimes(tempSplit.value(3), startTime, endTime);

                user.sunLoginStart.replace(currentIndex,startTime);
                user.sunLoginEnd.replace(currentIndex, endTime);

                getStartAndEndTimes(tempSplit.value(4), startTime, endTime);

                user.monLoginStart.replace(currentIndex,startTime);
                user.monLoginEnd.append(endTime);

                getStartAndEndTimes(tempSplit.value(5), startTime, endTime);

                user.tueLoginStart.replace(currentIndex,startTime);
                user.tueLoginEnd.append(endTime);

                getStartAndEndTimes(tempSplit.value(6), startTime, endTime);

                user.wedLoginStart.replace(currentIndex,startTime);
                user.wedLoginEnd.append(endTime);

                getStartAndEndTimes(tempSplit.value(7), startTime, endTime);

                user.thuLoginStart.replace(currentIndex,startTime);
                user.thuLoginEnd.append(endTime);

                getStartAndEndTimes(tempSplit.value(8), startTime, endTime);

                user.friLoginStart.replace(currentIndex,startTime);
                user.friLoginEnd.append(endTime);

                getStartAndEndTimes(tempSplit.value(9), startTime, endTime);

                user.satLoginStart.replace(currentIndex,startTime);
                user.satLoginEnd.append(endTime);
            }
            else
            {
                // user.username.append(tempSplit.value(2));

                QString startTime, endTime, time;

                time = tempSplit.value(3).remove(0,2);

                getStartAndEndTimes(time, startTime, endTime);

                // Append to say it's a General time
                user.sunLoginStart.replace(currentIndex,"GEN");
                user.sunLoginEnd.replace(currentIndex,"GEN");

                user.monLoginStart.replace(currentIndex,startTime);
                user.monLoginEnd.replace(currentIndex,endTime);

                user.tueLoginStart.replace(currentIndex,time);
                user.tueLoginEnd.replace(currentIndex,time);

                user.wedLoginStart.replace(currentIndex,time);
                user.wedLoginEnd.replace(currentIndex,time);

                user.thuLoginStart.replace(currentIndex,time);
                user.thuLoginEnd.replace(currentIndex,time);

                user.friLoginStart.replace(currentIndex,time);
                user.friLoginEnd.replace(currentIndex,time);

                user.satLoginStart.replace(currentIndex,time);
                user.satLoginEnd.replace(currentIndex,time);

            }
        }
    }

    if(userFound == 0)
    {

        int currentIndex = ui->selectUserName->currentIndex();

        // Append to say it's a General time
        user.sunLoginStart.replace(currentIndex,"NEW");
        user.sunLoginEnd.replace(currentIndex,"NEW");

    }
}
