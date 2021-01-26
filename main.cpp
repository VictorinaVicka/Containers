/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:32:23 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/26 17:17:11 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void testList();
void testQueue();
void testVector();
void testStack();
void testMap();

int main()
{
    std::cout << "<<<<<<<<<<<<Containers:>>>>>>>>>>" << std::endl;
    std::cout << "1: List" << std::endl;
    std::cout << "2: Queue" << std::endl;
    std::cout << "3: Vector" << std::endl;
    std::cout << "4: Stack" << std::endl;
    std::cout << "5: Map" << std::endl;

    std::cout << "Сhoice: ";
    std::string s;
    std::getline(std::cin, s);
    if (s[0] == '1')
        testList();
    else if (s[0] == '2')
        testQueue();
    else if (s[0] == '3')
        testVector();
    else if (s[0] == '4')
        testStack();
    else if (s[0] == '5')
        testMap();
    return 0;
}