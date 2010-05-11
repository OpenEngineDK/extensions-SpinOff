// MRI node.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/MRINode.h>

#include <Utils/MeshCreator.h>

using namespace OpenEngine::Utils::MeshCreator;

namespace OpenEngine {
    namespace Scene {

        MRINode::MRINode() {
            northPole = CreateCube(10, 1, Vector<3, float>(1,0,0));
            southPole = CreateCube(10, 1, Vector<3, float>(1,1,1));

            netMagnetization = Vector<3, float>(0,20,0);
        }

    }
}
