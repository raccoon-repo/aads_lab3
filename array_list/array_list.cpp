#include<iostream>
#include "array_list.h"
#include "../heap/heap.h"

int array_list::capacity() const { return source_capacity; }
int array_list::size() const { return source_size; }
bool array_list::isEmpty() const { return source_isEmpty; }

/**
 * Increases capacity of source array
 * when new element is being inserted and source
 * array hasn't got enough space to maintain
 * it
 */
void array_list::ensure_capacity(int size)
{
    if (size >= source_capacity)
    {
        int t_capacity = source_capacity << 1;
        int * temp = new int[t_capacity];

        for (int i = 0; i < source_capacity; i++)
            temp[i] = source[i];
        

        delete[] source;
        source_capacity = t_capacity;
        source = temp;
    }
}

void array_list::truncate_to_capacity(int new_capacity)
{
    int * temp = new int[new_capacity];
    for (int i = 0; i < source_size; i++)
        temp[i] = source[i];
    
    delete[] source;
    source_capacity = new_capacity;
    source = temp; 
}


void array_list::printList() const 
{
    std::cout << "[ ";
    for (int i = 0; i < source_size - 1; i++)
        std::cout << source[i] << ", ";
    if (source_size != 0) std::cout << source[source_size - 1];

    std::cout << " ]" << std::endl;
}

array_list::array_list(int * source, int capacity)
{
    source_size = 0;
    source_capacity = DEFAULT_CAPACITY > capacity ? DEFAULT_CAPACITY : capacity;
    this->source = new int[source_capacity];

    for (int i = 0; i < capacity; i++) {
        this->source[i] = source[i];
        source_size++;
    }
}

array_list::~array_list()
{
    delete[] source;
}

array_list::array_list()
{
    source_capacity = DEFAULT_CAPACITY;
    source_size = 0;
    source = new int[source_capacity];
}

array_list::array_list(int capacity)
{
    source_capacity = capacity;
    source_size = 0;
    source = new int[capacity];
}

void array_list::add(int item)
{
    ensure_capacity(source_size);
    source[source_size++] = item;
}

void array_list::addAll(int * values, int values_size)
{
    for (int i = 0; i < values_size; i++)
        add(values[i]);
}

void array_list::check_range(int index)
{
    if (index < 0 || index >= source_size)
        throw std::out_of_range("index must be >= 0 and < size of array list");
}

int array_list::remove(int index)
{
    check_range(index);
    int res = source[index];
    for (int i = index; i < source_size - 1; i++)
        source[i] = source[i + 1];
    
    source[--source_size] = 0;
    if (source_size && source_capacity / source_size >= 4) {
        truncate_to_capacity(source_capacity / 2);
    }

    return res;    
}

int array_list::get(int index)
{
    check_range(index);
    return source[index];
}

void array_list::set(int index, int value)
{
    check_range(index);
    source[index] = value;
}

void array_list::heap_sort(sort_order order)
{
    heap_type type = order == ASC ? MIN : MAX;
    heap_sort(type);
}

void array_list::heap_sort(heap_type type)
{
    heap * t_heap = new heap(source, source_size, type);
    int heap_size = t_heap->size();

    for (int i = 0; i < heap_size; i++)
        source[i] = t_heap->get_top();

    delete t_heap;
}
/**
 * It deletes and returns the list item 
 * that is considered as the top element of a maxheap.  
 * The method result should be a minheap also.
*/
int array_list::delete_top()
{
    // build minheap
    for (int i = source_size / 2; i >= 0; i--)
        sift_down(i);
    
    printList();
    // find index of max element
    int i = find_index_max();
    if (i == -1)
        return 0;
    // remove it from array
    return remove(i);
}

int array_list::find_index_max() {
    if (source_size <= 0)
        return -1;

    int max = source[0];
    int i_max = 0;
    for (int i = 1; i < source_size; i++) {
        if (max < source[i]) {
            max = source[i];
            i_max = i;
        }
    }

    return i_max;
}

void array_list::sift_down(int i)
{
    int l_child;
    int r_child;
    int parent;

    while(true)
    {
        l_child = (i << 1) + 1;
        r_child = (i << 1) + 2;
        parent = i;


        if (l_child < source_size && get(parent) > get(l_child))
            parent = l_child;
        if (r_child < source_size && get(parent) > get(r_child))
            parent = r_child;
        if (parent == i)
            break;

        int temp = get(i);
        set(i, get(parent));
        set(parent, temp);
        i = parent;
    }
}

int comparators::asc_comparator(int left, int right)
{
    return left - right;
}

int comparators::desc_comparator(int left, int right)
{
    return right - left;
}

