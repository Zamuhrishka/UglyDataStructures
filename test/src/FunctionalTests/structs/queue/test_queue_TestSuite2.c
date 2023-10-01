/**
 * @file    test_queue_TestSuite2.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of unit tests for Queue which checks the corner cases.
 * @date    2023-01-14
 */
//_____ I N C L U D E S _______________________________________________________
#include "CException.h"
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
  TEST_MESSAGE("Queue Corner Cases Tests");
}

/**
 * @brief Tests the behavior of the `queue_get` method when attempting to dequeue from an empty queue.
 *
 * This unit test specifically evaluates the corner case scenario where the `queue_get` method is invoked
 * on an empty queue. The expected behavior in this situation is for the `queue_get` method to return
 * `false`, indicating that there's no data to dequeue.
 */
void test_TestCase_1(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: get empty");
  TEST_ASSERT_FALSE(queue_get(queue, &data));
}

/**
 * @brief Tests the behavior of the `queue_add` method when attempting to enqueue to an full queue.
 *
 * This unit test specifically evaluates the corner case scenario where the `queue_add` method is invoked
 * on an full queue. The expected behavior in this situation is for the `queue_add` method to return
 * `false`, indicating that there's no data to enqueue.
 */
void test_TestCase_2(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: add full");

  for (size_t i = 0; i < TEST_QUEUE_LEN; i++)
  {
    TEST_ASSERT_TRUE(queue_add(queue, &data));
  }

  TEST_ASSERT_FALSE(queue_add(queue, &data));
}

/**
 * @brief Tests the behavior of the `queue_size` method when checking the size of an empty queue.
 *
 * This unit test is designed to validate the correct operation of the `queue_size` method, specifically
 * when the queue is empty. The expected behavior is for the method to return a size of `0`, indicating
 * that there are no elements in the queue.
 */
void test_TestCase_3(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: size for empty");
  size_t size = queue_size(queue);
  TEST_ASSERT_EQUAL_UINT32(0, size);
}

/**
 * @brief Tests the behavior of the `queue_create` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_create` method, specifically
 * when it is provided with an invalid size argument of `0`.
 */
void test_TestCase_4(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[QUEUE_TEST]: `create` function invalid argument");

  Try
  {
    queue_t* q = queue_create(TEST_QUEUE_LEN, 0);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_delete` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_delete` method, specifically
 * when it is provided with an invalid queue double pointer argument of `NULL`.
 */
void test_TestCase_5(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[QUEUE_TEST]: `delete` function invalid argument");

  Try
  {
    queue_delete(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_empty` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_empty` method, specifically
 * when it is provided with an invalid queue pointer argument of `NULL`.
 */
void test_TestCase_6(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[QUEUE_TEST]: `empty` function invalid argument");

  Try
  {
    bool res = queue_empty(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_add` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_add` method, specifically
 * when it is provided with an invalid queue pointer argument of `NULL`.
 */
void test_TestCase_7(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: `add` function invalid argument: queue");

  Try
  {
    bool res = queue_add(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_add` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_add` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_8(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[QUEUE_TEST]: `add` function invalid argument: data");

  Try
  {
    bool res = queue_add(queue, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_get` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_get` method, specifically
 * when it is provided with an invalid queue pointer argument of `NULL`.
 */
void test_TestCase_9(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: `get` function invalid argument: queue");

  Try
  {
    bool res = queue_get(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_get` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_get` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_10(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[QUEUE_TEST]: `get` function invalid argument: data");

  Try
  {
    bool res = queue_get(queue, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_peek` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_peek` method, specifically
 * when it is provided with an invalid queue pointer argument of `NULL`.
 */
void test_TestCase_11(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[QUEUE_TEST]: `peek` function invalid argument: queue");

  Try
  {
    bool res = queue_peek(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_peek` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_peek` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_12(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[QUEUE_TEST]: `peek` function invalid argument: data");

  Try
  {
    bool res = queue_peek(queue, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_size` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_size` method, specifically
 * when it is provided with an invalid queue pointer argument of `NULL`.
 */
void test_TestCase_13(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[QUEUE_TEST]: `size` function invalid argument: queue");

  Try
  {
    uint16_t data = queue_size(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `queue_clear` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `queue_clear` method, specifically
 * when it is provided with an invalid queue pointer argument of `NULL`.
 */
void test_TestCase_14(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[QUEUE_TEST]: `clear` function invalid argument: queue");

  Try
  {
    bool res = queue_clear(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}
