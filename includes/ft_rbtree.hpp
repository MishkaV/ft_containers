/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rbtree.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:12:37 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/14 14:12:38 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_HPP
# define FT_TREE_HPP

# include <algorithm>
# include <memory>
# include "ft_iterator.hpp"
# include "ft_extensions.hpp"
# include "ft_pair.hpp"


namespace ft {

    /*
     * Node for red-black tree
     */
    template<class T>
    class rbnode {

    public:
        typedef T value_type;
        typedef rbnode<T> *pointer_node;

        bool is_black;
        pointer_node left;
        pointer_node right;
        pointer_node parent;
        pointer_node value;

    private:
        rbnode() {};

        rbnode(const rbnode &) {};

        ~rbnode() {};
    };

    template<class PNode>
    PNode max_node(PNode root) {
        while (root->right)
            root = root->right;
        return root;
    }

    template<class PNode>
    PNode min_node(PNode root) {
        while (root->left)
            root = root->left;
        return root;
    }

    template<class PNode>
    PNode get_next_iterator(PNode root) {
        if (root->right)
            return min_node(root->right);
        while (root != root->parent->left)
            root = root->parent;
        return root->parent;
    }

    template<class PNode>
    PNode get_prev_iterator(PNode root) {
        if (root->left)
            return max_node(root->left);
        while (root == root->parent->left)
            root = root->parent;
        return root->parent;
    }


    /*
     * Iterator for red-black tree
     */
    template<class T, class PNode>
    class iterator_rbtree {

    public:
        typedef T value_type;
        typedef PNode pointer_node;
        typedef value_type *pointer;
        typedef value_type &reference;

    private:
        pointer_node current;

    private:
        explicit iterator_rbtree(pointer_node node) : current(node) {}

        template<class> friend
        class map_iterator;

        template<class, class> friend
        class const_iterator_rbtree;

        template<class, class, class> friend
        class rbtree;

        template<class, class, class> friend
        class set;

        template<class, class, class, class> friend
        class map;

    public:
        iterator_rbtree() : current() {};

        iterator_rbtree(const iterator_rbtree &tree) : current(tree.current) {};

        /*
         * Operators
         */
        friend bool operator==(const iterator_rbtree &rhs, const iterator_rbtree &lhs) {
            return rhs.ptr == lhs.ptr;
        }

        friend bool operator!=(const iterator_rbtree &rhs, const iterator_rbtree &lhs) {
            return rhs.ptr != lhs.ptr;
        }

        reference operator->() const {
            return &(current->value);
        }

        reference operator*() const {
            return current->value;
        }

        iterator_rbtree &operator++() const {
            current = get_next_iterator<PNode>(current);
            return *this;
        }

        iterator_rbtree operator++(int) const {
            iterator_rbtree curr(*this);
            (*this)++;
            return *curr;
        }

        iterator_rbtree &operator--() const {
            current = get_prev_iterator<PNode>(current);
            return *this;
        }

        iterator_rbtree operator--(int) const {
            iterator_rbtree curr(*this);
            (*this)--;
            return *curr;
        }

    };


    /*
     * Const Iterator for red-black tree
     */
    template<class T, class PNode>
    class const_iterator_rbtree {

    public:
        typedef T value_type;
        typedef PNode pointer_node;
        typedef value_type *pointer;
        typedef value_type &reference;

    private:
        pointer_node current;

    private:
        explicit const_iterator_rbtree(pointer_node node) : current(node) {}

        template<class> friend
        class map_iterator;

        template<class, class, class> friend
        class rbtree;

        template<class, class, class> friend
        class set;

        template<class, class, class, class> friend
        class map;

    public:
        const_iterator_rbtree() : current() {};

        const_iterator_rbtree(const const_iterator_rbtree &tree) : current(tree.current) {};

        /*
         * Operators
         */
        friend bool operator==(const const_iterator_rbtree &rhs, const const_iterator_rbtree &lhs) {
            return rhs.ptr == lhs.ptr;
        }

        friend bool operator!=(const const_iterator_rbtree &rhs, const const_iterator_rbtree &lhs) {
            return rhs.ptr != lhs.ptr;
        }

        reference operator->() const {
            return *this;
        }

        reference operator*() const {
            return current->value;
        }

        const_iterator_rbtree &operator++() const {
            current = get_next_iterator<PNode>(current);
            return *this;
        }

        const_iterator_rbtree operator++(int) const {
            const_iterator_rbtree curr(*this);
            (*this)++;
            return *curr;
        }

        const_iterator_rbtree &operator--() const {
            current = get_prev_iterator<PNode>(current);
            return *this;
        }

        const_iterator_rbtree operator--(int) const {
            const_iterator_rbtree curr(*this);
            (*this)--;
            return *curr;
        }
    };


    /*
     * Red-black tree
     */
    template<class T, class Compare, class Allocator>
    class rbtree {

    public:
        /*
         * Member types
         */
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef Compare compare_value;
        typedef rbnode<T> node;
        typedef typename node::pointer_node pointer_node;
        typedef iterator_rbtree<T, pointer_node> iterator;
        typedef const_iterator_rbtree<T, pointer_node> const_iterator;

    private:
        /*
         * Member types
         * [begin_node] - first element for iteration; default - min
         * [end_node] - last element for iteration; default - max
         */
        pointer_node root;
        pointer_node begin_node;
        pointer_node end_node;
        size_type total_size;
        allocator_type alloc;
        compare_value compare;

    public:
        /*
         * Constructors
         */
        rbtree(
                const rbtree &tree
        ) : root(tree.root), begin_node(tree.begin_node), end_node(tree.end_node), alloc(tree.alloc),
            compare(tree.compare), total_size(tree.size) {};

        explicit rbtree(
                compare_value const &compare,
                allocator_type const &alloc
        ) : compare(compare), alloc(alloc), root(0), begin_node(0), end_node(0), total_size(0) {};


        /*
         * Destructor
         */
        ~rbtree() { this->clean(root); }


        /*
         * Member functions
         */
        pointer_node &get_tree_root() { return root; }

        compare_value &get_compare_value() { return compare; }

        allocator_type get_allocator_type() { return alloc; }

        size_type max_size() const;

        size_type size() const { return total_size; }

        void insert(const value_type &val);

        void remove(const value_type &val);

        void clean(pointer_node &node);

        void swap(rbtree &other);

        template<class K>
        iterator map_find(const K &key);

        template<class K>
        pair <iterator, iterator> map_range_equal(const K &key);

        template<class K>
        iterator map_count(const K &key);

        template<class K>
        iterator map_lower_bound(const K &key);

        template<class K>
        iterator map_upper_bound(const K &key);

        template<class K>
        iterator set_find(const K &key);

        template<class K>
        pair <iterator, iterator> set_range_equal(const K &key);

        template<class K>
        iterator set_count(const K &key);

        template<class K>
        iterator set_lower_bound(const K &key);

        template<class K>
        iterator set_upper_bound(const K &key);


        /*
         * Iterators
         */
        iterator begin();

        const_iterator begin() const;

        iterator end();

        const_iterator end() const;
    };


    /*
     * Member functions
     */
    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::size_type
    rbtree<T, Compare, Allocator>::max_size() const {
        return std::min<T>(std::numeric_limits<size_type>::max(), this->alloc.max_size());;
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::insert(const value_type &val) {
        //TODO
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::remove(const value_type &val) {
        //TODO
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::clean(rbtree::pointer_node &node) {
        if (!node)
            return;
        clean(node->right);
        clean(node->left);
        alloc.destroy(node->value);
        alloc.deallocate(reinterpret_cast<value_type *>(node), 1);
        node = 0;
        total_size = 0;
        begin_node = min_node(root);
        end_node = max_node(root); //TODO?
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::swap(rbtree &other) {
        pointer_node new_root = other.root;
        pointer_node new_begin_node = other.begin_noder;
        pointer_node new_end_node = other.end_node;
        size_type new_total_size = other.total_size;
        allocator_type new_alloc = other.alloc;
        compare_value new_compare = other.compare;

        other.root = root;
        other.begin_noder = begin_node;
        other.end_node = end_node;
        other.total_size = total_size;
        other.alloc = alloc;
        other.compare = compare;

        root = new_root;
        begin_node = new_begin_node;
        end_node = new_end_node;
        total_size = new_total_size;
        alloc = new_alloc;
        compare = new_compare;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    typename rbtree<T, Compare, Allocator>::iterator
    rbtree<T, Compare, Allocator>::map_find(const K &key) {
        iterator it = map_lower_bound(key);
        if (!compare(key, (*it).first))
            return it;
        return end_node;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    pair<typename rbtree<T, Compare, Allocator>::iterator, typename rbtree<T, Compare, Allocator>::iterator>
    rbtree<T, Compare, Allocator>::map_range_equal(const K &key) {
        return pair<iterator, iterator>(map_lower_bound(key), map_upper_bound(key));
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    typename rbtree<T, Compare, Allocator>::iterator
    rbtree<T, Compare, Allocator>::map_count(const K &key) {
        pointer_node curr = root;

        while (curr) {
            if (compare(curr->value.first, key))
                curr = curr->right;
            else if (compare(key, curr->value.first))
                curr = curr->left;
            else
                return 1;
        }
        return 0;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    typename rbtree<T, Compare, Allocator>::iterator
    rbtree<T, Compare, Allocator>::map_lower_bound(const K &key) {
        pointer_node curr = root;
        pointer_node to_return = end_node;

        while (curr) {
            if (!compare(curr->value.first, key)) {
                to_return = curr;
                to_return = to_return->left;
            } else
                to_return = to_return->right;
        }
        return to_return;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    typename rbtree<T, Compare, Allocator>::iterator
    rbtree<T, Compare, Allocator>::map_upper_bound(const K &key) {
        pointer_node curr = root;
        pointer_node to_return = end_node;

        while (curr) {
            if (compare(curr->value.first, key)) {
                to_return = curr;
                to_return = to_return->left;
            } else
                to_return = to_return->right;
        }
        return to_return;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    typename rbtree<T, Compare, Allocator>::iterator
    rbtree<T, Compare, Allocator>::set_find(const K &key) {
        iterator it = map_lower_bound(key);
        if (!compare(key, *it))
            return it;
        return end_node;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    typename rbtree<T, Compare, Allocator>::iterator
    rbtree<T, Compare, Allocator>::set_count(const K &key) {
        pointer_node curr = root;

        while (curr) {
            if (compare(curr->value, key))
                curr = curr->right;
            else if (compare(key, curr->value))
                curr = curr->left;
            else
                return 1;
        }
        return 0;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    typename rbtree<T, Compare, Allocator>::iterator
    rbtree<T, Compare, Allocator>::set_lower_bound(const K &key) {
        pointer_node curr = root;
        pointer_node to_return = end_node;

        while (curr) {
            if (!compare(curr->value, key)) {
                to_return = curr;
                to_return = to_return->left;
            } else
                to_return = to_return->right;
        }
        return to_return;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    typename rbtree<T, Compare, Allocator>::iterator
    rbtree<T, Compare, Allocator>::set_upper_bound(const K &key) {
        pointer_node curr = root;
        pointer_node to_return = end_node;

        while (curr) {
            if (compare(curr->value, key)) {
                to_return = curr;
                to_return = to_return->left;
            } else
                to_return = to_return->right;
        }
        return to_return;
    }

    template<class T, class Compare, class Allocator>
    template<class K>
    pair<typename rbtree<T, Compare, Allocator>::iterator, typename rbtree<T, Compare, Allocator>::iterator>
    rbtree<T, Compare, Allocator>::set_range_equal(const K &key) {
        return pair<iterator, iterator>(set_lower_bound(key), set_upper_bound(key));
    }


    /*
     * Iterators
     */
    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::iterator rbtree<T, Compare, Allocator>::begin() {
        return begin_node;
    }

    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::const_iterator rbtree<T, Compare, Allocator>::begin() const {
        return begin_node;
    }

    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::iterator rbtree<T, Compare, Allocator>::end() {
        return end_node;
    }

    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::const_iterator rbtree<T, Compare, Allocator>::end() const {
        return end_node;
    }
}

#endif