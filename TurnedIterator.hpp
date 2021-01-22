/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TurnedIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:44:38 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/22 12:20:35 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TURNEDITERATOR_HPP
# define TURNEDITERATOR_HPP

# include <iostream>
# include <cstddef>
# include <limits>
# include <string>

namespace ft
{
	template<typename Iterator>
	class TurnedIterator
	{
		public:
		typedef TurnedIterator<Iterator> turned;
		typedef typename 	Iterator::diff_type diff_type;
		typedef typename 	Iterator::size size;
		typedef typename	Iterator::pointer pointer;
		typedef typename	Iterator::reference reference;
		typedef typename	Iterator::value value;
		typedef typename	Iterator::const_reference const_reference;
		typedef typename	Iterator::const_pointer const_pointer;

		TurnedIterator() {};

		TurnedIterator(const TurnedIterator& it)
		{
			base = it.base;
		};

		void operator = (const TurnedIterator& it)
		{
			base = it.base;
		};

		TurnedIterator(Iterator base): base(base)
		{};

			~TurnedIterator() {};

			bool operator == (const TurnedIterator& it) const
			{
				return (it.base == base);
			};

			bool operator != (const TurnedIterator& it) const
			{
				return (it.base != base);
			};

			reference operator * ()
			{
				return (*base);
			};

			pointer operator -> ()
			{
				return (&(*base));
			};

			TurnedIterator& operator -- ()
			{
				base++;
				return (*this);
			};

			TurnedIterator& operator ++ ()
			{
				base--;
				return (*this);
			};

			TurnedIterator operator -- (int)
			{
	 			TurnedIterator b = *this;

				base++;
				return (b);
			};

			TurnedIterator operator ++ (int)
			{
				TurnedIterator b = *this;

				base--;
				return (b);
			};

		TurnedIterator operator + (diff_type n)
		{
			TurnedIterator b;

			b.base = base - n;
			return (b);
		};

		TurnedIterator operator - (diff_type n)
		{
			TurnedIterator b;

			b.base = base + n;
			return (b);
		};

		diff_type operator - (TurnedIterator it)
		{
			return (it.base - base);
		};

		void operator += (diff_type n)
		{
			base -= n;
		};

		void operator -= (diff_type n)
		{
			base += n;
		};

		value& operator [] (diff_type n)
		{
			return (base[n]);
		};

		bool operator > (const TurnedIterator& it) const
		{
			return (base < it.base);
		};

		bool operator >= (const TurnedIterator& it) const
		{
			return (base <= it.base);
		};


		bool operator < (const TurnedIterator& it) const
		{
			return (base > it.base);
		};

		bool operator <= (const TurnedIterator& it) const
		{
			return (base >= it.base);
		};

		protected:
			Iterator base;
	};
};

#endif