#include "array_list/array_list.h"
#include "heap/heap.h"
#include <iostream>
#include <string>

int main()
{
    int values[] = {1, 2, 5, 3, 11, 0, 5, 19};
    array_list * list = new array_list(values, 8);

    std::cout << list->delete_top();
    list->printList();
    std::cout << list->delete_top();
    list->printList();

    delete list;
    return 0;
}