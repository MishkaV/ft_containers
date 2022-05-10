/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 21:05:00 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/07 21:05:01 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include "ft_iterator.hpp"


namespace ft {

    /*
     * Vector class
     */
    template<class T, class Allocator = std::allocator<T> >
    class vector {

    public:
        /*
         * Member types
         */
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename ft::iterator_traits<pointer>::pointer iterator;
        typedef typename ft::iterator_traits<const_pointer>::pointer const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

        /*
         * Member functions - [Constructors]
         */
        explicit vector(
                const allocator_type &alloc = allocator_type()
        ) : alloc(alloc), vec_begin(0), vec_end(0), vec_capacity(0) {};

        explicit vector(
                size_type count,
                const value_type &value = value_type(),
                const allocator_type &alloc = allocator_type()
        );

        template<class InputIterator>
        vector(
                InputIterator first,
                InputIterator last,
                const allocator_type &alloc = allocator_type()
        );

        vector(const vector &x);

        /*
         * Member functions - [Destructor]
         */
        ~vector();

        /*
         * Member functions - [operator=]
         */
        vector &operator=(const vector &other);

        /*
         * Member functions - [assign]
         */
        void assign(size_type count, const value_type &value);

        // TODO?
        template<class InputIterator>
        void assign(InputIterator first, InputIterator last);

        /*
         * Member functions - [get_allocator]
         */
        allocator_type get_allocator() const;

        /*
         * Element access
         */
        reference at(size_type pos);

        const_reference at(size_type pos) const;


        reference operator[](size_type pos);

        const_reference operator[](size_type pos) const;


        reference front();

        const_reference front() const;


        reference back();

        const_reference back() const;

        /*
         * Iterators
         */
        iterator begin();

        const_iterator begin() const;


        iterator end();

        const_iterator end() const;


        reverse_iterator rbegin();

        const_reverse_iterator rbegin() const;


        reverse_iterator rend();

        const_reverse_iterator rend() const;

        /*
         * Capacity
         */
        bool empty() const;

        size_type size() const;

        size_type max_size() const;

        void reserve(size_type new_cap);

        size_type capacity() const;

        /*
         * Modifiers
         */
        void clear();


        iterator insert(iterator pos, const value_type &value);

        void insert(iterator pos, size_type count, const value_type &value);

        // TODO?
        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last);


        iterator erase(iterator pos);

        iterator erase(iterator first, iterator last);


        void push_back(const value_type &value);

        void pop_back();

        void resize(size_type count, value_type value = value_type());

        void swap(vector &other);

    private:
        allocator_type alloc;
        pointer vec_begin;
        pointer vec_end;
        pointer vec_capacity;

        void free_vector();
    };


    /*
     * Realization
     */

    /*
     * Member functions - [Constructors]
     */
    template<class T, class Allocator>
    vector<T, Allocator>::vector(
            vector::size_type count,
            const value_type &value,
            const allocator_type &alloc
    ) : alloc(alloc), vec_begin(0), vec_end(0), vec_capacity(0) {
        if (count > 0) {
            if (max_size() < 2 * count)
                throw std::length_error("Max capacity of vector");

            this->vec_begin = this->vec_end = this->alloc.allocate(2 * count);
            vec_capacity = vec_begin + 2 * count;

            for (size_t i = 0; i < count; i++) {
                this->alloc.construct(this->vec_end, value);
                this->vec_end++;
            }
        }
    }

    template<class T, class Allocator>
    template<class InputIterator>
    vector<T, Allocator>::vector(
            InputIterator first,
            InputIterator last,
            const allocator_type &alloc
    ): alloc(alloc), vec_begin(0), vec_end(0), vec_capacity(0) {
        while (first != last) {
            push_back(*first);
            first++;
        }
    }

    template<class T, class Allocator>
    vector<T, Allocator>::vector(const vector &x): alloc(x.alloc), vec_begin(0), vec_end(0), vec_capacity(0) {
        size_t len = x.size();

        if (len > 0) {
            if (max_size() < 2 * len)
                throw std::length_error("Max capacity of vector");

            this->vec_begin = this->vec_end = this->alloc.allocate(2 * len);
            vec_capacity = vec_begin + 2 * len;

            pointer begin_x = x.vec_begin;
            for (size_t i = 0; i < len; i++) {
                this->alloc.construct(this->vec_end, *begin_x);
                this->vec_end++;
                begin_x++;
            }

        }
    }


    /*
     * Member functions - [Destructor]
     */
    template<class T, class Allocator>
    vector<T, Allocator>::~vector() {
        this->clear();
    }


    /*
     * Member functions - [operator=]
     */
    template<class T, class Allocator>
    vector<T, Allocator> &vector<T, Allocator>::operator=(const vector &other) {
        if (this == &other)
            return *this;
        this->clear();
        this->alloc = other.alloc;
        for (pointer begin = other.vec_begin; begin != other.vec_end; begin++)
            this->push_back(*begin);
        return *this;
    }


    /*
     * Member functions - [assign]
     */
    template<class T, class Allocator>
    void vector<T, Allocator>::assign(vector::size_type count, const value_type &value) {
        this->clear();
        for (size_t i = 0; i < count; i++)
            this->push_back(value);
    }

    template<class T, class Allocator>
    template<class InputIterator>
    void vector<T, Allocator>::assign(InputIterator first, InputIterator last) {
        this->clear();
        while (first != last) {
            this->push_back(*first);
            first++;
        }
    }


    /*
     * Member functions - [get_allocator]
     */
    template<class T, class Allocator>
    typename vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const {
        return this->alloc;
    }


    /*
     * Element access
     */
    template<class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::at(vector::size_type pos) {
        if (pos >= this->size())
            throw std::out_of_range("Position out of range");
        return *(this->vec_begin + pos);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(vector::size_type pos) const {
        if (pos >= this->size())
            throw std::out_of_range("Position out of range");
        return *(this->vec_begin + pos);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](vector::size_type pos) {
        if (pos >= this->size())
            throw std::out_of_range("Position out of range");
        return *(this->vec_begin + pos);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](vector::size_type pos) const {
        if (pos >= this->size())
            throw std::out_of_range("Position out of range");
        return *(this->vec_begin + pos);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
        return *(this->vec_begin);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const {
        return *(this->vec_begin);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
        return *(this->vec_end - 1);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const {
        return *(this->vec_end - 1);
    }


    /*
     * Iterators
     */




    /*
     * Capacity
     */
    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const {
        return static_cast<size_type>(this->vec_end - this->vec_begin);
    }

    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const {
        //TODO?
        return std::min<T>(std::numeric_limits<size_type>::max(), this->alloc.max_size());
    }

    template<class T, class Allocator>
    void vector<T, Allocator>::reserve(vector::size_type new_cap) {
        if (this->capacity() < new_cap) {
            pointer new_begin = this->alloc.allocate(new_cap);
            pointer new_end = new_begin;
            for (pointer old_begin = this->vec_begin; old_begin != this->vec_end; old_begin++, new_end++)
                this->alloc.construct(new_end, *old_begin);
            this->vec_begin = new_begin;
            this->vec_end = new_end;
            this->vec_capacity = this->vec_begin + new_cap;
        }
    }


    /*
     * Modifiers
     */
    template<class T, class Allocator>
    void vector<T, Allocator>::clear() {
        this->free_vector();
        this->vec_begin = 0;
        this->vec_end = 0;
        this->vec_capacity = 0;
    }

    template<class T, class Allocator>
    void vector<T, Allocator>::push_back(const value_type &value) {
        if (this->vec_end == this->vec_capacity) {
            size_t new_capacity = this->capacity() > 0 ? 2 * this->capacity() : 2;
            this->reserve(new_capacity);
        }
        this->alloc.construct(this->vec_end, value);
        this->vec_end++;
    }


    template<class T, class Allocator>
    typename vector<T, Allocator>::size_type vector<T, Allocator>::vector::capacity() const {
        return static_cast<size_type>(this->vec_capacity - this->vec_capacity);
    }


    /*
     * Utils functions
     */
    template<class T, class Allocator>
    void vector<T, Allocator>::free_vector() {
        size_t len = this->vec_capacity - this->vec_begin;
        for (size_t i = 0; i < len; i++)
            this->alloc.destroy(this->vec_begin + i);
        this->alloc.deallocate(this->vec_begin, len);
    }

}

#endif
