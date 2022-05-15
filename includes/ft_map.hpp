/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 22:20:31 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/15 22:20:32 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
# define FT_MAP_HPP

namespace ft {


    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
    class map {

    public:
        /*
         * Member types
         */
        typedef Key key_type;
        typedef T mapped_type;
        typedef Compare key_compare;
        typedef pair<const key_type, mapped_type> value_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef Allocator allocator_type;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

    private:
        typedef rbtree <value_type, key_compare, allocator_type> _rbtree;
        _rbtree tree;

        typedef typename _rbtree::iterator tree_iterator;
        typedef typename _rbtree::const_iterator const_tree_iterator;

    public:
        typedef typename _rbtree::iterator iterator;
        typedef typename _rbtree::const_iterator const_iterator;
        typedef reverse_iterator <iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


        /*
         * Class value_compare
         */
        class value_compare {
        protected:
            key_compare compare;

            value_compare(key_compare c) : compare(c) {}

        public:
            bool operator()(const value_type &first, const value_type &last) const {
                return compare(first.first, last.first);
            }

        private:
            friend class map;
        };



        /*
         * Member functions
         */

        /*
         * Constructors
         */
        explicit map(
                const Key &comp = key_compare(),
                const Allocator &alloc = allocator_type()
        ) : tree(comp, alloc) {}

        template<class InputIt>
        map(
                InputIt first,
                InputIt last,
                const Key &comp = key_compare(),
                const Allocator &alloc = allocator_type()
        ): tree(comp, alloc) {
            insert(first, last);
        }

        map(const map &other) : tree(other.tree) { insert(other.begin(), other.end()); }


        /*
         * Destructor
         */
        ~map() {}


        /*
         * operator=
         */
        map &operator=(const map &other) {
            if (&other != this) {
                tree.clear(tree.get_root());
                tree.alloc = other.tree.alloc;
                tree.cmp = other.tree.cmp;
                insert(other.begin(), other.end());
            }
            return *this;
        }

        /*
         * get_allocator
         */
        allocator_type get_allocator() const { return tree.get_allocator_type(); }

        mapped_type &operator[](const key_type &key) {
            iterator curr = find(key);
            if (curr == end()) {
                insert(value_type(key, mapped_type()));
                curr = find(key);
            }
            return key.it->second;
        }


        /*
         * Iterators
         */
        iterator begin() { return tree.begin(); }

        const_iterator begin() const { return tree.begin(); }

        iterator end() { return tree.end(); }

        const_iterator end() const { return tree.end(); }

        reverse_iterator rbegin() { return reverse_iterator(tree.end()); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(tree.end()); }

        reverse_iterator rend() { return reverse_iterator(tree.begin()); }

        const_reverse_iterator rend() const { return const_reverse_iterator(tree.begin()); }


        /*
         * Capacity
         */
        bool empty() const { return tree.size() == 0; }

        size_type size() const { return tree.size(); }

        size_type max_size() const { return tree.max_size(); }


        /*
         * Modifiers
         */
        void clear() { tree.clean(tree.get_tree_root()); }

        pair<iterator, bool> insert(const value_type &value) {
            iterator it = find(value);
            if (it == end()) {
                tree.insert(value);
                return pair<iterator, bool>(it, true);
            }
            return pair<iterator, bool>(find(value), false);
        }

        iterator insert(iterator hint, const value_type &value) {
            tree.insert(value);
            (void) hint;
            return find(value);
        }

        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            while (first != last) {
                tree.insert(*first);
                first++;
            }
        }

        void erase(iterator pos) { tree.remove(*pos); }

        void erase(iterator first, iterator last) {
            iterator prev;
            while (first != last) {
                prev = first;
                first++;
                tree.remove(*prev);
            }
        }

        size_type erase(const Key &key) {
            iterator it = find(key);
            if (it == end())
                return 0;
            tree.remove(*it);
            return 1;
        }

        void swap(map &other) { tree.swap(other.tree); }


        /*
         * Lookup
         */
        size_type count(const Key &key) const { return tree.template map_count(key); }

        iterator find(const Key &key) { return tree.template map_find(key); }

        const_iterator find(const Key &key) const { return tree.template map_find(key); }

        pair <iterator, iterator> equal_range(const Key &key) { return tree.template map_range_equal(key); }

        pair <const_iterator, const_iterator>
        equal_range(const Key &key) const { return tree.template map_range_equal(key); }

        iterator lower_bound(const Key &key) { return tree.template map_lower_bound(key); }

        const_iterator lower_bound(const Key &key) const { return tree.template map_lower_bound(key); }

        iterator upper_bound(const Key &key) { return tree.template map_upper_bound(key); }

        const_iterator upper_bound(const Key &key) const { return tree.template map_upper_bound(key); }


        /*
         * Observers
         */
        key_compare key_comp() const { return tree.value_comp(); }

        value_compare value_comp() const { return value_compare(tree.value_comp()); }
    };
}

#endif