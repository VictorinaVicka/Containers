/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:54:36 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/24 16:10:56 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <utility>
# include "TurnedIterator.hpp"
# include "Utils.hpp"

namespace ft
{
	template <typename T>
	class List;

	template <typename T>
	class	ListIt
	{
	public:
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef	std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

	private:
		typedef typename List<T>::_node _node;
		typedef ListIt<T> Self;

		_node *newNode;

	public:
		ListIt() {}
		ListIt(_node *node): newNode(node) {}
		ListIt(const ListIt<T> &c): newNode(c.newNode) {}
		~ListIt() {}

		template <typename _T>
		friend class List;

		template <typename _T>
		friend bool operator==(const ListIt<_T> &lhs, const ListIt<_T> &rhs);

		template <typename _T>
		friend bool operator!=(const ListIt<_T> &lhs, const ListIt<_T> &rhs);

		Self &operator=(const Self &c)
		{
			newNode = c.newNode;
			return *this;
		}

		Self &operator++()
		{
			newNode = newNode->next;
			return *this;
		}

		Self operator++(int)
		{
			Self copy = *this;
			++*this;
			return copy;
		}

		Self &operator--()
		{
			newNode = newNode->prev;
			return *this;
		}

		Self operator--(int)
		{
			Self cpy = *this;
			--*this;
			return cpy;
		}

		reference operator*() const
		{
			return newNode->data;
		}

		pointer operator->() const
		{
			return &newNode->data;
		}
	};

	template <typename T>
	bool operator==(const ListIt<T> &lhs, const ListIt<T> &rhs)
	{
		return lhs.newNode == rhs.newNode;
	}

	template <typename T>
	bool operator!=(const ListIt<T> &lhs, const ListIt<T> &rhs)
	{
		return !(lhs.newNode == rhs.newNode);
	}

	template <typename T>
	class	List
	{
	public:
		typedef T value_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef ListIt<T> iterator;
		typedef const ListIt<const T> const_iterator;
		typedef TurnedIterator<iterator> reverse_iterator;
		typedef const TurnedIterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t diff_type;
		typedef size_t size_type;

	private:
		typedef List<T> Self;

		struct _node
		{
			value_type data;
			_node *prev;
			_node *next;
			_node(_node *prev, _node *next): prev(prev), next(next) {};
		};
		size_type newSize;
		_node *firstN;
		_node *last;
	public:

		//Member functions:

		List(): newSize(0)
		{
			firstN = new _node(NULL, NULL);
			last = firstN;
		}

		List(size_type n, const value_type &val): newSize(0)
		{
			firstN = new _node(NULL, NULL);
			last = firstN;
			insert(begin(), n, val);
		}

		template <typename InputIterator>
		List(InputIterator first, InputIterator last): newSize(0)
		{
			firstN = new _node(NULL, NULL);
			last = firstN;
			insert(begin(), first, last);
		}

		List(const Self &c): newSize(0)
		{
			firstN = new _node(NULL, NULL);
			last = firstN;
			insert(begin(), c.begin(), c.end());
		}

		~List()
		{
			erase(begin(), end());
			delete last;
		}

		template <typename _T>
		friend class List;

		template <typename _T>
		friend class ListIt;

		template <typename Iterator>
		friend class ReverseIterator;

		Self &operator=(const List &c) {
			clear();
			insert(begin(), c.begin(), c.end());
			return *this;
		}

		// Iterators:

		iterator begin()
		{
			return iterator(firstN);
		}

		iterator end()
		{
			return iterator(last);
		}

		const_iterator begin() const
		{
			typedef typename List<const T>::_node const_node;
			return const_iterator(reinterpret_cast<const_node *>(firstN));
		}

		const_iterator end() const
		{
			typedef typename List<const T>::_node const_node;
			return const_iterator(reinterpret_cast<const_node *>(last));
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		//Capacity:

		bool empty() const
		{
			return newSize == 0;
		}

		size_type size() const
		{
			return newSize;
		}

		size_type max_size() const
		{
			return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
		}

		//Element access:

		reference front()
		{
			return firstN->data;
		}

		const_reference front() const
		{
			return firstN->data;
		}

		reference back()
		{
			return last->prev->data;
		}

		const_reference back() const
		{
			return last->prev->data;
		}

		//Modifiers:

		template<typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			clear();
			insert(begin(), first, last);
		}

		void assign(size_type n, const value_type &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void push_front(const value_type &val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		void push_back(const value_type &val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			iterator it = end();
			it--;
			erase(it);
		}

		iterator insert(iterator position, const value_type &val)
		{
			_node *n = new _node(position.newNode->prev, position.newNode);
			n->data = val;
			if (n->prev)
				n->prev->next = n;
			else
				firstN = n;

			n->next->prev = n;
			newSize++;
			return iterator(n);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			_node *leftNode = position.newNode->prev;
			_node *rightNode = position.newNode;
			_node *insert = leftNode;
			for (size_type i = 0; i < n; i++)
			{
				_node *n = new _node(insert, NULL);
				n->data = val;
				if (insert)
					insert->next = n;
				else
					firstN = n;
				newSize++;
				insert = n;
			}
			rightNode->prev = insert;
			if (insert)
				insert->next = rightNode;
		}

		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			_node *leftNode = position.newNode->prev;
			_node *rightNode = position.newNode;
			_node *insert = leftNode;
			for (InputIterator it = first; it != last; it++)
			{
				_node *n = new _node(insert, NULL);
				n->data = *it;
				if (insert)
					insert->next = n;
				else
					firstN = n;
				newSize++;
				insert = n;
			}
			rightNode->prev = insert;
			if (insert)
				insert->next = rightNode;
		}

		iterator erase(iterator position)
		{
			if (position.newNode->prev)
				position.newNode->prev->next = position.newNode->next;
			else
				firstN = position.newNode->next;
			if (position.newNode->next)
				position.newNode->next->prev = position.newNode->prev;

			iterator ret = position.newNode->next;
			newSize--;
			delete position.newNode;
			return ret;
		}

		iterator erase(iterator first, iterator last)
		{
			iterator it = first;
			while(it != last)
				it = erase(it);
			return it;
		}

		void swap(List &x)
		{
			std::swap(firstN, x.firstN);
			std::swap(last, x.last);
			std::swap(newSize, x.newSize);
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n >= newSize)
				insert(end(), n - newSize, val);
			else
			{
				iterator it = begin();
				for (size_type i = 0; i < n; i++)
					it++;
				erase(it, end());
			}
		}

		void clear()
		{
			erase(begin(), end());
		}

		//Operations:

		void splice(iterator position, Self &x)
		{
			splice(position, x, x.begin(), x.end());
		}

		void splice(iterator position, Self &x, iterator i)
		{
			iterator next = i;
			++next;
			splice(position, x, i, next);
		}

		void splice(iterator position, Self &x, iterator first, iterator last)
		{
			_node *node_right = position.newNode;
			_node *node_left = node_right->prev;

			_node *nodeR = last.newNode;
			_node *nodeL = first.newNode->prev;

			size_type count = 0;
			for (; first != last; ++first)
			{
				_node *to_transfer = first.newNode;

				if (node_left)
					node_left->next = to_transfer;
				else
					firstN = to_transfer;

				to_transfer->prev = node_left;

				node_left = to_transfer;
				++count;
			}

			node_left->next = node_right;
			node_right->prev = node_left;
			nodeR->prev = nodeL;
			if (nodeL)
				nodeL->next = nodeR;
			else
				x.firstN = nodeR;

			newSize += count;
			x.newSize -= count;
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

		template <typename Predicate>
		void remove_if(Predicate pred)
		{
			for (iterator it = begin(); it != end();)
			{
				if (pred(*it))
					it = erase(it);
				else
					it++;
			}
		}

		void unique()
		{
			unique(Peer<T>());
		}

		template <typename BinaryPredicate>
		void unique(BinaryPredicate binary_pred)
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

		void merge(List &x)
		{
			merge(x, std::less<T>());
		}

		template <typename Compare>
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
					firstN = tmp.newNode;
				tmp.newNode->prev = selfIt.newNode->prev;
				tmp.newNode->next = selfIt.newNode;
				selfIt.newNode->prev = tmp.newNode;
			}
			newSize += x.newSize;
			x.newSize = 0;
			x.firstN = x.last;
			x.last->prev = NULL;
		}

		void sort()
		{
			sort(Bit<T>());
		}

		template <typename Compare>
		void sort(Compare comp)
		{
			if (begin() == end())
				return ;
			for (size_type i = 0; i < newSize; i++)
			{
				iterator cur = begin();
				iterator nxt = cur;
				nxt++;
				while (nxt != end())
				{
					if (!comp(*cur, *nxt))
					{
						_node *node_left = cur.newNode->prev;
						_node *node_right = nxt.newNode->next;
						cur.newNode->prev = nxt.newNode;
						nxt.newNode->next = cur.newNode;
						if (node_left)
							node_left->next = nxt.newNode;
						else
							firstN = nxt.newNode;
						nxt.newNode->prev = node_left;
						node_right->prev = cur.newNode;
						cur.newNode->next = node_right;
						nxt = cur;
						nxt++;
					}
					else
					{
						cur = nxt;
						nxt++;
					}
				}
			}
		}

		void reverse()
		{
			iterator it = begin();
			iterator begin = it;
			while (1)
			{
				iterator tmp = it;
				++it;
				if (tmp.newNode->next == last)
				{
					tmp.newNode->next = tmp.newNode->prev;
					tmp.newNode->prev = NULL;
					firstN = tmp.newNode;
					break;
				}
				else
					std::swap(tmp.newNode->prev, tmp.newNode->next);
			}
			last->prev = begin.newNode;
			begin.newNode->next = last;
		}

	};

	//Non-member function overloads:

	template <typename T>
	bool operator==(const List<T> &lhs, const List<T> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T>
	bool operator!= (const List<T> &lhs, const List<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const List<T> &lhs, const List<T> &rhs)
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	bool operator<=(const List<T> &lhs, const List<T> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T>
	bool operator>(const List<T> &lhs, const List<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator>=(const List<T> &lhs, const List<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	void swap (List<T> &x, List<T> &y)
	{
		return x.swap(y);
	}

};

#endif
