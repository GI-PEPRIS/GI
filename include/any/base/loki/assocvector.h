/*!
 * The AnyBase package of PetroCOVERY Solution is a collection of native C++ classes that 
 * implement the fundamental algorithms & operations required to 
 * satisfy COMMON DEMANDS of other packages.
 *
 * Copyright (C) 2015 XIUJIE SHENG
 *
 * This library isn't a free software, so you cann't take the source code without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will not harm your computer or ongoing 
 * business if you illegally got it. 
 *
 * NOTE: 
 * AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
 * LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
 *
 * For more information, contact:
 *
 * China University of Geoseciences(Wuhan)
 * Resource Faculty
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYBASE_LOKI_ASSOCVECTOR_H__
#define __ANYBASE_LOKI_ASSOCVECTOR_H__

// Refer to STL definitions
#include "..\anystl.h"

// Modern C++: 
// Below are trick structs, classes or maroes based on generic programming ideas, namely template techniques.
// It includes how to report compiling error or warning, partial template initialization etc.
namespace AnyBase
{
	// Note:
	// This includes file which is benefited from the ideas of "Modern C++" written 
	// by Andrei Alexandrescu
    namespace Loki
    {
		/*!
		* \brief
		* Template class used to adapt an existing compare functor class in order to
		* satisfy with different funtion calling with varieties of parameters input
		**/
        template <class Value, class C>
        class AssocVectorCompare : public C
        {
            // Vector item being a pair 
            typedef std::pair<typename C::first_argument_type, Value> Data;

            // Compare functor for default vector-map items
            typedef typename C::first_argument_type first_argument_type;

        public:
			//
			// Constructors & Deconstructors
			//
			/*!
			* Default Ctr 
			**/
			AssocVectorCompare()
			{
			}
            
			/*!
			* Copy Ctr
			* Here C means a compare functor
			**/
			AssocVectorCompare(const C &src) : C(src)
			{
			}
            
			//
			// Indirect to STL compare functor specified against different occasions of parameter input
			// Note:
			// TRUE means unequal, FALSE means equal
			//
			/*!
			*
			**/
			bool operator()(const first_argument_type &lhs,  const first_argument_type &rhs) const
			{ 
				return C::operator()(lhs, rhs); 
			}
            
			/*!
			*
			**/
			bool operator()(const Data &lhs, const Data &rhs) const
			{ 
				return operator()(lhs.first, rhs.first); 
			}
            
			/*!
			*
			**/
			bool operator()(const Data &lhs, const first_argument_type &rhs) const
			{ 
				return operator()(lhs.first, rhs); 
			}
            
			/*!
			*
			**/
			bool operator()(const first_argument_type &lhs, const Data &rhs) const
			{ 
				return operator()(lhs, rhs.first); 
			}
        };

		/*!
		* \brief
		* An associative vector built as a syntactic drop-in replacement for std::map
		*
		* BEWARE: AssocVector doesn't respect all map's guarantees, the most important
		* being:
		* 1) iterators are invalidated by insert and erase operations
		* 2) the complexity of insert/erase is O(N) not O(log N)
		* 3) value_type is std::pair<K, V> not std::pair<const K, V>
		* 4) iterators are random
		**/
        template
        <
            class K, // Key
            class V, // Value
            class C = std::less<K>,  // Compare
            class A = std::allocator< std::pair<K, V> > // Allocator for "pair" elements
        >
        class AssocVector : private std::vector< std::pair<K, V>, A >, private AssocVectorCompare<V, C>
        {
            // Host vector defintion
            typedef std::vector<std::pair<K, V>, A> Base;

            // Compare functor for given vector items, namely, those self-pairs
            typedef AssocVectorCompare<V, C> MyCompare;

        public:
			// Pair item for this vector
			typedef K key_type;
			typedef V mapped_type;
			typedef typename Base::value_type value_type;
			typedef C key_compare;
			typedef A allocator_type;

			// A variant of declarations as a "qualified" std container
			typedef typename A::reference reference;
			typedef typename A::const_reference const_reference;
			typedef typename Base::iterator iterator;
			typedef typename Base::const_iterator const_iterator;
			typedef typename Base::size_type size_type;
			typedef typename Base::difference_type difference_type;
			typedef typename A::pointer pointer;
			typedef typename A::const_pointer const_pointer;
			typedef typename Base::reverse_iterator reverse_iterator;
			typedef typename Base::const_reverse_iterator const_reverse_iterator;

			/*!
			* \brief
			* Value compare funtor passed to key compare functor adapting outside compare class
			**/
			class value_compare : public std::binary_function<value_type, value_type, bool>, private key_compare
			{
				friend class AssocVector;

			protected:
				/*!
				* Ctr
				**/
				value_compare(key_compare pred) : key_compare(pred)
				{
				}

			public:
				/*!
				*
				**/
				bool operator()(const value_type &lhs, const value_type &rhs) const
				{ 
					 return key_compare::operator()(lhs.first, rhs.first); 
				}
			};

			//
			// Ctr & Dctr
			//
			/*!
			* 
			**/
			explicit AssocVector(const key_compare &comp = key_compare(), const A &alloc = A()) : Base(alloc), MyCompare(comp)
			{
			}
            
			/*!
			* Constrcut partial from other associated vector
			**/
			template <class InputIterator>
			AssocVector(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const A &alloc = A())
			: Base(first, last, alloc), MyCompare(comp)
			{
				MyCompare &me = *this;
				std::sort(begin(), end(), me);
			}
            
			/*!
			*
			**/
			AssocVector &operator = (const AssocVector& rhs)
			{ 
				AssocVector(rhs).swap(*this); 
				return *this;
			}

			//
			// iterators:
			// The following are here because MWCW gets 'using' wrong
			//
			/*!
			*
			**/
			iterator begin() 
			{ 
				return Base::begin(); 
			}

			/*!
			*
			**/
			const_iterator begin() const 
			{
				return Base::begin(); 
			}

			/*!
			*
			**/
			iterator end() 
			{ 
				return Base::end(); 
			}

			/*!
			*
			**/
			const_iterator end() const 
			{ 
				return Base::end(); 
			}

			/*!
			*
			**/
			reverse_iterator rbegin() 
			{ 
				return Base::rbegin(); 
			}

			/*!
			*
			**/
			const_reverse_iterator rbegin() const 
			{ 
				return Base::rbegin(); 
			}

			/*!
			*
			**/
			reverse_iterator rend() 
			{ 
				return Base::rend(); 
			}

			/*!
			*
			**/
			const_reverse_iterator rend() const 
			{ 
				return Base::rend(); 
			}
            
			//
			// capacity:
			//
			/*!
			*
			**/
			bool empty() const 
			{ 
				return Base::empty(); 
			}

			/*!
			*
			**/
			size_type size() const 
			{ 
				return Base::size(); 
			}

			/*!
			*
			**/
			size_type max_size() 
			{ 
				return Base::max_size(); 
			}

			 //
			 // 23.3.1.2 element access:
			 //
			 /*!
			*
			**/
			 mapped_type& operator[](const key_type &key)
			 { 
				 return insert(value_type(key, mapped_type())).first->second; 
			 }

			 /*!
			* modifiers:
			**/
			 std::pair<iterator, bool> insert(const value_type &val)
			 {
				 bool found = true;
				iterator i(lower_bound(val.first));

				 if(i == end() || this->operator()(val.first, i->first))
				 {
					  i = Base::insert(i, val);
					  found = false;
				 }
				 return std::make_pair(i, !found);
			 }

			 /*!
			*
			**/
			 iterator insert(iterator pos, const value_type &val)
			 {
				 if (pos != end() && this->operator()(*pos, val) && 
					  (pos == end() - 1 ||
						  !this->operator()(val, pos[1]) &&
							   this->operator()(pos[1], val)))
				 {
					  return Base::insert(pos, val);
				 }
				 return insert(val).first;
			 }
	       
			 /*!
			*
			**/
			 template <class InputIterator>
			 void insert(InputIterator first, InputIterator last)
			 { 
				 for(; first != last; ++first) 
				 {
					  insert(*first); 
				 }
			 }
	        
			 /*!
			*
			**/
			 void erase(iterator pos)
			 { 
				 Base::erase(pos); 
			 }

			 /*!
			*
			**/
			 size_type erase(const key_type &k)
			 {
				 iterator i(find(k));
				 if(i == end()) 
				 {
					  return 0;
				 }
				 erase(i);
				 return 1;
			 }

			 /*!
			*
			**/
			 void erase(iterator first, iterator last)
			 { 
				 Base::erase(first, last); 
			 }

			 /*!
			*
			**/
			 void swap(AssocVector &other)
			 {
				 using std::swap;
				 Base::swap(other);
				 MyCompare &me = *this;
				 MyCompare &rhs = other;
				 swap(me, rhs);
			 }
	        
			 /*!
			*
			**/
			 void clear()
			 { 
				 Base::clear(); 
			 }

			 /*!
			* observers:
			**/
			 key_compare key_comp() const
			 { 
				 return *this; 
			 }

			 /*!
			*
			**/
			 value_compare value_comp() const
			 {
				 const key_compare& comp = *this;
				 return value_compare(comp);
			 }

			 /*!
			* 23.3.1.3 map operations:
			**/
			 iterator find(const key_type &k)
			 {
				 iterator i(lower_bound(k));
				 if(i != end() && this->operator()(k, i->first))
				 {
					  i = end();
				 }
				 return i;
			 }

			 /*!
			*
			**/
			 const_iterator find(const key_type &k) const
			 {       
				 const_iterator i(lower_bound(k));
				 if(i != end() && this->operator()(k, i->first))
				 {
					  i = end();
				 }

				 return i;
			 }

			 /*!
			*
			**/
			 size_type count(const key_type& k) const
			 { 
				 return find(k) != end(); 
			 }

			 /*!
			*
			**/
			 iterator lower_bound(const key_type &k)
			 {
				 MyCompare &me = *this;
				 return std::lower_bound(begin(), end(), k, me);
			 }

			 /*!
			*
			**/
			 const_iterator lower_bound(const key_type &k) const
			 {
				 const MyCompare &me = *this;
				 return std::lower_bound(begin(), end(), k, me);
			 }

			 /*!
			*
			**/
			 iterator upper_bound(const key_type &k)
			 {
				 MyCompare &me = *this;
				 return std::upper_bound(begin(), end(), k, me);
			 }

			 /*!
			*
			**/
			 const_iterator upper_bound(const key_type &k) const
			 {
				 const MyCompare &me = *this;
				 return std::upper_bound(begin(), end(), k, me);
			 }

			 /*!
			*
			**/
			 std::pair<iterator, iterator> equal_range(const key_type &k)
			 {
				 MyCompare &me = *this;
				 return std::equal_range(begin(), end(), k, me);
			 }

			 /*!
			*
			**/
			 std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			 {
				 const MyCompare &me = *this;
				 return std::equal_range(begin(), end(), k, me);
			 }
	        
			 /*!
			*
			**/
			 friend bool operator == (const AssocVector &lhs, const AssocVector &rhs)
			 {
				 const Base &me = lhs;
				 return me == rhs;
			 } 
	        
			 /*!
			*
			**/
			 bool operator < (const AssocVector& rhs) const
			 {
				 const Base &me = *this;
				 const Base &yo = rhs;
				 return me < yo;
			 } 

			 /*!
			*
			**/
			 friend bool operator != (const AssocVector &lhs, const AssocVector &rhs)
			 { 
				 return !(lhs == rhs); 
			 }

			 /*!
			*
			**/
			 friend bool operator > (const AssocVector &lhs, const AssocVector &rhs)
			 { 
				 return rhs < lhs; 
			 }

			 /*!
			*
			**/
			 friend bool operator >= (const AssocVector &lhs, const AssocVector &rhs)
			 { 
				 return !(lhs < rhs); 
			 } 

			 /*!
			*
			**/
			 friend bool operator <= (const AssocVector &lhs, const AssocVector &rhs)
			 { 
				 return !(rhs < lhs); 
			 }
		};

		// specialized algorithms:
		template <class K, class V, class C, class A>
		void swap(AssocVector<K, V, C, A> &lhs, AssocVector<K, V, C, A> &rhs)
		{ 
			 lhs.swap(rhs); 
		}
	}
}
#endif
