/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 21:23:39 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/12 21:23:40 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
# define FT_STACK_HPP

#include <vector>

namespace ft {

    /*
     * stack
     */
    template<class T, class Container = std::vector<T> >
    class stack {

        /*
         * Member types
         */
    public:
        typedef Container container_type;
        typedef size_t size_type;
        typedef T value_type;

    protected:
        container_type container;

    private:
        /*
         * Constructor
         */
        explicit stack(const container_type &cont = container_type()) : container(cont) {};


        /*
         * Destructor
         */
        ~stack() {}

        /*
         * Member functions
         */
        size_type size() const { return container.size(); }

        value_type &top() { return container.back(); }

        const value_type &top() const { return container.back(); }

        void push(const value_type &val) { container.push_back(val); }

        void pop() { container.pop_back(); }
    };


    /*
     * Non-member functions
     */
    template<class T1, class Container1>
    bool operator==(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs) {
        return lhs.c == rhs.c;
    }

    template<class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs != rhs;
    }

    template<class T1, class Container1>
    bool operator<(const stack<T1, Container1> &lhs, const stack<T1, Container1> &rhs) {
        return lhs.c < rhs.c;
    }

    template<class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return rhs <= lhs;
    }

    template<class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return rhs > lhs;
    }

    template<class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs >= rhs;
    }
}

#endif