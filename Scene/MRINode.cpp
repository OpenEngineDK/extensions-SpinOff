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
            northPole = CreateSphere(2, 5, Vector<3, float>(1,0,0));
            IDataBlockPtr verts = northPole->GetGeometrySet()->GetVertices();
            *verts += Vector<3, float>(0,0,0.2);
            southPole = CreateSphere(2, 5, Vector<3, float>(1,1,1));
            verts = southPole->GetGeometrySet()->GetVertices();
            *verts -= Vector<3, float>(0,0,0.2);

            // Create the global axis
            yAxis = CreateCylinder(0.2, 20, 13, Vector<3, float>(0,1,0));
            verts = yAxis->GetGeometrySet()->GetVertices();
            *verts += Vector<3, float>(0,10,0);
            
            xAxis = CreateCylinder(0.2, 20, 13, Vector<3, float>(0,0,1));
            verts = xAxis->GetGeometrySet()->GetVertices();
            *verts += Vector<3, float>(0,10,0);

            zAxis = CreateCylinder(0.2, 20, 13, Vector<3, float>(1,0,0));
            verts = zAxis->GetGeometrySet()->GetVertices();
            *verts += Vector<3, float>(0,10,0);

            // Create rotating axes
            e1 = CreateCylinder(0.2, 20, 13, Vector<3, float>(1,0.5,0.5));
            verts = e1->GetGeometrySet()->GetVertices();
            *verts += Vector<3, float>(0,10,0);
            e2 = CreateCylinder(0.2, 20, 13, Vector<3, float>(1,0,1));
            verts = e2->GetGeometrySet()->GetVertices();
            *verts += Vector<3, float>(0,10,0);

            netMagnetization = Vector<3, float>(20,0,0);

            microTime = 0;
                        
            strengthB0 = 0.5; // tesla
            temperature = 293.15; // Kelvin
            larmorFrequency = gamma * strengthB0; // v = gamme * B
            photonEnergi = PLANCK_CONSTANT * larmorFrequency; // E = h * v
            spinRelation = exp(-photonEnergi / (BOLTZMANN_CONSTANT * temperature));// N- / N+ = exp(-E / (k * T))

            logger.info << "Larmor Frequency: " << larmorFrequency << "Hz and " << larmorFrequency * 1e-6<< "MHz" << logger.end;
            logger.info << "Photon energi to cause transition " << photonEnergi << "J" << logger.end;
            logger.info << "Spin relation " << spinRelation << logger.end;
        }

        void MRINode::Handle(Core::ProcessEventArg arg){
            microTime += arg.approx;

            // Lagt ned vector
            Vector<3, float> M0(20,0,0);

            netMagnetization = StaticFieldEffect(M0, double(microTime) * 1e-6);
        }

        Vector<3, float> MRINode::StaticFieldEffect(Vector<3, float> M0, double t){
            Vector<3, float> ret = M0;
            double cosToTime = cos(larmorFrequency * t);
            double sinToTime = sin(larmorFrequency * t);
            double T1exp = exp(-t/T1);
            double T2exp = exp(-t/T2);
            ret[0] = T2exp * (M0[0] * cosToTime - M0[1] * sinToTime);
            ret[1] = T2exp * (M0[0] * sinToTime - M0[1] * cosToTime);
            ret[2] = M0[2] * T1exp + 40 * strengthB0 * (1-T1exp);
            return ret;
        }

    }
}
