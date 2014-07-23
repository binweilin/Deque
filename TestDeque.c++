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
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestDeque

To obtain coverage of the test:
    % gcov-4.7 -b Deque.c++ TestDeque.c++
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

#include "gtest/gtest.h"

#include "Deque.h"


#define private public
#define protected public

using namespace std;
//total 62 functions


// ---------
// TestDeque
// ---------

// template <typename D>
// struct TestDeque : testing::Test {
//     // --------
//     // typedefs
//     // --------

//     typedef          D                  deque_type;
//     typedef typename D::allocator_type  allocator_type;
//     typedef typename D::value_type      value_type;
//     typedef typename D::size_type       size_type;
//     typedef typename D::difference_type difference_type;
//     typedef typename D::pointer         pointer;
//     typedef typename D::const_pointer   const_pointer;
//     typedef typename D::reference       reference;
//     typedef typename D::const_reference const_reference;};

// typedef testing::Types<
//             std::deque<int>,
//             std::deque<double>,
//             my_deque<int>,
//             my_deque<double> >
//         my_types;

// TYPED_TEST_CASE(TestDeque, my_types);

// TYPED_TEST(TestDeque, Empty) {
//     typedef typename TestFixture::deque_type      deque_type;
//     typedef typename TestFixture::allocator_type  allocator_type;
//     typedef typename TestFixture::value_type      value_type;
//     typedef typename TestFixture::size_type       size_type;
//     typedef typename TestFixture::difference_type difference_type;
//     typedef typename TestFixture::pointer         pointer;
//     typedef typename TestFixture::const_pointer   const_pointer;
//     typedef typename TestFixture::reference       reference;
//     typedef typename TestFixture::const_reference const_reference;

//     deque_type x;
//     const bool b = x.empty();
//     ASSERT_TRUE(b);}

// TYPED_TEST(TestDeque, Size) {
//     typedef typename TestFixture::deque_type      deque_type;
//     typedef typename TestFixture::allocator_type  allocator_type;
//     typedef typename TestFixture::value_type      value_type;
//     typedef typename TestFixture::size_type       size_type;
//     typedef typename TestFixture::difference_type difference_type;
//     typedef typename TestFixture::pointer         pointer;
//     typedef typename TestFixture::const_pointer   const_pointer;
//     typedef typename TestFixture::reference       reference;
//     typedef typename TestFixture::const_reference const_reference;

//     deque_type x;
//     const size_type s = x.size();
//     ASSERT_EQ(0, s);}

// --------------
// push_back
// --------------

TEST (my_deque, push_back_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.size() == 10);
    ASSERT_TRUE (x.back() ==  5);
    x.push_back(6);
    ASSERT_TRUE (x.size() == 11);
    ASSERT_TRUE (x.back() ==  6);}

TEST (my_deque, push_back_2){
    my_deque<int> x (1, 5);
    ASSERT_TRUE (x.size() == 10);
    ASSERT_TRUE (x.back() ==  5);
    x.push_back(2);
    x.push_back(2);
    x.push_back(2);

    ASSERT_TRUE (x.size() == 13);
    ASSERT_TRUE (x.back() ==  2);}

TEST (my_deque, push_back_3){
    my_deque<int> x;
    ASSERT_TRUE (x.size() == 0);
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_TRUE (x.size() == 1);
    ASSERT_TRUE (x.back() == 3);}

// --------------
// push_front
// --------------

TEST (my_deque, push_front_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.size() == 10);
    ASSERT_TRUE (x.front() ==  5);
    x.push_front(6);
    ASSERT_TRUE (x.size() == 11);
    ASSERT_TRUE (x.front() ==  6);}

TEST (my_deque, push_front_2){
    my_deque<int> x;
    ASSERT_TRUE (x.size() == 0);
    x.push_front(6);
    x.push_front(5);
    x.push_front(4);
    x.push_front(3);
    ASSERT_TRUE (x.size() == 4);
    ASSERT_TRUE (x.front() ==  3);}

TEST (my_deque, push_front_3){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.size() == 10);
    ASSERT_TRUE (x.front() ==  5);
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.push_front(4);
    x.push_front(5);

    ASSERT_TRUE (x.size() == 15);
    ASSERT_TRUE (x.front() == 5);}        


// -------------
// pop_back
// -------------

TEST (my_deque, pop_back_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.size() == 10);

    x.pop_back();
    ASSERT_TRUE (x.size() == 9);
    ASSERT_TRUE (x.back() == 5);}

TEST (my_deque, pop_back_2){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.size() == 10);

    x.pop_back();
    x.pop_back();
    x.pop_back();
    x.pop_back();
    x.pop_back();
    x.pop_back();
    x.pop_back();
    x.pop_back();
    x.pop_back();
    x.pop_back();

    ASSERT_TRUE (x.size() == 0);}

TEST (my_deque, pop_back_3){
    my_deque<int> x;
    ASSERT_TRUE (x.size() == 0);
    x.push_back(6);
    x.push_back(5);
    x.push_back(4);
    x.push_back(3);
    ASSERT_TRUE (x.size() == 4);
    ASSERT_TRUE (x.back() ==  3); 

    x.pop_back();
    ASSERT_TRUE (x.size() == 3);  
    ASSERT_TRUE (x.back() ==  4);  
    x.pop_back();
    x.pop_back();
    x.pop_back();
    ASSERT_TRUE (x.size() == 0);        
}


// --------------
// pop_front
// --------------
TEST (my_deque, pop_front_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.size() == 10);

    x.pop_front();
    ASSERT_TRUE (x.size() == 9);
    ASSERT_TRUE (x.front() == 5);}

TEST (my_deque, pop_front_2){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.size() == 10);

    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();
    x.pop_front();

    ASSERT_TRUE (x.size() == 0);}

TEST (my_deque, pop_front_3){
    my_deque<int> x;
    ASSERT_TRUE (x.size() == 0);
    x.push_front(6);
    x.push_front(5);
    x.push_front(4);
    x.push_front(3);
    ASSERT_TRUE (x.size() == 4);
    ASSERT_TRUE (x.front() ==  3); 

    x.pop_back();
    ASSERT_TRUE (x.size() == 3);  
    ASSERT_TRUE (x.front() ==  4);  
    x.pop_front();
    x.pop_front();
    x.pop_front();
    ASSERT_TRUE (x.size() == 0);        
}


// ---------
// back
// ---------

TEST (my_deque, back_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.back() == 5);
    ASSERT_TRUE (&x.back() == &x.at(19));}

TEST (my_deque, back_2){
    my_deque<int> x (1, 5);
    ASSERT_TRUE (x.back() == 5);
    ASSERT_TRUE (&x.back() == &x.at(0));}

TEST (my_deque, back_3){
    my_deque<int> x (10, 10);
    x.back() = 15;
    ASSERT_TRUE (x.back() == 15);
    ASSERT_TRUE (&x.back() == &x.at(9));}

// ---------
// front
// ---------

TEST (my_deque, front_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.front() == 5);
    ASSERT_TRUE (&x.front() == &x.at(0));}

TEST (my_deque, front_2){
    my_deque<int> x (10, 5);
    x.push_front(6);
    ASSERT_TRUE (x.front() == 6);
    ASSERT_TRUE (&x.front() == &x.at(0));}

TEST (my_deque, front_3){
    my_deque<int> x (10, 10);
    ASSERT_TRUE (x.front() == 10);
    x.front() = 15;
    ASSERT_TRUE (con1.front() == 15);
    ASSERT_TRUE (&x.front() == &x.at(0));}

// -------------
// TestIterator
// -------------