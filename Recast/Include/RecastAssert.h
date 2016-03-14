//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef RECASTASSERT_H
#define RECASTASSERT_H

#pragma once

#if !defined WIN32
#include <signal.h>
#endif
//------------------------------------------------------------------------------

namespace recast {

// Returned by an assert handler to indicate whether execution should be halted, or allowed to continue.
namespace AssertionFailureResponse
{
	enum Enum
	{
		Halt,
		Continue,
	};
}

typedef AssertionFailureResponse::Enum(*AssertHandler)(const char* file, const int line, const char* message);

// Get and set the global assert handler, called when an assertion fails.
// A default implementation is provided which logs the assert to the console, then halts.
const AssertHandler& GetAssertHandler();
void SetAssertHandler(AssertHandler handler);

namespace internal {
// Only to be called by the assert macro.
AssertionFailureResponse::Enum ReportAssertionFailure(const char* file, const int line, const char* message, ...);
}

} // namespace recast

//------------------------------------------------------------------------------

// Use RECAST_ASSERTS_ENABLED to control whether asserts should have any effect.
// Defaults to being on in development and debug configurations, off in release.
#ifndef RECAST_ASSERTS_ENABLED
	#define RECAST_ASSERTS_ENABLED !NDEBUG
#endif

#ifdef _MSC_VER
#	define RECAST_INLINE_PRAGMA(x) __pragma(x) // x is intentionally not wrapped; __pragma rejects expressions beginning with '('.
#else
#	define RECAST_INLINE_PRAGMA(x)
#endif

#define RECAST_MACRO_BEGIN do {

#define RECAST_MACRO_END \
	} RECAST_INLINE_PRAGMA(warning(push)) RECAST_INLINE_PRAGMA(warning(disable:4127)) while (0) RECAST_INLINE_PRAGMA(warning(pop))

// This creative trickery taken from this StackOverflow answer:
// http://stackoverflow.com/questions/4030959/will-a-variablename-c-statement-be-a-no-op-at-all-times/4030983#4030983
#define RECAST_UNUSED(x)\
	RECAST_MACRO_BEGIN\
		((void)(true ? 0 : ((x), void(), 0)));\
	RECAST_MACRO_END

#if defined WIN32
	#define RECAST_DEBUGBREAK() __debugbreak()
#else
	#define RECAST_DEBUGBREAK() raise(SIGTRAP)
#endif

#if RECAST_ASSERTS_ENABLED

	#define RECAST_ASSERT_FAIL(message, ...)\
		RECAST_MACRO_BEGIN\
			if(recast::internal::ReportAssertionFailure(__FILE__, __LINE__, (message), __VA_ARGS__) == recast::AssertionFailureResponse::Halt)\
			{\
				RECAST_DEBUGBREAK();\
			}\
		RECAST_MACRO_END

	#define RECAST_ASSERT_MESSAGE(cond, message, ...)\
		RECAST_MACRO_BEGIN\
			if(!(cond))\
			{\
				RECAST_ASSERT_FAIL(message, __VA_ARGS__);\
			}\
		RECAST_MACRO_END

#else

	#define RECAST_ASSERT_FAIL(message, ...)\
		RECAST_MACRO_BEGIN\
			RECAST_UNUSED(message);\
		RECAST_MACRO_END

	#define RECAST_ASSERT_MESSAGE(condition, message, ...)\
		RECAST_MACRO_BEGIN\
			RECAST_UNUSED(condition);\
			RECAST_UNUSED(message);\
		RECAST_MACRO_END

#endif

#define rcAssert(cond) RECAST_ASSERT_MESSAGE(cond, #cond)

//------------------------------------------------------------------------------

#endif // RECASTASSERT_H
