
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"
#include <queue>
#include <iostream>
#include <math.h>

/* given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

/* given */
twoDtree::~twoDtree(){
	clear();
}

/* given */
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}

/* given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){
	pair <int, int> lr;
	pair <int, int> ul;
	lr = make_pair(imIn.width() - 1, imIn.height() - 1);
	ul = make_pair(0,0);
	height = imIn.height();
	width = imIn.width();
	stats s = stats(imIn);
	root = buildTree(s, ul, lr);
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {
    twoDtree::Node* node = new twoDtree::Node(ul,lr,s.getAvg(ul,lr));

    if(ul==lr){
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    else{
        long minVScore = -1;
        pair<int,int> updateLr;
        pair<int,int> minLr;
        updateLr.second = lr.second;
        minLr.second = lr.second;
        minLr.first = lr.first - 1;
        for (int i = lr.first-1; i>=ul.first; i--){
            updateLr.first = i;
            pair<int,int> vUlOther;
            vUlOther.first = updateLr.first;
            vUlOther.second = ul.second;

            if(i==lr.first-1){
                minVScore = s.getScore(ul,updateLr)+ s.getScore(vUlOther,lr);
            }
            else if(s.getScore(ul,updateLr)+s.getScore(vUlOther,lr)<minVScore){
                minVScore = s.getScore(ul,updateLr)+ s.getScore(vUlOther,lr);
                minLr.first = updateLr.first;
            }
        }
        long minHScore = -1;
        pair<int,int> updateUl;
        pair<int,int> minUl;
        updateUl.first = ul.first;
        minUl.first = ul.first;
        minUl.second = ul.second +1;
        for (int j = ul.second+1; j <= lr.second; ++j){
            updateUl.second = j;
            pair<int,int> vLrOther;
            vLrOther.first = lr.first;
            vLrOther.second = updateUl.second;
            if(j==ul.second+1){
                minHScore = s.getScore(ul,vLrOther) + s.getScore(updateUl, lr);
            }
            else if(s.getScore(ul,vLrOther)+s.getScore(updateUl,lr)<minHScore){
                minHScore = s.getScore(ul,vLrOther)+s.getScore(updateUl,lr);
                minUl.second = updateUl.second;
            }
        }
        if(minVScore==-1){
            pair<int, int> new_lrChild;
            new_lrChild.first = lr.first;
            new_lrChild.second = minUl.second - 1;
            node->left = buildTree(s, ul, new_lrChild);
            node->right = buildTree(s, minUl, lr);
        }
        else if(minHScore == -1){
            pair<int, int> new_ulChild;
            new_ulChild.first = minLr.first + 1;
            new_ulChild.second = ul.second;
            node->left = buildTree(s, ul, minLr);
            node->right = buildTree(s, new_ulChild, lr);
        }
        else{
            if (minHScore >= minVScore) {
                pair<int, int> new_ulChild;
                new_ulChild.first = minLr.first + 1;
                new_ulChild.second = ul.second;
                node->left = buildTree(s, ul, minLr);
                node->right = buildTree(s, new_ulChild, lr);
            } else if (minVScore > minHScore) {
                pair<int, int> new_lrChild;
                new_lrChild.first = lr.first;
                new_lrChild.second = minUl.second - 1;
                node->left = buildTree(s, ul, new_lrChild);
                node->right = buildTree(s, minUl, lr);
            }
        }
    }
    return node;
}

PNG twoDtree::render(){
   PNG pic = PNG((unsigned int) width, (unsigned int) height);
   renderHelper(root, pic);
   return pic;
}

void twoDtree::renderHelper(Node* n, PNG &pic){
	if(n->left== nullptr&&n->right== nullptr){
		for (int y = n->upLeft.second; y<=n->lowRight.second; y++){
			for (int x = n->upLeft.first; x<=n->lowRight.first ; x++){
				RGBAPixel* pix = pic.getPixel(x, y);
				pix->r = n->avg.r;
				pix->g = n->avg.g;
				pix->b = n->avg.b;
				pix->a = n->avg.a;
			}
		}
  }
	else{
		renderHelper(n->left,pic);
		renderHelper(n->right,pic);
	}
}


void twoDtree::prune(double pct, int tol){
	pruneHelper(pct, tol, root);
}

void twoDtree::pruneHelper(double pct, int tol, Node* n){
	if(n->left == NULL && n->right == NULL)
		return;

    double total = ((n->lowRight.first + 1) - (n->upLeft.first)) * ((n->lowRight.second+1)-(n->upLeft.second));
	double count =tolLeafCounter(n, n, tol);


	if(count/total >= pct){
		clearHelper(n->left);
		clearHelper(n->right);
		n->left = NULL;
		n->right = NULL;
		return;
	}

	pruneHelper(pct, tol, n->left);
	pruneHelper(pct, tol, n->right);
}


double twoDtree::tolLeafCounter(Node* root, Node* n, int tol){
	if(n == NULL)
		return 0;
	if(n->left == NULL && n->right == NULL){
		int diff = 	pow(n->avg.g - root->avg.g, 2) +
								pow(n->avg.r - root->avg.r, 2) +
								pow(n->avg.b - root->avg.b, 2);
		if(diff > tol)
			return 0;
		else return 1;
		}
		return tolLeafCounter(root, n->left, tol) + tolLeafCounter(root, n->right, tol);
}


void twoDtree::clear() {
	clearHelper(root);
}

void twoDtree::clearHelper(Node* node){
	if(node == NULL)
        return;
	clearHelper(node->left);
	clearHelper(node->right);
	delete node;
}


void twoDtree::copy(const twoDtree & orig){
	height = orig.height;
	width = orig.width;
	root = copyHelper(orig.root);
}

twoDtree::Node* twoDtree::copyHelper(Node* node){
	Node* newNode = new Node(node->upLeft, node->lowRight, node->avg);
	if (node->left == NULL && node->right == NULL){
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	newNode->left = copyHelper(node->left);
	newNode->right = copyHelper(node->right);
	return newNode;
}
