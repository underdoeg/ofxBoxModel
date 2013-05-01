#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>

namespace ofx {

namespace boxModel {

namespace core {

/*****
* Templated container to stack BoxModels
****/

class TreeNodeBase{

};

/*****
* Templated container to stack objects
****/

template <class BoxModelType>
class TreeNode: public TreeNodeBase {
public:
	TreeNode() {};
	~TreeNode() {};
};

}

}

}

#endif // TREENODE_H
