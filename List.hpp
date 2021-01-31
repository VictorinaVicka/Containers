/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:54:36 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/31 16:11:43 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <utility>
# include <limits>
# include <memory>
# include "List_Iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class List
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef T	&reference;
		typedef const T	&const_reference;
		typedef	T	*pointer;
		typedef	const T	*const_pointer;
		typedef ft::ListIt<T>	iterator;
		typedef ft::ConstListIt<T>	const_iterator;
		typedef ft::ReverseListIt<T> reverse_iterator;
		typedef ft::ConstReverseListIt<T>	const_reverse_iterator;
		typedef typename ft::ListIt<T>::difference_type	difference_type;
		typedef size_t	size_type;

	private:
		Node<T>	*origin;
		Node<T>	*finish;
		Node<T>	*start;
		Node<T>	*stop;
		allocator_type alloc;
		size_type len;

	public:
		explicit List (const allocator_type& alloc = allocator_type())
		{
			this->alloc = alloc;
			start = new Node<T>();
			start->prev = NULL;
			stop = new Node<T>();
			stop->next = NULL;
			start->next = stop;
			stop->prev = start;
			origin = stop;
			finish = stop;
			len = 0;
			return ;
		}

		~List(void)
		{
			clear();
			delete(start);
			delete(stop);
			return ;
		}

		List(const List &list)
		{
			start = new Node<T>();
			stop = new Node<T>();
			stop->next = NULL;
			start->prev = NULL;
			start->next = stop;
			stop->prev = start;
			origin = stop;
			finish = stop;
			len = 0;
			*this = list;
			return ;
		}

		List &operator=(const List &list)
		{
			Node<T>	*node;

			clear();
			alloc = list.alloc;
			len = 0;
			if (list.len)
			{
				node = list.origin;
				while (node != list.stop)
				{
					push_back(*node->data);
					node = node->next;
				}
			}
			return (*this);
		}

		explicit List (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		{
			this->alloc = alloc;
			start = new Node<T>();
			start->prev = NULL;
			stop = new Node<T>();
			stop->next = NULL;
			start->next = stop;
			stop->prev = start;
			origin = stop;
			finish = stop;
			len = 0;
			assign(n, val);
		}

		template <class InputIterator>
  		List (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		{
			alloc = alloc;
			start = new Node<T>();
			start->prev = NULL;
			stop = new Node<T>();
			stop->next = NULL;
			start->next = stop;
			stop->prev = start;
			origin = stop;
			finish = stop;
			len = 0;
			assign(static_cast<InputIterator>(first), static_cast<InputIterator>(last));
		}

		// Iterators:

		iterator begin(void)
		{
			return (iterator(origin));
		}

		const_iterator	begin(void) const
		{
			return (const_iterator((origin)));
		}

		iterator end(void)
		{
			return (iterator(stop));
		}

		const_iterator	end(void) const
		{
			return (const_iterator(stop));
		}

		reverse_iterator rbegin(void)
		{
			return (reverse_iterator(finish));
		}

		const_reverse_iterator	rbegin(void) const
		{
			return (const_reverse_iterator(finish));
		}

		reverse_iterator rend(void)
		{
			return (reverse_iterator(start));
		}

		const_reverse_iterator	rend(void) const
		{
			return (const_reverse_iterator(start));
		}

		// Capacity:

		bool	empty(void) const
		{
			return (!len);
		}

		size_type	size(void) const
		{
			return (len);
		}

		size_type	max_size(void) const
		{
			return (std::numeric_limits<size_type>::max()/sizeof(origin));
		}

		// Element access:

		reference	front(void)
		{
			return (*origin->data);
		}

		const_reference	front(void) const
		{
			return (*origin->data);
		}

		reference	back(void)
		{
			return (*finish->data);
		}

		const_reference	back(void) const
		{
			return (*finish->data);
		}

		// Modifiers:

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			clear();
			insert(begin(), first, last);
		}

		void	assign(size_type n, const value_type &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void	push_front(const value_type &val)
		{
			insert(begin(), val);
		}

		void pop_front(void)
		{
			erase(begin());
		}

		void push_back(const value_type &val)
		{
			insert(end(), val);
		}

		void pop_back(void)
		{
			iterator it = end();
			it--;
			erase(it);
		}

		iterator insert(iterator position, const value_type &val)
		{
			Node<T>	*more;
			Node<T>	*node;

			more = new Node<T>;
			more->next = NULL;
			more->prev = NULL;
			more->data = alloc.allocate(1);
			alloc.construct(more->data, val);
			node = position.getNewNode();
			if (node->prev == start)
			{
				more->prev = start;
				start->next = more;
				if (len)
				{
					origin->prev = more;
					more->next = origin;
					origin = more;
				}
				else
				{
					finish = origin = more;
					more->next = stop;
					stop->prev = more;
				}
			}
			else if (!node->next)
			{
				more->next = stop;
				stop->prev = more;
				if (len)
				{
					finish->next = more;
					more->prev = finish;
					finish = finish->next;
				}
				else
				{
					origin = finish = more;
					more->prev = start;
					start->next = more;
				}
			}
			else
			{
				more->prev = node->prev;
				if (node->prev)
					node->prev->next = more;
				more->next = node;
				node->prev = more;
			}
			len++;
			return (iterator(more));
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			while (n--)
				insert(position, val);
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; it++)
				insert(position, *it);
		}

		iterator				erase(iterator position)
		{
			Node<T>		*next;
			Node<T>		*node;

			node = position.getNewNode();
			if (node == start)
				return (iterator(start));
			if (position == end())
				return (end());
			if (node->prev == start)
			{
				origin = node->next;
				origin->prev = start;
				start->next = origin;
			}
			else
				node->prev->next = node->next;
			if (node->next == stop)
			{
				if (node->prev != start)
				{
					finish = node->prev;
					finish->next = stop;
					stop->prev = finish;
				}
				else
					finish = stop;
			}
			else
				node->next->prev = node->prev;
			next = node->next;
			alloc.destroy(node->data);
			alloc.deallocate(node->data, 1);
			delete(node);
			len--;
			return (iterator(next));
		}

		iterator	erase(iterator first, iterator last)
		{
			iterator node;
		
			while (first != last)
			{
				node = first;
				first++;
				erase(node);
			}
			return (iterator(origin));
		}

		void	swap(List &x)
		{
			Node<T>	*node;
			size_type newLen;

			node = x.origin;
			x.origin = origin;
			origin = node;
			node = x.finish;
			x.finish = finish;
			finish = node;
			node = x.stop;
			x.stop = stop;
			stop = node;
			newLen = x.len;
			x.len = len;
			len = newLen;
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n >= len)
				insert(end(), n - len, val);
			else
			{
				iterator it = begin();
				for (size_type i = 0; i < n; i++)
					it++;
				erase(it, end());
			}
		}

		void clear(void)
		{
			erase(begin(), end());
		}

		// Operations:

		void splice(iterator position, List &x)
		{
			insert(position, x.begin(), x.end());
			x.clear();
		}

		void splice(iterator position, List &x, iterator i)
		{
			insert(position, *i);
			x.erase(i);
		}

		void splice(iterator position, List &x, iterator first, iterator last)
		{
			insert(position, first, last);
			x.erase(first, last);
		}

		void remove(const value_type &val)
		{
			for (iterator it = begin(); it != end();)
			{
				if (*it == val)
					it = erase(it);
				else
					it++;
			}
		}

		template <class Predicate>
		void	remove_if(Predicate pred)
		{
			for (iterator it = begin(); it != end();)
			{
				if (pred(*it))
					it = erase(it);
				else
					it++;
			}
		}

		void	unique(void)
		{
			iterator 	it;
			iterator	it2;
			iterator 	node;

			it = begin();
			while (it != end())
			{
				it2 = it;
				node = it2;
				it2++;
				while (it2 != end())
				{
					if (*it2 == *it)
					{
						erase(it2);
						it2 = node;
					}
					node = it2;
					it2++;
				}
				it++;
			}
		}

		template <class BinaryPredicate>
		void	unique(BinaryPredicate binary_pred)
		{
			if (begin() == end())
				return ;
			iterator prev = begin();
			iterator it = prev;
			it++;
			while (it != end())
			{
				if (binary_pred(*it, *prev))
					it = erase(it);
				else
				{
					prev = it;
					it++;
				}
			}
		}

		void	merge(List &x)
		{
			iterator	it;
			iterator	it2;
			iterator	next;
			size_type	size;

			size = len;
			if (size)
				it = begin();
			if (x.len)
				it2 = x.begin();
			while (x.len)
			{
				while (size && (it != end()) && !(*it2 < *it))
					it++;
				next = it2;
				if (x.len != 1)
					next++;
				if (size && it != end())
					splice(it, x, it2);
				else
				{
					push_back(*it2);
					x.erase(it2);
				}
				it2 = next;
			}
		}

		template <class Compare>
		void merge(List &x, Compare comp)
		{
			iterator selfIt = begin();
			for (iterator it = x.begin(); it != x.end();)
			{
				while(selfIt != end() && comp(*selfIt, *it))
					selfIt++;

				iterator tmp = it;
				it++;
				if (selfIt.newNode->prev)
					selfIt.newNode->prev->next = tmp.newNode;
				else
					origin = tmp.newNode;
				tmp.newNode->prev = selfIt.newNode->prev;
				tmp.newNode->next = selfIt.newNode;
				selfIt.newNode->prev = tmp.newNode;
			}
			len += x.len;
			x.len = 0;
			x.origin = x.finish;
			x.finish->prev = NULL;
		}

		void sort(void)
		{
			iterator it;
			iterator it2;
			size_type size;

			size = len;
			while (size--)
			{
				it = begin();
				it2 = it;
				it2++;
				while (it2 != end())
				{
					if (*it2 < *it)
						splice(it, *this, it2);
					else
						it++;
					it2 = it;
					it2++;
				}
			}
		}

		template <class Compare>
		void sort(Compare comp)
		{
			iterator it;
			iterator it2;
			size_type size;

			size = len;
			while (size--)
			{
				it = begin();
				it2 = it;
				it2++;
				while (it2 != end())
				{
					if (comp(*it2, *it))
						splice(it, *this, it2);
					else
						it++;
					it2 = it;
					it2++;
				}
			}
		}

		void reverse(void)
		{
			iterator it;
			size_type size;

			if (len)
			{
				size = len - 1;
				it = begin();
				while (size--)
					splice(it, *this, iterator(finish));
			}
		}
	};

	// Non-member function overloads:

	template <class T, class Alloc>
	bool operator==(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
	{
		size_t	size;
		typename List<T, Alloc>::const_iterator it = lhs.begin();
		typename List<T, Alloc>::const_iterator	it2 = rhs.begin();

		if (lhs.size() != rhs.size())
			return (false);
		size = 0;
		while (size < lhs.size())
		{
			if (*it != *it2)
				return (false);
			it++;
			it2++;
			size++;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
	{
		size_t	size1;
		size_t	size2;
		typename List<T, Alloc>::const_iterator	it = lhs.begin();
		typename List<T, Alloc>::const_iterator	it2 = rhs.begin();

		if (lhs.size() > rhs.size())
			size1 = rhs.size();
		else
			size1 = lhs.size();
		size2 = 0;
		while (size2 < size1)
		{
			if (*it != *it2)
				return (*it < *it2);
			size2++;
			it++;
			it2++;
		}
		return (lhs.size() < rhs.size());
	}

	template <class T, class Alloc>
	bool operator<=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator>(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
	{
		return (!(lhs < rhs) && !(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator>=(const List<T, Alloc> &lhs, const List<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap(List<T, Alloc> &x, List <T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif
