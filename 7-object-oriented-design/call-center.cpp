/*
Author: John Furlong
Date: June 12, 2020
Description: Call Center
    Imagine you have a call center with three levels of employees: respondent, manager, and director. An incoming telephone call
    must be first allocated to a respondent who is free. If the respondent can't handle the call, he/she must escalate the call to
    a manager. If the manager is not free or not able to handle it, then the call should be escalated to a director. Design the classes
    and data structures for this problem. Implement a method dispatchCall() which assign a call to the first available employee.
*/
#include <iostream>
#include <vector>
using namespace std;

struct Employee{
    // (1 = respondent, 2 = manager, 3 = director)
    int employeeType;
    bool busy;
    int callNumber;
};

class CallCenter{
    private:
        vector<Employee> respondents;
        vector<Employee> managers;
        vector<Employee> directors;
        vector<int> callQueue;
        int nRespondents, nManagers, nDirectors;
    public:

        CallCenter(int nRespondents, int nManagers, int nDirectors){
            nRespondents = nRespondents; 
            nManagers = nManagers;
            nDirectors = nDirectors;
            for(int i = 0; i < nRespondents; i++){
                Employee respondent;
                respondent.employeeType = 1;
                respondent.busy = false;
                respondent.callNumber = 0;
                respondents.push_back(respondent);
            }
            for(int i = 0; i < nManagers; i++){
                Employee manager;
                manager.employeeType = 2;
                manager.busy = false;
                manager.callNumber = 0;
                managers.push_back(manager);
            }
            for(int i = 0; i < nDirectors; i++){
                Employee director;
                director.employeeType = 3;
                director.busy = false;
                director.callNumber = 0;
                directors.push_back(director);
            }
        }

        // When all operators are busy, calls are queued for the first available assistance
        void callQueuePop(Employee employee){
            employee.busy = true;
            employee.callNumber = callQueue[0];
            callQueue.erase(callQueue.begin());
        }

        // Dispatch a call to the first available employee, escalating up employee ranks.
        void dispatchCall(int callNum){
            bool dispatched = false;

            for(int i = 0; i < nRespondents; i++){
                if(!respondents[i].busy){
                    respondents[i].busy = true;
                    respondents[i].callNumber = callNum;
                }
            }
            for(int i = 0; i < nManagers; i++){
                if(!managers[i].busy){
                    managers[i].busy = true;
                    managers[i].callNumber = callNum;
                }
            }
            for(int i = 0; i < nDirectors; i++){
                if(!directors[i].busy){
                    directors[i].busy = true;
                    directors[i].callNumber = callNum;
                }
            }
            // If all operators are busy, then push the call into the queue
            if(!dispatched)
                callQueue.push_back(callNum);
        }


};