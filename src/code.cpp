// ============================================================
// CSCI 232 Assignment 05 – Evolution of Data Structures
// Student Implementation
// ============================================================

#include "code.hpp"
#include <iostream>
#include <format>

// ============================================================
std::string AUTHOR_NAME = "Your Name";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this assignment independently, except where explicitly noted and referenced. Any collaboration or use of external resources has been properly cited. I am fully aware of the consequences of academic dishonesty and agree to abide by the university's academic integrity policy.";
// ============================================================

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// Converts a LegacyData union to a formatted string.
/// Format specs:
/// 'i' -> integer value as string (e.g., "42")
/// 'd' -> double value formatted to 2 decimal places (e.g., "3.14")
/// 'c' -> string pointer content (or "nullptr" if cPtr is null)
/// default -> "unknown"

std::string printLegacyData(LegacyData data, char type) {
    std::string result = "unknown";

    if (type == 'i')
    {
        result = std::format("{}", data.i);
    }
    if (type == 'c')
    {
        if (data.cPtr != NULL)
        {
            result = std::format("{}", data.cPtr);
        }
    }
    if (type == 'd')
    {
        result = std::format("{}", data.d);
    }
    return result;
}

// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// Initializes a structNode with value, type indicator, and nullptr nextPtr.
void initStructNode(structNode* nPtr, LegacyData val, char type) {
    nPtr->nextPtr = nullptr;
    nPtr->value = val;
    nPtr->typeData = type;
}

/// Dynamically allocates two structNodes.
/// Node 1: int 5 ('i')
/// Node 2: double 3.14 ('d')
/// Links Node 1 -> Node 2 -> nullptr
/// Returns pointer to Node 1.
structNode* createTwoStructNodes() {
    // TODO: Allocate dynamically using new, initialize both nodes, link them, and return head
    LegacyData val;
    val.i = 5;
    structNode *aPtr = new structNode;
    initStructNode(aPtr, val, 'i');
    val.d = 3.14;
    structNode *bPtr = new structNode;
    initStructNode(bPtr, val, 'd');
    aPtr->nextPtr = bPtr;
    return aPtr;
}

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// Constructor: Assign fields inside curly braces.
/// DO NOT use member initializer lists here!

// uncomment the following code to implement the classNode constructor

classNode::classNode(LegacyData val, char type) {
     // TODO: Assign value, typeData, and set nextPtr to nullptr
     if (type == 'i')
     {
        this->value.i = val.i;
        this->nextPtr = nullptr;
        this->typeData = type;
     }
     if (type == 'd')
     {
        this->value.d = val.d;
        this->nextPtr = nullptr;
        this->typeData = type;
     }
     if (type == 'cPtr')
     {
        this->value.cPtr = val.cPtr;
        this->nextPtr = nullptr;
        this->typeData = type;
     }
}

/// Dynamically allocates two classNodes (int 5, double 3.14) and links them.
classNode* createTwoClassNodes() {
    LegacyData val;
    val.i = 5;
    classNode* aPtr = new classNode(val, 'i');
    val.d = 3.14;
    classNode* bPtr = new classNode(val, 'd');
    aPtr->nextPtr = bPtr;
    return aPtr;
}

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// Dynamically allocates two classNodeT<int> objects (int 5, int 3) and links them.
classNodeT<int>* createTwoTemplateNodes() {
    // TODO: Instantiate classNodeT<int> nodes using new, link them, and return head
    classNodeT<int> *aPtr = new classNodeT(5);

    classNodeT<int> *bPtr = new classNodeT(3);

    aPtr->nextPtr = bPtr;
    return aPtr;
}

// ============================================================
// STAGE 4: C++17 Variant and LinkedList Manager
// ============================================================

// uncomment the following code to implement the LinkedList methods

LinkedList::LinkedList() {
    // TODO: Initialize headPtr to nullptr and counter to 0
    this->headPtr = nullptr;
    this->counter = 0;
}

LinkedList::~LinkedList() {
    // TODO: Clean up memory by calling destroyList()
    destroyList();
}
//uncoment the following code to implement the LinkedList methods

void LinkedList::destroyList() {
    // TODO: Iterate through list, delete all nodes, and reset counter to 0
    while (this->counter != 0)
    {
        deleteFirst();
    }
}

int LinkedList::addFirst(classNodeVariant* newNodePtr) {
    // TODO: Prepend node to the front of list, increment counter
    // Return -1 if newNodePtr is nullptr, 0 on success
    if (newNodePtr != nullptr)
    {
        newNodePtr->nextPtr = this->headPtr;
        this->headPtr = newNodePtr;
        this->counter += 1;
        return 0;
    }
    else
    {
        return -1;
    }
}

 int LinkedList::addLast(classNodeVariant* newNodePtr) {
    // TODO: Append node to the end of list, increment counter
    // Return -1 if newNodePtr is nullptr, 0 on success
    if (newNodePtr != nullptr)
    {
        if (this->headPtr == nullptr)
        {
            this->headPtr = newNodePtr;
            this->counter += 1;
            return 0;
        }
        classNodeVariant* currentPtr = this->headPtr;
        while (currentPtr->nextPtr != nullptr)
        {
            currentPtr = currentPtr->nextPtr;
        }
        currentPtr->nextPtr = newNodePtr;
        this->counter += 1;
        return 0;
    }
    else
    {
        return -1;
    }
}

 int LinkedList::deleteFirst() {
    // TODO: Delete first node, update headPtr, decrement counter
    // Return -1 if list is empty, 0 on success
    if (this->headPtr->nextPtr != nullptr)
    {
        classNodeVariant *firstPtr = this->headPtr->nextPtr;
        this->headPtr->nextPtr = this->headPtr->nextPtr->nextPtr;
        free(firstPtr);
        //firstPtr->nextPtr = nullptr;
        this->counter -= 1;
        return 0;
    }
    else
    {
        this->counter = 0;
        return -1;
    }
}

 int LinkedList::deleteLast() {
    // TODO: Find second-to-last node, delete last node, decrement counter
    // Return -1 if list is empty, 0 on success
    classNodeVariant* currentPtr = this->headPtr;
    if (this->headPtr->nextPtr != nullptr)
    {
        while (currentPtr->nextPtr->nextPtr != nullptr)
        {
            currentPtr = currentPtr->nextPtr;
        }
        classNodeVariant* lastPtr = currentPtr->nextPtr;
        currentPtr->nextPtr = nullptr;
        free(lastPtr);
        this->counter -= 1;
        return 0;
    }
    else
    {
        return -1;
    }
}

int LinkedList::deleteValue(ModernData targetValue) {
    // TODO: Traverse list, find node matching targetValue, unlink and delete it
    // Decrement counter
    // Return 0 if found and removed, -1 if not found or list is empty
    classNodeVariant* currentPtr = this->headPtr;
    if (this->headPtr->nextPtr != nullptr)
    {
        while (currentPtr->nextPtr->nextPtr != nullptr)
        {
            if (currentPtr->nextPtr->value == targetValue)
            {
                classNodeVariant* valuePtr = currentPtr->nextPtr;
                currentPtr->nextPtr = currentPtr->nextPtr->nextPtr;
                free(valuePtr);
                this->counter -= 1;
                return 0;
            }
            currentPtr = currentPtr->nextPtr;
        }
    }
    return -1;
}

int LinkedList::printList() {
    // TODO: Iterate through list and print each variant value to std::cout
    // Use std::holds_alternative or std::get
    // Return -1 if list is empty, 0 on success
    classNodeVariant* currentPtr = this->headPtr;
    if (this->headPtr->nextPtr != nullptr)
    {
        while (currentPtr != nullptr)
        {
            std::variant<int, double, std::string> myVariant;
            myVariant = currentPtr->value;

            if (holds_alternative<int>(myVariant)) {
                std::cout << get<int>(myVariant) << std::endl;
            } // print for int

            if (holds_alternative<double>(myVariant)) {
                std::cout << get<double>(myVariant) << std::endl;
            } // print for double

            if (holds_alternative<std::string>(myVariant)) {
                std::cout << std::endl << get<std::string>(myVariant) << std::endl;
            } // print for string

            currentPtr = currentPtr->nextPtr;

        }
        return 0;
    }
    else
    {
        return -1;
    }
}

int LinkedList::listLength() {
    // TODO: Return node count
    return this->counter;
}