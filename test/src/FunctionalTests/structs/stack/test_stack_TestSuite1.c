/**
 * @file    test_stack_TestSuite1.c
 * @author  Aleksander Kovalchuk (aliaksander.kavalchuk@gmail.com)
 * @brief   Set of simple unit tests for Stack.
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
#define TEST_STACK_LEN 10
//_____ D E F I N I T I O N S _________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E S _____________________________________________________
static stack_t* stack = NULL;
//_____ P R I V A T E  F U N C T I O N S_______________________________________
//_____ P U B L I C  F U N C T I O N S_________________________________________

/**
 * @brief Setup function that initializes a new stack before each test case.
 */
void setUp(void)
{
  stack = stack_create(sizeof(uint32_t), TEST_STACK_LEN);
}

/**
 * @brief Teardown function that deletes the stack after each test case.
 */
void tearDown(void)
{
  stack_delete(&stack);
}

/**
 * @brief Initial test message.
 */
void test_init(void)
{
  TEST_MESSAGE("Stack Simple Tests");
}

/**
 * @brief Test case to verify stack creation.
 */
void test_TestCase_0(void)
{
  TEST_MESSAGE("[STACK_TEST]: create");
  TEST_ASSERT_NOT_NULL(stack);
}

/**
 * @brief Tests the functionality of the `push` method for a stack.
 *
 * This unit test focuses on verifying the `push` operation of a stack. It tries to
 * push a single data item into the stack and checks the return value for success.
 */
void test_TestCase_1(void)
{
  uint32_t data = 0x55;
  TEST_MESSAGE("[STACK_TEST]: push");
  TEST_ASSERT_TRUE(stack_push(stack, &data));
}

/**
 * @brief Tests the functionality of the `stack_empty` method for a stack.
 *
 * This unit test aims to validate the correct operation of the `stack_empty` method.
 * The test checks whether the stack correctly reports its empty status before and
 * after an item has been pushed.
 */
void test_TestCase_2(void)
{
  uint32_t data = 0x55;
  TEST_MESSAGE("[STACK_TEST]: empty");
  TEST_ASSERT_TRUE(stack_empty(stack));
  stack_push(stack, &data);
  TEST_ASSERT_FALSE(stack_empty(stack));
}

/**
 * @brief Tests the functionality of the `stack_size` method for a stack.
 *
 * This unit test is designed to validate the correct operation of the `stack_size` method.
 * The primary objective is to confirm that the stack correctly reports its size after an item
 * has been pushed.
 */
void test_TestCase_3(void)
{
  uint32_t data = 0x55;
  TEST_MESSAGE("[STACK_TEST]: size");
  stack_push(stack, &data);
  size_t size = stack_size(stack);
  TEST_ASSERT_EQUAL_UINT32(1, size);
}

/**
 * @brief Tests the functionality of the `pop` method for a stack.
 *
 * This unit test aims to validate the correct operation of the `pop` method, which is responsible for popping
 * items from the stack. The primary objective is to ensure that the stack can successfully pop an item that has been
 * previously pushed.
 */
void test_TestCase_4(void)
{
  uint32_t data = 0x55;
  TEST_MESSAGE("[STACK_TEST]: pop");
  stack_push(stack, &data);
  TEST_ASSERT_TRUE(stack_pop(stack, &data));
}

/**
 * @brief Tests the functionality of the `stack_peek` method for a stack.
 *
 * This unit test is designed to verify the correct operation of the `stack_peek` method. The method's primary
 * responsibility is to allow users to view the top item of the stack without removing it. The test aims to confirm
 * that the method can successfully retrieve the top item and indicate the operation's success without modifying the
 * stack's state.
 */
void test_TestCase_5(void)
{
  uint32_t data = 0x55;
  TEST_MESSAGE("[STACK_TEST]: peek");
  stack_push(stack, &data);
  TEST_ASSERT_TRUE(stack_peek(stack, &data));
}

/**
 * @brief Tests the functionality of the `stack_full` method for a stack.
 *
 * This unit test aims to validate the correct operation of the `stack_full` method.
 * The test checks whether the stack correctly reports its full status before and
 * after it has been completely filled.
 */
void test_TestCase_6(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[STACK_TEST]: full");
  TEST_ASSERT_FALSE(stack_full(stack));

  for (size_t i = 0; i < TEST_STACK_LEN; i++)
  {
    stack_push(stack, &data);
  }

  TEST_ASSERT_TRUE(stack_full(stack));
}

/**
 * @brief Tests the functionality of the `stack_clear` method for a stack.
 *
 * This unit test is designed to validate the correct operation of the `stack_clear` method, which is responsible for
 * emptying the entire stack, removing all its elements. The test aims to ensure that after invoking the `stack_clear`
 * method, the stack becomes empty and its size is set to zero.
 */
void test_TestCase_7(void)
{
  uint32_t data = 0x55;

  TEST_MESSAGE("[STACK_TEST]: clear");

  stack_push(stack, &data);
  size_t size = stack_size(stack);
  TEST_ASSERT_EQUAL_UINT8(1, size);
  stack_clear(stack);
  size = stack_size(stack);
  TEST_ASSERT_EQUAL_UINT8(0, size);
  TEST_ASSERT_TRUE(stack_empty(stack));
}
