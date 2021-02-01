/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:53:39 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/01 12:11:31 by tfarenga         ###   ########.fr       */
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

		~Stack(void)
		{
			return ;
		}

		// Member functions:

		Stack(const Stack &stack)
		{
			*this = stack;
			return ;
		}

		Stack &operator=(const Stack &stack)
		{
			cont = stack.cont;
			return (*this);
		}

		bool empty(void) const
		{
			return (cont.empty());
		}

		void push (const value_type &val)
		{
			cont.push_back(val);
		}

		void pop (void)
		{
			cont.pop_back();
		}

		size_type size(void) const
		{
			return (cont.size());
		}

		value_type	&top(void)
		{
			return (cont.back());
		}

		const value_type &top(void) const
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
		return (rhs.cont > lhs.cont);
	}

	template <class T, class Container>
	bool	operator>=(const Stack<T,Container> &lhs, const Stack<T,Container> &rhs)
	{
		return (lhs.cont >= rhs.cont);
	}
};

#endif