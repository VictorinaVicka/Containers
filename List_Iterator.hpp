/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_Iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:27:25 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/03 11:41:14 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "Start.hpp"

namespace ft
{
	template <class T>
	struct Node
	{
		Node	*prev;
		Node	*next;
		T		*data;
	};

	template <class T, class Category = bidirectional_tag>
	class ListIt
	{
	private:
		ListIt	operator+(const ListIt &c) const;
		ListIt	operator+(int n) const;
		ListIt	operator-(const ListIt &c) const;
		ListIt	operator-(int n) const;
		ListIt	&operator+=(int n) const;
		ListIt	&operator-=(int n) const;
		bool	operator<(const ListIt &c) const;
		bool	operator<=(const ListIt &c) const;
		bool	operator>(const ListIt &c) const;
		bool	operator>=(const ListIt &c) const;
		T		&operator[](int n) const;

	protected:
		Node<T>	*newNode;
	public:
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;
		typedef Category category;
		typedef std::ptrdiff_t difference_type;

		ListIt() {}

		ListIt(const ListIt &copy)
		{
			*this = copy;
		}

		ListIt &operator=(const ListIt &target)
		{
			newNode = target.newNode;
			return (*this);
		}

		~ListIt() {}

		ListIt(Node<T> *list)
		{
			newNode = list;
		}

		ListIt &operator++()
		{
			if (this->newNode && this->newNode->next)
				this->newNode = this->newNode->next;
			return (*this);
		}

		ListIt operator++(int)
		{
			ListIt tmp(*this);
			this->operator++();
			return (tmp);
		}

		ListIt &operator--()
		{
			if (newNode && newNode->prev)
				newNode = newNode->prev;
			return (*this);
		}

		ListIt operator--(int)
		{
			ListIt tmp(*this);
			this->operator--();
			return (tmp);
		}

  		bool operator==(const ListIt &c) const
		{
			return (newNode == c.newNode);
		}

  		bool operator!=(const ListIt &c) const
		{
			return (newNode != c.newNode);
		}

		T &operator*()
		{
			return (*newNode->data);
		}

		T *operator->()
		{
			return (newNode->data);
		}

		Node<T> *getNewNode()
		{
			return (newNode);
		}
	};

	template <class T>
	class ReverseListIt : public ListIt<T>
	{
	public:
		ReverseListIt() {}

		ReverseListIt(Node<T> *copy)
		{
			this->newNode = copy;
		}

		ReverseListIt(const ReverseListIt &target)
		{
			*this = target;
		}

		~ReverseListIt() {}

		ReverseListIt &operator=(const ReverseListIt &target)
		{
			this->newNode = target.newNode;
			return (*this);
		}

		ReverseListIt &operator++()
		{
			if (this->newNode && this->newNode->prev)
				this->newNode = this->newNode->prev;
			return (*this);
		}

		ReverseListIt operator++(int)
		{
			ReverseListIt tmp(*this);
			this->operator++();
			return (tmp);
		}

		ReverseListIt &operator--()
		{
			if (this->newNode && this->newNode->next)
				this->newNode = this->newNode->next;
			return (*this);
		}

		ReverseListIt operator--(int)
		{
			ReverseListIt tmp(*this);
			this->operator--();
			return (tmp);
		}
	};

	template <class T>
	class ConstListIt : public ListIt<T>
	{
	public:
		ConstListIt() {}

		ConstListIt(Node<T> *list)
		{
			this->newNode = list;
		}

		ConstListIt(const ConstListIt &copy)
		{
			*this = copy;
		}

		ConstListIt &operator=(const ConstListIt &target)
		{
			this->newNode = target.newNode;
			return (*this);
		}

		~ConstListIt() {}

		const T &operator*()
		{
			return (*this->newNode->data);
		}
	};

	template <class T>
	class ConstReverseListIt : public ReverseListIt<T>
	{
	public:
		ConstReverseListIt() {}

		ConstReverseListIt(Node<T> *list)
		{
			this->newNode = list;
		}

		ConstReverseListIt(const ConstReverseListIt &copy)
		{
			*this = copy;
		}

		ConstReverseListIt &operator=(const ConstReverseListIt &target)
		{
			this->newNode = target.newNode;
			return (*this);
		}

		~ConstReverseListIt() {}

		const T &operator*()
		{
			return (*this->newNode->data);
		}
	};
};


#endif