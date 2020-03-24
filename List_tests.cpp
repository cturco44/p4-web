// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

TEST(push_back) {
    List<int> test;
    test.push_back(5);
    test.push_back(6);
    ASSERT_EQUAL(*test.begin(),5);
    ASSERT_EQUAL(*test.end(), 6);
}

TEST(empty) {
    List<int> test;
    ASSERT_TRUE(test.empty());
}

TEST(back) {
    List<int> test;
    test.push_back(5);
    ASSERT_EQUAL(test.back(), 5);
}

TEST(pop_back) {
    List<int> test;
    test.push_back(5);
    test.push_back(6);
    test.pop_back();
    ASSERT_EQUAL(test.back(), 5);
    test.pop_back();
    ASSERT_TRUE(test.empty());
}

TEST(erase) {
    List<int> test;
    test.push_back(5);
    test.push_back(6);
    test.push_back(7);
    test.push_back(8);
    test.begin();
    test.erase(++test.begin());
    test.erase(test.begin());
    test.erase(test.end());
    test.erase(test.begin());
    ASSERT_TRUE(test.empty());
}

TEST(not_equal_true) {
    List<string> test1;
    test1.push_back("HI");
    test1.push_back("World");
    ASSERT_TRUE(test1.begin() != test1.end());
}

TEST(not_equal_false) {
    List<string> test;
    test.push_back("Fish");
    ASSERT_FALSE(test.begin() != test.end());
}

TEST(copy_constructor) {
    List<int> test;
    test.push_back(5);
    test.push_back(4);
    test.push_back(3);

    List<int> copied_into = test;

}

TEST_MAIN()
