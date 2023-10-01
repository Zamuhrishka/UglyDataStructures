/**
 * @file test_ll.c
 * @author Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief
 * @date 2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "interface/allocator_if.h"
#include "structs/rb/ring_buffer.h"

//_____ C O N F I G S  ________________________________________________________
#define TEST_RB_LEN 32
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static ring_buffer_t* rb = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  rb = rb_create(TEST_RB_LEN, sizeof(uint32_t));
}

void tearDown(void)
{
  rb_delete(&rb);
}

void test_init(void)
{
  TEST_MESSAGE("RingBuffer Simple Tests");
}

/**
 * @brief Test case to verify stack creation.
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[RB_TEST]: create");
  TEST_ASSERT_NOT_NULL(rb);
}

/**
 * @brief Tests the behavior of the `rb_add` method when adding an element to the ring buffer.
 *
 * This unit test specifically checks if the `rb_add` function can successfully add a data element
 * to the ring buffer. The expected behavior is for the `rb_add` method to return `true`, indicating
 * that the data has been added successfully.
 */
void test_TestCase_1(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: add");
  TEST_ASSERT_TRUE(rb_add(rb, &data));
}

/**
 * @brief Tests the behavior of the `rb_is_empty` method for both empty and non-empty ring buffers.
 *
 * This unit test first checks if a newly initialized ring buffer is empty. After adding an element
 * to the ring buffer, it then checks if the buffer is no longer empty. The expected behavior is
 * for the `rb_is_empty` method to return `true` when the buffer is empty and `false` when it is not.
 */
void test_TestCase_2(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: is empty");
  TEST_ASSERT_TRUE(rb_is_empty(rb));
  rb_add(rb, &data);
  TEST_ASSERT_FALSE(rb_is_empty(rb));
}

/**
 * @brief Tests the behavior of the `rb_size` method after adding an element to the ring buffer.
 *
 * This unit test adds a data element to the ring buffer and then checks the size of the buffer using
 * the `rb_size` method. The expected behavior is for the `rb_size` method to return `1`, indicating
 * that there is one element in the buffer.
 */
void test_TestCase_3(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: size");
  rb_add(rb, &data);
  size_t size = rb_size(rb);
  TEST_ASSERT_EQUAL_UINT32(1, size);
}

/**
 * @brief Tests the behavior of the `rb_get` method when retrieving an element from the ring buffer.
 *
 * This unit test adds a data element to the ring buffer and then tries to retrieve it using the
 * `rb_get` method. The expected behavior is for the `rb_get` method to return `true`, indicating
 * that an element has been successfully retrieved from the buffer.
 */
void test_TestCase_4(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: get");
  rb_add(rb, &data);
  TEST_ASSERT_TRUE(rb_get(rb, &data));
}

/**
 * @brief Tests the behavior of the `rb_peek` method when viewing the top element of the ring buffer without removal.
 *
 * This unit test adds a data element to the ring buffer and then tries to view the top element using
 * the `rb_peek` method. The expected behavior is for the `rb_peek` method to return `true`, indicating
 * that the top element can be successfully viewed without removal.
 */
void test_TestCase_5(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: peek");
  rb_add(rb, &data);
  TEST_ASSERT_TRUE(rb_peek(rb, &data));
}
