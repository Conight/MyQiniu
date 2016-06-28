#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include <QFile>

namespace Ui {
class setDialog;
}

class setDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setDialog(QWidget *parent = 0);
    ~setDialog();
    void setQiniuKey();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::setDialog *ui;
    QString file;
};

#endif // SETDIALOG_H
