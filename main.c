#include"BIB.c"

int main(){

generer_tab_identifiants();
Charger_Noms("Noms.txt");
Charger_PrenomsG("Prenoms.txt");

for (int z = 0 ; z<25 ; z++){
    index_classe[z][0] = 1;
}

generer_fichier_note("Note0.txt" ,0,100);
generer_fichier_note("Note1.txt",1,100);
generer_fichier_note("Note2.txt",2,100);
generer_fichier_note("Note3.txt",3,100);
generer_fichier_note("Note4.txt",4,100);
generer_fichier_note("Note5.txt",5,100);

    Fichier_main = ouvrir("premiere annee", 'N');

   Buffer buff;
printf("himar");

  CreerFichierInitiale("note0.txt","note1.txt","note2.txt","note3.txt","note4.txt","note5.txt");

char eleve[50] = {0};
int lonngg = 0;
afficher_fichier();
for(int m = 0; m<25; m++){
        extr_enr(eleve,ident_index[m][1],ident_index[m][2],&lonngg);
                    printf( "--%d-- [%d,%d,%d] -- enr : %s \n" ,m,ident_index[m][0],ident_index[m][1],ident_index[m][2],eleve );

                }
int longg = 0 , identif = 0 ,i =0 ;


printf("\n tu veut supprimer quel eleve ?");
scanf("%d",&identif);


supprimer_eleve(identif);
Buffer bufff;
aff_entete(Fichier_main,1,20);
sprintf(bufff.chaine,"himar");
ecriredir(Fichier_main,20,bufff);
afficher_fichier();
for(int m = 0; m<25; m++){
        extr_enr(eleve,ident_index[m][1],ident_index[m][2],&lonngg);
                    printf( "--%d-- [%d,%d,%d] -- enr : %s \n" ,m,ident_index[m][0],ident_index[m][1],ident_index[m][2],eleve );

                }
  fermer(Fichier_main);

return 0;
}

