/**
 * \file    queue.c
 * \author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief   Implementation of a generic queue data structure.
 * \date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "queue.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "common/uc_assert.h"
#include "interface/allocator_if.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
typedef struct
{
  size_t capacity;
} qmeta_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes and returns a new queue
 *
 * Detailed description see in queue.h
 */
queue_t *queue_create(size_t size, size_t esize)
{
  UC_ASSERT(0 != esize);

  if (!is_allocator_valid())
  {
    return NULL;
  }

  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  queue_t *queue = (queue_t *)mem_allocate(sizeof(queue_t));
  if (NULL == queue)
  {
    return NULL;
  }

  queue->container = container_create(esize, CONTAINER_LINKED_LIST_BASED);
  if (NULL == queue->container)
  {
    mem_free(queue);
    return NULL;
  }

  queue->meta = (void *)mem_allocate(sizeof(qmeta_t));
  if (NULL == queue->meta)
  {
    container_delete(&queue->container);
    mem_free(queue);
    return NULL;
  }

  qmeta_t *meta = (qmeta_t *)queue->meta;
  meta->capacity = size;

  return queue;
}

/**
 * Frees up the memory associated with the queue
 *
 * Detailed description see in queue.h
 */
void queue_delete(queue_t **queue)
{
  UC_ASSERT(queue);
  UC_ASSERT(*queue);
  UC_ASSERT((*queue)->container);
  UC_ASSERT((*queue)->meta);

  free_fn_t mem_free = get_free();

  container_delete(&((*queue)->container));
  mem_free(((*queue)->meta));
  mem_free(*queue);
  *queue = NULL;
}

/**
 * Checks if the queue is empty.
 *
 * Detailed description see in queue.h
 */
bool queue_empty(const queue_t *queue)
{
  UC_ASSERT(queue);
  UC_ASSERT(queue->container);

  return (container_size(queue->container) == 0);
}

/**
 * Checks if the queue is full.
 *
 * Detailed description see in queue.h
 */
bool queue_full(const queue_t *queue)
{
  UC_ASSERT(queue);
  UC_ASSERT(queue->container);

  size_t size = ((qmeta_t *)queue->meta)->capacity;
  return (size != 0) ? container_size(queue->container) == size : false;
}

/**
 * Adds an element to the queue.
 *
 * Detailed description see in queue.h
 */
bool queue_add(queue_t *queue, const void *data)
{
  UC_ASSERT(queue);
  UC_ASSERT(data);
  UC_ASSERT(queue->container);

  return (!queue_full(queue)) ? container_push_back(queue->container, data) : false;
}

/**
 * Removes an element from the queue and returns it.
 *
 * Detailed description see in queue.h
 */
bool queue_get(queue_t *queue, void *data)
{
  UC_ASSERT(NULL != queue);
  UC_ASSERT(NULL != data);
  UC_ASSERT(queue->container);

  return container_pop_front(queue->container, data);
}

/**
 * Retrieves the element from the queue without removing it.
 *
 * Detailed description see in queue.h
 */
bool queue_peek(const queue_t *queue, void *data)
{
  UC_ASSERT(NULL != queue);
  UC_ASSERT(NULL != data);
  UC_ASSERT(queue->container);

  return container_at(queue->container, data, 0);
}

/**
 * Returns the number of elements in the queue.
 *
 * Detailed description see in queue.h
 */
size_t queue_size(const queue_t *queue)
{
  UC_ASSERT(NULL != queue);
  UC_ASSERT(queue->container);

  return container_size(queue->container);
}

/**
 * Clears all the elements from the queue.
 *
 * Detailed description see in queue.h
 */
bool queue_clear(queue_t *queue)
{
  UC_ASSERT(NULL != queue);
  UC_ASSERT(queue->container);

  return container_clear(queue->container);
}
