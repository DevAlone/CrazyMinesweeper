/********************************************************************************
** Form generated from reading UI file 'newgamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGAMEDIALOG_H
#define UI_NEWGAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewGameDialog
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *fieldWidth;
    QLabel *label_2;
    QLineEdit *fieldHeight;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLineEdit *cellWidth;
    QLabel *label_4;
    QLineEdit *cellHeight;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_4;
    QFormLayout *formLayout_4;
    QLabel *label_7;
    QLineEdit *borderWidth;
    QLabel *label_8;
    QLineEdit *borderHeight;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *minesPercent;
    QDialogButtonBox *buttonBox;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButtonEasy;
    QPushButton *pushButtonLIttleHarder;
    QPushButton *pushButtonAsianMode;
    QPushButton *pushButtonManually;

    void setupUi(QDialog *NewGameDialog)
    {
        if (NewGameDialog->objectName().isEmpty())
            NewGameDialog->setObjectName(QStringLiteral("NewGameDialog"));
        NewGameDialog->resize(400, 355);
        verticalLayout = new QVBoxLayout(NewGameDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        stackedWidget = new QStackedWidget(NewGameDialog);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        fieldWidth = new QLineEdit(groupBox);
        fieldWidth->setObjectName(QStringLiteral("fieldWidth"));

        formLayout->setWidget(0, QFormLayout::FieldRole, fieldWidth);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        fieldHeight = new QLineEdit(groupBox);
        fieldHeight->setObjectName(QStringLiteral("fieldHeight"));

        formLayout->setWidget(1, QFormLayout::FieldRole, fieldHeight);


        horizontalLayout->addLayout(formLayout);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        cellWidth = new QLineEdit(groupBox_2);
        cellWidth->setObjectName(QStringLiteral("cellWidth"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cellWidth);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        cellHeight = new QLineEdit(groupBox_2);
        cellHeight->setObjectName(QStringLiteral("cellHeight"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cellHeight);


        horizontalLayout_2->addLayout(formLayout_2);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(page);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_7);

        borderWidth = new QLineEdit(groupBox_3);
        borderWidth->setObjectName(QStringLiteral("borderWidth"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, borderWidth);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_8);

        borderHeight = new QLineEdit(groupBox_3);
        borderHeight->setObjectName(QStringLiteral("borderHeight"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, borderHeight);


        horizontalLayout_4->addLayout(formLayout_4);


        verticalLayout_2->addWidget(groupBox_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        minesPercent = new QLineEdit(page);
        minesPercent->setObjectName(QStringLiteral("minesPercent"));

        horizontalLayout_3->addWidget(minesPercent);


        verticalLayout_2->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(page);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButtonEasy = new QPushButton(page_2);
        pushButtonEasy->setObjectName(QStringLiteral("pushButtonEasy"));

        verticalLayout_3->addWidget(pushButtonEasy);

        pushButtonLIttleHarder = new QPushButton(page_2);
        pushButtonLIttleHarder->setObjectName(QStringLiteral("pushButtonLIttleHarder"));

        verticalLayout_3->addWidget(pushButtonLIttleHarder);

        pushButtonAsianMode = new QPushButton(page_2);
        pushButtonAsianMode->setObjectName(QStringLiteral("pushButtonAsianMode"));

        verticalLayout_3->addWidget(pushButtonAsianMode);

        pushButtonManually = new QPushButton(page_2);
        pushButtonManually->setObjectName(QStringLiteral("pushButtonManually"));

        verticalLayout_3->addWidget(pushButtonManually);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(NewGameDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewGameDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewGameDialog, SLOT(reject()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(NewGameDialog);
    } // setupUi

    void retranslateUi(QDialog *NewGameDialog)
    {
        NewGameDialog->setWindowTitle(QApplication::translate("NewGameDialog", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("NewGameDialog", "Field", 0));
        label->setText(QApplication::translate("NewGameDialog", "Width", 0));
        label_2->setText(QApplication::translate("NewGameDialog", "Height", 0));
        groupBox_2->setTitle(QApplication::translate("NewGameDialog", "Cell", 0));
        label_3->setText(QApplication::translate("NewGameDialog", "Width", 0));
        label_4->setText(QApplication::translate("NewGameDialog", "Height", 0));
        groupBox_3->setTitle(QApplication::translate("NewGameDialog", "Border", 0));
        label_7->setText(QApplication::translate("NewGameDialog", "Width", 0));
        label_8->setText(QApplication::translate("NewGameDialog", "Height", 0));
        label_5->setText(QApplication::translate("NewGameDialog", "mines percent", 0));
        pushButtonEasy->setText(QApplication::translate("NewGameDialog", "easy", 0));
        pushButtonLIttleHarder->setText(QApplication::translate("NewGameDialog", "little harder", 0));
        pushButtonAsianMode->setText(QApplication::translate("NewGameDialog", "asian mode", 0));
        pushButtonManually->setText(QApplication::translate("NewGameDialog", "manually", 0));
    } // retranslateUi

};

namespace Ui {
    class NewGameDialog: public Ui_NewGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGAMEDIALOG_H
