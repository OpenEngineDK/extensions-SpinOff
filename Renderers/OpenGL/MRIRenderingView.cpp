// MRI rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/OpenGL/MRIRenderingView.h>
#include <Math/Math.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

    MRIRenderingView::MRIRenderingView()
        : RenderingView(){
        
    }
    
    void MRIRenderingView::VisitMRINode(MRINode* node){
        // Draw "nucleus"
        ApplyMesh(node->northPole.get());
        ApplyMesh(node->southPole.get());

        // Draw global coordinate system
        glPushMatrix();
        glRotatef(90, 1,0,0);
        ApplyMesh(node->zAxis.get());
        glPopMatrix();
 
        ApplyMesh(node->yAxis.get());

        glPushMatrix();
        glRotatef(90, 0,0,-1);
        ApplyMesh(node->xAxis.get());
        glPopMatrix();

        glDisable(GL_DEPTH_TEST);
        glBegin(GL_LINES);

        // Draw coordinate frame
        glColor3f(1,1,0);
        Vector<3, float> e1 = node->e1 * 20;
        glVertex3f(0,0,0);
        glVertex3fv(e1.ToArray());
        
        glColor3f(1,1,0);
        Vector<3, float> e2 = node->e2 * 20;
        glVertex3f(0,0,0);
        glVertex3fv(e2.ToArray());

        // Draw net magnetization
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3fv(node->globalNetMagnetization.ToArray());

        glEnd();
        glEnable(GL_DEPTH_TEST);
    }

}
}
}
