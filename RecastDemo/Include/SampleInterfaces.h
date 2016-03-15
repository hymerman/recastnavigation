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

#ifndef SAMPLEINTERFACES_H
#define SAMPLEINTERFACES_H

#include "DebugDraw.h"
#include "Recast.h"
#include "RecastDefines.h"
#include "RecastDump.h"
#include "PerfTimer.h"

#include <stdio.h>

// These are example implementations of various interfaces used in Recast and Detour.

/// Recast build context.
class BuildContext : public rcContext
{
	TimeVal m_startTime[RC_MAX_TIMERS];
	TimeVal m_accTime[RC_MAX_TIMERS];

	static const int MAX_MESSAGES = 1000;
	const char* m_messages[MAX_MESSAGES];
	int m_messageCount;
	static const int TEXT_POOL_SIZE = 8000;
	char m_textPool[TEXT_POOL_SIZE];
	int m_textPoolSize;
	
public:
	BuildContext();
	
	/// Dumps the log to stdout.
	void dumpLog(const char* format, ...);
	/// Returns number of log messages.
	int getLogCount() const;
	/// Returns log message text.
	const char* getLogText(const int i) const;
	
protected:	
	/// Virtual functions for custom implementations.
	///@{
	RC_OVERRIDDEN_VIRTUAL void doResetLog() RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void doLog(const rcLogCategory category, const char* msg, const int len) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void doResetTimers() RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void doStartTimer(const rcTimerLabel label) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void doStopTimer(const rcTimerLabel label) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL int doGetAccumulatedTime(const rcTimerLabel label) const RC_OVERRIDE;
	///@}
};

/// OpenGL debug draw implementation.
class DebugDrawGL : public duDebugDraw
{
public:
	RC_OVERRIDDEN_VIRTUAL void depthMask(bool state) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void texture(bool state) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void begin(duDebugDrawPrimitives prim, float size = 1.0f) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void vertex(const float* pos, unsigned int color) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void vertex(const float x, const float y, const float z, unsigned int color) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void vertex(const float* pos, unsigned int color, const float* uv) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void vertex(const float x, const float y, const float z, unsigned int color, const float u, const float v) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void end() RC_OVERRIDE;
};

/// stdio file implementation.
class FileIO : public duFileIO
{
	FILE* m_fp;
	int m_mode;
public:
	FileIO();
	virtual ~FileIO();
	bool openForWrite(const char* path);
	bool openForRead(const char* path);
	RC_OVERRIDDEN_VIRTUAL bool isWriting() const RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL bool isReading() const RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL bool write(const void* ptr, const size_t size) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL bool read(void* ptr, const size_t size) RC_OVERRIDE;
private:
	// Explicitly disabled copy constructor and copy assignment operator.
	FileIO(const FileIO&);
	FileIO& operator=(const FileIO&) RC_DELETED_FUNCTION;
};

#endif // SAMPLEINTERFACES_H

