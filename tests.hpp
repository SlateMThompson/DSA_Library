#include "DataStructures.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// ANSI color codes for better display
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define UNDER   "\033[4m"

void printDivider(const std::string& title) {
    std::cout << BOLD << BLUE << "\n==================== " << title << " ====================\n" << RESET;
}

void printSubDivider(const std::string& subtitle) {
    std::cout << YELLOW << "\n--- " << subtitle << " ---\n" << RESET;
}

void printSuccess(const std::string& msg) {
    std::cout << GREEN << "[PASS] " << msg << RESET << std::endl;
}

void printFail(const std::string& msg) {
    std::cout << RED << "[FAIL] " << msg << RESET << std::endl;
}

void uniNodeTests(){
    printDivider("UniNode Tests");
    std::cout << CYAN << "Testing UniNode basic functionality: construction, linking, value setting, and unlinking.\n" << RESET;
    std::cout << BOLD << "[INIT] " << RESET << "Creating UniNode<int> n1(42).\n";
    UniNode<int> n1(42);
    std::cout << "[RESULT] Initial value (should be 42): " << n1.getValue() << std::endl;
    std::cout << BOLD << "[TEST] " << RESET << "Creating UniNode<int> n2(99) and linking as next of n1.\n";
    UniNode<int> n2(99);
    n1.setNext(&n2);
    std::cout << "[RESULT] n1.getNext()->getValue() (should be 99): " << n1.getNext()->getValue() << std::endl;
    std::cout << BOLD << "[TEST] " << RESET << "Updating n1's value to 123.\n";
    n1.setValue(123);
    std::cout << "[RESULT] n1.getValue() (should be 123): " << n1.getValue() << std::endl;
    std::cout << BOLD << "[TEST] " << RESET << "Unlinking n1.\n";
    n1.unlink();
    std::cout << "[RESULT] After unlink, n1.getNext() (should be nullptr): " << (n1.getNext() == nullptr ? "nullptr" : "not null") << std::endl;
    std::cout << BOLD << "[TEST] " << RESET << "Testing setNext(nullptr)...\n";
    n1.setNext(nullptr);
    if(n1.getNext() == nullptr) printSuccess("setNext(nullptr) sets next to nullptr as expected");
    else printFail("setNext(nullptr) did not set next to nullptr");
    std::cout << BOLD << GREEN << "\n[UniNode Tests Complete]\n" << RESET;
}

void biNodeTests(){
    printDivider("BiNode Tests");
    std::cout << CYAN << "Testing BiNode construction, linking, value setting, and unlinking.\n" << RESET;
    std::cout << BOLD << "[INIT] " << RESET << "Creating BiNode<int> n1(1), n2(2).\n";
    BiNode<int> n1(1);
    BiNode<int> n2(2);
    std::cout << BOLD << "[TEST] " << RESET << "Linking n1.next = n2, n2.prev = n1.\n";
    n1.setNext(&n2);
    n2.setPrev(&n1);
    std::cout << "[RESULT] n1 Value (should be 1): " << n1.getValue() << ", n2 Value (should be 2): " << n2.getValue() << std::endl;
    std::cout << "[RESULT] n1 Next is n2? " << (n1.getNext() == &n2 ? "ok" : "fail") << ", n2 Prev is n1? " << (n2.getPrev() == &n1 ? "ok" : "fail") << std::endl;
    std::cout << BOLD << "[TEST] " << RESET << "Updating n1's value to 10.\n";
    n1.setValue(10);
    std::cout << "[RESULT] n1.getValue() (should be 10): " << n1.getValue() << std::endl;
    std::cout << BOLD << "[TEST] " << RESET << "Unlinking n1.\n";
    n1.unlink();
    std::cout << "[RESULT] After unlink, n1.getNext() (should be nullptr): " << (n1.getNext() == nullptr ? "nullptr" : "not null") << ", n1.getPrev() (should be nullptr): " << (n1.getPrev() == nullptr ? "nullptr" : "not null") << std::endl;
    std::cout << BOLD << "[TEST] " << RESET << "Testing setPrev(nullptr)...\n";
    n2.setPrev(nullptr);
    if(n2.getPrev() == nullptr) printSuccess("setPrev(nullptr) sets prev to nullptr as expected");
    else printFail("setPrev(nullptr) did not set prev to nullptr");
    std::cout << BOLD << GREEN << "\n[BiNode Tests Complete]\n" << RESET;
}

void linkListTests(){
    printDivider("LinkList Tests");
    std::cout << CYAN << "Testing LinkList construction, insertion, removal, appending, moving, and error handling.\n" << RESET;
    std::cout << BOLD << "[INIT] " << RESET << "Creating empty LinkList<int> list1.\n";
    LinkList<int> list1;
    printSubDivider("Empty list");
    std::cout << "[INFO] Printing an empty list (should say 'List is empty.'):\n";
    list1.printList();
    printSubDivider("List of length 5 (default values)");
    std::cout << BOLD << "[INIT] " << RESET << "Creating LinkList<int> list2(5).\n";
    LinkList<int> list2(5);
    std::cout << "[INFO] Printing list2 (should have 5 default-initialized values):\n";
    list2.printList();
    int arr[] = {10, 20, 30, 40, 50};
    printSubDivider("List from array");
    std::cout << BOLD << "[INIT] " << RESET << "Creating LinkList<int> list3(arr, 5).\n";
    LinkList<int> list3(arr, 5);
    std::cout << "[INFO] Printing list3 (should show 10, 20, 30, 40, 50):\n";
    list3.printList();
    printSubDivider("Insert 99 at index 2");
    std::cout << BOLD << "[TEST] " << RESET << "Inserting 99 at index 2.\n";
    UniNode<int>* newNode = new UniNode<int>(99);
    list3.insertNode(newNode, 2);
    list3.printList();
    printSubDivider("Remove node at index 3 (should be 30)");
    std::cout << BOLD << "[TEST] " << RESET << "Removing node at index 3 (should remove 30):\n";
    UniNode<int>* removed = list3.removeNode(3);
    std::cout << "[RESULT] Removed value: " << removed->getValue() << " (Expected: 30)" << std::endl;
    // Only delete if it's the node we created with new
    if (removed == newNode) {
        delete removed;
    }
    list3.printList();
    printSubDivider("Append 77 to end");
    std::cout << BOLD << "[TEST] " << RESET << "Appending 77 to the end of the list.\n";
    UniNode<int>* appendNode = new UniNode<int>(77);
    list3 += appendNode;
    list3.printList();
    printSubDivider("Value at index 1");
    std::cout << BOLD << "[TEST] " << RESET << "Getting value at index 1 (should be 20): ";
    std::cout << list3.getValueAt(1) << std::endl;
    printSubDivider("Move node at index 0 to index 3");
    std::cout << BOLD << "[TEST] " << RESET << "Moving node at index 0 to index 3.\n";
    list3.moveNode(0, 3);
    list3.printList();
    printSubDivider("Remove from empty list");
    std::cout << BOLD << "[EDGE] " << RESET << "Trying to remove from an empty list (should throw an exception):\n";
    try {
        list1.removeNode(0);
        printFail("removeNode(0) on empty list should throw");
    } catch(const std::exception&) { printSuccess("removeNode(0) on empty list throws as expected"); }
    std::cout << BOLD << "[EDGE] " << RESET << "Trying to get value at out-of-bounds index 100 (should throw an exception):\n";
    try {
        list3.getValueAt(100);
        printFail("getValueAt(100) should throw");
    } catch(const std::exception&) { printSuccess("getValueAt(100) throws as expected"); }
    std::cout << BOLD << GREEN << "\n[LinkList Tests Complete]\n" << RESET;
}

void biLinkListTests(){
    printDivider("BiLinkList Tests");
    std::cout << CYAN << "Testing BiLinkList construction, insertion, removal, moving, and error handling.\n" << RESET;
    std::cout << BOLD << "[INIT] " << RESET << "Creating empty BiLinkList<int> blist1.\n";
    BiLinkList<int> blist1;
    printSubDivider("Empty list");
    std::cout << "[INFO] Printing an empty BiLinkList (should say 'List is empty.'):\n";
    blist1.printList();
    printSubDivider("List of length 4 (default values)");
    std::cout << BOLD << "[INIT] " << RESET << "Creating BiLinkList<int> blist2(4).\n";
    BiLinkList<int> blist2(4);
    std::cout << "[INFO] Printing blist2 (should have 4 default-initialized values):\n";
    blist2.printList();
    int arr[] = {1, 2, 3, 4};
    printSubDivider("List from array");
    std::cout << BOLD << "[INIT] " << RESET << "Creating BiLinkList<int> blist3(arr, 4).\n";
    BiLinkList<int> blist3(arr, 4);
    std::cout << "[INFO] Printing blist3 (should show 1, 2, 3, 4):\n";
    blist3.printList();
    printSubDivider("Insert 99 at index 2");
    std::cout << BOLD << "[TEST] " << RESET << "Inserting 99 at index 2.\n";
    BiNode<int>* newNode = new BiNode<int>(99);
    blist3.insertNode(newNode, 2);
    blist3.printList();
    printSubDivider("Remove node at index 3 (should be 3)");
    std::cout << BOLD << "[TEST] " << RESET << "Removing node at index 3 (should remove 3):\n";
    BiNode<int>* removed = blist3.removeNode(3);
    std::cout << "[RESULT] Removed value: " << removed->getValue() << " (Expected: 3)" << std::endl;
    delete removed;
    blist3.printList();
    printSubDivider("Move node at index 0 to index 2");
    std::cout << BOLD << "[TEST] " << RESET << "Moving node at index 0 to index 2.\n";
    blist3.moveNode(0, 2);
    blist3.printList();
    printSubDivider("Remove from empty list");
    std::cout << BOLD << "[EDGE] " << RESET << "Trying to remove from an empty BiLinkList (should throw an exception):\n";
    try {
        blist1.removeNode(0);
        printFail("removeNode(0) on empty list should throw");
    } catch(const std::exception&) { printSuccess("removeNode(0) on empty list throws as expected"); }
    std::cout << BOLD << "[EDGE] " << RESET << "Trying to get value at out-of-bounds index 100 (should throw an exception):\n";
    try {
        blist3.getValueAt(100);
        printFail("getValueAt(100) should throw");
    } catch(const std::exception&) { printSuccess("getValueAt(100) throws as expected"); }
    std::cout << BOLD << GREEN << "\n[BiLinkList Tests Complete]\n" << RESET;
}

void stackTests(){
    printDivider("Stack Tests");
    std::cout << CYAN << "Testing Stack push, pop, peek, discard, and error handling.\n" << RESET;
    std::cout << BOLD << "[INIT] " << RESET << "Creating empty Stack<int> s.\n";
    Stack<int> s;
    std::cout << "[INFO] Stack should be empty: " << (s.isEmpty() ? "yes" : "no") << std::endl;
    printSubDivider("Push 10, 20, 30");
    std::cout << BOLD << "[TEST] " << RESET << "Pushing 10, 20, 30 onto the stack.\n";
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "[RESULT] After pushes, top (should be 30): " << s.peek() << ", length: " << s.getStackLength() << std::endl;
    printSubDivider("Pop");
    std::cout << BOLD << "[TEST] " << RESET << "Popping the top value (should be 30):\n";
    UniNode<int>* popped = s.pop();
    std::cout << "[RESULT] Popped value: " << popped->getValue() << ", new top: " << s.peek() << std::endl;
    delete popped;
    printSubDivider("Discard");
    std::cout << BOLD << "[TEST] " << RESET << "Discarding the top value (should be 20):\n";
    s.discard();
    std::cout << "[RESULT] After discard, top (should be 10): " << s.peek() << ", length: " << s.getStackLength() << std::endl;
    printSubDivider("Pop until empty");
    std::cout << BOLD << "[TEST] " << RESET << "Popping last value (should be 10):\n";
    s.pop();
    std::cout << BOLD << "[EDGE] " << RESET << "Trying to pop from empty stack (should throw an exception):\n";
    try {
        s.pop();
        printFail("pop() on empty stack should throw");
    } catch(const std::exception&) { printSuccess("pop() on empty stack throws as expected"); }
    std::cout << BOLD << GREEN << "\n[Stack Tests Complete]\n" << RESET;
}

void queueTests(){
    printDivider("Queue Tests");
    std::cout << CYAN << "Testing Queue add, take, peek, discard, and error handling.\n" << RESET;
    std::cout << BOLD << "[INIT] " << RESET << "Creating empty Queue<int> q.\n";
    Queue<int> q;
    std::cout << "[INFO] Queue should be empty: " << (q.isEmpty() ? "yes" : "no") << std::endl;
    printSubDivider("Add 1, 2, 3");
    std::cout << BOLD << "[TEST] " << RESET << "Adding 1, 2, 3 to the queue.\n";
    UniNode<int>* n1 = new UniNode<int>(1);
    UniNode<int>* n2 = new UniNode<int>(2);
    UniNode<int>* n3 = new UniNode<int>(3);
    q.add(n1);
    q.add(n2);
    q.add(n3);
    std::cout << "[RESULT] After adds, front (should be 1): " << q.peek() << ", length: " << q.getQueueLength() << std::endl;
    printSubDivider("Take");
    std::cout << BOLD << "[TEST] " << RESET << "Taking the front value (should be 1):\n";
    UniNode<int>* taken = q.take();
    std::cout << "[RESULT] Taken value: " << taken->getValue() << ", new front: " << (q.isEmpty() ? "none" : std::to_string(q.peek())) << std::endl;
    delete taken;
    printSubDivider("Discard");
    std::cout << BOLD << "[TEST] " << RESET << "Discarding the front value (should be 2):\n";
    q.discard();
    std::cout << "[RESULT] After discard, front (should be 3): " << (q.isEmpty() ? "none" : std::to_string(q.peek())) << ", length: " << q.getQueueLength() << std::endl;
    printSubDivider("Take until empty");
    std::cout << BOLD << "[TEST] " << RESET << "Taking last value (should be 3):\n";
    q.take();
    std::cout << BOLD << "[EDGE] " << RESET << "Trying to take from empty queue (should throw an exception):\n";
    try {
        q.take();
        printFail("take() on empty queue should throw");
    } catch(const std::exception&) { printSuccess("take() on empty queue throws as expected"); }
    std::cout << BOLD << GREEN << "\n[Queue Tests Complete]\n" << RESET;
}

void hashTableTests(){
    printDivider("HashTable Tests");
    std::cout << CYAN << "Testing HashTable insertion, lookup, removal, printing, and error handling.\n" << RESET;
    HashTable<int> ht(3);
    std::cout << "\n" << BOLD << "[INIT] " << RESET << "Created HashTable<int> ht(3).\n";
    std::cout << "HashTable should be empty: " << (ht.isEmpty() ? "yes" : "no") << ", Buckets: " << ht.getBucketCount() << std::endl;
    printSubDivider("Insert 3 entries");
    std::cout << "[TEST] Inserting KVpair<int>(1, 100), KVpair<int>(4, 200), KVpair<int>(7, 300) into the table.\n";
    ht.insertEntry(KVpair<int>(1, 100));
    ht.insertEntry(KVpair<int>(4, 200));
    ht.insertEntry(KVpair<int>(7, 300));
    std::cout << "[INFO] Inserted 3 entries. Printing table (should show 3 entries, each in a bucket):\n";
    ht.printTable();
    printSubDivider("Insert duplicate key 4");
    std::cout << "[TEST] Inserting duplicate key 4 (should add another entry with key 4 in the same bucket):\n";
    ht.insertEntry(KVpair<int>(4, 222));
    ht.printTable();
    printSubDivider("Insert negative and zero keys");
    std::cout << "[TEST] Inserting KVpair<int>(-5, 555) and KVpair<int>(0, 999):\n";
    ht.insertEntry(KVpair<int>(-5, 555));
    ht.insertEntry(KVpair<int>(0, 999));
    ht.printTable();
    printSubDivider("Lookup key 4 (should find first occurrence, value 200)");
    try {
        auto found = ht.lookupEntry(4);
        std::cout << "[RESULT] Lookup key 4: found value = " << found.value << ". (Expected: 200)\n";
        if(found.value == 200) printSuccess("lookupEntry(4) found value 200 as expected");
        else printFail("lookupEntry(4) did not return expected value 200");
    } catch (const std::exception& e) {
        printFail(std::string("Lookup failed: ") + e.what());
    }
    printSubDivider("Lookup key -5");
    try {
        auto found = ht.lookupEntry(-5);
        std::cout << "[RESULT] Lookup key -5: found value = " << found.value << ". (Expected: 555)\n";
        if(found.value == 555) printSuccess("lookupEntry(-5) found value 555 as expected");
        else printFail("lookupEntry(-5) did not return expected value 555");
    } catch (const std::exception& e) {
        printFail(std::string("Lookup failed: ") + e.what());
    }
    printSubDivider("Remove key 1");
    std::cout << "[TEST] Removing key 1 (should remove value 100):\n";
    auto removed = ht.removeEntry(1);
    std::cout << "[RESULT] Removed key 1, value: " << removed->getValue().value << " (Expected: 100)" << std::endl;
    delete removed;
    ht.printTable();
    std::cout << "Is empty after remove: " << (ht.isEmpty() ? "yes" : "no") << std::endl;
    printSubDivider("Remove duplicate key 4 (should remove first occurrence)");
    auto removedDup = ht.removeEntry(4);
    std::cout << "[RESULT] Removed key 4, value: " << removedDup->getValue().value << " (Expected: 200)" << std::endl;
    delete removedDup;
    ht.printTable();
    printSubDivider("Remove non-existent key 42");
    std::cout << "[TEST] Trying to remove key 42 (should throw an exception):\n";
    try {
        ht.removeEntry(42);
        printFail("removeEntry(42) should throw");
    } catch(const std::exception&) { printSuccess("removeEntry(42) throws as expected"); }
    printSubDivider("Lookup non-existent key 99");
    std::cout << "[TEST] Trying to lookup key 99 (should throw an exception):\n";
    try {
        ht.lookupEntry(99);
        printFail("lookupEntry(99) should throw");
    } catch(const std::exception&) { printSuccess("lookupEntry(99) throws as expected"); }
    printSubDivider("Remove all remaining entries");
    try {
        ht.removeEntry(0);
        ht.removeEntry(7);
        ht.removeEntry(-5);
        ht.removeEntry(4); // Remove the duplicate 4
        printSuccess("All remaining entries removed");
    } catch(const std::exception& e) {
        printFail(std::string("Failed to remove all: ") + e.what());
    }
    ht.printTable();
    std::cout << "Is empty after all removes: " << (ht.isEmpty() ? "yes" : "no") << std::endl;
    printSubDivider("Edge: Remove from empty table");
    std::cout << "[TEST] Trying to remove from empty table (should throw):\n";
    try {
        ht.removeEntry(1);
        printFail("removeEntry(1) on empty table should throw");
    } catch(const std::exception&) { printSuccess("removeEntry(1) on empty table throws as expected"); }
    printSubDivider("Edge: Lookup from empty table");
    std::cout << "[TEST] Trying to lookup from empty table (should throw):\n";
    try {
        ht.lookupEntry(1);
        printFail("lookupEntry(1) on empty table should throw");
    } catch(const std::exception&) { printSuccess("lookupEntry(1) on empty table throws as expected"); }
    printSubDivider("Custom hash function (all keys to bucket 0)");
    std::cout << "[TEST] Setting custom hash function (all keys to bucket 0).\n";
    HashTable<int> ht1(5);
    ht1.setHashingFunction([](int, HashTable<int>* currTable) { return 0; });
    ht1.insertEntry(KVpair<int>(123, 321));
    ht1.insertEntry(KVpair<int>(456, 654));
    ht1.insertEntry(KVpair<int>(789, 987));
    std::cout << "[INFO] All keys should be in bucket 0:\n";
    ht1.printTable();
    printSubDivider("Table with 1 bucket");
    std::cout << "[TEST] Creating table with 1 bucket and inserting two entries.\n";
    HashTable<int> ht2(1);
    ht2.insertEntry(KVpair<int>(5, 55));
    ht2.insertEntry(KVpair<int>(10, 110));
    std::cout << "[INFO] All keys should be in the only bucket:\n";
    ht2.printTable();
    std::cout << BOLD << GREEN << "\n[HashTable Tests Complete]\n" << RESET;
}

void runAllTests(){
    uniNodeTests();
    biNodeTests();
    linkListTests();
    biLinkListTests();
    stackTests();
    queueTests();
    hashTableTests();
}

void runStructureTests(){
    linkListTests();
    biLinkListTests();
    stackTests();
    queueTests();
    hashTableTests();
}