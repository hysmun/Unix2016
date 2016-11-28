#include "Fichier.ini"
#include "Ecran.h"
#include <fcntl.h>

typedef struct
{ 
	char	NomUtilisateur[20];
	char	Gsm[20];
} UTILISATEUR;

UTILISATEUR		Utilisateur;
MESSAGE			M;

int main(int argc,char* argv[])
{
	int	hd, rc, idQ;
	Trace("Debut");

}
