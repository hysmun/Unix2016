#include "utilisateur.h"
#include "ui_utilisateur.h"

#include "Ecran.h"
#include "Fichier.ini"

extern MESSAGE	M;
extern int idMsg;
extern Utilisateur* w;

void HNouvelUtilisateur(int);
void HNouveauMessage(int);
void HTimeOut(int);

bool enModification = false;

//enCours = etat de la connection (login)
bool enCours = false;
char nomLogin[20];

Utilisateur::Utilisateur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Utilisateur) {
    
	ui->setupUi(this);
    
    //Armement des signaux : nouvel utilisateur connecté
    struct sigaction action;
    action.sa_handler = HNouvelUtilisateur;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGUSR1, &action, NULL) == -1)
    	printf("Erreur d armement du signal SIGUSR1\n");
}

Utilisateur::~Utilisateur() {   
    delete ui;
}

void Utilisateur::on_ButtonLogin_clicked()
{

   Trace("Dans on_ButtonLogin_clicked");
   if (enCours) return;
   if (ui->lineUtilisateur->text().size() == 0) return;
   Trace("en cours");
   enCours = true;
	M.Type = 1L;
	M.idPid = getpid();
	M.Requete = LOGIN;
	strcpy(M.Donnee, ui->lineUtilisateur->text().toStdString().c_str());
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	strcpy(nomLogin, ui->lineUtilisateur->text().toStdString().c_str());
}

void Utilisateur::on_ButtonDeconnecter_clicked() 
{
	Trace("Dans on_ButtonDeconnecter_clicked");
	
	if (!enCours) return;
   
	enCours = false;
	Trace("plus en cours");
	M.Type = 1L;
	M.idPid = getpid();
	M.Requete = DECONNEXION;
	// a vous la suite
	// ...
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	setUtilisateur("");
	setPersonne1("");
	setPersonne2("");
	setPersonne3("");
	setPersonne4("");
	setPersonne5("");
	setChechBox1(false);
	setChechBox2(false);
	setChechBox3(false);
	setChechBox4(false);
	setChechBox5(false);

	setNom("");
	setGsm("");
	ui->textEdit->clear();
}

pid_t		idAccesFichier;

void Utilisateur::on_ButtonRechercher_clicked()
{

    Trace("Dans on_ButtonRechercher_clicked\n");
    if (enModification)
       {
       ui->ButtonRechercher->setText("Rechercher");
		 ui->ButtonModifier->setText("---");
		 ui->lineNom->clear();
		 ui->lineGsm->clear();
		  // ...
       return;
       } 
		// ...
		
//		
//		if (M.Requete = RECHERCHEPERSONNEL)
//			{enModification = true;
//			ui->ButtonRechercher->setText("Annuler");
//			ui->ButtonModifier->setText("Modifier");
//			}
		
		
		//...
}

void Utilisateur::on_ButtonModifier_clicked()
{

	Trace("Dans on_ButtonModifier_clicked\n");
	if (!enModification) return;
	ui->ButtonRechercher->setText("Rechercher");
	ui->ButtonModifier->setText("---");
	
  //...
}

void Utilisateur::on_ButtonTransferer_clicked()
{

    Trace("Dans on_ButtonTransferer_clicked\n");
   //

}

void Utilisateur::on_ButtonTerminer_clicked() {
	Trace("Dans on_ButtonTerminer_clicked\n");
	
    //Envoyer un message avec requete = ENDWINDOW
    M.Requete = ENDWINDOW;
    M.Type = 1L;
    M.idPid = getpid();
    if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	exit(0);
}

void Utilisateur::on_checkBox1_clicked()
{

    Trace("Dans on_checkBox1_clicked\n");
    if (ui->checkBox1->isChecked()) 
   { setChechBox1(true) ;
   Trace("true");
     
   }
else
   { setChechBox1(false) ;
     Trace("false");
     
   }

}

void Utilisateur::on_checkBox2_clicked()
{

    Trace("Dans on_checkBox2_clicked\n");
    if (ui->checkBox2->isChecked()) 
   { ui->checkBox2->setChecked(true) ;
   Trace("true");
     
   }
else
   { ui->checkBox2->setChecked(false) ;
     Trace("false");
     
   }

}

void Utilisateur::on_checkBox3_clicked()
{

    Trace("Dans on_checkBox1_clicked\n");
    if (ui->checkBox3->isChecked()) 
   { ui->checkBox3->setChecked(true) ;
   Trace("true");
     
   }
else
   { ui->checkBox3->setChecked(false) ;
     Trace("false");
    
   }

}

void Utilisateur::on_checkBox4_clicked()
{

    Trace("Dans on_checkBox4_clicked\n");
    if (ui->checkBox4->isChecked()) 
   { ui->checkBox3->setChecked(true) ;
   Trace("true");
    
   }
else
   { ui->checkBox4->setChecked(false) ;
     Trace("false");
     
   }

}

void Utilisateur::on_checkBox5_clicked()
{

	Trace("Dans on_checkBox5_clicked\n");
	if (ui->checkBox5->isChecked()) 
	{
		ui->checkBox5->setChecked(true) ;
		Trace("true");
	}
	else
	{
		setChechBox1(false);
     	Trace("false");
	}
}

void Utilisateur::setChechBox1(bool b)
{
	ui->checkBox1->setChecked(b) ;
}
void Utilisateur::setChechBox2(bool b)
{
	ui->checkBox2->setChecked(b) ;
}
void Utilisateur::setChechBox3(bool b)
{
	ui->checkBox3->setChecked(b) ;
}
void Utilisateur::setChechBox4(bool b)
{
	ui->checkBox4->setChecked(b) ;
}
void Utilisateur::setChechBox5(bool b)
{
	ui->checkBox5->setChecked(b) ;
}

void Utilisateur::setPersonne1(const char *T)
{
	if (strlen(T)) ui->linePersonne1->setText(T);
	else ui->linePersonne1->clear();
}

const char* Utilisateur::getPersonne1()const
{
	if (ui->linePersonne1->text().size())
	   return ui->linePersonne1->text().toStdString().c_str();
	   return NULL;
}

void Utilisateur::setPersonne2(const char *T)
{
	if (strlen(T)) ui->linePersonne2->setText(T);
	else ui->linePersonne2->clear();
}

const char* Utilisateur::getPersonne2()const
{
	if (ui->linePersonne2->text().size())
		return ui->linePersonne2->text().toStdString().c_str();
	return NULL;
}

void Utilisateur::setPersonne3(const char *T)
{
	if (strlen(T)) ui->linePersonne3->setText(T);
	else ui->linePersonne3->clear();
}

const char* Utilisateur::getPersonne3()const
{
	if (ui->linePersonne3->text().size())
		return ui->linePersonne3->text().toStdString().c_str();
	return NULL;
}

void Utilisateur::setPersonne4(const char *T)
{
	if (strlen(T)) ui->linePersonne4->setText(T);
	else ui->linePersonne4->clear();
}

const char* Utilisateur::getPersonne4()const
{
	if (ui->linePersonne4->text().size())
		return ui->linePersonne4->text().toStdString().c_str();
	return NULL;
}

void Utilisateur::setPersonne5(const char *T)
{
	if (strlen(T)) ui->linePersonne5->setText(T);
	else ui->linePersonne5->clear();
}

const char* Utilisateur::getPersonne5()const
{
	if (ui->linePersonne5->text().size())
		return ui->linePersonne5->text().toStdString().c_str();
	return NULL;
}

void Utilisateur::setNom(const char* T)
{
	if (strlen(T)) ui->lineNom->setText(T);
	else ui->lineNom->clear();
}

void Utilisateur::setGsm(const char* T)
{
	if (strlen(T)) ui->lineGsm->setText(T);
	else ui->lineGsm->clear();
}

void Utilisateur::setUtilisateur(const char* T)
{
	if (strlen(T)) ui->lineUtilisateur->setText(T);
	else ui->lineUtilisateur->clear();
}

	 
void Utilisateur::setMessage(const char *T)
{
	if (!strlen(T))
	{
		ui->textEdit->clear();
		return;
	}

	char B[10000];
	sprintf(B,"%s%s\n",ui->textEdit->toPlainText().toStdString().c_str(),T);
	ui->textEdit->setText(B);
}

void HNouvelUtilisateur(int Sig)
{
	int rc;
	//Trace("dans HNouvelUtilisateur je suis %s ---> %s", M.Type, M.Donnee);
	if ((rc = msgrcv(idMsg,&M,sizeof(M) - sizeof(long),getpid(),0)) == -1)
	{
		perror("Err.de msgrcv()");
		exit(1);
	}
	
	Trace("dans HNouvelUtilisateur je suis %s ---> %s", nomLogin, M.Donnee);
	if(w->getPersonne1() == NULL)
	{w->setPersonne1(M.Donnee);return;}
	
	if(w->getPersonne2() == NULL)
	{w->setPersonne2(M.Donnee);return;}
	
	if(w->getPersonne3() == NULL)
	{w->setPersonne3(M.Donnee);return;}
	
	if(w->getPersonne4() == NULL)
	{w->setPersonne4(M.Donnee);return;}
	
	if(w->getPersonne5() == NULL)
	{w->setPersonne5(M.Donnee);return;}
	return;
}

void HNouveauMessage(int Sig)
{
	Trace("dans HNouveauMessage");
	w->setMessage(M.Donnee);
}

void HTimeOut(int Sig)
{
	Trace("Reception d'un TimeOut");
}
