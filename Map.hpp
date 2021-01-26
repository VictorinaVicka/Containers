/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:06:37 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/26 17:00:16 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "TurnedIterator.hpp"
# include "Utils.hpp"

namespace ft
{
	template <typename Key, typename T, typename Compare = Bit<Key> >
	class Map;

    template <typename Key, typename T, typename Compare = Bit<Key> >
	class MapIt
	{
	public:
        typedef Key key_type;
		typedef T mapped_type;
        typedef std::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
		typedef value_type *pointer;
		typedef value_type &reference;
		typedef	std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

	private:
		typedef typename Map<Key, T, Compare>::Node Node;
		typedef MapIt<Key, T, Compare> Self;
		Node *newNode;

	public:
		MapIt() {}
		MapIt(Node *node): newNode(node) {}
		MapIt(const Self &c): newNode(c.newNode) {}
		~MapIt() {}

		template <typename _Key, typename _T, typename _Compare>
		friend class Map;

		template <typename _Key, typename _T, typename _Compare>
		friend bool operator==(const MapIt<_Key, _T, _Compare> &lhs, const MapIt<_Key, _T, _Compare> &rhs);

		template <typename _Key, typename _T, typename _Compare>
		friend bool operator!=(const MapIt<_Key, _T, _Compare> &lhs, const MapIt<_Key, _T, _Compare> &rhs);

		Self &operator=(const Self &self)
		{
			newNode = self.newNode;
			return (*this);
		}

		Self &operator++()
		{
            if (newNode->more)
			{
                newNode = newNode->more;
                while (newNode->less)
                    newNode = newNode->less;
            }
            else
			{
                Node *tmp;
                do
				{
                    tmp = newNode;
                    newNode = newNode->source;
                } while(newNode && newNode->more == tmp);
            }
			return (*this);
		}

		Self operator++(int)
		{
			Self copy = *this;
            operator++();
			return (copy);
		}

		Self &operator--()
		{
            if (newNode->less)
			{
                newNode = newNode->less;
                while (newNode && newNode->more)
                    newNode = newNode->more;
            }
            else
			{
                Node *tmp;
                do
				{
                    tmp = newNode;
                    newNode = newNode->source;
                }
				while (newNode && newNode->less == tmp);
            }
			return (*this);
		}

		Self operator--(int)
		{
			Self copy = *this;
            operator--();
			return (copy);
		}

		reference operator*() const
		{
			return (newNode->data);
		}

		pointer operator->() const
		{
			return (&newNode->data);
		}
	};

	template <typename Key, typename T, typename Compare>
	bool operator==(const MapIt<Key, T, Compare> &lhs, const MapIt<Key, T, Compare> &rhs)
	{
		return (lhs.newNode == rhs.newNode);
	}

	template <typename Key, typename T, typename Compare>
	bool operator!=(const MapIt<Key, T, Compare> &lhs, const MapIt<Key, T, Compare> &rhs)
	{
		return !(lhs.newNode == rhs.newNode);
	}

    template <typename Key, typename T, typename Compare>
	class Map
	{
	public:
        typedef Key key_type;
		typedef T mapped_type;
        typedef std::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef MapIt<Key, T, Compare> iterator;
		typedef const MapIt<const Key, const T, Compare> const_iterator;
		typedef TurnedIterator<iterator> reverse_iterator;
		typedef const TurnedIterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;
	private:
		class Value
		{
		private:
			key_compare newKey;

		public:
			typedef bool result;
			typedef value_type first_argument;
			typedef value_type second_argument;
			template <typename _Key, typename _T, typename _Compare>
			friend class Map;

			Value(key_compare c): newKey(c) {}

			Value(const Value &val): newKey(val.newKey) {}

			~Value() {}

			Value &operator=(const Value &val)
			{
				newKey = val.newKey;
				return (*this);
			}

			bool operator()(value_type &x, value_type &y) const
			{
				return (newKey(x.first, y.first));
			}
		};

	private:
		typedef Map<Key, T, Compare> Self;
        struct Node
		{
			value_type data;
			Node *less; //<
			Node *more; //>
            Node *source;

			Node(Node *less_, Node *more_, Node *source_, value_type data_) :
				data(data_), less(less_), more(more_), source(source_) {};
		};
		size_type newSize;
		Node *center;
        Node *guard;
        key_compare newKey;
	public:

		//Member functions:

		Map(const key_compare &comp = key_compare()): newSize(0), newKey(comp)
		{
			center = new Node(NULL, NULL, NULL, value_type());
			guard = center;
		}

		template <typename InputIterator>
		Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare()): newSize(0), newKey(comp)
		{
			center = new Node(NULL, NULL, NULL, value_type());
			guard = center;
			insert(begin(), first, last);
		}

		Map(const Self &c): newSize(0), newKey(c.newKey)
		{
			center = new Node(NULL, NULL, NULL, value_type());
			guard = center;
			insert(begin(), c.begin(), c.end());
		}

		~Map()
		{
			clear();
			delete guard;
		}

		template <typename _Key, typename _T, typename _Compare>
		friend class Map;

		template <typename _Key, typename _T, typename _Compare>
		friend class MapIt;

		template <typename Iterator>
		friend class ReverseIterator;

		Self &operator=(const Map &c) {
			clear();
			newSize = 0;
			newKey = c.newKey;
			insert(begin(), c.begin(), c.end());
			return *this;
		}

		// Iterators:

		iterator begin()
		{
            Node *node = center;
            while (node && node->less)
                node = node->less;
			return (iterator(node));
		}

		const_iterator begin() const
		{
            Node *node = center;
            while (node && node->less)
                node = node->less;
			return (const_iterator(node));
		}

		iterator end()
		{
			return (iterator(guard));
		}

		const_iterator end() const
		{
			return (const_iterator(guard));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

        // Capacity:

		bool empty() const
		{
			return (newSize == 0);
		}

		size_type size() const
		{
			return (newSize);
		}

		size_type max_size() const
		{
			return (std::numeric_limits<std::size_t>::max() / sizeof(value_type));
		}

        // Element access:

        mapped_type &operator[](const key_type& k)
		{
            return (*((this->insert(std::make_pair(k,mapped_type()))).first)).second;
        }

        //Modifiers:

        std::pair<iterator, bool> insert(const value_type &val)
		{
            Node *node = center;

            while (1)
			{
				if (node == guard)
				{
					Node *source = guard->source;
					if (source)
					{
						source->more = new Node(NULL, guard, source, val);
						node = source->more;
					}
					else
					{
						center = new Node(NULL, guard, source, val);
						node = center;
					}
					guard->source = node;
					break ;
				}
                if (!newKey(node->data.first, val.first) && !newKey(val.first, node->data.first))
                    return (std::make_pair(iterator(node), false));
                if (newKey(node->data.first, val.first))
				{
                    if (node->more)
                        node = node->more;
                    else
					{
                        node->more = new Node(NULL, NULL, node, val);
                        node = node->more;
                        break ;
                    }
                }
                else if (newKey(val.first, node->data.first))
				{
                    if (node->less)
                        node = node->less;
                    else
					{
                        node->less = new Node(NULL, NULL, node, val);
                        node = node->less;
                        break ;
                    }
                }
            }
			newSize++;
            return (std::make_pair(iterator(node), true));
        }

        iterator insert(iterator position, const value_type &val)
		{
            (void)position;
            iterator it = insert(val).first;
            return (it);
        }

        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last)
		{
            for (; first != last; first++)
                insert(*first);
        }

		void erase(iterator position)
		{
			Node *node = position.newNode;
			if (node->source)
			{
				if (node->more)
				{
					if (node == node->source->more)
						node->source->more = node->more;
					else
						node->source->less = node->more;
					node->more->source = node->source;
					if (node->less)
					{
						Node *tmp = node->more;
						while (tmp->less)
							tmp = tmp->less;
						tmp->less = node->less;
						node->less->source = tmp;
					}
				}
				else if (node->less)
				{
					if (node == node->source->more)
						node->source->more = node->less;
					else
						node->source->less = node->less;
					node->less->source = node->source;
				}
				else
				{
					if (node == node->source->more)
						node->source->more = NULL;
					else
						node->source->less = NULL;
				}
			}
			else
			{
				if (node->more)
				{
					center = node->more;
					node->more->source = NULL;
					if (node->less)
					{
						Node *tmp = node->more;
						while (tmp->less)
							tmp = tmp->less;
						tmp->less = node->less;
						node->less->source = tmp;
					}
				}
				else if (node->less)
				{
					center = node->less;
					node->less->source = NULL;
				}
				else
					center = guard;
			}
			newSize--;
			delete node;
		}

		size_type erase(const key_type &k)
		{
			iterator it = begin();
			for(; (*it).first != k; it++)
			{}
			if (it != end())
			{
				erase(it);
				return (1);
			}
			return (0);
		}

		void erase(iterator first, iterator last)
		{
			for (; first != last;)
			{
				iterator it = first;
				first++;
				erase(it);
			}
		}

		void swap(Map &x)
		{
			std::swap(center, x.center);
			std::swap(guard, x.guard);
			std::swap(newSize, x.newSize);
		}

		void clear()
		{
			erase(begin(), end());
			guard->more = NULL;
			guard->less = NULL;
			guard->source = NULL;
			center = guard;
			newSize = 0;
		}

		//Observers:

		key_compare key_comp() const
		{
			return (newKey);
		}

		Value value_comp() const
		{
			Value compare(newKey);
			return (compare);
		}

		//Operations:

		iterator find(const key_type &k)
		{
			Node *node = center;
			while (node && node != guard)
			{
				bool tst = newKey(node->data.first, k);
				if (!tst && !newKey(k, node->data.first))
					return (iterator(node));
				if (!tst)
					node = node->less;
				else
					node = node->more;
			}
			return (end());
		}

		const_iterator find(const key_type &k) const
		{
			Node *node = center;
			while (node && node != guard)
			{
				bool tst = newKey(node->data.first, k);
				if (!tst && !newKey(k, node->data.first))
					return const_iterator(node);
				if (!tst)
					node = node->less;
				else
					node = node->more;
			}
			return (end());
		}

		size_type count(const key_type &k) const
		{
			Node *node = center;

			while (node && node != guard)
			{
				bool tst = newKey(node->data.first, k);
				if (!tst && !newKey(k, node->data.first))
					return (1);
				if (!tst)
					node = node->less;
				else
					node = node->more;
			}
			return (0);
		}

		iterator lower_bound(const key_type &k)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (!newKey((*it).first, k))
					return (it);
			}
			return (end());
		}

		const_iterator lower_bound(const key_type &k) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (!newKey((*it).first, k))
					return (it);
			}
			return (end());
		}

		iterator upper_bound(const key_type &k)
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (newKey(k, (*it).first))
					return (it);
			}
			return (end());
		}

		const_iterator upper_bound(const key_type &k) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (newKey(k, (*it).first))
					return (it);
			}
			return (end());
		}

		std::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (std::make_pair(lower_bound(k), upper_bound(k)));
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (std::make_pair(lower_bound(k), upper_bound(k)));
		}
    };
};

#endif