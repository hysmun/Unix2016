#include "Fichier.ini"
#include "Ecran.h"
#include <fcntl.h>



//int fcntl(int fd, int cmd, ... /* arg */ );
//F_SETLK, F_SETLKW, and F_GETLK 
//struct flock {
//               ...
//               short l_type;    /* Type of lock: F_RDLCK,
//                                   F_WRLCK, F_UNLCK */
//               short l_whence;  /* How to interpret l_start:
//                                   SEEK_SET, SEEK_CUR, SEEK_END */
//               off_t l_start;   /* Starting offset for lock */
//               off_t l_len;     /* Number of bytes to lock */
//               pid_t l_pid;     /* PID of process blocking our lock
//                                   (set by F_GETLK and F_OFD_GETLK) */
//               ...
//           };

typedef struct
{ 
	char	NomUtilisateur[20];
	char	Gsm[20];
} UTILISATEUR;

UTILISATEUR		Utilisateur;
MESSAGE			M;
int idMsg;
int idUti;
int pf;
UTILISATEUR buf;
char nomUti[20];

struct flock lkFile, lkTest;
short typelk;

int main(int argc,char* argv[])
{
	int	hd, rc, idQ, i, j, REQ;
	
	//ini des lock;
	lkFile.l_whence = SEEK_SET;
	lkFile.l_pid = getpid();
	lkFile.l_len = sizeof(UTILISATEUR);
	
	Trace("Debut");
	idMsg = atoi(argv[1]);
	if ((rc = msgrcv(idMsg,&M,sizeof(MESSAGE) - sizeof(long),getpid(),0)) == -1)
	{
		perror("Err.de msgrcv()");
		exit(1);
	}
	REQ = M.Requete;
	idUti = M.idPid;
	Trace("AccesFichier Message recu %s de %d", M.Donnee, M.idPid);
	strcpy(nomUti, M.Donnee);
	
	//traitement
	//ouverture fichier
	if(M.Requete == RECHERCHEPERSONNEL)
	{
		pf=open("Utilisateur.dat", O_RDWR);
		typelk = F_WRLCK;
	}
	if(M.Requete == RECHERCHER)
	{
		pf=open("Utilisateur.dat", O_RDONLY);
		typelk = F_RDLCK;
	}
	
	if(pf == -1 )
	{
		Trace("Erreur ouverture fichier");
		perror(NULL);
		exit(-1);
	}
	
	lkTest.l_whence = SEEK_SET;
	lkTest.l_pid = getpid();
	lkTest.l_len = sizeof(UTILISATEUR);
	//on passe les enregistrement bloquer
	fcntl(pf,F_GETLK, &lkTest);
	while(lkTest.l_type == F_WRLCK)
	{
		lseek(pf, sizeof(UTILISATEUR), SEEK_CUR);
		fcntl(pf,F_GETLK, &lkTest);
	}
	//on a trouver le premier que l'on peut lire'
	
	lkTest.l_type = F_RDLCK;
	fcntl(pf, F_SETLKW, &lkTest);
	i=read(pf, &buf, sizeof(UTILISATEUR));
	lkTest.l_type =  F_UNLCK;
	fcntl(pf, F_SETLK, &lkTest);
	j=0;
	//on charge dans le fichier l'utilisateur rechercher
	while(i > 0 && j != 1)
	{
		if((hd=strcmp(buf.NomUtilisateur, nomUti)) == 0 )
		{
			j = 1;
			//break;
		}
		if(j!=1)
		{
			lkTest.l_type = F_RDLCK;
			fcntl(pf, F_SETLKW, &lkTest);
			i=read(pf, &buf, sizeof(UTILISATEUR));
			Trace("A");
			lseek(pf,-sizeof(UTILISATEUR), SEEK_CUR);
			lkTest.l_type =  F_UNLCK;
			fcntl(pf, F_SETLK, &lkTest);
			lseek(pf, sizeof(UTILISATEUR), SEEK_CUR);
		}
			
	}
	
	if(j==0)
	{
		Trace("nom trouver");
		strcpy(M.Donnee, "non trouve");
	}
	else
	{
		Trace("trouver");
		strcpy(M.Donnee, buf.Gsm);
		lseek(pf,-sizeof(UTILISATEUR), SEEK_CUR);
		fcntl(pf, F_SETLKW, &lkFile);
		lseek(pf,sizeof(UTILISATEUR), SEEK_CUR);
	}
	
	
	//envois du résultat
	M.Type = idUti;
	M.idPid = getpid();
	M.Requete = RECHERCHER;
	//kill(idUti,SIGUSR1);
	
	if ((rc = msgsnd(idMsg,&M,sizeof(MESSAGE) - sizeof(long),0)) == -1)
	{
		perror("Err.de msgsnd()");
		close(pf);
		exit(1);
	}
	kill(idUti,SIGUSR1);
	Trace("Fin AccesFichier sauf recherche perso %s ", buf.Gsm);
	if(j==0)
	{
		close(pf);
		exit(-1);
	}
	
	if(REQ == RECHERCHEPERSONNEL)
	{
		fcntl(pf, F_SETLKW, &lkFile);
		Trace("recherche perso");
		//seulement dans le cas d une requete personnel
		if ((rc = msgrcv(idMsg,&M,sizeof(MESSAGE) - sizeof(long),getpid(),0)) == -1)
		{
			perror("Err.de msgrcv()");
			close(pf);
			exit(1);
		}
		if(M.Requete == MODIFIER)
		{
			strcpy(buf.Gsm, M.Donnee);
			write(pf, &buf, sizeof(UTILISATEUR));
			Trace("modifier %s", buf.Gsm);
			close(pf);
			exit(1);
		}
		if(M.Requete == ANNULER)
		{
			Trace("Annulation");
			close(pf);
			exit(1);
		}
	}
	Trace("end accesfichier");
	close(pf);
	exit(1);
}
