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

using namespace std;

int main()
{

    plein_ecran();
    INITIALISER_BIBLIOTHEQUE
    srand(time(NULL));
    Souris_clavier moukey;

    cout<<"CHARGEMENT"<<endl;
    INITIALISER_IMAGE_EN_MASSE(iLance_bombe,NI_LANCES_BOMBES,"./images/lances_bombes/")
    ALLEGRO_BITMAP* iBombe=al_load_bitmap("./images/bombes/1.png");
    INITIALISER_IMAGE_EN_MASSE(iBlocs,NI_BLOCS,"./images/blocs/")
    INITIALISER_IMAGE_EN_MASSE(iExplo1,NI_EXPLO1,"./images/explosion_bombe_jetable/")
    INITIALISER_IMAGE_EN_MASSE(iExplo3,NI_EXPLO3,"./images/explosion_centre_bombe_croix/")
    INITIALISER_IMAGE_EN_MASSE(iExplo2,NI_EXPLO2,"./images/explosion_croix/")
    INITIALISER_IMAGE_EN_MASSE(iExplo4,NI_EXPLO4,"./images/explosion_croix2/")
    cout<<endl<<"Fini"<<endl;

    bombe bombe_de_jet(iBombe,iExplo1,0,iExplo4,TAILLE_EXPLO3I,TAILLE_EXPLO4I,NI_EXPLO1,NI_EXPLO4,VITESSE_ANIM_BOMBE,VITESSE_ANIM_BOMBE_CROIX2);
    bombe bombe_pieges(iBombe,iExplo3,1,iExplo2,TAILLE_EXPLO3I,TAILLE_EXPLO2I,NI_EXPLO3,NI_EXPLO2,VITESSE_ANIM_BOMBE2,VITESSE_ANIM_BOMBE_CROIX);

    init_map(iBlocs);

    joueurs[0]=lance_bombe(iLance_bombe[1],TAILLEC_LB_I,ALLEGRO_KEY_Z,ALLEGRO_KEY_S,ALLEGRO_KEY_Q,ALLEGRO_KEY_D,ALLEGRO_KEY_SPACE,0,bombe_de_jet,bombe_pieges,ALLEGRO_KEY_E,ALLEGRO_KEY_LSHIFT);
    joueurs[0].tp(TAILLE_BLOCX*1.50,TAILLE_BLOCY*1.50);
    joueurs[1]=lance_bombe(iLance_bombe[2],TAILLEC_LB_I,ALLEGRO_KEY_UP,ALLEGRO_KEY_DOWN,ALLEGRO_KEY_LEFT,ALLEGRO_KEY_RIGHT,ALLEGRO_KEY_PAD_0,1,bombe_de_jet,bombe_pieges,ALLEGRO_KEY_PAD_1,ALLEGRO_KEY_RCTRL);
    joueurs[1].tp(XBASED-TAILLE_BLOCX*1.50,YBASED-TAILLE_BLOCY*1.50);
    copier_joueurs(joueurs_i,joueurs);
    INITIALISER_FONT(font_scores,"ALGER",int(TAILLE_BLOCY));

    char msg_map[N_CASES_X*N_CASES_Y+1];
    coder_map(msg_map);


    init_w();
    init_soc_receptrice();

    char attente[256]="en attente d'un joueur";
    cout<<attente<<endl;

    char *reception_j=NULL;
    reception_j=recevoir_msg_serveur();
    cout<<reception_j<<endl;


    envoyer_msg_server_to_client(msg_map);
    cout<<"Map envoyee"<<endl;


    char *reception_j2=NULL;
    reception_j2=recevoir_msg_serveur();
    cout<<reception_j2<<", la partie peut commencer"<<endl;

    int type_msg=0;//0:normal 1:nouvelle map  2:quitter
    int ea=0;
    al_start_timer(timer);
    while(!fin)
    {

        OBTENIRMOUSEETKEY
        recevoir_touches(recevoir_msg_serveur());
        fin=joueurs[1].jouer_en_ligne();
        if(!fin)
        {
            al_clear_to_color(beigef);
            type_msg=0;
            init_joueurs(joueurs);
            afficher_map();
            Jouer(joueurs);
            afficher_score(joueurs,font_scores);
            afficher_explosions(joueurs);

            if(touche_appuyee(TOUCHE_RECOMMENCER) && ea==0)
            {
                ea=1;
                type_msg=1;
            }
            if(touche_appuyee(TOUCHE_QUITTER))
            {
                type_msg=2;
            }
            if(type_msg==0)
            {
                if(!touche_appuyee(TOUCHE_RECOMMENCER))
                {
                    ea=0;
                }
                Codage_donnees(joueurs);
                envoyer_msg_server_to_client(get_packet());
            }
            if(type_msg==1)
            {
                init_map(iBlocs);
                copier_joueurs(joueurs,joueurs_i);
                encoder_charactere(msg_map,'M');
                coder_map(msg_map);
                envoyer_msg_server_to_client(msg_map);
            }
            if(type_msg==2)
            {
                envoyer_msg_server_to_client("F");
                fin=1;
            }

        }
        al_flip_display();
    }

    fermer_socket_receptrice();
    return 0;
}
