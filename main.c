#include"BIB.c"

int main(){

generer_tab_identifiants();
Charger_Noms("Noms.txt");
Charger_PrenomsG("Prenoms.txt");

for (int z = 0 ; z<25 ; z++){
    index_classe[z][0] = 1;
}

generer_fichier_note("Note0.txt",0,100);
generer_fichier_note("Note1.txt",1,100);
generer_fichier_note("Note2.txt",2,100);
generer_fichier_note("Note3.txt",3,100);
generer_fichier_note("Note4.txt",4,100);
generer_fichier_note("Note5.txt",5,100);

    Fichier_main = ouvrir("InitialeTest1", 'N');

   Buffer buff;


  CreerFichierInitiale("note0.txt","note1.txt","note2.txt","note3.txt","note4.txt","note5.txt");


afficher_fichier();

int longg = 0 , identif = 0 ,i =0 ;
char eleve[50];
printf("\n tu veut supprimer quel eleve ?");

scanf("%d",&identif);
rech_ident(num_eleve,identif,&i);
extr_enr(eleve,ident_index[i][1],ident_index[i][2],&longg);
printf("l'eleve supprimer est : %s \n  de l'identifiant : %d \n d'une longeur de : %d",eleve , identif,longg);

supprimer_eleve(eleve);

  fermer(Fichier_main);
afficher_fichier();

return 0;
}

