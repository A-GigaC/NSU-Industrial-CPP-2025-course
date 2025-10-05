#include <gtest/gtest.h>
#include "libcompressor/libcompressor.hpp"

TEST(CompressorTest, bzipEquationTest) {
  char equivalentString1[] = "equivalent string";
  char equivalentString2[] = "equivalent string";

  buffer buffer1;
  buffer1.data = equivalentString1;
  buffer1.size = 18;

  buffer buffer2;
  buffer2.data = equivalentString2;
  buffer2.size = 18;

  buffer resultBzip1 = compress(bzip, buffer1);
  buffer resultBzip2 = compress(bzip, buffer2);

  ASSERT_TRUE(resultBzip1.size == resultBzip2.size);
  ASSERT_TRUE(memcmp(resultBzip1.data, resultBzip2.data, resultBzip1.size) == 0);
}

TEST(CompressorTest, zlibEquationTest) {
  char equivalentString1[] = "equivalent string";
  char equivalentString2[] = "equivalent string";

  buffer buffer1;
  buffer1.data = equivalentString1;
  buffer1.size = 20;

  buffer buffer2;
  buffer2.data = equivalentString2;
  buffer2.size = 20;

  buffer resultZlib1 = compress(zlib, buffer1);
  buffer resultZlib2 = compress(zlib, buffer2);

  ASSERT_TRUE(resultZlib1.size == resultZlib2.size);
  ASSERT_TRUE(memcmp(resultZlib1.data, resultZlib2.data, resultZlib1.size) == 0);
}

TEST(CompressorTest, nullBufferTest) {
  buffer buf;
  buf.data = NULL;
  buf.size = 1;

  buffer resultBzip = compress(bzip, buf);
  ASSERT_TRUE(resultBzip.data == NULL);

  buffer resultZlib = compress(zlib, buf);
  ASSERT_TRUE(resultZlib.data == NULL);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}