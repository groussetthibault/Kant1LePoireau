#include "config.h"
#include "word2vec.h"
#include <iostream>
#include <vector>
#include <sstream>

int confirmation(int index, int indexpred){
    std::vector<std::string> pLigne;
    std::vector<std::string> questions;
    std::ifstream fichier(file_name_rep, std::ios::in);  // on ouvre le fichier en lecture
    std::string ligne;  // déclaration d'une chaîne qui contiendra la ligne lue

    if(fichier)  // si l'ouverture a réussi
    {
  
  
      while(getline(fichier, ligne)){  // on met dans "contenu" la ligne
            pLigne = split(ligne, separateur);      
            try{
                questions.push_back(pLigne[0]);
            }
            catch(exception const& e){
                questions.push_back(" pas de question sur cette ligne ");
            }
        }

    }
    fichier.close();
    cout << "je ne suis pas sur d'avoir compris, la question porte sur : " << questions[index-1] << " ? (oui/non)" << endl;
    cin >> ligne;
    if(ligne == "oui"){
        return index;
    }
    cout << "ah... et est-ce que la question porte sur : " << questions[indexpred-1] << " ? (oui/non)" << endl;
    cin >> ligne;
    if(ligne == "oui"){
        return indexpred;
    }
    return -1;
}

int trouverReponse(float* vecquestion, float** vecfichier, long long size){
  int index = -1;
  int indexpred = -1;
  float maxpred = 0;
  float max = 0;
  float cs;

  for(int i = 0; i < nbligne(); i++){
    cs = cosine_similarity(vecquestion, vecfichier[i], size);
    cout << "cs ligne " << i << " : " << cs << endl;
    if(cs > max){
        maxpred = max;
        indexpred = index;
        max = cs;
        index = i+1;
    }
  }
  if(max>=compris){
    return index;
  }
  else if (max >= confirmer){
      return confirmation(index, indexpred);
  }
  else{
      return -1;
  }
}