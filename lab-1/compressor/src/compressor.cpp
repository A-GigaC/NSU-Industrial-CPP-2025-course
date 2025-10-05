/**
 * @file compressor.cpp
 * @brief Excecutable file for compressing input data using specified algorithm.
 */
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libcompressor/libcompressor.hpp"
/**
 * @param argc - Argument count includes the program name, so argc should be 3.
 * @param argv - Arguments list. argv[1] - compression algorithm (zlib/bzip), argv[2] - string for compression.
 * @brief 
 */
int main(int argc, char** argv) {
  if (argc != 3) {
    spdlog::error("Not enough arguments(should be 2)");
    exit(EXIT_FAILURE);
  }

  compressionAlgorithm algo;
  buffer buff;
  buff.data = strdup(argv[2]);
  buff.size = strlen(argv[2]);

  if (!strcmp(argv[1], "zlib")) {
    algo = zlib;
  } else if (!strcmp(argv[1], "bzip")) {
    algo = bzip;
  } else {
    spdlog::error("Incorrect algorithm name");
    exit(EXIT_FAILURE);
  }

  buffer result = compress(algo, buff);

  if (result.data == NULL) {
    spdlog::error("NULL pointer returned");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < result.size; i++) {
    printf("%.2hhx", result.data[i]);
  }
  printf("\n");

  exit(EXIT_SUCCESS);
}