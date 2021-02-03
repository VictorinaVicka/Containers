/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:53:39 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/03 14:16:20 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class Stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t	size_type;

	private:
		container_type	cont;

	public:
		explicit Stack(const container_type &ctnr = container_type())
		{
			cont = ctnr;
			return ;
		}

		~Stack()
		{
			return ;
		}

		// Member functions:

		Stack(const Stack &copy)
		{
			*this = copy;
			return ;
		}

		Stack &operator=(const Stack &target)
		{
			cont = target.cont;
			return (*this);
		}

		bool empty() const
		{
			return (cont.empty());
		}

		void push (const value_type &val)
		{
			cont.push_back(val);
		}

		void pop ()
		{
			cont.pop_back();
		}

		size_type size() const
		{
			return (cont.size());
		}

		value_type	&top()
		{
			return (cont.back());
		}

		const value_type &top() const
		{
			return (cont.back());
		}

		template <class _T, class _Container>
		friend bool	operator==(const Stack<_T,_Container> &lhs, const Stack<_T,_Container> &rhs);

		template <class _T, class _Container>
		friend bool	operator!=(const Stack<_T,_Container> &lhs, const Stack<_T,_Container> &rhs);

		template <class _T, class _Container>
		friend bool	operator<(const Stack<_T,_Container> &lhs, const Stack<_T,_Container> &rhs);

		template <class _T, class _Container>
		friend bool	operator<=(const Stack<_T,_Container> &lhs, const Stack<_T,_Container> &rhs);

		template <class _T, class _Container>
		friend bool	operator>(const Stack<_T,_Container> &lhs, const Stack<_T,_Container> &rhs);

		template <class _T, class _Container>
		friend bool	operator>=(const Stack<_T,_Container> &lhs, const Stack<_T,_Container> &rhs);
	};

	// Non-member function overloads:

	template <class T, class Container>
	bool	operator==(const Stack<T,Container> &lhs, const Stack<T,Container> &rhs)
	{
		return (lhs.cont == rhs.cont);
	}

	template <class T, class Container>
	bool	operator!=(const Stack<T,Container> &lhs, const Stack<T,Container> &rhs)
	{
		return !(lhs.cont == rhs.cont);
	}

	template <class T, class Container>
	bool	operator<(const Stack<T,Container> &lhs, const Stack<T,Container> &rhs)
	{
		return (lhs.cont < rhs.cont);
	}

	template <class T, class Container>
	bool	operator<=(const Stack<T,Container> &lhs, const Stack<T,Container> &rhs)
	{
		return (lhs.cont <= rhs.cont);
	}

	template <class T, class Container>
	bool	operator>(const Stack<T,Container> &lhs, const Stack<T,Container> &rhs)
	{
		return (lhs.cont > rhs.cont);
	}

	template <class T, class Container>
	bool	operator>=(const Stack<T,Container> &lhs, const Stack<T,Container> &rhs)
	{
		return (lhs.cont >= rhs.cont);
	}
};

#endif