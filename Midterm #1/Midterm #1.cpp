// COMSC-210 | Midterm #1 | Jayson Yang
// IDE used: Visual Studio 
#include <iostream>
using namespace std;// This allows us to avoid typing std:: before functions like cout.
// constants for later use in the main function
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
// Our class for the doubly linked list
class DoublyLinkedList {
private:
    struct Node {
        int data; // This holds the value for each node
        Node* prev; // Pointer to the previous node in the list
        Node* next;// Pointer to the next node in the list
        // Constructor to make a new node. If there is no prev/next, it will defaults to nullptr
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head;// Pointer to the first node
    Node* tail;// Pointer to the last node

public:
    // Initializes an empty list
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // When there's no list, head is null and tail is null when the list is empty
    // Inserts a new node after a certain position
    void insert_after(int value, int position) {
        // Check if position is correct (greater than or equal to 0)
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);// Creates a new node with the certain value

        if (!head) {
            head = tail = newNode; // If the list is empty, make this the first node
            return;
        }
        // Move temp to the position where the new node will be
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        // If the position is not within the values then the node will not be inserted
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        // Change pointers to insert newNode after the temp
        newNode->next = temp->next;
        newNode->prev = temp;
        // If there's a node after temp, link its prev to newNode
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;// If temp was the last node it will update tail
        temp->next = newNode;// Put temp next to newNode
    }

    // Delete the first node with a specific value
    void delete_val(int value) {
        if (!head) return;  // If thre is no list, nothing to delete

        Node* temp = head;

        // Find the node with the value
        while (temp && temp->data != value)
            temp = temp->next;

        // If no node with the value is found, return
        if (!temp) return;

        // Adjust pointers to seperate the nodes
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;  // If temp was the head, then it will update

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;  // If temp was the tail, update tail

        delete temp;  // Free the memory of the node
    }

    // Used to delete a node by its position
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();  // If position is 1, just remove the head
            return;
        }

        Node* temp = head;

        // Move to the node at the specified position
        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }

        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        // If it's the last node, just pop the back
        if (!temp->next) {
            pop_back();
            return;
        }

        // Adjust the pointers to unlink temp
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // Add a new node at the end of the list
    void push_back(int v) {
        Node* newNode = new Node(v);

        if (!tail)
            head = tail = newNode;  // If the list is empty, newNode is both head and tail
        else {
            tail->next = newNode;   // Link the current tail to newNode
            newNode->prev = tail;   // Link newNode's prev to the old tail
            tail = newNode;         // Update tail to newNode
        }
    }


    void push_front(int v) {
        Node* newNode = new Node(v);

        if (!head)
            head = tail = newNode;  
        else {
            newNode->next = head;   
            head->prev = newNode;   
            head = newNode;        
        }
    }

    void pop_front() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;

        if (head->next) {
            head = head->next;      
            head->prev = nullptr;  
        }
        else
            head = tail = nullptr;  

        delete temp;  // Free memory
    }

    
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = tail;

        if (tail->prev) {
            tail = tail->prev;      
            tail->next = nullptr;   
        }
        else
            head = tail = nullptr;  

        delete temp;  // Free memory
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;  
        }
    }

    void print() {
        Node* current = head;

        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        while (current) {
            cout << current->data << " ";  
            current = current->next;      
        }

        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;

        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        while (current) {
            cout << current->data << " ";  
            current = current->prev;       
        }

        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning


    return 0;
}