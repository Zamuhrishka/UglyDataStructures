/**
 * @file    test_queue_TestSuite3.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Queue. This list of tests
 *          checks that all methods are correct executes i.e. works with
 *          data as expected.
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
#define TEST_QUEUE_LEN 32
#define TEST_UNLIMITED_QUEUE 0
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
  TEST_MESSAGE("Queue Complex Tests");
}

void test_TestCase_0(void)
{
  TEST_MESSAGE("[QUEUE_TEST]: create");
  TEST_ASSERT_NOT_NULL(queue);
}

/**
 * @brief Tests the core functionality of the queue's `enqueue` and `dequeue` operations.
 *
 * This unit test is crafted to validate that the `queue_add` (enqueue) and `queue_get` (dequeue) methods
 * of the queue data structure work in harmony. It ensures that items added to the queue are correctly
 * dequeued in the order they were enqueued (FIFO - First In, First Out).
 *
 * If the dequeued items match the expected output, it indicates that the queue's enqueue and dequeue operations are
 * functioning correctly.
 */
void test_TestCase_1(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[QUEUE_TEST]: enqueue/dequeue");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(queue_add(queue, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(queue_get(queue, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected) / sizeof(uint32_t));
}

/**
 * @brief Tests the combination of the queue's `enqueue`, `peek`.
 *
 * This unit test is designed to validate the interplay between the `queue_add` (enqueue) and
 * `queue_peek` (peek) methods of the queue data structure.
 * It ensures that items added to the queue can be previewed using the peek operation without
 * removing them.
 */
void test_TestCase_2(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output = 0;

  TEST_MESSAGE("[QUEUE_TEST]: enqueue/peek");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(queue_add(queue, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(queue_peek(queue, &output));
    TEST_ASSERT_EQUAL_UINT32(expected[i], output);
    queue_get(queue, &output);
  }
}

/**
 * @brief Tests the queue's `size` operation in conjunction with the `enqueue` operation.
 *
 * This unit test focuses on validating the accuracy and reliability of the queue's `queue_size`
 * method, especially when items are being added to the queue. The goal is to ensure that the
 * reported size of the queue always matches the number of enqueued items, providing real-time
 * feedback on the queue's current occupancy.
 *
 * If the reported size of the queue accurately reflects the number of enqueued items at all times
 * throughout the process, it suggests that the queue's `size` and `enqueue` operations are working
 * correctly and in tandem.
 */
void test_TestCase_3(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[QUEUE_TEST]: size #1");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    size_t size = queue_size(queue);
    TEST_ASSERT_EQUAL_UINT32(i, size);
    queue_add(queue, &input[i]);
  }
}

/**
 * @brief Tests the accuracy of the queue's `size` operation during both enqueue and dequeue operations.
 *
 * This unit test examines the correct behavior of the queue's `queue_size` method as items are both
 * added to and removed from the queue. The main goal is to ensure that the size reported by the
 * queue accurately reflects the number of elements contained within it at every stage of the test.
 *
 * If the reported sizes at each stage match the expected values, and if the dequeued items match the `expected` array,
 * it indicates that the `size`, `add`, and `get` operations of the queue are functioning correctly.
 */
void test_TestCase_4(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[QUEUE_TEST]: size #2");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    size_t size = queue_size(queue);
    TEST_ASSERT_EQUAL_UINT32(i, size);
    queue_add(queue, &input[i]);
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint32_t); i++)
  {
    size_t size = queue_size(queue);
    TEST_ASSERT_EQUAL_UINT32(sizeof(input) / sizeof(uint32_t) - i, size);
    queue_get(queue, &output[i]);
  }
}

/**
 * @brief Tests the behavior of the `queue_add` method when attempting to enqueue to an unlimited queue.
 *
 * This unit test is designed to validate the behavior of the `queue_add` method when items are enqueued to a queue that
 * has been initialized as "unlimited" in terms of its capacity. The primary goal is to ensure that the queue can handle
 * a large number of enqueue operations beyond its nominal capacity without reporting any errors or issues.
 *
 * If all enqueue operations succeed and the queue can be properly deallocated, it indicates that the queue's add and
 * delete operations function as expected even for an "unlimited" queue.
 */
void test_TestCase_5(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: add to unlimited queue");

  queue_t* u_queue = queue_create(TEST_UNLIMITED_QUEUE, sizeof(uint32_t));

  for (size_t i = 0; i < TEST_QUEUE_LEN * 10; i++)
  {
    TEST_ASSERT_TRUE(queue_add(u_queue, &data));
  }

  queue_delete(&u_queue);
}
