#ifndef SHOW_H
#define SHOW_H
#include <iostream>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
class Tester;//this is your tester class, you add your test functions in this class
class Show;
enum STATE {LIGHTON, LIGHTOFF};
enum LIGHTCOLOR {RED,GREEN,BLUE};
const int MINID = 10000;
const int MAXID = 99999;
#define DEFAULT_HEIGHT 0
#define DEFAULT_ID 0
#define DEFAULT_LIGHT RED
#define DEFAULT_STATE LIGHTON
class Drone{
public:
    friend class Show;
    friend class Grader;
    friend class Tester;
    friend class myTester;
    Drone(int id, LIGHTCOLOR type = DEFAULT_LIGHT, STATE state = DEFAULT_STATE)
            :m_id(id),m_type(type), m_state(state) {
        m_left = nullptr;
        m_right = nullptr;
        m_height = DEFAULT_HEIGHT;
    }
    Drone(){
        m_id = DEFAULT_ID;
        m_type = DEFAULT_LIGHT;
        m_state = DEFAULT_STATE;
        m_left = nullptr;
        m_right = nullptr;
        m_height = DEFAULT_HEIGHT;
    }
    int getID() const {return m_id;}
    STATE getState() const {return m_state;}
    string getStateStr() const {
        string text = "";
        switch (m_state)
        {
            case LIGHTOFF:text = "LIGHTOFF";break;
            case LIGHTON:text = "LIGHTON";break;
            default:text = "UNKNOWN";break;
        }
        return text;
    }
    LIGHTCOLOR getType() const {return m_type;}
    string getTypeStr() const {
        string text = "";
        switch (m_type)
        {
            case RED:text = "RED";break;
            case GREEN:text = "GREEN";break;
            case BLUE:text = "BLUE";break;
            default:text = "UNKNOWN";break;
        }
        return text
                ;
    }
    int getHeight() const {return m_height;}
    Drone* getLeft() const {return m_left;}
    Drone* getRight() const {return m_right;}
    void setID(const int id){m_id=id;}
    void setState(STATE state){m_state=state;}
    void setType(LIGHTCOLOR type){m_type=type;}
    void setHeight(int height){m_height=height;}
    void setLeft(Drone* left){m_left=left;}
    void setRight(Drone* right){m_right=right;}
private:
    int m_id;
    LIGHTCOLOR m_type;
    STATE m_state;
    Drone* m_left;//the pointer to the left child in the BST
    Drone* m_right;//the pointer to the right child in the BST
    int m_height;//the height of node in the BST
};
class Show{
public:
    friend class Grader;
    friend class Tester;
  friend class myTester;
    Show();
    ~Show();
    const Show & operator=(const Show & rhs);
    void insert(const Drone& aDrone);
    void clear();
    void remove(int id);
    void dumpTree() const;
    void listDrones() const;
    bool setState(int id, STATE state);
    void removeLightOff();//removes all LIGHTOFF Drones from the tree
    bool findDrone(int id) const;//returns true if the drone is in tree
    int countDrones(LIGHTCOLOR aColor) const;

private:
    Drone* m_root;//the root of the BST

    void dump(Drone* aDrone) const;//helper for recursive traversal
    // ***************************************************
    // Any private helper functions must be declared here!
    // ***************************************************
    void clearRecursive(Drone* aDrone);
    int countRecursive(Drone *aDrone, LIGHTCOLOR aColor, int &tempCount) const;
    void listRecursive(Drone* aDrone) const;
    Drone* removeRecursive(Drone* aDrone, int id);
    void removeLightRecursive(Drone* aDrone);
    int height(Drone* aDrone);
    int maxHeight(int lHeight, int rHeight);
    void updateHeight(Drone* aDrone);
    Drone* rightRotate(Drone* aDrone);
    Drone* leftRotate(Drone* aDrone);
    int balanceFactor(Drone* aDrone);
    Drone* balanceTree(Drone* aDrone);
    Drone* insertRecursive(const Drone& aDrone, Drone* temp);
    Drone* copyAssignment(Drone* aDrone);


};
#endif
