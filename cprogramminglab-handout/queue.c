/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * @author 0130 <lovenvibest@gmail.com>
 */

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        printf("MEMORY NOT ENOUGH: malloc queue\n");
        exit(-1);
    }
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = q->head;
    q->num = 0;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    }
    list_ele_t *head = q->head;
    if (head == NULL) {
        free(head);
        free(q);
        return;
    }
    while (head->next != NULL) {
        list_ele_t *new_head = head->next;
        free(head->value);
        free(head);
        head = new_head;
    }
    free(head->value);
    free(head);
    q->num = 0;
    free(q);
    return;
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        printf("MEMORY NOT ENOUGH: malloc newh\n");
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    char *s_copy = malloc(strlen(s) + 1);
    if (s_copy == NULL) {
        free(newh);
        printf("MEMORY NOT ENOUGH: malloc s_copy\n");
        return false;
    }
    strncpy(s_copy, s, strlen(s));
    s_copy[strlen(s)] = '\0';
    newh->value = s_copy;
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (q->num == 0) {
        q->tail = q->head;
    }
    q->num++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        printf("MEMORY NOT ENOUGH: malloc newh\n");
        return false;
    }
    char *s_copy = malloc(strlen(s) + 1);
    if (s_copy == NULL) {
        free(newh);
        printf("MEMORY NOT ENOUGH: malloc s_copy\n");
        return false;
    }
    strncpy(s_copy, s, strlen(s));
    s_copy[strlen(s)] = '\0';
    newh->value = s_copy;
    newh->next = NULL;
    if (q->tail != NULL) {
        q->tail->next = newh;
    }
    q->tail = newh;
    if (q->num == 0) {
        q->head = q->tail;
    }
    q->num++;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if (q == NULL || q->num == 0) {
        return false;
    }
    list_ele_t *head = q->head;
    q->head = q->head->next;
    if (buf != NULL && head->value != NULL) {
        strncpy(buf, head->value, bufsize - 1);
        buf[bufsize - 1] = '\0';
    }
    free(head);
    q->num--;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return 0;
    }
    return q->num;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (q == NULL || q->num == 0 || q->num == 1) {
        return;
    }
    list_ele_t *pre = NULL;
    list_ele_t *curr_head = q->head;
    while (curr_head->next != NULL) {
        list_ele_t *temp = curr_head->next;
        curr_head->next = pre;
        pre = curr_head;
        curr_head = temp;
    }
    curr_head->next = pre;
    list_ele_t *temp = q->head;
    q->head = q->tail;
    q->tail = temp;
    return;
}
