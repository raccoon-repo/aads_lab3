#include "heap.h"

heap::heap(int * source, int size, heap_type type)
{
    list = new array_list(source, size);
    heap_size = size;
    this->comparator = type == MAX ? comparators::desc_comparator 
                                   : comparators::asc_comparator;
    this->type = type;
    for (int i = heap_size / 2; i >= 0; i--)
        sift_down(i); 
}

heap::heap(heap_type type)
{
    list = new array_list();
    heap_size = 0;
    this->comparator = type == MAX ? comparators::desc_comparator 
                                   : comparators::asc_comparator;
    this->type = type;
}

void heap::sift_down(int i)
{

    int l_child;
    int r_child;
    int parent;

    while(true)
    {
        l_child = (i << 1) + 1;
        r_child = (i << 1) + 2;
        parent = i;


        // depending on comparator implementation
        // it builds either maxheap or minheap
        if (l_child < heap_size && comparator(list->get(parent), list->get(l_child)) > 0)
            parent = l_child;
        if (r_child < heap_size && comparator(list->get(parent), list->get(r_child) ) > 0)
            parent = r_child;
        if (parent == i)
            break;

        int temp = list->get(i);
        list->set(i, list->get(parent));
        list->set(parent, temp);
        i = parent;
    }

}

void heap::sift_up(int i)
{
    if (i == 0)
        return;
    int parent_idx = (i & 1) ? i / 2 : i / 2 - 1;

    int value = list->get(i);
    int parent = list->get(parent_idx);


    if (comparator(parent, value) > 0)
    {
        list->set(parent_idx, value);
        list->set(i, parent);
        sift_up(parent_idx);
    }
}

int heap::get_last()
{
    int item = list->get(heap_size - 1);
    list->remove(--heap_size);
    return item;
}

int heap::get_top()
{
    if (!heap_size)
        return 0;
    
    int head = list->get(0);
    int last = get_last();
    if (heap_size)
        list->set(0, last);
    sift_down(0);

    return head;
}

int heap::size() const { return heap_size; }

void heap::print() const { list->printList(); }

void heap::add(int item)
{
    list->add(item);
    heap_size++;

    sift_up(heap_size - 1);
}



heap::~heap()
{
    delete list;
}


