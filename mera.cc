#include "mera.h"

#include <iostream>
#include <vector>

// ===============================================
#define OUT_FD  stdout

static void reset_color() {
    fprintf(OUT_FD, "\033[0m");
}

static void start_color(Color c) {
    if (c == WHITE) {
        fprintf(OUT_FD, "\033[0m");
    } else {
        fprintf(OUT_FD, "\033[0;%dm", c);
    }
}

void cprintf(Color c, const char* fmt...) {

    va_list args;
    va_start(args, fmt);

    start_color(c);
    vfprintf(OUT_FD, fmt, args);
    reset_color();

    va_end(args);
}

// ===============================================

struct Section {
    std::string name_;
    size_t nr_pass_;
    size_t nr_fail_;

    void inc_pass() { nr_pass_ += 1; }
    void inc_fail() { nr_fail_ += 1; }

    void print_summary();
};

void Section::print_summary() {
    // cprintf(BROWN, "END SECTION [ %s ]\n", name_.c_str());
    cprintf(GREEN, "# Passed cases: %lu\n", nr_pass_);

    if (nr_fail_) {
        cprintf(RED, "# Failed cases: %lu\n", nr_fail_);
    } else {
        cprintf(WHITE, "# Failed cases: %lu\n", nr_fail_);
    }

    if (!nr_fail_) {
        cprintf(GREEN, "All passed\n");
    }
}

static Section g_test_section;
static std::vector<Section> g_sections;

static Section* curr_section() {
    if (g_sections.empty()) {
        return nullptr;
    }
    return &g_sections.back();
}
static void curr_section_summary() {
    auto *sec = curr_section();
    if (sec) {
        sec->print_summary();
    }
}

// ===============================================

void begin_test() {
    g_test_section = Section{ "TOTAL TESTS", 0, 0 };
}

void end_test() {
    curr_section_summary();

    cprintf(WHITE, "\n===== SUMMAY =======\n");
    g_test_section.print_summary();
}

void new_section(const std::string &name) {
    curr_section_summary();

    cprintf(WHITE, "\n===================\n\n");
    cprintf(BROWN, "SECTION [ %s ]\n", name.c_str());
    cprintf(WHITE, "---\n\n");

    g_sections.push_back(Section{name, 0, 0});
}

void pass_case() {
    g_test_section.inc_pass();

    if (curr_section()) {
        curr_section()->nr_pass_ += 1;
    }
}

void fail_case() {
    g_test_section.inc_fail();

    if (curr_section()) {
        curr_section()->nr_fail_ += 1;
    }
}
