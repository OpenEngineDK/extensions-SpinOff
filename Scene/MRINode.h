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

namespace OpenEngine {
    namespace Scene {

        class MRINode : public ISceneNode {
            OE_SCENE_NODE(MRINode, ISceneNode);

        public:
            MRINode();
        };

    }
}

#endif
