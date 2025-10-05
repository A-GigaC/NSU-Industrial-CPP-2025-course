/**
 * @file libcompressor.cpp
 * @brief Exported code for libcompressor library.
 */
#include <bzlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#include "libcompressor/libcompressor.hpp"

/**
 * @brief Compress data using specified algorithm.
 *
 * @param algo Compression algorithm name.
 * @param input Input data to be compressed.
 * @return buffer with compressed data.
 */
buffer compress(compressionAlgorithm algo, buffer input) {
  buffer compressedData;

  if (input.size == 0 || input.data == NULL) {
    compressedData.data = NULL;
    compressedData.size = 0;
    return compressedData;
  }

  compressedData.data = (char*)malloc(input.size + 1024);

  switch (alg) {
    case zlib: {
      z_stream data;
      data.zalloc = Z_NULL;
      data.zfree = Z_NULL;
      data.opaque = Z_NULL;

      if (deflateInit(&data, Z_DEFAULT_COMPRESSION) != Z_OK) {
        compressedData.data = NULL;
        compressedData.size = 0;
        return compressedData;
      }

      compressedData.size = deflateBound(&data, input.size);

      data.avail_in = input.size;
      data.next_in = (Bytef*)input.data;
      data.avail_out = compressedData.size;
      data.next_out = (Bytef*)compressedData.data;

      if (deflate(&data, Z_FINISH) != Z_STREAM_END) {
        deflateEnd(&data);
        compressedData.size = 0;
        free(compressedData.data);
        comressedData.data = NULL;
        return compressedData;
      }
      compressedData.size = data.total_out;

      deflateEnd(&data);
    } break;
    case bzip: {
      if (BZ2_bzBuffToBuffCompress(compressedData.data, (unsigned int*)&compressedData.size, input.data, input.size, 1,
                                   0, 0) != BZ_OK) {
        compressedData.size = 0;
        free(compressedData.data);
        comressedData.data = NULL;
      }
    } break;
    default:
      compressedData.data = NULL;
      compressedData.size = 0;
      return compressedData;
  }

  return compressedData;
}