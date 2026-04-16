#include <iostream>
#include <stdexcept>
#include "queue.h"

static int passed = 0;
static int failed = 0;

#define EXPECT_TRUE(expr)\
    do { \
        if (expr) { std::cout << "  PASS  " #expr "\n"; ++passed; } \
        else      { std::cout << "  FAIL  " #expr "\n"; ++failed; } \
    } while(0)

#define EXPECT_THROW(expr, ExcType) \
    do { \
        bool caught = false; \
           try { expr; } catch (const ExcType&) { caught = true; } \
           if (caught) { std::cout << "PASS throws " #ExcType "\n"; ++passed; } \
           else { std::cout << "FAIL expected " #ExcType "\n"; ++failed; } \
    } while (0)

void test_array_queue() {
    std::cout << "\n--- ArrayQueue ---\n";
    ArrayQueue q(4);

    EXPECT_TRUE(q.empty());
    EXPECT_TRUE(q.size() == 0);
    EXPECT_TRUE(q.capacity() == 4);

    q.enqueue(10);
    EXPECT_TRUE(q.front() == 10);
    EXPECT_TRUE(q.back() == 10);

    q.enqueue(20); q.enqueue(30); q.enqueue(40);
    EXPECT_TRUE(q.front() == 10);
    EXPECT_TRUE(q.front() == 10);
    EXPECT_TRUE(q.back() == 40);

    EXPECT_THROW(q.enqueue(50), std::overflow_error);

    q.dequeue(); EXPECT_TRUE(q.front() == 20);
    q.dequeue(); EXPECT_TRUE(q.front() == 30);
    q.dequeue(); q.dequeue();
    EXPECT_TRUE(q.empty());

    EXPECT_THROW(q.dequeue(), std::underflow_error);
    EXPECT_THROW(q.front(), std::underflow_error);
    EXPECT_THROW(q.back(), std::underflow_error);

    // Circular wrap-around
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    q.dequeue(); q.dequeue();
    q.enqueue(4); q.enqueue(5);
    EXPECT_TRUE(q.front() == 3);
    EXPECT_TRUE(q.back() == 5);
    EXPECT_TRUE(q.size() == 3);
}

void test_linked_queue() {
    std::cout << "\n--- LinkedQueue ---\n";
    LinkedQueue q;

    EXPECT_TRUE(q.empty());
    EXPECT_TRUE(q.size() == 0);

    q.enqueue(100);
    EXPECT_TRUE(q.front() == 100);
    EXPECT_TRUE(q.back() == 100);

    q.enqueue(200); q.enqueue(300);
    EXPECT_TRUE(q.front() == 100);
    EXPECT_TRUE(q.back() == 300);
    EXPECT_TRUE(q.size() == 3);

    q.dequeue(); EXPECT_TRUE(q.front() == 200);
    q.dequeue(); EXPECT_TRUE(q.front() == 300);
    q.dequeue(); EXPECT_TRUE(q.empty());

    EXPECT_THROW(q.dequeue(), std::underflow_error);

    q.enqueue(999);
    EXPECT_TRUE(q.front() == 999);
    EXPECT_TRUE(q.back() == 999);

    for (int i = 0; i < 1000; ++i) q.enqueue(i);
    EXPECT_TRUE(q.size() == 1001);
}

int main() {
    std::cout << "=== Queue Tests ===";
    test_array_queue();
    test_linked_queue();
    std::cout << "\nResult: " << passed << "passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}