/*
 * @file SttclPosixTime.cpp
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
#include "../SttclPosixTime.h"
#if defined(STTCL_POSIX_TIME) or defined(STTCL_POSIX_IMPL)

using namespace sttcl;
using namespace sttcl::internal;
using namespace sttcl::internal::posix_impl;

using sttcl::internal::posix_impl::SttclPosixTimeDuration;

void SttclPosixTimeDuration::setNative(unsigned int argHours, unsigned int argMinutes, unsigned int argSeconds, unsigned int argMilliSeconds, unsigned long argMicroSeconds, unsigned long argNanoSeconds)
{
	td.tv_sec = (argHours * 3600) + (argMinutes * 60) + argSeconds;
	td.tv_nsec = (argMilliSeconds * 1000000) + (argMicroSeconds * 1000) + argNanoSeconds;
	normalizeNative();
}

void SttclPosixTimeDuration::add(const NativeTimeDuration& nativeTimeDuration)
{
    td.tv_sec += nativeTimeDuration.tv_sec;
    td.tv_nsec += nativeTimeDuration.tv_nsec;
    normalizeNative();
}

void SttclPosixTimeDuration::substract(const NativeTimeDuration& nativeTimeDuration)
{
    td.tv_sec -= nativeTimeDuration.tv_sec;
    td.tv_nsec -= nativeTimeDuration.tv_nsec;
    normalizeNative();
}

void SttclPosixTimeDuration::multiply(int factor)
{
    td.tv_sec *= factor;
    td.tv_nsec *= factor;
    normalizeNative();
}

void SttclPosixTimeDuration::divide(int divider)
{
	if(divider != 0)
	{
	    td.tv_sec /= divider;
	    td.tv_nsec /= divider;
	    normalizeNative();
	}
}

void SttclPosixTimeDuration::normalizeNative()
{
	// Eliminate overflows.
    while (td.tv_nsec > 1e9L)
    {
    	td.tv_nsec -= 1e9L;
    	td.tv_sec++;
    }
    // Eliminate underflows.
    while (td.tv_nsec < 0L)
    {
    	td.tv_nsec += 1e9L;
    	td.tv_sec--;
    }
}
#endif



