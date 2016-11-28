#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
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

MESSAGE	M;
TABWINDOW	*Tab;
TABSERVEUR*	s;


void AfficheTab();



int main(int argc,char* argv[])
{
	int		rc,i,j,k,idFils, tmp;

	s = (TABSERVEUR*)malloc(sizeof(TABSERVEUR));


	if ((idMsg = msgget(KEY,IPC_CREAT|IPC_EXCL|0600)) == -1)
	{
		if ((idMsg = msgget(KEY,0)) == -1)
	  	exit(1);
	}   
	Trace("1");

	s->Serveur1 = getpid();



	AfficheTab();

	while(1)
	{
		if ((rc = msgrcv(idMsg,&M,sizeof(M) - sizeof(long),1,0)) == -1)
		{
			perror("Err.de msgrcv()");
			exit(1);
		}
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
			case ENDWINDOW:
				Trace("dans ENDWINDOW (%d)",M.Requete);
			  // ...
			  // prevenir les utilisateurs d'une deconnexion ou fin 
			 	for(i=0; i<NBMAX; i++)
			 	{
			 		//msgsnd()
			 	}
			  // vider Tab de la deconnexion pour l'utilisateur
				for(i=0; i<NBMAX; i++)
				{
					if(s->Tab[i].idPid == M.idPid)
					{
						strcpy(s->Tab[i].NomUtilisateur, "\0");
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
						//(M.idPid, SIGUSR1);
						//a verifier !!!!!!
			 			while (msgsnd(idMsg, &M, sizeof(MESSAGE)  - sizeof(long), IPC_NOWAIT) != -1);
							//perror("Err. de msgsnd()");
						kill(M.idPid, SIGUSR1);
						//sleep(1);
					}
				}
				break;

			case RECHERCHER:
			case RECHERCHEPERSONNEL:
				 	Trace("dans RECHERCHER");
				 	
				break;

			case ENVOYER:
				Trace("Dans ENVOYER (%s)",M.Donnee);
						  
				break;

			case ACCEPTER:
					Trace("dans ACCEPTER");
					// recherche de la personne qui émet 
		
					// recherche id de la personne acceptee   
		
					// Ajout id de la personne acceptee
		
			  AfficheTab();
				break;

			case REFUSER:
				 	Trace("dans REFUSER");
				 	// recherche de la personne qui émet 
		
					// Ajout id de la personne refusee
		
					// suppression id de la personne acceptee
		
				AfficheTab();	
				break;
		}
	}

	exit(0);
}

void AfficheTab()
{
	int i = 0;
	printf("pid du Serveur1 : %d\n",s->Serveur1);
	//printf("pid du Serveur2 : %d\n\n",s->Serveur2);
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





























