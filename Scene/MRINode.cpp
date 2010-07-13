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
#include <Math/Math.h>

#include <Utils/MeshCreator.h>

#include <Logging/Logger.h>

using namespace OpenEngine::Resources;
using namespace OpenEngine::Utils::MeshCreator;

namespace OpenEngine {
    namespace Scene {
        const double MRINode::T1 = 1e-5; // spin lattice in seconds.
        const double MRINode::T2 = 1e-6; // spin spin in seconds.
        const double MRINode::e = 2.718281828;
        const double MRINode::GYROMAGNETIC_RATIO = 42.58e6; // hertz pr tesla
        const double MRINode::BOLTZMANN_CONSTANT = 1.3805e-23; // Joule / Kelvin
        const double MRINode::PLANCK_CONSTANT = 6.626e-34; // Joule * seconds

        MRINode::MRINode() {
            northPole = CreateSphere(2, 6, Vector<3, float>(1,0,0));
            IDataBlockPtr verts = northPole->GetGeometrySet()->GetVertices();
            *verts += Vector<3, float>(0,0,0.05);
            southPole = CreateSphere(2, 6, Vector<3, float>(1,1,1));
            verts = southPole->GetGeometrySet()->GetVertices();
            *verts -= Vector<3, float>(0,0,0.05);

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
            e1 = Vector<3, float>(1, 0, 0);
            e2 = Vector<3, float>(0, 1, 0);

            m0 = Vector<3, float>(0,25,0);
            localNetMagnetization = Vector<3, float>(0,0,20);
            globalNetMagnetization = Vector<3, float>(0,0,20);

            precessionTime = 0;
            time = 0;
                        
            strengthB0 = 0.5; // tesla
            strengthB1 = 0.5; // tesla
            temperature = 293.15; // Kelvin
            larmorFrequency = GYROMAGNETIC_RATIO * strengthB0; // v = gamme * B
            photonEnergi = PLANCK_CONSTANT * larmorFrequency; // E = h * v
            spinRelation = exp(-photonEnergi / (BOLTZMANN_CONSTANT * temperature));// N- / N+ = exp(-E / (k * T))
            tau1 = (PI / 2.0) / (GYROMAGNETIC_RATIO * strengthB1);

            logger.info << "Larmor Frequency: " << larmorFrequency << "Hz and " << larmorFrequency * 1e-6<< "MHz" << logger.end;
            logger.info << "Photon energi to cause transition " << photonEnergi << "J" << logger.end;
            logger.info << "Spin relation " << spinRelation << logger.end;
            logger.info << "90 degree pulse time " << tau1 << "seconds" << logger.end;
        }

        void MRINode::Handle(Core::ProcessEventArg arg){
            double dT = double(arg.approx) * 1e-13;
            precessionTime += dT;
            time += dT;

            // Update the rotating framework
            e1[0] = cos(larmorFrequency * precessionTime);
            e1[1] = sin(larmorFrequency * precessionTime);
            e2[0] = -sin(larmorFrequency * precessionTime);
            e2[1] = cos(larmorFrequency * precessionTime);

            // Lagt ned vector
            //GlobalStaticFieldEffect();
            LocalStaticFieldEffect();

        }

        Vector<3, float> MRINode::GlobalStaticFieldEffect(){
            double T1exp = exp(-time/T1);
            double T2exp = exp(-time/T2);
            globalNetMagnetization[0] = T2exp * (m0[0] * e1[0] + m0[1] * e2[0]);
            globalNetMagnetization[1] = T2exp * (m0[0] * e1[1] + m0[1] * e2[1]);
            globalNetMagnetization[2] = m0[2] * T1exp + 40 * strengthB0 * (1-T1exp);

            // Update local vector
            localNetMagnetization[0] = globalNetMagnetization[0] * e1[0] + globalNetMagnetization[1] * e1[1];
            localNetMagnetization[1] = -globalNetMagnetization[0] * e1[1] + globalNetMagnetization[1] * e1[0];
            localNetMagnetization[2] = globalNetMagnetization[2];

            return globalNetMagnetization;
        }

        Vector<3, float> MRINode::LocalStaticFieldEffect(){
            double T1exp = exp(-time/T1);
            double T2exp = exp(-time/T2);
            
            localNetMagnetization[0] = T2exp * m0[0];
            localNetMagnetization[1] = T2exp * m0[1];
            localNetMagnetization[2] = m0[2] * T1exp + 40 * strengthB0 * (1-T1exp);
            
            // Update global vector
            globalNetMagnetization[0] = localNetMagnetization[0] * e1[0] + localNetMagnetization[1] * e2[0];
            globalNetMagnetization[1] = localNetMagnetization[0] * e1[1] + localNetMagnetization[1] * e2[1];
            globalNetMagnetization[2] = localNetMagnetization[2];

            return localNetMagnetization;
        }

        void MRINode::Flip(float degrees){
            m0 = Vector<3, float>(0,25,0);
            precessionTime += tau1;
            time = 0;
        }

    }
}
