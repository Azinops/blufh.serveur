#ifndef CLIENT_SOCKETS_H_INCLUDED
#define CLIENT_SOCKETS_H_INCLUDED
#include <winsock2.h> // pour les fonctions socket
#include <cstdio> // Pour les Sprintf
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include "sockets.h"

WSADATA initialisation_win32; // Variable permettant de r�cup�rer la structure d'information sur l'initialisation
int erreur; // Variable permettant de r�cup�rer la valeur de retour des fonctions utilis�es
int tempo; // Variable temporaire de type int
int nombre_de_caractere; // Indique le nombre de caract�res qui a �t� re�u ou envoy�
char buffer[NBRE_CHARACTERE_MAX]; // Tampon contennant les donn�es re�ues ou envoy�es
SOCKET id_de_la_socket; // Identifiant de la socket
SOCKET id_de_la_socket2; // Identifiant de la socket
SOCKADDR_IN information_sur_la_destination; // D�claration de la structure des informations li� au serveur
SOCKET id_de_la_nouvelle_socket; // Identifiant de la nouvelle socket
SOCKADDR_IN information_sur_la_source; // D�claration de la structure des informations li� � l'�coute

#endif // CLIENT_SOCKETS_H_INCLUDED
