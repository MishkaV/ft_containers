/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 21:06:08 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/07 21:06:09 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

namespace ft {

    /*
     * Tags for [Category] in [iterator]
     */
    struct input_iterator_tag {
    };
    struct output_iterator_tag {
    };
    struct forward_iterator_tag : public input_iterator_tag {
    };
    struct bidirectional_iterator_tag : public forward_iterator_tag {
    };
    struct random_access_iterator_tag : public bidirectional_iterator_tag {
    };

    /*
     * Iterator
     */
    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
    struct iterator {
        typedef Distance difference_type;
        typedef T value_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

    /*
     * Iterator_traits - meta-info for iterator
     * [Iter] - the iterator type to retrieve properties for
     * [T] - user's type, which can use like iterator
     * [typename] needs to identify type, not static property
     */
    template<class Iter>
    struct iterator_traits {
        typedef ptrdiff_t difference_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;
    };

    template<class T>
    struct iterator_traits<T *> {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef random_access_iterator_tag iterator_category;
    };


    /*
     * [advance] function needs to refer to the element at distance [dist]
     */
    template<class RandomAccessIterator>
    void p_advance(
            RandomAccessIterator &it,
            typename iterator_traits<RandomAccessIterator>::difference_type n,
            random_access_iterator_tag
    ) {
        it += n;
    }

    template<class InputIterator, class Distance>
    void advance(InputIterator &it, Distance n) {
        int dist = static_cast<int>(n);
        p_advance(it, dist, iterator_traits<InputIterator>::iterator_category());
    }


    /*
     * [distance] function needs to count distance between iterators
     */
    template<class RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type p_distance(
            RandomAccessIterator first,
            RandomAccessIterator second,
            random_access_iterator_tag
    ) {
        return second - first;
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::difference_type distance(
            Iterator first,
            Iterator second
    ) {
        return p_distance(first, second, typename iterator_traits<Iterator>::iterator_category());
    }
}

#endif
