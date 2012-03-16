/**
 * @file SttclCx11Semaphore.cpp
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

#include "../SttclCx11Semaphore.h"

#if defined(STTCL_CX11_THREADS) or defined(STTCL_CX11_IMPL)
using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::cx11_impl;
using namespace boost::posix_time;
using sttcl::internal::cx11_impl::SttclCx11Semaphore;

SttclCx11Semaphore::SttclCx11Semaphore(unsigned int initialCount)
: semaphore(initialCount)
{
}

SttclCx11Semaphore::~SttclCx11Semaphore()
{
}

void SttclCx11Semaphore::wait()
{
	semaphore.wait();
}

bool SttclCx11Semaphore::try_wait(const TimeDuration<>& timeout)
{
	if(timeout == TimeDuration<>::Zero)
	{
		return semaphore.try_wait();
	}

	boost::posix_time::ptime absTime = boost::posix_time::microsec_clock::universal_time() + timeout.getNativeValue();
	return semaphore.timed_wait(absTime);
}

void SttclCx11Semaphore::post()
{
	semaphore.post();
}
#endif
