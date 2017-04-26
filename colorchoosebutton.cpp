#include "colorchoosebutton.h"

#include <QColorDialog>

#include <QDebug>

ColorChooseButton::ColorChooseButton(QWidget* parent)
    : QPushButton(parent)
{
    connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
}

void ColorChooseButton::buttonClicked()
{
    qDebug() << "button clicked";
    color = QColorDialog::getColor(color);
    setColor(color);
}

void ColorChooseButton::setColor(const QColor& value)
{
    color = value;
    setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6);")
                      .arg(color.red())
                      .arg(color.green())
                      .arg(color.blue())
                      .arg(255 - color.red())
                      .arg(255 - color.green())
                      .arg(255 - color.blue()));
}

QColor ColorChooseButton::getColor() const
{
    return color;
}
