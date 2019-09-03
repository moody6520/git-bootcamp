/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL){
      return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  if (q != NULL){
    /* How about freeing the list elements and the strings? */
    if(q->size != 0){
      list_ele_t *cur = q->head;
      while(cur != q->tail){
        free(cur->value);
        list_ele_t *tmp = cur;
        cur = cur->next;
        free(tmp);
      }
      free(cur->value);
      free(cur);
      /* Free queue structure */
    }
    free(q);
  }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
  if (q != NULL){
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    if (newh != NULL){
      newh->value = malloc(strlen(s)+1);
      if (newh->value != NULL){
        strcpy(newh->value,s);
        if (q->size == 0){
          q->head = newh;
          q->tail = newh;
          newh->next = NULL;
          q->size = 1;
        }
        else{
          newh->next = q->head;
          q->head = newh;
          q->size += 1;
        }
        return true;
      }
      else{
        free(newh);
      }
    }
  }
  return false;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q!=NULL){
      list_ele_t *newt;
      newt = malloc(sizeof(list_ele_t));
      if(newt != NULL){
        newt->value = malloc(strlen(s)+1);
        if (newt->value != NULL){
          strcpy(newt->value,s);
          if (q->size == 0){
            q->head = newt;
            q->tail = newt;
            newt->next = NULL;
            q->size = 1;
          }
          else{
            q->tail->next = newt;
            q->tail = newt;
            newt->next = NULL;
            q->size += 1;
          }
          return true;
        }
        else{
          free(newt);
        }
      }
    }
    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q != NULL && q->size != 0){
      if (sp != NULL ){
        strncpy(sp, q->head->value,bufsize-1);
        sp[bufsize-1] = '\0';
      }
      free(q->head->value);
      list_ele_t *tmp = q->head;
      q->head = q->head->next;
      free(tmp);
      q->size -= 1;
      return true;
    }
    return false;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if ( q != NULL){
      return q->size;
    }
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->size <=1 ){
      return;
    }
    /*
      PP   P    PN 
      A -> B -> C -> D 
    */
    list_ele_t *pp = NULL;
    list_ele_t *p = q->head;
    list_ele_t *pn = NULL;
    q->tail = p;
    while( p->next != NULL){
      pn = p->next;
      p->next = pp;
      pp = p;
      p = pn;
    }
    pn->next = pp;
    q->head = pn;
}

