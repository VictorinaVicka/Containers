/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:20:37 by tfarenga          #+#    #+#             */
/*   Updated: 2021/01/25 14:56:08 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <sstream>
# include "TurnedIterator.hpp"

namespace ft
{
	template <typename T>
	class Vector;

    template <typename T>
	class	VectorIt
	{
	public:
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef	std::ptrdiff_t difference_type;
        typedef size_t size_type;
		typedef std::random_access_iterator_tag iterator_category;

	private:
		typedef VectorIt<T> Self;
        pointer pr;
	public:
		VectorIt(): pr(NULL) {}
		VectorIt(pointer elem): pr(elem) {}
		VectorIt(const VectorIt<T> &vector): pr(vector.pr) {}
		~VectorIt() {}

		template <typename _T>
		friend class Vector;

		template <typename _T>
		friend bool operator==(const VectorIt<_T> &lhs, const VectorIt<_T> &rhs);

		template <typename _T>
		friend bool operator!=(const VectorIt<_T> &lhs, const VectorIt<_T> &rhs);

        template <typename _T>
	    friend ptrdiff_t operator-(const VectorIt<_T> &lhs, const VectorIt<_T> &rhs);

		Self &operator=(const Self &self)
		{
			pr = self.pr;
			return *this;
		}

		Self &operator++()
		{
			++pr;
			return *this;
		}

		Self operator++(int)
		{
			Self copy = *this;
			++pr;
			return copy;
		}

		Self &operator--()
		{
            --pr;
			return *this;
		}

		Self operator--(int)
		{
			Self copy = *this;
			--pr;
			return copy;
		}

        Self &operator+=(size_type offset)
		{
            pr += offset;
            return *this;
        }

        Self &operator-=(size_type offset)
		{
            pr -= offset;
            return *this;
        }

		reference operator*() const
		{
			return *pr;
		}

		pointer operator->() const
		{
			return pr;
		}

        reference operator[](size_type n)
		{
            return *(*this + n);
        }
	};

    template <typename T>
	bool operator==(const VectorIt<T> &lhs, const VectorIt<T> &rhs)
	{
		return lhs.pr == rhs.pr;
	}

	template <typename T>
	bool operator!=(const VectorIt<T> &lhs, const VectorIt<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const VectorIt<T> &lhs, const VectorIt<T> &rhs)
	{
		return lhs.pr < rhs.pr;
	}

	template <typename T>
	bool operator>(const VectorIt<T> &lhs, const VectorIt<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator<=(const VectorIt<T> &lhs, const VectorIt<T> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T>
	bool operator>=(const VectorIt<T> &lhs, const VectorIt<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	VectorIt<T> operator+(const VectorIt<T> &it, size_t offset)
	{
		VectorIt<T> it2 = it;
		return it2 += offset;
	}

	template <typename T>
	VectorIt<T> operator+(typename VectorIt<T>::difference_type offset, const VectorIt<T> &it)
	{
		return it + offset;
	}

	template <typename T>
	VectorIt<T> operator-(const VectorIt<T> &it, typename VectorIt<T>::difference_type offset)
	{
		VectorIt<T> it2 = it;
		return it2 -= offset;
	}

	template <typename T>
	ptrdiff_t operator-(const VectorIt<T> &lhs, const VectorIt<T> &rhs)
	{
		return lhs.pr - rhs.pr;
	}

    template <typename T>
	class	Vector {
	public:
		typedef T value_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef VectorIt<T> iterator;
		typedef const VectorIt<const T> const_iterator;
		typedef TurnedIterator<iterator> reverse_iterator;
		typedef const TurnedIterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		typedef Vector<T> Self;

		size_type newSize;
        size_type newType;
        pointer array;

	public:

		//Member functions:

		Vector(): newSize(0), newType(0), array(NULL)
		{}

		Vector(size_type n, const value_type &val = value_type()): newSize(0), newType(0), array(NULL)
		{
			insert(begin(), n, val);
		}

		template <typename InputIterator>
		Vector(InputIterator first, InputIterator last): newSize(0), newType(0), array(NULL)
		{
			insert(begin(), first, last);
		}

		Vector(const Self &c): newSize(0), newType(0), array(NULL)
		{
			insert(begin(), c.begin(), c.end());
		}

		~Vector()
		{
            std::allocator<T> alloc;
            for (size_type i = 0; i < newSize; i++)
			{
                alloc.destroy(&array[i]);
            }
            alloc.deallocate(array, newType);
		}

		template <typename _T>
		friend class Vector;

		template <typename _T>
		friend class VectorIt;

		template <typename Iterator>
		friend class TurnedIterator;

		Self &operator=(const Vector &x)
		{
			clear();
			insert(begin(), x.begin(), x.end());
			return *this;
		}

		// Iterators:

		iterator begin()
		{
			return array;
		}

		const_iterator begin() const
		{
			return array;
		}

		iterator end()
		{
			return array + newSize;
		}

		const_iterator end() const
		{
			return array + newSize;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

        // Capacity:

        size_type size() const
		{
            return newSize;
        }

		size_type max_size() const
		{
			return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
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
            return newType;
        }

        bool empty() const
		{
			return newSize == 0;
		}

		void reserve(size_type n)
		{
			if (n <= newType)
				return ;
			if (!n)
				return ;
			std::allocator<T> alloc;
			T *new_array = alloc.allocate(n);
			for (size_type i = 0; i < newSize; i++)
			{
				alloc.construct(&new_array[i], array[i]);
				alloc.destroy(&array[i]);
			}
			alloc.deallocate(array, newType);
			array = new_array;
			newType = n;
		}

        // Element access:

        reference operator[](size_type n)
		{
            return array[n];
        }

        const_reference operator[](size_type n) const
		{
            return array[n];
        }

        reference at(size_type n)
		{
            if (n >= newSize)
			{
                std::stringstream str;
                str << "index " << n << " out of bound (size() is " << size() << ");";
                throw std::out_of_range(str.str());
            }
            return array[n];
        }

        const_reference at(size_type n) const
		{
            if (n >= newSize)
			{
                std::stringstream str;
                str << "index " << n << " out of bound (size() is " << size() << ");";
                throw std::out_of_range(str.str());
            }
            return array[n];
        }

        reference front()
		{
            return array[0];
        }

        const_reference front() const
		{
            return array[0];
        }

        reference back()
		{
            return array[newSize - 1];
        }

        const_reference back() const
		{
            return array[newSize - 1];
        }

        // Modifiers:

        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
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
			erase(end() - 1);
        }

        iterator insert(iterator position, const value_type &val)
		{
            insert(position, (size_type)1, val);
            return position;
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
            if (!n)
                return ;
            std::allocator<T> alloc;
            size_type ix = position.pr - array;
            reserve(newSize + n);
            for (ptrdiff_t i = newSize - 1; i >= (ptrdiff_t)ix; i--)
			{
                alloc.construct(&array[i + n], array[i]);
                alloc.destroy(&array[i]);
            }
            for (size_type i = ix; i < ix + n; i++)
			{
                alloc.construct(&array[i], val);
            }
            newSize += n;
		}

		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
            if (first == last)
                return ;
            std::allocator<T> alloc;
            size_type ix = position.pr - array;
            size_type count = last - first;
            reserve(newSize + count);
            for (ptrdiff_t i = newSize - 1; i >= (ptrdiff_t)ix; i--)
			{
                alloc.construct(&array[i + count], array[i]);
                alloc.destroy(&array[i]);
            }
            for (InputIterator it = first; it != last; it++)
			{
                alloc.construct(&array[ix++], *it);
            }
            newSize += count;
		}

		iterator erase(iterator position)
		{
            return erase(position, position + 1);
		}

		iterator erase(iterator first, iterator last)
		{
			size_type count = last - first;
			if (count <= 0)
				return last;
			size_type ix = first.pr - array;

			std::allocator<T> alloc;
			for (size_type i = ix; i < ix + count; i++)
				alloc.destroy(&array[i]);
			for (size_type i = ix + count; i < newSize; i++)
			{
				alloc.construct(&array[i - count], array[i]);
				alloc.destroy(&array[i]);
			}
			newSize -= count;
			return first;
		}

        void swap(Vector &x)
		{
			std::swap(array, x.array);
			std::swap(newSize, x.newSize);
			std::swap(newType, x.newType);

        }

        void clear()
		{
            erase(begin(), end());
        }

    };

	// Non-member function overloads:

	template <typename T>
	bool operator==(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T>
	bool operator!= (const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	bool operator<=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T>
	bool operator>(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator>=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	void swap (Vector<T> &x, Vector<T> &y)
	{
		return x.swap(y);
	}
}

#endif