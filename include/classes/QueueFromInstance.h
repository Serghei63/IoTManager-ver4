#pragma once
#include "classes/QueueInst.h"
#include "Global.h"
#include <queue>
#include <iostream>

using namespace std;

class QueueFromInstance;

class QueueFromInstance {
   public:
    QueueFromInstance();
    ~QueueFromInstance();

    void push(QueueInstance instance);
    void pop();
    QueueInstance front();

   private:
    queue<QueueInstance> queue1;
};

extern QueueFromInstance* myQueue;