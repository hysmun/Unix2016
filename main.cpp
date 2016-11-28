#include "utilisateur.h"
#include <QApplication>
#include "Fichier.ini"

Utilisateur* w;
MESSAGE	M;

int idMsg;

int main(int argc, char *argv[])
{
	if ((idMsg = msgget(KEY,0)) == -1) 
	{
		perror("Err. de msgget()");
		exit(1);
	}
	M.Type = 1L;
	M.idPid = getpid();
	M.Requete = NEWWINDOW;
	if (msgsnd(idMsg,&M,sizeof(long)+8,0) == -1)
   	perror("Err. de msgsnd()");
   
	QApplication a(argc, argv);
	w = new Utilisateur;
	w->show();

	return a.exec();
}
