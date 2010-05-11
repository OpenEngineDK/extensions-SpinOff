// MRI rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/OpenGL/MRIRenderingView.h>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

    MRIRenderingView::MRIRenderingView()
        : RenderingView(){
        
    }
    
    void MRIRenderingView::VisitMRINode(MRINode* node){
        ApplyMesh(node->northPole.get());
        //ApplyMesh(node->southPole.get());

        glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0, 0, 0);

        glVertex3f(0, 20, 0);
        
        glEnd();
    }

}
}
}
