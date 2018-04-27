#include "src/word2vec.h"
#include "src/gestionfichier.h" 
#include "src/config.h"
#include "src/decisions.h"
#include <iostream>
#include <unistd.h>


using namespace std;


std::vector<std::string> chargerFichierReponse(std::vector<std::vector<float>>& vecfichier, long long size){
  std::vector<std::string> pLigne;
  std::vector<std::string> reponse;
  int affichageTotalLigne = nbligne();
  char **monTableau = new char* [100];
  float vec[max_size];
  std::ifstream fichier(file_name_rep, std::ios::in);  // on ouvre le fichier en lecture

  for(int i = 0; i < 100; i++) monTableau[i] = new char[100];

  
  if(fichier)  // si l'ouverture a réussi
  {
    int index =0; // index représentant la ligne du file_name_rep

    std::string ligne;  // déclaration d'une chaîne qui contiendra la ligne lue

    while(getline(fichier, ligne)){  // on met dans "contenu" la ligne


      cout << "chargement de la ligne : " << index+1 << "/" << affichageTotalLigne << " ..."<<endl;
      
      pLigne = split(ligne, separateur);
      
      try{ 
        reponse.push_back(pLigne[1]); // <-------------------- peu generer des erreur si pas de réponse -> a gerer
      }
      catch(exception const& e){
        cerr<<"WARNING : pas de reponse pour cette ligne"<<endl;
        reponse.push_back("j'ai compris mais je n'ai pas de réponse");
      }
      int mot = supprimerStopWord(pLigne[0], monTableau); //on parse la ligne pour la mettre dans un char**



      for(int z = 0; z < mot ; ++z){ //pour chaque mot
        afficherVec(monTableau[z], vec); //je trouve le vecteur
        for(long long a = 0; a < size; a++) vecfichier[index][a] += vec[a]; //on ajoute dans la liste des vecteurs le vecteur du mot
      }
      index++; //on passe a la ligne suivante

    }
    
  }
  fichier.close();

  return reponse;
}


void chargerQuestion(std::string question, std::vector<float>& vecquestion, long long size){

  char **monTableau = new char* [100];
  float vec[max_size];

  for(int i = 0; i < 100; i++) monTableau[i] = new char[100];
  for (long long a = 0; a < size; a++) vecquestion[a] = 0;

  int mot = supprimerStopWord(question, monTableau); //on parse la ligne pour la mettre dans un char**

  int z = 0;
  while(z < mot)  //pour chaque mot
  {
    afficherVec(monTableau[z], vec); //je trouve le vecteur

    for(long long a = 0; a < size; a++)  //on ajoute dans la liste des vecteurs le vecteur du mot
    { 
      vecquestion[a] += vec[a];
    }
    ++z;
  }
  
}






int main(int argc, char **argv) {
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////declaration des variables///////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    FILE *f;
    int indexRep;
    std::vector<float> vecquestion;
    std::vector<std::vector<float>> vecfichier;
    long long size, words;
    std::string question;
    std::vector<std::string> reponse;


    ////////////////////////////////////////////////////////////////////////////
    //////////////////////initialisation des variables//////////////////////////
    ////////////////////////////////////////////////////////////////////////////


    //for(long long a = 0; a < 10; a++) vecfichier[a] = new float[size];
    vecquestion.resize(max_size);
    for (long long a = 0; a < size; a++) vecquestion.push_back(0);

    f = fopen(file_name, "rb");
    fscanf(f, "%lld", &words);
    fscanf(f, "%lld", &size);
    fclose(f);

    vecfichier.resize(nbligne());
    for(int a = 0; a < nbligne() ; a++){
      vecfichier[a].resize(size);
    }

    for(int a = 0; a < nbligne(); a++){
      for(int b = 0; b < size ; b++){
        vecfichier[a].push_back(0);
      }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //////////////////////gestion des erreurs d'entrés//////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    if (argc != 1) {
        return 0; //errcode no .bin enter 
    }



    ////////////////////////////////////////////////////////////////////////////
    ///////////////////////////algo de thibault/////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    reponse = chargerFichierReponse(vecfichier, size); //ici vecfichier contier la liste des vecteur de chaque ligne du fichier de reponse
    
    //boucle pour poser des questions
    while(42){
      cout << "posez donc votre question :" << endl << "> ";
      getline(cin, question);
      chargerQuestion(question, vecquestion, size); // on charge la question qu'on a posé
      indexRep = trouverReponse(vecquestion, vecfichier, size);
      cout << "la meilleure réponse est la reponse : " << indexRep-1 << endl;
      if(indexRep >= 1)
        cout << reponse[indexRep-1] << endl;
      else
        cout << "je n'ai pas compris la question" << endl;
    }

    return 0;
}
