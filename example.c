#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HOW_MANY  7

char *names[HOW_MANY] = { "Chris", "Ben", "RDJ", "Mark", "Scarlet", "Samuel", "Tom" };
int ages[HOW_MANY] = { 22, 24, 50, 26, 18, 32, 24 };

/* declare your struct for a person here */
struct person {
    char *name;
    int age;
    struct person *next;
};

static int compare_people(const struct person *a, const struct person *b) {
     return strcmp(a->name, b->name);
}

static struct person *insert_sorted(struct person *headptr, char *name, int age) {
    // Allocate heap space for a record
    struct person *ptr = malloc(sizeof(struct person));
    if (ptr == NULL) {
        abort();
    }

    // Assign to structure fields
    ptr->name = name;
    ptr->age = age;
    ptr->next = NULL;

    struct person **pp = &headptr;
    while (*pp != NULL && compare_people(ptr, *pp) >= 0) {
        pp = &(*pp)->next;
    }
    ptr->next = *pp;
    *pp = ptr;

    return headptr;
}

int main(int argc, char **argv) {
    // initialise the list to be empty
    struct person *headptr = NULL;

    // To insert all the info in the array
    for (int i = 0; i < HOW_MANY; i++) {
        headptr = insert_sorted(headptr, names[i], ages[i]);
    }

    struct person *current = headptr;
    while (current != NULL) {
        printf("The person's name is %s and the age is %d.\n", current->name, current->age);
        current = current->next;
    }
    return 0;
}