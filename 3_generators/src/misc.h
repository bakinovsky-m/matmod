#ifndef MISC_H
#define MISC_H

#include <cstdint>
#include <string>

typedef uint64_t u64;

const u64 AMOUNT = pow(2, 10) - 1;
const u64 D = 10;

#ifdef _WIN32
const std::string FILENAME = "build\\rand.txt";
#else
const std::string FILENAME = "build/rand.txt";
#endif

#endif