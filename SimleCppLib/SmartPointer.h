#ifndef SMART_POINTER_H
#define SMART_POINTER_H

namespace LSTL
{
	template<typename T>
	class SPtr{
		template<typename T1>
		friend class SPtr;
	private:
		T *pointer;
		size_t *count;

	public:
		SPtr()
		{
			pointer = 0;
			count = 0;
		}
		SPtr(T *ptr) :pointer(0), count(0)
		{
			this->operator=(ptr);
		}
		template<typename T1>
		SPtr(T1 * ptr)
			: pointer(0), count(0)
		{
			this->operator=(ptr);
		}

		SPtr(const SPtr<T> & ptr) :
			: pointer(0), count(0)
		{
			this->operator=(ptr);
		}
		template<typename T1>
		SPtr(const SPtr<T1> & ptr) :
			: pointer(0), count(0)
		{
			this->operator=(ptr);
		}
		SPtr(SPtr<T> &&ptr) :
			: pointer(0), count(0)
		{
			this->pointer = (static_cast<SPtr<T> &&>(ptr));
		}


		bool operator == (const T * ptr) const
		{
			return pointer == ptr;
		}
		bool operator != (const T * ptr) const
		{
			return pointer != ptr;
		}
		bool operator == (const SPtr<T> & ptr) const
		{
			return pointer == ptr.pointer;
		}
		bool operator != (const SPtr<T> & ptr) const
		{
			return pointer != ptr.pointer;
		}

		T* operator +(int offset) const
		{
			return pointer + offset;
		}
		T& operator [](int idx) const
		{
			return *(pointer + idx);
		}
		T &operator *() const
		{
			return *pointer;
		}
		T&operator->()const
		{
			return pointer;
		}
		operator void*() const
		{
			if (pointer)
				return (void*)(pointer);
			else
				return 0;
		}
		T * Ptr() const
		{
			return pointer;
		}
		
		T* Release()
		{
			if (pointer)
			{
				if ((*count) > 1)
				{
					(*count)--;
				}
				else
				{
					delete count;
				}
			}
			auto rs = pointer;
			count = 0;
			pointer = 0;
			return rs;
		}

		~SPtr()
		{
			Dereferance();
		}
		void Dereferance()
		{
			if (pointer)
			{
				if ((*count) > 1)
				{
					(*count)--;
				}
				else{
					delete pointer;
					delete count;
				}
			}
		}

		SPtr<T>& operator=(T *ptr)
		{
			Dereferance();
			pointer = ptr;
			if (ptr)
			{
				count = new size_t;
				(*count) = 1;
			}
			else
				count = 0;
			return *this;
		}
		template<typename T1>
		SPtr<T> & operator=(T1 *ptr)
		{
			Dereferance();
			pointer = dynamic_cast<T *>(ptr);
			if (ptr)
			{
				count = new size_t;
				*count = 1;
			}
			else
				count = 0;
			return *this;
		}

		SPtr<T>& operator=(const SPtr<T> &ptr)
		{
			if (this->pointer != ptr.pointer)
			{
				Dereferance();
				this->pointer = ptr.pointer;
				this->count = ptr.count;
				if (count)
				{
					(*count)++;
				}
			}
			return *this;
		}
		template<typename T1>
		SPtr<T> & operator=(const SPtr<T1>&ptr)
		{
			if (this->pointer != ptr.pointer)
			{
				Dereferance();
				this->pointer = dynamic_cast<T *>(ptr.pointer);
				this->count = ptr.count;
				if (count)
				{
					(*count)++;
				}
			}
			return *this;
		}
		SPtr<T> & operator=(SPtr<T>&&ptr)
		{
			if (this->pointer != ptr.pointer)
			{
				Dereferance();
				pointer = ptr.pointer;
				count = ptr.count;
				ptr.pointer = 0;
				ptr.count = 0;
			}
			return *this;
		}
	};
}

#endif