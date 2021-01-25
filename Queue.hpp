/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:53:50 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/25 11:16:29 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "List.hpp"

namespace ft {

    template <typename T, typename Container = List<T> >
	class	Queue
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	private:
		typedef Queue<T, Container> Self;

        container_type newCntr;

	public:

		//Member functions:

		explicit Queue(const container_type &cntr = container_type()): newCntr(cntr)
		{}

        bool empty() const
		{
            return newCntr.empty();
        }

        size_type size() const
		{
            return newCntr.size();
        }

        value_type &front()
		{
            return newCntr.front();
        }

        const value_type &front() const
		{
            return newCntr.front();
        }

        value_type &back()
		{
            return newCntr.back();
        }

        const value_type &back() const
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
		friend bool operator==(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool operator<(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);

    };

	// Non-member function overloads:

    template <typename T, typename Container>
	bool operator==(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return lhs.newCntr == rhs.newCntr;
	}

	template <typename T, typename Container>
	bool operator!=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return lhs.newCntr < rhs.newCntr;
	}

	template <typename T, typename Container>
	bool operator>(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator<=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Container>
	bool operator>=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
};

#endif