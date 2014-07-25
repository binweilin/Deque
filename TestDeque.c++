// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/d86_64-linud-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestInteger

To obtain coverage of the test:
    % gcov-4.7 -b Integer.c++ TestInteger.c++
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <cassert>

#include "gtest/gtest.h"

#include "Deque.h"


#define DEFS           typedef typename TestFixture::deque_type      deque_type; \
                        typedef typename TestFixture::allocator_type  allocator_type; \
                        typedef typename TestFixture::value_type      value_type; \
                        typedef typename TestFixture::size_type       size_type; \
                        typedef typename TestFixture::difference_type difference_type; \
                        typedef typename TestFixture::pointer         pointer; \
                        typedef typename TestFixture::const_pointer   const_pointer; \
                        typedef typename TestFixture::reference       reference; \
                        typedef typename TestFixture::const_reference const_reference;

// ---------
// TestDeque
// ---------

template <typename D>
struct TestDeque : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          D                  deque_type;
    typedef typename D::allocator_type  allocator_type;
    typedef typename D::value_type      value_type;
    typedef typename D::size_type       size_type;
    typedef typename D::difference_type difference_type;
    typedef typename D::pointer         pointer;
    typedef typename D::const_pointer   const_pointer;
    typedef typename D::reference       reference;
    typedef typename D::const_reference const_reference;};

typedef testing::Types<
            std::deque<int>,
            std::deque<double>,
            my_deque<int>,
            my_deque<double> >
        my_types;

TYPED_TEST_CASE(TestDeque, my_types);

TYPED_TEST(TestDeque, Empty) {
    
    DEFS
    
    deque_type d;
    
    const bool b = d.empty();
    ASSERT_TRUE(b);
}

TYPED_TEST(TestDeque, Size) {
    DEFS
    deque_type d;
    const size_type s = d.size();
    ASSERT_EQ(0, s);
}

///////////////
//////Own Test
///////////////
 

// --------------
// push_back
// --------------

TYPED_TEST(TestDeque, push_back_1) {

    DEFS
    
    deque_type d(10,5);
    d.push_back(6);
    ASSERT_TRUE (d.size() == 11);
    ASSERT_TRUE (d.back() ==  6);
}

TYPED_TEST(TestDeque, push_back_2) {
    DEFS
    
    deque_type d(1,5);
    d.push_back(2);
    d.push_back(2);
    d.push_back(2);
    ASSERT_TRUE (d.size() ==  4);
    ASSERT_TRUE (d.back() ==  2);
}

TYPED_TEST(TestDeque, push_back_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_TRUE (d.size() == 3);
    ASSERT_TRUE (d.back() == 3);
}


TYPED_TEST(TestDeque, push_back_4) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_back(1);
    ASSERT_TRUE (d.size() == 1);
    ASSERT_TRUE (d.back() == 1);
}


TYPED_TEST(TestDeque, push_back_5) {
    
    DEFS
    
    deque_type d;
    d.push_back(7);
    d.push_back(8);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 8);
    d.pop_back();
    d.push_back(4);
    ASSERT_EQ(d[1], 4);
}


TYPED_TEST(TestDeque, push_back_6) {
    
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_back(1);
    d.push_back(2);
    d.pop_back();
    d.push_back(3);
    ASSERT_TRUE (d.size() == 2);
    ASSERT_TRUE (d.back() == 3);
}

// --------------
// push_front
// --------------

TYPED_TEST(TestDeque, push_front_1) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.size() == 10);
    ASSERT_TRUE (d.front() ==  5);
    d.push_front(6);
    ASSERT_TRUE (d.size() == 11);
    ASSERT_TRUE (d.front() ==  6);
}

TYPED_TEST(TestDeque, push_front_2) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_front(6);
    d.push_front(5);
    d.push_front(4);
    d.push_front(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.front() ==  3);
}

TYPED_TEST(TestDeque, push_front_3) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.size() == 10);
    ASSERT_TRUE (d.front() ==  5);
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    d.push_front(4);
    d.push_front(5);

    ASSERT_TRUE (d.size() == 15);
    ASSERT_TRUE (d.front() == 5);
}

TYPED_TEST(TestDeque, push_front_4) {
    DEFS
    
    deque_type d (5, 5);
    ASSERT_TRUE (d.size() == 5);
    ASSERT_TRUE (d.front() ==  5);
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    d.push_front(4);
    d.push_front(5);

    ASSERT_TRUE (d.size() == 10);
    ASSERT_TRUE (d.front() == 5);
}

TYPED_TEST(TestDeque, push_front_5) {
    DEFS
    
    deque_type d (30, 5);
    ASSERT_TRUE (d.size() == 30);
    ASSERT_TRUE (d.front() ==  5);
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    d.push_front(4);
    d.push_front(5);

    ASSERT_TRUE (d.size() == 35);
    ASSERT_TRUE (d.front() == 5);
}

TYPED_TEST(TestDeque, push_front_6) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_front(1);

    ASSERT_TRUE (d.size() == 1);
    ASSERT_TRUE (d.front() == 1);
}


// -------------
// pop_back
// -------------

TYPED_TEST(TestDeque, pop_back_1) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.size() == 10);

    d.pop_back();
    ASSERT_TRUE (d.size() == 9);
    ASSERT_TRUE (d.back() == 5);
}

TYPED_TEST(TestDeque, pop_back_2) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.size() == 10);

    d.pop_back();
    d.pop_back();
    d.pop_back();
    d.pop_back();
    d.pop_back();
    d.pop_back();
    d.pop_back();
    d.pop_back();
    d.pop_back();
    d.pop_back();

    ASSERT_TRUE (d.size() == 0);
}

TYPED_TEST(TestDeque, pop_back_3) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_back(6);
    d.push_back(5);
    d.push_back(4);
    d.push_back(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.back() ==  3); 

    d.pop_back();
    ASSERT_TRUE (d.size() == 3);  
    ASSERT_TRUE (d.back() ==  4);  
    d.pop_back();
    d.pop_back();
    d.pop_back();
    ASSERT_TRUE (d.size() == 0);  
}

TYPED_TEST(TestDeque, pop_back_4) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_back(6);
    d.push_back(5);
    d.push_back(4);
    d.push_back(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.back() ==  3); 

    d.pop_back();
    ASSERT_TRUE (d.size() == 3);  
    ASSERT_TRUE (d.back() ==  4);         
}


TYPED_TEST(TestDeque, pop_back_5) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_back(6);
    d.push_back(5);
    d.push_back(4);
    d.push_back(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.back() ==  3); 
    d.pop_back(); 
    d.pop_back();
    ASSERT_TRUE (d.size() == 2);        
}


TYPED_TEST(TestDeque, pop_back_6) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_back(6);
    d.push_back(5);
    d.push_back(4);
    d.push_back(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.back() ==  3); 
    d.pop_back();
    d.pop_back();
    d.pop_back();
    ASSERT_TRUE (d.size() == 1);   
}

// --------------
// pop_front
// --------------

TYPED_TEST(TestDeque, pop_front_1) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.size() == 10);

    d.pop_front();
    ASSERT_TRUE (d.size() == 9);
    ASSERT_TRUE (d.front() == 5);
}

TYPED_TEST(TestDeque, pop_front_2) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.size() == 10);

    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.pop_front();

    ASSERT_TRUE (d.size() == 0);
}

TYPED_TEST(TestDeque, pop_front_3) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_front(6);
    d.push_front(5);
    d.push_front(4);
    d.push_front(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.front() ==  3); 

    d.pop_front();
    ASSERT_TRUE (d.size() == 3);  
    ASSERT_TRUE (d.front() == 4);  
    d.pop_front();
    ASSERT_TRUE (d.size() == 2);  
}

TYPED_TEST(TestDeque, pop_front_4) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_front(6);
    d.push_front(5);
    d.push_front(4);
    d.push_front(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.front() ==  3); 
    d.pop_front();
    ASSERT_TRUE (d.size() == 3);  
    ASSERT_TRUE (d.front() ==  4);  
    d.pop_front();
    d.pop_front();
    ASSERT_TRUE (d.size() == 1);  
}

TYPED_TEST(TestDeque, pop_front_5) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_front(6);
    d.push_front(5);
    d.push_front(4);
    d.push_front(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.front() ==  3); 

    d.pop_front();
    ASSERT_TRUE (d.size() == 3);  
    ASSERT_TRUE (d.front() ==  4);  
}
TYPED_TEST(TestDeque, pop_front_6) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE (d.size() == 0);
    d.push_front(6);
    d.push_front(5);
    d.push_front(4);
    d.push_front(3);
    ASSERT_TRUE (d.size() == 4);
    ASSERT_TRUE (d.front() ==  3); 

    d.pop_front();
    ASSERT_TRUE (d.size() == 3);  
    ASSERT_TRUE (d.front() ==  4);  
    d.pop_front();
    d.pop_front();
    d.pop_front();
    ASSERT_TRUE (d.size() == 0); 
}

// ---------
// back
// ---------

TYPED_TEST(TestDeque, back_1) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.back() == 5);
    ASSERT_TRUE (&d.back() == &d.at(9));
}

TYPED_TEST(TestDeque, back_2) {
    DEFS
    
    deque_type d (1, 5);
    ASSERT_TRUE (d.back() == 5);
    ASSERT_TRUE (&d.back() == &d.at(0));
}

TYPED_TEST(TestDeque, back_3) {
    DEFS
    
    deque_type d (10, 10);
    d.back() = 15;
    ASSERT_TRUE (d.back() == 15);
    ASSERT_TRUE (&d.back() == &d.at(9));
}

TYPED_TEST(TestDeque, back_4) {
    DEFS
    
    deque_type d (10, 10);
    ASSERT_TRUE (d.back() == 10);
    ASSERT_TRUE (&d.back() == &d.at(9));
}

TYPED_TEST(TestDeque, back_5) {
    DEFS
    
    deque_type d (1, 20);
    ASSERT_TRUE (d.back() == 20);
    ASSERT_TRUE (&d.back() == &d.at(0));
}

TYPED_TEST(TestDeque, back_6) {
    DEFS
    
    deque_type d (20, 15);
    d.back() = 15;
    ASSERT_TRUE (d.back() == 15);
    ASSERT_TRUE (&d.back() == &d.at(19));
}

// ------------------------
// const_reference_back
// ------------------------   

TYPED_TEST(TestDeque, Const_Back_1) {
  DEFS

  deque_type x(30);
  x[29] = 99;
  const deque_type y = x;

  const_reference b = y.back();
  ASSERT_EQ(b, 99);
  ASSERT_EQ(&b, &y[29]);
}

TYPED_TEST(TestDeque, Const_Back_2) {
  typedef typename TestFixture::deque_type      deque_type;
  DEFS

  deque_type x(30, 16);
  x[29] = 99;
  x.pop_back();
  const deque_type y = x;

  const_reference b = y.back();
  ASSERT_EQ(b, 16);
  ASSERT_EQ(&b, &y[28]);
}
// ---------
// front
// ---------

TYPED_TEST(TestDeque, front_1) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.front() == 5);
    ASSERT_TRUE (&d.front() == &d.at(0));
}

TYPED_TEST(TestDeque, front_2) {
    DEFS
    
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);

    ASSERT_EQ(d.front(), 3);
    d.pop_front();
    ASSERT_EQ(d.front(), 2);
}

TYPED_TEST(TestDeque, front_3) {
    DEFS
    
    deque_type d (10, 10);
    ASSERT_TRUE (d.front() == 10);
    d.front() = 15;
    ASSERT_TRUE (d.front() == 15);
}

TYPED_TEST(TestDeque, front_4) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_TRUE (d.front() == 5);
    d.pop_front();
    ASSERT_TRUE (d.front() == 5);
}

TYPED_TEST(TestDeque, front_5) {
    DEFS
    
    deque_type d (10, 5);
    d.push_front(6);
    ASSERT_TRUE (d.front() == 6);
    d.pop_front();
    ASSERT_TRUE(d.front() == 5);
}

TYPED_TEST(TestDeque, front_6) {
    DEFS
    
    deque_type d;
    d.push_back(10);
    ASSERT_TRUE (d.front() == 10);
}

// ------------------------
// const_reference_front
// ------------------------    

TYPED_TEST(TestDeque, const_front_1) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    ASSERT_EQ(e.front(), 1);
}

TYPED_TEST(TestDeque, const_front_2) {
    DEFS
    
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e.front(), 3);
}

TYPED_TEST(TestDeque, const_front_3) {
    DEFS
    
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(d.front(), 3);
}

// ----------
// begin
// ----------

TYPED_TEST(TestDeque, begin_1) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_EQ(*d.begin(), 5);
    ASSERT_EQ(d[1], 5);
    ASSERT_EQ(d[1], 5);
}

TYPED_TEST(TestDeque, begin_2) {
    DEFS
    
    deque_type d (1, 5);
    ASSERT_EQ(*d.begin(), 5);
}

TYPED_TEST(TestDeque, begin_3) {
    DEFS
    
    deque_type d (10, 5);
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);

    ASSERT_EQ(*d.begin(), 5);
    ASSERT_EQ(d[1], 5);   
    d.pop_front();
    ASSERT_EQ(*d.begin(), 5);
}

TYPED_TEST(TestDeque, begin_4) {
    DEFS
    
    deque_type d (10, 7);

    ASSERT_EQ(*d.begin(), 7);
    ASSERT_EQ(d[1], 7);   
    d.pop_front();
    ASSERT_EQ(*d.begin(), 7);
}

TYPED_TEST(TestDeque, begin_5) {
    DEFS
    
    deque_type d (1, 20);

    ASSERT_EQ(*d.begin(), 20);
    ASSERT_EQ(d[1], 20);   
    d.pop_front();
    ASSERT_EQ(*d.begin(),20);
}

TYPED_TEST(TestDeque, begin_6) {
    DEFS
    
    deque_type d (5, 5);


    ASSERT_EQ(*d.begin(), 5);
    ASSERT_EQ(d[1], 5);   
    d.pop_front();
    ASSERT_EQ(*d.begin(), 5);
}

// -----------
// const_begin
// -----------

TYPED_TEST(TestDeque, const_begin_1) {
    DEFS
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    ASSERT_EQ(*e.begin(), 1);
    ASSERT_EQ(e[1], 2);
}
TYPED_TEST(TestDeque, const_begin_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    d.pop_front();
    
    const deque_type e(d);
    
    ASSERT_EQ(*e.begin(), 2);
    ASSERT_EQ(e[0], 2);
    
    d.pop_front();
    ASSERT_EQ(*e.begin(), 2);
}

TYPED_TEST(TestDeque, const_begin_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(*e.begin(), 1);

}

// ----------
// end
// ----------

TYPED_TEST(TestDeque, end_1) {
    DEFS
    
    deque_type d(10, 5);

    ASSERT_EQ(*(--d.end()), 5);
}

TYPED_TEST(TestDeque, end_2) {
    DEFS
    
    deque_type d;
    d.push_back(22);
    
    ASSERT_EQ(*(--d.end()), 22);
}

TYPED_TEST(TestDeque, end_3) {
    DEFS
    
    deque_type d(2,1);

    ASSERT_EQ(*(--d.end()), 1);
}

TYPED_TEST(TestDeque, end_4) {
    DEFS
    
    deque_type d;

    try {
        d.end();
        ASSERT_TRUE(true);
    }

    catch(...) {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestDeque, end_5) {
    DEFS
    
    deque_type d;
    d.push_back(22);
    d.push_back(1);
    d.push_back(2);
    
    ASSERT_EQ(*(--d.end()), 2);
}

TYPED_TEST(TestDeque, end_6) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(23);    
    ASSERT_EQ(*(--d.end()), 3);
}

// ----------
// const_end
// ----------


TYPED_TEST(TestDeque, const_end_1) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(*(--e.end()), 3);
    ASSERT_EQ(e[1], 2);
}

TYPED_TEST(TestDeque, const_end_2) {
    DEFS
    
    deque_type d;
    d.push_back(22);
    
    const deque_type e(d);
    
    ASSERT_EQ(*e.begin(), 22);
    ASSERT_EQ(*(--e.end()), 22);
    ASSERT_EQ(e[0], 22);
}

TYPED_TEST(TestDeque, const_end_3) {
    DEFS
    
    deque_type d;
    d.push_back(-1);
    
    const deque_type e(d);

    ASSERT_EQ(*e.begin(), -1);
    ASSERT_EQ(*(--e.end()), -1);
    ASSERT_EQ(e[0], -1);
}

// ------------
// operator[]
// ------------

TYPED_TEST(TestDeque, index_1) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_EQ(d[0], 5);
    ASSERT_EQ(d[1], 5);
}

TYPED_TEST(TestDeque, index_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);  
    try {
        d[2];
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestDeque, index_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[2], 3);   
}

TYPED_TEST(TestDeque, index_4) {
    DEFS
    
    deque_type d (10,5);
    ASSERT_TRUE (d[0] == 5);
    ASSERT_TRUE (d[1] == 5);
    ASSERT_TRUE (d[2] == 5);
    ASSERT_TRUE (d[3] == 5);
}

TYPED_TEST(TestDeque, index_5) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);  
    try {
        d[2];
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestDeque, index_6) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_back(4);
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[2], 3); 
    d.pop_back();
    d.push_back(5);
    ASSERT_TRUE(d[3] == 5);  
}


// ------------------
// operator const_[]
// ------------------


TYPED_TEST(TestDeque, const_index_1) {
    DEFS
    
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e[0], 3);
    ASSERT_EQ(e[1], 2);
}

TYPED_TEST(TestDeque, const_index_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);
    
    try {
        e[3];
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestDeque, const_index_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.pop_back();
    
    const deque_type e(d);
    
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);   
}

// ----
// at
// ----

TYPED_TEST(TestDeque, at_1) {
    DEFS
    
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    ASSERT_EQ(d.at(0), 3);
    ASSERT_EQ(d.at(1), 2);
}

TYPED_TEST(TestDeque, at_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.at(0), 1);
    ASSERT_EQ(d.at(1), 2);
    
    try {
        d.at(3);
        ASSERT_TRUE(false);
    } catch (...) {
        ASSERT_TRUE(true);
    }
}

TYPED_TEST(TestDeque, at_3) {
    DEFS
    
    deque_type d (10,5);    
    ASSERT_EQ(d.at(0), 5);
    ASSERT_EQ(d.at(1), 5);
    ASSERT_EQ(d.at(2), 5);
    
    d.push_back(15);
    try {
        ASSERT_TRUE(d.at(10) == 15);
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    } 
}

TYPED_TEST(TestDeque, at_4) {
    DEFS
    
    deque_type d ;    
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.at(0), 1);
    ASSERT_EQ(d.at(1), 2);
    try {
        ASSERT_TRUE(d.at(4) != 3);
        ASSERT_TRUE(false);
    } catch (...) {
        ASSERT_TRUE(true);
    }
}

TYPED_TEST(TestDeque, at_5) {
    DEFS
    
    deque_type d (10,5);
    ASSERT_TRUE (d.at(0) == 5);
    
    d.push_back(15);
    try {
        ASSERT_TRUE(d.at(10) == 15);
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    } 
}

TYPED_TEST(TestDeque, at_6) {
    DEFS
    
    deque_type d (10,5);
    ASSERT_TRUE (d.at(0) == 5);
    d.push_back(15);
    try {
        ASSERT_TRUE(d.at(10) == 15);
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

// ---------
// const_at
// ---------

TYPED_TEST(TestDeque, const_at_1) {
    DEFS
    
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e.at(0), 3);
    ASSERT_EQ(e.at(1), 2);
}

TYPED_TEST(TestDeque, const_at_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.at(0), 1);
    ASSERT_EQ(d.at(1), 2);
    
    const deque_type e(d);
    
    try {
        e.at(3);
        ASSERT_TRUE(false);
    } catch (...) {
        ASSERT_TRUE(true);
    }
}

TYPED_TEST(TestDeque, const_at_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e.at(0), 1);
    ASSERT_EQ(e.at(1), 2);
    ASSERT_EQ(e.at(2), 3);
    
}

// ----------
// erase
// ----------

TYPED_TEST(TestDeque, erase_1) {
    DEFS
    
    deque_type d (10,5);
    
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 9);
    ASSERT_EQ(d[0], 5);  
}

TYPED_TEST(TestDeque, erase_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 3);   
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 2);
    ASSERT_EQ(d[1], 3);
}

TYPED_TEST(TestDeque, erase_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 3);    
    d.erase(d.begin());

    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 2);
    ASSERT_EQ(d[1], 3);
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 3);
    
}

TYPED_TEST(TestDeque, erase_4) {
    DEFS
    
    deque_type d (10,5);
    ASSERT_EQ(d.size(), 10);
    ASSERT_EQ(d[0], 5);

    ASSERT_EQ(*(d.erase(++d.begin())), 5);
    ASSERT_EQ(d.size(), 9);
    ASSERT_EQ(d[0], 5);
}

TYPED_TEST(TestDeque, erase_5) {
    DEFS
    
    deque_type d; 
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 3);   
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 2);
    ASSERT_EQ(d[1], 3);
}

TYPED_TEST(TestDeque, erase_6) {
    DEFS
    
    deque_type d (10,10);
    
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 9);
    ASSERT_EQ(d[0], 10);  
}

// -----------
// insert
// -----------


TYPED_TEST(TestDeque, insert_1) {
    DEFS
    
    deque_type d(10,5);
    ASSERT_EQ(d.size(), 10);  
    d.insert(d.begin(), 10);
    ASSERT_EQ(d.size(), 11);
    ASSERT_EQ(d[0], 10);
    ASSERT_EQ(d[1], 5);   
}

TYPED_TEST(TestDeque, insert_2) {
    DEFS
    
    deque_type d(10,5);
    ASSERT_EQ(d.size(), 10);
    
    d.insert(d.begin(), 20);
    ASSERT_EQ(d.size(), 11);
    ASSERT_EQ(d[0], 20);
    ASSERT_EQ(d[1], 5);
}

TYPED_TEST(TestDeque, insert_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 3);

    d.insert(++d.begin(), 50);

    ASSERT_EQ(d.size(), 4);
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 50);
    ASSERT_EQ(d[2], 2);
    
}

TYPED_TEST(TestDeque, insert_4) {
    DEFS
    
    deque_type d(10, 5);

    ASSERT_EQ(d.size(), 10);
    d.insert(++d.begin(), 50);
    ASSERT_EQ(d.size(), 11);
    
}

TYPED_TEST(TestDeque, insert_5) {
    DEFS
    
    deque_type d(20,5);
    ASSERT_EQ(d.size(), 20);  
    d.insert(d.begin(), 10);
    ASSERT_EQ(d.size(), 21);
    ASSERT_EQ(d[0], 10);
    ASSERT_EQ(d[1], 5);   
}

TYPED_TEST(TestDeque, insert_6) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 3);
    d.insert(d.begin(), 5);
    ASSERT_EQ(d.size(), 4);
    ASSERT_EQ(d[0], 5);
    ASSERT_EQ(d[1], 1);
}



// ---------
// size
// ---------

TYPED_TEST(TestDeque, size_1) {
    DEFS
    
    deque_type d (10, 5);
    ASSERT_EQ(d.size(), 10);
}

TYPED_TEST(TestDeque, size_2) {
    DEFS
    
    deque_type d (1, 5);
    ASSERT_TRUE (d.size() == 1);
    d.push_back(2);
    d.push_back(2);
    ASSERT_EQ(d.size(), 3);
}

TYPED_TEST(TestDeque, size_3) {
    DEFS
    
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    d.push_back(9);
    ASSERT_EQ(d.size(), 3);
}

TYPED_TEST(TestDeque, size_4) {
    DEFS
    
    deque_type d (20, 5);
    ASSERT_EQ(d.size(), 20);
}

TYPED_TEST(TestDeque, size_5) {
    DEFS
    
    deque_type d (10, 5);
    d.push_back(2);
    d.push_back(2);
    ASSERT_EQ(d.size(), 12);
}

TYPED_TEST(TestDeque, size_6) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_back(4);
    ASSERT_EQ(d.size(), 4);
}


// ---------
// empty
// ---------

TYPED_TEST(TestDeque, empty_1) {
    DEFS
    
    deque_type d (10,5);
    ASSERT_FALSE(d.empty());
}

TYPED_TEST(TestDeque, empty_2) {
    DEFS
    
    deque_type d (1,5);
    ASSERT_FALSE(d.empty());
    d.pop_back();
    ASSERT_TRUE(d.empty());   
}
TYPED_TEST(TestDeque, empty_3) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE(d.empty());
    d.push_back(1);
    ASSERT_FALSE(d.empty());
}

TYPED_TEST(TestDeque, empty_4) {
    DEFS
    
    deque_type d (20,5);
    ASSERT_FALSE(d.empty());
}

TYPED_TEST(TestDeque, empty_5) {
    DEFS
    
    deque_type d (1,5);
    ASSERT_TRUE(d.size() == 1);
    d.push_back(1);
    d.push_back(1);
    d.push_back(1);
    d.push_back(1);
    d.push_back(1);

    ASSERT_FALSE(d.empty());
}

TYPED_TEST(TestDeque, empty_6) {
    DEFS
    
    deque_type d;
    ASSERT_TRUE(d.empty());
    d.push_back(1);
    d.push_back(2);
    ASSERT_FALSE(d.empty());
}


// ---------------------
// fill_constructor
// ---------------------

TYPED_TEST(TestDeque, fill_constructor_1) {
    DEFS
    
    deque_type d;
    ASSERT_EQ(d.size(), 0);
}

TYPED_TEST(TestDeque, fill_constructor_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 1);
}

TYPED_TEST(TestDeque, fill_constructor_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 1);
}

TYPED_TEST(TestDeque, fill_constructor_4) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(1);
    d.push_back(2);
    ASSERT_EQ(d.size(), 4);
    ASSERT_EQ(d[0], 1);
}

TYPED_TEST(TestDeque, fill_constructor_5) {
    DEFS
    
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(1);
    d.push_front(2);
    d.push_front(1);
    d.push_front(2);
    ASSERT_EQ(d.size(), 6);
    ASSERT_EQ(d[0], 2);
}

TYPED_TEST(TestDeque, fill_constructor_6) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.pop_back();
    d.pop_back();
    ASSERT_EQ(d.size(), 0);
}

// ---------------------
// copy_constructor
// ---------------------

TYPED_TEST(TestDeque, copy_constructor_1) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    ASSERT_EQ(d.size(), 2);
   
    deque_type e(d);
    e.push_back(3);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);
    ASSERT_EQ(e[2], 3);
}

TYPED_TEST(TestDeque, copy_constructor_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 3);
    deque_type e(d);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);
    ASSERT_EQ(e[2], 3);

}

TYPED_TEST(TestDeque, copy_constructor_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 3); 
    deque_type e(d);
    d.push_back(4);
    d.push_back(5);
    
    ASSERT_EQ(e.size(), 5);
}

// ---------------------
// constructor_size
// ---------------------

TYPED_TEST(TestDeque, constructor_size_1) {
    DEFS
    
    deque_type d(10,5);
    ASSERT_EQ(d.size(), 10);
}

TYPED_TEST(TestDeque, constructor_size_2) {
    DEFS
    
    deque_type d(1);
    d.push_back(2);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 0);
    ASSERT_EQ(d[1], 2);
}

TYPED_TEST(TestDeque, constructor_size_3) {
    DEFS
    
    deque_type d(10,5);
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 13);
}


// ---------------
// assignment
// ---------------

TYPED_TEST(TestDeque, assignment_1) {
    DEFS
    
    deque_type e;
    {
    deque_type d (10,5);
    e = (const deque_type)d;
    }

    ASSERT_EQ(e.size(), 10);
    ASSERT_EQ(e[0], 5);
}

TYPED_TEST(TestDeque, assignment_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    ASSERT_EQ(d.size(), 2);

    deque_type e = d;
    e.push_back(3);  
    ASSERT_EQ(e.size(), 3);
}

TYPED_TEST(TestDeque, assignment_3) {
    DEFS
    
    deque_type d;
    ASSERT_EQ(d.size(), 0);
    deque_type e = d;
    
    ASSERT_EQ(e.size(), 0);
}

TYPED_TEST(TestDeque, assignment_4) {
    DEFS
    
    deque_type e (2,2);
    deque_type d = e;

    ASSERT_TRUE(e.size() == d.size());
}

TYPED_TEST(TestDeque, assignment_5) {
    DEFS
    
    deque_type e (2,2);
    deque_type d = e;

    ASSERT_TRUE(e.size() == d.size());
}

TYPED_TEST(TestDeque, assignment_6) {
    DEFS
    
    deque_type e (5,5);
    deque_type d = e;

    ASSERT_TRUE(e.size() == d.size());
}

// -------------
// equality
// -------------

TYPED_TEST(TestDeque, equality_1) {
    DEFS
    
    deque_type e (5,5);
    deque_type d (5,5);

    ASSERT_TRUE(e == d);
}

TYPED_TEST(TestDeque, equality_2) {
    DEFS
    
    deque_type e (10,5);
    deque_type d (20,5);

    ASSERT_FALSE(e == d);
}

TYPED_TEST(TestDeque, equality_3) {
    DEFS
    
    deque_type e;
    deque_type d;

    ASSERT_TRUE(e == d);
}

TYPED_TEST(TestDeque, equality_4) {
    DEFS
    
    deque_type e (2,1);
    deque_type d (2,1);

    ASSERT_TRUE(e == d);
}

TYPED_TEST(TestDeque, equality_5) {
    DEFS
    
    deque_type e (10,1);
    deque_type d (50,1);

    ASSERT_FALSE(e == d);
}

TYPED_TEST(TestDeque, equality_6) {
    DEFS
    
    deque_type e (20,20);
    deque_type d (20,20);

    ASSERT_TRUE(e== d);
}

// ----------------------------
// less than
// ----------------------------

TYPED_TEST(TestDeque, less_than_1) {
    DEFS
    
    deque_type e (10,10);
    deque_type d (20,20);

    ASSERT_TRUE(e < d);
}

TYPED_TEST(TestDeque, less_than_2) {
    DEFS
    
    deque_type e (10,1);
    deque_type d (20,1);

    ASSERT_TRUE(e < d);
}

TYPED_TEST(TestDeque, less_than_3) {
    DEFS
    
    deque_type e (10,10);
    deque_type d (10,15);

    ASSERT_TRUE(e < d);
}

// -----------
// resize
// -----------


TYPED_TEST(TestDeque, resize_1) {
    DEFS
    
    deque_type d (10,5);
    d.resize(5);
    ASSERT_EQ(d.size(), 5);   
}

TYPED_TEST(TestDeque, resize_2) {
    DEFS
    
    deque_type d (10,5);
    d.resize(15,5);
    ASSERT_EQ(d.size(), 15);
}

TYPED_TEST(TestDeque, resize_3) {
    DEFS
    
    deque_type d;
    ASSERT_EQ(d.size(), 0);
    d.resize(20,5);
    ASSERT_EQ(d.size(), 20);
}

TYPED_TEST(TestDeque, resize_4) {
    DEFS
    
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    d.push_back(11);
    d.push_back(13);
    ASSERT_EQ(d.size(), 4);
    d.resize(2,4);
    ASSERT_EQ(d.size(), 2);
    ASSERT_TRUE(d[0] == 7);
    ASSERT_TRUE(d[1] == 9);
}


// ----------
// clear
// ----------


TYPED_TEST(TestDeque, clear_1) {
    DEFS
    
    deque_type d (10, 5);
    d.clear();
    ASSERT_EQ(d.size(), 0);   
}

TYPED_TEST(TestDeque, clear_2) {
    DEFS
    
    deque_type d;
    d.clear();
    ASSERT_EQ(d.size(), 0);   
}

TYPED_TEST(TestDeque, clear_3) {
    DEFS
    
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    d.clear();
    ASSERT_EQ(d.size(), 0);
    d.push_back(5);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 5);
    d.clear();
    ASSERT_EQ(d.size(), 0); 
}


// ---------
// swap
// ---------

TYPED_TEST(TestDeque, swap_1) {
    DEFS
    
    deque_type d (10,5);    
    deque_type e (5,1);
    ASSERT_TRUE(d.size() == 10);
    ASSERT_TRUE(e.size() == 5);

    e.swap(d);
    ASSERT_TRUE(d.size() == 5);
    ASSERT_TRUE(e.size() == 10);
}

TYPED_TEST(TestDeque, swap_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    ASSERT_EQ(d.size(), 3);
    
    deque_type e;
    e.push_back(4);
    e.push_back(5);
    ASSERT_EQ(e.size(), 2);
    
    e.swap(d);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(d.size(), 2);
}

TYPED_TEST(TestDeque, swap_3) {
    DEFS
    
    deque_type d(10,5);
    ASSERT_EQ(d.size(), 10);
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);
    
    deque_type e(5,1);    
    e.swap(d);
    
    ASSERT_EQ(d.size(), 5);
    ASSERT_EQ(e.size(), 5);
}


//***********************************************************/
// TestIterator
//***********************************************************/


// --------------------------
// const_iterator_constructor
// --------------------------

TYPED_TEST(TestDeque, Const_Iterator_Constructor_1) {
  DEFS

  const deque_type x(100, 4);
  const deque_type y(100, 4);
  typename deque_type::const_iterator b1 = x.end();
  typename deque_type::const_iterator b2 = y.end();
  ASSERT_FALSE(b1 == b2);
}

TYPED_TEST(TestDeque, Const_Iterator_Constructor_2) {
  DEFS
  const deque_type x(100, 4);
  typename deque_type::const_iterator b1 = x.begin();
  typename deque_type::const_iterator b2 = x.begin();
  while(b1 != x.end()) {
    ASSERT_TRUE(b1 == b2);
    b1++;
    b2++;
  }
}

TYPED_TEST(TestDeque, Const_Iterator_Constructor_3) {
  DEFS

  const deque_type x(27, 4);
  typename deque_type::const_iterator b1 = x.begin();
  typename deque_type::const_iterator b2 = x.begin();
  while(b1 != x.end()) {
    ASSERT_TRUE(*b1 == *b2);
    b1++;
    b2++;
  }
}

TYPED_TEST(TestDeque, Const_Iterator_Constructor_4) {
  DEFS
  const deque_type x(100, 4);
  typename deque_type::const_iterator b1 = x.end();
  typename deque_type::const_iterator b2 = x.end();
  ASSERT_TRUE(b1 == b2);
}


// -------------------
// iterator_equal
// -------------------

TYPED_TEST(TestDeque, it_equals_1) {
    DEFS
    
    deque_type d;
    d.push_back(1);

    ASSERT_TRUE(d.begin() == d.begin());
}

TYPED_TEST(TestDeque, it_equals_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);

    ASSERT_TRUE(d.begin() == --d.end());
}

TYPED_TEST(TestDeque, it_equals_3) {
    DEFS
    
    deque_type d;
    d.push_back(7);
    d.push_back(8);
    
    ASSERT_TRUE(++d.begin() == --d.end());
}

// -------------------------
// const_iterator_equal
// -------------------------

TYPED_TEST(TestDeque, const_iterator_equals_1)
{
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*(y+1),4);
}

TYPED_TEST(TestDeque, const_iterator_equals_2)
{
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*(y+2),1);
}

TYPED_TEST(TestDeque, const_iterator_equals_3)
{
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    x.push_front(6);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    ASSERT_EQ(*(y+3),1);
}

// -------------------
// iterator_not_equal
// -------------------

TYPED_TEST(TestDeque, it_not_equals_1) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    
    ASSERT_TRUE(d.begin() != d.end());
}

TYPED_TEST(TestDeque, it_not_equals_2) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    
    ASSERT_FALSE(d.begin() != --d.end());
}

TYPED_TEST(TestDeque, it_not_equals_3) {
    DEFS
    
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    
    ASSERT_FALSE(++d.begin() != --d.end());
}

// ----------------
// iterator_++
// ----------------

TYPED_TEST(TestDeque, plus_plus_1) {
    DEFS
    deque_type x(1, 1);
    x.resize(2, 2);
    const size_type s = x.size();
    ASSERT_EQ(2, s);

    const deque_type y(x);

    /* Iterators */
    typename deque_type::const_iterator it = y.begin();
    typename deque_type::const_iterator it2 = ++y.begin();

    ASSERT_EQ(*it, 1);
    ASSERT_EQ(*it2, 2);
    ASSERT_TRUE(++it == it2);
}

TYPED_TEST(TestDeque, plus_plus_2) {
    DEFS
    
    deque_type x(1, 1);
    x.resize(2, 2);
    x.resize(3, 3);
    const size_type s = x.size();
    ASSERT_EQ(3, s);

    /* Iterators */
    typename deque_type::iterator it = x.begin();
    typename deque_type::iterator it2 = ++x.begin();
    typename deque_type::iterator it3 = it2;
    ++it3;

    ASSERT_EQ(*it, 1);
    ASSERT_EQ(*it2, 2);
    ASSERT_EQ(*it3, 3);
}

TYPED_TEST(TestDeque, plus_plus_3) {
    DEFS
    deque_type x(1, 1);
    x.resize(2, 2);
    const size_type s = x.size();
    ASSERT_EQ(2, s);

    /* Iterators */
    typename deque_type::iterator it = x.begin();
    typename deque_type::iterator it2 = ++x.begin();

    ASSERT_EQ(*it, 1);
    ASSERT_EQ(*it2, 2);
    ASSERT_TRUE(++it == it2);
}

// ----------------------
// const_iterator_++
// ----------------------

TYPED_TEST(TestDeque, const_plus_plus_1) {
    typedef typename TestFixture::deque_type      deque_type;  

    deque_type x;
    x.push_back(7);
    x.push_back(3);
    x.push_back(2);
    x.push_front(1);
    x.pop_back();
    
    const deque_type y(x);
    
    ASSERT_EQ(y.size(), 3);
    ASSERT_EQ(y[0], 1);
    
    ASSERT_EQ(*(y.begin()), 1);
    ASSERT_EQ(*(++y.begin()), 7);
    ASSERT_EQ(*(++++y.begin()), 3);
}

TYPED_TEST(TestDeque, const_plus_plus_2) {
    typedef typename TestFixture::deque_type      deque_type; 
    
    deque_type x;
    x.push_back(7);
    x.push_back(3);
    x.push_front(1);
    x.push_front(2);
    
    const deque_type y(x);
    
    ASSERT_EQ(y.size(), 4);
    ASSERT_EQ(y[1], 1);
    
    ASSERT_EQ(*(++y.begin()), 1);
}

TYPED_TEST(TestDeque, const_plus_plus_3) {
    typedef typename TestFixture::deque_type      deque_type; 

    deque_type x;
    for(int i = 0; i < 5; ++i)
        x.push_back(1);

    for (int i = 0; i < 5; ++i)
        x.push_front(2);

    for (int i = 0; i < 5; ++i)
        x.push_back(3);
    
    const deque_type y(x);
    
    ASSERT_EQ(y.size(), 15);
    ASSERT_EQ(y[0], 2);
    
    ASSERT_EQ(*(y.begin()), 2);
    ASSERT_EQ(*(++y.begin()), 2);
    ASSERT_EQ(*(++++y.begin()), 2);
}

// ----------------
// iterator_--
// ----------------

TYPED_TEST(TestDeque, minus_minus_1) {
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    y--;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, minus_minus_2) {
    DEFS

    deque_type x;

    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    y--;
    y--;
    ASSERT_EQ(*y, 5);
}

TYPED_TEST(TestDeque, minus_minus_3) {
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    --y;
    --y;
    ASSERT_EQ(*y, 5);
}

TYPED_TEST(TestDeque, minus_minust_4) {
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    --y;
    ASSERT_EQ(*y, 4);
}

// ----------------------
// const_iterator_--
// ----------------------

TYPED_TEST(TestDeque, const_minus_minust_1) {
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    y--;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, const_minus_minust_2) {
    DEFS

    deque_type x;

    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    y--;
    y--;
    ASSERT_EQ(*y, 5);
}

TYPED_TEST(TestDeque, const_minus_minust_3) {
     DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    --y;
    --y;
    ASSERT_EQ(*y, 5);
}

TYPED_TEST(TestDeque, const_minus_minust_4) {
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.end() - 1;
    --y;
    ASSERT_EQ(*y, 4);
}


// ----------------
// iterator_+=
// ----------------

TYPED_TEST(TestDeque, plus_equal_1) {
    DEFS
    
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    y = y + 1;
    ASSERT_EQ(*y, 4);
}

TYPED_TEST(TestDeque, plus_equal_2) {
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    try
        {y = y + 3;}
    catch(...)
        {assert(true);}
}

TYPED_TEST(TestDeque, plus_equal_3) {
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    typename deque_type::iterator y = x.begin();
    y = y + 2;
    ASSERT_EQ(*y, 1);
}

// ----------------------
// const_iterator_+=
// ----------------------

TYPED_TEST(TestDeque, const_plus_equals_1)
{
    DEFS
    deque_type x(5, 1);
    const size_type s = x.size();
    ASSERT_EQ(5, s);

    x.resize(10, 2);

    const deque_type y(x);

    /* Iterators */
    typename deque_type::const_iterator it = y.end() - 1;
    
    typename deque_type::const_iterator it2 = it - 5;

    ASSERT_EQ(*it, 2);
    ASSERT_EQ(*it2, 1);
}

TYPED_TEST(TestDeque, const_plus_equals_2)
{
    DEFS
    deque_type x(5, 1);
    x.resize(10, 2);
    x.resize(50, 3);
    const size_type s = x.size();
    ASSERT_EQ(50, s);

    const deque_type y(x);

    /* Iterators */
    typename deque_type::const_iterator it = y.end() - 1;
    
    typename deque_type::const_iterator it2 = it - 40;
    typename deque_type::const_iterator it3 = it2 - 5;

    ASSERT_EQ(*it, 3);
    ASSERT_EQ(*it2, 2);
    ASSERT_EQ(*it3, 1);
}

TYPED_TEST(TestDeque, const_plus_equals_3)
{
    DEFS
    deque_type x;
    x.push_front(1);
    x.push_front(4);
    x.push_front(5);
    const deque_type a(x);
    typename deque_type::const_iterator y = a.begin();
    try
        {y = y + 3;}
    catch(...)
        {assert(true);}
}

// ----------------
// iterator_-=
// ----------------

TYPED_TEST(TestDeque, minus_equal_1) {
    DEFS
    deque_type x(5, 1);
    x.resize(10, 2);
    x.resize(50, 3);
    const size_type s = x.size();
    ASSERT_EQ(50, s);

    /* Iterators */
    typename deque_type::iterator it = x.end() - 1;
    
    typename deque_type:: iterator it2 = it;
    it2 -= 40;
    typename deque_type:: iterator it3 = it2;
    it3 -= 5;

    ASSERT_EQ(*it, 3);
    ASSERT_EQ(*it2, 2);
    ASSERT_EQ(*it3, 1);
}

TYPED_TEST(TestDeque, minus_equal_2) {
    DEFS
    
    deque_type x(5, 1);
    const size_type s = x.size();
    ASSERT_EQ(5, s);

    x.resize(10, 2);

    /* Iterators */
    typename deque_type::iterator it = x.end() - 1;
    
    typename deque_type:: iterator it2 = it;
    it2 -= 5;

    ASSERT_EQ(*it, 2);
    ASSERT_EQ(*it2, 1);
}

TYPED_TEST(TestDeque, minus_equal_3) {
    DEFS
    
    deque_type x(5, 1);
    x.resize(10, 2);
    x.resize(50, 3);
    const size_type s = x.size();
    ASSERT_EQ(50, s);

    /* Iterators */
    typename deque_type::iterator it = x.end() - 1;
    
    typename deque_type:: iterator it2 = it;
    it2 -= 40;
    typename deque_type:: iterator it3 = it2;
    it3 -= 5;

    ASSERT_EQ(*it, 3);
    ASSERT_EQ(*it2, 2);
    ASSERT_EQ(*it3, 1);
}

// ----------------------
// const_iterator_-=
// ----------------------

TYPED_TEST(TestDeque, const_minus_equals_1)
{
    DEFS
    deque_type x(5, 1);
    const size_type s = x.size();
    ASSERT_EQ(5, s);

    const deque_type y(x);

    /* Iterators */
    typename deque_type::const_iterator it = y.end() - 1;
    
    
    typename deque_type::const_iterator it2 = it;
    it2 -= 3;

    ASSERT_EQ(*it, 1);
    ASSERT_EQ(*it2, 1);
}

TYPED_TEST(TestDeque, const_minus_equals_2)
{
    DEFS
    deque_type x(5, 1);
    const size_type s = x.size();
    ASSERT_EQ(5, s);

    x.resize(10, 2);

    const deque_type y(x);

    /* Iterators */
    typename deque_type::const_iterator it = y.end() - 1;
    
    typename deque_type::const_iterator it2 = it;
    it2 -= 5;

    ASSERT_EQ(*it, 2);
    ASSERT_EQ(*it2, 1);
}

// -----
// star
// ------

TYPED_TEST(TestDeque, star_1) {
    DEFS
    
    deque_type d(45);
    d.push_back(7);
    *d.begin() = 8;
    ASSERT_EQ(d.size(), 46);
    ASSERT_EQ(d[0], 8);
}

TYPED_TEST(TestDeque, star_2) {
    DEFS
    
    deque_type d(10,5);

    ASSERT_EQ(*d.begin(), 5);
}

TYPED_TEST(TestDeque, star_3) {
    DEFS
    
    deque_type d(10,5);
    d.push_back(7);
    ASSERT_EQ(*d.begin(), 5);
}

// ----------------------
// iterator_constructor
// ----------------------

TYPED_TEST(TestDeque, it_cons_1) {
    DEFS
    
    deque_type d;
    deque_type x(5, 1);
    value_type a[] = {1, 1, 1, 1, 1};
    const size_type s = x.size();
    ASSERT_EQ(5, s);
    ASSERT_TRUE(std::equal(x.begin(), x.end(), a));
}

TYPED_TEST(TestDeque, it_cons_2) {
    DEFS
    
    deque_type d;
    d.push_back(7);
    
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 7);
    
    ASSERT_EQ(*(d.begin()), 7);
}

TYPED_TEST(TestDeque, it_cons_3) {
    DEFS
    
    deque_type x(2, 1);
    x.resize(5, 3);
    value_type a[] = {1, 1, 3, 3, 3};
    const size_type s = x.size();
    ASSERT_EQ(5, s);
    ASSERT_TRUE(std::equal(x.begin(), x.end(), a));
}
