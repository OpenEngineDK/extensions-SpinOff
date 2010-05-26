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

        // Draw coordinate frame
        float degreesPrRad = 360 / (2 * PI);
        glPushMatrix();
        glRotatef(90, 0,0,-1);
        glRotatef(degreesPrRad * node->time * node->larmorFrequency, 0, 0, 1);
        ApplyMesh(node->e1.get());
        glPopMatrix();

        glPushMatrix();
        glRotatef(degreesPrRad * node->time * node->larmorFrequency, 0, 0, 1);
        ApplyMesh(node->e2.get());
        glPopMatrix();
        

        // Draw net magnetization
        glDisable(GL_DEPTH_TEST);
        glBegin(GL_LINES);

        glColor3f(1,1,0);
        glVertex3f(0,0,0);
        glVertex3fv(node->netMagnetization.ToArray());

        glEnd();
        glEnable(GL_DEPTH_TEST);
    }

}
}
}
