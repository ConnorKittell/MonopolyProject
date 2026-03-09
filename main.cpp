#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static const int MAX_SPACES = 40;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    MonopolySpace() {
        // TODO: define default constructor (recommended)
        propertyName = "";
        propertyColor = "";
        value = 0;
        rent = 0;
    }

    MonopolySpace(string propertyName, string propertyColor, int value, int rent):
        propertyName(propertyName), propertyColor(propertyColor), value(value), rent(rent) {}

    bool isEqual(MonopolySpace other) {
        if (other.propertyName==propertyName && other.propertyColor==propertyColor
            && other.value==value && other.rent==rent) {return true;}
        return false;
    }

    void print() {
        cout << propertyName << " | " << propertyColor << " | $" << value << " | Rent " << rent << endl;
    }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
    T data;
    Node<T>* nextNode;

    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
    Node<T>* headNode;
    Node<T>* tailNode;

    // player cursor for traversal-based gameplay
    Node<T>* playerNode;

    int nodeCount;
    int passGoCount;

public:
    CircularLinkedList() {
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }

    // -------------------------------
    // Board Construction Policy (Reminder)
    // -------------------------------
    // Spaces are added during board construction BEFORE gameplay.
    // You choose how to construct the board:
    // - hardcode spaces, read from file, or generate programmatically
    // The only non-negotiable requirement:
    // - enforce MAX_SPACES
    // - maintain circular integrity
    // -------------------------------

    // -------------------------------
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
    bool addSpace(T value) {
        // TODO:
        // - If nodeCount == MAX_SPACES return false (do not corrupt list)
        // - Create new node
        // - If empty list: head=tail=player=new, new->next=head
        // - Else: tail->next=new, tail=new, tail->next=head
        // - nodeCount++
        if (nodeCount==MAX_SPACES){return false;}
        Node<T>* newNode = new Node<T>(value);
        if (nodeCount==0) {
            headNode = newNode;
            tailNode = newNode;
            tailNode->nextNode = headNode;
            playerNode=newNode;
        }
        else {
            tailNode->nextNode = newNode;
            tailNode = newNode;
            tailNode->nextNode = headNode;
        }
        nodeCount++;
        return true;
    }

    // -------------------------------
    // Core B: Add Multiple Spaces at Once
    // -------------------------------
    int addMany(vector<T> values) {
        // TODO:
        // - Add sequentially until full
        // - Stop exactly when you reach MAX_SPACES
        // - Return number successfully added
        // - Do not corrupt pointers if capacity is exceeded
        int count=0;
        while (count<values.size()&&nodeCount<MAX_SPACES) {
            addSpace(values[count]);
            count++;
        }
        return count;
    }

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    void movePlayer(int steps) {
        // TODO:
        // - Move playerNode forward 'steps' times, node-by-node
        // - Wrap naturally because list is circular
        // - Detect and track passing GO:
        //   increment passGoCount when a move crosses from tail back to head
        // - Must handle empty list safely
        if (nodeCount==0)
            return;
        for (int i=0; i<steps; i++) {
            if (playerNode->nextNode == headNode)
                passGoCount++;
            playerNode = playerNode->nextNode;
        }
    }

    int getPassGoCount() {
        return passGoCount;
    }

    // -------------------------------
    // Core D: Controlled Board Display
    // -------------------------------
    void printFromPlayer(int count) {
        // TODO:
        // - Print exactly 'count' nodes starting from playerNode
        // - Must not infinite loop
        // - Must handle empty list
        // - Output must be deterministic and readable
        if (nodeCount==0) {
            cout<<"Board empty :("<<endl;
        }
        Node<T>* temp = playerNode;
        for (int i=0; i<count; i++) {
            temp->data.print();
            temp = temp->nextNode;
        }

        cout << "printFromPlayer unwritten" << endl;
    }

    // Optional helper: print full board once (one full cycle)
    void printBoardOnce() {
        // TODO:
        // - Traverse exactly one full cycle and print each node
        if (nodeCount==0)
            cout<<"Board DNE"<<endl;
        Node<T>* temp = headNode;
        for (int i=0; i<nodeCount; i++) {
            temp->data.print();
            temp = temp->nextNode;
        }
    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    bool removeByName(string name) {
        // TODO:
        // - Delete FIRST matching node
        // - Must handle:
        //   - deleting head
        //   - deleting tail
        //   - deleting the only-node list
        // - Maintain circular link tail->next=head
        // - If playerNode points to deleted node, move playerNode to a safe node
        // - nodeCount--
        cout << "removeByName unwritten" << endl;
        return false;
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(string color) {
        // TODO:
        // - Traverse ring exactly once
        // - Collect matching names in vector<string>
        // - Return matches
        cout << "findByColor unwritten" << endl;
        vector<string> matches;
        return matches;
    }

    // -------------------------------
    // Advanced Option B (Level 2): Mirror the Board (Circular Reversal)
    // -------------------------------
    void mirrorBoard() {
        // TODO:
        // - Reverse the direction of the circular list by reversing next pointers
        // - Preserve circular structure
        // - Correctly handle empty list and single-node list
        // - Player cursor must remain on the same logical space after reversal

        //cannot reverse an empty or single node
        if (nodeCount<=1)
            return;

        //Main reversal section
        Node<T>* prevNode = headNode;
        Node<T>* currentNode = prevNode->nextNode;
        Node<T>* futureNode = currentNode->nextNode;
        for (int i=0; i<nodeCount; i++) {
            currentNode->nextNode = prevNode;
            prevNode = currentNode;
            currentNode = futureNode;
            futureNode = futureNode->nextNode;
        }

        //flips the head and tail
        Node<T>* temp = headNode;
        headNode = tailNode;
        tailNode = temp;
    }

    // -------------------------------
    // Edge-case helper: countSpaces O(n)
    // -------------------------------
    int countSpaces() {
        // TODO:
        // - Must be O(n), traverse exactly once with correct stop condition
        // - Do NOT rely on nodeCount for this method
        if (headNode==nullptr)
            return 0;
        Node<T>* temp = headNode;
        int count = 1;
        while (temp->nextNode!=headNode) {
            count++;
            temp=temp->nextNode;
        }
        return count;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        // TODO:
        // - Safely delete all nodes
        // - Tip: if tailNode exists, break the cycle first: tailNode->nextNode = nullptr
        // - Then delete like a normal singly linked list
        tailNode->nextNode = nullptr;
        Node<T> *temp = headNode;
        while (headNode) {
            headNode = headNode->nextNode;
            delete temp;
            temp = headNode;
        }
    }
};

// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    CircularLinkedList<MonopolySpace> board;

    cout<<board.countSpaces()<<endl;

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    // You decide how to build the board:
    // - hardcode spaces, load from file, or generate spaces programmatically
    // The only requirement: never exceed MAX_SPACES and keep the list circular.
    //
    // Example (hardcoded) usage:
    // vector<MonopolySpace> spaces;
    // spaces.push_back(MonopolySpace("GO","None",0,0));
    // ...
    // board.addMany(spaces);
    //
    // NOTE: This starter calls addSpace once to show the intended API,
    // but your final submission should build a meaningful board.
    board.addSpace(MonopolySpace("GO", "None", 0, 0));
    board.addSpace(MonopolySpace("Baltic Avenue", "Brown", 60, 4));
    board.addSpace(MonopolySpace("St. James Place", "Orange", 180, 16));
    board.addSpace(MonopolySpace("B. & O. Railroad", "Railroad", 200, 25));
    board.addSpace(MonopolySpace("Boardwalk", "Blue", 400, 50));
    vector<MonopolySpace> spaces = {
        MonopolySpace("Oriental Avenue", "Light Blue", 120, 6),
        MonopolySpace("Jail", "None", 0, 0),
        MonopolySpace("Ventnor Place", "Yellow", 280, 28)
    };
    vector<MonopolySpace> spaces1={};
    cout<<board.addMany(spaces1)<<endl;
    cout<<board.addMany(spaces)<<endl;
    cout<<board.countSpaces()<<endl;

    board.printBoardOnce();

    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }

    // -------------------------------
    // Advanced Feature Demos (students choose path)
    // -------------------------------
    // Option A examples:
    // board.removeByName("Baltic Avenue");
    // vector<string> brownProps = board.findByColor("Brown");
    //
    // Option B example:
    cout << "\nPre-mirror board;"<<endl;
    board.printBoardOnce();
    board.mirrorBoard();
    cout << "\nMirror board:" << endl;
    board.printBoardOnce();

    board.clear();
    return 0;
}