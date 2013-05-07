/**
 * @file SttclCx11Semaphore.h
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

#ifndef STTCLCX11SEMAPHORE_H_
#define STTCLCX11SEMAPHORE_H_

#if defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <locale>

#include "../include/SttclTime.h"

namespace sttcl
{

namespace internal
{
namespace cx11_impl
{
class Cx11SemaphoreSurrogate {
     private:
         std::mutex condMutex;
         std::condition_variable condVar;
         int countValue;
     public:
         Cx11SemaphoreSurrogate(int v)
         : countValue(v)
         {
         }
         virtual ~Cx11SemaphoreSurrogate()
         {
         }
         void post(int count=1)
         {
             std::unique_lock<std::mutex> lock(condMutex);
             countValue+=count;
             if (countValue > 0)
             {
                 condVar.notify_all();
                 std::this_thread::yield();
             }
         }
         void wait(int count = 1)
         {
             std::unique_lock<std::mutex> lock(condMutex);
             countValue-= count;
             while (countValue < 0)
             {
                 condVar.wait(lock);
             }
         }
         template<typename T>
         bool try_wait(int count = 1, T duration = T())
         {
             std::unique_lock<std::mutex> lock(condMutex);
             countValue-= count;
             while (countValue < 0)
             {
                 std::cv_status status = condVar.wait_for(lock,duration);
            	 switch(status)
            	 {
                 case std::cv_status::no_timeout:
                     return true;
                 case std::cv_status::timeout:
                     countValue+= count;
                     return false;
            	 }
			 }
             return true;
         }
 };
/**
 * The C++ 11 standard default implementation for sttcl::SttclSemaphore<>.
 */
class SttclCx11Semaphore
{
public:
	typedef Cx11SemaphoreSurrogate NativeSemaphoreType;
	SttclCx11Semaphore(unsigned int initialCount);
	virtual ~SttclCx11Semaphore();

	void wait();
	bool try_wait(const TimeDuration<>& timeout);
	void post();

private:
	NativeSemaphoreType semaphore;
};

}
}
}
#endif
#endif /* STTCLCX11SEMAPHORE_H_ */
