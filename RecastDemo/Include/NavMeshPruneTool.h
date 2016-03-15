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

#ifndef NAVMESHPRUNETOOL_H
#define NAVMESHPRUNETOOL_H

#include "Sample.h"
#include "RecastDefines.h"

// Prune navmesh to accessible locations from a point.

class NavMeshPruneTool : public SampleTool
{
	Sample* m_sample;
	
	class NavmeshFlags* m_flags;

	float m_hitPos[3];
	bool m_hitPosSet;
	
public:
	NavMeshPruneTool();
	virtual ~NavMeshPruneTool();
	
	RC_OVERRIDDEN_VIRTUAL int type() RC_OVERRIDE { return TOOL_NAVMESH_PRUNE; }
	RC_OVERRIDDEN_VIRTUAL void init(Sample* sample) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void reset() RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void handleMenu() RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void handleClick(const float* s, const float* p, bool shift) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void handleToggle() RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void handleStep() RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void handleUpdate(const float dt) RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void handleRender() RC_OVERRIDE;
	RC_OVERRIDDEN_VIRTUAL void handleRenderOverlay(double* proj, double* model, int* view) RC_OVERRIDE;

private:
	// Explicitly disabled copy constructor and copy assignment operator.
	NavMeshPruneTool(const NavMeshPruneTool&);
	NavMeshPruneTool& operator=(const NavMeshPruneTool&);
};

#endif // NAVMESHPRUNETOOL_H
