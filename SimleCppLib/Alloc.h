#ifndef ALLOC_H
#define ALLOC_H


#if 0
#include <new>
#define __THROW_BAD_ALLOC throw bad_alloc

#elif !defined(__THROW_BAD_ALLOC)

#include <iostream>
#define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl; exit(1)
#endif

#include <cstdlib>

namespace LSTL{

	class __malloc_alloc_template{
	private:
		static void *oom_malloc(size_t);
		static void *oom_realloc(void *, size_t);
		static void(*__malloc_alloc_oom_handler)();

	public:

		static void *allocate(size_t n)
		{
			void *reuslt = oom_malloc(n);
		}

		static void deallocate(void *p)
		{
			free(p);
		}
		static void *reallocate(void *p, size_t new_sz){
			void *result = realloc(p, new_sz);
			if (0 == result)
				result = oom_realloc(p, new_sz);
			return result;
		}

		static void(*set_malloc_handler(void(*f)()))(){
			void(*old)() = __malloc_alloc_oom_handler;
			__malloc_alloc_oom_handler = f;
			return old;
		}
	};

	
	typedef __malloc_alloc_template malloc_alloc;


//////////////////////////////////////////////////////////////////////////////////////////


	class __default_alloc_template{

	private:
		enum LALIGN { __ALIGN__ = 8};
		enum LMAX_BYTES { __MAX_BYTES__ = 128 };
		enum LNFREE_LISTS { __NFREELISTS__ = (LMAX_BYTES::__MAX_BYTES__ / LALIGN::__ALIGN__) };

	private:

		union obj
		{
			union obj * next;
			char client_data[1];
		};
		static obj * free_list[LNFREE_LISTS::__NFREELISTS__];

	private:
		static size_t ROUND_UP(size_t bytes){
			return (((bytes)+LALIGN::__ALIGN__ - 1) & ~(LALIGN::__ALIGN__ - 1));
		}

		//根据区块大小，决定使用第n号free-list，n从0开始计算
		static size_t FREELIST_INDEX(size_t bytes){
			return (((bytes)+LALIGN::__ALIGN__ - 1) / LALIGN::__ALIGN__ - 1);
		}

	private:
		static void *refill(size_t n);
		static char *chunk_alloc(size_t size, size_t &nobjs);
		static char *start_free;//内存池起始位置
		static char *end_free;//内存池结束位置
		static size_t heap_size;//

	public:
		static void *allocate(size_t bytes);
		static void deallocate(void *ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
	};
	typedef __default_alloc_template alloc;
}

#endif