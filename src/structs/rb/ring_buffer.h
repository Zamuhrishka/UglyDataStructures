/**
 * @file ring_buffer.h
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-18
 */

#pragma once

//_____ I N C L U D E S _______________________________________________________
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "structs/ds.h"
//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
typedef ds_t ring_buffer_t;
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
/**
 * \brief Initializes and returns a new ring buffer.
 *
 * \param[in] size The size in elements of this ring buffer.
 * \param[in] esize The size in bytes of the single element that this ring buffer will store.
 *
 * \return Pointer to the newly created ring buffer or NULL.
 */
ring_buffer_t *rb_create(size_t size, size_t esize);

/**
 * \brief Frees up the memory associated with the ring buffer.
 *
 * \param[in] rb Double pointer to the ring buffer to be deleted.
 */
void rb_delete(ring_buffer_t **rb);

/**
 * \brief Checks if the ring buffer is empty.
 *
 * \param[in] rb Pointer to the ring buffer.
 * \return true if the ring buffer is empty, false otherwise.
 */
bool rb_is_empty(const ring_buffer_t *rb);

/**
 * \brief Checks if the ring buffer is full.
 *
 * \param[in] rb Pointer to the ring buffer.
 * \return true if the ring buffer is full, false otherwise.
 */
bool rb_is_full(const ring_buffer_t *rb);

/**
 * \brief Adds an element to the ring buffer.
 *
 * \param[in] rb Pointer to the ring buffer.
 * \param[in] data Pointer to the variable to be added.
 * \return true if the operation was successful, false otherwise.
 */
bool rb_add(ring_buffer_t *rb, const void *data);

/**
 * \brief Removes an element from the ring buffer and returns it.
 *
 * \param[in] rb Pointer to the ring buffer.
 * \param[out] data Pointer to a variable where the retrieved element will be stored.
 * \return true if the operation was successful, false otherwise.
 */
bool rb_get(ring_buffer_t *rb, void *data);

/**
 * \brief Retrieves an element from the ring buffer without removing it.
 *
 * \param[in] rb Pointer to the ring buffer.
 * \param[out] data Pointer to a variable where the peeked element will be stored.
 * \return true if the operation was successful, false otherwise.
 */
bool rb_peek(const ring_buffer_t *rb, void *data);

/**
 * \brief Returns the number of elements in the ring buffer.
 *
 * \param[in] rb Pointer to the ring buffer.
 * \return Number of elements in the ring buffer.
 */
size_t rb_size(const ring_buffer_t *rb);

/**
 * \brief Clears all the elements from the ring buffer.
 *
 * \param[in] rb Pointer to the ring buffer.
 * \return true if the operation was successful, false otherwise.
 */
bool rb_clear(ring_buffer_t *rb);
