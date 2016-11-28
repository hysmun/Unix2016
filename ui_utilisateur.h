/********************************************************************************
** Form generated from reading UI file 'utilisateur.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UTILISATEUR_H
#define UI_UTILISATEUR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Utilisateur
{
public:
    QWidget *centralWidget;
    QLabel *labelUtilisateur;
    QLineEdit *lineUtilisateur;
    QPushButton *ButtonDeconnecter;
    QPushButton *ButtonLogin;
    QCheckBox *checkBox4;
    QCheckBox *checkBox5;
    QPushButton *ButtonRechercher;
    QPushButton *ButtonModifier;
    QLineEdit *linePersonne5;
    QLineEdit *lineNom;
    QLabel *labelPersonneConnectee;
    QCheckBox *checkBox1;
    QLabel *Renseignements;
    QLineEdit *linePersonne1;
    QCheckBox *checkBox3;
    QLineEdit *linePersonne2;
    QLineEdit *linePersonne4;
    QLineEdit *linePersonne3;
    QCheckBox *checkBox2;
    QLabel *labelNom;
    QLineEdit *lineGsm;
    QLabel *labelGsm;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *ButtonTransferer;
    QPushButton *ButtonTerminer;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Utilisateur)
    {
        if (Utilisateur->objectName().isEmpty())
            Utilisateur->setObjectName(QString::fromUtf8("Utilisateur"));
        Utilisateur->resize(640, 400);
        centralWidget = new QWidget(Utilisateur);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        labelUtilisateur = new QLabel(centralWidget);
        labelUtilisateur->setObjectName(QString::fromUtf8("labelUtilisateur"));
        labelUtilisateur->setGeometry(QRect(20, 10, 50, 15));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelUtilisateur->setFont(font);
        lineUtilisateur = new QLineEdit(centralWidget);
        lineUtilisateur->setObjectName(QString::fromUtf8("lineUtilisateur"));
        lineUtilisateur->setGeometry(QRect(90, 10, 120, 20));
        ButtonDeconnecter = new QPushButton(centralWidget);
        ButtonDeconnecter->setObjectName(QString::fromUtf8("ButtonDeconnecter"));
        ButtonDeconnecter->setGeometry(QRect(520, 10, 100, 25));
        ButtonLogin = new QPushButton(centralWidget);
        ButtonLogin->setObjectName(QString::fromUtf8("ButtonLogin"));
        ButtonLogin->setGeometry(QRect(400, 10, 100, 25));
        checkBox4 = new QCheckBox(centralWidget);
        checkBox4->setObjectName(QString::fromUtf8("checkBox4"));
        checkBox4->setGeometry(QRect(540, 290, 80, 20));
        checkBox5 = new QCheckBox(centralWidget);
        checkBox5->setObjectName(QString::fromUtf8("checkBox5"));
        checkBox5->setGeometry(QRect(540, 320, 80, 20));
        ButtonRechercher = new QPushButton(centralWidget);
        ButtonRechercher->setObjectName(QString::fromUtf8("ButtonRechercher"));
        ButtonRechercher->setGeometry(QRect(400, 140, 100, 25));
        ButtonModifier = new QPushButton(centralWidget);
        ButtonModifier->setObjectName(QString::fromUtf8("ButtonModifier"));
        ButtonModifier->setGeometry(QRect(520, 140, 100, 25));
        linePersonne5 = new QLineEdit(centralWidget);
        linePersonne5->setObjectName(QString::fromUtf8("linePersonne5"));
        linePersonne5->setGeometry(QRect(400, 320, 115, 20));
        linePersonne5->setReadOnly(true);
        lineNom = new QLineEdit(centralWidget);
        lineNom->setObjectName(QString::fromUtf8("lineNom"));
        lineNom->setGeometry(QRect(460, 80, 120, 20));
        labelPersonneConnectee = new QLabel(centralWidget);
        labelPersonneConnectee->setObjectName(QString::fromUtf8("labelPersonneConnectee"));
        labelPersonneConnectee->setGeometry(QRect(400, 180, 180, 15));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        labelPersonneConnectee->setFont(font1);
        checkBox1 = new QCheckBox(centralWidget);
        checkBox1->setObjectName(QString::fromUtf8("checkBox1"));
        checkBox1->setGeometry(QRect(540, 200, 80, 20));
        Renseignements = new QLabel(centralWidget);
        Renseignements->setObjectName(QString::fromUtf8("Renseignements"));
        Renseignements->setGeometry(QRect(400, 60, 180, 15));
        Renseignements->setFont(font1);
        linePersonne1 = new QLineEdit(centralWidget);
        linePersonne1->setObjectName(QString::fromUtf8("linePersonne1"));
        linePersonne1->setGeometry(QRect(400, 200, 115, 20));
        linePersonne1->setReadOnly(true);
        checkBox3 = new QCheckBox(centralWidget);
        checkBox3->setObjectName(QString::fromUtf8("checkBox3"));
        checkBox3->setGeometry(QRect(540, 260, 80, 20));
        linePersonne2 = new QLineEdit(centralWidget);
        linePersonne2->setObjectName(QString::fromUtf8("linePersonne2"));
        linePersonne2->setGeometry(QRect(400, 230, 115, 20));
        linePersonne2->setReadOnly(true);
        linePersonne4 = new QLineEdit(centralWidget);
        linePersonne4->setObjectName(QString::fromUtf8("linePersonne4"));
        linePersonne4->setGeometry(QRect(400, 290, 115, 20));
        linePersonne4->setReadOnly(true);
        linePersonne3 = new QLineEdit(centralWidget);
        linePersonne3->setObjectName(QString::fromUtf8("linePersonne3"));
        linePersonne3->setGeometry(QRect(400, 260, 115, 20));
        linePersonne3->setReadOnly(true);
        checkBox2 = new QCheckBox(centralWidget);
        checkBox2->setObjectName(QString::fromUtf8("checkBox2"));
        checkBox2->setGeometry(QRect(540, 230, 80, 20));
        labelNom = new QLabel(centralWidget);
        labelNom->setObjectName(QString::fromUtf8("labelNom"));
        labelNom->setGeometry(QRect(400, 80, 50, 15));
        lineGsm = new QLineEdit(centralWidget);
        lineGsm->setObjectName(QString::fromUtf8("lineGsm"));
        lineGsm->setGeometry(QRect(460, 110, 120, 20));
        labelGsm = new QLabel(centralWidget);
        labelGsm->setObjectName(QString::fromUtf8("labelGsm"));
        labelGsm->setGeometry(QRect(400, 110, 47, 13));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 40, 360, 260));
        textEdit->setReadOnly(true);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 320, 360, 20));
        ButtonTransferer = new QPushButton(centralWidget);
        ButtonTransferer->setObjectName(QString::fromUtf8("ButtonTransferer"));
        ButtonTransferer->setGeometry(QRect(20, 350, 100, 25));
        ButtonTerminer = new QPushButton(centralWidget);
        ButtonTerminer->setObjectName(QString::fromUtf8("ButtonTerminer"));
        ButtonTerminer->setGeometry(QRect(520, 350, 100, 25));
        Utilisateur->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Utilisateur);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 21));
        Utilisateur->setMenuBar(menuBar);
        statusBar = new QStatusBar(Utilisateur);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Utilisateur->setStatusBar(statusBar);

        retranslateUi(Utilisateur);

        QMetaObject::connectSlotsByName(Utilisateur);
    } // setupUi

    void retranslateUi(QMainWindow *Utilisateur)
    {
        Utilisateur->setWindowTitle(QApplication::translate("Utilisateur", "Utilisateur", 0, QApplication::UnicodeUTF8));
        labelUtilisateur->setText(QApplication::translate("Utilisateur", "Nom :", 0, QApplication::UnicodeUTF8));
        ButtonDeconnecter->setText(QApplication::translate("Utilisateur", "D\303\251connexion", 0, QApplication::UnicodeUTF8));
        ButtonLogin->setText(QApplication::translate("Utilisateur", "Connexion", 0, QApplication::UnicodeUTF8));
        checkBox4->setText(QApplication::translate("Utilisateur", "Accepter", 0, QApplication::UnicodeUTF8));
        checkBox5->setText(QApplication::translate("Utilisateur", "Accepter", 0, QApplication::UnicodeUTF8));
        ButtonRechercher->setText(QApplication::translate("Utilisateur", "Rechercher", 0, QApplication::UnicodeUTF8));
        ButtonModifier->setText(QApplication::translate("Utilisateur", "---", 0, QApplication::UnicodeUTF8));
        labelPersonneConnectee->setText(QApplication::translate("Utilisateur", "Personnes connect\303\251es :", 0, QApplication::UnicodeUTF8));
        checkBox1->setText(QApplication::translate("Utilisateur", "Accepter", 0, QApplication::UnicodeUTF8));
        Renseignements->setText(QApplication::translate("Utilisateur", "Renseignements :", 0, QApplication::UnicodeUTF8));
        checkBox3->setText(QApplication::translate("Utilisateur", "Accepter", 0, QApplication::UnicodeUTF8));
        checkBox2->setText(QApplication::translate("Utilisateur", "Accepter", 0, QApplication::UnicodeUTF8));
        labelNom->setText(QApplication::translate("Utilisateur", "Nom :", 0, QApplication::UnicodeUTF8));
        labelGsm->setText(QApplication::translate("Utilisateur", "Gsm :", 0, QApplication::UnicodeUTF8));
        ButtonTransferer->setText(QApplication::translate("Utilisateur", "Transf\303\251rer", 0, QApplication::UnicodeUTF8));
        ButtonTerminer->setText(QApplication::translate("Utilisateur", "Terminer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Utilisateur: public Ui_Utilisateur {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UTILISATEUR_H
