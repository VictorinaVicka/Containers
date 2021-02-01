/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:53:50 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/01 12:13:56 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class Queue
	{
	public:
		typedef T	value_type;
		typedef Container	container_type;
		typedef size_t	size_type;

	private:
		container_type	cont;

	public:
		explicit Queue(const container_type& ctnr = container_type())
		{
			cont = ctnr;
			return ;
		}

		~Queue(void)
		{
			return ;
		}

		// Member functions:

		Queue(const Queue &queue)
		{
			*this = queue;
			return ;
		}

		Queue &operator=(const Queue &queue)
		{
			cont = queue.cont;
			return (*this);
		}

		value_type &back(void)
		{
			return (cont.back());
		}

		const value_type &back(void) const
		{
			return (cont.back());
		}

		bool empty(void) const
		{
			return (cont.empty());
		}

		value_type &front(void)
		{
			return (cont.front());
		}

		const value_type &front(void) const
		{
			return (cont.front());
		}

		void pop(void)
		{
			return (cont.pop_front());
		}

		void push(const value_type &val)
		{
			return (cont.push_back(val));
		}

		size_type size(void) const
		{
			return (cont.size());
		}

		template <typename _T, typename _Container>
		friend bool operator==(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool operator<(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool	operator!=(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool	operator<=(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool	operator>(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);

		template <typename _T, typename _Container>
		friend bool	operator>=(const Queue<_T, _Container> &lhs, const Queue<_T, _Container> &rhs);
	};

	// Non-member functions:

	template <class T, class Container>
	bool operator==(const Queue<T,Container> &lhs, const Queue<T,Container> &rhs)
	{
		return (lhs.cont == rhs.cont);
	}

	template <class T, class Container>
	bool operator!=(const Queue<T,Container> &lhs, const Queue<T,Container> &rhs)
	{
		return (lhs.cont != rhs.cont);
	}

	template <class T, class Container>
	bool operator<(const Queue<T,Container> &lhs, const Queue<T,Container> &rhs)
	{
		return (lhs.cont < rhs.cont);
	}

	template <class T, class Container>
	bool operator<=(const Queue<T,Container> &lhs, const Queue<T,Container> &rhs)
	{
		return (lhs.cont <= rhs.cont);
	}

	template <class T, class Container>
	bool operator>(const Queue<T,Container> &lhs, const Queue<T,Container> &rhs)
	{
		return (rhs.cont > lhs.cont);
	}

	template <class T, class Container>
	bool operator>=(const Queue<T,Container> &lhs, const Queue<T,Container> &rhs)
	{
		return (lhs.cont >= rhs.cont);
	}
};

#endif
