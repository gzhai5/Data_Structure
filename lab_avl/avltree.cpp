/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;



template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * rht = t -> right;
    t -> right = rht -> left;
    rht -> left = t;
    t -> height = max(heightOrNeg1(t -> left),heightOrNeg1(t -> right)) + 1;
    t = rht;
    t -> height = max(heightOrNeg1(t -> left),heightOrNeg1(t -> right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * lft = t -> left;
    t -> left = lft -> right;
    lft -> right = t;
    t -> height = max(heightOrNeg1(t -> left),heightOrNeg1(t -> right)) + 1;
    t = lft;
    t -> height = max(heightOrNeg1(t -> left),heightOrNeg1(t -> right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t -> right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);    //calculate the blance factor
    if (balance == -2){                                                              //check if the node is current not in balance
        int lft_balance = heightOrNeg1(subtree -> left -> right) - heightOrNeg1(subtree -> left -> left);
        if (lft_balance == -1){
            rotateRight(subtree);
        }
        else{
            rotateLeftRight(subtree);
        }
    }
    else if (balance == 2){
        int rht_balance = heightOrNeg1(subtree -> right -> right) - heightOrNeg1(subtree -> right -> left);
        if (rht_balance == 1){
            rotateLeft(subtree);
        }
        else{
            rotateRightLeft(subtree);
        }
    }
    subtree -> height = max(heightOrNeg1(subtree -> left), heightOrNeg1(subtree -> right)) + 1;
}


template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL){
        subtree = new Node(key, value);
    }
    else if (key < subtree -> key){
        insert(subtree -> left, key, value);
    }
    else if (key > subtree -> key){
        insert(subtree -> right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key){
        // your code here
        remove(subtree -> left, key);
        rebalance(subtree);
    } 
    else if (key > subtree->key){
        // your code here
        remove(subtree -> right, key);
        rebalance(subtree);
    } 
    else{
        if (subtree->left == NULL && subtree->right == NULL){
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } 
        else if (subtree->left != NULL && subtree->right != NULL){
            /* two-child remove */
            // your code here
            Node * lft = subtree -> left;
            Node * tmp;
            while (lft -> right != NULL){
                tmp = lft;
                lft = lft -> right;
            }
            swap(subtree, lft);
            delete lft;
            tmp -> right = NULL;
        } 
        else{
            /* one-child remove */
            // your code here
            Node * tmp2 = subtree;
            subtree = subtree->left ? subtree->left : subtree->right;
            delete tmp2;
        }
        // your code here
    }

}
