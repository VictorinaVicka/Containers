/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:32:23 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/22 16:35:22 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main() {
    std::cout << "Select Container:" << std::endl;
    std::cout << "List" << std::endl;
    // std::cout << "2- Vector" << std::endl;
    // std::cout << "3- Map" << std::endl;
    // std::cout << "4- Stack" << std::endl;
    // std::cout << "5- Queue" << std::endl << std::endl;

    std::cout << "Entry: ";
    std::string line;
    std::getline(std::cin, line);
    while (line.length() != 1 && line[0] < '1' && line[0] > '5') {
        std::cout << "Wrong entry" << std::endl;
        std::cout << "Entry: ";
        std::getline(std::cin, line);
		std::cout << std::endl;
    }

    if (line[0] == '1')
        testList();
    // else if (line[0] == '2')
    //     testVector();
    // else if (line[0] == '3')
    //     testMap();
    // else if (line[0] == '4')
    //     testStack();
    // else if (line[0] == '5')
    //     testQueue();

    return 0;
}