#ifndef ALGORIGHM_H
#define ALGORIGHM_H
#include "TypeTraits.h"
#include "allocator.h"
#include "Iterator.h"
namespace LSTL{
	template <class ForwardIterator,class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}
	inline void fill(char *first, char *last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}
	inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}

	///////////////////////////////////////////////////////

	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
	template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	/////////////////////////////////////////////////////////////////

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		_distance(InputIterator first, InputIterator last, input_iterator_tag){
			typename iterator_traits<InputIterator>::difference_type dist = 0;
			while (first++ != last){
				++dist;
			}
			return dist;
		}
	template<class RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
		_distance(RandomIterator first, RandomIterator last, random_access_iterator_tag){
			auto dist = last - first;
			return dist;
		}
	template<class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last){
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			return _distance(first, last, iterator_category());
		}

	/////////////////////////////////////////////////////////////////


	namespace {
		template<class InputIterator, class Distance>
		void _advance(InputIterator& it, Distance n, input_iterator_tag){
			assert(n >= 0);
			while (n--){
				++it;
			}
		}
		template<class BidirectionIterator, class Distance>
		void _advance(BidirectionIterator& it, Distance n, bidirectional_iterator_tag){
			if (n < 0){
				while (n++){
					--it;
				}
			}
			else{
				while (n--){
					++it;
				}
			}
		}
		template<class RandomIterator, class Distance>
		void _advance(RandomIterator& it, Distance n, random_access_iterator_tag){
			if (n < 0){
				it -= (-n);
			}
			else{
				it += n;
			}
		}
	}
	template <class InputIterator, class Distance>
	void advance(InputIterator& it, Distance n){
		typedef iterator_traits<InputIterator>::iterator_category iterator_category;
		_advance(it, n, iterator_category());
	}



	////////////////////////////////////////////////////////////////
	template<class InputIterator, class OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _true_type){
		auto dist = distance(first, last);
		memcpy(result, first, sizeof(*first) * dist);
		advance(result, dist);
		return result;
	}
	template<class InputIterator, class OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _false_type){
		while (first != last){
			*result = *first;
			++result;
			++first;
		}
		return result;
	}
	template<class InputIterator, class OutputIterator, class T>
	OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, T*){
		typedef typename LSTL::_type_traits<T>::is_POD_type is_pod;
		return __copy(first, last, result, is_pod());
	}
	template <class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result){
		return _copy(first, last, result, value_type(first));
	}
	template<>
	inline char *copy(char *first, char *last, char *result){
		auto dist = last - first;
		memcpy(result, first, sizeof(*first) * dist);
		return result + dist;
	}
	template<>
	inline wchar_t *copy(wchar_t *first, wchar_t *last, wchar_t *result){
		auto dist = last - first;
		memcpy(result, first, sizeof(*first) * dist);
		return result + dist;
	}
	//////////////////////////////////////////////////////////////////////////////
	////////////////////////copy_backward////////////////////////////////////////


	template <class _BidirectionalIter1, class _BidirectionalIter2,class _Distance>
	inline _BidirectionalIter2 __copy_backward(_BidirectionalIter1 __first,
		_BidirectionalIter1 __last,
		_BidirectionalIter2 __result,
		bidirectional_iterator_tag,
		_Distance*)
	{
			while (__first != __last)
				*--__result = *--__last;
			return __result;
		}

	template <class _RandomAccessIter, class _BidirectionalIter, class _Distance>
	inline _BidirectionalIter __copy_backward(_RandomAccessIter __first,
		_RandomAccessIter __last,
		_BidirectionalIter __result,
		random_access_iterator_tag,
		_Distance*)
	{
		for (_Distance __n = __last - __first; __n > 0; --__n)
			*--__result = *--__last;
		return __result;
	}


	template <class _BidirectionalIter1, class _BidirectionalIter2,class _BoolType>
	struct __copy_backward_dispatch
	{
		typedef typename iterator_traits<_BidirectionalIter1>::iterator_category
		_Cat;
		typedef typename iterator_traits<_BidirectionalIter1>::difference_type
			_Distance;

		static _BidirectionalIter2 copy(_BidirectionalIter1 __first,
			_BidirectionalIter1 __last,
			_BidirectionalIter2 __result) {
			return __copy_backward(__first, __last, __result, _Cat(), (_Distance*)0);
		}
	};
	template <class _Tp>
	struct __copy_backward_dispatch<_Tp*, _Tp*, _true_type>
	{
		static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) {
			const ptrdiff_t _Num = __last - __first;
			memmove(__result - _Num, __first, sizeof(_Tp)* _Num);
			return __result - _Num;
		}
	};

	template <class _Tp>
	struct __copy_backward_dispatch<const _Tp*, _Tp*, _true_type>
	{
		static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) {
			return  __copy_backward_dispatch<_Tp*, _Tp*, _true_type>
				::copy(__first, __last, __result);
		}
	};

	template <class _Tp>
	struct __copy_backward_dispatch<_Tp*, _Tp*, _false_type>
	{
		static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) {
			return __copy_backward(__first, __last, __result,iterator_category(__first),difference_type(__first));
		}
	};

	template <class _Tp>
	struct __copy_backward_dispatch<const _Tp*, _Tp*, _false_type>
	{
		static _Tp* copy(const _Tp* __first, const _Tp* __last, _Tp* __result) {
			return  __copy_backward_dispatch<_Tp*, _Tp*, _false_type>
				::copy(__first, __last, __result);
		}
	};
	
	template <class _BI1, class _BI2>
	inline _BI2 copy_backward(_BI1 __first, _BI1 __last, _BI2 __result) {

		typedef typename _type_traits<typename iterator_traits<_BI2>::value_type>
			::has_trivial_assignment_operator
			_Trivial;
		return __copy_backward_dispatch<_BI1, _BI2, _Trivial>
			::copy(__first, __last, __result);
	}

	/*template <class _BI1, class _BI2>
	inline _BI2 copy_backward(_BI1 __first, _BI1 __last, _BI2 __result) {
		return __copy_backward(__first, __last, __result,
			iterator_category(__first),
			difference_type(__first));
	}*/
}
#endif