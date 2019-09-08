#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "myDefinitions.h" //MAKE SURE THIS IS FIRST
#include "myStructs.h"     //AND THIS IS SECOND
#include "myDictFuncs.h"   //And this is the final one

int PULoc_comparator(char Loc1Str[], char Loc2Str[]);

void print_Trip(Trip_t *trip, char *outFilename);
int search_BST(BST_t *parent, char key[], int counter, char *outFilename);
void search_controller(char *outFilename, BST_t *Dict);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

int PULoc_comparator(char Loc1Str[], char Loc2Str[]){ 
    //returns 0 if Time2 is < Time1
    //returns 1 if Time2 is > Time1
    //returns 2 if Time2 == Time1
    
    int Loc1 = atoi(Loc1Str);
    int Loc2 = atoi(Loc2Str);
    
    if(Loc1 == Loc2){
        return 2;
    }
    else if(Loc1 < Loc2){
        return 1;
    }
    else{
        return 0;
    }
}

void print_Trip(Trip_t *trip, char *outFilename){
    printf("%s --> ", trip->PULocID);
    printf("%s", trip->PUDateTimeID);
    printf("\n");
}
void print_LinkedList(LinkedList_t *list, char *outFilename){
    assert(list != NULL);
	// free each node
	Trip_t *node = list->head;
	Trip_t *next;
	while (node) {
		next = node->next;
		print_Trip(node, outFilename);
		node = next;
	}
}
int search_BST(BST_t *parent, char key[], int counter, char *outFilename){
    if(parent == NULL){
        printf("NOT FOUND\n");
        return counter;
    }
    if(PULoc_comparator(parent->data->head->PULocID,
                           key) == 0){
        counter = search_BST(parent->left, key, counter + 1, outFilename);
    }
    else if(PULoc_comparator(parent->data->head->PULocID,
                                key) == 1){
        counter = search_BST(parent->right, key, counter + 1, outFilename);
    }
    else{
        print_LinkedList(parent->data, outFilename);
    }
    return counter;
}
void search_controller(char *outFilename, BST_t *Dict){
    FILE *file;
    file = fopen(outFilename, "w");
    fclose(file);
    
    char key[MAXFIELDSIZE];
    empty_string(key, MAXFIELDSIZE);
    
    while (scanf("%s",
                key) == 1){
        int counter = search_BST(Dict, key, 0, outFilename);
        printf("%s --> %d\n", key, counter);
    }
    
    
}

int main(int argc, char **argv){
	if (argc >= 3){
        //Create the Dictionary BST
        BST_t *Dict = new_BST();
        
        int len = strlen(argv[1]);
        if(argv[1][len - 4] == '.' && argv[1][len - 3] == 'c' && argv[1]
           [len - 2] == 's' && argv[1][len - 1] == 'v'){
		    read_csv(argv[1], Dict);
        }
        else{
            for(int i = 1; i < argc - 1; i++){
                read_line_inp(argv[i], Dict);
            }
        }
        
        search_controller(argv[argc - 1], Dict);
        
        
        //free the tree
        //free_tree(Dict);
	}
    else{
        printf("%d arguments were inputed. At least 3 are required\n", argc);
    }
	
    return 0;
}