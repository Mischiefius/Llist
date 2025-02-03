// All methods which are inline do not mutate the List
// Memory is managed by the caller, both allocation and freeing

// This struct never exists on its own, its always inside a super struct, defined by the user.
// The user should have a way to type-pun a pointer of this struct to a pointer to the super struct, which holds the data
typedef struct llistLink{
    struct llistLink * left;
    struct llistLink * right;
} llistLink;

// The struct that holds the ends of the list. It's fields should be considered
// private
typedef llistLink Llist;
//This is because the fields are actually swapped, l;eft points to the right and vici-versa
//It is done like this to make the cursor functionality posssible

inline Llist Llist_new(){ Llist new_list = { &new_list, &new_list }; return new_list; }

//The direction enum is used to control the direction of the various other functions.
enum Llist_dir {left, right};

//Pushes a new node onto either end of the list, controlled by dir
void llist_push(enum Llist_dir dir, Llist* self, llistLink* new_node);

//Returns the left/right most node and removes it from the list
llistLink* llist_pop(enum Llist_dir dir, Llist* self);

//Same as pop but does not remove the node from the list
inline llistLink* llist_peek(enum Llist_dir dir, Llist* self){
    return (dir==left) ? self->right : self->left;
}


//The Cursor is API is exactly like a text Cursor, it can iterate, delete, insert and splice (paste) efficiently.
//This is the type of cursor that lies on a node, and will wrap around if it reaches either end. See full behaviour below.
typedef llistLink* Llist_Cursor;
//When at the end it will point to a 'phantom node' to signify wrap-around. It does not contain any data.
//is_valid_pos(&cursor,&list) checks if the cursor points to a true node
//Multiple Cursors can co-exist, the node that the cursor is currently on must not be popped or freed

//Return a cursor to the righmost or leftmost element depending on the passed direction.
inline Llist_Cursor cursor_new(enum Llist_dir dir, Llist* list){ return list; }

inline void move_cursor(enum Llist_dir dir, Llist_Cursor* self){
    *self = (dir==left) ? (*self)->left : (*self)->right;
}

//deletes the CURRENT node, and moves either left or right depending on dir
llistLink* delete_move(enum Llist_dir dir, Llist_Cursor* self);

//Splices a given Llist either to the left or the right of the cursor, the cursor does not move
void cursor_splice(enum Llist_dir dir, Llist_Cursor self, Llist* new_list);
// creates a new cursor to the left/right of the current one
inline Llist_Cursor make_cursor(enum Llist_dir dir, Llist_Cursor self){
    return (dir==left) ? self->left : self->right;
}

inline int is_valid_pos(Llist_Cursor* self, Llist* origin) { return *self == origin; }
