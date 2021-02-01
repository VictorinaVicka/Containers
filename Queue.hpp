/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:53:50 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/01 21:25:41 by tfarenga         ###   ########.fr       */
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

		~Queue()
		{
			return ;
		}

		// Member functions:

		Queue(const Queue &copy)
		{
			*this = copy;
			return ;
		}

		Queue &operator=(const Queue &target)
		{
			cont = target.cont;
			return (*this);
		}

		value_type &back()
		{
			return (cont.back());
		}

		const value_type &back() const
		{
			return (cont.back());
		}

		bool empty() const
		{
			return (cont.empty());
		}

		value_type &front()
		{
			return (cont.front());
		}

		const value_type &front() const
		{
			return (cont.front());
		}

		void pop()
		{
			return (cont.pop_front());
		}

		void push(const value_type &val)
		{
			return (cont.push_back(val));
		}

		size_type size() const
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
