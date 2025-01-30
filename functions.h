#ifndef _FUNCTIONS_
#define _FUNCTIONS_

// ----------------------------------------------------------------------------
Queue initQueue(){
    Queue q;
    q.front = NULL;
    q.rear = NULL;
    return q;
}

List createList(Tree value){
    
    List head = malloc( sizeof(struct list) );
    head->valoare = value;
    head->next = NULL;
    return head;

}

void enqueue(Queue *q, Tree nod){
    
    if( q->front == NULL ){
        q->front = q->rear = createList(nod);
    } else {
        List list = createList(nod);
        q->rear->next = list;
        q->rear = list;
    }

}

Tree dequeue(Queue *q){
    
    if (q->front == NULL)
        return NULL;
    Tree result = q->front->valoare;
    List tmp = q->front;
    q->front = q->front->next;
    if ( tmp->next == NULL ) {
        q->rear = NULL;
    }
    free(tmp);
    return result;

}

// ----------------------------------------------------------------------------

Tree createQuadTree(Tree root){
    
    root = malloc(sizeof(struct node));
    root->first = NULL;
    root->second = NULL;
    root->third = NULL;
    root->fourth = NULL;
    root->color.blue = 0;
    root->color.red = 0;
    root->color.green = 0;
    root->size = 0;
    root->type = 1;
    return root;

}

Color** ReadMatrix( FILE * in, int height){
    
    Color **colormatrix = (Color **) calloc(height, sizeof(Color*));
        
        for (int i = 0; i < height; i++) {
            
            colormatrix[i] = calloc(height, sizeof(Color));
            
        }
        
        for(int i = 0; i < height; i++ ) {
            for(int j = 0; j < height; j++) {
                
                fread(&colormatrix[i][j].red, 1, 1, in);
                fread(&colormatrix[i][j].green, 1, 1, in);
                fread(&colormatrix[i][j].blue, 1, 1, in);
               
            }
            
        }
    return colormatrix;

}

Tree entireQuadTree(Tree root, int size, Color **cm, int x, int y, int p){
    
    if( size ==  0 ) {
        return root;
    }
    root->size = size;
    long long int mean = 0, red = 0, green = 0, blue = 0;
    for (int i = x; i < size+x; i++) {
        for(int j = y; j < size+y ; j++) {
            red += cm[i][j].red;
        }
    }
    root->color.red = red/(size*size);
    for (int i = x; i < size+x; i++) {
        for(int j = y; j < size+y ; j++) {
            blue += cm[i][j].blue;
        }
    }
    root->color.blue = blue/(size*size);
    for (int i = x; i < size+x; i++) {
        for(int j = y; j < size+y ; j++) {
            green += cm[i][j].green;
        }
    }
    root->color.green = green/(size*size);
    for (int i = x; i < size+x; i++) {
        for(int j = y; j < size+y ; j++) {
            
            mean = (root->color.red-cm[i][j].red)*
            (root->color.red-cm[i][j].red)+
            (root->color.blue-cm[i][j].blue)*
            (root->color.blue-cm[i][j].blue)+
            (root->color.green-cm[i][j].green)*
            (root->color.green-cm[i][j].green) 
            + mean;

        }
    }
    mean = mean /(size*size*3);
    if ( mean > p ) {
        root->type = 0;
        root->first = createQuadTree(root->first);
        root->first = entireQuadTree(root->first, size/2, cm, x, y, p);
        root->second = createQuadTree(root->second);
        root->second = entireQuadTree(root->second, size/2, cm, x, y+size/2, p);
        root->third = createQuadTree(root->third);
        root->third = entireQuadTree(root->third, size/2, cm, x+size/2, y+size/2, p);
        root->fourth = createQuadTree(root->fourth);
        root->fourth = entireQuadTree(root->fourth, size/2, cm, x+size/2, y, p);
    } 
    return root;

}
// Functie auxiliara pentru heightTree
int max(int a, int b, int c, int d){
    
    int *vect = malloc(4*sizeof(int));
    vect[0] = a;
    vect[1] = b;
    vect[2] = c;
    vect[3] = d;
    int max = vect[0];
    for ( int i = 0; i < 4; i++) {
        if( vect[i] > max) {
            max = vect[i];
        }
    }
    free(vect);
    return max;

}

int heightTree(Tree root){
    
    if (root == NULL) return 0;
    int one=0, two=0, three=0, four=0;
    one = heightTree(root->first);
    two = heightTree(root->second);
    three = heightTree(root->third);
    four = heightTree(root->fourth);
    return max(one,two,three,four)+1;

}

int MaxSizeNediv(Tree root, int *n){
    
    int ok = 0, nr =0;
    if(root == NULL) {
        return 0;
    }
    Queue q = initQueue();
    Tree current;
    enqueue(&q, root);
    while(q.front != NULL) {
        current = dequeue(&q);
        if(current != NULL) {
            if (current->type == 1) {
                if ( ok == 0 ) {
                    ok = 1;
                    *n = current->size;
                }
                nr++;
            } 
            enqueue(&q, current->first);
            enqueue(&q, current->second);
            enqueue(&q, current->third);
            enqueue(&q, current->fourth);
        }
    }
    return nr;

}

int NeDiv(Tree root) {
    
    int n = 0;
    if(root == NULL) {
        return 0;
    }
    Queue q = initQueue();
    Tree current;
    enqueue(&q, root);
    while(q.front != NULL) {
        current = dequeue(&q);
        if(current != NULL) {
            if (current->type == 1) n++; 
            enqueue(&q, current->first);
            enqueue(&q, current->second);
            enqueue(&q, current->third);
            enqueue(&q, current->fourth);
        }
    }
    return n;

}

void cerinta2(Tree root, FILE *out){
    
    if(root == NULL){
        return ;
    }
    Queue q = initQueue();
    Tree current;
    int ret = 1;
    enqueue(&q, root);
    fwrite(&root->size, sizeof(int),1 , out);
    while(q.front != NULL) {
        current = dequeue(&q);
        if(current != NULL) {
            if ( current->type == 0) {
                fwrite(&current->type, 1, 1, out);
            } else {
                fwrite(&current->type, 1, 1, out);
                fwrite(&current->color.red, 1, 1, out);
                fwrite(&current->color.green, 1, 1, out);
                fwrite(&current->color.blue, 1, 1, out);  
            }
            enqueue(&q, current->first);
            enqueue(&q, current->second);
            enqueue(&q, current->third);
            enqueue(&q, current->fourth);
        }
    }

}

Tree cerinta3(Tree root, FILE *in){
    
    Queue q = initQueue();
    int size = 0, type = 2;
    fread(&size, sizeof(int),1 , in);
    fread(&type, 1, 1, in);
    if (type == 0){
        root->type = 0;
        enqueue(&q, root);
    } else {
        fread(&root->color.red, 1, 1, in);
        fread(&root->color.green, 1, 1, in);
        fread(&root->color.blue, 1, 1, in);
        root->size = size;
        return root;
    }
    Tree current;
    while(q.front != NULL) {     
    
        current = dequeue(&q);
            for( int i = 0; i < 4; i++){
                fread(&type, 1, 1, in);
                    switch (i)
                    {
                    case 0:
                        if (type == 0) {
                            current->first = createQuadTree(current->first);
                            current->first->type = 0;
                            enqueue(&q, current->first);
                        } else {
                            current->first = createQuadTree(current->first);
                            fread(&current->first->color.red, 1, 1, in);
                            fread(&current->first->color.green, 1, 1, in);
                            fread(&current->first->color.blue, 1, 1, in);
                        }
                        break;
                    case 1:
                        if (type == 0) {
                            current->second = createQuadTree(current->second);
                            current->second->type = 0;
                            enqueue(&q, current->second);
                        } else {
                            current->second = createQuadTree(current->second);
                            fread(&current->second->color.red, 1, 1, in);
                            fread(&current->second->color.green, 1, 1, in);
                            fread(&current->second->color.blue, 1, 1, in);
                        }
                        break;
                    case 2:
                        if (type == 0) {
                            current->third = createQuadTree(current->third);
                            current->third->type = 0;
                            enqueue(&q, current->third);
                        } else {
                            current->third = createQuadTree(current->first);
                            fread(&current->third->color.red, 1, 1, in);
                            fread(&current->third->color.green, 1, 1, in);
                            fread(&current->third->color.blue, 1, 1, in);
                        }
                        
                        break;
                    case 3:
                        if (type == 0) {
                            current->fourth = createQuadTree(current->fourth);
                            current->fourth->type = 0;
                            enqueue(&q, current->fourth);
                        } else {
                            current->fourth = createQuadTree(current->first);
                            fread(&current->fourth->color.red, 1, 1, in);
                            fread(&current->fourth->color.green, 1, 1, in);
                            fread(&current->fourth->color.blue, 1, 1, in);
                        }
                        break;
                    default:
                        printf("Da o ncolo\n");
                        break;
                    }

            } // end for

    }
    root->size = size;
    return root;

}

Color ** MatrixDec(Tree root, int size, Color **cm, int x, int y){
    
    if( root->first == NULL && 
    root->second == NULL && 
    root->third == NULL && 
    root->fourth == NULL) {
        for ( int i = y; i < size+y; i++) {
            for( int j = x; j < size+x ; j++) {
                cm[i][j].red = root->color.red;
                cm[i][j].green = root->color.green;
                cm[i][j].blue = root->color.blue;
            }
        }
    } else {
        MatrixDec(root->first , size/2, cm, x       , y);
        MatrixDec(root->second, size/2, cm, x+size/2, y);
        MatrixDec(root->third , size/2, cm, x+size/2, y+size/2);
        MatrixDec(root->fourth, size/2, cm, x, y+size/2);
    }
   return cm;

}

void FreeMatrix(Color ** colormatrix, int height) {
    
        for (int i = 0; i < height; i++) {
            free(colormatrix[i]);          
        }
        
        free(colormatrix);

}

void FinalCerinta3(Tree root, FILE * out) {
    
    Color **cm = (Color **) calloc(root->size, sizeof(Color*));
    for (int i = 0; i < root->size; i++) {
            cm[i] = calloc(root->size, sizeof(Color));
    }
    cm = MatrixDec(root, root->size, cm, 0, 0);
    
    fprintf(out, "P6\n");
    fprintf(out,"%d %d\n", root->size, root->size);
    fprintf(out,"255\n");
    for( int i = 0; i < root->size; i++ ) {
            for( int j = 0; j < root->size; j++) {
                
                fwrite(&cm[i][j].red, 1, 1, out);
                fwrite(&cm[i][j].green, 1, 1, out);
                fwrite(&cm[i][j].blue, 1, 1, out);
            
            }

        }
    FreeMatrix(cm, root->size);

}



void FreeQuadTree( Tree root) {
    if( root == NULL) return;
    FreeQuadTree(root->first);
    FreeQuadTree(root->second);
    FreeQuadTree(root->third);
    FreeQuadTree(root->fourth);
    free(root);
}












#endif // _FUNCTIONS_