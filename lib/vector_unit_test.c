#include "vector.h"
#include "item.h"
#include <stdio.h>

int main()
{
    Vector v = create_vector();

    printf("Is vector empty? %s\n", vector_empty(v) ? "Yes" : "No");

    //Create the vector and add elements to it
    printf("%d %d\n", vector_size(v), vector_capacity(v));
    vector_push_back(v, create_item(1));
    vector_push_back(v, create_item(2));
    vector_push_back(v, create_item(3));
    vector_push_back(v, create_item(4));
    vector_push_back(v, create_item(5));
    printf("%d %d\n", vector_size(v), vector_capacity(v));
    vector_push_back(v, create_item(6));
    vector_push_back(v, create_item(7));
    vector_push_back(v, create_item(8));
    vector_push_back(v, create_item(9));
    vector_push_back(v, create_item(10));
    printf("%d %d\n", vector_size(v), vector_capacity(v));

    printf("Is the vector still empty? %s\n", vector_empty(v) ? "Yes" : "No");

    for (int i = 0; i < 10; i++)
    {
        printf("Value at %d: %d\n", i, vector_at(v, i)->j);
    }

    Item i = vector_pop(v);
    printf("Last item gets popped..: %d\n", i->j);
    delete_item(i);
    printf("Now the size of the vector is: %d\n", vector_size(v));

    vector_insert(v, 3, create_item(20));
    for (int i = 0; i < 10; i++)
    {
        printf("Value at %d: %d\n", i, vector_at(v, i)->j);
    }

    delete_vector(v, delete_item);
}