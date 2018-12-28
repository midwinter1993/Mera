#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "mera.h"

static uint64_t fact(int n) {
    assert(n > 0);
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 1;
    }
    return fact(n-1) + fact(n-2);
}

// ===============================================

int main() {
    BEGIN_TEST();

    SECTION("TEST fact") {
        ASSERT_EQ(fact(5), 5);
    }

    SECTION("TEST string") {
        std::string s = "github oops";
        ASSERT_FALSE(s.empty());
        ASSERT_TRUE(s.find("github") == 0);
    }

    END_TEST();

    return 0;
}
