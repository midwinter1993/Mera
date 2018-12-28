#ifndef __MERA_H__
#define __MERA_H__

#include <stdio.h>

#include <iostream>
#include <sstream>

// ===============================================
enum Color {
    WHITE     = 0,
    BLACK     = 30,
    RED       = 31,
    GREEN     = 32,
    BROWN     = 33,
    BLUE      = 34,
    MAGENTA   = 35,
    CYAN      = 36,
    LIGHTGRAY = 37
};

void cprintf(Color c, const char* fmt...);

// ===============================================

void begin_test();
void end_test();

void new_section(const std::string &name);

void pass_case();
void fail_case();

// ===============================================

template<typename T, typename U>
void print_obj(const T &left, const U &right) {
    std::ostringstream oss;

    oss << "Left: " << left;
    oss << "\nRight: " << right;

    cprintf(BLUE, "%s\n", oss.str().c_str());
}

#define ASSERT_EQ(left, right) \
    do { \
        if ((left) == (right)) { \
            pass_case(); \
        } else { \
            cprintf(WHITE, "-------------------\n"); \
            printf("%s %d fails: \n", __FILE__, __LINE__); \
            print_obj(left, right); \
            cprintf(WHITE, "-------------------\n"); \
            fail_case(); \
        } \
    } while (0)

#define ASSERT_TRUE(cond) \
    ASSERT_EQ(cond, true)

#define ASSERT_FALSE(cond) \
    ASSERT_EQ(cond, false)

#define BEGIN_TEST() \
    do { \
        begin_test(); \
    } while (0) \

#define END_TEST() \
    do { \
        end_test(); \
    } while (0)

#define SECTION(name) \
    do { \
        new_section(name); \
    } while (0);

#endif /* ifndef __MERA_H__ */
