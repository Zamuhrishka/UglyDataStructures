/**
 * @file    test_queue_TestSuite2.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of unit tests for Ring Buffer which checks the corner cases.
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
#include "structs/rb/ring_buffer.h"

//_____ C O N F I G S  ________________________________________________________
//_____ D E F I N I T I O N S _________________________________________________
#define RB_MAX_SIZE 32
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static ring_buffer_t* rb = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  rb = rb_create(RB_MAX_SIZE, sizeof(uint32_t));
}

void tearDown(void)
{
  rb_delete(&rb);
}

void test_init(void)
{
  TEST_MESSAGE("RingBuffer Limits Tests");
}

void test_TestCase_0(void)
{
  TEST_MESSAGE("[RB_TEST]: create");
  TEST_ASSERT_NOT_NULL(rb);
}

/**
 * @brief Tests the behavior of the `rb_get` method when attempting to retrieve from an empty ring buffer.
 *
 * This unit test specifically evaluates the corner case scenario where the `rb_get` method is invoked
 * on an empty ring buffer. The expected behavior in this situation is for the `rb_get` method to return
 * `false`, indicating that there's no data to retrieve.
 */
void test_TestCase_1(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: get empty");
  TEST_ASSERT_FALSE(rb_get(rb, &data));
}

/**
 * @brief Tests the behavior of the `rb_peek` method when attempting to view the top element of an empty ring buffer.
 *
 * This unit test specifically evaluates the corner case scenario where the `rb_peek` method is invoked
 * on an empty ring buffer. The expected behavior in this situation is for the `rb_peek` method to return
 * `false`, indicating that there's no data to view.
 */
void test_TestCase_2(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: peek empty");
  TEST_ASSERT_FALSE(rb_peek(rb, &data));
}

/**
 * @brief Tests the behavior of the `rb_add` method when attempting to add an element to a full ring buffer.
 *
 * This unit test specifically evaluates the corner case scenario where the `rb_add` method is invoked
 * on a full ring buffer. The expected behavior in this situation is for the `rb_add` method to return
 * `false`, indicating that there's no space to add more data.
 */
void test_TestCase_3(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: add full");
  for (size_t i = 0; i < RB_MAX_SIZE; i++)
  {
    rb_add(rb, &data);
  }

  TEST_ASSERT_FALSE(rb_add(rb, &data));
}

/**
 * @brief Tests the behavior of the `rb_size` method when checking the size of an empty ring buffer.
 *
 * This unit test is designed to validate the correct operation of the `rb_size` method, specifically
 * when the ring buffer is empty. The expected behavior is for the method to return a size of `0`, indicating
 * that there are no elements in the buffer.
 */
void test_TestCase_4(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: size empty");
  size_t size = rb_size(rb);
  TEST_ASSERT_EQUAL_UINT32(0, size);
}

/**
 * @brief Tests the behavior of the `rb_create` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_create` method, specifically
 * when it is provided with an invalid size argument of `0`.
 */
void test_TestCase_5(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[RB_TEST]: `create` function invalid argument");

  Try
  {
    ring_buffer_t* q = rb_create(RB_MAX_SIZE, 0);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_delete` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_delete` method, specifically
 * when it is provided with an invalid rb double pointer argument of `NULL`.
 */
void test_TestCase_6(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[RB_TEST]: `delete` function invalid argument");

  Try
  {
    rb_delete(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_empty` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_empty` method, specifically
 * when it is provided with an invalid rb pointer argument of `NULL`.
 */
void test_TestCase_7(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[RB_TEST]: `empty` function invalid argument");

  Try
  {
    bool res = rb_is_empty(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_add` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_add` method, specifically
 * when it is provided with an invalid rb pointer argument of `NULL`.
 */
void test_TestCase_8(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: `add` function invalid argument: rb");

  Try
  {
    bool res = rb_add(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_add` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_add` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_9(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[RB_TEST]: `add` function invalid argument: data");

  Try
  {
    bool res = rb_add(rb, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_get` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_get` method, specifically
 * when it is provided with an invalid rb pointer argument of `NULL`.
 */
void test_TestCase_10(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: `get` function invalid argument: rb");

  Try
  {
    bool res = rb_get(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_get` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_get` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_11(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[RB_TEST]: `get` function invalid argument: data");

  Try
  {
    bool res = rb_get(rb, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_peek` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_peek` method, specifically
 * when it is provided with an invalid rb pointer argument of `NULL`.
 */
void test_TestCase_12(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[RB_TEST]: `peek` function invalid argument: rb");

  Try
  {
    bool res = rb_peek(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_peek` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_peek` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_13(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[RB_TEST]: `peek` function invalid argument: data");

  Try
  {
    bool res = rb_peek(rb, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_size` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_size` method, specifically
 * when it is provided with an invalid rb pointer argument of `NULL`.
 */
void test_TestCase_14(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[RB_TEST]: `size` function invalid argument: rb");

  Try
  {
    uint16_t data = rb_size(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `rb_clear` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `rb_clear` method, specifically
 * when it is provided with an invalid rb pointer argument of `NULL`.
 */
void test_TestCase_15(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[RB_TEST]: `clear` function invalid argument: rb");

  Try
  {
    bool res = rb_clear(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}
