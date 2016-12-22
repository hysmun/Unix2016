.SILENT:
TMP = "default"



all:
	clear
	clear
	echo make all
	make CreeFichierUtilisateur
	make AccesFichier
	make Utilisateur
	make Serveur
	

Ecran.o: 
	echo Création de Ecran.o
	g++ -m64 -c $(HOME)/Ecran/Ecran.cpp -D LINUX

main.o: main.cpp Fichier.ini
	echo création de main.o
	g++ -c -m64 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__ -O2 -Wall -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I. -I/opt/Qt4.8/include/QtCore -I/opt/Qt4.8/include/QtGui -I/opt/Qt4.8/include -I $(HOME)/Ecran -I/usr/include -I/usr/X11/include -o main.o main.cpp

utilisateur.o: utilisateur.cpp Fichier.ini
	echo création de utilisateur.o
	g++ -c -m64 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__ -O2 -Wall -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I. -I/opt/Qt4.8/include/QtCore -I/opt/Qt4.8/include/QtGui -I/opt/Qt4.8/include -I $(HOME)/Ecran -I/usr/include -I/usr/X11/include -o utilisateur.o utilisateur.cpp

moc_utilisateur.o: moc_utilisateur.cpp
	echo création de moc_utilisateur.o
	g++ -c -m64 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__ -O2 -Wall -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I. -I/opt/Qt4.8/include/QtCore -I/opt/Qt4.8/include/QtGui -I/opt/Qt4.8/include -I $(HOME)/Ecran -I/usr/include -I/usr/X11/include -o moc_utilisateur.o moc_utilisateur.cpp

Utilisateur: Ecran.o main.o  utilisateur.o  moc_utilisateur.o
	echo création de Utilisateur
	g++ -m64 -Wl,-R,/opt/Qt4.8/lib -o Utilisateur Ecran.o main.o  utilisateur.o  moc_utilisateur.o -L/usr/lib/64 -L/usr/X11/lib/64 -L/opt/Qt4.8/lib -lQtGui -L/opt/Qt4.8/lib -L/usr/lib/64 -L/usr/X11/lib/64 -lQtCore -lpthread -lrt

Serveur: Ecran.o Serveur.cpp Fichier.ini
	echo Création de Serveur
	g++ -m64 Serveur.cpp -o Serveur -I $(HOME)/Ecran Ecran.o

AccesFichier: Ecran.o AccesFichier.cpp Fichier.ini
	echo Création de AccesFichier
	g++ -m64 AccesFichier.cpp -o AccesFichier -I $(HOME)/Ecran Ecran.o

CreeFichierUtilisateur: Ecran.o CreeFichierUtilisateur.cpp
	echo Création de CreeFichierUtilisateur
	g++ -m64 CreeFichierUtilisateur.cpp -o CreeFichierUtilisateur -I $(HOME)/Ecran Ecran.o






clean:
	clear
	clear
	echo clean
	rm -f *.o makefile~ *.o~ CreeFichierUtilisateur Serveur Utilisateur *.dat
	make CreeFichierUtilisateur
	./CreeFichierUtilisateur


git:
	clear
	clear
	git add -A
	git commit -m "$(TMP)"
	git push


ipcrm:
	clear
	ipcrm -Q 1337
	ipcrm -M 1337
	ipcrm -S 1337

runUti:
	clear
	clear
	echo Utilisateur lancer 4 fois
	./Utilisateur &
	./Utilisateur &
	./Utilisateur &
	./Utilisateur &














