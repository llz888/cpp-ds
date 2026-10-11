#pragma once
#include <iostream>

inline int g_failures = 0;

#define CHECK(expr)                                                     \
    do {                                                                \
        if (!(expr)) {                                                  \
            ++g_failures;                                               \
            std::cout << "  [FAIL] " << __FILE__ << ":" << __LINE__     \
                      << "   " << #expr << "\n";                        \
        }                                                               \
    } while (0)

