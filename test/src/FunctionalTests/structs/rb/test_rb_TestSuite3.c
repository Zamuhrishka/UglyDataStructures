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

//_____ D E F I N I T I O N S _________________________________________________
#define RB_MAX_SIZE 30
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
  TEST_MESSAGE("RingBuffer Complex Tests");
  // TEST_IGNORE_MESSAGE("This TestSuite haven`t implemented");
}

void test_TestCase_0(void)
{
  TEST_MESSAGE("[RB_TEST]: create");
  TEST_ASSERT_NOT_NULL(rb);
}

/**
 * @brief Tests the behavior of the `rb_is_empty` method across different states of the ring buffer.
 *
 * This unit test evaluates the functionality of the `rb_is_empty` method by:
 * 1. Checking if a newly initialized ring buffer is empty.
 * 2. Iteratively adding elements to the ring buffer and asserting that it isn't empty after each addition.
 * 3. Iteratively retrieving elements from the ring buffer and asserting that it remains non-empty until the last
 * element is retrieved.
 * 4. Checking if the ring buffer is empty after all elements have been retrieved.
 *
 * The expected behavior is for the ring buffer to correctly report its emptiness state at each step of the process.
 */
void test_TestCase_1(void)
{
  uint32_t input[RB_MAX_SIZE] = {
      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535,
      10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,
  };
  uint32_t output[RB_MAX_SIZE] = {};

  TEST_MESSAGE("[RB_TEST]: is empty");

  TEST_ASSERT_TRUE(rb_is_empty(rb));

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
    TEST_ASSERT_FALSE(rb_is_empty(rb));
  }

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_FALSE(rb_is_empty(rb));
    TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
  }

  TEST_ASSERT_TRUE(rb_is_empty(rb));
}

/**
 * @brief Tests the behavior of the `rb_is_full` method across different states of the ring buffer.
 *
 * This unit test evaluates the functionality of the `rb_is_full` method by:
 * 1. Checking if a newly initialized ring buffer is not full.
 * 2. Iteratively adding elements to the ring buffer and asserting that it isn't full until the last available slot is
 * filled.
 * 3. Checking if the ring buffer is full after it has been filled to its capacity.
 * 4. Iteratively retrieving elements from the ring buffer and asserting that it becomes non-full after the first
 * retrieval and remains so.
 *
 * The expected behavior is for the ring buffer to correctly report its fullness state at each step of the process.
 */
void test_TestCase_2(void)
{
  uint32_t input[RB_MAX_SIZE] = {
      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535,
      10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,
  };
  uint32_t output[RB_MAX_SIZE] = {};

  TEST_MESSAGE("[RB_TEST]: is full");

  TEST_ASSERT_FALSE(rb_is_full(rb));

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_FALSE(rb_is_full(rb));
    TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
  }

  TEST_ASSERT_TRUE(rb_is_full(rb));

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
    TEST_ASSERT_FALSE(rb_is_full(rb));
  }
}

/**
 * @brief Tests the functionality of the `rb_add` and `rb_get` methods in a sequence.
 *
 * This unit test is designed to validate the correct operation of the `rb_add` and `rb_get` methods
 * by carrying out the following steps:
 * 1. Populating the ring buffer with a predefined set of data using the `rb_add` method.
 * 2. Sequentially retrieving data from the ring buffer using the `rb_get` method and storing it in an output array.
 * 3. Comparing the retrieved data (output) with the expected data set.
 *
 * The expected outcome is that the retrieved data matches the original input data, demonstrating that
 * the ring buffer maintains the order of elements and correctly handles add/get operations.
 */
void test_TestCase_3(void)
{
  uint32_t input[RB_MAX_SIZE] = {
      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535,
      10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,
  };
  uint32_t expected[RB_MAX_SIZE] = {
      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535,
      10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,
  };
  uint32_t output[RB_MAX_SIZE] = {};

  TEST_MESSAGE("[RB_TEST]: add/get #1");

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
  }

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, RB_MAX_SIZE - 1);
}

void test_TestCase_4(void)
{
  uint32_t input[RB_MAX_SIZE] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[RB_MAX_SIZE] = {771535, 10021, 90197, 907163, 562610, 1,     93274, 67793, 66,    54519,
                                    771535, 10021, 90197, 907163, 562610, 11111, 22222, 33333, 44444, 55555,
                                    66666,  77777, 88888, 999999, 11111,  22222, 33333, 44444, 55555, 66666};
  uint32_t output[RB_MAX_SIZE] = {};

  TEST_MESSAGE("[RB_TEST]: add/get #2");

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
  }

  for (size_t i = 0; i < (RB_MAX_SIZE / 2) - 1; i++)
  {
    uint32_t out = 0;
    TEST_ASSERT_TRUE(rb_get(rb, &out));
  }

  for (size_t i = 0; i < (RB_MAX_SIZE / 2) - 1; i++)
  {
    uint32_t in[RB_MAX_SIZE / 2] = {11111,  22222, 33333, 44444, 55555, 66666, 77777, 88888,
                                    999999, 11111, 22222, 33333, 44444, 55555, 66666};
    TEST_ASSERT_TRUE(rb_add(rb, &in[i]));
  }

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_get(rb, &output[i]));
  }

  TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, output, RB_MAX_SIZE - 1);
}

/**
 * @brief Tests the ring buffer's ability to handle interleaved add and get operations.
 *
 * This unit test aims to validate the proper functioning of the ring buffer when performing interleaved `rb_add`
 * and `rb_get` operations. The test's sequence is as follows:
 * 1. Populate the ring buffer almost to its capacity using the `rb_add` method.
 * 2. Retrieve half of the buffer's content using the `rb_get` method.
 * 3. Add another half of the buffer's capacity with different data.
 * 4. Retrieve all the remaining data from the ring buffer using the `rb_get` method.
 * 5. Compare the retrieved data with an expected dataset.
 *
 * The test ensures that even after interleaved operations, the ring buffer maintains the correct order
 * and data integrity.
 */
void test_TestCase_5(void)
{
  uint32_t input[RB_MAX_SIZE] = {
      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535,
      10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,
  };
  uint32_t expected[RB_MAX_SIZE] = {
      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535,
      10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,
  };
  uint32_t output[RB_MAX_SIZE] = {};

  TEST_MESSAGE("[RB_TEST]: peek");

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
  }

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_peek(rb, &output[i]));
    TEST_ASSERT_EQUAL_UINT32(expected[i], output[i]);
    rb_get(rb, &output[i]);
  }
}

/**
 * @brief Tests the ring buffer's size calculation during add and get operations.
 *
 * This unit test is designed to validate the proper functioning of the `rb_size` function
 * during the usage of the ring buffer. The test's sequence is as follows:
 * 1. Ensure that the ring buffer size increases by one for each item added.
 * 2. Ensure that the ring buffer size decreases by one for each item retrieved.
 * 3. Validate that the `rb_size` function reports the correct buffer size throughout the process.
 *
 * The test ensures that the size reported by `rb_size` matches the expected behavior
 * when items are added and retrieved.
 */
void test_TestCase_6(void)
{
  uint32_t input[RB_MAX_SIZE] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[RB_MAX_SIZE] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
  uint32_t output[RB_MAX_SIZE] = {};

  TEST_MESSAGE("[RB_TEST]: size #1");

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    size_t size = rb_size(rb);
    TEST_ASSERT_EQUAL_UINT32(size, i);
    TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
  }

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_EQUAL_UINT32(rb_size(rb), RB_MAX_SIZE - 1 - i);
    rb_get(rb, &output[i]);
  }

  TEST_ASSERT_EQUAL_UINT32(rb_size(rb), 0);
}

/**
 * @brief Tests the ring buffer's size consistency during peek operations.
 *
 * This unit test is designed to ensure that the size of the ring buffer, as reported by the
 * `rb_size` function, remains unchanged after performing a series of peek operations. The test
 * sequence is as follows:
 * 1. Add items to the ring buffer one by one, ensuring the size reported by `rb_size`
 *    increases accordingly with each addition.
 * 2. Peek into the ring buffer to view the items without removing them. The size of the ring buffer
 *    should remain consistent after each peek operation.
 * 3. Validate that throughout the peek operations, the reported size of the ring buffer remains
 *    consistent with the number of items added.
 *
 * The test ensures that the `rb_peek` operation does not alter the size of the ring buffer,
 * verifying that it is a non-destructive read operation.
 */
void test_TestCase_7(void)
{
  uint32_t input[RB_MAX_SIZE] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                 93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
  uint32_t expected[RB_MAX_SIZE] = {93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1,
                                    93274, 67793, 66, 54519, 771535, 10021, 90197, 907163, 562610, 1};
  uint32_t output[RB_MAX_SIZE] = {};

  TEST_MESSAGE("[RB_TEST]: size #2");

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    size_t size = rb_size(rb);
    TEST_ASSERT_EQUAL_UINT32(size, i);
    TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
  }

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    rb_peek(rb, &output[i]);
    TEST_ASSERT_EQUAL_UINT32(rb_size(rb), RB_MAX_SIZE - 1);
  }
}

/**
 * @brief Tests the ability of the ring buffer to clear its contents.
 *
 * This unit test is designed to validate the functionality of the `rb_clear` function, which
 * is intended to remove all items from the ring buffer without necessarily extracting them one by one.
 * The sequence of the test is as follows:
 * 1. Add a series of items to the ring buffer.
 * 2. Confirm that the ring buffer is not empty using the `rb_is_empty` function.
 * 3. Invoke the `rb_clear` function to clear all the items from the ring buffer.
 * 4. Validate that the ring buffer is now empty using the `rb_is_empty` function.
 *
 * The test ensures that the `rb_clear` function successfully clears the contents of the ring buffer
 * and that the ring buffer's state is updated correctly after the clear operation.
 */
void test_TestCase_8(void)
{
  uint32_t input[RB_MAX_SIZE] = {
      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535,
      10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,
  };
  uint32_t expected[RB_MAX_SIZE] = {
      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535,
      10021, 90197, 907163, 562610, 1,      93274, 67793, 66,     54519,  771535, 10021, 90197, 907163, 562610, 1,
  };
  uint32_t output[RB_MAX_SIZE] = {};

  TEST_MESSAGE("[RB_TEST]: add/get #1");

  for (size_t i = 0; i < RB_MAX_SIZE - 1; i++)
  {
    TEST_ASSERT_TRUE(rb_add(rb, &input[i]));
  }

  TEST_ASSERT_FALSE(rb_is_empty(rb));
  TEST_ASSERT_TRUE(rb_clear(rb));
  TEST_ASSERT_TRUE(rb_is_empty(rb));
}
