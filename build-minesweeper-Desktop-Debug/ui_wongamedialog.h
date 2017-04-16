/********************************************************************************
** Form generated from reading UI file 'wongamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WONGAMEDIALOG_H
#define UI_WONGAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WonGameDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WonGameDialog)
    {
        if (WonGameDialog->objectName().isEmpty())
            WonGameDialog->setObjectName(QStringLiteral("WonGameDialog"));
        WonGameDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(WonGameDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(WonGameDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(WonGameDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setPointSize(15);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        buttonBox = new QDialogButtonBox(WonGameDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::No|QDialogButtonBox::Yes);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(WonGameDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), WonGameDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WonGameDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(WonGameDialog);
    } // setupUi

    void retranslateUi(QDialog *WonGameDialog)
    {
        WonGameDialog->setWindowTitle(QApplication::translate("WonGameDialog", "Dialog", 0));
        label->setText(QApplication::translate("WonGameDialog", "Congratulation, you won!", 0));
        label_2->setText(QApplication::translate("WonGameDialog", "Try again?", 0));
    } // retranslateUi

};

namespace Ui {
    class WonGameDialog: public Ui_WonGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WONGAMEDIALOG_H
