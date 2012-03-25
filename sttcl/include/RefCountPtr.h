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
{
public:
	/**
	 * The signature of a release function.
	 * @param ptr The pointee to release (delete).
	 */
	typedef void (*ReleaseFunc)(T* ptr);

private:
	struct PtrRef
	{
		T* pointee;
		int refcount;
		MutexType refcountMutex;
		ReleaseFunc releaseFunc;

		PtrRef(T* argPointee, ReleaseFunc argReleaseFunc)
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

public:

	/**
	 * Default constructor for class RefCountPtr.
	 */
	RefCountPtr()
	: ptrRef(0)
	{
	}

	/**
	 * Constructor for class RefCountPtr.
	 * @param argPointee The pointee to manage.
	 * @param argReleaseFunc An optional alternate release function for the pointee.
	 */
	RefCountPtr(T* argPointee, ReleaseFunc argReleaseFunc = RefCountPtr<T,MutexType>::release)
	: ptrRef(0)
	{
		if(argPointee)
		{
			ptrRef = new PtrRef(argPointee,argReleaseFunc);
			incrementRefCount();
		}
	}
	/**
	 * Copy constructor for class RefCountPtr. This operation will increment the reference
	 * count of the copied pointee.
	 * @param rhs The other instance to copy from.
	 */
	RefCountPtr(const RefCountPtr<T,MutexType>& rhs)
	: ptrRef(rhs.ptrRef)
	{
		incrementRefCount();
	}
	/**
	 * Destructor for class RefCountPtr. This operation will decrement the reference count
	 * of the managed pointee.
	 */
	~RefCountPtr()
	{
		decrementRefCount();
	}

	/**
	 * Assignment operator. This operation will increment the reference count of the copied
	 * pointee.
	 * @param rhs The other instance to copy from.
	 * @return A reference to this instance.
	 */
	RefCountPtr& operator=(const RefCountPtr& rhs)
	{
		if(ptrRef && ptrRef != rhs.ptrRef)
		{
			decrementRefCount();
		}
		ptrRef = rhs.ptrRef;
		incrementRefCount();
		return *this;
	}

	/**
	 * Gets the pointee.
	 * @return The pointee.
	 */
	T* get() const
	{
		if(ptrRef)
		{
			return ptrRef->pointee;
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
		if(ptrRef)
		{
			return ptrRef->pointee;
		}
		return 0;
	}

	/**
	 * Star dereference operator.
	 * @return A reference to the pointee if available.
	 */
	template<typename U>
	U& operator*()
	{
		static U dummy;
		if(ptrRef)
		{
			return *reinterpret_cast<U*>(ptrRef->pointee);
		}
		return dummy;
	}

private:
	void incrementRefCount();
	void decrementRefCount();
	static void release(T* ptr);
	PtrRef* ptrRef;
};

template
< typename T
, class MutexType
>
void RefCountPtr<T,MutexType>::incrementRefCount()
{
	if(ptrRef)
	{
		sttcl::internal::AutoLocker<MutexType> lock(ptrRef->refcountMutex);
		++(ptrRef->refcount);
	}
}

template
< typename T
, class MutexType
>
void RefCountPtr<T,MutexType>::decrementRefCount()
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

template
< typename T
, class MutexType
>
void RefCountPtr<T,MutexType>::release(T* ptr)
{
	delete ptr;
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
