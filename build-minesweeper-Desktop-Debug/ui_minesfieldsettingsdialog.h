/********************************************************************************
** Form generated from reading UI file 'minesfieldsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINESFIELDSETTINGSDIALOG_H
#define UI_MINESFIELDSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "colorchoosebutton.h"

QT_BEGIN_NAMESPACE

class Ui_MinesFieldSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    ColorChooseButton *backgroundColorButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    ColorChooseButton *openedCellColorButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    ColorChooseButton *closedCellColorButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    ColorChooseButton *markedAsBombColorButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    ColorChooseButton *markedAsQuestionColorButton;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    ColorChooseButton *borderColorButton;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_7;
    ColorChooseButton *minesAroundColorButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MinesFieldSettingsDialog)
    {
        if (MinesFieldSettingsDialog->objectName().isEmpty())
            MinesFieldSettingsDialog->setObjectName(QStringLiteral("MinesFieldSettingsDialog"));
        MinesFieldSettingsDialog->resize(423, 313);
        verticalLayout = new QVBoxLayout(MinesFieldSettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(MinesFieldSettingsDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        backgroundColorButton = new ColorChooseButton(MinesFieldSettingsDialog);
        backgroundColorButton->setObjectName(QStringLiteral("backgroundColorButton"));

        horizontalLayout->addWidget(backgroundColorButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(MinesFieldSettingsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        openedCellColorButton = new ColorChooseButton(MinesFieldSettingsDialog);
        openedCellColorButton->setObjectName(QStringLiteral("openedCellColorButton"));

        horizontalLayout_2->addWidget(openedCellColorButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(MinesFieldSettingsDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        closedCellColorButton = new ColorChooseButton(MinesFieldSettingsDialog);
        closedCellColorButton->setObjectName(QStringLiteral("closedCellColorButton"));

        horizontalLayout_3->addWidget(closedCellColorButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(MinesFieldSettingsDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        markedAsBombColorButton = new ColorChooseButton(MinesFieldSettingsDialog);
        markedAsBombColorButton->setObjectName(QStringLiteral("markedAsBombColorButton"));

        horizontalLayout_4->addWidget(markedAsBombColorButton);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(MinesFieldSettingsDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        markedAsQuestionColorButton = new ColorChooseButton(MinesFieldSettingsDialog);
        markedAsQuestionColorButton->setObjectName(QStringLiteral("markedAsQuestionColorButton"));

        horizontalLayout_5->addWidget(markedAsQuestionColorButton);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(MinesFieldSettingsDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        borderColorButton = new ColorChooseButton(MinesFieldSettingsDialog);
        borderColorButton->setObjectName(QStringLiteral("borderColorButton"));

        horizontalLayout_6->addWidget(borderColorButton);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(MinesFieldSettingsDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        minesAroundColorButton = new ColorChooseButton(MinesFieldSettingsDialog);
        minesAroundColorButton->setObjectName(QStringLiteral("minesAroundColorButton"));

        horizontalLayout_7->addWidget(minesAroundColorButton);


        verticalLayout->addLayout(horizontalLayout_7);

        buttonBox = new QDialogButtonBox(MinesFieldSettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(backgroundColorButton);
        label_2->setBuddy(openedCellColorButton);
        label_3->setBuddy(closedCellColorButton);
        label_4->setBuddy(markedAsBombColorButton);
        label_5->setBuddy(markedAsQuestionColorButton);
        label_6->setBuddy(borderColorButton);
        label_7->setBuddy(borderColorButton);
#endif // QT_NO_SHORTCUT

        retranslateUi(MinesFieldSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MinesFieldSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MinesFieldSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MinesFieldSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *MinesFieldSettingsDialog)
    {
        MinesFieldSettingsDialog->setWindowTitle(QApplication::translate("MinesFieldSettingsDialog", "Dialog", 0));
        label->setText(QApplication::translate("MinesFieldSettingsDialog", "background color", 0));
        backgroundColorButton->setText(QApplication::translate("MinesFieldSettingsDialog", "choose", 0));
        label_2->setText(QApplication::translate("MinesFieldSettingsDialog", "opened cell color", 0));
        openedCellColorButton->setText(QApplication::translate("MinesFieldSettingsDialog", "choose", 0));
        label_3->setText(QApplication::translate("MinesFieldSettingsDialog", "closed cell color", 0));
        closedCellColorButton->setText(QApplication::translate("MinesFieldSettingsDialog", "choose", 0));
        label_4->setText(QApplication::translate("MinesFieldSettingsDialog", "marked as bomb color", 0));
        markedAsBombColorButton->setText(QApplication::translate("MinesFieldSettingsDialog", "choose", 0));
        label_5->setText(QApplication::translate("MinesFieldSettingsDialog", "marked as question", 0));
        markedAsQuestionColorButton->setText(QApplication::translate("MinesFieldSettingsDialog", "choose", 0));
        label_6->setText(QApplication::translate("MinesFieldSettingsDialog", "border color", 0));
        borderColorButton->setText(QApplication::translate("MinesFieldSettingsDialog", "choose", 0));
        label_7->setText(QApplication::translate("MinesFieldSettingsDialog", "mines around color", 0));
        minesAroundColorButton->setText(QApplication::translate("MinesFieldSettingsDialog", "choose", 0));
    } // retranslateUi

};

namespace Ui {
    class MinesFieldSettingsDialog: public Ui_MinesFieldSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINESFIELDSETTINGSDIALOG_H
