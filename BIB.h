#ifndef BIB_H_INCLUDED
#define BIB_H_INCLUDED

/**************************inclusions*******************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

/**************************definitions******************************/
#define Tail_bloc 50
#define Max_tab 20
#define Nnoms 200
#define Nprenoms 200


/***********************structures_definitions**********************/

typedef struct enreg
{
    int classe;
    int bloc;
    int deplacement;
} enreg;

typedef struct Tbloc
{
    char chaine[Tail_bloc];
} Tbloc ;
typedef struct TblocTOF
{
     enreg tab[Max_tab];
     int nb;
} TblocTOF ;


typedef struct Tbloc Buffer ;
typedef struct TblocTOF Buffer1 ;

typedef struct Adresse
{
    int bloc;
    int deplacement;
} Adresse ;
Adresse tab_index[24];

typedef struct Entete
{
    int adr_dernier_bloc ;
    int nb_insert ;
    int indice_libre ;
    int nb_sup ;
} Entete ;

typedef struct EnteteTOF
{
    int dernier_bloc ;

} EnteteTOF ;

typedef struct TOVC
{
    FILE *F ;
    Entete entete ;
} TOVC ;

typedef struct TOF
{
    FILE *F ;
    EnteteTOF entete ;
} TOF ;

/***********************Variales_Generales**************************/

TOVC *Fichier_main;

TOF *Fichier_index;

char AP0[5][20] = {"Arabe" , "Education Civique", "Education Islamique", "Math" ,"Science"};
char AP1[5][20] = {"Arabe" , "Education Civique", "Education Islamique", "Math" ,"Science"};
char AP2[5][20] = {"Arabe" , "Education Civique", "Education Islamique", "Math" ,"Science"};
char AP3[8][20] = {"Anglais", "Arabe" ,"Education Civique", "Education Islamique","Francais","Histoire Geographie", "Math" ,"Science"};
char AP4[9][20] = {"Anglais", "Arabe" ,"Education Civique", "Education Islamique","Francais","Histoire Geographie", "Math" ,"Science" , "Tamazight"};
char AP5[9][20] = {"Anglais", "Arabe" ,"Education Civique", "Education Islamique","Francais","Histoire Geographie", "Math" ,"Science", "Tamazight"};

char Noms[Nnoms][20] = {0};

char Prenoms[Nprenoms][20] = {0};

char Genres[Nprenoms] = {0};

int ident[600] = {0} ;

int ident_index[600][3] = {0};

int num_eleve = 0;

int index_classe[25][2] = {0};



/***********************machine_abstraite***************************/

// Les fichiers TOVC :

TOVC *ouvrir(char *nomfich,char mod);

void fermer(TOVC *pF);

int entete(TOVC *pF,int i);

void aff_entete(TOVC *pF,int i,int val);

void liredir(TOVC *pF,int i,Buffer *buf);

void ecriredir(TOVC *pF,int i,Buffer buf);

int alloc_bloc(TOVC *pF);


//Les fichiers TOF:

TOF *ouvrirTOF(char *nomfich,char mod);

void fermerTOF(TOF *pF);

int enteteTOF(TOF *pF,int i);

void aff_enteteTOF(TOF *pF,int i,int val);

void liredirTOF(TOF *pF,int i,Buffer1 *buf);

void ecriredirTOF(TOF *pF,int i,Buffer1 buf);


/****************************functions*******************************/
// charger les fichiers noms / prenoms_genre en MC :

void Charger_Noms(char *nomfich);

void Charger_PrenomsG(char *nomfich);



void extr_Snote(char *nomfich,int i,char *nom);

void generer_fichier_note(char *nomfich, int annee , int nbeleve);

void Gnr_eleve(char *eleve,int annee,char classe,int i,char *Notes);

void extrer_cle(char *chaine,char *cle);

void extrer_NomPrenom(char *chaine,char *cle);

void vider_chaine(char *chaine);

void extr_enr(char *chaine,int block,int deplacement,int *longeur);

void insertion(char * eleve,int i_init ,int j_init,int bloc_final,int chmp_final);

int rechercher(char *cle_recherche,int *block,int *champ, int i, int j,int i_final,int j_final);

void generer_tab_identifiants();

void afficher_fichier();

void insertion_index(char *eleve);

int supprimer_eleve(char *eleve) ;

int CreerFichierInitiale(char *note0 ,char *note1 ,char *note2,char *note3,char *note4,char *note5 );

void recuperer_chaine(TOVC *f,char *chaine,int length,int block,int dep);

int recherche_TOF(TOF *F,int cle_recherche, int *bloc, int *deplacement);

void insertion_eleve(char *fichetudiant,TOF *index, char *nom,char *prenom,int annee,int classe,char genre);

void insert_ident(int identt, int blockk , int champp ,int longeur);

int rech_ident(int n, int key, int *i);

#endif // BIB_H_INCLUDED
