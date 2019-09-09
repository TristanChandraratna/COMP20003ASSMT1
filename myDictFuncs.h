void empty_string(char str[], int size);
int create_substring_int(char str[], int startingPos, int noOfLtrs);
int date_comparator(char Time1[], char Time2[]);
void print_tree(BST_t *parent, int counter);

Trip_t *new_trip();
LinkedList_t *new_LinkedList();
BST_t *new_BST();

void edit_Trip(Trip_t *trip, char VendorID[], char PUDateTimeID[], char DODateTimeID[], char passengerCount[], char tripDistance[], char RatecodeID[], 
            char storeAndFwdFlag[], char PULocID[], char DOLocID[], 
            char paymentTypeID[], char fareAmount[], char extras[], 
            char MTATax[], char tipAmount[], char tollsAmount[], 
            char improvementSurcharge[], char totalAmount[], 
            char tripDuration[]);
Trip_t *copy_Trip(Trip_t *Trip);
void linked_list_add_end(LinkedList_t *list, Trip_t *trip);
BST_t *bst_insert(BST_t *parent, Trip_t *trip);

void read_csv(char *filename, BST_t *Dict);
void read_line_inp(char inp[], BST_t *Dict);

void free_trip(Trip_t *trip);
void free_list(LinkedList_t *list);
void free_tree(BST_t *parent);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void empty_string(char str[], int size){
    for(int i = 0; i < size; i++){
        str[i] = '\0';
    }
}
int create_substring_int(char str[], int startingPos, int noOfLtrs){
    char *tmp = malloc(sizeof(char *) * noOfLtrs);
    for(int i = 0; i < noOfLtrs; i++){
        tmp[i] = str[startingPos + i];
    }
    
    int intTmp = atoi(tmp);
    free(tmp);
    
    return intTmp;
}
int date_comparator(char Time1[], char Time2[]){
    if(strcmp(Time1,Time2) == 0){
        return 2;
    }
    else if(strcmp(Time1,Time2) < 0){
        return 1;
    }
    else{
        return 0;
    }
    
    return 1;
}
void print_tree(BST_t *parent, int counter){
    printf("%d %s\n",counter, parent->data->head->PUDateTimeID);
    
    if(parent->left != 0){
        print_tree(parent->left, counter + 1);
    }
    if(parent->right != 0){
        print_tree(parent->right, counter + 1);
    }
}

Trip_t *new_trip(){
    Trip_t *trip = malloc(sizeof *trip);
	assert(trip);

	return trip;
}
LinkedList_t *new_LinkedList(){
    LinkedList_t *LList = malloc(sizeof *LList);
	assert(LList);

	LList->head = NULL;
	LList->tail = NULL;
	LList->size = 0;

	return LList;
}
BST_t *new_BST(){
    BST_t *bst = malloc(sizeof *bst);
	assert(bst);

	bst->left = NULL;
	bst->right = NULL;
	bst->data = new_LinkedList();

	return bst;
}

void edit_Trip(Trip_t *trip, char PUDateTimeID[], char VendorID[], 
            char passengerCount[], char tripDistance[], char RatecodeID[], 
            char storeAndFwdFlag[], char PULocID[], char DOLocID[], 
            char paymentTypeID[], char fareAmount[], char extras[], 
            char MTATax[], char tipAmount[], char tollsAmount[], 
            char improvementSurcharge[], char totalAmount[], 
            char DODateTimeID[], char tripDuration[]){
    
    strcpy(trip->PUDateTimeID, PUDateTimeID); 
    strcpy(trip->VendorID, VendorID);
    strcpy(trip->passengerCount, passengerCount);
    strcpy(trip->tripDistance, tripDistance);
    strcpy(trip->RatecodeID, RatecodeID);
    strcpy(trip->storeAndFwdFlag, storeAndFwdFlag);
    strcpy(trip->PULocID, PULocID);
    strcpy(trip->DOLocID, DOLocID);
    strcpy(trip->paymentTypeID, paymentTypeID);
    strcpy(trip->fareAmount, fareAmount);
    strcpy(trip->extras, extras);
    strcpy(trip->MTATax, MTATax);
    strcpy(trip->tipAmount, tipAmount);
    strcpy(trip->tollsAmount, tollsAmount);
    strcpy(trip->improvementSurcharge, improvementSurcharge);
    strcpy(trip->totalAmount, totalAmount);
    strcpy(trip->DODateTimeID, DODateTimeID);
    strcpy(trip->tripDuration, tripDuration);
    
    
}
Trip_t *copy_Trip(Trip_t *trip){
    Trip_t *newTrip = new_trip();
    
    strcpy(newTrip->PUDateTimeID, trip->PUDateTimeID); 
    strcpy(newTrip->VendorID, trip->VendorID);
    strcpy(newTrip->passengerCount, trip->passengerCount);
    strcpy(newTrip->tripDistance, trip->tripDistance);
    strcpy(newTrip->RatecodeID, trip->RatecodeID);
    strcpy(newTrip->storeAndFwdFlag, trip->storeAndFwdFlag);
    strcpy(newTrip->PULocID, trip->PULocID);
    strcpy(newTrip->DOLocID, trip->DOLocID);
    strcpy(newTrip->paymentTypeID, trip->paymentTypeID);
    strcpy(newTrip->fareAmount, trip->fareAmount);
    strcpy(newTrip->extras, trip->extras);
    strcpy(newTrip->MTATax, trip->MTATax);
    strcpy(newTrip->tipAmount, trip->tipAmount);
    strcpy(newTrip->tollsAmount, trip->tollsAmount);
    strcpy(newTrip->improvementSurcharge, trip->improvementSurcharge);
    strcpy(newTrip->totalAmount, trip->totalAmount);
    strcpy(newTrip->DODateTimeID, trip->DODateTimeID);
    strcpy(newTrip->tripDuration, trip->tripDuration);
    
    return newTrip;
}
// From list.c given in Foundations of Algorithims
// remove and return the front data element from a list
// this operation is O(1)
// error if the list is empty (so first ensure list_size() > 0)
void linked_list_add_end(LinkedList_t *list, Trip_t *trip) {
    
	assert(list != NULL);

	// we'll need a new list node to store this data
	Trip_t *LTrip = copy_Trip(trip);
    
	if(list->size == 0) {
		// if the list was empty, new node is now the first node
		list->head = LTrip;
	} 
    else {
		// otherwise, it goes after the current last node
		list->tail->next = LTrip;
	}

	// place this new node at the end of the list
	list->tail = LTrip;

	// and keep size updated too
	list->size++;
    
    
}

void read_csv(char *filename, BST_t *Dict){
	FILE *file;
	file = fopen(filename, "r+");
    assert(file != NULL);
    
    char buffer[MAXFIELDSIZE];
    fgets(buffer, MAXFIELDSIZE, file);
    
    char PUDateTimeID[MAXFIELDSIZE], DODateTimeID[MAXFIELDSIZE], 
        VendorID[MAXFIELDSIZE], passengerCount[MAXFIELDSIZE], 
        RatecodeID[MAXFIELDSIZE], storeAndFwdFlag[MAXFIELDSIZE], 
        PULocID[MAXFIELDSIZE], DOLocID[MAXFIELDSIZE], 
        paymentTypeID[MAXFIELDSIZE], tripDistance[MAXFIELDSIZE], 
        fareAmount[MAXFIELDSIZE], extras[MAXFIELDSIZE],
        MTATax[MAXFIELDSIZE], tipAmount[MAXFIELDSIZE],
        tollsAmount[MAXFIELDSIZE], improvementSurcharge[MAXFIELDSIZE],
        totalAmount[MAXFIELDSIZE], tripDuration[MAXFIELDSIZE];
    
    empty_string(PUDateTimeID, MAXFIELDSIZE);
    empty_string(DODateTimeID, MAXFIELDSIZE);
    empty_string(VendorID, MAXFIELDSIZE);
    empty_string(passengerCount, MAXFIELDSIZE);
    empty_string(RatecodeID, MAXFIELDSIZE);
    empty_string(storeAndFwdFlag, MAXFIELDSIZE);
    empty_string(PULocID, MAXFIELDSIZE);
    empty_string(DOLocID, MAXFIELDSIZE);
    empty_string(paymentTypeID, MAXFIELDSIZE);
    empty_string(tripDistance, MAXFIELDSIZE);
    empty_string(fareAmount, MAXFIELDSIZE);
    empty_string(extras, MAXFIELDSIZE);
    empty_string(MTATax, MAXFIELDSIZE);
    empty_string(tipAmount, MAXFIELDSIZE);
    empty_string(tollsAmount, MAXFIELDSIZE);
    empty_string(improvementSurcharge, MAXFIELDSIZE);
    empty_string(totalAmount, MAXFIELDSIZE);
    empty_string(tripDuration, MAXFIELDSIZE);
    
	while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,^\n]",
                VendorID, passengerCount, tripDistance, 
                RatecodeID, storeAndFwdFlag, PULocID, DOLocID, 
                paymentTypeID, fareAmount, extras, MTATax, 
                tipAmount, tollsAmount, improvementSurcharge, 
                totalAmount, PUDateTimeID, DODateTimeID, 
                tripDuration) == NOOFCOLUMNS){
        
        Trip_t *trip = new_trip();
        if (VendorID[0] == '\n'){
            memmove(VendorID, VendorID+1, strlen(VendorID));
        }
        
        edit_Trip(trip, PUDateTimeID, VendorID, passengerCount,
                tripDistance, RatecodeID, storeAndFwdFlag, PULocID,
                  DOLocID, paymentTypeID, fareAmount, extras,  MTATax,
                  tipAmount, tollsAmount, improvementSurcharge,
                  totalAmount, DODateTimeID, tripDuration);

        bst_insert(Dict, trip);
        
        free(trip);
        
        for(int i = 0; i < 0;i++){
            fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,^\n]",
                VendorID, passengerCount, tripDistance, 
                RatecodeID, storeAndFwdFlag, PULocID, DOLocID, 
                paymentTypeID, fareAmount, extras, MTATax, 
                tipAmount, tollsAmount, improvementSurcharge, 
                totalAmount, PUDateTimeID, DODateTimeID, 
                tripDuration);
        }
    }
    
    fclose(file);
}
void read_line_inp(char inp[], BST_t *Dict){
    Trip_t trip = *new_trip();
    edit_Trip(&trip, 
              strtok(inp, ","), 
              strtok(NULL, ","), 
              strtok(NULL, ","),
              strtok(NULL, ","), 
              strtok(NULL, ","), 
              strtok(NULL, ","), 
              strtok(NULL, ","),
              strtok(NULL, ","), 
              strtok(NULL, ","), 
              strtok(NULL, ","), 
              strtok(NULL, ","),  
              strtok(NULL, ","),
              strtok(NULL, ","), 
              strtok(NULL, ","), 
              strtok(NULL, ","),
              strtok(NULL, ","), 
              strtok(NULL, ","), 
              strtok(NULL, ","));
    bst_insert(Dict, &trip);
}

void free_trip(Trip_t *trip){    
    free(trip);
}
// Also stolen from list.c Foundations of Algorithms
void free_list(LinkedList_t *list) {
	assert(list != NULL);
	// free each node
	Trip_t *node = list->head;
	Trip_t *next;
	while (node) {
		next = node->next;
		free_trip(node);
		node = next;
	}
	// free the list struct itself
	free(list);
}
void free_tree(BST_t *parent){
    if(! parent){
        return;
    }
    /* Fill in function according to function description. */
    if(parent->right != 0){
        free_tree(parent->right);
    }
    if(parent->left != 0){
        free_tree(parent->left);
    }
    
    free_list(parent->data);
    free(parent);
}
