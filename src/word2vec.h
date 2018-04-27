#include "config.h"
#include <iostream>
#include <vector>

#ifndef __WORD_2_VEC__
#define __WORD_2_VEC__

    using namespace std;
    int afficherVec(const char* word, float *vec){
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////// to initialize mikolov algorithm //////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    
        FILE *f;
        char st1[max_size];
        char st[100][max_size];
        float dist, len;
        long long words, size, a, b, c, d, cn, bi[100];
        float *M;
        char *vocab;
        f = fopen(file_name, "rb");
        if (f == NULL) {
        return -1; //input not found errcode
        }
        fscanf(f, "%lld", &words);
        fscanf(f, "%lld", &size);
        vocab = (char *)malloc((long long)words * max_w * sizeof(char));
        M = (float *)malloc((long long)words * (long long)size * sizeof(float));
        if (M == NULL) {
        return -1; //M too long can't allocate memory needed
        }
        for (b = 0; b < words; b++) {
        a = 0;
        while (1) {
            vocab[b * max_w + a] = fgetc(f);
            if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
            if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
        }
        vocab[b * max_w + a] = 0;
        for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
        len = 0;
        for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
        len = sqrt(len);
        for (a = 0; a < size; a++) M[a + b * size] /= len;
        }
        fclose(f);
        
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////// to run mikolov algorithm /////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    
        //clean the words and their similarity to st1[a]
        //printf("Enter word or sentence (EXIT to break): ");
        a = 0;
    
        //treat bad entries
        while (1) {
            st1[a] = word[a];
            if ((st1[a] == '\n') || (a >= max_size - 1)) {
            st1[a] = 0;
            break;
            }
            a++;
        }
    
    
        cn = 0;
        b = 0;
        c = 0;
        //met dans st[cn][b] le mot que l'on a entré en parametre
        while (1) {
            st[cn][b] = st1[c];
            b++;
            c++;
            st[cn][b] = 0;
            if (st1[c] == 0) break;
            if (st1[c] == ' ') break;
        }
        cn++;
    
        for (a = 0; a < cn; a++) {
            for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
            if (b == words) b = -1;
            bi[a] = b;
            //printf("Word: %s  Position in vocabulary: %lld\n\n", st[a], bi[a]);
            if (b == -1) {
            return -1;
            //printf("Out of dictionary word!\n");
            break;
            }
        }
        //if (b == -1) continue;
        //printf("\n                                              Word       Cosine distance\n------------------------------------------------------------------------\n");
        for (a = 0; a < size; a++) vec[a] = 0;
        for (b = 0; b < cn; b++) {
            if (bi[b] == -1) continue;
            for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
        }
        len = 0;
        for (a = 0; a < size; a++) len += vec[a] * vec[a];
        len = sqrt(len);
        for (a = 0; a < size; a++) vec[a] /= len;
        
        
        /*for (b = 0; b < size; b++) printf(" %f |", vec[b]);
        printf("\n");*/

    
        return 1;
    }

    //ici on calcule la similarité cosinus de deux vecteur de taille vector_length
    float cosine_similarity(std::vector<float> A, std::vector<float> B, long long Vector_Length)
    {
        float dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
        for(long long i = 0; i < Vector_Length; ++i) {
            dot += A[i] * B[i] ;
            denom_a += A[i] * A[i] ;
            denom_b += B[i] * B[i] ;
        }
        return dot / (sqrt(denom_a) * sqrt(denom_b)) ;
    }


#endif