#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "myDefinitions.h" //MAKE SURE THIS IS FIRST
#include "myStructs.h"     //AND THIS IS SECOND
#include "myDictFuncs.h"   //And this is the final one

int PULoc_comparator(char Loc1Str[], char Loc2Str[]);
void swap(Trip_t *a, Trip_t *b);

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
BST_t *bst_insert(BST_t *parent, Trip_t *trip){
    if(parent == 0){
        parent = new_BST();
        linked_list_add_end(parent->data, trip);
    }
    else if(parent->data->size == 0){
        linked_list_add_end(parent->data, trip);
    }
    else{
        if(PULoc_comparator(parent->data->head->PULocID,
                           trip->PULocID) == 0){
            parent->left = bst_insert(parent->left, trip);
        }
        else if(PULoc_comparator(parent->data->head->PULocID,
                                trip->PULocID) == 1){
            parent->right = bst_insert(parent->right, trip);
        }
        else{
            linked_list_add_end(parent->data, trip);
        }
    }
    
    //Enter here to balance
    
    
    return parent;
}
void print_Trip(Trip_t *trip, char *outFilename){
    FILE *file;
    file = fopen(outFilename, "a");
    
    fprintf(file, "%s --> ", trip->PULocID);
    fprintf(file, "%s", trip->PUDateTimeID);
    fprintf(file, "\n");
    
    fclose(file);
    
}
/* From Foundations of Algorithms */
void bubbleSort(Trip_t *start){ 
    int swapped, i; 
    Trip_t *ptr1; 
    Trip_t *lptr = NULL; 
    
    if (start == NULL){
        return; 
    }
  
    do{ 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr){ 
            if (date_comparator(ptr1->PUDateTimeID,ptr1->next->PUDateTimeID) == 0){  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    }while (swapped); 
} 
void swap(Trip_t *a, Trip_t *b){ 
    Trip_t *temp = a; 
    a = b; 
    b = temp; 
} 
void print_LinkedList(LinkedList_t *list, char *outFilename){
    assert(list != NULL);
    bubbleSort(list->head);
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
        FILE *file;
        file = fopen(outFilename, "a");
        
        fprintf(file, "NOT FOUND\n");
        
        fclose(file);
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
        free_tree(Dict);
	}
    else{
        printf("%d arguments were inputed. At least 3 are required\n", argc);
    }
	
    return 0;
}