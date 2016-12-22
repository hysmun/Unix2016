#include "utilisateur.h"
#include "ui_utilisateur.h"

#include "Ecran.h"
#include "Fichier.ini"

#define TIMEALARM (120)

extern MESSAGE	M;
extern int idMsg;
extern Utilisateur* w;

void HNouvelUtilisateur(int);
void HDecoUtilisateur(int sig);
void HNouveauMessage(int);
void HTimeOut(int);
void handlerSIGUSR1(int sig);
pid_t		idAccesFichier;
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
    action.sa_handler = handlerSIGUSR1;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if( sigaction(SIGUSR1, &action, NULL) == -1)
    	printf("Erreur d armement du signal SIGUSR1\n");
    
    action.sa_handler = HTimeOut;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if( sigaction(SIGALRM, &action, NULL ) == -1)
    	Trace("erreur armement signal SIGALRM");
    alarm(TIMEALARM);
}
	
Utilisateur::~Utilisateur() 
{ 
	Trace(" x cliqued");
	M.Type = 1L;
	M.idPid = getpid();
	M.Requete = DECONNEXION;
	// a vous la suite
	// ...
	if(enModification == true)
	{
		M.Requete = ANNULER;
		M.Type = idAccesFichier;
		if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
			perror("Err. de msgsnd()");
	}
	M.idPid = getpid();
	M.Requete = DECONNEXION;
	strcpy(M.Donnee, nomLogin);
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()"); 
	
	alarm(TIMEALARM);
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
	
	alarm(TIMEALARM);
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
	if(enModification == true)
	{
		M.Requete = ANNULER;
		M.Type = idAccesFichier;
		if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
			perror("Err. de msgsnd()");
	}
	M.Type = 1L;
	M.idPid = getpid();
	M.Requete = DECONNEXION;
	strcpy(M.Donnee, nomLogin);
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	strcpy(nomLogin, "");
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



void Utilisateur::on_ButtonRechercher_clicked()
{
	int rc;
	Trace("Dans on_ButtonRechercher_clicked\n");
	if (enModification)
	{
		ui->ButtonRechercher->setText("Rechercher");
		ui->ButtonModifier->setText("---");
		ui->lineNom->clear();
		ui->lineGsm->clear();
		// ...
		M.Requete = ANNULER;
		M.Type = idAccesFichier;
		if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
			perror("Err. de msgsnd()");
		enModification = false;
		return;
	} 
	// ...
	if(strcmp(nomLogin, ui->lineNom->text().toStdString().c_str())==0)
		M.Requete = RECHERCHEPERSONNEL;
	else
		M.Requete = RECHERCHER;
	
	if (M.Requete == RECHERCHEPERSONNEL)
	{
		enModification = true;
		ui->ButtonRechercher->setText("Annuler");
		ui->ButtonModifier->setText("Modifier");
	}
	M.Type = 1L;
	M.idPid = getpid();
	strcpy(M.Donnee,ui->lineNom->text().toStdString().c_str() );
	if ((rc = msgsnd(idMsg,&M,sizeof(MESSAGE) - sizeof(long),0)) == -1)
	{
		perror("Err.de msgsnd()");
		//exit(1);
	}
	alarm(TIMEALARM);
}

void Utilisateur::on_ButtonModifier_clicked()
{
	int rc;
	Trace("Dans on_ButtonModifier_clicked\n");
	if (!enModification) return;
	ui->ButtonRechercher->setText("Rechercher");
	ui->ButtonModifier->setText("---");
	
  //...
	M.Type = idAccesFichier;
	M.idPid = getpid();
	M.Requete = MODIFIER;
	strcpy(M.Donnee,ui->lineGsm->text().toStdString().c_str() );
	if ((rc = msgsnd(idMsg,&M,sizeof(MESSAGE) - sizeof(long),0)) == -1)
	{
		perror("Err.de msgsnd()");
		//exit(1);
	}
	enModification = false;
	alarm(TIMEALARM);
}

void Utilisateur::on_ButtonTransferer_clicked()
{

    Trace("Dans on_ButtonTransferer_clicked\n");
   //
	M.Requete = ENVOYER;
	M.Type = 1L;
	M.idPid = getpid();
	//if(ui->textEdit->text().toStdString().c_str() != NULL)
	strcpy(M.Donnee, ui->lineEdit->text().toStdString().c_str());
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	
	alarm(TIMEALARM);
	return;
}

void Utilisateur::on_ButtonTerminer_clicked() {
	Trace("Dans on_ButtonTerminer_clicked\n");
	
    //Envoyer un message avec requete = ENDWINDOW
    if(enModification == true)
	{
		M.Requete = ANNULER;
		M.Type = idAccesFichier;
		if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
			perror("Err. de msgsnd()");
	}
    M.Requete = ENDWINDOW;
    M.Type = 1L;
    M.idPid = getpid();
    strcpy(M.Donnee, nomLogin);
    if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	exit(0);
}

void Utilisateur::on_checkBox1_clicked()
{
	if(w->getPersonne1() == NULL)
		return;
	
	Trace("Dans on_checkBox1_clicked\n");
	if (ui->checkBox1->isChecked()) 
	{ 
		setChechBox1(true) ;
		Trace("true");
		M.Requete = ACCEPTER;
	}
	else
	{
		setChechBox1(false) ;
		Trace("false");
		M.Requete = REFUSER;
	}
	M.Type = 1L;
	M.idPid = getpid();
	strcpy(M.Donnee, w->getPersonne1());
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	alarm(TIMEALARM);
}

void Utilisateur::on_checkBox2_clicked()
{
	if(w->getPersonne2() == NULL)
		return;
	
	Trace("Dans on_checkBox2_clicked\n");
	if (ui->checkBox2->isChecked()) 
	{
		ui->checkBox2->setChecked(true) ;
		Trace("true");
		M.Requete= ACCEPTER;
	}
	else
	{
		ui->checkBox2->setChecked(false) ;
		Trace("false");
		M.Requete = REFUSER;
	}
	M.Type = 1L;
	M.idPid = getpid();
	strcpy(M.Donnee, getPersonne2());
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	alarm(TIMEALARM);
}

void Utilisateur::on_checkBox3_clicked()
{
	if(w->getPersonne3() == NULL)
		return;
	
	Trace("Dans on_checkBox1_clicked\n");
	if (ui->checkBox3->isChecked()) 
	{
		ui->checkBox3->setChecked(true) ;
		Trace("true");
		M.Requete = ACCEPTER;
	}
	else
	{
		ui->checkBox3->setChecked(false) ;
		Trace("false");
		M.Requete = REFUSER;
	}
	M.Type = 1L;
	M.idPid = getpid();
	strcpy(M.Donnee, w->getPersonne3());
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	alarm(TIMEALARM);
}

void Utilisateur::on_checkBox4_clicked()
{
	if(w->getPersonne4() == NULL)
		return;
	
	Trace("Dans on_checkBox4_clicked\n");
	if (ui->checkBox4->isChecked()) 
	{
		ui->checkBox3->setChecked(true) ;
		Trace("true");
		M.Requete = ACCEPTER;
	}
	else
	{
		ui->checkBox4->setChecked(false) ;
		Trace("false");
		M.Requete = REFUSER;
	}
	M.Type = 1L;
	M.idPid = getpid();
	strcpy(M.Donnee, w->getPersonne4());
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	alarm(TIMEALARM);
}

void Utilisateur::on_checkBox5_clicked()
{
	if(w->getPersonne5() == NULL)
		return;
	
	Trace("Dans on_checkBox5_clicked\n");
	if (ui->checkBox5->isChecked()) 
	{
		ui->checkBox5->setChecked(true) ;
		Trace("true");
		M.Requete = ACCEPTER;
	}
	else
	{
		setChechBox1(false);
	  	Trace("false");
	  	M.Requete = REFUSER;
	}
	M.Type = 1L;
	M.idPid = getpid();
	strcpy(M.Donnee, w->getPersonne5());
	if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
		perror("Err. de msgsnd()");
	alarm(TIMEALARM);
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
	
	Trace("dans HNouvelUtilisateur je suis %s ---> %s", nomLogin, M.Donnee);
	if(w->getPersonne1() == NULL)
	{w->setPersonne1(M.Donnee);}
	else
	{
		if(w->getPersonne2() == NULL)
		{w->setPersonne2(M.Donnee);}
		else
		{
			if(w->getPersonne3() == NULL)
			{w->setPersonne3(M.Donnee);}
			else
			{
				if(w->getPersonne4() == NULL)
				{w->setPersonne4(M.Donnee);}
				else
				{
					if(w->getPersonne5() == NULL)
					{w->setPersonne5(M.Donnee);}
				}
			}
		}
	}
	
	return;
}

void HNouveauMessage(int Sig)
{
	Trace("dans HNouveauMessage je suis %s \net j'ai recu ce message %s", nomLogin, M.Donnee);
	w->setMessage(M.Donnee);
}

void HTimeOut(int Sig)
{
	Trace("Reception d'un TimeOut");
	
	w->on_ButtonDeconnecter_clicked();
}

void HDecoUtilisateur(int sig)
{
	Trace("dans HDecoUtilisateur je suis %s ---> %s", nomLogin, M.Donnee);
	if(strcmp(M.Donnee, w->getPersonne1()) == 0)
	{w->setPersonne1("");return;}
	
	if(strcmp(M.Donnee, w->getPersonne2()) == 0)
	{w->setPersonne2("");return;}
	
	if(strcmp(M.Donnee, w->getPersonne3()) == 0)
	{w->setPersonne3("");return;}
	
	if(strcmp(M.Donnee, w->getPersonne4()) == 0)
	{w->setPersonne4("");return;}
	
	if(strcmp(M.Donnee, w->getPersonne5()) == 0)
	{w->setPersonne5("");return;}
}

void handlerSIGUSR1(int sig)
{
	int rc;
	Trace("handler SIGUSR1 chez %s", nomLogin);
	while ((rc = msgrcv(idMsg,&M,sizeof(MESSAGE) - sizeof(long),getpid(),IPC_NOWAIT)) != -1)
	{
		switch(M.Requete)
		{
			case LOGIN:
				HNouvelUtilisateur(sig);
				break;
			case ENDWINDOW:
			case DECONNEXION:
				HDecoUtilisateur(sig);
				break;
			case ENVOYER:
				HNouveauMessage(sig);
				break;
			case RECHERCHEPERSONNEL:
			case RECHERCHER:
				Trace("dans rechercher %s", M.Donnee);
				w->setGsm(M.Donnee);
				idAccesFichier = M.idPid;
				break;
			default:
				Trace("Erreur !!! %s", nomLogin);
		}
	}
}




































