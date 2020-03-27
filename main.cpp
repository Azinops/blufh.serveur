#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <windows.h>
#include <math.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#include "fonctions.h"
#include "affichage.h"
#include "variables_main.h"
#include "souris_clavier.h"
#include "Classes.h"
#include "f_map.h"
#include "f_main.h"
#include "sockets.h"
#define IP "192.168.1.35"

using namespace std;

int main()
{
    plein_ecran();
    INITIALISER_BIBLIOTHEQUE
    srand(time(NULL));
    Souris_clavier moukey;

    cout<<"CHARGEMENT"<<endl;
    INITIALISER_IMAGE_EN_MASSE(iLance_bombe,NI_LANCES_BOMBES,"./images/lances_bombes/")
    INITIALISER_IMAGE_EN_MASSE(iBlocs,NI_BLOCS,"./images/blocs/")
    INITIALISER_IMAGE_EN_MASSE(iExplo1,NI_EXPLO1,"./images/explosion_bombe_jetable/")
    INITIALISER_IMAGE_EN_MASSE(iExplo3,NI_EXPLO3,"./images/explosion_centre_bombe_croix/")
    INITIALISER_IMAGE_EN_MASSE(iBombes,NI_BOMBES,"./images/bombes/")
    INITIALISER_IMAGE_EN_MASSE(iExplo2,NI_EXPLO2,"./images/explosion_croix/")
    INITIALISER_IMAGE_EN_MASSE(iExplo4,NI_EXPLO4,"./images/explosion_croix2/")
    cout<<endl<<"Fini"<<endl;

    bombe bombe_de_jet(iBombes[1],iExplo1,0,iExplo4,TAILLE_EXPLO3I,TAILLE_EXPLO4I,NI_EXPLO1,NI_EXPLO4,VITESSE_ANIM_BOMBE,VITESSE_ANIM_BOMBE_CROIX2);
    bombe bombe_pieges(iBombes[1],iExplo3,1,iExplo2,TAILLE_EXPLO3I,TAILLE_EXPLO2I,NI_EXPLO3,NI_EXPLO2,VITESSE_ANIM_BOMBE2,VITESSE_ANIM_BOMBE_CROIX);

    init_map(iBlocs);

    lance_bombe joueurs[NBRE_JOUEURS];
    lance_bombe joueurs_i[NBRE_JOUEURS];
    joueurs[0]=lance_bombe(iLance_bombe[1],TAILLEC_LB_I,ALLEGRO_KEY_Z,ALLEGRO_KEY_S,ALLEGRO_KEY_Q,ALLEGRO_KEY_D,ALLEGRO_KEY_SPACE,0,bombe_de_jet,bombe_pieges,ALLEGRO_KEY_E,ALLEGRO_KEY_LSHIFT);
    joueurs[0].tp(TAILLE_BLOCX*1.50,TAILLE_BLOCY*1.50);
    joueurs[1]=lance_bombe(iLance_bombe[2],TAILLEC_LB_I,ALLEGRO_KEY_UP,ALLEGRO_KEY_DOWN,ALLEGRO_KEY_LEFT,ALLEGRO_KEY_RIGHT,ALLEGRO_KEY_PAD_0,1,bombe_de_jet,bombe_pieges,ALLEGRO_KEY_PAD_1,ALLEGRO_KEY_RCTRL);
    joueurs[1].tp(XBASED-TAILLE_BLOCX*1.50,YBASED-TAILLE_BLOCY*1.50);
    copier_joueurs(joueurs_i,joueurs);
    INITIALISER_FONT(font_scores,"ALGER",int(TAILLE_BLOCY));

    char msg_map[N_CASES_X*N_CASES_Y+1];
    coder_map(msg_map);

    char ip_client[256]=IP;
    //cin>>ip_client;

    init_w(IP);
    init_soc_receptrice();

    char attente[256]="en attente d'un joueur";
    cout<<attente<<endl;

    char *reception_j=NULL;
    reception_j=recevoir_msg();
    cout<<reception_j<<endl;

    envoyer_msg(msg_map);


    al_start_timer(timer);
    while(!fin)
    {
        ESCAPE
        OBTENIRMOUSEETKEY
        EVENT
        if(event.type==ALLEGRO_EVENT_KEY_DOWN && touche_appuyee(TOUCHE_RECOMMENCER))
        {
            init_map(iBlocs);
            copier_joueurs(joueurs,joueurs_i);
            encoder_charactere(msg_map,'M');
            coder_map(msg_map);
            envoyer_msg(msg_map);
        }
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(beigef);
            Codage_donnees(joueurs);
            envoyer_msg(get_packet());
            recevoir_touches(recevoir_msg());
            joueurs[1].jouer_en_ligne();

            init_joueurs(joueurs);
            afficher_map();
            Jouer(joueurs);
            afficher_score(joueurs,font_scores);
            afficher_explosions(joueurs);
            al_flip_display();
        }
    }

    return 0;
}
