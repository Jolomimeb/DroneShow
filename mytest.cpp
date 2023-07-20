/*****************************************
** File:    mytest.cpp
** Project: CMSC 341 Project 2, Spring 2023
** Author:  Oritsejolomisan Mebaghanje
** Date:    03/28/23
** E-mail:  xz94254@umbc.edu
**
** This file contains the program for mytest.cpp.
**
**
***********************************************/

#include "show.h"
using namespace std;

#include <random>

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution
};



class myTester{
public:
    bool testInsertNormal();
    bool testInsertEdge();
    bool testInsertError();
    bool testInsertBalance();

    bool testRemoveNormal();
    bool testRemoveEdge();
    bool testRemoveError();
    bool testRemoveBalance();

    bool testRemoveLightOff();
    bool testCountDrones();

    bool testFindDroneNormal();
    bool testFindDroneError();

    bool testAssignmentOperatorNormal();
    bool testAssignmentOperatorError();

    void testRemovalOperation();
    void testInsertionOperation();
    double sampleTimeMeasurement(Show & aShow, int tempArray[], int arraySize);

    int balanceFactor(Drone* aDrone);
    int height(Drone* aDrone);
    bool checkBalance(Drone* aDrone);

private:

};

int main(){
    myTester Tester1;

    //returns true
    if(Tester1.testInsertNormal()){
        cout << "Test Insert Normal returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Insert normal returned false" << endl;
    }

    //returns true
    if(Tester1.testInsertEdge()){
        cout << "Test Insert Edge returned true, works correctly for Edge case" << endl;
    }
    else{
        cout << "Test Insert Edge returned false" << endl;
    }
    //returns false
    if(Tester1.testInsertError()){
        cout << "Test Insert Error returned true" << endl;
    }
    else{
        cout << "Test Insert Error returned false, works correctly for error case" << endl;
    }

    //returns false
    if(Tester1.testRemoveNormal()){
        cout << "Test Remove Normal returned true" << endl;
    }
    else{
        cout << "Test Remove normal returned false, works correctly for normal case" << endl;
    }

    //returns false
    if(Tester1.testRemoveEdge()){
        cout << "Test Remove Edge returned true" << endl;
    }
    else{
        cout << "Test Remove Edge returned false, works correctly for Edge case" << endl;
    }

    //returns false
    if(Tester1.testRemoveError()){
        cout << "Test Remove Error returned true" << endl;
    }
    else{
        cout << "Test Remove Error returned false, works correctly for error case" << endl;
    }

    //returns true
    if(Tester1.testRemoveLightOff()){
        cout << "Test Remove Light off returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Remove Light off returned false" << endl;
    }
    
    //returns true
    if(Tester1.testCountDrones()){
        cout << "Test Count Drones returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Count Drones returned false" << endl;
    }
    

    //returns true
    if(Tester1.testFindDroneNormal()){
        cout << "Test find drone normal returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test find drone normal returned false" << endl;
    }

    //returns false
    if(Tester1.testFindDroneError()){
        cout << "Test find drone error returned true" << endl;
    }
    else{
        cout << "Test find drone error returned false, works correctly for error case" << endl;
    }

    //returns true
    if(Tester1.testAssignmentOperatorNormal()){
        cout << "Test assignment operator returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test assignment operator returned false" << endl;
    }

    //returns true;
    if(Tester1.testAssignmentOperatorError()){
        cout << "Test assignment operator Error returned true, works correctly for error case" << endl;
    }
    else{
        cout << "Test assignment operator Error returned false" << endl;
    }
    
    //returns true
    if(Tester1.testInsertBalance()){
        cout << "Test Insert balance returned true, works correctly" << endl;
    }
    else{
        cout << "Test Insert balance returned false" << endl;
    }

    //returns true
    if(Tester1.testRemoveBalance()){
        cout << "Test Remove balance returned true, works correctly" << endl;
    }
    else{
        cout << "Test Remove balance returned false" << endl;
    }
    
    Tester1.testInsertionOperation();
    
    Tester1.testRemovalOperation();

        
    return 0;
}

bool myTester::testInsertNormal() {
    //inserting 15 drones into the tree
    bool result = false;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int teamSize = 15;
    for(int i=0;i<teamSize;i++){
        int ID = idGen.getRandNum();
        Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
        //checks if the drone was successfully inserted and sets result if it was
        if (show.findDrone(ID) == true){
            result = true;
        }
    }
    /*
    cout << "\nDump after inserting " << teamSize << " nodes:\n\n";
    show.dumpTree();
    cout << "\n\nList of Drones after inserting " << teamSize << " nodes:\n";
    show.listDrones();
    cout << endl;
    */
    return result;
}

bool myTester::testInsertEdge() {
    //inserting a drone into an empty tree
    bool result = false;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int ID = idGen.getRandNum();
    Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    show.insert(drone);
    //checks if the drone was successfully inserted and sets result if it was
    if (show.findDrone(ID) == true){
        result = true;
    }

    return result;
}

bool myTester::testInsertError() {
    //inserting a drone with the ID that is outside the range of min ID and max ID meant to return false
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    int badID = 500;

    Show show;
    int teamSize = 10;
    for(int i=0;i<teamSize;i++){
        int ID = idGen.getRandNum();
        Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
    }
    //adding a drone to the tree that has an ID less than minID
    Drone drone2(badID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    show.insert(drone2);
    //checks if the drone was successfully inserted and sets result if it was
    result = result and show.findDrone(badID);

    return result;
}

bool myTester::testInsertBalance() {
  //checks if the tree is balance after insertion
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int teamSize = 300;
    int ID = 0;

    for(int i=0;i<teamSize;i++){
        ID = idGen.getRandNum();
        Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
    }
    bool balance = checkBalance(show.m_root);

    return balance;
}

bool myTester::testRemoveNormal(){
    //inserting a drone into an empty tree
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int ID = 10500;
    int ID2 = 11000;
    int ID3 = 15000;
    Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone2(ID2,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone3(ID3,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    show.insert(drone);
    show.insert(drone2);
    show.insert(drone3);

    //removing a drone from the tree
    show.remove(ID3);

    //checks if the drone with ID was successfully removed and sets result if it was
    result = result and show.findDrone(ID3);

    return result;
}

bool myTester::testRemoveEdge(){
    //edge case removing the root of the tree
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int ID = 10500;
    int ID2 = 11000;
    int ID3 = 15000;
    int ID4 = 70000;
    Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone2(ID2,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone3(ID3,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone4(ID4,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));

    show.insert(drone);
    show.insert(drone2);
    show.insert(drone3);
    show.insert(drone4);

    //removing root drone from the tree
    show.remove(ID2);

    //checks if the drone with ID was successfully removed and sets result if it was
    result = result and show.findDrone(ID2);

    return result;
}

bool myTester::testRemoveError(){
    //removing drone that does not exist in tree
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int ID = 10500;
    int ID2 = 11000;
    int ID3 = 15000;
    int ID4 = 70000;
    int wrongID = 85000;
    Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone2(ID2,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone3(ID3,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone4(ID4,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));

    show.insert(drone);
    show.insert(drone2);
    show.insert(drone3);
    show.insert(drone4);

    //removing root drone from the tree
    show.remove(wrongID);
    //checks if the drone with ID was not found and sets result to false
    result = result and show.findDrone(wrongID);

    return result;
}

bool myTester::testRemoveBalance(){
  //tests if the tree is balanced after removing 150 drones from a tree containing 300 drones
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int teamSize = 300;
    int ID = 0;
    int arraySize = 150;
    //array to store the ID's to remove
    int newArray[arraySize];

    for(int i=0;i<teamSize;i++){
        ID = idGen.getRandNum();
        Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
        for (int j = 0; j < arraySize; j++){
            newArray[j] = ID;
        }
    }
    //removes the drones with ID from the show
    for (int k = 0; k < arraySize; k++){
        show.remove(newArray[k]);
    }

    bool balance = checkBalance(show.m_root);

    return balance;
}

bool myTester::testRemoveLightOff() {
  //sets the state of a drone to light off and removes it from the tree
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int ID = 10500;
    int ID2 = 11000;
    int ID3 = 15000;
    int ID4 = 70000;
    Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone2(ID2,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone3(ID3, static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone4(ID4,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));

    show.insert(drone);
    show.insert(drone2);
    show.insert(drone3);
    show.insert(drone4);

    show.setState(ID3, LIGHTOFF);
    show.removeLightOff();

    return result;
}

bool myTester::testCountDrones() {
    //inserting 15 drones into the tree
    bool result = false;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    int NUM_OF_GREEN = 15;

    Show show;
    int teamSize = 15;
    for(int i=0;i<teamSize;i++){
        int ID = idGen.getRandNum();
        Drone drone(ID,DEFAULT_LIGHT);
        show.insert(drone);
    }
    int counter = show.countDrones(DEFAULT_LIGHT);
    if (counter == NUM_OF_GREEN){
        result = true;
    }

    return result;
}

bool myTester::testFindDroneNormal() {
    //drone to be found is in the tree and valid ID
    bool result = false;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int ID = 10500;
    int ID2 = 11000;
    int ID3 = 15000;
    int ID4 = 70000;
    Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone2(ID2,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone3(ID3,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone4(ID4,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));

    show.insert(drone);
    show.insert(drone2);
    show.insert(drone3);
    show.insert(drone4);
    //checks if the drone was found
    if(show.findDrone(ID4)){
        result = true;
    }


    return result;
}

bool myTester::testFindDroneError() {
    //finding drone with ID that does not exist
    bool result = true;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    int wrongID = 100;

    Show show;
    int ID = 10500;
    int ID2 = 11000;
    int ID3 = 15000;
    int ID4 = 70000;
    Drone drone(ID,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone2(ID2,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone3(ID3,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
    Drone drone4(ID4,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));

    show.insert(drone);
    show.insert(drone2);
    show.insert(drone3);
    show.insert(drone4);
    //checks if the drone was not found
    if (show.findDrone(wrongID) == false){
        result = false;
    }

    return result;
}

bool myTester::testAssignmentOperatorNormal() {
    bool result = false;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;
    int ID = 10500;
    int ID2 = 11000;
    int ID3 = 15000;
    int ID4 = 70000;
    Drone drone(ID,DEFAULT_LIGHT);
    Drone drone2(ID2,DEFAULT_LIGHT);
    Drone drone3(ID3,DEFAULT_LIGHT);
    Drone drone4(ID4,DEFAULT_LIGHT);

    show.insert(drone);
    show.insert(drone2);
    show.insert(drone3);
    show.insert(drone4);

    //create new show object and perform assignment
    Show newShow;
    newShow = show;

    //counts the number of drone in newShow and checks if it is the same as that in show
    if (newShow.countDrones(DEFAULT_LIGHT) == show.countDrones(DEFAULT_LIGHT)){
        result = true;
    }

    return result;
}

bool myTester::testAssignmentOperatorError() {
    //assigning to empty object
    bool result = false;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show;

    //create new show object and perform assignment
    Show newShow;
    newShow = show;

    //counts the number of drone in newShow and checks if it is the same as that in show
    if (newShow.countDrones(DEFAULT_LIGHT) == show.countDrones(DEFAULT_LIGHT)){
        result = true;
    }

    return result;
}

double myTester::sampleTimeMeasurement(Show & aShow, int tempArray[], int arraySize){
    double T = 0.0;//stores running times
    clock_t start, stop;//stores the clock ticks while running the program
    start = clock();
    // the algorithm to be measured
    for (int j=0;j<arraySize;j++){
        aShow.findDrone(tempArray[j]);
    }
    stop = clock();
    T = stop - start;//number of clock ticks the algorithm took
    double measureTime = T/CLOCKS_PER_SEC;//time in seconds
    return measureTime;
}

void myTester::testRemovalOperation() {
    myTester Tester;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // there are three colors
    //tree with 1000 nodes
    double tree1Time = 0.0;
    //tree with 2000 nodes
    double tree2Time = 0.0;

    double actualRatio = 0.0;
    double absError = 0.4;
    double expectedRatio = 1.1;
    double leastBound = expectedRatio - absError;
    double greatestBound = expectedRatio + absError;

    //first tree
    Show show;
    int size = 1000;
    int tempIDs[1001] = {0};
    int id = 0;
    for(int i=0;i<size;i++){
        id = idGen.getRandNum();
        tempIDs[i] = id;//we store this ID for later use
        Drone drone(id,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
	show.remove(tempIDs[i]);
    }
    tree1Time = Tester.sampleTimeMeasurement(show, tempIDs, size);

    //second tree
    Show show2;
    int size2 = 1000;
    int tempIDs2[1001] = {0};
    int id2 = 0;
    for(int i=0;i<size2;i++){
        id2 = idGen.getRandNum();
        tempIDs2[i] = id2;//we store this ID for later use
        Drone drone(id2,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show2.insert(drone);
	show2.remove(tempIDs2[i]);
    }
    tree2Time = Tester.sampleTimeMeasurement(show2, tempIDs2, size2);

    //calculate the actualRatio
    actualRatio = tree2Time / tree1Time;

    if (actualRatio > leastBound and actualRatio < greatestBound){
        cout << "Removal performs in O(log n) with performance time of: " << actualRatio << endl;
    }
}

void myTester::testInsertionOperation() {
    myTester Tester;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // there are three colors
    //tree with 1000 nodes
    double tree1Time = 0.0;
    //tree with 2000 nodes
    double tree2Time = 0.0;
    double actualRatio = 0.0;
    double absError = 0.4;
    double expectedRatio = 1.1;
    double leastBound = expectedRatio - absError;
    double greatestBound = expectedRatio + absError;

    //first tree
    Show show;
    int size = 1000;
    int tempIDs[1001] = {0};
    int id = 0;
    for(int i=0;i<size;i++){
        id = idGen.getRandNum();
        tempIDs[i] = id;//we store this ID for later use
        Drone drone(id,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show.insert(drone);
    }
    tree1Time = Tester.sampleTimeMeasurement(show, tempIDs, size);

    //second tree
    Show show2;
    int size2 = 1000;
    int tempIDs2[1001] = {0};
    int id2 = 0;
    for(int i=0;i<size2;i++){
        id2 = idGen.getRandNum();
        tempIDs2[i] = id2;//we store this ID for later use
        Drone drone(id2,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show2.insert(drone);
    }
    tree2Time = Tester.sampleTimeMeasurement(show2, tempIDs2, size2);

    //calculate the actualRatio
    actualRatio = tree2Time / tree1Time;

    if (actualRatio > leastBound and actualRatio < greatestBound){
        cout << "Insertion performs in O(log n) with performance time of: " << actualRatio << endl;
    }


}


int myTester::height(Drone* aDrone){
    if (aDrone == nullptr){
        return -1;
    }
    else{
        return aDrone->m_height;
    }
}

int myTester::balanceFactor(Drone* aDrone){
    if (aDrone == nullptr){
        return 0;
    }
    return height(aDrone->m_left) - height(aDrone->m_right);
}

bool myTester::checkBalance(Drone* aDrone){
    if (aDrone == nullptr){
        return true;
    }
    int bf = balanceFactor(aDrone);
    if ((bf < -1) or (bf > 1)){
        return false;
    }
    checkBalance(aDrone->m_left);
    checkBalance(aDrone->m_right);
    return true;
}
