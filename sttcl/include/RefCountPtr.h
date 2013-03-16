/**
 * @file RefCountPtr.h
 *
 * Copyright (c) 2012, Guenther Makulik All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 * 3) Neither the name STTCL nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef REFCOUNTPTR_H_
#define REFCOUNTPTR_H_

#include "SttclMutex.h"
#include <stdlib.h>

namespace sttcl
{

namespace internal
{
template<class MutexType>
class RefCountPtrBase
{
public:
	/**
	 * The signature of a release function.
	 * @param ptr The pointee to release (delete).
	 */
	typedef void (*ReleaseFunc)(void* ptr);

	/**
	 * Destructor for class RefCountPtrBase. This operation will decrement the reference count
	 * of the managed pointee.
	 */
	~RefCountPtrBase()
	{
		decrementRefCount();
	}


protected:

	struct PtrRef
	{
		void* pointee;
		int refcount;
		MutexType refcountMutex;
		ReleaseFunc releaseFunc;

		PtrRef(void* argPointee, ReleaseFunc argReleaseFunc)
		: pointee(argPointee)
		, refcount(0)
		, refcountMutex()
		, releaseFunc(argReleaseFunc)
		{
		}

		~PtrRef()
		{
		}
	};

	/**
	 * Default constructor for class RefCountPtrBase.
	 */
	RefCountPtrBase()
	: ptrRef(0)
	{
	}

	/**
	 * Default constructor for class RefCountPtrBase.
	 */
	RefCountPtrBase(void* argPointee, ReleaseFunc argReleaseFunc)
	: ptrRef(0)
	{
		if(argPointee)
		{
			ptrRef = new PtrRef(argPointee,argReleaseFunc);
			incrementRefCount();
		}
	}

	/**
	 * Copy constructor for class RefCountPtrBase.
	 * @param rhs The other instance to copy from.
	 */
	RefCountPtrBase(const RefCountPtrBase& rhs)
	: ptrRef(rhs.ptrRef)
	{
		incrementRefCount();
	}

	/**
	 * Assignment operator for RefCountPtrBase.
	 * @param rhs The other instance to copy from.
	 * @return A reference to this instance.
	 */
	RefCountPtrBase& operator=(const RefCountPtrBase<MutexType>& rhs)
	{
		if(ptrRef && ptrRef != rhs.ptrRef)
		{
			decrementRefCount();
		}
		ptrRef = rhs.ptrRef;
		incrementRefCount();
		return *this;
	}

	void incrementRefCount();
	void decrementRefCount();

	mutable PtrRef* ptrRef;
};

template
< class MutexType
>
void RefCountPtrBase<MutexType>::incrementRefCount()
{
	if(ptrRef)
	{
		sttcl::internal::AutoLocker<MutexType> lock(ptrRef->refcountMutex);
		++(ptrRef->refcount);
	}
}

template
< class MutexType
>
void RefCountPtrBase<MutexType>::decrementRefCount()
{
	if(ptrRef)
	{
		bool destroy = false;
		{ sttcl::internal::AutoLocker<MutexType> lock(ptrRef->refcountMutex);
			--(ptrRef->refcount);
			if(ptrRef->refcount <= 0)
			{
				if(ptrRef->releaseFunc)
				{
					(*ptrRef->releaseFunc)(ptrRef->pointee);
					ptrRef->pointee = 0;
				}
				destroy = true;
			}
		}
		if(destroy)
		{
			delete ptrRef;
			ptrRef = 0;
		}
	}
}
}

/**
 * Represents a smart pointer class for STTCL dispatched event arguments.
 * The implementation provides a simple reference counting smart pointer.
 * There's also a specialization for \em T as void, but it will never be really used
 * with void pointees, since void event argument types won't be instantiated in the
 * event dispatch interfaces.
 * @tparam T The event arguments type.
 * @tparam MutexType The mutex type used to guarantee thread safety of the RefCountPtr instances.
 */
template
< typename T
, class MutexType = internal::SttclMutex<STTCL_DEFAULT_MUTEXIMPL>
>
class RefCountPtr
: public sttcl::internal::RefCountPtrBase<MutexType>
{
public:

	/**
	 * Default constructor for class RefCountPtr.
	 */
	RefCountPtr()
	: sttcl::internal::RefCountPtrBase<MutexType>()
	{
	}

	/**
	 * Constructor for class RefCountPtr.
	 * @param argPointee The pointee to manage.
	 * @param argReleaseFunc An optional alternate release function for the pointee.
	 */
	RefCountPtr(T* argPointee, typename sttcl::internal::RefCountPtrBase<MutexType>::ReleaseFunc argReleaseFunc = RefCountPtr<T,MutexType>::release)
	: sttcl::internal::RefCountPtrBase<MutexType>(argPointee,argReleaseFunc)
	{
	}

	/**
	 * Copy constructor for class RefCountPtr. This operation will increment the reference
	 * count of the copied pointee.
	 * @param rhs The other instance to copy from.
	 */
	RefCountPtr(const RefCountPtr<T,MutexType>& rhs)
	: sttcl::internal::RefCountPtrBase<MutexType>(rhs)
	{
	}

	/**
	 * Copy constructor for class RefCountPtr. This operation will increment the reference
	 * count of the copied pointee.
	 * @param rhs The other instance to copy from.
	 */
	template<typename U>
	RefCountPtr(const RefCountPtr<U,MutexType>& rhs)
	: sttcl::internal::RefCountPtrBase<MutexType>(rhs)
	//: ptrRef(static_cast<const RefCountPtr<T,MutexType>::PtrRef*>(rhs.ptrRef))
	//: ptrRef(rhs.ptrRef)
	{
	}

	/**
	 * Destructor for class RefCountPtr. This operation will decrement the reference count
	 * of the managed pointee.
	 */
	~RefCountPtr()
	{
	}

	/**
	 * Assignment operator. This operation will increment the reference count of the copied
	 * pointee.
	 * @param rhs The other instance to copy from.
	 * @return A reference to this instance.
	 */
	RefCountPtr& operator=(const RefCountPtr<T,MutexType>& rhs)
	{
		sttcl::internal::RefCountPtrBase<MutexType>::operator=(rhs);
		return *this;
	}

	/**
	 * Assignment operator. This operation will increment the reference count of the copied
	 * pointee.
	 * @param rhs The other instance to copy from.
	 * @return A reference to this instance.
	 */
	template<typename U>
	RefCountPtr& operator=(const RefCountPtr<U,MutexType>& rhs)
	{
		sttcl::internal::RefCountPtrBase<MutexType>::operator=(rhs);
		return *this;
	}

	/**
	 * Gets the pointee.
	 * @return The pointee.
	 */
	T* get() const
	{
		if(sttcl::internal::RefCountPtrBase<MutexType>::ptrRef)
		{
			return sttcl::internal::RefCountPtrBase<MutexType>::ptrRef->pointee;
		}
		return 0;
	}

	/**
	 * Gets the pointee.
	 */
	operator T*() const
	{
		return get();
	}

	/**
	 * Arrow derefernce operator.
	 * @return The pointee if available.
	 */
	T* operator->()
	{
		if(sttcl::internal::RefCountPtrBase<MutexType>::ptrRef)
		{
			return reinterpret_cast<T*>(sttcl::internal::RefCountPtrBase<MutexType>::ptrRef->pointee);
		}
		return 0;
	}

	/**
	 * Star dereference operator.
	 * @return A reference to the pointee if available.
	 */
	T& operator*()
	{
		static T dummy;
		if(sttcl::internal::RefCountPtrBase<MutexType>::ptrRef)
		{
			return *(reinterpret_cast<T*>(sttcl::internal::RefCountPtrBase<MutexType>::ptrRef->pointee));
		}
		return dummy;
	}

private:
	static void release(void* ptr);
};

template
< typename T
, class MutexType
>
void RefCountPtr<T,MutexType>::release(void* ptr)
{
	delete reinterpret_cast<T*>(ptr);
}

/**
 * Specializes RefCountPtr for void.
 */
template<class MutexType>
class RefCountPtr<void,MutexType>
{
	static void release(void* ptr)
	{
//		free(ptr);
	}
};

} /* namespace sttcl */
#endif /* REFCOUNTPTR_H_ */
