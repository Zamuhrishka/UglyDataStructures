/**
 * @file    test_stack_TestSuite.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of corner case unit tests for Stack.
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
#include "structs/stack/stack.h"

//_____ C O N F I G S  ________________________________________________________
#define TEST_STACK_LEN 10
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static stack_t* stack = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________
void setUp(void)
{
  stack = stack_create(TEST_STACK_LEN, sizeof(uint32_t));
}

void tearDown(void)
{
  stack_delete(&stack);
}

void test_init(void)
{
  TEST_MESSAGE("Stack Corner Cases Tests");
}

/**
 * @brief Tests the behavior of the `stack_pop` method when attempting to pop from an empty stack.
 *
 * This unit test specifically evaluates the corner case scenario where the `stack_pop` method is invoked
 * on an empty stack. The expected behavior in this situation is for the `stack_pop` method to return
 * `false`, indicating that there's no data to pop.
 */
void test_TestCase_1(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[STACK_TEST]: pop empty");
  TEST_ASSERT_FALSE(stack_pop(stack, &data));
}

/**
 * @brief Tests the behavior of the `stack_push` method when attempting to push to a full stack.
 *
 * This unit test specifically evaluates the corner case scenario where the `stack_push` method is invoked
 * on a full stack. The expected behavior in this situation is for the `stack_push` method to return
 * `false`, indicating that there's no space to push data.
 */
void test_TestCase_2(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[STACK_TEST]: push full");
  for (size_t i = 0; i < TEST_STACK_LEN; i++)
  {
    TEST_ASSERT_TRUE(stack_push(stack, &data));
  }
  TEST_ASSERT_FALSE(stack_push(stack, &data));
}

/**
 * @brief Tests the behavior of the `stack_size` method when checking the size of an empty stack.
 *
 * This unit test is designed to validate the correct operation of the `stack_size` method, specifically
 * when the stack is empty. The expected behavior is for the method to return a size of `0`, indicating
 * that there are no elements in the stack.
 */
void test_TestCase_3(void)
{
  TEST_MESSAGE("[STACK_TEST]: size for empty");
  size_t size = stack_size(stack);
  TEST_ASSERT_EQUAL_UINT32(0, size);
}

/**
 * @brief Tests the behavior of the `stack_create` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_create` method, specifically
 * when it is provided with an invalid size argument of `0`.
 */
void test_TestCase_4(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[STACK_TEST]: `create` function invalid argument");
  Try
  {
    stack_t* s = stack_create(TEST_STACK_LEN, 0);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_delete` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_delete` method, specifically
 * when it is provided with an invalid stack double pointer argument of `NULL`.
 */
void test_TestCase_5(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[STACK_TEST]: `delete` function invalid argument");
  Try
  {
    stack_delete(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_empty` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_empty` method, specifically
 * when it is provided with an invalid stack pointer argument of `NULL`.
 */
void test_TestCase_6(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[STACK_TEST]: `empty` function invalid argument");
  Try
  {
    bool res = stack_empty(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_add` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_add` method, specifically
 * when it is provided with an invalid stack pointer argument of `NULL`.
 */
void test_TestCase_7(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[STACK_TEST]: `push` function invalid argument: stack");
  Try
  {
    bool res = stack_push(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_add` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_add` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_8(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[STACK_TEST]: `push` function invalid argument: data");
  Try
  {
    bool res = stack_push(stack, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_get` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_get` method, specifically
 * when it is provided with an invalid stack pointer argument of `NULL`.
 */
void test_TestCase_9(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[STACK_TEST]: `pop` function invalid argument: stack");
  Try
  {
    bool res = stack_pop(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_get` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_get` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_10(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[STACK_TEST]: `pop` function invalid argument: data");
  Try
  {
    bool res = stack_pop(stack, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_peek` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_peek` method, specifically
 * when it is provided with an invalid stack pointer argument of `NULL`.
 */
void test_TestCase_11(void)
{
  CEXCEPTION_T e;
  uint32_t data = 0x55;

  TEST_MESSAGE("[STACK_TEST]: `peek` function invalid argument: stack");
  Try
  {
    bool res = stack_peek(NULL, &data);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_peek` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_peek` method, specifically
 * when it is provided with an invalid data pointer argument of `NULL`.
 */
void test_TestCase_12(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[STACK_TEST]: `peek` function invalid argument: data");
  Try
  {
    bool res = stack_peek(stack, NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_size` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_size` method, specifically
 * when it is provided with an invalid stack pointer argument of `NULL`.
 */
void test_TestCase_13(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[STACK_TEST]: `size` function invalid argument: stack");
  Try
  {
    size_t size = stack_size(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}

/**
 * @brief Tests the behavior of the `stack_clear` method when provided with an invalid argument.
 *
 * This unit test is designed to validate the correct error handling of the `stack_clear` method, specifically
 * when it is provided with an invalid stack pointer argument of `NULL`.
 */
void test_TestCase_14(void)
{
  CEXCEPTION_T e;

  TEST_MESSAGE("[STACK_TEST]: `clear` function invalid argument: stack");

  Try
  {
    bool res = stack_clear(NULL);
    TEST_FAIL_MESSAGE("Should have thrown!");
  }
  Catch(e)
  {
    TEST_ASSERT_EQUAL(0, e);
  }
}
