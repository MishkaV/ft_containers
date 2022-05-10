/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbenjy <jbenjy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:07:47 by jbenjy            #+#    #+#             */
/*   Updated: 2022/05/07 14:20:26 by jbenjy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "../includes/ft_containers.hpp"

int main() {
    {
        std:: cout << "\nTEST 1\n";
        ft::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        std:: cout << "Last element is " << vec.back() << "\n";
        size_t size = 4;
        vec.assign(size, 5);
        std::cout << vec[2] << '\n';

        std:: cout << "Test out of range exc:\n";
        try {
            vec[4];
        }
        catch (std::out_of_range e) {
            std::cout << e.what() << '\n';
        }
    }

    {
        std:: cout << "\nTEST 2\n";
        ft::vector<int> vec;
        int *pointer = vec.get_allocator().allocate(1);
        vec.get_allocator().construct(pointer, 1);

        std:: cout << pointer[0] << '\n'; ;

        vec.get_allocator().destroy(pointer);
        vec.get_allocator().deallocate(pointer, 1);
    }

    {
        std:: cout << "\nTEST 3\n";
        ft::vector<int> vec;

        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        std::cout << "Origin:\n";
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert begin:\n";
        vec.insert(vec.begin(), 0);
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert end:\n";
        vec.insert( vec.end(), 4);
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert mid:\n";
        vec.insert( vec.begin() + 1, 10);
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";



        size_t count = 2;
        std::cout << "\nCheck insert dubl:\n";
        std::cout << "Origin:\n";
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert begin:\n";
        vec.insert(vec.begin(), count,11);
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert end:\n";
        vec.insert( vec.end(), count,12);
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert mid:\n";
        vec.insert( vec.begin() + 1, count,13);
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";


        vec.clear();
        vec.push_back(10);
        vec.push_back(10);
        vec.push_back(10);

        ft::vector<int> vec2(4,3);
        std::cout << "\nCheck insert range:\n";
        std::cout << "Origin(vec):\n";
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert begin:\n";
        vec.insert(vec.begin(), vec2.begin(), vec2.end());
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert end:\n";
        vec.insert(vec.end(), vec2.begin(), vec2.end());
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";

        std::cout << "Insert mid:\n";
        vec.insert( vec.begin() + 1, vec2.begin(), vec2.end());
        for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
            std:: cout << *it << " ";
        std:: cout << "\n";
    }
}