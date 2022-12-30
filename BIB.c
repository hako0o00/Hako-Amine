#include "BIB.h"

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

/**************************************************************************************/

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

/**************************************************************************************/

void fermer(TOVC *pF)
{

    fseek(pF->F,0,0);
    fwrite(&(pF->entete),sizeof(Entete),1,pF->F);
    fclose(pF->F);

}

/**************************************************************************************/

void fermerTOF(TOF *pF)
{

    fseek(pF->F,0,0);
    fwrite(&(pF->entete),sizeof(EnteteTOF),1,pF->F);
    fclose(pF->F);

}

/**************************************************************************************/

int entete(TOVC *pF,int i)
{
    if (i==1) return ((pF->entete).adr_dernier_bloc);
    if (i==2) return ((pF->entete).nb_insert);
    if (i==3) return ((pF->entete).indice_libre);
    return ((pF->entete).nb_sup);
}

/**************************************************************************************/

int enteteTOF(TOF *pF,int i)
{
    if (i==1) return ((pF->entete).dernier_bloc);
}

/**************************************************************************************/

void aff_entete(TOVC *pF,int i,int val)
{
    if (i==1) (pF->entete).adr_dernier_bloc=val;
    else if (i==2) (pF->entete).nb_insert=val;
    else if (i==3) (pF->entete).indice_libre=val;
    else if (i==4) (pF->entete).nb_sup=val;
}

/**************************************************************************************/

void aff_enteteTOF(TOF *pF,int i,int val)
{
    if (i==1) (pF->entete).dernier_bloc=val;
   }

/**************************************************************************************/

void liredir(TOVC *pF,int i,Buffer *buf)
{

        fseek(pF->F,sizeof(Entete)+(i-1)*sizeof(Tbloc),SEEK_SET);
        fread(buf,sizeof(Tbloc),1,pF->F);
        rewind(pF->F);
        (*buf).chaine[Tail_bloc] = '\0';

}

/**************************************************************************************/

void liredirTOF(TOF *pF,int i,Buffer1 *buf)
{

        fseek(pF->F,sizeof(EnteteTOF)+(i-1)*sizeof(TblocTOF),SEEK_SET);
        fread(buf,sizeof(TblocTOF),1,pF->F);
        rewind(pF->F);
       // (*buf).chaine[Tail_bloc] = '\0';

}

/**************************************************************************************/

void ecriredir(TOVC *pF,int i,Buffer buf)
{
        buf.chaine[Tail_bloc] = '\0';
        fseek(pF->F,sizeof(Entete)+(i-1)*sizeof(Tbloc),SEEK_SET);
        fwrite(&buf,sizeof(Tbloc),1,pF->F);
        rewind(pF->F);
}

/**************************************************************************************/

void ecriredirTOF(TOF *pF,int i,Buffer1 buf)
{
        //buf.chaine[Tail_bloc] = '\0';
        fseek(pF->F,sizeof(EnteteTOF)+(i-1)*sizeof(TblocTOF),SEEK_SET);
        fwrite(&buf,sizeof(TblocTOF),1,pF->F);
        rewind(pF->F);
}

/**************************************************************************************/

int alloc_bloc(TOVC *pF)
{
    aff_entete(pF,1,entete(pF,1)+1);
    return entete(pF,1);
}

/****************************************************************************************/

void vider_chaine(char *chaine){
int i=0;
   for (i = 0 ; i<Tail_bloc ; i++){
    chaine[i] = '\0';
   }

}

/****************************************************************************************/
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

/***********************************************************************************/

void Charger_Noms(char *nomfich){
    FILE *F;
    int pos=0,cpt = 0;
    char c;
    F = fopen(nomfich,"r");
    c = fgetc(F);
    while (pos < Nnoms){
        if ( c == ','){
        Noms[pos][cpt] = '\0';
        pos++;
        cpt = 0;
        }
        else {
        Noms[pos][cpt]= c;
        cpt++;
        }
        c = fgetc(F);
        }

 fclose(F);
}

/**************************************************************************************/

void Charger_PrenomsG(char *nomfich){
    FILE *F;
    int pos=0,cpt = 0;
    char c;
    F = fopen(nomfich,"r");
    c = fgetc(F);
     while (pos < Nnoms){
        if ( c == ','){
        Prenoms[pos][cpt] = '\0';
        cpt = 0;
        c = fgetc(F);
        Genres[pos] = c;
        pos++;
        c = fgetc(F);
        c = fgetc(F);
        }
        else {
        Prenoms[pos][cpt]= c;
        cpt++;
        c = fgetc(F);
        }

        }
 fclose(F);
}
/*************************************************************************************/

void generer_tab_identifiants()
{

    int entier , i= 0 , k ,egalite;
    srand(time(NULL));
   while (i<=600)
    {
        entier=rand()%9999;
        k = 0;
        egalite=0;
        while ((k<=i) && egalite == 0 )
        {
            if(entier==ident[k]) { egalite=1;}
            k++;
        }
        if(egalite != 1){ ident[i]= entier ; i++;}
    }
}

/*************************************************************************************/

void generer_fichier_note(char *nomfich, int annee , int nbeleve)
{
    srand(time(NULL));
    FILE *f;
    int p[11] = {2, 3, 3, 5, 10 , 17, 18, 17, 12, 8, 5};
    int nb,inter,interr,i=0;
    int cpt=1;
    int nb_matiere;
    int comt=1;
    f = fopen(nomfich,"w+");
    if(annee<=2) nb_matiere=5;
    else{
        if(annee==3) nb_matiere=8;
        else {nb_matiere=9;}
    }
    char note[2];
    while(comt<= nbeleve)
    {
      int cpt=1;
      while (cpt <= nb_matiere)
      {
          i=0;
          inter = (rand () % 100+1);
          interr = p[i];
          while(interr < inter){
            i++;
            interr += p[i];
          }
          if(i < 10) nb = i*4 + rand()%4;
          else nb = 40;
          NumtoS( nb,2,note);
          fputc(note[0],f);
          fputc(note[1],f);
         cpt++;
      }
     fputc(',',f);
     comt++;
    }
    fclose(f);


}

/************************************************************************************/

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

/*************************************************************************************/

void extrer_cle(char *chaine,char *cle)
{
    int i =9;
    cle[0]=chaine[6];
    cle[1]=chaine[7];
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
    cle[j] = '\0';
}

/******************************************************************************/

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

/**************************************************************************************/

void Gnr_eleve(char *eleve,int annee,char classe,int i,char *Notes)
{
  char ann[6]= {"P12345"};
  char inter[100];
  char identifiant[4];
  char nom[20];
  char Snotes[20];
  char prenom[20];
  char genre;
  int num_nom,num_prenom,longg;
  longg = 0;
     NumtoS(ident[i],4,identifiant);
    num_prenom = rand()%Nprenoms;
    num_nom = rand()%Nnoms;
    extr_Snote(Notes,i,Snotes);
    sprintf(inter ,"%s%c%d%c%s,%s%s", identifiant, ann[annee], classe , Genres[num_prenom], Noms[num_nom], Prenoms[num_prenom],Snotes);
       longg=strlen(inter)+2;
    sprintf(eleve ,"%d%s",longg,inter);

}

/************************************************************************************/
void afficher_fichier()
{
    printf("\n**********ENTETE**************\n");
    printf("*1/-----------i= %d          *\n",entete(Fichier_main,1)),
    printf("*2/-----------j= %d          *\n",entete(Fichier_main,3)),
    printf("*3/nb_insertion= %d          *\n",entete(Fichier_main,2)),
    printf("*4/nb_suppres  = %d          *\n",entete(Fichier_main,4)),
    printf("******************************\n");
    int i=1;
    Buffer buff;
    printf("--------------------blocs-----------------\n");
    while(i<=entete(Fichier_main,1))
    {
        liredir(Fichier_main,i,&buff);
        printf("| %s\n",buff.chaine);
        printf("------------------------------------------\n");
        i++;
    }

}

/************************************************************************************/

void extr_enr(char *chaine,int block,int deplacement,int *longeur){
       int j = deplacement , cpy = 0, suiv = block, longg = 5;
       char longgg[2];
       Buffer buf1;
       liredir(Fichier_main,suiv,&buf1);
       while (cpy <= longg-1){
         if (j<Tail_bloc){
            chaine[cpy] = buf1.chaine[j];
            cpy++;
            j++;
            if (cpy == 3){
                longgg[0] = chaine[0];
                longgg[1] = chaine[1];
                longgg[2] = '\0';
                longg = atoi(longgg);
            }
         }
         else {
           suiv++;
           liredir(Fichier_main,suiv,&buf1);
           j=0;
         }}
         chaine[longg] = '\0';
         *longeur = longg;
       }


/***********************************************************************************/

int rechercher(char *cle_rechercher,int *block,int *champ, int i_init, int j_init,int i_final,int j_final){

   int trouve = 0 , i = i_init , j = j_init , cmp = 0 ,   longeurr = 0;
    char chaineee[Tail_bloc];
    char cle_extrait[Tail_bloc];

        extr_enr(chaineee,i,j,&longeurr);
        extrer_cle(chaineee,cle_extrait);
        cmp = strcmp(cle_extrait,cle_rechercher);
         while (!trouve && cmp<0 && ((i<=i_final) || ( (i == i_final)  && (j<=j_final)) )){

        i = i + ((longeurr + j) / Tail_bloc);
        j = (j + longeurr) % Tail_bloc ;
        extr_enr(chaineee,i,j,&longeurr);
        extrer_cle(chaineee,cle_extrait);
        cmp = strcmp(cle_extrait,cle_rechercher);
    if (cmp == 0){
        trouve = 1;
    }

    if (cmp < 0 &&  (i + ((longeurr + j) / Tail_bloc)) == i_final &&  ((j + longeurr) % Tail_bloc) >= j_final-1 ){

        i = i + ((longeurr + j) / Tail_bloc);
        j = (j + longeurr) % Tail_bloc ;
       trouve = 0;
       break;
    }
    }
    if (cmp == 0){trouve = 1;}
*block = i;
*champ = j;
return trouve;
}
 /********************************************************************************/

 void insertion(char * eleve,int i_init ,int j_init,int bloc_final,int chmp_final)
{
    int i = i_init,j=j_init,h, taille=strlen(eleve), k=0,m=0;
    char cle[Tail_bloc];
    int  classe  , annee ;

    extrer_cle(eleve,cle);
    if(rechercher(cle,&i,&j,i_init,j_init,bloc_final,chmp_final)==0)
    {
        if(i>entete(Fichier_main,1)) {aff_entete(Fichier_main,1,entete(Fichier_main,1)+1); aff_entete(Fichier_main,3,0);}
        Buffer buff ;

        liredir(Fichier_main,i,&buff);
          if ((i==entete(Fichier_main,1))&&(j==0)&&(entete(Fichier_main,3)==0)){
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
             ecriredir(Fichier_main,i,buff);
             j=0;
             i++;
             if(i<=entete(Fichier_main,1)){  liredir(Fichier_main,i,&buff);}
             else{ int a=Tail_bloc-1;
                 while(a>=0){
                     buff.chaine[a]='\0';
                     a--;}
                 aff_entete(Fichier_main,1,i);}
           }
          while((h < taille)&& (stop==1))
          {
              if(eleve[h] != '\0' ) stop = 0;
              h++;
          }
       }
        if(j>0){ ecriredir(Fichier_main,i,buff);}
        aff_entete(Fichier_main,3,j);
        aff_entete(Fichier_main,2,entete(Fichier_main,2)+1);
    }
}

/*************************************************************************************************/

void afficher_index(){
for (int z = 0 ; z<25 ; z++){
    printf("\n classe : %d index is :[%d,%d] ",z,index_classe[z][0],index_classe[z][1]);
}
}

/*************************************************************************************************/
void insertion_index(char *eleve){

    int classe , annee , longeurr = strlen(eleve) ;
    int i_init , j_init,i_final, j_final;


    classe = (int)(eleve[7]) -48 ;
    if ( eleve[6] == 'P' ) {annee = 0;}
    else {annee = (int)(eleve[6])-48;}
    i_init = index_classe[annee*4 + classe -1][0] ;
    j_init = index_classe[annee*4 + classe -1][1] ;
    i_final = index_classe[annee*4 + classe][0] ;
    j_final = index_classe[annee*4 + classe][1] ;

    insertion(eleve,i_init,j_init,i_final,j_final);

    // mise a jour index
    for( int i = annee*4 + classe ; i<25 ; i++ ){
       index_classe[i][0] = index_classe[i][0] + ((longeurr + index_classe[i][1]) / Tail_bloc);
       index_classe[i][1] = (index_classe[i][1] + longeurr) % Tail_bloc ;

    }

}


/*********************************************************************************/

int CreerFichierInitiale(char *note0 ,char *note1 ,char *note2,char *note3,char *note4,char *note5 ){

int i,j,k,h;
char eleve[Tail_bloc];
     for(i=0;i<=0;i++)
     {
         h=1;
         //printf("*******i********\n");
         for(j=1;j<=1;j++)
         {
             for(k=0;k<=24;k++)
              {
                 // printf("**********k***********\n");
                       switch (i){
                          case 0:
                              Gnr_eleve(eleve,i,j,h,note0);
                              break;
                          case 1 :
                              Gnr_eleve(eleve,i,j,h,note1);
                              break;
                          case 2 :
                              Gnr_eleve(eleve,i,j,h,note2);
                              break;
                          case 3 :
                              Gnr_eleve(eleve,i,j,h,note3);
                              break;
                          case 4 :
                              Gnr_eleve(eleve,i,j,h,note4);
                              break;
                          case 5 :
                              Gnr_eleve(eleve,i,j,h,note5);
                              break;
                      }
                      printf("insertions success de : %d\n",k);
               insertion_index(eleve);
                h++;
             }

         }
     }


}

/*******************************************************************************************/
