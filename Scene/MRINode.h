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

#include <Scene/ISceneNode.h>
#include <boost/shared_ptr.hpp>
#include <Math/Vector.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
    namespace Geometry {
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;
    }
    namespace Scene {

        class MRINode : public ISceneNode {
            OE_SCENE_NODE(MRINode, ISceneNode);
        public:

            Geometry::MeshPtr northPole;
            Geometry::MeshPtr southPole;
            Vector<3, float> netMagnetization;

        public:
            MRINode();

            
        };

    }
}

#endif
