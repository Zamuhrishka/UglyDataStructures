/**
 * \file    stack.h
 * \author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief   Implementation of a generic stack data structure.
 * \date    2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "core/container.h"
#include "structs/ds.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
typedef ds_t stack_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes and returns a new stack.
 *
 * \param[in] size The size in elements of this stack or 0 if you won`t limit size of stack.
 * \param[in] esize The size in bytes of the single element that this stack will store.
 *
 * \note if the `size` argument equals 0 then the stack would be unlimited by size.
 *
 * \return Pointer to the newly created stack or NULL.
 */
stack_t *stack_create(size_t size, size_t esize);

/**
 * \brief Frees up the memory associated with the stack.
 *
 * \param[in] stack Double pointer to the stack to be deleted.
 */
void stack_delete(stack_t **stack);

/**
 * \brief Adds an element to the top of the stack.
 *
 * \param[in] stack Pointer to the stack.
 * \param[in] data Pointer to the variable to be pushed.
 * \return true if the operation was successful, false otherwise.
 */
bool stack_push(stack_t *stack, const void *data);

/**
 * \brief Removes the top element from the stack and returns it.
 *
 * \param[in] stack Pointer to the stack.
 * \param[out] data Pointer to a variable where the popped element will be stored.
 * \return true if the operation was successful, false otherwise.
 */
bool stack_pop(stack_t *stack, void *data);

/**
 * \brief Retrieves the top element from the stack without removing it.
 *
 * \param[in] stack Pointer to the stack.
 * \param[out] data Pointer to a variable where the peeked element will be stored.
 * \return true if the operation was successful, false otherwise.
 */
bool stack_peek(const stack_t *stack, void *data);

/**
 * \brief Returns the number of elements in the stack.
 *
 * \param[in] stack Pointer to the stack.
 * \return Number of elements in the stack.
 */
size_t stack_size(const stack_t *stack);

/**
 * \brief Checks if the stack is empty.
 *
 * \param[in] stack Pointer to the stack.
 * \return true if the stack is empty, false otherwise.
 */
bool stack_empty(const stack_t *stack);

/**
 * \brief Checks if the stack is full.
 *
 * \param[in] stack Pointer to the stack.
 * \return true if the stack is full, false otherwise.
 */
bool stack_full(const stack_t *stack);

/**
 * \brief Clears all the elements from the stack.
 *
 * \param[in] stack Pointer to the stack.
 * \return true if the operation was successful, false otherwise.
 */
bool stack_clear(stack_t *stack);
