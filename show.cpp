#include "show.h"
Show::Show(){
    //sets the root to nullptr
    m_root = nullptr;
}

Show::~Show(){
    //calls the clear function
    clear();
}

void Show::insert(const Drone& aDrone){
    //checks if the drone already exists or is valid
    if ((aDrone.m_id < MINID or aDrone.m_id > MAXID) or findDrone(aDrone.m_id)){
        return;
    }
    //calls the recursive insert function
    m_root = insertRecursive(aDrone, m_root);
}
Drone* Show::insertRecursive(const Drone& aDrone, Drone* temp){

    //checks if the root of the tree is empty and then sets it to the new drone
    if (temp == nullptr){
        Drone* toInsert = new Drone(aDrone);
        return toInsert;
    }

        //checks if the ID drone to insert is less than the roots ID
    else if (aDrone.m_id < temp->m_id){
        temp->m_left = insertRecursive(aDrone, temp->m_left);

    }
        //checks if the ID drone to insert is greater than the roots ID
    else if (aDrone.m_id > temp->m_id){
        temp->m_right = insertRecursive(aDrone, temp->m_right);

    }
    //updates the height and balances the tree
    updateHeight(temp);
    temp = balanceTree(temp);
    return temp;
}


void Show::clear(){
    //calls the recursive clear function
    clearRecursive(m_root);
}
void Show::clearRecursive(Drone* aDrone){
    //deletes the drones
    if (aDrone != nullptr){
        clearRecursive(aDrone->m_left);
        clearRecursive(aDrone->m_right);
        delete aDrone;
    }
}


void Show::remove(int id){
    //sets the root to the recursive function
    m_root = removeRecursive(m_root, id);
}
Drone* Show::removeRecursive(Drone* aDrone, int id){
    //checks if the tree is null
    if (aDrone == nullptr){
        return aDrone;
    }

    //checks if the id is less than the current id
    if (id < aDrone->m_id){
        //recurse left
        aDrone->m_left = removeRecursive(aDrone->m_left, id);
    }
        //checks if the id is less than the current id
    else if (id > aDrone->m_id){
        //recurse right
        aDrone->m_right = removeRecursive(aDrone->m_right, id);
    }

    else if (id == aDrone->m_id){
        //case with no child
        if ((aDrone->m_left == nullptr) and (aDrone->m_right == nullptr)){
            //creates temp that point to aDrone and deletes the drone
            Drone* temp = aDrone;
            delete temp;
            return nullptr;
        }

            //case with one child
        else if ((aDrone->m_left == nullptr) or (aDrone->m_right == nullptr)) {
            //checks if the left of the drone is null
            if (aDrone->m_left == nullptr) {
                Drone* tempRight = aDrone->m_right;
                delete aDrone;
                return tempRight;
                //checks if the right of the drone is null
            } else if (aDrone->m_right == nullptr) {
                Drone* tempLeft = aDrone->m_left;
                delete aDrone;
                return tempLeft;
            }

        }
            //case with two children find the inorder successor and replace the node with it
        else if ((aDrone->m_left != nullptr) and (aDrone->m_right != nullptr)){
            Drone* replaceDrone = aDrone->m_right;
            while (replaceDrone->m_left != nullptr) {
                replaceDrone = replaceDrone->m_left;
            }
            aDrone->m_id = replaceDrone->m_id;
            aDrone->m_right = removeRecursive(aDrone->m_right, replaceDrone->m_id);
            return aDrone;
        }
    }
    //updates height and balances tree
    updateHeight(aDrone);
    balanceTree(aDrone);
    return aDrone;
}



void Show::dumpTree() const {dump(m_root);}
void Show::dump(Drone* aDrone) const{
    if (aDrone != nullptr){
        cout << "(";
        dump(aDrone->m_left);//first visit the left child
        cout << aDrone->m_id << ":" << aDrone->m_height;//second visit the node itself
        dump(aDrone->m_right);//third visit the right child
        cout << ")";
    }
}


void Show::listDrones() const {
    //calls the recursive list drone function
    listRecursive(m_root);
}
void Show::listRecursive(Drone* aDrone) const{
    //displays the drone inorder
    if (aDrone != nullptr){
        listRecursive(aDrone->m_left);
        cout << aDrone->m_id << ":" << aDrone->getStateStr() << ":" << aDrone->getTypeStr() << endl;
        listRecursive((aDrone->m_right));
    }
}


bool Show::setState(int id, STATE state){
    Drone* tempDrone = m_root;
    while (tempDrone != nullptr){
        //checks if the drone was found
        if (findDrone(id) and tempDrone->m_id == id){
            //sets the m_state to state
            tempDrone->m_state = state;
            return true;
        }
        //iterate to the left if the id is less than current id in temp
        else if(id < tempDrone->m_id){
            tempDrone = tempDrone->m_left;
        }
        //iterate to the right if the id is less than current id in temp
        else if(id > tempDrone->m_id){
            tempDrone = tempDrone->m_right;
        }
    }
    return false;
}


void Show::removeLightOff(){
    //calls the recursive remove light function
    removeLightRecursive(m_root);
}
void Show::removeLightRecursive(Drone* aDrone){
    //check if the tree is empty
    if (aDrone == nullptr){
        return;
    }
    //checks if the state is off and calls the remove function on the drone that has lightOff state
    if (aDrone->m_state == LIGHTOFF){
        int tempId = aDrone->m_id;
        remove(tempId);
    }
    else{
        removeLightRecursive(aDrone->m_left);
        removeLightRecursive(aDrone->m_right);
    }
}

bool Show::findDrone(int id) const {
    //create temp tree
    Drone* temp = m_root;
    //traverse the tree
    while (temp != nullptr){
        //checks if the id matches the given id
        if (temp->m_id == id){
            return true;
        }
        //iterate to the left if the id is less than current id in temp
        else if(id < temp->m_id){
            temp = temp->m_left;
        }
        //iterate to the right if the id is less than current id in temp
        else if(id > temp->m_id){
            temp = temp->m_right;
        }
    }
    return false;
}

const Show & Show::operator=(const Show & rhs){
    //checks for self assignment
    if (&rhs != this){
        if (m_root != nullptr){
            clear();
        }
        m_root = copyAssignment(rhs.m_root);
    }
    return *this;
}
Drone* Show::copyAssignment(Drone* aDrone){
    //checks if aDrone is null
    if (aDrone == nullptr){
        return nullptr;
    }
    //performs the assignment
    Drone* newDrone = new Drone(aDrone->m_id);
    newDrone->m_height = aDrone->m_height;
    newDrone->m_left = copyAssignment(aDrone->m_left);
    newDrone->m_right = copyAssignment(aDrone->m_right);
    return newDrone;
}


int Show::countDrones(LIGHTCOLOR aColor) const{
    int tempCount = 0;
    //calls the recursive count drone function
    int count = countRecursive(m_root, aColor, tempCount);
    return count;
}
int Show::countRecursive(Drone *aDrone, LIGHTCOLOR aColor, int &counter) const{
    //checks to make sure tree isn't empty
    if (aDrone != nullptr){
        //checks if the color matches
        if (aDrone->getType() == aColor){
            counter++;
        }
        //recursive function calls itself to the left and right
        countRecursive(aDrone->m_left, aColor, counter);
        countRecursive(aDrone->m_right, aColor, counter);
    }
    return counter;
}


//returns the height of tree
int Show::height(Drone* aDrone){
    if (aDrone == nullptr){
        return -1;
    }
    else{
        return aDrone->m_height;
    }
}

//returns the max height
int Show::maxHeight(int lHeight, int rHeight){
    if (lHeight > rHeight){
        return lHeight;
    }
    else{
        return rHeight;
    }
}

//updates the height
void Show::updateHeight(Drone* aDrone){
    if (aDrone == nullptr){
        return;
    }
    int leftHeight = -1;
    int rightHeight = -1;

    if (aDrone->m_left != nullptr){
        leftHeight = aDrone->m_left->m_height;
    }
    if (aDrone->m_right != nullptr){
        rightHeight = aDrone->m_right->m_height;
    }
    aDrone->m_height = maxHeight(leftHeight, rightHeight);
    aDrone->m_height = aDrone->m_height + 1;

}

//performs the right rotation
Drone* Show::rightRotate(Drone* aDrone){
    Drone* left1 = aDrone->m_left;
    Drone* left2 = left1->m_right;

    left1->m_right = aDrone;
    aDrone->m_left = left2;

    //updates height of the drone and subtree
    updateHeight(aDrone);
    updateHeight(left1);
    return left1;

}

//performs the left rotation
Drone* Show::leftRotate(Drone* aDrone){
    Drone* right1 = aDrone->m_right;
    Drone* right2 = right1->m_left;

    right1->m_left = aDrone;
    aDrone->m_right = right2;

    //updates height of the drone and subtree
    updateHeight(aDrone);
    updateHeight(right1);

    return right1;

}

//returns the balance factor
int Show::balanceFactor(Drone* aDrone){
    if (aDrone == nullptr){
        return 0;
    }
    return height(aDrone->m_left) - height(aDrone->m_right);
}

//balances the tree
Drone* Show::balanceTree(Drone* aDrone){
    if (aDrone == nullptr){
        return nullptr;
    }
    int bFactor = balanceFactor(aDrone);

    //right rotation
    if (bFactor > 1){
        //left - right rotation
        if (balanceFactor(aDrone->m_left) < 0){
            aDrone->m_left = leftRotate(aDrone->m_left);
        }
        return rightRotate(aDrone);
    }
    //left rotation
    if (bFactor < -1){
        //right - left rotate
        if (balanceFactor(aDrone->m_right) > 0){
            aDrone->m_right = rightRotate(aDrone->m_right);
        }
        return leftRotate(aDrone);
    }
    return aDrone;
}
