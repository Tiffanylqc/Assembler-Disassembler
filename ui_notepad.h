/********************************************************************************
** Form generated from reading UI file 'notepad.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_H
#define UI_NOTEPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Notepad
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionNew;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *actionOpen_2;
    QAction *actionNew_2;
    QAction *actionSave_2;
    QAction *actionSave_AS;
    QWidget *centralWidget;
    QLabel *label;
    QTextEdit *textEdit_2;
    QLabel *label_2;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuBIN;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Notepad)
    {
        if (Notepad->objectName().isEmpty())
            Notepad->setObjectName(QStringLiteral("Notepad"));
        Notepad->resize(806, 421);
        actionOpen = new QAction(Notepad);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(Notepad);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionNew = new QAction(Notepad);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionSave_As = new QAction(Notepad);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionExit = new QAction(Notepad);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOpen_2 = new QAction(Notepad);
        actionOpen_2->setObjectName(QStringLiteral("actionOpen_2"));
        actionNew_2 = new QAction(Notepad);
        actionNew_2->setObjectName(QStringLiteral("actionNew_2"));
        actionSave_2 = new QAction(Notepad);
        actionSave_2->setObjectName(QStringLiteral("actionSave_2"));
        actionSave_AS = new QAction(Notepad);
        actionSave_AS->setObjectName(QStringLiteral("actionSave_AS"));
        centralWidget = new QWidget(Notepad);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 320, 191, 31));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(470, 50, 301, 231));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(530, 330, 171, 16));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(140, 50, 301, 233));
        textEdit->setLineWidth(24);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 50, 113, 32));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 80, 113, 32));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(140, 290, 301, 32));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(470, 290, 301, 31));
        Notepad->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Notepad);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 806, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuBIN = new QMenu(menuBar);
        menuBIN->setObjectName(QStringLiteral("menuBIN"));
        Notepad->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Notepad);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Notepad->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Notepad);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Notepad->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuBIN->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionExit);
        menuBIN->addAction(actionOpen_2);
        menuBIN->addAction(actionNew_2);
        menuBIN->addAction(actionSave_2);
        menuBIN->addAction(actionSave_AS);

        retranslateUi(Notepad);

        QMetaObject::connectSlotsByName(Notepad);
    } // setupUi

    void retranslateUi(QMainWindow *Notepad)
    {
        Notepad->setWindowTitle(QApplication::translate("Notepad", "Notepad", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("Notepad", "Open", Q_NULLPTR));
        actionOpen->setShortcut(QApplication::translate("Notepad", "Meta+O", Q_NULLPTR));
        actionSave->setText(QApplication::translate("Notepad", "Save", Q_NULLPTR));
        actionSave->setShortcut(QApplication::translate("Notepad", "Meta+S", Q_NULLPTR));
        actionNew->setText(QApplication::translate("Notepad", "New", Q_NULLPTR));
        actionNew->setShortcut(QApplication::translate("Notepad", "Meta+N", Q_NULLPTR));
        actionSave_As->setText(QApplication::translate("Notepad", "Save As ", Q_NULLPTR));
        actionSave_As->setShortcut(QApplication::translate("Notepad", "Meta+Shift+S", Q_NULLPTR));
        actionExit->setText(QApplication::translate("Notepad", "Done", Q_NULLPTR));
        actionOpen_2->setText(QApplication::translate("Notepad", "Open", Q_NULLPTR));
        actionOpen_2->setShortcut(QApplication::translate("Notepad", "Meta+O", Q_NULLPTR));
        actionNew_2->setText(QApplication::translate("Notepad", "New", Q_NULLPTR));
        actionNew_2->setShortcut(QApplication::translate("Notepad", "Meta+N", Q_NULLPTR));
        actionSave_2->setText(QApplication::translate("Notepad", "Save", Q_NULLPTR));
        actionSave_2->setShortcut(QApplication::translate("Notepad", "Meta+S", Q_NULLPTR));
        actionSave_AS->setText(QApplication::translate("Notepad", "Save AS", Q_NULLPTR));
        actionSave_AS->setShortcut(QApplication::translate("Notepad", "Meta+Shift+S", Q_NULLPTR));
        label->setText(QApplication::translate("Notepad", "Assembly Language Window", Q_NULLPTR));
        label_2->setText(QApplication::translate("Notepad", "Machine Language Window", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Notepad", "ASM->BIN", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Notepad", "BIN->ASM", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Notepad", "Clear Assembly Language", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("Notepad", "Clear Machine Language", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("Notepad", "ASM", Q_NULLPTR));
        menuBIN->setTitle(QApplication::translate("Notepad", "BIN", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Notepad: public Ui_Notepad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAD_H
