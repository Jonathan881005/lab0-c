#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *t;
    if (!q)
        return;

    while (q->head) {
        t = q->head;
        q->head = t->next;
        free(t->value);
        free(t);
    }

    free(q);

}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *t = malloc(sizeof(list_ele_t));
    if (!t) {
        free(t);
        return false;
    }
    t->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!t->value) {
        free(t->value);
        free(t);
        return false;
    }
    /*
    if (!newh->value) {
        free(newh->value);
        free(newh);
        return false;
    }
    */

    strncpy(t->value, s, strlen(s));
    t->value[strlen(s)] = '\0';
    t->next = NULL;

    if (q->size == 0) {
        q->head = q->tail = t;
        t->next = NULL;
    } else {
        t->next = q->head;
        q->head = t;
    }
    q->size++;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *t = malloc(sizeof(list_ele_t));
    if (!t) {
        free(t);
        return false;
    }

    t->value = malloc(sizeof(char) * strlen(s) + 1);
    if (!t->value) {
        free(t->value);
        free(t);
        return false;
    }

    strncpy(t->value, s, strlen(s));
    t->value[strlen(s)] = '\0';
    t->next = NULL;

    if (q->size == 0) {
        q->head = q->tail = t;
        t->next = NULL;
    } else {
        q->tail->next = t;
        q->tail = t;
    }
    q->size++;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;

    list_ele_t *t = q->head;
    q->head = q->head->next;

    if (t->value) {
        if (sp) {
            strncpy(sp, t->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        }
        free(t->value);
    }
    free(t);

    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head || q->size == 1)
        return;

    list_ele_t *a, *b, *c;
    a = NULL;
    b = q->head;
    c = b->next;

    q->tail = q->head;
    while (c != NULL) {
        b->next = a;
        a = b;
        b = c;
        c = c->next;
    }
    b->next = a;
    q->head = b;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || !q->head)
        return;
    /*
    list_ele_t *t;
    for(int i = 0; i < q->size; i++){
        t = q->head;
        for(int j = 0; j < i; j++)  t = t->next;
        while(t->next != NULL)
    }
    */
}
