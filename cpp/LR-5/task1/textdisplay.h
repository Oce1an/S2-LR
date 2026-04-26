//----------------------- textdisplay.h -----------------------
#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <QWidget>
#include <QStringList>
#include "trainermodel.h"

class TextDisplay : public QWidget {
    Q_OBJECT
public:
    explicit TextDisplay(TrainerModel *model, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    TrainerModel *m_model;
};

#endif // TEXTDISPLAY_H