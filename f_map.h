#ifndef F_MAP_H_INCLUDED
#define F_MAP_H_INCLUDED
#include "define_info.h"
#include "Classes.h"

void init_map(ALLEGRO_BITMAP* ibloc[NI_BLOCS+1]);
void afficher_map();
int comptage_01(int a);
bool collision_mur(double x,double y);
bool case_vise(int xi,int yi);
void generer_tunnel(int I,int J,int d);
bool collision_mur_object_carre(double x,double y,double tx,double ty);
bool collision_mur_object_carre_destr(double x,double y,double tx,double ty);
void init_joueurs(lance_bombe joueursi[]);
int collision_spherique_joueur_ennemi(double x,double y,int j_allie,double rayon_sphere); //-1: non  i€[0,+infini[ : le jouer i est touché
double distance_bombe_jet_proche(double x,double y);
int i_map(double x);
int j_map(double y);
double x_map(int i);
double y_map(int j);
void coder_map(char* chaine);
void decoder_map(char* mapr);
void coder_double(double nombre,char* packet,int indice);
double decoder_double(char* packet,int indice);
void coder_int(int nombre,char* packet,int indice);
int decoder_int(char* packet,int indice);
void encoder_double(double nombre);
void encoder_int(int nombre);
void encoder_map();
void encoder_mapr();
double decoder_doubler();
int decoder_intr();
void Codage_donnees(lance_bombe j[NBRE_JOUEURS]);
char* get_packet();
void encoder_charactere(char* chaine,char charactere);
void recevoir_touches(char* packet);
#endif // F_MAP_H_INCLUDED
