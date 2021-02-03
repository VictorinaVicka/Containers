/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:20:37 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/03 10:57:06 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <sstream>
# include "Vector_Iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class Vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef T &reference;
		typedef const T	&const_reference;
		typedef	T *pointer;
		typedef	const T	*const_pointer;
		typedef ft::VectorIt<T>	iterator;
		typedef ft::ConstVectorIt<T> const_iterator;
		typedef ft::ReverseVectorIt<T>	reverse_iterator;
		typedef ft::ConstReverseVectorIt<T>	const_reverse_iterator;
		typedef typename ft::ReverseVectorIt<T>::difference_type difference_type;
		typedef size_t size_type;

	private:
		allocator_type	alloc;
		value_type	*arr;
		size_type	newSize;
		size_type	newType;

	public:
		explicit Vector(const allocator_type& alloc = allocator_type())
		{
			this->alloc = alloc;
			arr = this->alloc.allocate(2);
			newSize = 0;
			newType = 0;
			return ;
		}

		Vector(const Vector &copy)
		{
			alloc = copy.alloc;
			arr = alloc.allocate(2);
			newSize = 0;
			newType = 0;
			*this = copy;
			return ;
		}

		Vector &operator=(const Vector &target)
		{
			size_type size;

			clear();
			alloc.deallocate(arr, newType + 2);
			alloc = target.alloc;
			newType = target.newType;
			arr = alloc.allocate(newType + 2);
			newSize = target.newSize;
			size = target.newSize + 1;
			while (size--)
				arr[size] = target.arr[size];
			return (*this);
		}

		~Vector()
		{
			if (newType > 0)
				alloc.deallocate(arr, newType);
		}

		// Member functions:

		explicit Vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		{
			this->alloc = alloc;
			arr = alloc.allocate(2);
			newSize = 0;
			newType = 0;
			assign(static_cast<size_type>(n), static_cast<value_type>(val));
		}

		template <class InputIt>
		Vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
		{
			this->alloc = alloc;
			arr = alloc.allocate(2);
			newSize = 0;
			newType = 0;
			assign(static_cast<InputIt>(first), static_cast<InputIt>(last));
		}

		iterator begin()
		{
			return (iterator(&(arr[0 + 1])));
		}

		const_iterator begin() const
		{
			return (const_iterator(&(arr[0 + 1])));
		}

		iterator end()
		{
			return (iterator(&(arr[newSize + 1])));
		}

		const_iterator end() const
		{
			return (const_iterator(&(arr[newSize + 1])));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(&(arr[newSize])));
		}

		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(&(arr[newSize])));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(&(arr[0])));
		}

		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(&(arr[0])));
		}

		// Capacity:

		size_type size() const
		{
			return (newSize);
		}

		size_type max_size() const
		{
			return (std::numeric_limits<size_type>::max()/sizeof(value_type));
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n >= newSize)
				insert(end(), n - newSize, val);
			else
				erase(begin() + n, end());
		}

		size_type capacity() const
		{
			return (newType);
		}

		bool empty() const
		{
			return (!newSize);
		}

		void reserve(size_type n)
		{
			if (n > max_size())
				throw(std::length_error("max_size done"));
			if (n > newType)
			{
				size_type	tmp;
				value_type	*newArr;

				newArr = alloc.allocate(n + 2);
				tmp = newType;
				newType = n;
				while (n)
				{
					if (n <= newSize + 1)
						newArr[n] = arr[n];
					n--;
				}
				alloc.deallocate(arr, tmp + 2);
				arr = newArr;
			}
		}

		// Element access:

		reference operator[](size_type n)
		{
			return (arr[n + 1]);
		}

		const_reference operator[](size_type n) const
		{
			return (arr[n + 1]);
		}

		reference at(size_type n)
		{
			if (n >= newSize)
			{
				std::stringstream str;
                str << "index " << n << " out of bound (size() is " << size() << ");";
				throw std::out_of_range(str.str());
			}
			return (arr[n + 1]);
		}

		const_reference at(size_type n) const
		{
			if (n >= newSize)
				{
                std::stringstream str;
                str << "index " << n << " out of bound (size() is " << size() << ");";
                throw std::out_of_range(str.str());
           		}
			return (arr[n + 1]);
		}

		reference front()
		{
			return (arr[0]);
		}

		const_reference front() const
		{
			return (arr[0]);
		}

		reference back()
		{
			return (arr[newSize]);
		}

		const_reference back() const
		{
			return (arr[newSize]);
		}

		// Modifiers:

		template <class InputIt>
		void assign(InputIt first, InputIt last)
		{
			clear();
			insert(begin(), first, last);
		}

		void assign(size_type n, const value_type &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void push_back(const value_type &val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			if (newSize)
				newSize--;
		}

		iterator insert(iterator position, const value_type &val)
		{
			iterator it;
			size_t i;
			size_t j;

			i = newSize + 1;
			it = end();
			while (position != it)
			{
				arr[i] = arr[i - 1];
				i--;
				position++;
			}
			arr[i] = val;
			j = newSize + 1;
			if ((j) > capacity())
				reserve(j);
			newSize++;
			return (iterator(&arr[i]));
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			while (n--)
				position = insert(position, val);
		}

		template <class InputIt>
		void insert(iterator position, InputIt first, InputIt last)
		{
			while (first != last)
			{
				position = insert(position, *first);
				position++;
				first++;
			}
		}

		iterator erase(iterator position)
		{
			iterator it;
			iterator it2;

			it2 = position;
			while (it2 != end())
			{
				it = it2;
				it++;
				*it2 = *it;
				it2++;
			}
			newSize--;
			return (position);
		}

		iterator erase(iterator first, iterator last)
		{
			iterator it;
			iterator it2;

			it = first;
			it2 = last;
			while (last != end())
			{
				*it = *last;
				it++;
				last++;
			}
			last = it2;
			it = first;
			while (it != last)
			{
				it++;
				newSize--;
			}
			return (first);
		}

		void swap(Vector &x)
		{
			value_type *valueType_temp = arr;
			arr = x.arr;
			x.arr = valueType_temp;
			size_type sizetype_temp = newSize;
			newSize = x.newSize;
			x.newSize = sizetype_temp;
			sizetype_temp = newType;
			newType = x.newType;
			x.newType = sizetype_temp;
			allocator_type allocatortype_temp = alloc;
			alloc = x.alloc;
			x.alloc = allocatortype_temp;
		}

		void clear()
		{
			erase(begin(), end());
		}

	};

	// Non-member function overloads:

	template <class T, class Alloc>
	bool operator==(const Vector<T,Alloc> &lhs, const Vector<T,Alloc> &rhs)
	{
		size_t i;

		if (lhs.size() != rhs.size())
			return (false);
		i = 0;
		while (i < lhs.size())
		{
			if (lhs.at(i) != rhs.at(i))
				return (false);
			i++;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!=(const Vector<T,Alloc> &lhs, const Vector<T,Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const Vector<T,Alloc> &lhs, const Vector<T,Alloc> &rhs)
	{
		size_t size1;
		size_t size2;

		size1 = 0;
		if (lhs.size() < rhs.size())
			size2 = lhs.size();
		else
			size2 = rhs.size();
		while (size1 < size2)
		{
			if (lhs.at(size1) != rhs.at(size1))
				return (lhs.at(size1) < rhs.at(size1));
			size1++;
		}
		return (lhs.size() < rhs.size());
	}

	template <class T, class Alloc>
	bool operator<=(const Vector<T,Alloc> &lhs, const Vector<T,Alloc> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator>(const Vector<T,Alloc> &lhs, const Vector<T,Alloc> &rhs)
	{
		return (!(lhs < rhs) && !(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator>=(const Vector<T,Alloc> &lhs, const Vector<T,Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap(Vector<T,Alloc> &x, Vector<T,Alloc> &y)
	{
		x.swap(y);
	}
};

#endif
