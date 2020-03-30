#include "map.h"
#include "affichage.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f_map.h"
#include "fonctions.h"
#include "Classes.h"

int comptage_01(int a)
{
    if(a!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void generer_tunnel(int I,int J,int d)
{
    int i=I;
    int j=J;
    MAP[j][i]=1;
    int a;
    while(MAP[j][i]!=0)
    {
        MAP[j][i]=0;
        a=random(1,COEF_LAB2);
        if(a==1)
        {
            if(d==1)
            {
                d=-1;
            }
            else
            {
                d=1;
            }
        }
        if(d==1)
        {
            if(MAP[j-1][i]==0)
            {
                j+=1;
            }
            else
            {
                if(MAP[j+1][i]==0)
                {
                    j-=1;
                }
                else
                {
                    j+=random(0,1)*2-1;
                }
            }
        }
        else
        {
            if(MAP[j][i-1]==0)
            {
                i+=1;
            }
            else
            {
                if(MAP[j][i+1]==0)
                {
                    i-=1;
                }
                else
                {
                    i+=random(0,1)*2-1;
                }
            }
        }
    }
}
void init_map(ALLEGRO_BITMAP* ibloc[])
{
    int i;
    int j;
    for(i=1;i<=NI_BLOCS;i++)
    {
        iBlocs[i]=ibloc[i];
    }
    xim_bloc=al_get_bitmap_width(iBlocs[1]);
    yim_bloc=al_get_bitmap_height(iBlocs[1]);
    for(i=0;i<=N_CASES_Y-1;i++)
    {
        for(j=0;j<=N_CASES_X-1;j++)
        {
            MAP[i][j]=0;
            if(i==N_CASES_Y-1 or i==0 or j==N_CASES_X-1 or j==0)
            {
                MAP[i][j]=1;
            }
        }
    }
    for(i=2;i<=N_CASES_Y-3;i++)
    {
        for(j=2;j<=N_CASES_X-3;j++)
        {
            MAP[i][j]=1;
        }
    }
    int a;
    int d;
    int I;
    int J;
    int k;
    for(I=2;I<=N_CASES_X-3;I++)
    {
        for(J=2;J<=N_CASES_Y-3;J++)
        {
            if(comptage_01(MAP[J-1][I-1])+comptage_01(MAP[J-1][I])+comptage_01(MAP[J-1][I+1])+comptage_01(MAP[J][I-1])+comptage_01(MAP[J][I])
               +comptage_01(MAP[J][I+1])+comptage_01(MAP[J+1][I-1])+comptage_01(MAP[J+1][I])+comptage_01(MAP[J+1][I+1]==9))
            {
                a=random(1,COEF_LAB1);
                if(a==1)
                {
                    d=random(0,1)-1;
                    i=I;
                    j=J;
                    for(k=0;k<=1;k++)
                    {
                        generer_tunnel(i,j,d);
                    }
                }
            }
        }
    }
    int f1=0;
    int f2=0;
    for(k=2;k<=N_CASES_X-4;k++)
    {
        if(MAP[2][k]==0 && f1==0)
        {
            MAP[1][k+1]=1;
            f1=1;
        }
        if(MAP[N_CASES_Y-3][k]==0 && f2==0)
        {
            MAP[N_CASES_Y-2][k-1]=1;
            f2=1;
        }
    }
    for(k=2;k<=N_CASES_X-3;k++)
    {
        if(MAP[1][k+1]==1 && MAP[2][k]==1)
        {
            generer_tunnel(k,2,1);
        }
        if(MAP[N_CASES_Y-2][k+1]==1 && MAP[N_CASES_Y-3][k]==1)
        {
            generer_tunnel(k,N_CASES_Y-3,1);
        }
    }
}
void afficher_map()
{
    int i;
    int j;
    for(i=0;i<=N_CASES_X-1;i++)
    {
        for(j=0;j<=N_CASES_Y-1;j++)
        {
            if(MAP[j][i]!=0)
            {
                afficher_image(iBlocs[MAP[j][i]],0.00,0.00,double(i)*TAILLE_BLOCX,double(j)*TAILLE_BLOCY,TAILLE_BLOCX/xim_bloc,TAILLE_BLOCY/yim_bloc,0.00,0);
            }
        }
    }
}
bool collision_mur(double x,double y)
{
    if(MAP[int(y/YBASED*N_CASES_Y)][int(x/XBASED*N_CASES_X)]!=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool collision_mur_object_carre(double x,double y,double tx,double ty)
{
    tx/=2.00;
    ty/=2.00;
    if(collision_mur(x+tx,y+ty)==true || collision_mur(x+tx,y-ty)==true || collision_mur(x-tx,y+ty)==true || collision_mur(x-tx,y-ty)==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool collision_mur_object_carre_destr(double x,double y,double tx,double ty)
{
    tx/=2.00;
    ty/=2.00;
    int i;
    int j;
    if(DETRUIRE_MUR==1)
    {
        if(collision_mur(x+tx,y+ty)==true)
        {
            i=i_map(x+tx);
            j=j_map(y+ty);
            if(i!=0 && i!=N_CASES_X-1 && j!=0 && j!=N_CASES_Y-1)
            {
                MAP[j][i]=0;
            }
            return true;

        }
        if(collision_mur(x+tx,y-ty)==true)
        {

            i=i_map(x+tx);
            j=j_map(y-ty);
            if(i!=0 && i!=N_CASES_X-1 && j!=0 && j!=N_CASES_Y-1)
            {
                MAP[j][i]=0;
            }
            return true;
        }
        if(collision_mur(x-tx,y+ty)==true)
        {
            i=i_map(x-tx);
            j=j_map(y+ty);
            if(i!=0 && i!=N_CASES_X-1 && j!=0 && j!=N_CASES_Y-1)
            {
                MAP[j][i]=0;
            }
            return true;
        }
        if(collision_mur(x-tx,y-ty)==true)
        {
            i=i_map(x-tx);
            j=j_map(y-ty);
            if(i!=0 && i!=N_CASES_X-1 && j!=0 && j!=N_CASES_Y-1)
            {
                MAP[j][i]=0;
            }
            return true;
        }
    }
    else
    {
        if(collision_mur(x+tx,y+ty)==true || collision_mur(x+tx,y-ty)==true || collision_mur(x-tx,y+ty)==true || collision_mur(x-tx,y-ty)==true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;

}
void init_joueurs(lance_bombe joueursi[])
{
    int k;
    for(k=0;k<=NBRE_JOUEURS-1;k++)
    {
        joueursT[k]=joueursi[k];
    }
}
int collision_spherique_joueur_ennemi(double x,double y,int j_allie,double rayon_sphere)
{
    int k;
    int i;
    double d=double(INFINITE);
    for(k=0;k<=NBRE_JOUEURS-1;k++)
    {
        if(k!=j_allie && joueursT[k].get_vivant()==1)
        {
            if(distance(x,y,joueursT[k].get_x(),joueursT[k].get_y())<=d)
            {
                d=distance(x,y,joueursT[k].get_x(),joueursT[k].get_y());
                i=k;
            }
        }
    }
    if(d<=rayon_sphere)
    {
        return i;
    }
    else
    {
        return -1;
    }
}
double distance_bombe_jet_proche(double x,double y)
{
    int k;
    double d=double(INFINITE);
    double nd;
    int j;
    for(j=0;j<=NBRE_JOUEURS-1;j++)
    {
        for(k=0;k<=NBRE_BOMBES_MAX-1;k++)
        {
            if(joueursT[j].get_etat_bombe_jet(k)!=0)
            {
                nd=distance(x,y,joueursT[j].get_x_bombe_jet(k),joueursT[j].get_y_bombe_jet(k));
                if(nd<d && round(nd)!=0 && (joueursT[j].get_etat_bombe_jet(k)==2 || (joueursT[j].get_etat_bombe_jet(k)==3 && joueursT[j].get_etat_anim_bombe_jet(k)<=DERNIER_ETAT_LETHAL_ANIM_EXPLO1)))
                {
                    d=nd;
                }
            }
        }
    }
    return d;
}
int i_map(double x)
{
    return int(x/XBASED*double(N_CASES_X));
}
int j_map(double y)
{
    return int(y/YBASED*double(N_CASES_Y));
}
double y_map(int j)
{
    return double(j*int(TAILLE_BLOCY));
}

double x_map(int i)
{
    return double(i*int(TAILLE_BLOCX));
}
bool case_vise(int xi,int yi)
{
    if(MAP[yi][xi]==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int bombe::collision_explo_croix_joueur()
{
    int k;
    int i;
    int dx;
    int dy;
    int j_touche=-1;
    int j;
    int ij[NBRE_JOUEURS][2];
    int xi=i_map(x);
    int yi=j_map(y);
    int xp;
    int yp;
    for(k=0;k<=3;k++)
    {
        if(k==0)
        {
            dx=0;
            dy=1;
        }
        if(k==1)
        {
            dx=0;
            dy=-1;
        }
        if(k==2)
        {
            dx=-1;
            dy=0;
        }
        if(k==3)
        {
            dx=1;
            dy=0;
        }
        for(j=0;j<=NBRE_JOUEURS-1;j++)
        {
            ij[j][0]=i_map(joueursT[j].get_x());
            ij[j][1]=j_map(joueursT[j].get_y());
        }
        xp=xi;
        yp=yi;
        for(i=0;i<=n_cases_explosees[k];i++)
        {
            xp+=dx;
            yp+=dy;
            for(j=0;j<=NBRE_JOUEURS-1;j++)
            {
                if(xp==ij[j][0] && yp==ij[j][1] && joueursT[j].get_vivant()==1)
                {
                    if(FRIENDLY_FIRE==0)
                    {
                        if(j!=expediteur)
                        {
                            j_touche=j;
                        }
                    }
                    else
                    {
                        j_touche=j;
                    }
                }
            }
        }
    }
    return j_touche;
}
void coder_map(char* chaine)
{
    int i;
    int j;
    char charactere;
    for(j=0;j<=N_CASES_Y-1;j++)
    {
        for(i=0;i<=N_CASES_X-1;i++)
        {
            switch(MAP[j][i])
            {
            case 0: charactere='0';
                    break;
            case 1:charactere='1';
                    break;
            default:charactere='0';
            }
            chaine[n_encode+i+N_CASES_X*j]=charactere;
        }
    }
}
void decoder_map(char* mapr)
{
    int i;
    int j;
    for(j=0;j<=N_CASES_Y-1;j++)
    {
        for(i=0;i<=N_CASES_X-1;i++)
        {
            MAP[j][i]=int(mapr[i+N_CASES_X*j])-48;
        }
    }
}
void coder_double(double nombre,char* packet,int indice)
{
    int k;
    char chiffre[2];
    double nombre_abs=absd(nombre);
    for(k=0;k<=NBRE_CHIFFRE_CODAGE_DOUBLE-2;k++)
    {
        sprintf(chiffre,"%d",n_ieme_chiffrem(nombre_abs,k-PLACEMENT_VIRGULE_CODAGE_DOUBLE));

        packet[indice+k]=chiffre[0];
    }
    if(nombre>=0.00)
    {
        packet[indice+NBRE_CHIFFRE_CODAGE_DOUBLE-1]='+';
    }
    else
    {
        packet[indice+NBRE_CHIFFRE_CODAGE_DOUBLE-1]='-';
    }
}
double decoder_double(char* packet,int indice)
{
    double rep=0.00;
    int k;
    for(k=0;k<=NBRE_CHIFFRE_CODAGE_DOUBLE-2;k++)
    {
        rep+=double(int(packet[indice+k])-48)*pow(10.00,double(PLACEMENT_VIRGULE_CODAGE_DOUBLE-k));
    }
    if(packet[indice+NBRE_CHIFFRE_CODAGE_DOUBLE-1]=='-')
    {
        rep*=-1.00;
    }
    return rep;
}
void coder_int(int nombre,char* packet,int indice)
{
    int k;
    char chiffre[2];
    int nombre_abs=abs(nombre);
    for(k=0;k<=NBRE_CHIFFRE_CODAGE_INT-2;k++)
    {
        sprintf(chiffre,"%d",n_ieme_chiffremi(nombre_abs,NBRE_CHIFFRE_CODAGE_INT-2-k));

        packet[indice+k]=chiffre[0];
    }
    if(nombre<0)
    {
        packet[indice+NBRE_CHIFFRE_CODAGE_INT-1]='-';
    }
    else
    {
        packet[indice+NBRE_CHIFFRE_CODAGE_INT-1]='+';
    }
}
int decoder_int(char* packet,int indice)
{
    int rep=0;
    int k;
    for(k=0;k<=NBRE_CHIFFRE_CODAGE_INT-2;k++)
    {
        rep+=(int(packet[indice+k])-48)*roundi(pow(10.00,double(NBRE_CHIFFRE_CODAGE_INT-2-k)));
    }
    if(packet[indice+NBRE_CHIFFRE_CODAGE_INT-1]=='-')
    {
        rep*=-1;
    }
    return rep;
}
void encoder_double(double nombre)
{
    coder_double(nombre,PACKET_INFO,n_encode);
    n_encode+=NBRE_CHIFFRE_CODAGE_DOUBLE;
}
void encoder_int(int nombre)
{
    coder_int(nombre,PACKET_INFO,n_encode);
    n_encode+=NBRE_CHIFFRE_CODAGE_INT;
}
void encoder_mapr()
{
    coder_map(PACKET_INFO);
    n_encode+=N_CASES_X*N_CASES_Y;
}
double decoder_doubler()
{
    double rep=decoder_double(PACKET_INFO,n_decode);
    n_decode+=NBRE_CHIFFRE_CODAGE_DOUBLE;
    return rep;
}
int decoder_intr()
{
    int rep=decoder_int(PACKET_INFO,n_decode);
    n_decode+=NBRE_CHIFFRE_CODAGE_INT;
    return rep;
}
void encoder_charactere(char* chaine,char charactere)
{
    chaine[n_encode]=charactere;
    n_encode+=1;
}

void Codage_donnees(lance_bombe j[NBRE_JOUEURS])
{
    n_encode=0;
    int k=0;
    int i=0;
    int p=0;
    encoder_charactere(PACKET_INFO,'J');
    for(k=0;k<=NBRE_JOUEURS-1;k++)
    {
        encoder_double(j[k].get_x());
        encoder_double(j[k].get_y());
        encoder_double(j[k].corps.get_angle());
        encoder_int(j[k].get_vivant());
        encoder_int(j[k].get_kills());
        for(i=0;i<=NBRE_BOMBES_MAX-1;i++)
        {
            encoder_double(j[k].bombe_jet[i].get_x());
            encoder_double(j[k].bombe_jet[i].get_y());
            encoder_int(j[k].bombe_jet[i].get_etat_anim_bombe_explo());
            encoder_int(j[k].bombe_jet[i].get_etat());
            encoder_int(j[k].bombe_jet[i].get_existence());
            encoder_double(j[k].bombe_jet[i].iexplo.get_taille_x());
            encoder_double(j[k].bombe_jet[i].iexplo.get_taille_y());

            encoder_double(j[k].bombe_jet[i].iexplo.get_centre_x());
            encoder_double(j[k].bombe_jet[i].iexplo.get_centre_y());

            encoder_double(j[k].bombe_jet[i].iexplo.get_angle());

            for(p=0;p<=3;p++)
            {
                encoder_double(j[k].bombe_jet[i].iexplo2[p].get_taille_x());
                encoder_double(j[k].bombe_jet[i].iexplo2[p].get_taille_y());
                encoder_double(j[k].bombe_jet[i].iexplo2[p].get_centre_x());
                encoder_double(j[k].bombe_jet[i].iexplo2[p].get_centre_y());
                encoder_double(j[k].bombe_jet[i].iexplo2[p].get_angle());
                encoder_int(j[k].bombe_jet[i].iexplo2[p].get_existence());
                encoder_int(j[k].bombe_jet[i].iexplo2[p].get_etat_anim());

            }
        }
        encoder_double(j[k].bombe_piege.get_x());
        encoder_double(j[k].bombe_piege.get_y());
        encoder_int(j[k].bombe_piege.iexplo.get_etat_anim());
        encoder_int(j[k].bombe_piege.get_etat());
        encoder_int(j[k].bombe_piege.iexplo.get_existence());

        encoder_double(j[k].bombe_piege.iexplo.get_taille_x());
        encoder_double(j[k].bombe_piege.iexplo.get_taille_y());

        encoder_double(j[k].bombe_piege.iexplo.get_centre_x());
        encoder_double(j[k].bombe_piege.iexplo.get_centre_y());

        encoder_double(j[k].bombe_piege.iexplo.get_angle());
        for(p=0;p<=3;p++)
        {
            encoder_double(j[k].bombe_piege.iexplo2[p].get_taille_x());
            encoder_double(j[k].bombe_piege.iexplo2[p].get_taille_y());
            encoder_double(j[k].bombe_piege.iexplo2[p].get_centre_x());
            encoder_double(j[k].bombe_piege.iexplo2[p].get_centre_y());
            encoder_double(j[k].bombe_piege.iexplo2[p].get_angle());
            encoder_int(j[k].bombe_piege.iexplo2[p].get_existence());
            encoder_int(j[k].bombe_piege.iexplo2[p].get_etat_anim());
        }
    }
    n_encode=0;
}
char* get_packet()
{
    return PACKET_INFO;
}
void recevoir_touches(char* packet)
{
    PACKET_TOUCHE=packet;
}
int lance_bombe::jouer_en_ligne()
{
    origine=1;
    n_decode=0;
    int f=0;
    char msg_fin;
    haut=decoder_int(PACKET_TOUCHE,n_decode);n_decode+=NBRE_CHIFFRE_CODAGE_INT;
    bas=decoder_int(PACKET_TOUCHE,n_decode);n_decode+=NBRE_CHIFFRE_CODAGE_INT;
    gauche=decoder_int(PACKET_TOUCHE,n_decode);n_decode+=NBRE_CHIFFRE_CODAGE_INT;
    droite=decoder_int(PACKET_TOUCHE,n_decode);n_decode+=NBRE_CHIFFRE_CODAGE_INT;
    touche_lance_bombe=decoder_int(PACKET_TOUCHE,n_decode);n_decode+=NBRE_CHIFFRE_CODAGE_INT;
    touche_pose_bombe_croix=decoder_int(PACKET_TOUCHE,n_decode);n_decode+=NBRE_CHIFFRE_CODAGE_INT;
    touche_position=decoder_int(PACKET_TOUCHE,n_decode);n_decode+=NBRE_CHIFFRE_CODAGE_INT;
    msg_fin=PACKET_TOUCHE[n_decode];n_decode++;
    if(msg_fin=='F')
    {
        f=1;
    }
    return f;
}

