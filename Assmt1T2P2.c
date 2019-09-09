#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "myDefinitions.h" //MAKE SURE THIS IS FIRST
#include "myStructs.h"     //AND THIS IS SECOND
#include "myDictFuncs.h"   //And this is the final one

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

int PULoc_comparator(char Loc1Str[], char Loc2Str[]);
void swap(Trip_t *a, Trip_t *b);

void print_Trip(Trip_t *trip, char *outFilename);
int search_BST(BST_t *parent, char key[], int counter, char *outFilename);
void search_controller(char *outFilename, BST_t *Dict);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

int PULoc_comparator(char Loc1Str[], char Loc2Str[]){ 
    /* This function compares two location IDs given in any number format */
    /* If the location IDs are shown to be the same value, 2 is returned  */
    /* If the first location ID is smaller than the second, 1 is returned */
    /* If the first location ID is larger than the second, 0 is returned  */
    
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
    /* Insert each Trip_t into the BST by their date time primary key */
    
    /* If the parent does not already exist or the linked list is empty, it */
    /*   is created and the trip is added to the head of the linked list    */
    if(parent == 0){
        parent = new_BST();
        linked_list_add_end(parent->data, trip);
    }
    else if(parent->data->size == 0){
        linked_list_add_end(parent->data, trip);
    }
    else{
        /* Traverse the tree to get the point in which the trip is located */
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
    
    /* Enter here to balance if time constraints allow */
    return parent;
}
void print_Trip(Trip_t *trip, char *outFilename){
    /* open the file and print all data stored in the Trip_t struct into it */
    FILE *file;
    file = fopen(outFilename, "a");
    
    fprintf(file, "%s --> ", trip->PULocID);
    fprintf(file, "%s", trip->PUDateTimeID);
    fprintf(file, "\n");
    
    fclose(file);
    
}
/* From past tutorials in Foundations of Algorithms */
void bubbleSort(Trip_t *start){ 
    /*  initiate variables */
    int swapped, i; 
    Trip_t *ptr; 
    Trip_t *lptr = NULL; 
    
    /* make sure the list is not empty */
    if (start == NULL){
        return; 
    }
    
    do{ 
        swapped = 0; 
        ptr = start; 
  
        /* loops through each value in the list */
        while (ptr->next != lptr){ 
            /* check if the two trips need to be swapped */
            if (date_comparator(ptr->PUDateTimeID,ptr->next->PUDateTimeID) == 0){
                swap(ptr, ptr->next); 
                swapped = 1; 
            } 
            ptr = ptr->next; 
        } 
        lptr = ptr; 
        
       /* stop when the list isnt changed after going through the full loop */ 
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
	
    /* Access each node individually to print them to the output file */
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
        /* If there is no node with the specified key output NOT FOUND to */
        /*   the output file                                              */
        FILE *file;
        file = fopen(outFilename, "a");
        
        fprintf(file, "NOT FOUND\n");
        
        fclose(file);
        return counter;
    }
    /* The algorithm to search the binary search tree and */ 
    /*   print all nodes in the associated linked list    */
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
    /* clear output file */
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
            /* After the each key is collected from the file, it is inputed */
            /*  into the search function, where each value for the inputed  */
            /*  keys are stored in the specified text file and the number   */
            /*  of comparisons are printed to the standard output           */
            int counter = search_BST(Dict, key, 1, outFilename);
            printf("%s --> %d\n", key, counter);
			empty_string(key, MAXFIELDSIZE);
            i = 0;
		}
	}
    /* The final key is inputed into the search tree in the same way */
    /*   fashion as the previous keys                                */
    if(c == EOF){
        int counter = search_BST(Dict, key, 1, outFilename);
        printf("%s --> %d\n", key, counter);   
    }
}

int main(int argc, char **argv){
	if (argc >= 3){
        //Create the Dictionary BST
        BST_t *Dict = new_BST();
        
        int len = strlen(argv[1]);
        
        /* checks if the input is within a csv file or otherwise as */
        /*    explained in other file                               */
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