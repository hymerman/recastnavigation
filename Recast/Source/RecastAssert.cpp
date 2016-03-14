#include "RecastAssert.h"

#include <cstdarg>
#include <string>

//------------------------------------------------------------------------------

namespace {

recast::AssertionFailureResponse::Enum defaultHandler(
	const char*		file,
	const int		line,
	const char*		message
)
{
	printf("Assertion failure: %s(%d)", file, line);

	if(message)
	{
		printf(message);
	}

	return recast::AssertionFailureResponse::Halt;
}

recast::AssertHandler globalAssertHandler = defaultHandler;

} // anonymous namespace

//------------------------------------------------------------------------------

namespace recast {

//------------------------------------------------------------------------------

const AssertHandler& GetAssertHandler()
{
	return globalAssertHandler;
}

//------------------------------------------------------------------------------

void SetAssertHandler(AssertHandler handler)
{
	globalAssertHandler = handler;
}

//------------------------------------------------------------------------------

namespace internal {

AssertionFailureResponse::Enum ReportAssertionFailure(
	const char*		file,
	const int		line,
	const char*		message,
	...
)
{
	if(const auto& handler = GetAssertHandler())
	{
		const char* formattedMessage = nullptr;

		if(message)
		{
			char messageBuffer[1024];

			{
				va_list args;
				va_start(args, message);
				vsnprintf(messageBuffer, 1024, message, args);
				va_end(args);
			}

			formattedMessage = messageBuffer;
		}

		return handler(file, line, formattedMessage);
	}

	return AssertionFailureResponse::Halt;
}

} // namespace internal

//------------------------------------------------------------------------------

} // namespace recast

//------------------------------------------------------------------------------

