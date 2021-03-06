// MRI rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _MRI_RENDERING_VIEW_H_
#define _MRI_RENDERING_VIEW_H_

#include <Renderers/OpenGL/RenderingView.h>
#include <Scene/MRINode.h>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

    class MRIRenderingView : public RenderingView {
    public:
        MRIRenderingView();

        void VisitMRINode(MRINode* node);
    };

}
}
}

#endif
