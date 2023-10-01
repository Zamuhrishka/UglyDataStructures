/**
 * \file    stack.h
 * \author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief   Implementation of a generic stack data structure.
 * \date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "stack.h"

#include "common/uc_assert.h"
#include <stdbool.h>
#include <stdint.h>

#include "interface/allocator_if.h"

//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
typedef struct
{
  size_t capacity;
} smeta_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes and returns a new stack.
 *
 * Detailed description see in stack.h
 */
stack_t *stack_create(size_t size, size_t esize)
{
  UC_ASSERT(0 != esize);

  if (!is_allocator_valid())
  {
    return NULL;
  }

  allocate_fn_t mem_allocate = get_allocator();
  free_fn_t mem_free = get_free();

  stack_t *stack = (stack_t *)mem_allocate(sizeof(stack_t));
  if (NULL == stack)
  {
    return NULL;
  }

  stack->container = container_create(esize, CONTAINER_VECTOR_BASED);
  if (NULL == stack->container)
  {
    mem_free(stack);
    return NULL;
  }

  // stack->private = (void *)mem_allocate(sizeof(smeta_t));
  // if (NULL == stack->private)
  // {
  //   container_delete(&stack->container);
  //   mem_free(stack);
  //   return NULL;
  // }

  // smeta_t *stack_priv = (smeta_t *)stack->private;
  // stack_priv->capacity = size;

  // // stack->capacity = size;

  stack->meta = (void *)mem_allocate(sizeof(smeta_t));
  if (NULL == stack->meta)
  {
    container_delete(&stack->container);
    mem_free(stack);
    return NULL;
  }

  smeta_t *meta = (smeta_t *)stack->meta;
  meta->capacity = size;

  return stack;
}

/**
 * \brief Frees up the memory associated with the stack.
 *
 * Detailed description see in stack.h
 */
void stack_delete(stack_t **stack)
{
  UC_ASSERT(stack);
  UC_ASSERT(*stack);
  UC_ASSERT((*stack)->container);
  UC_ASSERT((*stack)->meta);

  free_fn_t mem_free = get_free();

  container_delete(&((*stack)->container));
  mem_free(((*stack)->meta));
  mem_free(*stack);
  *stack = NULL;
}

/**
 * \brief Adds an element to the stack.
 *
 * Detailed description see in stack.h
 */
bool stack_push(stack_t *stack, const void *data)
{
  UC_ASSERT(stack);
  UC_ASSERT(data);
  UC_ASSERT(stack->container);

  return (!stack_full(stack)) ? container_push_back(stack->container, data) : false;
}

/**
 * \brief Removes an element from the stack and returns it.
 *
 * Detailed description see in stack.h
 */
bool stack_pop(stack_t *stack, void *data)
{
  UC_ASSERT(stack);
  UC_ASSERT(data);
  UC_ASSERT(stack->container);

  return container_pop_back(stack->container, data);
}

/**
 * \brief Retrieves the element from the stack without removing it.
 *
 * Detailed description see in stack.h
 */
bool stack_peek(const stack_t *stack, void *data)
{
  UC_ASSERT(stack);
  UC_ASSERT(data);
  UC_ASSERT(stack->container);

  return container_at(stack->container, data, container_size(stack->container) - 1);
}

/**
 * \brief Returns the number of elements in the stack.
 *
 * Detailed description see in stack.h
 */
size_t stack_size(const stack_t *stack)
{
  UC_ASSERT(stack);
  UC_ASSERT(stack->container);

  return container_size(stack->container);
}

/**
 * \brief Checks if the stack is empty.
 *
 * Detailed description see in stack.h
 */
bool stack_empty(const stack_t *stack)
{
  UC_ASSERT(stack);
  return (container_size(stack->container) == 0);
}

/**
 * \brief Checks if the stack is full.
 *
 * Detailed description see in stack.h
 */
bool stack_full(const stack_t *stack)
{
  UC_ASSERT(stack);
  UC_ASSERT(stack->container);

  size_t size = ((smeta_t *)stack->meta)->capacity;
  return (size != 0) ? container_size(stack->container) == size : false;
}

/**
 * \brief Clears all the elements from the stack.
 *
 * Detailed description see in stack.h
 */
bool stack_clear(stack_t *stack)
{
  UC_ASSERT(stack);
  UC_ASSERT(stack->container);

  return container_clear(stack->container);
}
