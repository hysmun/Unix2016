#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

#include "Fichier.ini"
#include "Ecran.h"

/*
typedef struct {
	long Type; //destinataire
	pid_t idPid; //envoyeur
	int	Requete;
	char Donnee[255];
} MESSAGE;


typedef struct {
	pid_t idPid;
	char NomUtilisateur[20];
	int Autre[NBMAX];
} TABWINDOW;

typedef struct {
	pid_t Serveur1;
	pid_t Serveur2;
	TABWINDOW Tab[NBMAX];
} TABSERVEUR;

#define		KEY						(key_t)1234

*/
pid_t			AAA;

int idMsg;
int idShm;
int idMem;
int idSem;
int idFils;

MESSAGE	M;
TABWINDOW	*Tab;
TABSERVEUR*	s;
char strTmp[254];


void AfficheTab();
int SemWait(int Sema);
int SemSignal(int Sema);



int main(int argc,char* argv[])
{
	int		rc,i,j,k,idFils, tmp;

	//s = (TABSERVEUR*)malloc(sizeof(TABSERVEUR));

	// file message
	if ((idMsg = msgget(KEY,IPC_CREAT|IPC_EXCL|0600)) == -1)
	{
		if ((idMsg = msgget(KEY,0)) == -1)
	  	exit(1);
	}
	
	//memoire partager
	if((idMem = shmget(KEY,sizeof(TABSERVEUR) ,IPC_CREAT|IPC_EXCL|0600)) == -1);
	{
		if ((idMem = shmget(KEY,sizeof(TABSERVEUR),0)) == -1)
	  		exit(1);
	}
	
	// sémaphore
	if((idSem = semget(KEY, 1 ,IPC_CREAT|IPC_EXCL|0600)) == -1);
	{
		if ((idSem = semget(KEY,1,0)) == -1)
	  		exit(1);
	}
	
	
	s = (TABSERVEUR *)shmat(idMem, NULL, 0);
	
	Trace("1");
	if(s->Serveur1 == 0)
		s->Serveur1 = getpid();
	else
		s->Serveur2 = getpid();



	AfficheTab();

	while(1)
	{
		if ((rc = msgrcv(idMsg,&M,sizeof(M) - sizeof(long),1,0)) == -1)
		{
			perror("Err.de msgrcv()");
			exit(1);
		}
		SemSignal(0);
		Trace("Message recu");
		switch(M.Requete)
		{ 
			case NEWWINDOW:
				Trace("dans NEWWINDOW");
				for(i=0; i<NBMAX; i++)
				{
					if(s->Tab[i].idPid == 0)
					{
						s->Tab[i].idPid = M.idPid;
						i= NBMAX;
					}	
					
				}
				AfficheTab();
				
				break;
			case DECONNEXION:
				Trace("deconnexion");
			case ENDWINDOW:
				Trace("dans ENDWINDOW (%d) -- %s",M.Requete, M.Donnee);
				// ...
				tmp = -1;
				for(i=0; i<NBMAX; i++)
				{
					if(strcmp(s->Tab[i].NomUtilisateur, M.Donnee) == 0)
					{
						tmp = i;
						i = NBMAX;
					}
				}
				// prevenir les utilisateurs d'une deconnexion ou fin 
			 	for(i=0; i<NBMAX; i++)
			 	{
			 		//msgsnd()
			 		if((strlen(s->Tab[i].NomUtilisateur) != 0) && i != tmp)
			 		{
			 			//strcpy(M.Donnee, M.Donnee);
			 			if(strlen(M.Donnee) > 0)
			 			{
					 		M.Type = s->Tab[i].idPid;
					 		kill(s->Tab[i].idPid, SIGUSR1);
					 		if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
									perror("Err. de msgsnd()");
						}
						for(j=0; j<NBMAX;j++)
						{
							if(s->Tab[i].Autre[j] == M.idPid)
								s->Tab[i].Autre[j] =0;
						}
						
					}
			 	}
			  // vider Tab de la deconnexion pour l'utilisateur
				for(i=0; i<NBMAX; i++)
				{
					if(s->Tab[i].idPid == M.idPid)
					{
						strcpy(s->Tab[i].NomUtilisateur, "");
						if(M.Requete == ENDWINDOW)
							s->Tab[i].idPid = 0;
						for(j=0; j<NBMAX;j++)
							s->Tab[i].Autre[j] = 0;
						i=NBMAX;
					}
				}
				AfficheTab();
				break;
			case LOGIN:
				Trace("dans LOGIN (%s)",M.Donnee);
			 	// Recherche d'une place libre
			 	for(i=0; i<NBMAX; i++)
			 	{
			 		if(s->Tab[i].idPid == M.idPid)
			 		{
			 			strcpy(s->Tab[i].NomUtilisateur, M.Donnee);
			 			tmp = i;
			 			i = NBMAX;
			 		}
			 	}
			  	AfficheTab();
				// Emission aux utilisateurs connectés
				for(i=0; i<NBMAX; i++)
			 	{
			 		if((strlen(s->Tab[i].NomUtilisateur) != 0)  && i != tmp)
			 		{
			 			//envoyer a cette utilisateur le login d'un nouveau
			 			Trace("Hello envois connection de %s ----> %s",s->Tab[tmp].NomUtilisateur, s->Tab[i].NomUtilisateur );
			 			M.Type = s->Tab[i].idPid;
			 			strcpy(M.Donnee, s->Tab[tmp].NomUtilisateur);
			 			kill(s->Tab[i].idPid, SIGUSR1);
			 			if (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
							perror("Err. de msgsnd()");
						//kill(s->Tab[i].idPid, SIGUSR1);
			 		}
			 	}
				// Emission des utilisateurs connectés
				M.Type = M.idPid;
				for(i=0; i<NBMAX; i++)
				{
					if((strlen(s->Tab[i].NomUtilisateur) != 0) && i != tmp)
					{
						Trace("envois des uti %s connecter à %s",s->Tab[i].NomUtilisateur, s->Tab[tmp].NomUtilisateur );
						strcpy(M.Donnee,s->Tab[i].NomUtilisateur);
						kill(M.idPid, SIGUSR1);
						//a verifier !!!!!!
			 			if(msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
							perror("Err. de msgsnd()");
						//kill(M.idPid, SIGUSR1);
						//sleep(1);
					}
				}
				break;

			case RECHERCHER:
			case RECHERCHEPERSONNEL:
				 	Trace("dans RECHERCHER");
				 	if((idFils = fork()))
				 	{
				 		// Pere
				 		M.Type = idFils;
				 		if(msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
							perror("Err. de msgsnd()");
						Trace("Pere");
				 	}
				 	else
				 	{
				 		// Fils
				 		Trace("FILS");
				 		sprintf(strTmp, "%d",idMsg);
				 		execlp("./AccesFichier","AccesFichier",strTmp, NULL);
				 		Trace("exec fail");
				 		exit(0);
				 	}
				 	
				break;
			case ENVOYER:
				Trace("Dans ENVOYER (%s)",M.Donnee);
				// recherche de la personne qui envois
				tmp = -1;
				for(i=0; i<NBMAX; i++)
				{
					if(s->Tab[i].idPid== M.idPid )
					{
						tmp = i;
						i = NBMAX;
					}
				}
				// envois du message au utilisateur accepter
				sprintf(strTmp, "(%s): %s", s->Tab[tmp].NomUtilisateur, M.Donnee);
				strcpy(M.Donnee, strTmp);
				for(i=0; i<NBMAX; i++)
				{
					if(s->Tab[tmp].Autre[i] != 0 )
					{
						
						
						Trace("Envois messages a %d -- %s", s->Tab[tmp].Autre[i], M.Donnee);
						M.Type = s->Tab[tmp].Autre[i];
						kill(s->Tab[tmp].Autre[i], SIGUSR1);
						//a verifier !!!!!!
			 			if(msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), 0) == -1)
							perror("Err. de msgsnd()");
					}
				}
				break;
			case ACCEPTER:
					Trace("dans ACCEPTER");
					// recherche de la personne qui émet 
					tmp = -1;
					for(i=0; i<NBMAX; i++)
					{
						if(s->Tab[i].idPid== M.idPid )
						{
							tmp = i;
							i = NBMAX;
						}
					}
					// recherche id de la personne acceptee   
					j = -1;
					for(i=0; i<NBMAX; i++)
					{
						if(strcmp(s->Tab[i].NomUtilisateur, M.Donnee) == 0)
						{
							j = s->Tab[i].idPid;
							i = NBMAX;
						}
					}
					// Ajout id de la personne acceptee
					for(i=0; i< NBMAX; i++)
					{
						if(s->Tab[tmp].Autre[i] == 0)
						{
							s->Tab[tmp].Autre[i] = j;
							i = NBMAX;
						}
					}
			  AfficheTab();
				break;

			case REFUSER:
				 	Trace("dans REFUSER %s ", M.Donnee);
				 	// recherche de la personne qui émet 
					tmp = -1;
					for(i=0; i<NBMAX; i++)
					{
						if(s->Tab[i].idPid == M.idPid )
						{
							tmp = i;
							i = NBMAX;
						}
					}
					// recherche  id de la personne refusee  
					j = -1;
					for(i=0; i<NBMAX; i++)
					{
						if(strcmp(s->Tab[i].NomUtilisateur, M.Donnee) == 0)
						{
							j = s->Tab[i].idPid;
							i = NBMAX;
						}
					}
					// suppression id de la personne acceptee
					for(i=0; i<NBMAX; i++)
					{
						if(s->Tab[tmp].Autre[i] == j)
						{
							s->Tab[tmp].Autre[i]=0;
						}
					}
				AfficheTab();	
				break;
			
		}
		SemWait(0);
	}

	exit(0);
}

void AfficheTab()
{
	int i = 0;
	printf("pid du Serveur1 : %d\n",s->Serveur1);
	printf("pid du Serveur2 : %d\n\n",s->Serveur2);
	printf("Tab :\n");
	while (i < NBMAX) 
		{ printf("%5d --%-10s-- %5d %5d %5d %5d %5d\n",
			   s->Tab[i].idPid, s->Tab[i].NomUtilisateur,
			   s->Tab[i].Autre[0], s->Tab[i].Autre[1], s->Tab[i].Autre[2],
			   s->Tab[i].Autre[3], s->Tab[i].Autre[4]);
		  i++;
		}

	return ;
}


int SemWait(int Sema)
{
	struct sembuf SemOp;
	
	SemOp.sem_num = Sema;
	SemOp.sem_op = -1;
	SemOp.sem_flg = SEM_UNDO;
	
	return semop(idSem, &SemOp, 1);
}

int SemSignal(int Sema)
{
	struct sembuf SemOp;
	
	SemOp.sem_num = Sema;
	SemOp.sem_op = +1;
	SemOp.sem_flg = SEM_UNDO;
	
	return semop(idSem, &SemOp, 1);
}
























