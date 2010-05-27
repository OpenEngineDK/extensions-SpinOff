// MRI node.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _MRI_NODE_H_
#define _MRI_NODE_H_

#include <Core/EngineEvents.h>
#include <Core/IListener.h>
#include <Math/Vector.h>
#include <Scene/ISceneNode.h>

#include <boost/shared_ptr.hpp>

using namespace OpenEngine::Math;

namespace OpenEngine {
    namespace Geometry {
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;
    }
    namespace Scene {

        class MRINode : public ISceneNode,
                        public Core::IListener<Core::ProcessEventArg>{
            OE_SCENE_NODE(MRINode, ISceneNode);
        public:

            static const double T1 = 1e-5; // spin lattice in seconds.
            static const double T2 = 1e-6; // spin spin in seconds.
            static const double e = 2.718281828;
            static const double GYROMAGNETIC_RATIO = 42.58e6; // hertz pr tesla
            static const double BOLTZMANN_CONSTANT = 1.3805e-23; // Joule / Kelvin
            static const double PLANCK_CONSTANT = 6.626e-34; // Joule * seconds


            double strengthB0; // strength in tesla.
            double strengthB1; // strength in tesla of the RF magnetic field.
            double temperature; // Kelvin
            double larmorFrequency; // hertz
            double photonEnergi; // Joule
            double spinRelation; // Relation between spin at the lower
                                 // energi level and spins at the upper energi level
            double tau1; // The time it takes the RF field to flip the
                         // magnetization vector by 90 degrees.

            Geometry::MeshPtr northPole;
            Geometry::MeshPtr southPole;
            Geometry::MeshPtr xAxis;
            Geometry::MeshPtr yAxis;
            Geometry::MeshPtr zAxis;
            Vector<3, float> e1;
            Vector<3, float> e2;
            Vector<3, float> m0;
            Vector<3, float> localNetMagnetization;
            Vector<3, float> globalNetMagnetization;

            double precessionTime; // time in seconds
            double time; // time since last action

        public:
            MRINode();

            void Handle(Core::ProcessEventArg arg);

            /**
             * The position of the vector mag at time t, influenced
             * only by the static magnetic field B0.
             */
            Vector<3, float> GlobalStaticFieldEffect();
            Vector<3, float> LocalStaticFieldEffect();
            
            void Flip(float degrees);
        };

    }
}

#endif
