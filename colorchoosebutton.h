#ifndef COLORCHOOSEBUTTON_H
#define COLORCHOOSEBUTTON_H

#include "minesfieldwidgetsettings.h"

#include <QPushButton>

class ColorChooseButton : public QPushButton {
    Q_OBJECT
public:
    explicit ColorChooseButton(QWidget* parent = 0);

    QColor getColor() const;

    void setColor(const QColor& value);

private slots:
    void buttonClicked();
signals:

public slots:

private:
    QColor color = Qt::transparent;
};

#endif // COLORCHOOSEBUTTON_H
