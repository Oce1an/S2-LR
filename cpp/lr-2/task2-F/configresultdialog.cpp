#include "configresultdialog.h"

ConfigResultDialog::ConfigResultDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("PC Configuration Results");
    setMinimumSize(700, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);

    labelCount = new QLabel("Found configurations:", this);
    labelCount->setFont(QFont("Arial", 12, QFont::Bold));
    layout->addWidget(labelCount);

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    textEdit->setFont(QFont("Courier New", 10));
    textEdit->setLineWrapMode(QTextEdit::NoWrap);
    layout->addWidget(textEdit);

    QPushButton *closeBtn = new QPushButton("Close", this);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(closeBtn);
}

void ConfigResultDialog::setConfigurations(const QString& configText, int count)
{
    labelCount->setText(QString("Found %1 PC configuration(s):").arg(count));
    textEdit->setPlainText(configText);
    textEdit->moveCursor(QTextCursor::Start);
}
