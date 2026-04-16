#include <iostream>
#include <stdexcept>
#include "stack.h"

static int passed = 0;
static int failed = 0;

#define EXPECT_TRUE(expr)\
    do{\
        if(expr) { std::cout << "  PASS  " #expr "\n"; ++passed; }\
        else     { std::cout << "  FAIL  " #expr "\n"; ++failed; }\
    } while (0)

#define EXPECT_THROW(expr, ExcType)\
    do { \
        bool caught = false; \
        try { expr; } catch (const ExcType&) { caught = true; } \
        if (caught) { std::cout << "  PASS  throws " #ExcType "\n"; ++passed; } \
        else        { std::cout << "  FAIL  throws " #ExcType "\n"; ++failed; } \
    } while (0)

void test_array_stack() {
    std::cout << "\n--- ArrayStack ---\n";
    ArrayStack s(3);

    EXPECT_TRUE(s.empty());
    EXPECT_TRUE(s.size() == 0);
    EXPECT_TRUE(s.capacity() == 3);

    s.push(10);
    EXPECT_TRUE(s.top() == 10);
    EXPECT_TRUE(s.size() == 1);

    s.push(20);
    s.push(30);
    EXPECT_TRUE(s.full());
    EXPECT_TRUE(s.top() == 30);

    EXPECT_THROW(s.push(40), std::overflow_error);

    s.pop();
    EXPECT_TRUE(s.top() == 20);

    s.pop(); s.pop();
    EXPECT_TRUE(s.empty());

    EXPECT_THROW(s.pop(), std::underflow_error);
    EXPECT_THROW(s.top(), std::underflow_error);

    s.push(99);
    EXPECT_TRUE(s.top() == 99);
}

void test_linked_stack(){
    std::cout << "\n--- LinkedStack ---\n";
    LinkedStack s;

    EXPECT_TRUE(s.empty());
    EXPECT_TRUE(s.size() == 0);

    s.push(1); s.push(2); s.push(3);
    EXPECT_TRUE(s.top() == 3);
    EXPECT_TRUE(s.size() == 3);

    s.pop(); EXPECT_TRUE(s.top() == 2);
    s.pop(); EXPECT_TRUE(s.top() == 1);
    s.pop(); EXPECT_TRUE(s.empty());

    EXPECT_THROW(s.pop(), std::underflow_error);
    EXPECT_THROW(s.top(), std::underflow_error);

    // No fixed cap
    for (int i = 0; i < 1000; ++i) s.push(i);
    EXPECT_TRUE(s.size() == 1000);
    EXPECT_TRUE(s.top() == 999);
}

int main() {
    std::cout << "=== Stack Tests ===";
    test_array_stack();
    test_linked_stack();
    std::cout << "\nResult: " << passed << " passed, " << failed << " failed \n";
    return failed == 0 ? 0 : 1;  
}