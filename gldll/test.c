#include "gldll.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _person{

    int age;
    int weight;
    gldll_t gldll;
} person_t ;

int 
senior_citizen(person_t *p1, person_t *p2){

    if(p1->age == p2->age) return 0;
    if(p1->age < p2->age) return 1;
    return -1;
}

#define offset(struct_name, fld_name) \
    (unsigned int)&(((struct_name *)0)->fld_name)

gldll_TO_STRUCT(thread_to_person, person_t, gldll);

int main(int argc, char **argv){

    person_t person[5];
    memset(person, 0, sizeof(person_t) * 5);
    person[0].age = 1;
    person[0].weight = 2;
    person[1].age = 3;
    person[1].weight = 4;
    person[2].age = 5;
    person[2].weight = 6;
    person[3].age = 7;
    person[3].weight = 8;
    person[4].age = 9;
    person[4].weight = 10;

    gldll_t base_gldll;
    init_gldll(&base_gldll);

    gldll_priority_insert(&base_gldll, &person[4].gldll, senior_citizen, offset(person_t, gldll));
    gldll_priority_insert(&base_gldll, &person[3].gldll, senior_citizen, offset(person_t, gldll));
    gldll_priority_insert(&base_gldll, &person[2].gldll, senior_citizen, offset(person_t, gldll));
    gldll_priority_insert(&base_gldll, &person[1].gldll, senior_citizen, offset(person_t, gldll));
    gldll_priority_insert(&base_gldll, &person[0].gldll, senior_citizen, offset(person_t, gldll));

    gldll_t *curr = NULL;
    ITERATE_gldll_BEGIN(&base_gldll, curr){

        person_t *p = thread_to_person(curr);
        printf("Age = %d\n", p->age);
    } ITERATE_gldll_END(&base_gldll, curr);
    
    return 0;
}
