// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

TEST(default_constructor) {
    List<int> test;
}
TEST(push_back) {
    List<int> test;
    test.push_back(5);
    test.push_back(6);
    ASSERT_EQUAL(*test.begin(),5);
    ASSERT_EQUAL(*++test.begin(), 6);
}

TEST(empty) {
    List<int> test;
    ASSERT_TRUE(test.empty());
    
    List<int> test2;
    test2.push_back(5);
    test2.push_back(3);
    ASSERT_TRUE(!test2.empty());
    
}

TEST(back) {
    List<int> test;
    test.push_back(5);
    ASSERT_EQUAL(test.back(), 5);
    test.push_back(3);
    test.push_back(2);
    ASSERT_EQUAL(test.back(), 2);
    test.push_front(7);
    ASSERT_EQUAL(test.back(), 2);
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
    test.erase(++test.begin());
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
    test.push_back("Dog");
    List<string>::Iterator it1 = test.begin();
    List<string>::Iterator it2 = ++test.begin();
    ASSERT_TRUE(*it1 != *it2);
    ASSERT_TRUE(!(*it1 != *it1));
}

TEST(copy_constructor) {
    List<int> test;
    test.push_back(5);
    test.push_back(4);
    test.push_back(3);

    List<int> copied_into = test;
    
    
    List<int>::Iterator starting = test.begin();
    List<int>::Iterator cop = copied_into.begin();
    int thing1 = 0;
    int thing2 = 0;
    ASSERT_EQUAL(test.size(), copied_into.size());
    for(; starting != test.end(); ++starting) {
        thing1 = *starting;
        thing2 = *cop;
        ASSERT_EQUAL(thing1, thing2);
        ++cop;
    }
    
}
TEST(copy_constructor2) {
    List<int> test;

    List<int> copied_into = test;
    
    
    List<int>::Iterator start_test = test.begin();
    List<int>::Iterator copied_into_start = copied_into.begin();
    int holder1 = 0;
    int holder2 = 0;
    ASSERT_EQUAL(test.size(), copied_into.size());
    for(; start_test != test.end(); ++start_test) {
        holder1 = *start_test;
        holder2 = *copied_into_start;
        ASSERT_EQUAL(holder1, holder2);
        ++copied_into_start;
    }
    
}
TEST(assignment_operator) {
    List<int> test;
    test.push_back(5);
    test.push_back(4);
    test.push_back(3);
    
    List<int>copied_into;
    copied_into = test;
    
    List<int>::Iterator test_begin = test.begin();
    List<int>::Iterator copied_begin = copied_into.begin();
    
    ASSERT_EQUAL(copied_into.size(), test.size());
    
    for(; test_begin != test.end(); ++test_begin) {
        int holder1 = *copied_begin;
        int holder2 = *test_begin;
        ASSERT_EQUAL(holder1, holder2);
        ++copied_begin;
    }
    
    test = test;
    List<int>::Iterator it = test.begin();
    ASSERT_EQUAL(*it, 5);
    ASSERT_EQUAL(*++it, 4);
    ASSERT_EQUAL(*++it, 3);
    
    
    
}
TEST(count) {
    List<string> test;
    test.push_back("Hello");
    test.push_back("my");
    test.push_back("dude");
    
    ASSERT_EQUAL(test.front(), "Hello");
    ASSERT_EQUAL(test.back(), "dude");
    ASSERT_EQUAL(test.size(), 3);
    
    //Edge case: Tests array of size 0
    List<int>num;
    ASSERT_EQUAL(num.size(), 0);
    num.push_front(7);
    ASSERT_EQUAL(num.size(), 1);
}
TEST(push_front) {
    List<int> test;
    test.push_back(5);
    test.push_back(4);
    test.push_back(3);
    
    test.push_front(6);
    
    List<int> correct;
    correct.push_back(6);
    correct.push_back(5);
    correct.push_back(4);
    correct.push_back(3);

    List<int>::Iterator start_test = test.begin();
    List<int>::Iterator start_correct = correct.begin();
    int holder1 = 0;
    int holder2 = 0;
    ASSERT_EQUAL(correct.size(), test.size())
    for(; start_test != test.end(); ++start_test) {
        holder1 = *start_test;
        holder2 = *start_correct;
        ASSERT_EQUAL(holder1, holder2);
        ++start_correct;
    }
    
    //Edge case: Empty list
    List<int> haha;
    haha.push_front(69);
    
    ASSERT_EQUAL(haha.size(), 1);
    ASSERT_EQUAL(*haha.begin(), 69);

}
TEST(pop_front) {
    //Edge Case: 1 Item in List
    List<int> oneitem;
    oneitem.push_back(5);
    oneitem.pop_front();
    ASSERT_EQUAL(oneitem.size(), 0);
    
    //Normal Case
    List<int> test;
    test.push_back(5);
    test.push_back(4);
    test.push_back(3);
    test.pop_front();
    
    ASSERT_EQUAL(test.size(), 2);
    List<int>::Iterator it = test.begin();
    ASSERT_EQUAL(*it, 4);
    ASSERT_EQUAL(*(++it), 3);
}
TEST(insert) {
    //Edge Case: Empty List
    List<int> empty;
    List<int>::Iterator emptyit = empty.begin();
    empty.insert(emptyit, 5);
    ASSERT_EQUAL(*empty.begin(), 5);
    ASSERT_EQUAL(empty.size(), 1);
    
    //Case 2: Iterator at end
    List<int> test1;
    test1.push_back(5);
    test1.push_back(4);
    test1.push_back(3);
    
    List<int> test1correct;
    test1correct.push_back(5);
    test1correct.push_back(4);
    test1correct.push_back(3);
    test1correct.push_back(2);
    
    List<int>::Iterator test1it = test1.end();
    test1.insert(test1it, 2);
    
    List<int>::Iterator test1start = test1.begin();
    List<int>::Iterator correctstart = test1correct.begin();
    ASSERT_EQUAL(test1.size(), test1correct.size());
    
    for(; test1start != test1.end(); ++test1start) {
        int holder1 = *correctstart;
        int holder2 = *test1start;
        ASSERT_EQUAL(holder1, holder2);
        ++correctstart;
    }
}
TEST(insert2) {
    
    //Case 3: Iterator at beginning
    List<int> test1;
    test1.push_back(4);
    test1.push_back(3);
    test1.push_back(2);
    
    List<int> test1correct;
    test1correct.push_back(5);
    test1correct.push_back(4);
    test1correct.push_back(3);
    test1correct.push_back(2);
    
    List<int>::Iterator test1it = test1.begin();
    test1.insert(test1it, 5);
    
    List<int>::Iterator test1start = test1.begin();
    List<int>::Iterator correctstart = test1correct.begin();
    ASSERT_EQUAL(test1.size(), test1correct.size());
    
    for(; test1start != test1.end(); ++test1start) {
        int holder1 = *correctstart;
        int holder2 = *test1start;
        ASSERT_EQUAL(holder1, holder2);
        ++correctstart;
    }
}
TEST(insert3) {
    
    //Case 4: Iterator in middle
    List<int> test1;
    test1.push_back(5);
    test1.push_back(4);
    test1.push_back(2);
    test1.push_back(1);
    
    List<int> test1correct;
    test1correct.push_back(5);
    test1correct.push_back(4);
    test1correct.push_back(3);
    test1correct.push_back(2);
    test1correct.push_back(1);
    
    List<int>::Iterator test1it = test1.begin();
    ++++test1it;
    ASSERT_EQUAL(*test1it, 2);
    test1.insert(test1it, 3);
    
    List<int>::Iterator test1start = test1.begin();
    List<int>::Iterator correctstart = test1correct.begin();
    ASSERT_EQUAL(test1.size(), test1correct.size());
    
    for(; test1start != test1.end(); ++test1start) {
        int holder1 = *correctstart;
        int holder2 = *test1start;
        ASSERT_EQUAL(holder1, holder2);
        ++correctstart;
    }
}
TEST_MAIN()
