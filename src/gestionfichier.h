#include "config.h"
#include "word2vec.h"
#include <iostream>
#include <vector>
#include <sstream>


using namespace std;
//nombre de ligne de mon fichier contenant les reponse (exemple.txt)
int nbligne(){
    std::ifstream fichier(file_name_rep, std::ios::in);  // on ouvre le fichier en lecture
    int index = 0;
    if(fichier)  // si l'ouverture a réussi
    {
        std::string ligne;
        while(getline(fichier, ligne))  // on met dans "contenu" la ligne
            index++; //on passe a la ligne suivante
    }
    fichier.close();
    return index;
}


//fonction pour separer les mot d'une phrase
std::vector<std::string> split(const std::string &text, char sep) {
    
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
      tokens.push_back(text.substr(start, end - start));
      start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}


//je parse le string en parametre en enlevant les stopword
//je met les mots dans un char**
int supprimerStopWord(std::string monString, char** monTableau){
   
    int mot = 0;
    vector<std::string> results = split(monString, ' ');
    bool isWS[results.size()];
    std::ifstream fichier(file_stopWord, std::ios::in);
    std::string ligne;

    for (int i = 0 ; i < results.size() ; ++i) isWS[i] = false; //tableau bool a false
    if (fichier){
        while(getline(fichier, ligne)){  //pour chaque ligne
            for (int i = 0 ; i < results.size() ; ++i){ //je regarde dans mon vecteur de mots
                if(ligne == results[i]) // si le mot est dans les stopwords
                    isWS[i] = true; // si oui je met le bool correspondant a true
            }
        }
    }
    fichier.close();
    for (int i = 0 ; i < results.size() ; ++i){ // pour chaque mot dans mon vecteur
        if(!isWS[i]){                           // si le mot n'est pas un stop word
            strcpy(monTableau[mot], results[i].c_str()); // je le met dans mon tableau
            mot++;                                      // j'augmente le nombre de mot
            //cout << mot << " " << results[i] << endl;
        }
    }

    return mot;
}



