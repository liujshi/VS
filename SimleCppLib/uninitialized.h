#ifndef UNITIALIZED_H
#define UNITIALIZED_H

#include "Construct.h"
#include "TypeTraits.h"
#include "Algorithm.h"
namespace LSTL{



	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x){
		return _unitialized_fill_n(first, n, x, value_type(first));
	}

	template <class ForwardIterator,class Size,class T,class T1>
	inline ForwardIterator _unitialized_fill_n(ForwardIterator first, Size n, const T&x, T1 *)
	{
		typedef typename  _type_traits<T1>::is_POD_type is_POD;
		return _unitialized_fill_n_aux(first, n, x, is_POD());
	}

	template <class ForwardIterator, class Size, class T>
	inline ForwardIterator
		_unitialized_fill_n_aux(ForwardIterator first, Size n, const T&x, _true_type)
	{
			return fill_n(first, n, x);
	}
	template <class ForwardIterator,class Size,class T>
	ForwardIterator
		_unitialized_fill_n_aux(ForwardIterator first, Size n, const T&x, _false_type)
	{
			ForwardIterator cur = first;
			for (; , n > 0; --n, ++cur)
				construct(&*cur, x);
			return cur;
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	
	template<class InputIterator, class ForwardIterator>
	ForwardIterator
		uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
	{
			return _unitialized_copy(first, last, result, value_type(result));
		}

	template<class InputIterator,class ForwardIterator, class T>
	inline ForwardIterator
		_unitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*){
			typedef typename _type_traits<T>::is_POD_type is_POD;
			return _unitialized_copy_aux(first, last, result, is_POD());
		}
	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator
		_unitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type)
	{
			return copy(first, last, result);
		}

	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator
		_unitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type)
	{
			ForwardIterator cur = result;
			for (; , first!=last; ++first, ++cur)
				construct(&*cur, *first);
			return cur;
		}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	template <class ForwardIterator, class T>
	inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T&x)
	{
		_uninitialized_fill(first, last, x, value_type(first));
	}
	template <class ForwardIterator, class T, class T1>
	inline void _uninitialized_fill(ForwardIterator first, ForwardIterator last, const T&x, T1*)
	{
		typedef typename _type_traits<T1>::is_POD_type is_POD;
		_uninitialized_fill_aux(first, last, x, is_POD());
	}

	template <class ForwardIterator,class T>
	inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T&x, _true_type)
	{
		fill(first, last, x);
	}

	template <class ForwardIterator,class T>
	inline void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T&x, _false_type)
	{
		for (; cur != last; ++cur)
		{
			construct(&*cur, x);
		}
	}
}

#endif