#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){ 
    clear();
}

/** //helper for copy
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
    /*your code here*/
    Node* listingNode = new Node(Block(ndata));
    Node* handling = tail_ -> prev;
    handling -> next = listingNode;
    tail_ -> prev = listingNode;
    listingNode -> prev = handling;
    listingNode -> next = tail_;
    length_ ++;
    handling = NULL;
    listingNode = NULL;
}

/**
 * Modifies the Chain by moving a contiguous subset of len Nodes
 * dist nodes toward the end of the chain beginning from startPos
 * (maintaining the sentinel at the end). Their order is
 * not changed in the move. You may assume that the startPos and
 * len parameters are kind: startPos + len -1 <= length. If there
 * are not enough nodes to shift by dist, just shift as many as
 * possible.
 */
void Chain::moveBack(int startPos, int len, int dist){
    /*your code here*/
    if (dist != 0) {
        if(startPos + len + dist > size()) {
            dist = size() - (startPos + len) + 1;
        }

        Node* nex = head_;
        for (int i = 0; i < startPos; i++) {
            nex = nex -> next;
        }

        Node* previ = nex;
        for (int i = 1; i < len; i++) {
            previ = previ -> next;
        }

        Node* handling = previ;
        for (int i = 0; i < dist; i++) {
            handling = handling -> next;
        }

        nex -> prev -> next = previ -> next;
        previ -> next -> prev = nex -> prev;
        handling -> next -> prev = previ;
        previ -> next = handling -> next;
        nex -> prev = handling;
        handling -> next = nex;
        
        nex = NULL;
        previ = NULL;
        handling = NULL;
    }
}

/**
 * Rolls the current Chain by k nodes: removes the last
 * k nodes from the Chain and attaches them, in order, at
 * the start of the chain (maintaining the sentinel at the front).
 */
void Chain::roll(int k){
    /*your code here*/
    Node* handling;
    for (int i = 0; i < k; i++) {
        handling = tail_ -> prev;
        handling -> prev -> next = tail_;
        tail_ -> prev = handling -> prev;
        head_ -> next -> prev = handling;
        handling -> next = head_ -> next;
        handling -> prev = head_;
        head_ -> next = handling;
    }
    handling = NULL;
}

/**
 * Modifies the current chain by reversing the subchain
 * between pos1 and pos2, inclusive. The positions are
 * 1-based. You may assume that pos1 and pos2 are valid
 * locations in the Chain, and that pos2 >= pos1.
 */
void Chain::reverseSub(int pos1, int pos2){
    /*your code here */
    int lim = ceil ((pos2 - pos1 + 2)/2);

    Node* position1 = head_;
    for(int i = 0; i < pos1; i++) {
        position1 = position1 -> next;
    }

    Node* position2 = tail_;
    for(int i = 0; i < size() - pos2 + 1; i++) {
        position2 = position2 -> prev;
    }

    for (int i = 0; i < lim; i++) {
        if (position1->next != position2) {
            position1 -> prev -> next = position2;
            position2 -> next -> prev = position1;
            position1 -> next -> prev = position2;
            position2 -> prev -> next = position1;

            Node* p1prev = position1 -> prev;
            Node* p1next = position1 -> next;
            Node* p2prev = position2 -> prev;

            position1 -> next = position2 -> next;
            position1 -> prev = position2 -> prev;
            position2 -> prev = p1prev;
            position2 -> next = p1next;
            position1 = p1next;
            position2 = p2prev;

            p1next = NULL;
            p1prev = NULL;
            p2prev = NULL;
        }
        else {
            position1 -> prev -> next = position2;
            position2 -> next -> prev = position1;
            position2 -> prev = position1 -> prev;
            position1 -> next = position2 -> next;
            position1 -> prev = position2;
            position2 -> next = position1;
            position1 = NULL;
            position2 = NULL;
        }
    }

}

/*
* Modifies both the current and input chains by removing
* nodes from other, and interleaving them between the Nodes
* from the current Chain. The nodes from the other Chain
* should occupy the even locations in the result. length
* of the resulting chain should be the sums of the lengths
* of current and the other. The other chain should have only
* two sentinels and no data nodes at the end of the operation.
* the weave fails and the original chains should be unchanged if block sizes are different.
* in that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
    /*your code here */
    if (width_ != other.width_ ) { //if this.size() != other.size()
        cout << "Block size differ." << endl;
    }
    else if(other.size() <= size()) {
        Node* h1 = head_ -> next;
        Node* h2 = head_ -> next -> next;
        Node* oh1 = other.head_ -> next;
        Node* oh2 = other.head_ -> next -> next;
        bool check = false;
        int sizing = other.size();
        for (int i = 0; i < other.size(); i++){ // (size-1) because of the index
            h1 -> next -> prev = oh1;
            oh1 -> prev = h1;
            oh1 -> next = h1 -> next;
            h1 -> next = oh1;
            h1 = h2;
            oh1 = oh2;
            h2 = h2 -> next;
            oh2 = oh2 -> next;
        }
        other.head_ -> next = other.tail_;
        other.tail_ -> prev = other.head_;
        length_ = length_ + other.length_;
        other.length_ = 0;
        h1 = NULL;
        h2 = NULL;
        oh1 = NULL;
        oh2 = NULL;
    }
    else {
        Node* h1 = head_ -> next;
        Node* h2 = head_ -> next -> next;
        Node* oh1 = other.head_ -> next;
        Node* oh2 = other.head_ -> next -> next;
        for (int i = 0; i < size() - 1; i++) {
            h1 -> next -> prev = oh1;
            oh1 -> prev = h1;
            oh1 -> next = h1 -> next;
            h1 -> next = oh1;
            h1 = h2;
            oh1 = oh2;
            h2 = h2 -> next;
            oh2 = oh2 -> next;
        }
        oh2 = other.tail_ -> prev;
        h1 -> next = oh1;
        oh1 -> prev = h1;
        oh2 -> next = tail_;
        h2 -> prev = oh2;

        other.head_ -> next = other.tail_;
        other.tail_ -> prev = other.head_;
        length_ = length_ + other.length_;
        other.length_ = 0;
        h1 = NULL;
        h2 = NULL;
        oh1 = NULL;
        oh2 = NULL;
    }
}

/** //helper for ~clear
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear() {
    /*your code here*/
    if (head_ != NULL) {
        for (int i = 0; i < size(); i++) {
            delete walk(head_, size() - i);
        }
    }

    delete head_;
    head_ = NULL;

    if (tail_ != NULL) {
        delete tail_;
        tail_ = NULL;
    }
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */

void Chain::copy(Chain const& other) {
    /*your code here*/
    width_ = other.width_;
    height_ = other.height_;
    head_ = new Node();
    tail_ = new Node();
    head_ -> next = tail_;
    tail_ -> prev = head_;
    length_ = 0;
    Node* current = other.head_;
    while (current -> next != other.tail_) {
        Node* tailing = new Node(current -> next -> data);
        tail_ -> prev -> next = tailing;
        tailing -> prev = tail_ -> prev;
        tail_ -> prev = tailing;
        tailing -> next = tail_;
        current = current -> next;
        length_++;
    }
    // while (current -> next != other.tail_) {
    //     insertBack(current -> next -> data);
    //     current = current -> next;
    // }
}