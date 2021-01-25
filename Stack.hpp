/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:53:39 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/25 15:10:23 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft
{
    template <typename T, typename Container = Vector<T> >
	class Stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
	private:
		typedef Stack<T, Container> Self;
        container_type newCntr;
	public:

		// Member functions:

		explicit Stack(const container_type &cntr = container_type()): newCntr(cntr) {}

        bool empty() const
		{
            return newCntr.empty();
        }

        size_type size() const
		{
            return newCntr.size();
        }

        value_type &top()
		{
            return newCntr.back();
        }

        const value_type &top() const
		{
            return newCntr.back();
        }

        void push(const value_type &val)
		{
            newCntr.push_back(val);
        }

        void pop()
		{
            newCntr.pop_back();
        }

        template <typename _T, typename _Container>
		friend bool operator==(const Stack<_T, _Container> &lhs, const Stack<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool operator<(const Stack<_T, _Container> &lhs, const Stack<_T, _Container> &rhs);
    };

	// Non-member function overloads:

    template <typename T, typename Container>
	bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return lhs.newCntr == rhs.newCntr;
	}

	template <typename T, typename Container>
	bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return lhs.newCntr < rhs.newCntr;
	}

	template <typename T, typename Container>
	bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Container>
	bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
};

#endif