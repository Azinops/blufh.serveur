#ifndef SOCKETS_H_INCLUDED
#define SOCKETS_H_INCLUDED

#define AFFICHER_MSG 0
#define PORT_EMETTEUR 33333
#define PORT_RECEPTEUR 29979
#define TAILLE_SOCKET 32000//Taille de la chaine de charactere max à envoyer/recevoir


void init_w(char adr_ip[]);
void init_soc_receptrice();
void fermer_socket();
void envoyer_msg(char msg[]);
char* recevoir_msg();
void fermer_socket_receptrice();
#endif // SOCKETS_H_INCLUDED
