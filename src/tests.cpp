#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <sstream>
#include <iostream>

// ============================================================
// STAGE 0 Tests
// ============================================================

/// Create a LegacyData union with an int (42). Call printLegacyData.
/// Verify the returned string matches "42".
void test_printLegacyData_int(void) 
{
    LegacyData val;
    val.i = 42;
    std::string returnedString = printLegacyData(val, 'i');
    std::string check = "42";
    TEST_ASSERT_EQUAL_STRING(check.c_str(), returnedString.c_str());
}

/// Create a LegacyData union with a double (3.14). Call printLegacyData.
/// Verify the returned string matches "3.14".
void test_printLegacyData_double(void) 
{
    LegacyData val;
    val.d = 3.14;
    std::string returnedString = printLegacyData(val, 'd');
    std::string check = "3.14";
    TEST_ASSERT_EQUAL_STRING(check.c_str(), returnedString.c_str());
}

// ============================================================
// STAGE 1 Tests
// ============================================================

/// Call createTwoStructNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoStructNodes_links_correctly(void) 
{
    structNode *nodeHead = createTwoStructNodes();

    TEST_ASSERT_EQUAL(5, nodeHead->value.i);
    TEST_ASSERT_EQUAL('i', nodeHead->typeData);
    TEST_ASSERT_EQUAL(3.14,nodeHead->nextPtr->value.d);
    TEST_ASSERT_EQUAL('d', nodeHead->nextPtr->typeData);
}

// ============================================================
// STAGE 2 Tests
// ============================================================

/// Call createTwoClassNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoClassNodes_links_correctly(void) 
{
    classNode *nodeHead = createTwoClassNodes();

    TEST_ASSERT_EQUAL(5, nodeHead->value.i);
    TEST_ASSERT_EQUAL('i', nodeHead->typeData);
    TEST_ASSERT_EQUAL(3.14,nodeHead->nextPtr->value.d);
    TEST_ASSERT_EQUAL('d', nodeHead->nextPtr->typeData);
}

// ============================================================
// STAGE 3 Tests
// ============================================================

/// Call createTwoTemplateNodes().
/// Verify head->value is 5 and head->nextPtr->value is 3.
/// Clean up allocated memory.
void test_createTwoTemplateNodes_links_correctly(void) 
{
    classNodeT headPtr = createTwoTemplateNodes();

    TEST_ASSERT_EQUAL(5, headPtr.value->value);
    TEST_ASSERT_EQUAL(3, headPtr.value->nextPtr->value);
}

// ============================================================
// STAGE 4: LinkedList Tests
// ============================================================

/// Create a LinkedList. Add two nodes using addFirst.
/// Verify listLength() returns 2 after insertions.
void test_linkedList_addFirst_updates_counter(void) 
{
    // used geeks for geeks as a reference to better understand variants

    std::variant<int, double, std::string> var1;
    var1 = 5;

    std::variant<int, double, std::string> var2;
    var2 = 4;

    LinkedList *headPtr = new LinkedList();
    classNodeVariant *nodeA = new classNodeVariant(var1);
    classNodeVariant *nodeB = new classNodeVariant(var2);


    headPtr->addFirst(nodeA);
    headPtr->addFirst(nodeB);
    int result = headPtr->listLength();
    TEST_ASSERT_EQUAL(2, result);
}

/// Create a LinkedList. Add nodes (10, then 20) using addLast.
/// Capture std::cout and verify elements appear in order ("10" before "20").
void test_linkedList_addLast_places_at_end(void) 
{
    LinkedList *headPtr = new LinkedList();

    std::variant<int, double, std::string> var1;
    var1 = 10;

    std::variant<int, double, std::string> var2;
    var2 = 20;

    classNodeVariant *nodeA = new classNodeVariant(var1);
    classNodeVariant *nodeB = new classNodeVariant(var2);
    
    headPtr->addLast(nodeA);
    headPtr->addLast(nodeB);

    // referenced streambuf and stringstream
    std::streambuf* buffer = std::cout.rdbuf();

    std::stringstream stream;

    std::cout.rdbuf(stream.rdbuf()); // sets cout buffer to stream
    headPtr->printList();

    std::string streamOutput = stream.str();

    std::cout.rdbuf(buffer); // restores cout buffer to normal

    std::string word;

    std::string subS = "10\n20\n";

    // use find function instead for one that actually makes sense and can actually check

    bool result = false;
    if (streamOutput == subS)
    {
        result = true;
    }
    TEST_ASSERT_EQUAL(true, result);
}

/// Create a LinkedList with an int, double, and string.
/// Call deleteValue() with the double value (3.14).
/// Verify list length decreases to 2 and second call returns -1.
void test_linkedList_deleteValue_removes_variant(void) 
{
    LinkedList *headPtr = new LinkedList();

    std::variant<int, double, std::string> var1;
    var1 = 10;

    std::variant<int, double, std::string> var2;
    var2 = 3.14;

    std::variant<int, double, std::string> var3;
    var3 = "hello world";

    classNodeVariant *nodeA = new classNodeVariant(var1);
    classNodeVariant *nodeB = new classNodeVariant(var2);
    classNodeVariant *nodeC = new classNodeVariant(var3);
    
    headPtr->addLast(nodeA);
    headPtr->addLast(nodeB);
    headPtr->addLast(nodeC);

    headPtr->deleteValue(var2);

    int listLength = headPtr->listLength();

    TEST_ASSERT_EQUAL(2, listLength);
    TEST_ASSERT_EQUAL(-1, headPtr->deleteValue(var2));

}
/// Create a LinkedList and insert three nodes.
/// Call destroyList().
/// Verify listLength() becomes 0.
void test_linkedList_destroyList_clears_all(void) 
{
    LinkedList *headPtr = new LinkedList();

    std::variant<int, double, std::string> var1;
    var1 = 10;

    std::variant<int, double, std::string> var2;
    var2 = 3.14;

    std::variant<int, double, std::string> var3;
    var3 = "hello world";

    classNodeVariant *nodeA = new classNodeVariant(var1);
    classNodeVariant *nodeB = new classNodeVariant(var2);
    classNodeVariant *nodeC = new classNodeVariant(var3);
    
    headPtr->addLast(nodeA);
    headPtr->addLast(nodeB);
    headPtr->addLast(nodeC);

    headPtr->destroyList();

    TEST_ASSERT_EQUAL(0, headPtr->listLength());
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteFirst().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteFirst(void) 
{
    LinkedList *headPtr = new LinkedList();

    std::variant<int, double, std::string> var1;
    var1 = 10;

    std::variant<int, double, std::string> var2;
    var2 = 20;

    std::variant<int, double, std::string> var3;
    var3 = 30;

    classNodeVariant *nodeA = new classNodeVariant(var1);
    classNodeVariant *nodeB = new classNodeVariant(var2);
    classNodeVariant *nodeC = new classNodeVariant(var3);
    
    headPtr->addFirst(nodeA);
    headPtr->addFirst(nodeB);
    headPtr->addFirst(nodeC);

    int result = headPtr->deleteFirst();
    int lisLength = headPtr->listLength();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(2, lisLength);
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteLast().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteLast(void) 
{
    LinkedList *headPtr = new LinkedList();

    std::variant<int, double, std::string> var1;
    var1 = 10;

    std::variant<int, double, std::string> var2;
    var2 = 20;

    std::variant<int, double, std::string> var3;
    var3 = 30;

    classNodeVariant *nodeA = new classNodeVariant(var1);
    classNodeVariant *nodeB = new classNodeVariant(var2);
    classNodeVariant *nodeC = new classNodeVariant(var3);
    
    headPtr->addFirst(nodeA);
    headPtr->addFirst(nodeB);
    headPtr->addFirst(nodeC);

    int result = headPtr->deleteLast();
    int lisLength = headPtr->listLength();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(2, lisLength);
}

/// Create a LinkedList with nodes (1, 2.5, "test").
/// Redirect std::cout buffer and call printList().
/// Verify printed output contains "1", "2.5" (or "2.50"), and "test".
void test_linkedList_printList(void) 
{
    LinkedList *headPtr = new LinkedList();

    std::variant<int, double, std::string> var1;
    var1 = 1;

    std::variant<int, double, std::string> var2;
    var2 = 2.5;

    std::variant<int, double, std::string> var3;
    var3 = "test";

    classNodeVariant *nodeA = new classNodeVariant(var1);
    classNodeVariant *nodeB = new classNodeVariant(var2);
    classNodeVariant *nodeC = new classNodeVariant(var3);
    
    headPtr->addFirst(nodeA);
    headPtr->addFirst(nodeB);
    headPtr->addFirst(nodeC);
}