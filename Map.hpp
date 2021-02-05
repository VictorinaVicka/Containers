/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:11:09 by tfarenga          #+#    #+#             */
/*   Updated: 2021/02/03 14:28:35 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <limits>
# include <functional>
# include "Map_Iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class Map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef std::less<key_type> key_compare;
		typedef Alloc allocator_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef	T *pointer;
		typedef	const T *const_pointer;
		typedef ft::MapIt<Key, T> iterator;
		typedef ft::ConstMapIt<Key, T> const_iterator;
		typedef ft::ReverseMapIt<Key, T> reverse_iterator;
		typedef ft::ConstReverseMapIt<Key, T> const_reverse_iterator;
		typedef typename ft::MapIt<Key, T>::difference_type	difference_type;
		typedef size_t size_type;

	class compareVal
	{
  	friend class map;
	protected:
  		Compare com;
  		compareVal (Compare c) : com(c) {}

	public:
		typedef bool result;
		typedef value_type firstArg;
		typedef value_type secondArg;

		bool operator() (const value_type& lhs, const value_type& rhs) const
		{
			return com(lhs.first, rhs.first);
		}
	};

	private:
		MapThree<Key, T> *origin;
		MapThree<Key, T> *_begin;
		MapThree<Key, T> *finish;
		allocator_type alloc;
		key_compare newKey;
		size_type len;

		void	turnLeft(MapThree<Key, T> *lhs, MapThree<Key, T> *rhs)
		{
			if (!lhs->parent)
				this->origin = rhs;
			else if (lhs->parent->right == lhs)
				lhs->parent->right = rhs;
			else if (lhs->parent->left == lhs)
				lhs->parent->left = rhs;
			rhs->parent = lhs->parent;
			lhs->parent = rhs;
			if (rhs->left)
				rhs->left->parent = lhs;
			lhs->right = rhs->left;
			rhs->left = lhs;
			if (lhs->right)
			{
				heightLen(lhs->right);
			}
			else
				lhs->newRight = 0;
				heightLen(lhs);
		}

		void	toRight(MapThree<Key, T> *lhs, MapThree<Key, T> *rhs)
		{
			if (!rhs->parent)
				this->origin = lhs;
			else if (rhs->parent->right == rhs)
				rhs->parent->right = lhs;
			else if (rhs->parent->left == rhs)
				rhs->parent->left = lhs;
			lhs->parent = rhs->parent;
			rhs->parent = lhs;
			if (lhs->right)
				lhs->right->parent = rhs;
			rhs->left = lhs->right;
			lhs->right = rhs;
			if (!rhs->left)
			{
				rhs->newLeft = 0;
				heightLen(rhs);
			}
			else
				heightLen(rhs->left);
		}

		void	heightLen(MapThree<Key, T> *branch)
		{
			MapThree<Key, T> *origin;

			origin = (branch) ? branch->parent : NULL;
			while (origin)
			{
				if (origin->left == branch)
					origin->newLeft = std::max<int>(branch->newLeft, branch->newRight) + 1;
				else if (origin->right == branch)
					origin->newRight = std::max<int>(branch->newLeft, branch->newRight) + 1;
				branch = origin;
				origin = branch->parent;
			}
		}

		void	turnLeftRight(MapThree<Key, T> *lhs, MapThree<Key, T> *rhs, MapThree<Key, T> *z)
		{
			turnLeft(rhs, lhs);
			toRight(lhs, z);
		}

		void	turnRightLeft(MapThree<Key, T> *lhs, MapThree<Key, T> *rhs, MapThree<Key, T> *z)
		{
			toRight(lhs, rhs);
			turnLeft(z, lhs);
		}

		void	balance(MapThree<Key, T> *branch, int type)
		{
			MapThree<Key, T> *start;
			MapThree<Key, T> *grCh;
			MapThree<Key, T> *origin;
			int factor;

			start = branch;
			heightLen(branch);
			grCh = branch;
			origin = (branch && branch->parent) ? branch->parent : branch;
			while (origin)
			{
				factor = static_cast<int>(origin->newLeft - origin->newRight);
				if (factor > 1 || factor < -1)
				{
					rebalance(factor, grCh, type);
					balance(branch, type);
				}
				grCh = branch;
				branch = origin;
				origin = branch->parent;
			}
			heightLen(start);
			factor = static_cast<int>(this->origin->newLeft - this->origin->newRight);
			if (factor > 1 || factor < -1)
				balance(start, type);
		}

		void	rebalance(int factor1, MapThree<Key, T> *branch, int type)
		{
			if (type == 0)
			{
				if (factor1 < 1)
				{
					if (branch == branch->parent->right)
						turnLeft(branch->parent, branch);
					else if (branch == branch->parent->left)
						turnRightLeft(branch, branch->parent, branch->parent->parent);
				}
				else if (factor1 > 1)
				{
					if (branch == branch->parent->left)
						toRight(branch, branch->parent);
					else if (branch == branch->parent->right)
						turnLeftRight(branch, branch->parent, branch->parent->parent);
				}
			}
			else if (type == 1)
			{
				int factor2;

				if (factor1 < -1)
				{
					factor2 = static_cast<int>(branch->right->newLeft - branch->right->newRight);
					if (factor2 <= 0)
						turnLeft(branch, branch->right);
					else
						turnRightLeft(branch->right, branch, branch->parent);
				}
				else if (factor1 > 1)
				{
					factor2 = static_cast<int>(branch->left->newLeft - branch->left->newRight);
					if (factor2 >= 0)
						toRight(branch->left, branch);
					else
						turnLeftRight(branch->left, branch, branch->parent);
				}
			}
		}

		void	delnewMap(MapThree<Key, T> *newMap)
		{
			MapThree<Key, T> *child;
			MapThree<Key, T> *newBalance;

			if ((!newMap->left || newMap->left == this->_begin) && (!newMap->right || newMap->right == this->finish))
			{
				if (newMap->parent && newMap->parent->left == newMap)
				{
					if (newMap->left == this->_begin)
						newMap->parent->left = this->_begin;
					else
						newMap->parent->left = NULL;
				}
				else if (newMap->parent && newMap->parent->right == newMap)
				{
					if (newMap->right == this->finish)
						newMap->parent->right = this->finish;
					else
						newMap->parent->right = NULL;
				}
				else
				{
					this->origin = this->finish;
					this->origin->left = this->_begin;
					this->_begin->parent = this->origin;
				}
				newBalance = newMap->parent;
				delete (newMap);
			}
			else if (newMap->left && newMap->left != this->_begin && newMap->right && newMap->right != this->finish)
			{
				MapThree<Key, T> *child2;

				newBalance = NULL;
				child = newMap->left;
				while (child->right && child->right != this->finish)
					child = child->right;
				child2 = new MapThree<Key, T>();
				child2->parent = newMap->parent;
				child2->left = newMap->left;
				child2->right = newMap->right;
				child2->newLeft = newMap->newLeft;
				child2->newRight = newMap->newRight;
				newMap->parent = child->parent;
				newMap->left = child->left;
				newMap->right = child->right;
				newMap->newLeft = child->newLeft;
				newMap->newRight = child->newRight;
				if (newMap->left)
					newMap->left->parent = newMap;
				if (newMap->right)
					newMap->right->parent = newMap;
				if (newMap->parent == newMap)
				{
					newMap->parent = child;
					newMap->parent->left = newMap;
				}
				else if (newMap->parent->left == child)
					newMap->parent->left = newMap;
				else if (newMap->parent->right == child)
					newMap->parent->right = newMap;
				child->parent = child2->parent;
				if (!child->parent)
					this->origin = child;
				else if (child->parent->left == newMap)
					child->parent->left = child;
				else if (child->parent->right == newMap)
					child->parent->right = child;
				child->left = child2->left;
				child->right = child2->right;
				child->newLeft = child2->newLeft;
				child->newRight = child2->newRight;
				if (child->left == child)
					child->left = newMap;
				else if (child->right == child)
					child->right = newMap;
				if (child->left)
					child->left->parent = child;
				if (child->right)
					child->right->parent = child;
				delete(child2);
				delnewMap(newMap);
			}
			else
			{
				child = (newMap->left && newMap->left != this->_begin) ? newMap->left : newMap->right;
				child->parent = newMap->parent;
				if (!child->parent)
					this->origin = child;
				else if (child->parent->left == newMap)
					child->parent->left = child;
				else if (child->parent->right == newMap)
					child->parent->right = child;
				newBalance = (child->parent) ? child->parent : child;
				heightLen(child);
				if (newMap->left == this->_begin)
					child->left = this->_begin;
				delete(newMap);
			}
			if (newBalance)
				balance(newBalance, 1);
		}

	public:

	// Member functions:

		explicit Map(const key_compare &newKey = key_compare(), const allocator_type &alloc = allocator_type())
		{
			this->newKey = newKey;
			this->alloc = alloc;
			_begin = new MapThree<Key, T>();
			_begin->left = NULL;
			_begin->right = NULL;
			finish = new MapThree<Key, T>();
			finish->left = _begin;
			_begin->parent = finish;
			finish->right = NULL;
			finish->parent = NULL;
			origin = finish;
			len = 0;
			return ;
		}

		Map(const Map &copy)
		{
			_begin = new MapThree<Key, T>();
			_begin->left = NULL;
			_begin->right = NULL;
			finish = new MapThree<Key, T>();
			finish->left = _begin;
			_begin->parent = finish;
			finish->right = NULL;
			finish->parent = NULL;
			origin = finish;
			len = 0;
			*this = copy;
			return ;
		}

		Map &operator=(const Map &target)
		{
			clear();
			newKey = target.newKey;
			alloc = target.alloc;
			insert(target.begin(), target.end());
			return (*this);
		}

		~Map()
		{
			clear();
			delete(finish);
			delete(_begin);
			return ;
		}

		template <class InputIterator>
		Map(InputIterator first, InputIterator last, const key_compare &newKey = key_compare(), const allocator_type &alloc = allocator_type())
		{
			this->newKey = newKey;
			this->alloc = alloc;
			_begin = new MapThree<Key, T>();
			_begin->left = NULL;
			_begin->right = NULL;
			finish = new MapThree<Key, T>();
			finish->left = _begin;
			_begin->parent = finish;
			finish->right = NULL;
			finish->parent = NULL;
			origin = finish;
			len = 0;
			insert(first, last);
		}

		// Iterators:

		iterator begin()
		{
			MapThree<Key, T> *newMap;

			newMap = origin;
			while (newMap->left && newMap->left != _begin)
				newMap = newMap->left;
			return (iterator(newMap));
		}

		const_iterator begin() const
		{
			MapThree<Key, T> *newMap;

			newMap = origin;
			while (newMap->left && newMap->left != _begin)
				newMap = newMap->left;
			return (const_iterator(newMap));
		}

     	iterator end()
		{
			return (iterator(finish));
		}

		const_iterator end() const
		{
			return (const_iterator(finish));
		}

		reverse_iterator rbegin()
		{
			MapThree<Key, T> *newMap;

			newMap = origin;
			while (newMap->right && newMap->right != finish)
				newMap = newMap->right;
			return (reverse_iterator(newMap));
		}

		const_reverse_iterator	rbegin() const
		{
			MapThree<Key, T> *newMap;

			newMap = origin;
			while (newMap->right && newMap->right != finish)
				newMap = newMap->right;
			return (const_reverse_iterator(newMap));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(_begin));
		}

		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(_begin));
		}

		// Capacity:

		bool empty() const
		{
			return (!len);
		}

		size_type  size() const
		{
			return (len);
		}

		size_type max_size() const
		{
			return (std::numeric_limits<size_type>::max()/sizeof(origin));
		}

		// Element access:

		mapped_type &operator[](const key_type &k)
		{
			MapThree<Key, T> *newMap;

			newMap = origin;
			while (newMap && newMap != finish && newMap != _begin)
			{
				if (k == newMap->two.first)
					return (newMap->two.second);
				if (newKey(k, newMap->two.first))
				{
					if (newMap->left)
						newMap = newMap->left;
					else
						insert(iterator(newMap), value_type(k, 0));
				}
				else
				{
					if (newMap->right)
						newMap = newMap->right;
					else
						insert(iterator(newMap), value_type(k, 0));
				}
			}
			insert(value_type(k, 0));
			return (origin->two.second);
		}

		// Modifiers:

		std::pair<iterator, bool> insert(const value_type &val)
		{
			MapThree<Key, T> *newMap;
			MapThree<Key, T> *newnewMap;

			newnewMap = new MapThree<Key, T>();
			newnewMap->parent = NULL;
			newnewMap->left = NULL;
			newnewMap->right = NULL;
			newnewMap->two = val;
			newnewMap->newLeft = 0;
			newnewMap->newRight = 0;
			if (origin != finish)
			{
				newMap = origin;
				while (!newnewMap->parent)
				{
					if (newnewMap->two.first == newMap->two.first)
					{
						delete(newnewMap);
						return (std::pair<iterator, bool>(iterator(newMap), false));
					}
					if (newKey(newnewMap->two.first, newMap->two.first))
					{
						if (newMap->left && newMap->left != _begin)
							newMap = newMap->left;
						else
						{
							if (newMap->left == _begin)
								_begin->parent = newnewMap;
							newMap->left = newnewMap;
							newnewMap->parent = newMap;
							if (_begin->parent == newnewMap)
								newnewMap->left = _begin;
						}
					}
					else
					{
						if (newMap->right && newMap->right != finish)
							newMap = newMap->right;	
						else
						{
							if (newMap->right == finish)
								finish->parent = newnewMap;
							newMap->right = newnewMap;
							newnewMap->parent = newMap;
							if (finish->parent == newnewMap)
								newnewMap->right = finish;
						}
					}
				}
			}
			else
			{
				origin = newnewMap;
				origin->right = finish;
				origin->left = _begin;
				finish->parent = origin;
				finish->left = NULL;
				finish->right = NULL;
				_begin->parent = origin;
			}
			balance(newnewMap, 0);
			len++;
			return (std::pair<iterator, bool>(iterator(newnewMap), true));
		}

		iterator insert(iterator position, const value_type &val)
		{
			MapThree<Key, T> *newMap;
			MapThree<Key, T> *newnewMap;
			iterator it;

			it = find(val.first);
			if (it != this->end())
				return (it);
			newnewMap = new MapThree<Key, T>();
			newnewMap->parent = NULL;
			newnewMap->left = NULL;
			newnewMap->right = NULL;
			newnewMap->two = val;
			newnewMap->newLeft = 0;
			newnewMap->newRight = 0;
			if (this->origin != this->finish)
			{
				newMap = position.getMap();
				while (!newnewMap->parent)
				{
					if (newMap == this->finish || newMap == this->_begin)
						newMap = this->origin;
					if (this->newKey(newnewMap->two.first, newMap->two.first))
					{
						if (newMap->left && newMap->left != this->_begin)
							newMap = newMap->left;
						else
						{
							if (newMap->left == this->_begin)
								this->_begin->parent = newnewMap;
							newMap->left = newnewMap;
							newnewMap->parent = newMap;
							if (this->_begin->parent == newnewMap)
								newnewMap->left = this->_begin;
						}
					}
					else
					{
						if (newMap->right && newMap->right != this->finish)
							newMap = newMap->right;
						else
						{
							if (newMap->right == this->finish)
								this->finish->parent = newnewMap;
							newMap->right = newnewMap;
							newnewMap->parent = newMap;
							if (this->finish->parent == newnewMap)
								newnewMap->right = this->finish;
						}
					}
				}
			}
			else
			{
				this->origin = newnewMap;
				this->origin->right = this->finish;
				this->origin->left = this->_begin;
				this->finish->parent = this->origin;
				this->finish->left = NULL;
				this->finish->right = NULL;
				this->_begin->parent = this->origin;
			}
			this->balance(newnewMap, 0);
			this->len++;
			return (iterator(newnewMap));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase(iterator position)
		{
			delnewMap(position.getMap());
			this->len--;
		}

		size_type erase(const key_type &k)
		{
			MapThree<Key, T> *newMap;

			newMap = this->origin;
			while (newMap && newMap != this->finish && newMap != this->_begin)
			{
				if (k == newMap->two.first)
				{
					erase(iterator(newMap));
					return (1);
				}
				if (this->newKey(k, newMap->two.first))
					newMap = newMap->left;
				else
					newMap = newMap->right;
			}
			return (0);
		}

		void erase(iterator first, iterator last)
		{
			iterator next;

			while (first != last)
			{
				next = first;
				next++;
				erase(first);
				first = next;
			}
		}

		void swap(Map &lhs)
		{
			MapThree <Key, T> *tmp;
			size_type len;

			tmp = origin;
			origin = lhs.origin;
			lhs.origin = tmp;
			tmp = finish;
			finish = lhs.finish;
			lhs.finish = tmp;
			tmp = _begin;
			_begin = lhs._begin;
			lhs._begin = tmp;
			len = this->len;
			this->len = lhs.len;
			lhs.len = len;
		}

		void clear()
		{
			erase(begin(), end());
		}

		// Observers:

		key_compare key_comp() const
		{
			return (newKey);
		}

		compareVal value_comp() const
		{
			return (this->compareVal);
		}

		// Operations:

		iterator find(const key_type &k)
		{
			MapThree <Key, T>	*newMap;

			newMap = origin;
			while (newMap && newMap != finish && newMap != _begin)
			{
				if (k == newMap->two.first)
					return (iterator(newMap));
				if (newKey(k, newMap->two.first))
					newMap = newMap->left;
				else
					newMap = newMap->right;
			}
			return (end());
		}

		const_iterator find(const key_type &k) const
		{
			MapThree <Key, T>	*newMap;

			newMap = origin;
			while (newMap && newMap != finish && newMap != _begin)
			{
				if (k == newMap->two.first)
					return (const_iterator(newMap));
				if (newKey(k, newMap->two.first))
					newMap = newMap->left;
				else
					newMap = newMap->right;
			}
			return (end());
		}

		size_type count(const key_type &k) const
		{
			return ((find(k) == end()));
		}

		iterator lower_bound(const key_type &k)
		{
			iterator it;
			iterator it2;

			it = begin();
			it2 = end();
			while (it != it2)
			{
				if (key_comp()((*it).first, k) <= 0)
					return (iterator(it));
				++it;
			}
			return (end());
		}

		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator it;
			const_iterator it2;

			it = begin();
			it2 = end();
			while (it != it2)
			{
				if (key_comp()((*it).first, k) <= 0)
					return (const_iterator(it));
				++it;
			}
			return (end());
		}

		iterator upper_bound(const key_type &k)
		{
			iterator it;
			iterator it2;

			it = begin();
			it2 = end();
			while (it != it2)
			{
				if (((*it).first == k))
					return (iterator(++it));
				if (key_comp()((*it).first, k) <= 0)
					return (iterator(it));
				++it;
			}
			return (end());
		}

		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator it;
			const_iterator it2;

			it = begin();
			it2 = end();
			while (it != it2)
			{
				if (((*it).first == k))
					return (iterator(++it));
				if (key_comp()((*it).first, k) <= 0)
					return (iterator(it));
				++it;
			}
			return (end());
		}

		std::pair<const_iterator,const_iterator> equal_range(const key_type &k) const
		{
			return (std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}

		std::pair<iterator,iterator> equal_range(const key_type &k)
		{
			return (std::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}

	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::Map<Key, T, Compare, Alloc> &lhs, const ft::Map<Key, T, Compare, Alloc> &rhs)
	{
		typename Map<Key, T, Compare, Alloc>::const_iterator it;
		size_t i;

		it = lhs.begin();
		if (lhs.size() != rhs.size())
			return (false);
		i = 0;
		while (i < lhs.size())
		{
			typename Map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.find(it->first);
			if (it2 == rhs.end())
				return (false);
			if (it2->first != it->first || it2->second != it->second)
				return (false);
			it++;
			i++;
		}
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::Map<Key, T, Compare, Alloc> &lhs, const ft::Map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::Map<Key, T, Compare, Alloc> &lhs, const ft::Map<Key, T, Compare, Alloc> &rhs)
	{
		typename Map<Key, T, Compare, Alloc>::const_iterator	it;
		size_t n;
		size_t i;

		it = rhs.begin();
		if (lhs.size() > rhs.size())
			n = rhs.size();
		else
		{
			it = lhs.begin();
			n = lhs.size();
		}
		i = 0;
		while (i < n)
		{
			if (lhs.size() > rhs.size())
			{
				typename Map<Key, T, Compare, Alloc>::const_iterator it2 = lhs.find(it->first);
				if (it2 == lhs.end())
					return (true);
				if (it->first != it2->first)
					return (it2->first < it->first);
				if (it->second != it2->second)
					return (it2->second < it->second);
			}
			else
			{
				typename Map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.find(it->first);
				if (it2 == rhs.end())
					return (false);
				if (it->first != it2->first)
					return (it->first < it2->first);
				if (it->second != it2->second)
					return (it->second < it2->second);
			}
			it++;
			i++;
		}
		return (lhs.size() < rhs.size());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::Map<Key, T, Compare, Alloc> &lhs, const ft::Map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::Map<Key, T, Compare, Alloc> &lhs, const ft::Map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs) && !(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::Map<Key, T, Compare, Alloc> &lhs, const ft::Map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::Map<Key, T, Compare, Alloc> &lhs, ft::Map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
};

#endif