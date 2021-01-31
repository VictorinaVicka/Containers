/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List_Iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:27:25 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/30 14:45:07 by tfarenga         ###   ########.fr       */
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
		typedef T								value_type;
		typedef T								&reference;
		typedef T								*pointer;
		typedef Category						category;
		typedef std::ptrdiff_t					difference_type;

		ListIt(void) {}

		~ListIt(void) {}

		ListIt(const ListIt &it)
		{
			*this = it;
		}

		ListIt &operator=(const ListIt &c)
		{
			newNode = c.newNode;
			return (*this);
		}

		ListIt(Node<T> *list)
		{
			newNode = list;
		}

		ListIt &operator++(void)
		{
			if (newNode && newNode->next)
				newNode = newNode->next;
			return (*this);
		}

		ListIt operator++(int)
		{
			ListIt tmp(*this);
			this->operator++();
			return (tmp);
		}

		ListIt &operator--(void)
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

		T &operator*(void)
		{
			return (*newNode->data);
		}

		T *operator->(void)
		{
			return (newNode->data);
		}

		Node<T> *getNewNode(void)
		{
			return (newNode);
		}
	};

	template <class T>
	class ReverseListIt : public ListIt<T>
	{
	public:
		ReverseListIt(void) {}
		~ReverseListIt(void) {}

		ReverseListIt(Node<T> *list)
		{
			this->newNode = list;
		}

		ReverseListIt(const ReverseListIt &it)
		{
			*this = it;
		}

		ReverseListIt			&operator=(const ReverseListIt &it)
		{
			this->newNode = it.newNode;
			return (*this);
		}

		ReverseListIt			&operator++(void)
		{
			if (this->newNode && this->newNode->prev)
				this->newNode = this->newNode->prev;
			return (*this);
		}

		ReverseListIt			operator++(int)
		{
			ReverseListIt tmp(*this);
			this->operator++();
			return (tmp);
		}

		ReverseListIt			&operator--(void)
		{
			if (this->newNode && this->newNode->next)
				this->newNode = this->newNode->next;
			return (*this);
		}

		ReverseListIt			operator--(int)
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
		ConstListIt(void) {}
		~ConstListIt(void) {}

		ConstListIt(Node<T> *list)
		{
			this->newNode = list;
		}

		ConstListIt(const ConstListIt &it)
		{
			*this = it;
		}

		ConstListIt			&operator=(const ConstListIt &it)
		{
			this->newNode = it.newNode;
			return (*this);
		}

		const T						&operator*(void) // dereferenced lvalue
		{
			return (*this->newNode->data);
		}
	};

	template <class T>
	class ConstReverseListIt : public ReverseListIt<T>
	{
	public:
		ConstReverseListIt(void) {}
		~ConstReverseListIt(void) {}

		ConstReverseListIt(Node<T> *list)
		{
			this->newNode = list;
		}

		ConstReverseListIt(const ConstReverseListIt &it)
		{
			*this = it;
		}

		ConstReverseListIt			&operator=(const ConstReverseListIt &it)
		{
			this->newNode = it.newNode;
			return (*this);
		}

		const T						&operator*(void) // dereferenced lvalue
		{
			return (*this->newNode->data);
		}
	};
};


#endif