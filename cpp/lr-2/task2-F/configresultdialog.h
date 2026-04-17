#ifndef CONFIGRESULTDIALOG_H
#define CONFIGRESULTDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ConfigResultDialog : public QDialog {
    Q_OBJECT

public:
    explicit ConfigResultDialog(QWidget *parent = nullptr);
    void setConfigurations(const QString& configText, int count);

private:
    QTextEdit *textEdit;
    QLabel *labelCount;
};

#endif // CONFIGRESULTDIALOG_H
