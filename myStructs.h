typedef struct TripStruct Trip_t;
typedef struct LinkedList LinkedList_t;
typedef struct BST BST_t;

struct TripStruct{
    char PUDateTimeID[MAXFIELDSIZE];
    char VendorID[MAXFIELDSIZE];
    char passengerCount[MAXFIELDSIZE];
    char tripDistance[MAXFIELDSIZE];
    char RatecodeID[MAXFIELDSIZE];
    char storeAndFwdFlag[MAXFIELDSIZE];
    char PULocID[MAXFIELDSIZE];
    char DOLocID[MAXFIELDSIZE];
    char paymentTypeID[MAXFIELDSIZE];
    char fareAmount[MAXFIELDSIZE];
    char extras[MAXFIELDSIZE];
    char MTATax[MAXFIELDSIZE];
    char tipAmount[MAXFIELDSIZE];
    char tollsAmount[MAXFIELDSIZE];
    char improvementSurcharge[MAXFIELDSIZE];
    char totalAmount[MAXFIELDSIZE]; //redundant
    char DODateTimeID[MAXFIELDSIZE];
    char tripDuration[MAXFIELDSIZE]; //redundant
    
    Trip_t *next;
};
struct LinkedList{
   // struct LinkedTrips *head;
    Trip_t *head;
    //struct LinkedTrips *tail;
    Trip_t *tail;
    
    int size;
};
struct BST {
    struct BST *left;
    struct BST *right;
    LinkedList_t *data;
};