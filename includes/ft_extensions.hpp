/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extensions.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:21:40 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/12 20:21:41 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXTENSIONS_HPP
# define FT_EXTENSIONS_HPP

namespace ft {

    /*
     * lexicographical compare
     */
    template<class InputIterator1, class InputIterator2>
    bool lexicographical_compare(
            InputIterator1 first1,
            InputIterator1 last1,
            InputIterator2 first2,
            InputIterator2 last2
    ) {
        for (; first1 != last1 || first2 != last2; first1++, first2++) {
            if (*first2 < *first1)
                return false;
            if (*first1 < *first2)
                return true;
        }
        return first2 != last2 && first1 == last1;
    }

    template<class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare(
            InputIterator1 first1,
            InputIterator1 last1,
            InputIterator2 first2,
            InputIterator2 last2,
            Compare comp
    ) {
        for (; first1 != last1 || first2 != last2; first1++, first2++) {
            if (comp(*first2, *first1))
                return false;
            if (comp(*first1, *first2) || *first1 < *first2)
                return true;
        }
        return false;
    }


    /*
     * equal
     */
    template<class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        while(first1 != last1) {

            if (*first1 != *first2)
                return false;

            first1++;
            first2++;
        }
        return true;
    }

    template<class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
               BinaryPredicate p)
    {
        while(first1 != last1) {

            if (!p(*first1, *first2))
                return false;

            first1++;
            first2++;
        }
        return true;
    }
}

#endif