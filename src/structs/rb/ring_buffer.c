/**
 * @file ring_buffer.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-18
 */

//_____ I N C L U D E S _______________________________________________________
#include "ring_buffer.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common/uc_assert.h"
#include "core/container.h"
#include "interface/allocator_if.h"

//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
/**
 *  \brief
 */
typedef struct
{
  volatile size_t tail;
  volatile size_t head;
  size_t max_size;
} rbmeta_t;

//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes and returns a new ring buffer.
 *
 * Detailed description see in stack.h
 */
ring_buffer_t *rb_create(size_t size, size_t esize)
{
  UC_ASSERT(0 != esize);
  UC_ASSERT(0 != size);

  if (!is_allocator_valid())
  {
    return NULL;
  }

  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  ring_buffer_t *rb = (ring_buffer_t *)mem_allocate(sizeof(ring_buffer_t));
  if (NULL == rb)
  {
    return NULL;
  }

  void *data = (void *)mem_allocate(esize);
  if (NULL == data)
  {
    return NULL;
  }

  memset(data, 0, esize);

  rb->container = container_create(esize, CONTAINER_VECTOR_BASED);
  if (NULL == rb->container)
  {
    return NULL;
  }

  for (size_t i = 0; i < size; i++)
  {
    if (!container_push_back(rb->container, data))
    {
      return NULL;
    }
  }

  rb->meta = (void *)mem_allocate(sizeof(rbmeta_t));
  if (NULL == rb->meta)
  {
    container_delete(&rb->container);
    mem_free(data);
    mem_free(rb);
    return NULL;
  }

  rbmeta_t *meta = (rbmeta_t *)rb->meta;
  meta->head = 0;
  meta->tail = 0;
  meta->max_size = size;

  return rb;
}

/**
 * \brief Frees up the memory associated with the ring buffer.
 *
 * Detailed description see in stack.h
 */
void rb_delete(ring_buffer_t **rb)
{
  UC_ASSERT(rb);
  UC_ASSERT(*rb);
  UC_ASSERT((*rb)->container);
  UC_ASSERT((*rb)->meta);

  free_fn_t mem_free = get_free();

  container_delete((container_t **)(*rb)->container);
  mem_free(((*rb)->meta));
  mem_free(*rb);
  *rb = NULL;
}

/**
 * \brief Adds an element to the ring buffer.
 *
 * Detailed description see in stack.h
 */
bool rb_add(ring_buffer_t *rb, const void *data)
{
  UC_ASSERT(rb);
  UC_ASSERT(rb->container);
  UC_ASSERT(data);

  if (rb_is_full(rb))
  {
    return false;
  }

  rbmeta_t *meta = (rbmeta_t *)rb->meta;

  if (!container_replace(rb->container, data, meta->head))
  {
    return false;
  }

  meta->head = (meta->head + 1) % meta->max_size;

  return true;
}

/**
 * \brief Removes an element from the ring buffer and returns it.
 *
 * Detailed description see in stack.h
 */
bool rb_get(ring_buffer_t *rb, void *data)
{
  UC_ASSERT(rb);
  UC_ASSERT(rb->container);
  UC_ASSERT(data);

  if (rb_is_empty(rb))
  {
    return false;
  }

  rbmeta_t *meta = (rbmeta_t *)rb->meta;

  if (!container_at((container_t *)rb->container, data, meta->tail))
  {
    return false;
  }

  meta->tail = (meta->tail + 1) % meta->max_size;
}

/**
 * \brief Retrieves an element from the ring buffer without removing it.
 *
 * Detailed description see in stack.h
 */
bool rb_peek(const ring_buffer_t *rb, void *data)
{
  UC_ASSERT(rb);
  UC_ASSERT(rb->container);
  UC_ASSERT(data);

  if (rb_is_empty(rb))
  {
    return false;
  }

  rbmeta_t *meta = (rbmeta_t *)rb->meta;

  return container_at((container_t *)rb->container, data, meta->tail);
}

/**
 * \brief Returns the number of elements in the ring buffer.
 *
 * Detailed description see in stack.h
 */
size_t rb_size(const ring_buffer_t *rb)
{
  UC_ASSERT(rb);

  rbmeta_t *meta = (rbmeta_t *)rb->meta;

  return abs((int)(meta->tail - meta->head));
}

/**
 * \brief Checks if the ring buffer is empty.
 *
 * Detailed description see in stack.h
 */
bool rb_is_empty(const ring_buffer_t *rb)
{
  UC_ASSERT(rb);

  rbmeta_t *meta = (rbmeta_t *)rb->meta;
  return (abs((int)(meta->tail - meta->head)) == 0);
}

/**
 * \brief Checks if the ring buffer is full.
 *
 * Detailed description see in stack.h
 */
bool rb_is_full(const ring_buffer_t *rb)
{
  UC_ASSERT(rb);

  rbmeta_t *meta = (rbmeta_t *)rb->meta;
  return (abs((int)(meta->tail - meta->head)) >= meta->max_size - 1);
}

/**
 * \brief Clears all the elements from the ring buffer.
 *
 * Detailed description see in stack.h
 */
bool rb_clear(ring_buffer_t *rb)
{
  UC_ASSERT(rb);

  rbmeta_t *meta = (rbmeta_t *)rb->meta;

  meta->tail = meta->head = 0;

  return true;
}
