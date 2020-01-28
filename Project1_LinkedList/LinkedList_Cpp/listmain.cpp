//Main file used to test the list
//---------------------------------------------------------------
// File: ListMain.cpp
// Purpose: Main file with tests for a demonstration of an unsorted  
//          list implemented as a linked structure.
// Programming Language: C++

#include "linked_list.h"
#include <cstdio>

int main(int argc, char **argv) {
    Linked_List theList;
    float f;

    printf("Simple List Demonstration\n");
    printf("(List implemented as an Array - Do not try this at home)\n\n");
    printf("Create a list and add a few tasks to the list\n");

    // Instantiate list object
    theList = Linked_List();

    // Insert 5 elements into the list
    theList.Insert(5, 3.1f);
    theList.Insert(1, 5.6f);
    theList.Insert(3, 8.3f);
    theList.Insert(2, 7.4f);
    theList.Insert(4, 2.5f);

    // Show what is in the list
    theList.PrintList();

    // Test the list length function
    printf("\nList now contains %u items\n\n", theList.ListLength());

    // Test delete function
    printf("Testing delete of last item in list (key 4).\n");
    theList.Delete(4);
    theList.PrintList();
    printf("Testing delete of first item in list (key 5).\n");
    theList.Delete(5);
    theList.PrintList();
    printf("Testing delete of a middle item in list (key 3).\n");
    theList.Delete(3);
    theList.PrintList();

    // Test delete function with a known failure argument
    printf("Testing failure in delete function (key 4).\n");
    if (theList.Delete(4))
        printf("FAIL. Should not have been able to delete.\n");
    else
        printf("PASS. Unable to locate item to delete.\n");

    // Test search (known failure)
    printf("Testing Search function. Search for key 3\n");
    if (theList.Search(3, &f))
        printf("FAIL. Search result: theData = %f\n", f);
    else
        printf("PASS. Search result: Unable to locate item in list\n");

    // Test search (known success)
    printf("Testing Search function. Search for key 2\n");
    if (theList.Search(2, &f))
        printf("PASS. Search result: theData = %f\n", f);
    else
        printf("FAIL. Search result: Unable to locate item in list\n");

    printf("\n\nEnd list demonstration...");

    return 0;
}