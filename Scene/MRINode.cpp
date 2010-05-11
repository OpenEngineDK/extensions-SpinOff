// MRI node.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/MRINode.h>
#include <Geometry/Mesh.h>
#include <Geometry/GeometrySet.h>
#include <Resources/IDataBlock.h>

#include <Utils/MeshCreator.h>

#include <Logging/Logger.h>

using namespace OpenEngine::Resources;
using namespace OpenEngine::Utils::MeshCreator;

namespace OpenEngine {
    namespace Scene {

        MRINode::MRINode() {
            northPole = CreateCube(10, 1, Vector<3, float>(1,0,0));
            IDataBlockPtr verts = northPole->GetGeometrySet()->GetVertices();
            *verts += Vector<3, float>(0,0,5);
            southPole = CreateCube(10, 1, Vector<3, float>(1,1,1));
            verts = southPole->GetGeometrySet()->GetVertices();
            *verts -= Vector<3, float>(0,0,5);

            netMagnetization = Vector<3, float>(0,0,20);

            microTime = 0;
            
            strengthB0 = 0.5;
            microOmega0 = microGamma * strengthB0;
        }

        void MRINode::Handle(Core::ProcessEventArg arg){
            microTime += arg.approx;

            // Lagt ned vector
            Vector<3, float> M0(20,0,0);

            netMagnetization = StaticFieldEffect(M0, microTime);
        }

        Vector<3, float> MRINode::StaticFieldEffect(Vector<3, float> M0, unsigned int t){
            Vector<3, float> ret = M0;
            double cosToTime = cos(microOmega0 * t);
            double sinToTime = sin(microOmega0 * t);
            double T1exp = exp(-1 * double(-t)/double(T1));
            double T2exp = exp(-1 * double(t)/double(T2));
            ret[0] = T2exp * (M0[0] * cosToTime - M0[1] * sinToTime);
            ret[1] = T2exp * (M0[0] * sinToTime - M0[1] * cosToTime);
            ret[2] = M0[2] * T1exp + 40 * strengthB0 * (1-T1exp);
            return ret;
        }

    }
}
