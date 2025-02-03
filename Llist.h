// Memory is managed by the caller, both allocation and freeing

// This struct never exists on its own, its always inside a super struct, defined by the user.
// The user should have a way to type-pun a pointer of this struct to a pointer to the super struct, which holds the data
typedef struct llistLink{
    struct llistLink * left;
    struct llistLink * right;
} llistLink;

// The struct that holds the ends of the list. It's fields should be considered
// private, and do not behave as their names would suggest.
typedef llistLink Llist;
//This is because the fields are actually swapped, left points to the right and vici-versa
//It is done like this to make the cursor functionality posssible

void Llist_init(Llist* self);

//The direction enum is used to control the direction of the various other functions.
enum Llist_dir {left, right};

//Pushes a new node onto either end of the list, controlled by dir
void llist_push(enum Llist_dir dir, Llist* self, llistLink* new_node);

//Returns the left/right most node and removes it from the list
llistLink* llist_pop(enum Llist_dir dir, Llist* self);

//Same as pop but does not remove the node from the list

llistLink* llist_peek(enum Llist_dir dir, Llist* self);

//The Cursor is API is exactly like a text Cursor, it can iterate, delete, insert and splice (paste) efficiently.
//This is the type of cursor that lies on a node, and will wrap around if it reaches either end.
//See full behaviour below (in header file).
typedef llistLink* Llist_Cursor;
//When at the end it will point to a 'false node' to signify wrap-around. It does not contain any data.
//is_valid_pos(&cursor,&list) checks if the cursor points to a true node
//Multiple Cursors can co-exist, the node that the cursor is currently on must not be popped or freed
//The cursor may be copied by value, giving another cursor that points to the same node 

// All methods that mutate the cursor take Llist_Cursor*
// If they don't mutate the cursor they take it by value, since it is pointer sized, this has no extra penalty

//Return a cursor to the righmost or leftmost element depending on the passed direction.
//Points to a false node if the list is empty.
Llist_Cursor cursor_new(enum Llist_dir dir, Llist *list);

//Moves the cursor 1 step to the left/right, if already at the end, it will move to the false node.
//If it is already at the false node, then it will end up at the left/right end of the list after moving
void move_cursor(enum Llist_dir dir, Llist_Cursor* self);

//deletes the CURRENT node from the list, and moves either left or right depending on dir
llistLink* delete_move(enum Llist_dir dir, Llist_Cursor* self);

//Splices a given Llist either to the left or the right of the cursor, the cursor does not move
//The Llist struct passed as new_list should be treated as immutable after splicing, or should be ignored entirely
void cursor_splice(enum Llist_dir dir, Llist_Cursor self, Llist* new_list);

//Pushes a single node to the left/right of the current node 
void cursor_push(enum Llist_dir dir, Llist_Cursor self, llistLink* new_node);

// creates a new cursor to the left/right of the current one
Llist_Cursor make_cursor(enum Llist_dir dir, Llist_Cursor self);
//Checks if the cursor currently points to a valid node, if false it signals that the cursor
//is at the false node
int is_valid_pos(Llist_Cursor self, Llist* origin);
