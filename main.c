#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define Tail_bloc 100
#define Max_tab 20

char AP0[5][20] = {"Arabe" , "Education Civique", "Education Islamique", "Math" ,"Science"};
char AP1[5][20] = {"Arabe" , "Education Civique", "Education Islamique", "Math" ,"Science"};
char AP2[5][20] = {"Arabe" , "Education Civique", "Education Islamique", "Math" ,"Science"};
char AP3[8][20] = {"Anglais", "Arabe" ,"Education Civique", "Education Islamique","Francais","Histoire Geographie", "Math" ,"Science"};
char AP4[9][20] = {"Anglais", "Arabe" ,"Education Civique", "Education Islamique","Francais","Histoire Geographie", "Math" ,"Science" , "Tamazight"};
char AP5[9][20] = {"Anglais", "Arabe" ,"Education Civique", "Education Islamique","Francais","Histoire Geographie", "Math" ,"Science", "Tamazight"};
int ident[600] = {0};

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

//-----DEFENITION DU MODELE--------------------------------------------//

TOVC *ouvrir(char *nomfich,char mod)  // mod = 'A' ancien (rb+)
{
    TOVC *I=malloc(sizeof(TOVC)) ;
    char s[3];
    if ((mod == 'A') || (mod =='a')) sprintf(s,"rb+");
    else sprintf(s,"wb+");
    I->F=fopen(nomfich,s) ;
    if ((mod == 'A') || (mod =='a'))
    {
        fread(&(I->entete),sizeof(Entete),1,I->F);
    }
    else
    {
        (I->entete).adr_dernier_bloc=0;
        (I->entete).nb_insert=0;
        (I->entete).indice_libre=0;
        (I->entete).nb_sup=0;
        fwrite(&(I->entete),sizeof(Entete),1,I->F);
    }
    return I;

}

TOF *ouvrirTOF(char *nomfich,char mod)  // mod = 'A' ancien (rb+)
{
    TOF *I=malloc(sizeof(TOF)) ;
    char s[3];
    if ((mod == 'A') || (mod =='a')) sprintf(s,"rb+");
    else sprintf(s,"wb+");
    I->F=fopen(nomfich,s) ;
    if ((mod == 'A') || (mod =='a'))
    {
        fread(&(I->entete),sizeof(EnteteTOF),1,I->F);
    }
    else
    {
        (I->entete).dernier_bloc=0;
        fwrite(&(I->entete),sizeof(EnteteTOF),1,I->F);
    }
    return I;

}



void fermer(TOVC *pF)
{

    fseek(pF->F,0,0);
    fwrite(&(pF->entete),sizeof(Entete),1,pF->F);
    fclose(pF->F);

}

void fermerTOF(TOF *pF)
{

    fseek(pF->F,0,0);
    fwrite(&(pF->entete),sizeof(EnteteTOF),1,pF->F);
    fclose(pF->F);

}
int entete(TOVC *pF,int i)
{
    if (i==1) return ((pF->entete).adr_dernier_bloc);
    if (i==2) return ((pF->entete).nb_insert);
    if (i==3) return ((pF->entete).indice_libre);
    return ((pF->entete).nb_sup);
}

int enteteTOF(TOF *pF,int i)
{
    if (i==1) return ((pF->entete).dernier_bloc);
    /*if (i==2) return ((pF->entete).nb_insert);
    if (i==3) return ((pF->entete).indice_libre);
    return ((pF->entete).nb_sup);*/
}

void aff_entete(TOVC *pF,int i,int val)
{
    if (i==1) (pF->entete).adr_dernier_bloc=val;
    else if (i==2) (pF->entete).nb_insert=val;
    else if (i==3) (pF->entete).indice_libre=val;
    else if (i==4) (pF->entete).nb_sup=val;
}

void aff_enteteTOF(TOF *pF,int i,int val)
{
    if (i==1) (pF->entete).dernier_bloc=val;
   /* else if (i==2) (pF->entete).nb_insert=val;
    else if (i==3) (pF->entete).indice_libre=val;
    else if (i==4) (pF->entete).nb_sup=val;*/
}
void liredir(TOVC *pF,int i,Buffer *buf)
{

        fseek(pF->F,sizeof(Entete)+(i-1)*sizeof(Tbloc),SEEK_SET);
        fread(buf,sizeof(Tbloc),1,pF->F);
        rewind(pF->F);
        (*buf).chaine[Tail_bloc] = '\0';

}

void liredirTOF(TOF *pF,int i,Buffer1 *buf)
{

        fseek(pF->F,sizeof(EnteteTOF)+(i-1)*sizeof(TblocTOF),SEEK_SET);
        fread(buf,sizeof(TblocTOF),1,pF->F);
        rewind(pF->F);
       // (*buf).chaine[Tail_bloc] = '\0';

}

void ecriredir(TOVC *pF,int i,Buffer buf)
{
        buf.chaine[Tail_bloc] = '\0';
        fseek(pF->F,sizeof(Entete)+(i-1)*sizeof(Tbloc),SEEK_SET);
        fwrite(&buf,sizeof(Tbloc),1,pF->F);
        rewind(pF->F);
}
void ecriredirTOF(TOF *pF,int i,Buffer1 buf)
{
        //buf.chaine[Tail_bloc] = '\0';
        fseek(pF->F,sizeof(EnteteTOF)+(i-1)*sizeof(TblocTOF),SEEK_SET);
        fwrite(&buf,sizeof(TblocTOF),1,pF->F);
        rewind(pF->F);
}
int alloc_bloc(TOVC *pF)
{
    aff_entete(pF,1,entete(pF,1)+1);
    return entete(pF,1);
}

// transformation d'un entier en une char, ajout de zéros
void NumtoS(int Num,int max,char* S)
{
    char inter[max];
    sprintf(S,"");
    sprintf(inter,"%d",Num);
    int j = max - strlen(inter);
    while (j>0)
    {
        sprintf(S,"%s0",S);
        j--;
    }
    sprintf(S,"%s%s",S,inter);
}

// atoi(ch) => transforme ch à entier

void extr_nom(char *nomfich,int i,char *nom){
    FILE *F;
    int pos=1,cpt = 0;
    char c;
    F = fopen(nomfich,"r");
    c = fgetc(F);
    while (pos != i){
        if ( c == ','){
        pos++;}
        c = fgetc(F);}
    while (c != ','){
        nom[cpt]= c;
        c = fgetc(F);
        cpt++;}
 fclose(F);
 nom[cpt] = '\0';
}


void extr_Snote(char *nomfich,int i,char *nom){
    FILE *F;
    int pos=1,cpt = 0;
    char c;
    F = fopen(nomfich,"r");
    c = fgetc(F);
    while (pos != i){
        if ( c == ','){
        pos++;}
        c = fgetc(F);}
    while (c != ','){
        nom[cpt]= c;
        c = fgetc(F);
        cpt++;}
 fclose(F);
 nom[cpt] = '\0';
}
void extr_Gprenom(char *nomfich,int i,char *prenom,char *genre){
    FILE *F;
    int pos=1,cpt = 0;
    char c;
    F = fopen(nomfich,"r");
    c = fgetc(F);
    while (pos != i){
        if ( c == ';'){
        pos++;}
        c = fgetc(F);}
    while (c != ','){
        prenom[cpt]= c;
        c = fgetc(F);
        cpt++;}
    c = fgetc(F);
    *genre = c;
 fclose(F);
 prenom[cpt] = '\0';
}
//**************************************************************
/*void generer_fichier_note(char *nomfich, int nb_matiere , int nb_eleve)
{
    srand(time(NULL));
    FILE *f;
    int nb;
    int cpt=1;
    int comt=1;
    f = fopen(nomfich,"w+");
    char note[2];
    while(comt<= nb_eleve)
    {
      int cpt=1;
      while (cpt <= nb_matiere)
      {
          nb = rand () % 10 ;
          NumtoS( nb,1,note);
         fputc(note[0],f);
         fputc(note[1],f);
         cpt++;
      }
     fputc(',',f);
     comt++;
    }
    fclose(f);
}*/
void generer_fichier_note(char *nomfich, int annee )
{
    srand(time(NULL));
    FILE *f;
    int nb;
    int cpt=1;
    int nb_matiere;
    int comt=1;
    f = fopen(nomfich,"w+");
    if(annee<=2) nb_matiere=5;
    else{
        if(annee==3) nb_matiere=8;
        else {nb_matiere=9;}
    }
    char note[1];
    while(comt<= 100)
    {
      int cpt=1;
      while (cpt <= nb_matiere)
      {
          nb = (rand () % 10)+1 ;
          if(nb != 10){  NumtoS( nb,1,note);}
          else { note[0]='#';}
          fputc(note[0],f);
         cpt++;
      }
     fputc(',',f);
     comt++;
    }
    fclose(f);


}
//***********************************************************************************
void Gnr_eleve(char *eleve,int annee,char classe,int i,char *Noms,char *Prenoms,char *Notes)
{
  //srand(time(NULL));
  char ann[6]= {"P12345"};
  char inter[100];
  char ident[4];
  char nom[20];
  char Snotes[20];
  char prenom[20];
  char genre;
  int num_nom,num_prenom,longg;
  longg = 0;
  NumtoS(rand()%9999,4,ident);
    num_prenom = rand()%613 + 1;
    num_nom = rand()%250 + 1;
    extr_Gprenom(Prenoms,num_prenom,prenom,&genre);
    extr_nom(Noms,num_nom,nom);
    extr_nom(Notes,i,Snotes);
    sprintf(inter ,"%s%c%d%c%s,%s%s", ident, ann[annee], classe , genre, nom, prenom,Snotes);
   /* if (annee < 3){
        longg = strlen(inter) + 3;
    }
    else {
        if (annee == 3)
        {
            longg = strlen(inter) + 3;
        }
        else {
            longg = strlen(inter) + 3;
        }
    }*/
    longg=strlen(inter)+3;
    sprintf(eleve ,"%d0%s",longg,inter);

}

void extrer_cle(char *chaine,char *cle)
{
    int i =10;
    cle[0]=chaine[7];
    cle[1]=chaine[8];
    int j=2;
    while ((chaine[i] != '0')&& (chaine[i] != '1')&& (chaine[i] != '2')&& (chaine[i] != '3')&& (chaine[i] != '4')&& (chaine[i] != '5')&& (chaine[i] != '6')&& (chaine[i] != '7')&& (chaine[i] != '8')&& (chaine[i] != '9')&& (chaine[i] != '@') )
    {
       if( chaine[i] != ',' )
       {
          cle[j]=chaine[i];
          j++;

       }

       i++;
    }
}
//********************************************************************************
void extrer_NomPrenom(char *chaine,char *cle)
{
    int i =10;
    int j=0;
    while ((chaine[i] != '0')&& (chaine[i] != '1')&& (chaine[i] != '2')&& (chaine[i] != '3')&& (chaine[i] != '4')&& (chaine[i] != '5')&& (chaine[i] != '6')&& (chaine[i] != '7')&& (chaine[i] != '8')&& (chaine[i] != '9')&& (chaine[i] != '@') )
    {
       if( chaine[i] != ',' )
       {
          cle[j]=chaine[i];
          j++;

       }

       i++;
    }
}


void vider_chaine(char *chaine){
int i=0;
   for (i = 0 ; i<Tail_bloc ; i++){
    chaine[i] = '\0';
   }

}
//*******************************************************

void insertion( TOVC *f, char * eleve,int bloc,int deplacement,int bloc_final,int chmp_final)
{
    int i,j,h;
    int taille=strlen(eleve);
    char cle[Tail_bloc];

    extrer_NomPrenom(eleve,cle);
    int k=0,m=0;

    if(rechercher(f,cle,&i,&j,bloc,deplacement,bloc_final,chmp_final)==0)
    {
        //printf("\nla position d'insertion:------------i=%d-----------------j=%d--------",i,j);
        if(i>entete(f,1)) {aff_entete(f,1,entete(f,1)+1); aff_entete(f,3,0);}
        Buffer buff ;
        liredir(f,i,&buff);
          if ((i==entete(f,1))&&(j==0)&&(entete(f,3)==0)){
          while(k<Tail_bloc)
          {
             buff.chaine[k]='\0';
             k++;
          }

        }

       char c;
       int stop=0;

       while(stop == 0)
       {

           h=0;
           stop=1;
           if(j<Tail_bloc)
           {
               if(m>=taille){ m=0;}
                c=buff.chaine[j];
                buff.chaine[j]=eleve[m];
                eleve[m]=c;
                m++;
                j++;
           }
           else
           {
             ecriredir(f,i,buff);
             j=0;
             i++;
             if(i<=entete(f,1)){  liredir(f,i,&buff);}
             else{ int a=Tail_bloc-1;
                 while(a>=0){
                     buff.chaine[a]='\0';
                     a--;}
                 aff_entete(f,1,i);}
           }
          while((h < taille)&& (stop==1))
          {
              if(eleve[h] != '\0' ) stop = 0;
              h++;
          }
       }
        if(j>0){ ecriredir(f,i,buff);}
        aff_entete(f,3,j);
        aff_entete(f,2,entete(f,2)+1);
    }
}

//************************************************************************************

void extr_enr(TOVC *F,char *chaine,int block,int deplacement,int *longeur,int *supp){
       int j = deplacement , cpy = 0, suiv = block, longg = 5;
       char longgg[2],supprimer[2];
       Buffer buf1;
       liredir(F,suiv,&buf1);
       while (cpy <= longg-1){
         if (j<Tail_bloc){
            chaine[cpy] = buf1.chaine[j];
            cpy++;
            j++;
            if (cpy == 3){
                longgg[0] = chaine[0];
                longgg[1] = chaine[1];
                supprimer[0] = '0';
                supprimer[1] =  chaine[2];
                longgg[2] = '\0';
                longg = atoi(longgg);
            }
         }
         else {
           suiv++;
           liredir(F,suiv,&buf1);
           j=0;
         }}
         supprimer[2] = '\0';
         chaine[longg] = '\0';
         *supp = atoi(supprimer);
         *longeur = longg;
       }

//****************************************************************************
int rechercher(TOVC *F,char *cle_recherche,int *block,int *champ, int i, int j,int i_final,int j_final)
{
    char chaine[Tail_bloc];
    char cle_extr[Tail_bloc];
    //int i=1,j=0;

    int length,sup,cmp,trouve=0,stop=0,ind_enrg=1;
    Buffer buff;
    while((trouve==0)&&(stop==0)&&(ind_enrg<=entete(F,2))&&((i<i_final)||(j<j_final)))
    {
      extr_enr(F,chaine,i,j,&length,&sup);
     // extrer_cle(chaine,cle_extr);
     extrer_NomPrenom(chaine,cle_extr);
      cmp=strcmp(cle_recherche,cle_extr);
      if(cmp==0 && sup==0){trouve=1;}
      else{
        if(cmp>0)
        {
            j=j+length;
            if(j>=Tail_bloc)
            {
               j=j-Tail_bloc;
               i++;
               liredir(F,i,&buff);
            }
        }
        else{ stop=1;}
      }
      ind_enrg++;
    }
    *block=i;
    *champ=j;
    return trouve;


}
//****************************************************************************************















//*****************************************************************************************
void supprimer_eleve(TOVC *f,char *eleve)
{
    int i=1,j=49;
    Buffer buff;
    int ind;
    if((Tail_bloc-j)<3){ i++; ind =3 -(Tail_bloc-j)-1;    }
    else{ ind = j+2;}
    liredir(f,i,&buff);
    buff.chaine[ind]='1';
    ecriredir(f,i,buff);
    aff_entete(f,4,entete(f,4)+1);

}

//***************************************************************************************
void generer_tab_identifiants()
{

    int entier , i= 0 , k ,egalite;
    srand(time(NULL));
   while (i<=600)
    {
        entier=rand()%9999;
        k = 0;
        egalite=0;
        while ((k<i) && egalite == 0 )
        {
            if(entier==ident[k]) { egalite=1;}
            k++;
        }
        if(egalite==0){ ident[i]= entier ; i++;}
    }
}
//****************************************************************************************
void afficher_fichier(TOVC *f)
{
    printf("\n**********ENTETE**************\n");
    printf("*1/-----------i= %d          *\n",entete(f,1)),
    printf("*2/-----------j= %d          *\n",entete(f,3)),
    printf("*3/nb_insertion= %d          *\n",entete(f,2)),
    printf("*4/nb_suppres  = %d          *\n",entete(f,4)),
    printf("******************************\n");
    int i=1;
    Buffer buff;
    printf("--------------------blocs-----------------\n");
    while(i<=entete(f,1))
    {
        liredir(f,i,&buff);
        printf("| %s\n",buff.chaine);
        printf("------------------------------------------\n");
        i++;
    }

}

  int CreerFichierInitiale(TOVC *F,TOF *f , char *FichierNoms , char *FichierPrenoms ,char *note0 ,char *note1 ,char *note2,char *note3,char *note4,char *note5 ){

     int i,j,h,k;
     char eleve[70];
    // char *FichierNotes;
     //TOF *f;
     //f=ouvrir(NomFichier,'n');
     Buffer1 buf;

     int block1,dep1,block0=1,dep0=0,blc=1,chmp=0,blocIndex=1,PosIndex=0;
    // tab_index[0].bloc=1;
     //tab_index[0].deplacement=0;
     for(i=0;i<=5;i++)
     {
         h=1;
         //printf("*******i********\n");
         for(j=1;j<=4;j++)
         {
             for(k=0;k<=24;k++)
              {
                 // printf("**********k***********\n");
                       switch (i){
                          case 0:
                              Gnr_eleve(eleve,i,j,h,FichierNoms,FichierPrenoms,note0);
                              break;
                          case 1 :
                              Gnr_eleve(eleve,i,j,h,FichierNoms,FichierPrenoms,note1);
                              break;
                          case 2 :
                              Gnr_eleve(eleve,i,j,h,FichierNoms,FichierPrenoms,note2);
                              break;
                          case 3 :
                              Gnr_eleve(eleve,i,j,h,FichierNoms,FichierPrenoms,note3);
                              break;
                          case 4 :
                              Gnr_eleve(eleve,i,j,h,FichierNoms,FichierPrenoms,note4);
                              break;
                          case 5 :
                              Gnr_eleve(eleve,i,j,h,FichierNoms,FichierPrenoms,note5);
                              break;
                      }
                GenererAdrClasse(eleve,block0,dep0,&block1,&dep1);
                block0=block1;
                dep0=dep1;
                insertion(F,eleve,blc,chmp,1000000000000,100000000000);
                h++;
             }
             if(PosIndex <= Max_tab-1)
             {
                buf.tab[PosIndex].bloc=blc;
                buf.tab[PosIndex].deplacement=chmp;
                buf.tab[PosIndex].classe=(i*10)+j;
                PosIndex++;
             }
             else{
                buf.nb=PosIndex-1;
                ecriredirTOF(f,blocIndex,buf);
                blocIndex++;
                PosIndex=1;
                buf.tab[0].bloc=blc;
                buf.tab[0].deplacement=chmp;
                buf.tab[0].classe=(i*10)+j;

             }

            // tab_index[indice_tab_index].bloc=blc;
            // tab_index[indice_tab_index].deplacement=chmp;

             blc=block0;
             chmp=dep0;

             //indice_tab_index++;
         }
     }

     buf.nb=PosIndex-1;
     ecriredirTOF(f,blocIndex,buf);
     aff_enteteTOF(f,1,blocIndex);
     //fermerTOF (f);
  }
  //*************************************************************************************
  void recuperer_chaine(TOVC *f,char *chaine,int length,int block,int dep)
  {
      int h=0;
      Buffer buff;
      liredir(f,block,&buff);
      while(h<length)
      {
         if(dep<Tail_bloc)
         {
             chaine[h]=buff.chaine[dep];
             dep++;
             h++;
         }
         else{
            block++;
            dep=0;
            liredir(f,block,&buff);

         }
      }
  }
  //******************************************************************************************
/*void debut_recherche_adr(TOVC *f,int block,int dep,int *i, int *j)
{
    if(entete(f,2)>=1){
    char taille[2];
    int taille_nb;
    recuperer_chaine(f,taille,2,block,dep);
    taille_nb= atoi(taille);
    *j=dep+taille_nb;
    if(*j>=Tail_bloc)
    {
        block++;
        *j=Tail_bloc-1-taille_nb;
    }
    *i=block;
    }
}*/
//********************************************************************
void GenererAdrClasse(char *enreg,int bloc,int dep,int *i,int *j)
{
    int blc=bloc,chmp=dep;
    char taille[1];
    taille[0]=enreg[0];
    taille[1]=enreg[1];
    int taille_nb=atoi(taille),ind;

     blc = (blc*Tail_bloc + taille_nb + chmp) / Tail_bloc;
     chmp = (chmp + taille_nb ) % Tail_bloc ;
    *i=blc;
    *j=chmp;


}
//***********************************************************************
int recherche_TOF(TOF *F,int cle_recherche, int *bloc, int *deplacement)
{
    int bi=1,bs=enteteTOF(F,1),trouve=0,stop=0;
    int j=0,i;
    Buffer1 buf;
    while((bi<=bs)&&(trouve==0)&&(stop==0))
    {
        i=(bi+bs)/2;
        liredirTOF(F,i,&buf);
        if((cle_recherche >= buf.tab[0].classe)&&(cle_recherche<=buf.tab[buf.nb].classe))
           {
               int inf=0,sup = buf.nb;
               while((inf <= sup)&&(trouve==0))
               {
                  j= ( inf + sup)/2;
                  if(cle_recherche==buf.tab[j].classe) {trouve = 1 ;
                  *deplacement=buf.tab[j].deplacement;
                  *bloc=buf.tab[j].bloc;
                  }
                  else{
                    if(cle_recherche<buf.tab[j].classe) {sup=j-1;}
                    else{inf=j+1;}
                  }
               }
               if (trouve==0) j=inf ;
               stop=1;
           }
           else{
            if(cle_recherche<buf.tab[0].classe) {bs=i-1;}
            else bi=i+1;
           }

    }
    //if(trouve==0) i=bi;
    return trouve;

}
//***********************************************************************
void insertion_eleve(TOVC *f,TOF *index, char *nom,char *prenom,int annee,int classe,char genre,int nb_bloc_index)
{

  srand(time(NULL));
  char ann[6]= {"P12345"};
  char inter[100];
  char ident[4];
  char fichiernote[50];
  char Snotes[20];
  char eleve[Tail_bloc];
  int longg;
  longg = 0;
  switch(annee){
  case 0:
    strcpy(fichiernote,"note0.txt");
    break;
  case 1:
    strcpy(fichiernote,"note1.txt");
    break;
  case 2:
    strcpy(fichiernote,"note2.txt");
    break;
  case 3:
    strcpy(fichiernote,"note3.txt");
    break;
  case 4:
    strcpy(fichiernote,"note4.txt");
    break;
  case 5:
    strcpy(fichiernote,"note5.txt");
    break;
  }
  NumtoS(rand()%9999,4,ident);
    extr_nom(fichiernote,rand()%100,Snotes);
    sprintf(inter ,"%s%c%d%c%s,%s%s", ident, ann[annee], classe , genre, nom, prenom,Snotes);
    longg=strlen(inter)+3;
    sprintf(eleve ,"%d0%s",longg,inter);
    int i,j;
    Buffer1 buf;
    if(eleve[7]=='P'){
      j=(classe-1)%Max_tab ;
      i=((classe-1)/Max_tab)+1 ;
    }
    else {
      j=(4*annee+classe-1)%Max_tab ;
      i=((4*annee+classe-1)/Max_tab)+1;
    }
    int bloc,depl;
    liredirTOF(index,i,&buf);
    bloc=buf.tab[j].bloc;
    depl=buf.tab[j].deplacement;
    j++;
    if(j>buf.nb)
    {
        i++;
        liredirTOF(index,i,&buf);
        j=0;
    }
    if((annee<5)||(classe<4)){insertion(f,eleve,bloc,depl,buf.tab[j].bloc,buf.tab[j].deplacement);}
    else{insertion(f,eleve,bloc,depl,10000000000,100000000);}
    aff_enteteTOF(index,1,nb_bloc_index);

  /*  while(i<=nb_bloc_index)
    {
        while(j<=buf.nb)
        {
            printf("\n++i=%d ------j=%d +++++++ i avant= %d +++++++++++j avant=%d  *********",i,j,buf.tab[j].bloc,buf.tab[j].deplacement);
            buf.tab[j].bloc = ((buf.tab[j].bloc)*Max_tab + longg + (buf.tab[j].deplacement)) / Max_tab;
            buf.tab[j].deplacement = ((buf.tab[j].deplacement) + longg ) % Max_tab ;
            printf(" i apres= %d +++++++++++j apres=%d  *********\n",buf.tab[j].bloc,buf.tab[j].deplacement);
            j++;
        }
        ecriredirTOF(index,i,buf);
        i++;
        j=0;
        if(i<=nb_bloc_index){liredir(index,i,&buf);}
    }*/
   // printf("\n-----nb_bloc=%d -----\n",enteteTOF(index,1));
  /*  while(i<=nb_bloc_index)
    {
        while(j<=buf.nb)
        {
            printf("\n++i=%d ------j=%d +++++++ i avant= %d +++++++++++j avant=%d  *********",i,j,buf.tab[j].bloc,buf.tab[j].deplacement);
            buf.tab[j].deplacement = (buf.tab[j].deplacement) + longg;
            if((buf.tab[j].deplacement)>=Tail_bloc)
            {
                buf.tab[j].deplacement= (buf.tab[j].deplacement)-Tail_bloc;
                buf.tab[j].bloc=(buf.tab[j].bloc)+1;
            }
            printf(" i apres= %d +++++++++++j apres=%d  *********\n",buf.tab[j].bloc,buf.tab[j].deplacement);
            j++;
        }
       // ecriredirTOF(index,i,buf);
        //i++;
        j=0;
        //if(i<=nb_bloc_index-1){liredir(index,i+1,&buf);}
        i++;
        printf("\n+-+-+-+-+-+-+-+-+-+-%d",i);

    }*/


}




int main()
{
    srand(time(NULL));
    char chaine1[50] = {"3006502P1fRAHMOUNE,Meryem14524"};
    char chaine2[50] = {"2600491P1fREZIG,Basma38652"};
    char chaine3[50] = {"3001479P1fBENYAMINA,Donya##195"};
    char chaine4[50] = {"3004466P1fBOUCHAREB,Dalia96636"};
    char chaine5[50] = {"3008717P1fBOUCHAREB,Leila82##5"};
    char chaine6[50] = {"2801539P1fBERKANI,Sofia75878"};
    char chaine7[50] = {"28"};

    char cle1[50];
    char cle2[50];
    int longeur,supp;
    TOVC *F;
    TOF *index;
    int i,j;
  F = ouvrir("FICHIERETUDIANTS",'a');
  index=ouvrirTOF("INDEXCLASSE",'a');
  int b,a=1;
  Buffer1 buff;

 // printf("%d\n",enteteTOF(index,1));


  //CreerFichierInitiale(F,index,"Noms.txt","Prenoms.txt","note0.txt","note1.txt","note2.txt","note3.txt","note4.txt","note5.txt");
/*while(a<=enteteTOF(index,1)){
    liredirTOF(index,a,&buff);
    for(b=0;b<=buff.nb;b++)
    {
        printf("classe: %d bloc: %d deplacement: %d\n",buff.tab[b].classe,buff.tab[b].bloc,buff.tab[b].deplacement);
    }
    a++;
  }*/
  //insertion_eleve(F,index,"ABBBBB","mouaici",0,1,'m',enteteTOF(index,1));
  printf("\n*****************************************************************************\n");
   //afficher_fichier(F);
  printf("\n*****************************************************************************\n");

  a=1;
 /* while(a<=enteteTOF(index,1)){
    liredirTOF(index,a,&buff);
    for(b=0;b<=buff.nb;b++)
    {
        printf("classe: %d bloc: %d deplacement: %d\n",buff.tab[b].classe,buff.tab[b].bloc,buff.tab[b].deplacement);
    }
    a++;
  }*/
   //afficher_fichier(F);
  //printf("%d",entete(F,3));
   fermer(F);
   fermerTOF(index);
   return 0;


}
