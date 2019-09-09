#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "myDefinitions.h" //MAKE SURE THIS IS FIRST
#include "myStructs.h"     //AND THIS IS SECOND
#include "myDictFuncs.h"   //And this is the final one

void print_Trip(Trip_t *trip, char *outFilename);
void print_LinkedList(LinkedList_t *list, char *outFilename);
int search_BST(BST_t *parent, char key[], int counter, char *outFilename);
void search_controller(char *outFilename, BST_t *Dict);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

BST_t *bst_insert(BST_t *parent, Trip_t *trip){
    if(parent == 0){
        parent = new_BST();
        linked_list_add_end(parent->data, trip);
    }
    else if(parent->data->size == 0){
        linked_list_add_end(parent->data, trip);
    }
    else{
        if(date_comparator(parent->data->head->PUDateTimeID,
                           trip->PUDateTimeID) == 0){
            parent->left = bst_insert(parent->left, trip);
        }
        else if(date_comparator(parent->data->head->PUDateTimeID,
                                trip->PUDateTimeID) == 1){
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
    
    fprintf(file, "%s --> ", trip->PUDateTimeID);
    fprintf(file, "VendorID: %s || ", trip->VendorID);
    fprintf(file, "passenger count: %s || ", trip->passengerCount);
    fprintf(file, "trip distance: %s || ", trip->tripDistance);
    //*
    fprintf(file, "ratecode ID: %s || ", trip->RatecodeID);
    fprintf(file, "store and forward flag: %s || ", trip->storeAndFwdFlag);
    fprintf(file, "pick-up location ID: %s || ", trip->PULocID);
    fprintf(file, "drop-off location ID: %s || ", trip->DOLocID);
    //*/
    fprintf(file, "payment type: %s || ", trip->paymentTypeID);
    fprintf(file, "fare amount: %s || ", trip->fareAmount);
    fprintf(file, "extra: %s || ", trip->extras);
    fprintf(file, "mta tax: %s || ", trip->MTATax);
    fprintf(file, "tip amount: %s || ", trip->tipAmount);
    fprintf(file, "tolls amount: %s || ", trip->tollsAmount);
    fprintf(file, "improvement surcharge: %s || ", trip->improvementSurcharge);
    fprintf(file, "total amount: %s || ", trip->totalAmount);
    fprintf(file, "DOdatetime: %s || ", trip->DODateTimeID);
    fprintf(file, "trip duration: %s ||", trip->tripDuration);
    fprintf(file, "\n");
    
    fclose(file);
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
        FILE *file;
        file = fopen(outFilename, "a");
        
        fprintf(file, "%s --> ", key);
        fprintf(file, "NOT FOUND\n");
        
        fclose(file);
        return counter;
    }
    if(date_comparator(parent->data->head->PUDateTimeID,
                       key) == 0){
        counter = search_BST(parent->left, key, counter + 1, outFilename);
    }
    else if(date_comparator(parent->data->head->PUDateTimeID,
                            key) == 1){
        counter = search_BST(parent->right, key, counter + 1, outFilename);
    }
    else{
        print_LinkedList(parent->data, outFilename);
    }
    
    return counter;
}
void search_controller(char *outFilename, BST_t *Dict){
    //clear output file
    FILE *file;
    file = fopen(outFilename, "w");
    fclose(file);
    
    char key[MAXFIELDSIZE];
    empty_string(key, MAXFIELDSIZE);
    
    int i = 0, c;
    while (((c = getchar()) != EOF)) {
		if ((c != '\n') && (c != '\r')) {
			key[i++] = c;
		} 
        else {
            int counter = search_BST(Dict, key, 1, outFilename);
            printf("%s --> %d\n", key, counter);
			empty_string(key, MAXFIELDSIZE);
            i = 0;
		}
	}if(c == EOF){
        int counter = search_BST(Dict, key, 1, outFilename);
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
                read_csv(argv[1], Dict);
                //read_line_inp(argv[i], Dict);
            }
        }
        //print_tree(Dict, 0);
        //search the tree using the keys in the key file
        search_controller(argv[argc - 1], Dict);
        
        //free the tree
        free_tree(Dict);
	}
    else{
        printf("%d arguments were inputed. At least 3 are required\n", argc);
    }
    
    return 0;
}