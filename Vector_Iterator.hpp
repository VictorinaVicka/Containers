/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector_Iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:31:56 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/02 12:42:53 by tfarenga         ###   ########.fr       */
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

		VectorIt() {}

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

		~VectorIt() {}

		VectorIt &operator++()
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

		VectorIt &operator--()
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

		T &operator*()
		{
			return (*point);
		}

		T *operator->()
		{
			return (point);
		}

		VectorIt operator+(int target) const
		{
			VectorIt ptr(*this);

			ptr += target;
			return (ptr);
		}

		VectorIt operator-(int target) const
		{
			VectorIt ptr(*this);

			ptr -= target;
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

		VectorIt &operator+=(int target)
		{
			while (target < 0)
			{
				target++;
				operator--();
			}
			while (target > 0)
			{
				target--;
				operator++();
			}
			return (*this);
		}

		VectorIt &operator-=(int target)
		{
			while (target < 0)
			{
				target++;
				operator++();
			}
			while (target > 0)
			{
				target--;
				operator--();
			}
			return (*this);
		}

		T &operator[](int target) const
		{
			return (*(*this + target));
		}

		pointer	getPoint() const
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
		ReverseVectorIt() {}

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

		~ReverseVectorIt() {}

		ReverseVectorIt	&operator++()
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

		ReverseVectorIt	&operator+=(int target) const
		{
			while (target < 0)
			{
				target++;
				this++;
			}
			while (target > 0)
			{
				target--;
				this--;
			}
			return (*this);
		}

		ReverseVectorIt	&operator--()
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

		ReverseVectorIt	&operator-=(int target) const
		{
			while (target < 0)
			{
				target++;
				this--;
			}
			while (target > 0)
			{
				target--;
				this++;
			}
			return (*this);
		}

		T &operator[](int target) const
		{
			return (*(*this - target));
		}
	};

	template <class T>
	class ConstVectorIt : public VectorIt<T>
	{
	public:
		ConstVectorIt() {}

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

		~ConstVectorIt() {}

		const T	&operator*()
		{
			return (*this->point);
		}
	};

	template <class T>
	class ConstReverseVectorIt : public ReverseVectorIt<T>
	{
	public:
		ConstReverseVectorIt() {}

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

		~ConstReverseVectorIt() {}

		const T	&operator*()
		{
			return (*this->point);
		}
	};
};


#endif