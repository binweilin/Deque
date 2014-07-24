// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=
#include <iostream> 

#define WIDTH 50
using namespace std;
// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::template rebind<T*>::other allocator_type2;
        typedef typename allocator_type2::pointer pointer2;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * @param lhs a my_deque reference to the left of operator 
         * @param rhs a my_deque reference to the right of operator 
         * return true if contents of lhs and rhs are equal, else false
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::equal()
            return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());}

        // ----------
        // operator <
        // ----------

        /**
         * @param lhs a my_deque reference to the left of operator 
         * @param rhs a my_deque reference to the right of operator         
         * return true if rhs lexicographically greater than lhs
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    private:
        // ----
        // data
        // ----

        allocator_type _a;

        // <your data>
        allocator_type2 _a2;

        size_type _size;
        size_type _capacity;

        pointer2 _out_b;
        pointer2 _out_e;
        pointer  _in_b;
        pointer  _in_e;

        pointer _af;
        pointer _ae;
        pointer _uf;
        pointer _ue;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            //cout << "af " << _af <<endl<<"ae " << _ae <<endl<< _uf <<endl<< _ue <<endl<<_size<<endl;
            //cout<< "minus " <<_ue - _uf;
            // if(_af < _ae && _uf < _ue && _size > 0)
            //     return true;
            // if(_af == 0 && _ae == 0 && _uf == 0 && _ue == 0 && _size == 0)
            //     return true;
            // return false;
            return (!_ae && !_af && !_ue && !_uf) ||
                ((_af <= _uf) && (_uf <= _ue) && (_ue <= _ae));
        }

        my_deque(my_deque& that, size_type s): _a(that._a), _a2(){
            _uf = _af = _a.allocate(s);
            _out_b = _out_e = 0;
            _in_b = _in_e;
            _ue = _ae = _uf + s;
            uninitialized_copy(_a, that.begin(), that.end(), begin());
            assert(valid());
        }

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename my_deque::value_type      value_type;
                typedef typename my_deque::difference_type difference_type;
                typedef typename my_deque::pointer         pointer;
                typedef typename my_deque::reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs an iterator reference 
                 * @param rhs an iterator reference
                 * reutrn true if rhs and lhs are pointing the same location
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    // <your code>
                    return (lhs._p == rhs._p) && (lhs._d == rhs._d);}

                /**
                 * @param lhs an iterator reference 
                 * @param rhs an iterator reference
                 * return true if lhs and rhs are not on the same location
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs an iterator value
                 * @param rhs a difference_type value
                 * return the sum of two value to lhs
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs an iterator value
                 * @param rhs a difference_type value
                 * return the subtraction of two values to lhs.
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
                size_type _p;
                my_deque* _d;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return _p >= 0;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * construct an iterator for a my_deque object
                 */
                iterator (my_deque* d = nullptr, size_type i = 0): _d(d), _p(i) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * return reference to the value at iterator location
                 */
                reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    return (*_d)[_p];}

                // -----------
                // operator ->
                // -----------

                /**
                 * return pointer to the value at iterator location
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * move the pointer to next element in my_deque
                 * return iterator reference 
                 */
                iterator& operator ++ () {
                    // <your code>
                    assert(valid());
                    _p++;
                    return *this;}

                /**
                 * @param int is same as this
                 * increment this
                 * return iterator
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * move the pointer to previous element in my_deque
                 * return iterator reference 
                 */
                iterator& operator -- () {
                    // <your code>
                    assert(valid());
                    _p--;
                    return *this;}

                /**
                 * @param int is same as this
                 * decrement this
                 * return iterator
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * @param d a diference_type
                 * move the reference forward with d elements
                 * return reference to iterator
                 */
                iterator& operator += (difference_type d) {
                    // <your code>
                    assert(valid());
                    _p += d;
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d a diference_type
                 * move the reference backward with d elements
                 * return reference to iterator
                 */
                iterator& operator -= (difference_type d) {
                    // <your code>
                    assert(valid());
                    _p -= d;
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename my_deque::value_type      value_type;
                typedef typename my_deque::difference_type difference_type;
                typedef typename my_deque::const_pointer   pointer;
                typedef typename my_deque::const_reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs a const const_iterator reference 
                 * @param rhs a const const_iterator reference 
                 * return true if the lhs and rhs are pointing the same location
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    // <your code>
                    return (lhs._p == rhs._p) && (lhs._d == rhs._d);}

                /**
                 * @param lhs a const const_iterator reference 
                 * @param rhs a const const_iterator reference 
                 * return true if the lhs and rhs are not pointing the same location
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs a const_iterator 
                 * @param rhs a difference_type
                 * return lhs with the sum of lhs and rhs
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs a const_iterator 
                 * @param rhs a difference_type
                 * return lhs with the subtraction of lhs and rhs
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
                size_type _p;
                const my_deque* _d;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return _p >= 0;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator (const my_deque* d, size_type i = 0): _d(d), _p(i) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * return reference to the value at iterator location
                 */
                reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    return (*_d)[_p];}

                // -----------
                // operator ->
                // -----------

                /**
                 * return pointer to the value at iterator location
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * move the pointer to next element in my_deque
                 * return const_iterator reference 
                 */
                const_iterator& operator ++ () {
                    // <your code>
                    _p++;
                    assert(valid());
                    return *this;}

                /**
                 * @param int is same as this
                 * increment this
                 * return const_iterator
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * move the pointer to previous element in my_deque
                 * return const_iterator reference 
                 */
                const_iterator& operator -- () {
                    // <your code>
                    this->_p--;
                    assert(valid());
                    return *this;}

                /**
                 * @param int is same as this
                 * decrement this
                 * return const_iterator
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * @param d a diference_type
                 * move the reference forward with d elements
                 * return reference to const_iterator
                 */
                const_iterator& operator += (difference_type d) {
                    // <your code>
                    _p += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d a diference_type
                 * move the reference backward with d elements
                 * return reference to const_iterator
                 */
                const_iterator& operator -= (difference_type d) {
                    // <your code>
                    _p -= d;
                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * @param a an allocator_type reference
         * set inner,outer array, capacity to size 0
         */
        explicit my_deque (const allocator_type& a = allocator_type()): _a(a), _a2() {
            // <your code>
            _a = a;
            _out_b = 0;
            _out_e = 0;
            _in_b = 0;
            _in_e = 0;
            _ue = 0;
            _uf = 0;
            _ae = 0;
            _af = 0;
            _size = 0;
            _capacity = 0;
            assert(valid());}

        /**
         * @param s a size_type
         * @param v a const_reference 
         * @param a an allocator_type reference
         * construct an instance with s, v, a given value.
         */
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()): _a(a), _a2() {
            // <your code>
            _size = s;           

            size_type inner = s / WIDTH;
            if (s % WIDTH > 0)
                inner++;
                
            _out_b = _a2.allocate(inner);
            _out_e = _out_b + inner;
            for (size_type i = 0; i < inner; i++)
                _out_b[i] = _a.allocate(WIDTH);

            _in_b = _out_b[0];
            _in_e = _out_b[inner-1] + s - WIDTH*(inner-1);

            for (size_type i = 0; i < inner; ++i) {
                _a.deallocate(_out_b[i], WIDTH);
            }

            _a2.deallocate(_out_b, inner);
            _af = _uf = _a.allocate(s);
            _ae = _ue = _uf + s;

            _capacity = _ae - _af;

            uninitialized_fill(_a, begin(), end(), v);
            assert(valid());}

        /**
         * @param that is a my_deque reference 
         * copy constructor that constrcut a new instance with my_deque content
         */
        my_deque (const my_deque& that):_a (that._a), _a2() {
            // <your code>
            _out_b = _out_e = 0;
            _in_b = _in_e;
            _af = _uf = _a.allocate(that.size());
            _ae = _ue = _af + that.size();
            _capacity = _ae - _af;
            _size = that._size;

            uninitialized_copy(_a, that.begin(), that.end(), begin());
            cout<<"this"<<endl;
            for(int i = 0; i < 5; i ++)
                cout << *this[i] <<endl;
            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
         * deallocate the my_deque
         */
        ~my_deque () {
            // <your code>
            if(_af > 0){
                clear();
                _a.deallocate(_af, _capacity);
                _size = 0;
            }
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * @param rhs a my_deque reference
         * copy my_deque instance
         * return my_deque reference
         */
        my_deque& operator = (const my_deque& rhs) {
            // <your code>
            if (this == &rhs){
                cout <<"==  "<<endl;
                return *this;
            }
            if (rhs.size() == size()){
                cout <<"size "<<endl;
                std::copy(rhs.begin(), rhs.end(), begin());
            }
            else if (rhs.size() < size()) {
                cout <<"< "<<endl;
                std::copy(rhs.begin(), rhs.end(), begin());
                resize(rhs.size());}
            else if (rhs.size() <= _capacity) {
                cout <<"<= "<<endl;
                std::copy(rhs.begin(), rhs.begin() + size(), begin());
                _ue = &(*uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end()));
            }
            else {
                cout <<"else "<<endl;
                clear();
                my_deque x(rhs);
                swap(x);}
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * @param index a size_type
         * index the position in the deque
         * return reference of where it is
         */
        reference operator [] (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            return *(_uf+index);}

        /**
         * @param index a size_type
         * index the position in the deque
         * reutrn const_reference of where it is
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * @param index a size_type
         * index the position in the deque 
         * throw out_of_range exception if access if not in the range
         * return reference to value of my_deque
         */
        reference at (size_type index) throw (std:: out_of_range){
            // <your code>
            if(index >= size())
                throw std::out_of_range("Deque");
            return (*this)[index];}

        /**
         * @param index a size_type
         * index the position in the deque 
         * throw out_of_range exception if access if not in the range
         * return const_reference to value of my_deque
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * return reference to last element in deque
         */
        reference back () {
            // <your code>
            assert(!empty());
            return *(_ue - 1);
            // dummy is just to be able to compile the skeleton, remove it
            // static value_type dummy;
            // return dummy;
        }

        /**
         * return const_reference to last element in deque
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * return reference to first element in deque
         */
        iterator begin () {
            // <your code>
            return iterator(this, 0);}

        /**
         * return const_reference to first element in deque
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(this, 0);}

        // -----
        // clear
        // -----

        /**
         * make array size to 0
         */
        void clear () {
            // <your code>
            resize(0);
            _size = 0;
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * remove all elements in deque
         */
        bool empty () const {
            return size() == 0;}

        // ---
        // end
        // ---

        /**
         * return iterator to value at the end of deque
         */
        iterator end () {
            // <your code>
            //cout<<"here2!!!!!!!!!!!!!!"<<endl;
            //cout<<"size "<<size()<<endl;
            return iterator(this, size() );}

        /**
         * return const_iterator to the end of deque
         */
        const_iterator end () const {
            // <your code>
            //cout<<"here!!!!!!!!!!!!!!"<<endl;
            //cout<<size()<<endl;
            return const_iterator(this, size()-1);}

        // -----
        // erase
        // -----

        /**
         * @param iterator a iterator
         * remove value at iterator location from deque
         * every element will move forward
         * return next loation of iterator
         */
        iterator erase (iterator p) {
            // <your code>
            if(p == end() - 1)
                pop_back();
            else {
                std::copy(p+1, end(), p);
                resize(size()-1);}
            _size--;
            assert(valid());
            return iterator(this);}

        // -----
        // front
        // -----

        /**
         * return reference to value at the front of the deque
         */
        reference front () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            assert(!empty());
            return *begin();}

        /**
         * return const_reference to value at the front of the deque
         */
        const_reference front () const {
            return const_cast<my_deque&>(*this).front();}

        // ------
        // insert
        // ------

        /**
         * @param iterator an iterator
         * @param const_reference
         * insert value at given position
         * push the remaining elements backward in the deque
         * return iterator to where the value is
         */
        iterator insert (iterator p, const_reference v) {
            // <your code>
           if(p == end())
                push_back(v);
            else if(p == begin())
                push_front(v);
            else {
                resize(size()+1);
                iterator it = end();
                while(it != p-1){
                    *it = *(it-1);
                    it--; 
                }
                *p = v;
                }
            assert(valid());
            return iterator();}

        // ---
        // pop
        // ---

        /**
         * remove element of the back of the deque
         */
        void pop_back () {
            // <your code>               x.push_back(4);cout<<"2 "<<x[2]<<endl;

            assert(!empty() );
            //cout <<"here!!!!!"<<endl;
            resize(size() - 1);
            _size--;
            //cout<<"ue2 "<<_ue<<endl;
            assert(valid());}

        /**
         * remove element of the front of the deque
         */
        void pop_front () {
            // <your code>
            destroy(_a, begin(), begin()+1);
            ++_uf;
            _size--;
            assert(valid());}

        // ----
        // push
        // ----

        /**
         * add element of the back of the deque
         */
        void push_back (const_reference v) {
            // <your code>    
            //cout<<"push back"<<endl;      
            resize(size() + 1, v);

            _size++;
            assert(valid());}

        /**
         * add element of the front of the deque
         */
        void push_front (const_reference v) {
            // <your code>
            if (_af == _uf) 
                resize(size() + 1);

            std::copy(begin(), end(), begin()+1);
            _a.construct(&*begin(), v);           
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * @param s a size_type
         * @param v a const_reference
         * resize the deque to given size.
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>

            if (s == size()){
                //cout << "=="<<endl;
                return;
            }
            if (s < size()){
                //cout << "<"<<endl;
                //cout<<"s "<<s<<endl;
                _ue = &*destroy(_a, begin() + s, end());
                //cout<<"ue "<<_ue<<endl;
            }
            else if (s <= _capacity){
                //cout << "<="<<endl;
                _ue = &*uninitialized_fill(_a, end(), begin() + s, v);
            }
            else {
                //cout <<"else\n";
                size_type si = std::max(2*size()+1, s);
                my_deque x(si, v);
                std::copy(begin(), end(), x.begin());
                //_uf = x.begin();
                //_ue = x.end();
                swap(x);
                resize(s, v);
            }
            _size = _ue - _uf;
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * reutrn size of deque
         */
        size_type size () const {
            // <your code>
            return _ue-_uf;
        }

        // ----
        // swap
        // ----

        /**
         * @param my_deque reference
         * sway the contents to another deque
         */
        void swap (my_deque& that) {
            // <your code>
            if (_a == that._a) {
                std::swap(_ue, that._ue);
                std::swap(_uf, that._uf);
                std::swap(_ae, that._ae);
                std::swap(_af, that._af);}
            else {
                my_deque x(*this);
                *this = that;
                that  = x;}
            assert(valid());}};


#endif // Deque_h
