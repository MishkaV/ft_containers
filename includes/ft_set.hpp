/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:59:33 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/15 20:59:34 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SET_HPP
# define FT_SET_HPP

# include <memory>
# include "ft_iterator.hpp"
# include "ft_rbtree.hpp"

namespace ft {
    template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set {

    public:
        /*
         * Member types
         */
        typedef Key key_type;
        typedef Key value_type;
        typedef size_t size_type;
        typedef Compare key_compare;
        typedef key_compare value_compare;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

    private:
        typedef rbtree <value_type, value_compare, allocator_type> _rbtree;
        _rbtree tree;

    public:

        typedef typename _rbtree::const_iterator const_iterator;
        typedef typename _rbtree::iterator iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator <iterator> reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;



        /*
         * Member functions
         */

        /*
         * Constructors
         */
        explicit set(
                const key_compare &comp = key_compare(),
                const allocator_type &alloc = allocator_type()
        ) : tree(comp, alloc) {};

        template<class InputIt>
        set(
                InputIt first,
                InputIt last,
                const Compare &comp = key_compare(),
                const Allocator &alloc = allocator_type()
        ): tree(comp, alloc) {
            insert(first, last);
        }

        set(const set &other) : tree(other.tree) {
            insert(other.begin(), other.end());
        }


        /*
         * Destructor
         */
        ~set() {}


        /*
         * operator=
         */
        set &operator=(const set &other) {
            tree = other.tree;
            return *this;
        }

        /*
         * get_allocator
         */
        allocator_type get_allocator() const { return tree.get_allocator_type(); }


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

        void swap(set &other) { tree.swap(other.tree); }


        /*
         * Lookup
         */
        size_type count(const Key &key) const { return tree.template set_count(key); }

        iterator find(const Key &key) { return tree.template set_find(key); }

        const_iterator find(const Key &key) const { return tree.template set_find(key); }

        pair <iterator, iterator> equal_range(const Key &key) { return tree.template set_range_equal(key); }

        pair <const_iterator, const_iterator>
        equal_range(const Key &key) const { return tree.template set_range_equal(key); }

        iterator lower_bound(const Key &key) { return tree.template set_lower_bound(key); }

        const_iterator lower_bound(const Key &key) const { return tree.template set_lower_bound(key); }

        iterator upper_bound(const Key &key) { return tree.template set_upper_bound(key); }

        const_iterator upper_bound(const Key &key) const { return tree.template set_upper_bound(key); }
    };
}


#endif