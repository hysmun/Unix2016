echo Création de Ecran.o
g++ -m64 -c $HOME/Ecran/Ecran.cpp -D SUN

echo création de main.o
g++ -c -m64 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__ -O2 -Wall -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I. -I/opt/Qt4.8/include/QtCore -I/opt/Qt4.8/include/QtGui -I/opt/Qt4.8/include -I $HOME/Ecran -I/usr/include -I/usr/X11/include -o main.o main.cpp

echo création de utilisateur.o
g++ -c -m64 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__ -O2 -Wall -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I. -I/opt/Qt4.8/include/QtCore -I/opt/Qt4.8/include/QtGui -I/opt/Qt4.8/include -I $HOME/Ecran -I/usr/include -I/usr/X11/include -o utilisateur.o utilisateur.cpp

echo création de moc_utilisateur.o
g++ -c -m64 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__ -O2 -Wall -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I. -I/opt/Qt4.8/include/QtCore -I/opt/Qt4.8/include/QtGui -I/opt/Qt4.8/include -I $HOME/Ecran -I/usr/include -I/usr/X11/include -o moc_utilisateur.o moc_utilisateur.cpp

echo création de Utilisateur
g++ -m64 -Wl,-R,/opt/Qt4.8/lib -o Utilisateur Ecran.o main.o  utilisateur.o  moc_utilisateur.o -L/usr/lib/64 -L/usr/X11/lib/64 -L/opt/Qt4.8/lib -lQtGui -L/opt/Qt4.8/lib -L/usr/lib/64 -L/usr/X11/lib/64 -lQtCore -lpthread -lrt

echo Création de Serveur
g++ -m64 Serveur.cpp -o Serveur -I $HOME/Ecran Ecran.o

echo Création de AccesFichier
g++ -m64 AccesFichier.cpp -o AccesFichier -I $HOME/Ecran Ecran.o

echo Création de CreeFichierUtilisateur
g++ -m64 CreeFichierUtilisateur.cpp -o CreeFichierUtilisateur -I $HOME/Ecran Ecran.o

