/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector_Iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:31:56 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/01 17:30:58 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "Start.hpp"

namespace ft
{

	template <class T, class Container = random_access>
	class VectorIt
	{
	public:
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;
		typedef Container сontainer;
		typedef std::ptrdiff_t difference_type;

	protected:
		pointer	point;

	public:

		VectorIt(void) {}

		~VectorIt(void) {}

		VectorIt(const VectorIt &it)
		{
			*this = it;
		}

		VectorIt &operator=(const VectorIt &target)
		{
			point = target.point;
			return (*this);
		}

		VectorIt(pointer ptr)
		{
			point = ptr;
		}

		VectorIt &operator++(void)
		{
			point++;
			return (*this);
		}

		VectorIt operator++(int)
		{
			VectorIt ptr(*this);
			operator++();
			return (ptr);
		}

		VectorIt &operator--(void)
		{
			point--;
			return (*this);
		}

		VectorIt operator--(int)
		{
			VectorIt ptr(*this);
			operator--();
			return (ptr);
		}

  		bool operator==(const VectorIt &target) const
		{
			return (point == target.point);
		}

  		bool operator!=(const VectorIt &target) const
		{
			return (point != target.point);
		}

		T &operator*(void)
		{
			return (*point);
		}

		T *operator->(void)
		{
			return (point);
		}

		VectorIt operator+(int n) const
		{
			VectorIt ptr(*this);

			ptr += n;
			return (ptr);
		}

		VectorIt operator-(int n) const
		{
			VectorIt ptr(*this);

			ptr -= n;
			return (ptr);
		}

		bool operator<(const VectorIt &target) const
		{
			return (point < target.point);
		}

		bool operator<=(const VectorIt &target) const
		{
			return (point <= target.point);
		}

		bool operator>(const VectorIt &target) const
		{
			return (point > target.point);
		}

		bool operator>=(const VectorIt &target) const
		{
			return (point >= target.point);
		}

		VectorIt &operator+=(int n)
		{
			while (n < 0)
			{
				n++;
				operator--();
			}
			while (n > 0)
			{
				n--;
				operator++();
			}
			return (*this);
		}

		VectorIt &operator-=(int n)
		{
			while (n < 0)
			{
				n++;
				operator++();
			}
			while (n > 0)
			{
				n--;
				operator--();
			}
			return (*this);
		}

		T &operator[](int n) const
		{
			return (*(*this + n));
		}

		pointer	getPoint(void) const
		{
			return (point);
		}
	};

	template <class T, class Container = random_access>
	class ReverseVectorIt : public VectorIt<T>
	{
	public:
		typedef T	value_type;
		typedef T	&reference;
		typedef T	*pointer;
		typedef Container	container;
		typedef std::ptrdiff_t	difference_type;

	public:
		ReverseVectorIt(void) {}

		~ReverseVectorIt(void) {}

		ReverseVectorIt(pointer ptr)
		{
			this->point = ptr;
		}

		ReverseVectorIt(const ReverseVectorIt &copy)
		{
			*this = copy;
		}

		ReverseVectorIt	&operator=(const ReverseVectorIt &target)
		{
			this->point = target.point;
			return (*this);
		}

		ReverseVectorIt	&operator++(void)
		{
			this->point--;
			return (*this);
		}

		ReverseVectorIt	operator++(int)
		{
			ReverseVectorIt ptr(*this);
			operator++();
			return (ptr);
		}

		ReverseVectorIt	&operator+=(int n) const
		{
			while (n < 0)
			{
				n++;
				this++;
			}
			while (n > 0)
			{
				n--;
				this--;
			}
			return (*this);
		}

		ReverseVectorIt	&operator--(void)
		{
			this->point++;
			return (*this);
		}

		ReverseVectorIt	operator--(int)
		{
			ReverseVectorIt ptr(*this);
			operator--();
			return (ptr);
		}

		ReverseVectorIt	&operator-=(int n) const
		{
			while (n < 0)
			{
				n++;
				this--;
			}
			while (n > 0)
			{
				n--;
				this++;
			}
			return (*this);
		}

		T &operator[](int n) const
		{
			return (*(*this - n));
		}
	};

	template <class T>
	class ConstVectorIt : public VectorIt<T>
	{
	public:
		ConstVectorIt(void) {}

		~ConstVectorIt(void) {}

		ConstVectorIt(T *ptr)
		{
			this->point = ptr;
		}

		ConstVectorIt(const ConstVectorIt &copy)
		{
			*this = copy;
		}

		ConstVectorIt &operator=(const ConstVectorIt &target)
		{
			this->point = target.point;
			return (*this);
		}

		const T	&operator*(void)
		{
			return (*this->point);
		}
	};

	template <class T>
	class ConstReverseVectorIt : public ReverseVectorIt<T>
	{
	public:
		ConstReverseVectorIt(void) {}

		~ConstReverseVectorIt(void) {}

		ConstReverseVectorIt(T *ptr)
		{
			this->point = ptr;
		}

		ConstReverseVectorIt(const ConstReverseVectorIt &copy)
		{
			*this = copy;
		}

		ConstReverseVectorIt &operator=(const ConstReverseVectorIt &target)
		{
			this->point = target.point;
			return (*this);
		}

		const T	&operator*(void)
		{
			return (*this->point);
		}
	};
};


#endif