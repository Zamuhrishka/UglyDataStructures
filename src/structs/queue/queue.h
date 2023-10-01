/**
 * \file    queue.h
 * \author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * \brief   Implementation of a generic queue data structure.
 * \date    2023-01-14
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include "core/container.h"
#include "structs/ds.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
typedef ds_t queue_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes and returns a new queue.
 *
 * \param[in] size The size in elements of this queue or 0 if you won`t limit size of queue.
 * \param[in] esize The size in bytes of the single element that this queue will store.
 *
 * \note if the `size` argument equals 0 then the queue would be unlimited by size.
 *
 * \return Pointer to the newly created queue or NULL.
 */
queue_t *queue_create(size_t size, size_t esize);

/**
 * \brief Frees up the memory associated with the queue.
 *
 * \param[in] queue Double pointer to the queue to be deleted.
 */
void queue_delete(queue_t **queue);

/**
 * \brief Checks if the queue is empty.
 *
 * \param[in] queue Pointer to the queue.
 * \return true if the queue is empty, false otherwise.
 */
bool queue_empty(const queue_t *queue);

/**
 * \brief Checks if the queue is full.
 *
 * \param[in] queue Pointer to the queue.
 * \return true if the queue is full, false otherwise.
 */
bool queue_full(const queue_t *queue);

/**
 * \brief Removes an element from the queue and returns it.
 *
 * \param[in] queue Pointer to the queue.
 * \param[out] data Pointer to a variable where the dequeued element will be stored.
 * \return true if the operation was successful, false otherwise.
 */
bool queue_get(queue_t *queue, void *data);

/**
 * \brief Adds an element to the queue.
 *
 * \param[in] queue Pointer to the queue.
 * \param[in] data Pointer to the variable to be enqueued.
 * \return true if the operation was successful, false otherwise.
 */
bool queue_add(queue_t *queue, const void *data);

/**
 * \brief Retrieves the element from the queue without removing it.
 *
 * \param queue[in] Pointer to the queue.
 * \param data[in] Pointer to a variable where the peeked element will be stored.
 * \return true if the operation was successful, false otherwise.
 */
bool queue_peek(const queue_t *queue, void *data);

/**
 * \brief Returns the number of elements in the queue.
 *
 * \param queue[in] Pointer to the queue.
 * \return Number of elements in the queue.
 */
size_t queue_size(const queue_t *queue);

/**
 * \brief Clears all the elements from the queue.
 *
 * \param queue[in] Pointer to the queue.
 * \return true if the operation was successful, false otherwise.
 */
bool queue_clear(queue_t *queue);
