
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

#ifndef __H_CONFIG__
#define __H_CONFIG__


    const long long max_size = 2000;         // max length of strings
    //const long long N = 10;                  // number of closest words that will be shown
    const long long max_w = 50;              // max length of vocabulary entries
    const char file_name[max_size] = "data/bibliofr.bin"; //name of biblio used
    const char file_name_rep[max_size] = "data/exemples.csv";
    const char file_stopWord[max_size] = "data/stopwords_fr.txt";
    const char separateur = '|';

    //similarité cosinus minimum pour donner une reponse sure / voir decision
    float compris = 0.8;
    float confirmer = 0.6;

#endif