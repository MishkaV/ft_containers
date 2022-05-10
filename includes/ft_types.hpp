/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:37:51 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/10 19:37:52 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_HPP
# define FT_TYPES_HPP

namespace ft {

    /*
     * enable_if
     */
    template<bool B, class T = void>
    struct enable_if {
    };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    /*
     * integral_constant
     */
    template<class T, T val>
    struct integral_constant
    {
        static const T value = val;
        typedef T value_type;
        typedef integral_constant<T, val> type;
        operator value_type() const {
            return value;
        }
    };

    /*
     * types
     */
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template<class T> struct is_integral: public false_type {};
    template<> struct is_integral<long>: public true_type {};
    template<> struct is_integral<unsigned long>: public true_type {};
    template<> struct is_integral<long long>: public true_type {};
    template<> struct is_integral<unsigned long long>: public true_type {};
    template<> struct is_integral<bool>: public true_type {};
    template<> struct is_integral<char>: public true_type {};
    template<> struct is_integral<signed char>: public true_type {};
    template<> struct is_integral<unsigned char>: public true_type {};
    template<> struct is_integral<short>: public true_type {};
    template<> struct is_integral<unsigned short>: public true_type {};
    template<> struct is_integral<int>: public true_type {};
    template<> struct is_integral<unsigned int>: public true_type {};
}

#endif