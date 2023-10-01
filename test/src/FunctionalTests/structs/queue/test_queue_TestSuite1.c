/**
 * @file    test_queue_TestSuite1.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Queue. This list of tests just
 *          checks that all methods are executes but not checks the
 *          valid execution.
 * @date    2023-01-14
 */

//_____ I N C L U D E S _______________________________________________________
#include "unity.h"

#include <stdbool.h>
#include <stdint.h>

#include "core/container.h"
#include "core/linked_list/linked_list.h"
#include "core/vector/vector.h"
#include "interface/allocator_if.h"
#include "structs/queue/queue.h"

//_____ C O N F I G S  ________________________________________________________
#define TEST_QUEUE_LEN 10
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static queue_t* queue = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  queue = queue_create(TEST_QUEUE_LEN, sizeof(uint32_t));
}

void tearDown(void)
{
  queue_delete(&queue);
}

void test_init(void)
{
  TEST_MESSAGE("Queue Simple Tests");
}

/**
 * \brief Test case to verify creation
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[QUEUE_TEST]: create");
  TEST_ASSERT_NOT_NULL(queue);
}

/**
 * @brief Tests the functionality of the `add` method for a queue.
 *
 * This unit test focuses on verifying the `enqueue` operation of a queue. It tries to
 * enqueue a single data item into the queue and checks the return value for success.
 *
 * The main functionality being tested is the ability of the queue to accept a new item
 * for insertion (enqueue operation) and indicate the success of this operation.
 */
void test_TestCase_1(void)
{
  uint32_t data = 0x55;
  TEST_MESSAGE("[QUEUE_TEST]: add");
  TEST_ASSERT_TRUE(queue_add(queue, &data));
}

/**
 * @brief Tests the functionality of the `queue_empty` method for a queue.
 *
 * This unit test aims to validate the correct operation of the `queue_empty` method.
 * The test checks whether the queue correctly reports its empty status before and
 * after an item has been enqueued.
 */
void test_TestCase_2(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: is empty");
  TEST_ASSERT_TRUE(queue_empty(queue));
  queue_add(queue, &data);
  TEST_ASSERT_FALSE(queue_empty(queue));
}

/**
 * @brief Tests the functionality of the `queue_full` method for a queue.
 *
 * This unit test aims to validate the correct operation of the `queue_full` method.
 * The test checks whether the queue correctly reports its full status before and
 * after an item has been full enqueued.
 */
void test_TestCase_3(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: is full");
  TEST_ASSERT_FALSE(queue_full(queue));

  for (size_t i = 0; i < TEST_QUEUE_LEN; i++)
  {
    queue_add(queue, &data);
  }

  TEST_ASSERT_TRUE(queue_full(queue));
}

/**
 * @brief Tests the functionality of the `queue_size` method for a queue.
 *
 * This unit test is designed to validate the correct operation of the `queue_size` method.
 * The primary objective is to confirm that the queue correctly reports its size after an item
 * has been enqueued.
 */
void test_TestCase_4(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: size");
  queue_add(queue, &data);
  size_t size = queue_size(queue);
  TEST_ASSERT_EQUAL_UINT32(1, size);
}

/**
 * @brief Tests the functionality of the `queue_get` (dequeue) method for a queue.
 *
 * This unit test aims to validate the correct operation of the `queue_get` method, which is responsible for dequeuing
 * items. The primary objective is to ensure that the queue can successfully dequeue an item that has been previously
 * enqueued.
 */
void test_TestCase_5(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: get");
  queue_add(queue, &data);
  TEST_ASSERT_TRUE(queue_get(queue, &data));
}

/**
 * @brief Tests the functionality of the `queue_peek` method for a queue.
 *
 * This unit test is designed to verify the correct operation of the `queue_peek` method. The method's primary
 * responsibility is to allow users to view the front item of the queue without removing it. The test aims to confirm
 * that the method can successfully retrieve the front item and indicate the operation's success without modifying the
 * queue's state.
 */
void test_TestCase_6(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: peek");
  queue_add(queue, &data);
  TEST_ASSERT_TRUE(queue_peek(queue, &data));
}

/**
 * @brief Tests the functionality of the `queue_clear` method for a queue.
 *
 * This unit test is designed to validate the correct operation of the `queue_clear` method, which is responsible for
 * emptying the entire queue, removing all its elements. The test aims to ensure that after invoking the `queue_clear`
 * method, the queue becomes empty and its size is set to zero.
 */
void test_TestCase_7(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[CONTAINER_TEST]: clear");

  queue_add(queue, &data);
  size_t size = queue_size(queue);
  TEST_ASSERT_EQUAL_UINT8(1, size);
  TEST_ASSERT_TRUE(queue_clear(queue));
  size = queue_size(queue);
  TEST_ASSERT_EQUAL_UINT8(0, size);
}
