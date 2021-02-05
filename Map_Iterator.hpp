/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map_Iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:38:59 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/03 14:27:06 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "Start.hpp"
# include <iostream>

namespace ft
{
	template <class Key, class T>
	struct MapThree
	{
		MapThree *parent;
		MapThree *left;
		MapThree *right;
		size_t newLeft;
		size_t newRight;
		std::pair<Key,T> two;
	};

	template <class Key, class T, class Compare = ft::bidirectional_tag>
	class MapIt
	{
	private:
		MapIt operator+(const MapIt &target) const;
		MapIt operator+(int n) const;
		MapIt operator-(const MapIt &target) const;
		MapIt operator-(int n) const;
		MapIt &operator+=(int n) const;
		MapIt &operator-=(int n) const;
		T &operator[](int n) const;
		bool operator<(const MapIt &target) const;
		bool operator>(const MapIt &target) const;
		bool operator<=(const MapIt &target) const;
		bool operator>=(const MapIt &target) const;

	protected:
		MapThree<Key, T> *map;

	public:
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;
		typedef Compare compare;
		typedef std::ptrdiff_t difference_type;

		MapIt() {}

		MapIt(const MapIt &copy)
		{
			*this = copy;
		}

		MapIt &operator=(const MapIt &target)
		{
			map = target.map;
			return (*this);
		}

		~MapIt() {}

		MapIt(MapThree<Key, T> *map)
		{
			this->map = map;
		}

		MapIt &operator++()
		{
			MapThree<Key, T> *newMap;

			if (!map)
				return (*this);
			if (map->right)
			{
				newMap = map->right;
				while (newMap->left)
					newMap = newMap->left;
			}
			else
			{
				newMap = map;
				while (newMap->parent && newMap == newMap->parent->right)
					newMap = newMap->parent;
				newMap = newMap->parent;
			}
			map = newMap;
			return (*this);
		}

		MapIt operator++(int)
		{
			MapIt tmp(*this);
			operator++();
			return (tmp);
		}

		MapIt &operator--()
		{
			MapThree<Key, T> *newMap;

			if (map->left)
			{
				newMap = map->left;
				while (newMap->right)
					newMap = newMap->right;
			}
			else
			{
				newMap = map;
				while (newMap->parent && newMap == newMap->parent->left)
					newMap = newMap->parent;
				newMap = newMap->parent;
			}
			map = newMap;
			return (*this);
		}

		MapIt operator--(int)
		{
			MapIt tmp(*this);
			operator--();
			return (tmp);
		}

  		bool operator==(const MapIt &target) const
		{
			return (map == target.map);
		}

  		bool operator!=(const MapIt &target) const
		{
			return (map != target.map);
		}

		std::pair<Key, T> &operator*()
		{
			return (map->two);
		}

		std::pair<Key, T> *operator->()
		{
			return (&map->two);
		}

		MapThree<Key, T> *getMap()
		{
			return (map);
		}
	};

	template <class Key, class T>
	class ReverseMapIt : public MapIt<Key, T>
	{
	public:
		ReverseMapIt() {}

		ReverseMapIt(MapThree<Key, T> *map)
		{
			this->map = map;
		}

		ReverseMapIt(const ReverseMapIt &copy)
		{
			*this = copy;
		}

		ReverseMapIt &operator=(const ReverseMapIt &target)
		{
			this->map = target.map;
			return (*this);
		}

		ReverseMapIt &operator++()
		{
			MapThree<Key, T> *newMap;

			if (this->map->left)
			{
				newMap = this->map->left;
				while (newMap->right)
					newMap = newMap->right;
			}
			else
			{
				newMap = this->map;
				while (newMap->parent && newMap == newMap->parent->left)
					newMap = newMap->parent;
				newMap = newMap->parent;
			}
			this->map = newMap;
			return (*this);
		}

		ReverseMapIt operator++(int)
		{
			ReverseMapIt tmp(*this);
			operator++();
			return (tmp);
		}

		ReverseMapIt &operator--()
		{
			MapThree<Key, T> *newMap;

			if (!this->map->right)
			{
				newMap = this->map->right;
				while (newMap->left)
					newMap = newMap->left;
			}
			else
			{
				newMap = this->map;
				while (newMap->parent && newMap == newMap->parent->right)
					newMap = newMap->parent;
				newMap = newMap->parent;
			}
			this->map = newMap;
			return (*this);
		}

		ReverseMapIt operator--(int)
		{
			ReverseMapIt tmp(*this);
			operator--();
			return (tmp);
		}

		~ReverseMapIt() {}
	};

	template <class Key, class T>
	class ConstMapIt : public MapIt<Key, T>
	{
	public:
		ConstMapIt(void) {}
		~ConstMapIt(void) {}

		ConstMapIt(MapThree<Key, T> *map)
		{
			this->map = map;
		}

		ConstMapIt(const ConstMapIt &copy)
		{
			*this = copy;
		}

		ConstMapIt &operator=(const ConstMapIt &target)
		{
			this->map = target.map;
			return (*this);
		}

		const std::pair<Key, T> &operator*(void)
		{
			return (this->map->two);
		}
	};

	template <class Key, class T>
	class ConstReverseMapIt : public ReverseMapIt<Key, T>
	{
	public:
		ConstReverseMapIt() {}

		ConstReverseMapIt(MapThree<Key, T> *map)
		{
			this->map = map;
		}

		ConstReverseMapIt(const ConstReverseMapIt &copy)
		{
			*this = copy;
		}

		ConstReverseMapIt &operator=(const ConstReverseMapIt &target)
		{
			this->map = target.map;
			return (*this);
		}

		~ConstReverseMapIt() {}

		const std::pair<Key, T> &operator*(void)
		{
			return (this->map->two);
		}
	};
};

#endif