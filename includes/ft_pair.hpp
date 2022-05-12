/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pair.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:35:51 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/12 20:35:52 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP

#include "utility"

namespace ft {

    /*
     * pair
     */
    template<class T1, class T2>
    struct pair {

        /*
         * Member types
         */
        typedef T1 first_type;
        typedef T2 second_type;

        /*
         * Member types
         */
        T1 first;
        T2 second;

        /*
         * Constructors
         */
        pair() : first(), second() {};

        pair(const T1 &x, const T2 &y) : first(x), second(y) {};

        template<class U1, class U2>
        pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {};

        /*
         * operator=
         */
        pair &operator=(const pair &other) {
            first = other.first;
            second = other.second;
            return *this;
        }
    };



    /*
     * make pair
     */
    template<class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {
        return pair<T1, T2>(x, y);
    }



    /*
     * Operators
     */
    template<class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return lhs.first != rhs.first && lhs.second != rhs.second;
    }

    template<class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return ((!(rhs.first < lhs.first) && lhs.second < rhs.second) || lhs.first < rhs.first);
    }

    template<class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(rhs < lhs);
    }

    template<class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return rhs < lhs;
    }

    template<class T1, class T2>
    bool operator>=(const std::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) {
        return !(lhs < rhs);
    }
}

#endif