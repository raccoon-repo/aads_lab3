#ifndef __ARRAY_LIST__
#define __ARRAY_LIST__
#include "heap_type.h"

enum sort_order { ASC, DESC };

class array_list
{
private:
    int * source;
    static const int DEFAULT_CAPACITY = 16;
    int source_capacity;
    int source_size;
    bool source_isEmpty;

    void check_range(int index);
    void ensure_capacity(int size);
    void truncate_to_capacity(int new_size);

    void sift_down(int i);
    int find_index_max();

    void heap_sort(heap_type type);
public:
    ~array_list();
    array_list();
    array_list(int capacity);
    array_list(int * source, int source_capacity);

    bool isEmpty() const;
    void printList() const;
    void heap_sort(sort_order order = ASC);
    int size() const;
    int capacity() const;

    void add(int item);
    void addAll(int * values, int values_size);
    int remove(int index);
    int get(int index);
    void set(int index, int value);

    int delete_top();
};

namespace comparators {
    int asc_comparator(int left, int right);
    int desc_comparator(int left, int right);
}

#endif