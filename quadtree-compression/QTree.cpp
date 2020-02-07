/**
 *
 * Balanced Quad Tree (pa3)
 *
 * This file will be used for grading.
 *
 */

#include "QTree.h"

// Return the biggest power of 2 less than or equal to n
int biggestPow2(int n) {
  if( n < 1 ) return 0;
  int v = 1;
  while( v <= n ) v <<= 1;
  return v >> 1;
}


QTree::Node::Node(PNG & im, pair<int,int> ul, int sz, Node *par)
  :upLeft(ul),size(sz),parent(par),nw(NULL),ne(NULL),sw(NULL),se(NULL)
{
  var = varAndAvg(im,ul,size,avg);
}

// bool QTree::Node::Compare(Node* a, Node* b) {
//   return (a->var > b->var);
// }

// bool QTree::Node::operator()(const Node* & a, const Node* & b) {
//   return (a->var > b->var);
// }

QTree::~QTree(){
  clear();
}

QTree::QTree(const QTree & other) {
  copy(other);
}


QTree & QTree::operator=(const QTree & rhs){
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}


QTree::QTree(PNG & imIn, int leafB, RGBAPixel frameC, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(true), frameColor(frameC)
{
    this->im = imIn;
    int pow2_x = biggestPow2(imIn.width());
    int pow2_y = biggestPow2(imIn.height());
    int imSize = min(pow2_x, pow2_y); // if we have an image 256x1024, rather have an image 256x256 than 1024x1024
    this->im.resize(imSize, imSize); // resize image to 2^k where k is biggest k able to fit in the image

    this->root = new Node(this->im, make_pair(0,0), imSize, NULL);
    this->frameColor = NULL;

    leaves.push(this->root);
    this->numLeaf = 1;
    //split(leaves.top());

    //loop around leaves
    while (!leaves.empty() && numLeaf < leafBound) {

        Node * t = leaves.top();

        if (isLeaf(t) && t->size > 1) {
            split(t);
            leaves.pop();
            //this->numLeaf -= 1;
        } else {
            leaves.pop();
            //this->numLeaf -= 1;
        };


        if (this->balanced) {

            // for balance - check is t parent has nbrs that need to be split and if so, insert them into leaves
            if (t->parent != NULL) {
                if (t->parent != this->root) {
                    if (t == t->parent->nw || t == t->parent->ne) {
                        Node * north = NNbr(t->parent);
                        if (north != NULL && isLeaf(north)) {
                            split(north);
                        }
                    }

                    if (t == t->parent->se || t == t->parent->ne) {
                        Node * east = ENbr(t->parent);
                        if (east != NULL && isLeaf(east)) {
                            split(east);
                        }
                    }

                    if (t == t->parent->sw || t == t->parent->se) {
                        Node * south = SNbr(t->parent);
                        if (south != NULL && isLeaf(south)) {
                            split(south);
                        }
                    }

                    if (t == t->parent->nw || t == t->parent->sw) {
                        Node * west  = WNbr(t->parent);
                        if (west != NULL && isLeaf(west)) {
                            split(west);
                        }
                    }
                }
            }

        }


    }

}




QTree::QTree(PNG & imIn, int leafB, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(false)
{
  this->im = imIn;
  int pow2_x = biggestPow2(imIn.width());
  int pow2_y = biggestPow2(imIn.height());
  int imSize = min(pow2_x, pow2_y); // if we have an image 256x1024, rather have an image 256x256 than 1024x1024
  this->im.resize(imSize, imSize); // resize image to 2^k where k is biggest k able to fit in the image

  this->root = new Node(this->im, make_pair(0,0), imSize, NULL);
  this->frameColor = NULL;

  leaves.push(this->root);
  this->numLeaf = 1;
    //split(leaves.top());

    //loop around leaves
    while (!leaves.empty() && numLeaf < leafBound) {

        Node * t = leaves.top();

        if (isLeaf(t) && t->size > 1) {
            split(t);
            leaves.pop();
            //this->numLeaf -= 1;
        } else {
            leaves.pop();
            //this->numLeaf -= 1;
        };


        if (this->balanced) {

            // for balance - check is t parent has nbrs that need to be split and if so, insert them into leaves
            if (t->parent != NULL) {
                if (t->parent != this->root) {
                    if (t == t->parent->nw || t == t->parent->ne) {
                        Node * north = NNbr(t->parent);
                        if (north != NULL && isLeaf(north)) {
                            split(north);
                        }
                    }

                    if (t == t->parent->se || t == t->parent->ne) {
                        Node * east = ENbr(t->parent);
                        if (east != NULL && isLeaf(east)) {
                            split(east);
                        }
                    }

                    if (t == t->parent->sw || t == t->parent->se) {
                        Node * south = SNbr(t->parent);
                        if (south != NULL && isLeaf(south)) {
                            split(south);
                        }
                    }

                    if (t == t->parent->nw || t == t->parent->sw) {
                        Node * west  = WNbr(t->parent);
                        if (west != NULL && isLeaf(west)) {
                            split(west);
                        }
                    }
                }
            }

        }


    }

}


bool QTree::isLeaf( Node *t ) {
  
//if (t->nw && t->ne && t->sw && t->se) return false; // if node has children, it's not a leaf

if (t == NULL) return false;

  if (t->nw && t->ne && t->sw && t->se) {
      return false;
  }
  //else if (t->parent){
     return true;
  }

//  bool result = false;
//  Node* test = t;
//  bool whileLoop = true;
//
//  while (whileLoop) { // climb the node's tree and check if the topmost parent is the root of this tree
//    if (test->parent == NULL) {
//      result = (test->parent == root);
//      whileLoop = false;
//      break;
//    } else {
//      test = test->parent;
//    }
//  }
//
//  return result;


  
void QTree::split( Node *t) {

    t->nw = new Node(im, t->upLeft, t->size / 2, t);
    leaves.push(t->nw);
    //this->numLeaf += 1;

    t->ne = new Node(im, make_pair(t->upLeft.first + t->size / 2, t->upLeft.second), t->size / 2, t);
    leaves.push(t->ne);
    //this->numLeaf += 1;

    t->sw = new Node(im, make_pair(t->upLeft.first, t->upLeft.second + t->size / 2), t->size / 2, t);
    leaves.push(t->sw);
    //this->numLeaf += 1;

    t->se = new Node(im, make_pair(t->upLeft.first + t->size / 2, t->upLeft.second + t->size / 2), t->size / 2, t);
    leaves.push(t->se);
    //this->numLeaf += 1;
    numLeaf+=3;

//    int leavesSize = (int) leaves.size();
//
//    Node * temp;
//    for (int i = 0; i < leavesSize; i++) {
//        temp = leaves.top();
//
//        if (!isLeaf(temp)) {
//            leaves.pop();
//            this->numLeaf -= 1;
//        } else {
//            leaves.pop();
//            this->numLeaf -= 1;
//            leaves.push(temp);
//            this->numLeaf += 1;
//        }
//    }


  // FOR BALANCED QTREES-------------------------------------------------
  // A split might cause one or two nbrs of the parent of t to split
  // to maintain balance.  Note that these two nbrs exist (unless they're
  // not in the image region) because the current set of leaves are
  // balanced.
  // if( t is a NW (or NE or SW or SE) child ) then we need to check that
  // the North and West (or North and East or South and West or
  // South and East) nbrs of t->parent have children. If they don't
  // we need to split them.

  //NOTE: ALWAYS input t = leaves.top();
  // leaves is supposed to be self-sorting - we split the highest var leaf, and that will be leaves.top()


}

//void QTree::splitBalance( Node *t) {
//}


/* NNbr(t)
 * return the same-sized quad tree node that is north of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::NNbr(Node *t) {

  /* YOUR CODE HERE */
  /* PART2 */
  if (t == root) return NULL;
  if (t == t->parent->sw) return t->parent->nw;
  if (t == t->parent->se) return t->parent->ne;

  Node* v = NNbr(t->parent);
  if (isLeaf(v) || v == NULL) {
      return NULL;
  } else if (t == t->parent->nw) {
      return v->sw;
  } else {
      return v->se;
  }
}

/* SNbr(t)
 * return the same-sized quad tree node that is south of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::SNbr(Node *t) {

  /* YOUR CODE HERE */
  /* PART2 */
  if (t == root) return NULL;
  if (t == t->parent->nw) return t->parent->sw;
  if (t == t->parent->ne) return t->parent->se;

  Node* v = SNbr(t->parent);
  if (isLeaf(v) || v == NULL) {
      return NULL;
  } else if (t == t->parent->sw) {
        return v->nw;
  } else {
      return v->ne;
  }

}

/* ENbr(t)
 * return the same-sized quad tree node that is east of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::ENbr(Node *t) {

    /* YOUR CODE HERE */
    /* PART2 */
    if (t == root) return NULL;
    if (t == t->parent->nw) return t->parent->ne;
    if (t == t->parent->sw) return t->parent->se;

    Node* v = ENbr(t->parent);
    if (isLeaf(v) || v == NULL) {
        return NULL;
    } else if (t == t->parent->ne) {
        return v->nw;
    } else {
        return v->sw;
    }

}

/* WNbr(t)
 * return the same-sized quad tree node that is west of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::WNbr(Node *t) {

    /* YOUR CODE HERE */
    /* PART2 */
    if (t == root) return NULL;
    if (t == t->parent->ne) return t->parent->nw;
    if (t == t->parent->se) return t->parent->sw;

    Node* v = WNbr(t->parent);
    if (isLeaf(v) || v == NULL) {
        return NULL;
    } else if (t == t->parent->nw) {
        return v->ne;
    } else {
        return v->se;
    }

}

bool QTree::write(string const & fileName){


  int leavesSize = (int) leaves.size();
//
//  // iterate through leaves and paint onto image
//    for (int i = 0; i < leavesSize; i++) {
//        write(leaves.top(), this->im);
//        leaves.pop();
//    }

    // iterate through leaves and paint onto image

    Node * temp;
    for (int i = 0; i < leavesSize; i++) {
        temp = leaves.top();

        if (isLeaf(temp)) {
            write(temp, this->im);
            leaves.pop();
            //this->numLeaf -= 1;
        } else {
            leaves.pop();
            //this->numLeaf -= 1;
        }
    }

  // include the following line to write the image to file.
  return(im.writeToFile(fileName));

}

bool QTree::write(Node* t, PNG & im) {
  if (this->drawFrame) {
    //RGBAPixel blackBorder(0,0,0,255);
    RGBAPixel blackBorder = frameColor;

    int target = t->size; 

    for (int x = t->upLeft.first; x < t->upLeft.first + target; x++) { // top/bottom
      RGBAPixel * GooglePixel = im.getPixel(x,t->upLeft.second); 
      *GooglePixel = blackBorder; 
      RGBAPixel * GooglePixel2 = im.getPixel(x,t->upLeft.second + target - 1); 
      *GooglePixel2 = blackBorder; 
    }

    for (int y = t->upLeft.second; y < t->upLeft.second + target; y++) { //left/right
      RGBAPixel * GooglePixel = im.getPixel(t->upLeft.first,y); 
      *GooglePixel = blackBorder; 
      RGBAPixel * GooglePixel2 = im.getPixel(t->upLeft.first + target - 1,y); 
      *GooglePixel2 = blackBorder; 
    }

    for (int x = t->upLeft.first + 1; x < t->upLeft.first + target - 1; x++) { // everywhere else
      for (int y = t->upLeft.second + 1; y < t->upLeft.second + target - 1; y++) {
        RGBAPixel * GooglePixel = im.getPixel(x,y); 
        *GooglePixel = t->avg; 
      }
    }
  } else {
    int target = t->size; 

    for (int x = t->upLeft.first; x < t->upLeft.first + target; x++) { //everywhere else
      for (int y = t->upLeft.second; y < t->upLeft.second + target; y++) {
        RGBAPixel * GooglePixel = im.getPixel(x,y); 
        *GooglePixel = t->avg; 
      }
    }
  }

  return true;
}

void QTree::clear() {

  clear(this->root);
  
}

void QTree::clear(Node* t) {

  if (t == NULL) return;

  clear(t->nw);
  clear(t->ne);
  clear(t->sw);
  clear(t->se);
  delete t;
  t = NULL;
  
}


void QTree::copy(const QTree & orig) {
  
  if (orig.root == NULL) clear();

  PNG origIm = orig.im;

  this->root = new Node(origIm, orig.root->upLeft, orig.root->size, orig.root->parent);;
  this->im = origIm;
  this->numLeaf = orig.numLeaf;
  this->leafBound = orig.leafBound;
  this->balanced = orig.balanced;
  this->drawFrame = orig.drawFrame;
  this->frameColor = orig.frameColor;

  copy(this->root, orig.root, origIm);
  
}

void QTree::copy(Node* thisUpper, Node* copyNext, PNG copyIm) {

  if (copyNext == NULL) return;

  if (copyNext->nw != NULL) {
    thisUpper->nw = new Node(copyIm, copyNext->nw->upLeft, copyNext->nw->size, thisUpper);
    copy(thisUpper->nw, copyNext->nw, copyIm);
  }
  
  if (copyNext->ne != NULL) {
    thisUpper->ne = new Node(copyIm, copyNext->ne->upLeft, copyNext->ne->size, thisUpper);
    copy(thisUpper->ne, copyNext->ne, copyIm); 
  }

  if (copyNext->sw != NULL) {
    thisUpper->sw = new Node(copyIm, copyNext->sw->upLeft, copyNext->sw->size, thisUpper);
    copy(thisUpper->sw, copyNext->sw, copyIm);
  }
  
  if (copyNext->se != NULL) {
    thisUpper->se = new Node(copyIm, copyNext->se->upLeft, copyNext->se->size, thisUpper);
    copy(thisUpper->se, copyNext->se, copyIm);
  }

}
