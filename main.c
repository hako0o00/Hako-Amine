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
   afficher_fichier();

  CreerFichierInitiale("note0.txt","note1.txt","note2.txt","note3.txt","note4.txt","note5.txt");

afficher_index();
afficher_fichier();

  fermer(Fichier_main);


return 0;
}
