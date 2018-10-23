/********************************************************************************
** Form generated from reading UI file 'Project.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT_H
#define UI_PROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *Img_label;
    QLabel *ImgOut_label;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Bt_openImg;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Edit_R;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *Edit_G;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *Edit_B;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *Bt_start;
    QSpacerItem *horizontalSpacer_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjectClass)
    {
        if (ProjectClass->objectName().isEmpty())
            ProjectClass->setObjectName(QStringLiteral("ProjectClass"));
        ProjectClass->resize(832, 355);
        centralWidget = new QWidget(ProjectClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Img_label = new QLabel(centralWidget);
        Img_label->setObjectName(QStringLiteral("Img_label"));

        horizontalLayout_3->addWidget(Img_label);

        ImgOut_label = new QLabel(centralWidget);
        ImgOut_label->setObjectName(QStringLiteral("ImgOut_label"));

        horizontalLayout_3->addWidget(ImgOut_label);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        Bt_openImg = new QPushButton(centralWidget);
        Bt_openImg->setObjectName(QStringLiteral("Bt_openImg"));

        horizontalLayout_7->addWidget(Bt_openImg);

        horizontalSpacer = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        Edit_R = new QLineEdit(centralWidget);
        Edit_R->setObjectName(QStringLiteral("Edit_R"));
        Edit_R->setMaxLength(32767);

        horizontalLayout->addWidget(Edit_R);


        horizontalLayout_6->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        Edit_G = new QLineEdit(centralWidget);
        Edit_G->setObjectName(QStringLiteral("Edit_G"));

        horizontalLayout_4->addWidget(Edit_G);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        Edit_B = new QLineEdit(centralWidget);
        Edit_B->setObjectName(QStringLiteral("Edit_B"));

        horizontalLayout_5->addWidget(Edit_B);


        horizontalLayout_6->addLayout(horizontalLayout_5);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        Bt_start = new QPushButton(centralWidget);
        Bt_start->setObjectName(QStringLiteral("Bt_start"));

        horizontalLayout_2->addWidget(Bt_start);

        horizontalSpacer_5 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        ProjectClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProjectClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 832, 18));
        ProjectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjectClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProjectClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProjectClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProjectClass->setStatusBar(statusBar);

        retranslateUi(ProjectClass);

        QMetaObject::connectSlotsByName(ProjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectClass)
    {
        ProjectClass->setWindowTitle(QApplication::translate("ProjectClass", "Project", nullptr));
        Img_label->setText(QApplication::translate("ProjectClass", "TextLabel", nullptr));
        ImgOut_label->setText(QApplication::translate("ProjectClass", "TextLabel", nullptr));
        Bt_openImg->setText(QApplication::translate("ProjectClass", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
        label->setText(QApplication::translate("ProjectClass", "AR\357\274\232", nullptr));
        label_2->setText(QApplication::translate("ProjectClass", "AG\357\274\232", nullptr));
        label_3->setText(QApplication::translate("ProjectClass", "AB\357\274\232", nullptr));
        Bt_start->setText(QApplication::translate("ProjectClass", "\345\274\200\345\247\213\345\244\204\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectClass: public Ui_ProjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT_H
