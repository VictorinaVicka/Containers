/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TurnedIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:44:38 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/22 17:21:36 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TURNEDITERATOR_HPP
# define TURNEDITERATOR_HPP

# include <iostream>
# include <cstddef>

namespace ft
{
    template <typename Iterator>
	class	TurnedIterator
	{
	public:
		typedef Iterator iterator_type;
		typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename std::iterator_traits<Iterator>::value_type value_type;
		typedef typename std::iterator_traits<Iterator>::difference_type diff_type;
		typedef typename std::iterator_traits<Iterator>::pointer pointer;
		typedef typename std::iterator_traits<Iterator>::reference reference;

	private:
		typedef TurnedIterator<Iterator> Self;

        Iterator newBase;

	public:
        TurnedIterator() {}
		TurnedIterator(Iterator base): newBase(base) {}
		TurnedIterator(const TurnedIterator<Iterator> &c): newBase(c.newBase) {}
		~TurnedIterator() {}

        iterator_type base() const
		{
            return newBase;
        }

        Self &operator=(const Self &c)
		{
			newBase = c.newBase;
			return *this;
		}

        reference operator*() const
		{
            iterator_type it(newBase);
            it--;
            return *it;
        }

        pointer operator->() const
		{
			iterator_type it(newBase);
			--it;
			return it.operator->();
		}

        Self &operator--()
		{
			++newBase;
			return *this;
		}

		Self operator--(int)
		{
			Self rit(newBase++);
			return rit;
		}

        Self &operator-=(diff_type offset)
		{
			newBase += offset;
			return *this;
		}

		Self &operator++()
		{
            --newBase;
            return *this;
        }

        Self  operator++(int)
		{
            Self rit(newBase--);
            return rit;
        }

        Self &operator+=(diff_type offset)
		{
			newBase -= offset;
			return *this;
		}
    };

    template <typename Iterator>
	bool operator==(const TurnedIterator<Iterator> &lhs, const TurnedIterator<Iterator> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator>
	bool operator!=(const TurnedIterator<Iterator> &lhs, const TurnedIterator<Iterator> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename Iterator>
	bool operator<(const TurnedIterator<Iterator> &lhs, const TurnedIterator<Iterator> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iterator>
	bool operator<=(const TurnedIterator<Iterator> &lhs, const TurnedIterator<Iterator> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename Iterator>
	bool operator>(const TurnedIterator<Iterator> &lhs, const TurnedIterator<Iterator> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator>
	bool operator>=(const TurnedIterator<Iterator> &lhs, const TurnedIterator<Iterator> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename Iterator>
	TurnedIterator<Iterator> operator-(const TurnedIterator<Iterator> &rit, typename TurnedIterator<Iterator>::difference_type offset)
	{
		TurnedIterator<Iterator> r(rit.base() + offset);
		return r;
	}

	template <typename Iterator>
	ptrdiff_t operator-(const TurnedIterator<Iterator> &lhs, const TurnedIterator<Iterator> &rhs)
	{
		return rhs.base() - lhs.base();
	}

	template <typename Iterator>
	TurnedIterator<Iterator> operator+(const TurnedIterator<Iterator> &rit, size_t offset)
	{
		TurnedIterator<Iterator> r(rit.base() - offset);
		return r;
	}

	template <typename Iterator>
	TurnedIterator<Iterator> operator+(typename TurnedIterator<Iterator>::difference_type offset, const TurnedIterator<Iterator> &rit)
	{
		TurnedIterator<Iterator> r(rit.base() - offset);
		return r;
	}
}

#endif
