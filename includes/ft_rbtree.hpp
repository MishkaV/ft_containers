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
        value_type value;

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
        typedef bidirectional_iterator_tag iterator_category;

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
            return rhs.current == lhs.current;
        }

        friend bool operator!=(const iterator_rbtree &rhs, const iterator_rbtree &lhs) {
            return rhs.current != lhs.current;
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
        typedef bidirectional_iterator_tag iterator_category;

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
            return rhs.current == lhs.current;
        }

        friend bool operator!=(const const_iterator_rbtree &rhs, const const_iterator_rbtree &lhs) {
            return rhs.current != lhs.current;
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

        /*
         * Extension functions for tree
         */
        pointer_node &get_grandparent(pointer_node &node);

        pointer_node &get_uncle(pointer_node &node);

        void left_rotation(pointer_node &node);

        void right_rotation(pointer_node &node);

        void optimize_insertion(pointer_node &node);

        void optimize_removing(rbtree::pointer_node &curr, pointer_node &parent);

        void removing_both_child(pointer_node &node);


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
        ) : root(0), begin_node(0), end_node(0), total_size(0), alloc(alloc), compare(compare) {};


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
     * Extension functions for tree
     */
    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::pointer_node &
    rbtree<T, Compare, Allocator>::get_grandparent(rbtree::pointer_node &node) {
        if (node && node->parent)
            return node->parent->parent;
        else
            return 0;
    }

    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::pointer_node &
    rbtree<T, Compare, Allocator>::get_uncle(rbtree::pointer_node &node) {
        pointer_node grand_node = get_grandparent(node);
        if (!grand_node)
            return NULL;
        if (node->parent == grand_node->left)
            return grand_node->right;
        else
            return grand_node->left;
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::left_rotation(rbtree::pointer_node &node) {
        pointer_node curr = node->right;

        curr->parent = node->parent;
        if (node->parent) {
            if (node->parent->left != node)
                node->parent->right = curr;
            else
                node->parent->left = curr;
        }
        node->right = curr->left;
        if (curr->left)
            curr->left->parent = node;
        node->parent = curr;
        curr->left = node;
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::right_rotation(rbtree::pointer_node &node) {
        pointer_node curr = node->left;

        curr->parent = node->parent;
        if (node->parent) {
            if (node->parent->left != node)
                node->parent->right = curr;
            else
                node->parent->left = curr;
        }
        node->left = curr->right;
        if (curr->right)
            curr->right->parent = node;
        node->parent = curr;
        curr->right = node;
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::optimize_insertion(rbtree::pointer_node &node) {
        pointer_node grandparent = node->parent->parent;
        pointer_node uncle;
        if (!grandparent)
            uncle = NULL;
        else if (node->parent == grandparent->left)
            uncle = grandparent->right;
        else
            uncle = grandparent->left;
        pointer_node parent = node->parent;

        if (node == root) {
            node->is_black = true;
            return;
        }

        while (!parent->is_black) {
            if (grandparent && parent == grandparent->left) {
                if (uncle && !uncle->is_black) {
                    parent->is_black = true;
                    uncle->is_black = true;
                    grandparent->is_black = false;
                    node = grandparent;
                } else {
                    if (parent && node == parent->right) {
                        node = parent;
                        left_rotation(node);
                    }
                    parent->is_black = true;
                    grandparent->is_black = false;
                    right_rotation(grandparent);
                }
            } else {
                if (uncle && !uncle->is_black) {
                    parent->is_black = true;
                    uncle->is_black = true;
                    grandparent->is_black = false;
                    node = grandparent;
                } else {
                    if (parent && node == parent->left) {
                        node = node->parent;
                        right_rotation(node);
                    }
                    parent->is_black = true;
                    grandparent->is_black = false;
                    left_rotation(grandparent);
                }
            }
        }

        root->is_black = true;
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::optimize_removing(
            rbtree::pointer_node &curr,
            rbtree::pointer_node &parent
    ) {
        while ((curr->is_black && curr != root) || curr) {
            if (parent->left == curr) {
                if (!parent->right->is_black) {
                    parent->right->is_black = true;
                    parent->is_black = false;
                    left_rotation(parent);
                }
                if (parent->right->right->is_black && parent->right->left->is_black)
                    parent->right->is_black = false;
                else {
                    if (parent->right->right->is_black) {
                        parent->right->left->is_black = true;
                        parent->right->is_black = false;
                        right_rotation(parent->right);
                    }
                    parent->right->is_black = parent->is_black;
                    parent->is_black = true;
                    parent->right->right->is_black = true;
                    left_rotation(parent);
                    curr = root;
                }
            } else {
                pointer_node brother = parent->left;
                if (!brother->is_black) {
                    brother->is_black = true;
                    parent->is_black = false;
                    left_rotation(curr.parent);
                }
                if (brother->right->is_black && brother->left->is_black)
                    brother->is_black = false;
                else {
                    if (brother->left->is_black) {
                        brother->right->is_black = true;
                        brother->is_black = false;
                        right_rotation(brother);
                    }
                    brother = parent;
                    parent->is_black = true;
                    brother->left->is_black = true;
                    right_rotation(curr->parent);
                    curr = root;
                }
            }
        }
        curr->is_black = true;
        root->is_black = true;
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::removing_both_child(rbtree::pointer_node &node) {
        pointer_node rep = node->right;

        while (rep->left)
            rep = rep->left;
        if (node->parent) {
            if (node->parent->left == node)
                node->parent->left = rep;
            else
                node->parent->right = rep;
        } else
            root = rep;

        pointer_node children = rep->right;
        pointer_node parent = rep->parent;
        bool color = rep->is_black;

        if (parent == node)
            parent = rep;
        else {
            if (children)
                children->parent = parent;
            parent->left = children;
            rep->right = node->right;
            node->right->parent = rep;
        }
        rep->parent = node->parent;
        rep->is_black = node->is_black;
        rep->left = node->left;
        node->left->parent = rep;
        if (color)
            optimize_removing(children, parent);
        alloc.destroy(&node->value);
        alloc.deallocate(reinterpret_cast<value_type *>(node), 1);
    }


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
        pointer_node new_node = reinterpret_cast<pointer_node>(this->alloc.allocate(sizeof(node)));
        new_node->parent = new_node->left = new_node->right = NULL;
        new_node->value = val;
        new_node->is_black = false;

        if (!root)
            root = new_node;
        else {
            pointer_node parent = NULL;
            pointer_node curr = root;
            while (curr) {
                parent = curr;
                if (new_node->value < curr->value)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            new_node->parent = parent;
            if (parent->value < new_node->value)
                parent->right = new_node;
            else
                parent->left = new_node;
        }
        optimize_insertion(new_node);
        begin_node = min_node(root);
        end_node = max_node(root);
        total_size++;
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::remove(const value_type &val) {
        pointer_node curr = root;
        pointer_node parent = 0;
        pointer_node childer = 0;
        bool color;

        while (curr && curr->value != val) {
            parent = curr;
            if (curr->value < val)
                curr = curr->right;
            else
                curr = curr->left;
        }

        if (!curr)
            return;
        if (curr->left && curr->right)
            removing_both_child(curr);
        if (curr->left)
            childer = curr->left;
        else
            childer = curr->right;

        parent = curr->parent;
        color = curr->is_black;

        if (childer)
            childer->parent = parent;
        if (parent) {
            if (curr == parent->left)
                parent->left = childer;
            else
                parent->right = childer;
        } else
            root = childer;

        if (color)
            optimize_removing(childer, parent);

        alloc.destroy(&curr->value);
        alloc.deallocate(reinterpret_cast<value_type *>(curr), 1);
        total_size--;
        begin_node = min_node(root);
        end_node = max_node(root);
    }

    template<class T, class Compare, class Allocator>
    void rbtree<T, Compare, Allocator>::clean(pointer_node &node) {
        if (!node)
            return;
        clean(node->right);
        clean(node->left);
        alloc.destroy(&node->value);
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
        iterator it = set_lower_bound(key);
        if (it != end() && !compare(key, *it))
            return it;
        return (iterator) end_node;
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
        return (iterator) to_return;
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
        return (iterator) begin_node;
    }

    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::const_iterator rbtree<T, Compare, Allocator>::begin() const {
        return (iterator) begin_node;
    }

    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::iterator rbtree<T, Compare, Allocator>::end() {
        return (iterator) end_node;
    }

    template<class T, class Compare, class Allocator>
    typename rbtree<T, Compare, Allocator>::const_iterator rbtree<T, Compare, Allocator>::end() const {
        return (iterator) end_node;
    }

}

#endif