#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QMainWindow>

namespace Ui {
class Utilisateur;
}

class Utilisateur : public QMainWindow
{
    Q_OBJECT

public:
    explicit Utilisateur(QWidget *parent = 0);
    ~Utilisateur();
	 void setPersonne1(const char *);
	 const char* getPersonne1()const;
	 void setPersonne2(const char *);
	 const char* getPersonne2()const;
	 void setPersonne3(const char *);
	 const char* getPersonne3()const;
	 void setPersonne4(const char *);
	 const char* getPersonne4()const;
	 void setPersonne5(const char *);
	 const char* getPersonne5()const;
	 void setMessage(const char *);
	 void setChechBox1(bool);
	 void setChechBox2(bool);
	 void setChechBox3(bool);
	 void setChechBox4(bool);
	 void setChechBox5(bool);
	 void setNom(const char*);
	 void setGsm(const char*);
	 void setUtilisateur(const char*);
	 void on_ButtonDeconnecter_clicked();
private slots:
    void on_ButtonLogin_clicked();
   
    void on_ButtonRechercher_clicked();
    void on_ButtonModifier_clicked();
    void on_ButtonTransferer_clicked();
    void on_ButtonTerminer_clicked();
    void on_checkBox1_clicked();
    void on_checkBox2_clicked();
    void on_checkBox3_clicked();
    void on_checkBox4_clicked();
    void on_checkBox5_clicked();

private:
    Ui::Utilisateur *ui;
};

#endif // UTILISATEUR_H
