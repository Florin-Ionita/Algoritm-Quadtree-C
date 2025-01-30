#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

int main(int argc, char *argv[]) {

    int p = 0; // Pragul 
    Tree root = createQuadTree(root);
    FILE *in;
    FILE *out;
    if (argc == 5) {
        in = fopen(argv[3], "rb");
        out = fopen(argv[4], "w");
    } else {
        if (argc == 4) {
        in = fopen(argv[2], "rb");
        out = fopen(argv[3], "w");
        } else {
        printf("Big error\n");
        }
    }
 
    if ( !in ) {
        printf("File didn't open abort the operation\n");
        exit(1);
    }
    
    if (!strcmp(argv[1], "-c1")){
        
        char tip[2];
        unsigned int width, height;
        unsigned int maxcolor;
        char mychar;
        fscanf(in, "%s", tip);
        fscanf(in, "%d %d", &width, &height);
        fscanf(in, "%d", &maxcolor);
        fscanf(in, "%c", &mychar);
        // Mychar este folosit pentru a citii \n de la unele exemple
        Color **colormatrix = ReadMatrix(in, height);
        // Am efectuat citirea matricei de culori

        p = atoi(argv[2]);
        entireQuadTree(root, width, colormatrix, 0, 0, p);
        int nivel = heightTree(root);
        int *maxsize = malloc(sizeof(int));
        int nediv = MaxSizeNediv(root, maxsize);
        fprintf(out, "%d\n%d\n%d\n", nivel, nediv, *maxsize);
        free(maxsize);
        FreeMatrix(colormatrix, width);
        FreeQuadTree(root);

    }

    if (!strcmp(argv[1], "-c2")){
        
        char tip[2];
        unsigned int width, height;
        unsigned int maxcolor;
        char mychar;
        fscanf(in, "%s", tip);
        fscanf(in, "%d %d", &width, &height);
        fscanf(in, "%d", &maxcolor);
        fscanf(in, "%c", &mychar);
        Color **colormatrix = ReadMatrix(in, height);
        // Am terminat cu citirea fisierului
        p = atoi(argv[2]);
        // atoi imi transforma stringul in int
        entireQuadTree(root, width, colormatrix, 0, 0, p);
        cerinta2(root, out);
        FreeMatrix(colormatrix, width);
        FreeQuadTree(root);
    }

    if(!strcmp(argv[1], "-d")) {
        root = cerinta3(root, in);
        FinalCerinta3(root, out);
        FreeQuadTree(root);
    }

    fclose(out);
    fclose(in);
    return 0;
}