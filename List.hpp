/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:54:36 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/22 15:12:59 by tfarenga         ###   ########.fr       */
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
		typedef T value;
		typedef T *pointer;
		typedef T &reference;
		typedef	std::ptrdiff_t diff;
		typedef std::bidirectional_iterator_tag iterator_tag;

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
		friend bool operator==(const ListIt<_T> &left, const ListIt<_T> &right);

		template <typename _T>
		friend bool operator!=(const ListIt<_T> &left, const ListIt<_T> &right);

		Self &operator=(const Self &s)
		{
			newNode = s.newNode;
			return *this;
		}

		Self &operator--()
		{
			newNode = newNode->prev;
			return *this;
		}

		Self operator--(int)
		{
			Self copy = *this;
			--*this;
			return copy;
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
	bool operator==(const ListIt<T> &left, const ListIt<T> &right)
	{
		return left.newNode == right.newNode;
	}

	template <typename T>
	bool operator!=(const ListIt<T> &left, const ListIt<T> &right)
	{
		return !(left.newNode == right.newNode);
	}

	template <typename T>
	class	List
	{
	public:
		typedef T value;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef ListIt<T> iterator;
		typedef const ListIt<const T> const_iterator;
		typedef TurnedIterator<iterator> reverse_iterator;
		typedef const TurnedIterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		typedef List<T> Self;

		struct Node
		{
			value data;
			Node *prev;
			Node *next;

			Node(Node *prev_, Node *next_): prev(prev_), next(next_) {};
		};
		size_type _size;
		Node *first;
		Node *last;
	public:

		//Member functions:

		List(): _size(0)
		{
			first = new Node(NULL, NULL);
			last = first;
		}

		List(size_type n, const value &val): _size(0)
		{
			first = new Node(NULL, NULL);
			last = first;
			insert(begin(), n, val);
		}

		template <typename InputIterator>
		List(InputIterator first, InputIterator last): _size(0)
		{
			first = new Node(NULL, NULL);
			last = first;
			insert(begin(), first, last);
		}

		List(const Self &c): _size(0)
		{
			first = new Node(NULL, NULL);
			last = first;
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


		Self &operator=(const List &c)
		{
			clear();
			insert(begin(), c.begin(), c.end());
			return *this;
		}

		// Iterators:

		iterator begin()
		{
			return iterator(first);
		}

		iterator end()
		{
			return iterator(last);
		}

		const_iterator begin() const
		{
			typedef typename List<const T>::_node const_node;
			return const_iterator(reinterpret_cast<const_node *>(first));
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
			return _size == 0;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return std::numeric_limits<std::size_t>::max() / sizeof(value);
		}

		//Element access:

		reference front()
		{
			return first->data;
		}

		const_reference front() const
		{
			return first->data;
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

		void assign(size_type n, const value &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void push_front(const value &val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		void push_back(const value &val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			iterator it = end();
			it--;
			erase(it);
		}

		iterator insert(iterator position, const value &val)
		{
			Node *n = new Node(position.newNode->prev, position.newNode);
			n->data = val;

			if (n->prev)
				n->prev->next = n;
			else
				first = n;

			n->next->prev = n;
			_size++;
			return iterator(n);
		}

		void insert(iterator position, size_type n, const value &val)
		{
			Node *leftNode = position.newNode->prev;
			Node *rightNode = position.newNode;

			Node *insert = leftNode;
			for (size_type i = 0; i < n; i++)
			{
				Node *n = new Node(insert, NULL);
				n->data = val;

				if (insert)
					insert->next = n;
				else
					first = n;

				_size++;
				insert = n;
			}
			rightNode->prev = insert;
			if (insert)
				insert->next = rightNode;
		}

		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			Node *leftNode = position.newNode->prev;
			Node *rightNode = position.newNode;
			Node *insert = leftNode;
			for (InputIterator it = first; it != last; it++)
			{
				Node *n = new Node(insert, NULL);
				n->data = *it;
				if (insert)
					insert->next = n;
				else
					first = n;
				_size++;
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
				first = position.newNode->next;
			if (position.newNode->next)
				position.newNode->next->prev = position.newNode->prev;
			iterator ret = position.newNode->next;
			_size--;
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
			std::swap(first, x.first);
			std::swap(last, x.last);
			std::swap(_size, x._size);
		}

		void resize(size_type n, value val = value())
		{
			if (n >= _size)
				insert(end(), n - _size, val);
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

		void splice(iterator position, List &x)
		{
			splice(position, x, x.begin(), x.end());
		}

		void splice(iterator position, List &x, iterator i)
		{
			Node *left = position.newNode->prev;
			Node *right = position.newNode;
			Node *x_left = i.newNode->prev;
			Node *x_rightNode = i.newNode->next;
			if (left) {
				left->next = i.newNode;
				i.newNode->prev = left;
			}
			else {
				first = i.newNode;
				i.newNode->prev = NULL;
			}
			i.newNode->next = right;
			right->prev = i.newNode;
			if (x_left)
				x_left->next = x_rightNode;
			else
				x.first = x_rightNode;
			x_rightNode->prev = x_left;
			_size++;
			x._size--;
		}

		void splice(iterator position, List &x, iterator first, iterator last)
		{
			while (first != last) {
				iterator it = first;
				first++;
				splice(position, x, it);
			}
		}

		void remove(const value &val)
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
			iterator self = begin();
			for (iterator it = x.begin(); it != x.end();)
			{
				while(self != end() && comp(*self, *it))
					self++;

				iterator tmp = it;
				it++;
				if (self.newNode->prev)
					self.newNode->prev->next = tmp.newNode;
				else
					first = tmp.newNode;
				tmp.newNode->prev = self.newNode->prev;
				tmp.newNode->next = self.newNode;
				self.newNode->prev = tmp.newNode;
			}

			_size += x._size;
			x._size = 0;
			x.first = x.last;
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
			for (size_type i = 0; i < _size; i++)
			{
				iterator cur = begin();
				iterator next = cur;
				next++;
				while (next != end())
				{
					if (!comp(*cur, *next))
					{
						Node *left = cur.newNode->prev;
						Node *right = next.newNode->next;
						cur.newNode->prev = next.newNode;
						next.newNode->next = cur.newNode;
						if (left)
							left->next = next.newNode;
						else
							first = next.newNode;
						next.newNode->prev = left;
						right->prev = cur.newNode;
						cur.newNode->next = right;
						next = cur;
						next++;
					}
					else
					{
						cur = next;
						next++;
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
					first = tmp.newNode;
					break;
				}
				else
					std::swap(tmp.newNode->prev, tmp.newNode->next);
			}
			last->prev = begin.newNode;
			begin.newNode->next = last;
		}
	};

	//Non-member function overloads

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
