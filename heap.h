#ifndef __HEAP__
#define __HEAP__
#include "heap_type.h"
#include "array_list.h"

class heap 
{
private:
    int heap_size;
    array_list * list;
    void heapify(int);
    /**
     * A pointer to a function
     * that represents a rule for 
     * comparing two elements  
     */

    int (*comparator)(int, int);
    void sift_up(int);
    void sift_down(int);
    heap_type type;
public: 
    ~heap();
    heap(int * source, int size, heap_type type);
    heap(heap_type type = MIN);

    int size() const;
    int get_top();
    int get_last();
    void print() const;
    void add(int item);
};


#endif