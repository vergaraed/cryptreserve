#include "../../include/queue.h"


int test_queue()
{
/*  struct lfds710_queue_bmm_element
    qbmme[8]; // TRD : must be a positive integer power of 2 (2, 4, 8, 16, etc)

  struct lfds710_queue_bmm_state
    qbmms;

  struct test_data
    td,
    *temp_td;

  lfds710_queue_bmm_init_valid_on_current_logical_core( &qbmms, qbmme, 8, NULL );

  strcpy( td.name, "Madge The Skutter" );

  lfds710_queue_bmm_enqueue( &qbmms, NULL, &td );

  lfds710_queue_bmm_dequeue( &qbmms, NULL, &temp_td );

  printf( "skutter name = %s\n", temp_td->name );

  lfds710_queue_bmm_cleanup( &qbmms, NULL );
*/
  return( EXIT_SUCCESS );
}


Queue *ConstructQueue(int limit) {
    if (limit <= 0) {
        limit = 65535;
    }
    Queue *queue = (Queue*) malloc(sizeof(Queue)*limit);
    if (queue == NULL) {
        return NULL;
    }
    queue->limit = limit;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

void DestructQueue(Queue *queue) {
    NODE *pN;
    while (!isEmpty(queue)) {
        pN = Dequeue(queue);
	// free members as well
        free(pN);
    }
    free(queue);
}

int Enqueue(Queue *pQueue, NODE *item) {
    /* Bad parameter */
    if ((pQueue == NULL) || (item == NULL)) {
        return FALSE;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= pQueue->limit) {
        return FALSE;
    }
    /*the queue is empty*/
    item->prev = NULL;
    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;

    } else {
        /*adding item to the end of the queue*/
        pQueue->tail->prev = item;
        pQueue->tail = item;
    }
    pQueue->size++;
    return TRUE;
}

NODE * Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    NODE *item;
    if (isEmpty(pQueue))
        return NULL;
    item = pQueue->head;
    pQueue->head = (pQueue->head)->prev;
    pQueue->size--;
    return item;
}

int isEmpty(Queue* pQueue) {
    if (pQueue == NULL) {
        return FALSE;
    }
    if (pQueue->size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int queuemain() {
    int i;
    Queue *pQ = ConstructQueue(7);
    NODE *pN;

    for (i = 0; i < 9; i++) {
        pN = (NODE*) malloc(sizeof (NODE));
        pN->data.number = 100 + i;
        Enqueue(pQ, pN);
    }

    while (!isEmpty(pQ)) {
        pN = Dequeue(pQ);
        printf("\nDequeued: Name: %s  CID:%s Number:%d", pN->data.name, pN->data.CID, pN->data.number);
        free(pN);
    }
    DestructQueue(pQ);
    return (EXIT_SUCCESS);
}
