/**
 * @file    test_stack_TestSuite3.c
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
#include "structs/stack/stack.h"

//_____ C O N F I G S  ________________________________________________________
#define TEST_STACK_LEN 32
#define TEST_UNLIMITED_STACK 0
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
  TEST_MESSAGE("Stack Complex Tests");
}

void test_TestCase_0(void)
{
  TEST_MESSAGE("[STACK_TEST]: create");
  TEST_ASSERT_NOT_NULL(stack);
}

/**
 * @brief Tests the push and pop operations of the stack to ensure LIFO (Last-In-First-Out) behavior.
 *
 * This unit test focuses on the fundamental principle of a stack, which is LIFO.
 * It pushes a series of data elements onto the stack in a defined order and then
 * pops them off, expecting the reverse order due to the LIFO property of the stack.
 */
void test_TestCase_1(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {1,     562610, 907163, 90197, 10021, 99999, 771535, 77777,
                         54519, 55555,  66,     33333, 67793, 11111, 93274};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[STACK_TEST]: push/pop");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(stack_push(stack, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(stack_pop(stack, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, sizeof(expected) / sizeof(uint32_t));
}

/**
 * @brief Tests the push and peek operations of the stack to ensure accurate retrieval of the top element.
 *
 * This unit test focuses on the behavior of the stack when using the `peek` operation
 * in conjunction with the `push` operation. The primary objective is to ensure that the
 * `peek` operation always retrieves the last pushed (top) element without removing it
 * from the stack, thereby preserving the LIFO (Last-In-First-Out) principle of the stack.
 *
 * By the end of this process, this test validates both the correct LIFO behavior of the
 * stack and the correct functioning of the `peek` operation.
 */
void test_TestCase_2(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {1,     562610, 907163, 90197, 10021, 99999, 771535, 77777,
                         54519, 55555,  66,     33333, 67793, 11111, 93274};
  uint32_t output = 0;

  TEST_MESSAGE("[STACK_TEST]: push/peek");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(stack_push(stack, &input[i]));
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint32_t); i++)
  {
    TEST_ASSERT_TRUE(stack_peek(stack, &output));
    TEST_ASSERT_EQUAL_UINT32(expected[i], output);
    stack_pop(stack, &output);
  }
}

/**
 * @brief Tests the accuracy of the stack's size property during push and peek operations.
 *
 * This unit test focuses on ensuring that the stack correctly updates and reports its size
 * during successive push and peek operations. By verifying the size of the stack at each
 * step, we can be confident in the stack's internal management of its elements.
 *
 * Steps:
 * 1. An array of input values is defined, representing the sequence of values to be pushed
 *    onto the stack.
 * 2. An array of expected values is defined, which should match the input values as the
 *    stack is a LIFO structure and the peek operation does not remove elements.
 * 3. For each value in the input array:
 *    a. The current size of the stack is obtained and verified to match the current iteration
 *       index. This ensures that the size property accurately reflects the number of items
 *       on the stack.
 *    b. The current input value is pushed onto the stack.
 * 4. For each expected value:
 *    a. The current size of the stack is obtained and should remain constant (equal to the
 *       total number of input values) since the peek operation does not modify the stack.
 *    b. The `peek` operation is used to retrieve the current top value of the stack.
 *
 * By the end of this process, this test validates the stack's size reporting mechanism and
 * ensures that the `peek` operation does not affect the reported size.
 */
void test_TestCase_3(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[STACK_TEST]: size #1");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    size_t size = stack_size(stack);
    TEST_ASSERT_EQUAL_UINT32(i, size);
    stack_push(stack, &input[i]);
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint32_t); i++)
  {
    size_t size = stack_size(stack);
    TEST_ASSERT_EQUAL_UINT32(sizeof(input) / sizeof(uint32_t), size);
    stack_peek(stack, &output[i]);
  }
}

/**
 * @brief Tests the accuracy of the stack's size property during push and pop operations.
 *
 * This unit test emphasizes the correctness of the stack's size reporting mechanism when
 * items are pushed onto and popped off the stack. The goal is to ensure the internal
 * management of the stack's size is consistent with the number of elements it holds.
 *
 * At the conclusion of this test, we have effectively validated the stack's size reporting
 * mechanism during both push and pop operations, ensuring that the stack's size property
 * is updated correctly and consistently.
 */
void test_TestCase_4(void)
{
  uint32_t input[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                      771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[] = {93274,  11111, 67793, 33333, 66,     55555,  54519, 77777,
                         771535, 99999, 10021, 90197, 907163, 562610, 1};
  uint32_t output[sizeof(expected) / sizeof(uint32_t)] = {};

  TEST_MESSAGE("[STACK_TEST]: size #2");

  for (size_t i = 0; i < sizeof(input) / sizeof(uint32_t); i++)
  {
    size_t size = stack_size(stack);
    TEST_ASSERT_EQUAL_UINT32(i, size);
    stack_push(stack, &input[i]);
  }

  for (size_t i = 0; i < sizeof(expected) / sizeof(uint32_t); i++)
  {
    size_t size = stack_size(stack);
    TEST_ASSERT_EQUAL_UINT32(sizeof(input) / sizeof(uint32_t) - i, size);
    stack_pop(stack, &output[i]);
  }
}

/**
 * @brief Tests the behavior of the `stack_add` method when attempting to stack to an unlimited stack.
 *
 * This unit test is designed to validate the behavior of the `stack_add` method when items are stack to a stack that
 * has been initialized as "unlimited" in terms of its capacity. The primary goal is to ensure that the stack can handle
 * a large number of stack operations beyond its nominal capacity without reporting any errors or issues.
 *
 * If all stack operations succeed and the stack can be properly deallocated, it indicates that the stack's add and
 * delete operations function as expected even for an "unlimited" stack.
 */
void test_TestCase_5(void)
{
  uint16_t data = 0x55;

  TEST_MESSAGE("[STACK_TEST]: add to unlimited stack");

  stack_t* u_stack = stack_create(TEST_UNLIMITED_STACK, sizeof(uint32_t));

  for (size_t i = 0; i < TEST_STACK_LEN * 10; i++)
  {
    TEST_ASSERT_TRUE(stack_push(u_stack, &data));
  }

  stack_delete(&u_stack);
}
