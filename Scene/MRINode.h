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

            static const double T1 = 1e6; // spin lattice in microseconds.
            static const double T2 = 1e6; // spin spin in microseconds.
            static const double e = 2.718281828;
            static const double gamma = 42.6e6; // hertz pr tesla
            static const double microGamma = 42.6; // microhertz pr tesla

            double strengthB0; // strength in tesla.
            double microOmega0; // microhertz

            Geometry::MeshPtr northPole;
            Geometry::MeshPtr southPole;
            Vector<3, float> netMagnetization;

            unsigned int microTime; // time in microseconds.

        public:
            MRINode();

            void Handle(Core::ProcessEventArg arg);

        private:

            /**
             * The position of the vector mag at time t, influenced
             * only by the static magnetic field B0.
             */
            Vector<3, float> StaticFieldEffect(Vector<3, float> mag, unsigned int t);
        };

    }
}

#endif
