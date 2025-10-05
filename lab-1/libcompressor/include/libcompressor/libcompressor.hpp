/**
 * @file libcompressor.hpp
 * @brief Header file for the libcompressor library.
 */
#ifndef LIBCOMPRR
#define LIBCOMPRR

/**
 * @brief Compression algorithms enumeration.
 */
enum compressionAlgorithm { zlib, bzip };

/**
 * @brief Buffer structure for holding data and its size.
 */
typedef struct buffer {
  char* data;
  int size;
} buffer;

/**
 * @param algo - Compression algorithm.
 * @param input - Input data.
 * @brief Compression function that uses different algorithms.
 */
buffer compress(compressionAlgorithm algo, buffer input);

#endif