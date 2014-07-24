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
//total 61 functions


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
    ASSERT_TRUE (x.size() == 3);
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


// ------------------------
// const_reference_back
// ------------------------   

TEST (my_deque, const_back_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.back() == 5);
    ASSERT_TRUE (&x.back() == &x.at(19));}

TEST (my_deque, const_back_2){
    my_deque<int> x (1, 5);
    ASSERT_TRUE (x.back() == 5);
    ASSERT_TRUE (&x.back() == &x.at(0));}

TEST (my_deque, const_back_3){
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
    ASSERT_TRUE (x.front() == 15);
    ASSERT_TRUE (&x.front() == &x.at(0));}



// ------------------------
// const_reference_front
// ------------------------    

TEST (my_deque, const_front_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.front() == 5);
    ASSERT_TRUE (&x.front() == &x.at(0));}

TEST (my_deque, const_front_2){
    my_deque<int> x (10, 5);
    x.push_front(6);
    ASSERT_TRUE (x.front() == 6);
    ASSERT_TRUE (&x.front() == &x.at(0));}

TEST (my_deque, const_front_3){
    my_deque<int> x (10, 10);
    ASSERT_TRUE (x.front() == 10);
    x.front() = 15;
    ASSERT_TRUE (x.front() == 15);
    ASSERT_TRUE (&x.front() == &x.at(0));}

// ----------
// begin
// ----------

TEST (my_deque, begin_1){
    my_deque<int> x (10, 5);
    my_deque<int>::iterator i = x.begin();
    ASSERT_TRUE(*i == 5);
    ASSERT_TRUE(&*i == &x[0]);
    ASSERT_TRUE(&*i == &x.front());}

TEST (my_deque, begin_2){
    my_deque<int> x (1, 5);
    my_deque<int>::iterator i = x.begin();
    ASSERT_TRUE(*i == 5);
    ASSERT_TRUE(&*i == &x[0]);
    ASSERT_TRUE(&*i == &x.front());}

TEST (my_deque, begin_3){
    my_deque<int> x (10, 5);
    my_deque<int>::iterator i = x.begin();
    ASSERT_TRUE(*i == 5);
    *i = 20;
    ASSERT_TRUE(*i == 20);
    ASSERT_TRUE(&*i == &x[0]);
    ASSERT_TRUE(&*i == &x.front());
    i++;
    ASSERT_TRUE(*i == 5);
}     

// ----------
// const_begin
// ----------

TEST (my_deque, const_begin_1){
    my_deque<int> x (10, 5);
    const my_deque<int>::iterator i = x.begin();
    ASSERT_TRUE(*i == 5);
    ASSERT_TRUE(&*i == &x[0]);
    ASSERT_TRUE(&*i == &x.front());}

TEST (my_deque, const_begin_2){
    my_deque<int> x (1, 5);
    const my_deque<int>::iterator i = x.begin();
    ASSERT_TRUE(*i == 5);
    ASSERT_TRUE(&*i == &x[0]);
    ASSERT_TRUE(&*i == &x.front());}

TEST (my_deque, const_begin_3){
    my_deque<int> x (10, 5);
    const my_deque<int>::iterator i = x.begin();
    ASSERT_TRUE(*i == 5);
    *i = 20;
    ASSERT_TRUE(*i == 20);
    ASSERT_TRUE(&*i == &x[0]);
    ASSERT_TRUE(&*i == &x.front());}      

// ----------
// end
// ----------

TEST (my_deque, end_1){
    my_deque<int> x (10, 5);
    my_deque<int>::iterator i = x.end();
    --i;
    ASSERT_TRUE(*i == 5);
    ASSERT_TRUE(&*i == &x[9]);
    ASSERT_TRUE(&*i == &x.back());}

TEST (my_deque, end_2){
    my_deque<int> x (10, 5);
    my_deque<int>::iterator i = x.end();
    --i;
    ASSERT_TRUE(*i == 5);
    *i = 20;
    ASSERT_TRUE(*i == 20);
    ASSERT_TRUE(&*i == &x[9]);
    ASSERT_TRUE(&*i == &x.back());}

TEST (my_deque, end_3){
    my_deque<int> x (1, 5);
    my_deque<int>::iterator i = x.end();
    my_deque<int>::iterator j = x.begin();
    --i;
    ASSERT_TRUE(*i == *j);
    ASSERT_TRUE(i == j);
    ASSERT_TRUE(&*i == &*j);}       

// ----------
// const_end
// ----------

TEST (my_deque, const_end_1){
    my_deque<int> x (10, 5);
    const my_deque<int>::iterator i = x.end();
    ASSERT_TRUE(*i == 5);
    ASSERT_TRUE(&*i == &x[9]);
    ASSERT_TRUE(&*i == &x.back());}

TEST (my_deque, const_end_2){
    my_deque<int> x (10, 5);
    const my_deque<int>::iterator i = x.end();
    ASSERT_TRUE(*i == 5);;}

TEST (my_deque, const_end_3){
    my_deque<int> x (1, 5);
    const my_deque<int>::iterator i = x.end();
    const my_deque<int>::iterator j = x.begin();
    ASSERT_TRUE(i != j);}       

// ------------
// operator[]
// ------------

TEST (my_deque, index_1) {
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x[0] == 5);
    ASSERT_TRUE (x[3] == 5);}

TEST (my_deque, index_2) {
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_TRUE (x[0] == 1);
    ASSERT_TRUE (x[1] == 2);

    try {
        x[2];
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST (my_deque, index_3) {
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    
    ASSERT_TRUE(x[0] == 1);
    ASSERT_TRUE(x[1] == 2);
    ASSERT_TRUE(x[2] == 3);
    
    x.pop_back();
    x.push_back(5);
    ASSERT_TRUE(x[2] == 5);}

// ------------
// operator const_[]
// ------------

TEST (my_deque, const_index_1) {
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x[0] == 5);
    ASSERT_TRUE (x[3] == 5);}

TEST (my_deque, const_index_2) {
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_TRUE (x[0] == 1);
    ASSERT_TRUE (x[1] == 2);

    try {
        x[2];
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

TEST (my_deque, const_index_3) {
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    
    ASSERT_TRUE(x[0] == 1);
    ASSERT_TRUE(x[1] == 2);
    ASSERT_TRUE(x[2] == 3);
    
    x.pop_back();
    x.push_back(5);
    ASSERT_TRUE(x[2] == 5);}

// ----
// at
// ----

TEST (my_deque, at_1) {
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_TRUE (x[0] == 1);
    ASSERT_TRUE (x[1] == 2);

    try {
        ASSERT_TRUE(x.at(3) != 3);
        ASSERT_TRUE(false);
    } catch (...) {
        ASSERT_TRUE(true);
    }
}

TEST (my_deque, at_2) {
    my_deque<int> x (10,5);
    ASSERT_TRUE (x.at(0) == 5);
    ASSERT_TRUE(&x.at(0) == &x[0]);

    try {
        ASSERT_TRUE(x.at(11) != 3);
        ASSERT_TRUE(false);
    } catch (...) {
        ASSERT_TRUE(true);
    }
}

TEST (my_deque, at_3) {
    my_deque<int> x (10,5);
    ASSERT_TRUE (x.at(0) == 5);
    ASSERT_TRUE(&x.at(0) == &x[0]);
    x.push_back(15);
    try {
        ASSERT_TRUE(x.at(10) == 15);
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

// ---------
// const_at
// ---------

TEST (my_deque, const_at_1) {
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_TRUE (x[0] == 1);
    ASSERT_TRUE (x[1] == 2);

    try {
        ASSERT_TRUE(x.at(3) != 3);
        ASSERT_TRUE(false);
    } catch (...) {
        ASSERT_TRUE(true);
    }
}

TEST (my_deque, const_at_2) {
    my_deque<int> x (10,5);
    ASSERT_TRUE (x.at(0) == 5);
    ASSERT_TRUE(&x.at(0) == &x[0]);

    try {
        ASSERT_TRUE(x.at(11) != 3);
        ASSERT_TRUE(false);
    } catch (...) {
        ASSERT_TRUE(true);
    }
}

TEST (my_deque, const_at_3) {
    my_deque<int> x (10,5);
    ASSERT_TRUE (x.at(0) == 5);
    ASSERT_TRUE(&x.at(0) == &x[0]);
    x.push_back(15);
    try {
        ASSERT_TRUE(x.at(10) == 15);
        ASSERT_TRUE(true);
    } catch (...) {
        ASSERT_TRUE(false);
    }
}

// ----------
// erase
// ----------

TEST (my_deque, erase_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator p = x.end();
    x.erase(p-1);
    ASSERT_TRUE (x.size() == 9);
    ASSERT_TRUE (x[8] == 5);}

TEST (my_deque, erase_2){
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.erase(x.begin());
    ASSERT_TRUE (x.size() == 2);
    ASSERT_TRUE (x[0] == 2);}

TEST (my_deque, erase_3){
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.erase(x.begin());
    ASSERT_TRUE (x.size() == 2);
    ASSERT_TRUE (x[0] == 2);
    x.erase(x.begin());
    ASSERT_TRUE (x.size() == 1);
    ASSERT_TRUE (x[0] == 3);}        

// -----------
// insert
// -----------

TEST (my_deque, insert_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator p = x.end();
    x.insert(p-1, 3);
    ASSERT_TRUE (x.size() == 11);
    ASSERT_TRUE (x[9] == 5);
    ASSERT_TRUE (x[10] == 3);}

TEST (my_deque, insert_2){
    my_deque<int> x (10,5);
    my_deque<int>::iterator p = x.begin();
    x.insert(p, 3);
    ASSERT_TRUE (x.size() == 11);
    ASSERT_TRUE (x[0] == 3);
    ASSERT_TRUE (x[10] == 5);}

 TEST (my_deque, insert_3){
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_TRUE (x.size() == 3);
    ASSERT_TRUE (x[0] == 1);
    x.insert(x.begin(), 10);
    ASSERT_TRUE (x[0] == 10);
    ASSERT_TRUE (x[1] == 1);} 

// ---------
// size
// ---------

TEST (my_deque, size_1){
    my_deque<int> x (10, 5);
    ASSERT_TRUE (x.size() == 11);}

TEST (my_deque, size_2){
    my_deque<int> x (1, 5);
    ASSERT_TRUE (x.size() == 10);
    x.push_back(2);
    x.push_back(2);
    x.push_back(2);
    ASSERT_TRUE (x.size() == 13);}

TEST (my_deque, size_3){
    my_deque<int> x;
    ASSERT_TRUE (x.size() == 0);
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_TRUE (x.size() == 3);
    ASSERT_TRUE (x.back() == 3);}

// ---------------------
// fill_constructor
// ---------------------

TEST(my_deque, fill_constructor_1){
    my_deque<int> x;
    ASSERT_TRUE(x.size() == 0);}

TEST(my_deque, fill_constructor_2){
    my_deque<int> x;
    x.push_back(1);
    ASSERT_TRUE(x.size() == 1);}

TEST(my_deque, fill_constructor_3){
    my_deque<int> x;
    x.push_back(1);
    x.push_back(2);
    ASSERT_TRUE(x.size() == 0);}


// ---------------------
// copy_constructor
// ---------------------


// ---------------
// assignment
// ---------------

TEST(my_deque, assignment_1){
    my_deque<int> x (1,1);
    my_deque<int> y (1,1);
    ASSERT_TRUE(x == y);}

TEST(my_deque, assignment_2){
    my_deque<int> x (10,1);
    my_deque<int> y (20,1);
    ASSERT_TRUE(!(x < y));}    

TEST(my_deque, assignment_3){
    my_deque<int> x;
    my_deque<int> y;
    ASSERT_TRUE(x == y);} 

// -------------
// equality
// -------------

TEST(my_deque, equality_1){
    my_deque<int> x (1,1);
    my_deque<int> y (1,1);
    ASSERT_TRUE(x == y);}

TEST(my_deque, equality_2){
    my_deque<int> x (10,1);
    my_deque<int> y (20,1);
    ASSERT_TRUE(!(x < y));}    

TEST(my_deque, equality_3){
    my_deque<int> x;
    my_deque<int> y;
    ASSERT_TRUE(x == y);}   

// ----------------------------
// less than
// ----------------------------

TEST(my_deque, less_than_1){
    my_deque<int> x (1,1);
    my_deque<int> y (1,1);
    ASSERT_TRUE(!(x < y));}

TEST(my_deque, less_than_2){
    my_deque<int> x (10,1);
    my_deque<int> y (20,1);
    ASSERT_TRUE(x < y);}    

TEST(my_deque, less_than_3){
    my_deque<int> x (10,1);
    my_deque<int> y (10,2);
    ASSERT_TRUE(x < y);}        




// -----------
// resize
// -----------

TEST (my_deque, resize_1) {
    my_deque<int> x(10, 5);
    x.resize(5);
    for (int i = 0; i < 5; ++i) {
        ASSERT_TRUE (x[i] == 5);
    }
    ASSERT_TRUE (x.size() == 5);}

TEST (my_deque, resize_2) {
    my_deque<int> x (10, 5);
    x.resize(15, 5);
    for (int i = 0; i < 15; ++i) {
        ASSERT_TRUE (x[i] == 5);
    }

    ASSERT_TRUE (x.size() == 15);}

TEST (my_deque, resize_3) {
    my_deque<int> x;
    x.resize(20, 5);
    ASSERT_TRUE (x.size() == 20);}

// ----------
// clear
// ----------

TEST (my_deque, clear_1) {
    my_deque<int> x(10, 5);
    x.clear();
    ASSERT_TRUE (x.size() == 0);}

TEST (my_deque, clear_2) {
    my_deque<int> x;
    x.clear();

    ASSERT_TRUE (x.size() == 0);}

TEST (my_deque, clear_3) {
    my_deque<int> x;
    x.clear();
    ASSERT_TRUE (x.size() == 0);}

// ---------
// swap
// ---------

TEST (my_deque, swap_1){
    my_deque<int> x(10,5);
    my_deque<int> y(5, 1);
    ASSERT_TRUE(x.size() == 10);
    ASSERT_TRUE(y.size() == 5);
    x.swap(y);
    ASSERT_TRUE(x.size() == 5);
    ASSERT_TRUE(y.size() == 10);}

TEST (my_deque, swap_2){
    my_deque<int> x;
    my_deque<int> y;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    ASSERT_TRUE(x.size() == 3);

    y.push_back(5);
    y.push_back(6);
    y.push_back(7);
    y.push_back(8);
    ASSERT_TRUE(y.size() == 4);
    x.swap(y);
    ASSERT_TRUE(x.size() == 4);
    ASSERT_TRUE(y.size() == 3);}

TEST (my_deque, swap_3){
    my_deque<int> x(10,5);
    my_deque<int> y(5, 1);
    ASSERT_TRUE(x.size() == 10);
    ASSERT_TRUE(y.size() == 5);
    ASSERT_TRUE(x.front() == 5);
    ASSERT_TRUE(y.front() == 1);
    x.swap(y);
    ASSERT_TRUE(x.size() == 5);
    ASSERT_TRUE(y.size() == 10);
    ASSERT_TRUE(x.front() == 1);
    ASSERT_TRUE(y.front() == 5);}

// -------------
// TestIterator
// -------------

// -------------------------
// test_iterator_constructor
// -------------------------




// -------------------------
// test_iterator_dereference
// -------------------------


// -------------------
// iterator_equal
// -------------------

TEST(Iterator, equality_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i1 = x.begin();
    my_deque<int>::iterator i2 = x.begin();
    ASSERT_TRUE(i1 == i2);
}

TEST(Iterator, equality_2){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i1 = x.begin();
    my_deque<int>::iterator i2 = x.begin();
    ASSERT_TRUE(i1 == i2);
}

TEST(Iterator, equality_3){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i1 = x.begin();
    my_deque<int>::iterator i2 = x.begin();
    ASSERT_TRUE(i1 == i2);
}



// -------------------------
// const_iterator_equal
// -------------------------





// ----------------
// iterator_++
// ----------------

TEST(Iterator, plus_plus_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.begin();
    i++;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, plus_plus_2){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.begin();
    for(int j = 0; j < 10 ; j++){
        ASSERT_TRUE(*i == 5); 
        i++;
    } 
}

TEST(Iterator, plus_plus_3){
    my_deque<int> x (50,5);
    my_deque<int>::iterator i = x.begin();
    i++;
    i++;
    ASSERT_TRUE(*i == 5);
}

// ----------------------
// const_iterator_++
// ----------------------

TEST(Iterator, const_plus_plus_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.begin();
    i++;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, const_plus_plus_2){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.begin();
    for(int j = 0; j < 10 ; j++){
        ASSERT_TRUE(*i == 5); 
        i++;
    } 
}

TEST(Iterator, const_plus_plus_3){
    my_deque<int> x (50,5);
    my_deque<int>::iterator i = x.begin();
    i++;
    i++;
    ASSERT_TRUE(*i == 5);
}

// ----------------
// iterator_--
// ----------------

TEST(Iterator, minus_minus_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.end();
    i --;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, minus_minus_2){
    my_deque<int> x (20,5);
    my_deque<int>::iterator i = x.end();
    i--;
    i--;
    i--;

    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, minus_minus_3){
    my_deque<int> x (50,5);
    my_deque<int>::iterator i = x.end();
    i--;
    ASSERT_TRUE(*i == 5);
}

// ----------------------
// const_iterator_--
// ----------------------

TEST(Iterator, const_minus_minus_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.end();
    i --;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, const_minus_minus_2){
    my_deque<int> x (20,5);
    my_deque<int>::iterator i = x.end();
    i--;
    i--;
    i--;

    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, const_minus_minus_3){
    my_deque<int> x (50,5);
    my_deque<int>::iterator i = x.end();
    i--;
    ASSERT_TRUE(*i == 5);
}
// ----------------
// iterator_+=
// ----------------

TEST(Iterator, plus_equal_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.begin();
    i += 4;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, plus_equal_2){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.begin();
    for(int j = 0; j < 10 ; j++){
        i += 1;
        ASSERT_TRUE(*i == 5); 
    } 
}

TEST(Iterator, plus_equal_3){
    my_deque<int> x (50,5);
    my_deque<int>::iterator i = x.begin();
    i += 20;
    ASSERT_TRUE(*i == 5);
}

// ----------------------
// const_iterator_+=
// ----------------------

TEST(Iterator, const_plus_equal_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.begin();
    i += 4;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, const_plus_equal_2){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.begin();
    for(int j = 0; j < 10 ; j++){
        i += 1;
        ASSERT_TRUE(*i == 5); 
    } 
}

TEST(Iterator, const_plus_equal_3){
    my_deque<int> x (50,5);
    my_deque<int>::iterator i = x.begin();
    i += 20;
    ASSERT_TRUE(*i == 5);
}

// ----------------
// iterator_-=
// ----------------

TEST(Iterator, minus_equal_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.end();
    i -= 4;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, minus_equal_2){
    my_deque<int> x (20,5);
    my_deque<int>::iterator i = x.end();
    i -= 10;
    i -= 5;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, minus_equal_3){
    my_deque<int> x (50,5);
    my_deque<int>::iterator i = x.end();
    i -= 20;
    ASSERT_TRUE(*i == 5);
}

// ----------------------
// const_iterator_-=
// ----------------------

TEST(Iterator, const_minus_equal_1){
    my_deque<int> x (10,5);
    my_deque<int>::iterator i = x.end();
    i -= 4;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, const_minus_equal_2){
    my_deque<int> x (20,5);
    my_deque<int>::iterator i = x.end();
    i -= 10;
    i -= 5;
    ASSERT_TRUE(*i == 5);
}

TEST(Iterator, const_minus_equal_3){
    my_deque<int> x (50,5);
    my_deque<int>::iterator i = x.end();
    i -= 20;
    ASSERT_TRUE(*i == 5);
}

// -------------------
// test_iterator_valid
// -------------------


// --------------------
// Const Iterator Tests
// --------------------

// -------------------------------
// test_const_iterator_constructor
// -------------------------------


// -------------------------------
// test_const_iterator_dereference
// -------------------------------





// -------------------------
// test_const_iterator_valid
// -------------------------