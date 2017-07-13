/*
 ==============================================================================
 
 MapperInterface.cpp
 Created: 10 Apr 2015 12:22:55pm
 Author:  johnty
 
 ==============================================================================
 */

#include "MapperInterface.h"
#include "ICubeXInterface/ICubeXInteface.h"

MapperInterface::MapperInterface() : Thread("MapperInterfaceThread")
{
    myMapperOut = new mapper::Device("ICubeX");
    //int min[8] = {  0,   0,   0,   0,   0,   0,   0,   0};
    //int max[8] = {127, 127, 127, 127, 127, 127, 127, 127};
    int min = 0;
    int max = 127;
    //myMapperOut->add_output("/ICubeXSensors", kNUM_ICUBEX_SENSORS, 'i', "raw", &min, &max);
    
    mySigVals.reserve(kNUM_ICUBEX_SENSORS);
    for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
    {
        String signame = "/sensor" + String(i);
        myMapperOut->add_output_signal(signame.toStdString(), 1, 'i', "raw", &min, &max);
        mySigVals.push_back(0);
    }
    //myMapperOut->add_input("/testLoopback", 1, 'f', "Hz", &min, &max, inputHandler, 0);
    
    
    
    
    //    pt2Member = &MapperInterface::DoIt;
    //    int result = (*this.*pt2Member)(12, 'a', 'b');
    //    DBG("DoIT res = " + String(result));
}

MapperInterface::~MapperInterface()
{
    DBG("stopping thread...\n");
    int res = stopThread(2000);
    DBG("thead stopped: " + String(res));
}

void MapperInterface::run()
{
    DBG("starting mapper interface thread...\n");
    while (!threadShouldExit())
    {
        //do stuff here...
        int idx=0;
        if (myMapperOut != NULL)
        {
            myMapperOut->poll();
            for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
            {
                String signame = "/sensor" + String(i);
                int sensorVal = mySigVals.at(idx);
                
                //note: we assume this signal exists, which may not be the case!
                myMapperOut->signal(signame.toStdString()).update(sensorVal);
            }
            
            sleep(50); //lets not be too hasty here...
            
        }
    }
    if (myMapperOut != NULL) {
        delete myMapperOut;
    }
    DBG("ending mapper interface thread...\n");
}

void MapperInterface::updateVals(std::vector<int> newVals)
{
    threadLock.enter();
    mySigVals = newVals;
    threadLock.exit();
}

//void MapperInterface::MapperInputHandler(mapper::Signal msig,
//                                         int instance_id,
//                                         void *value,
//                                         int count,
//                                         mapper::Timetag tt)
//{
//    DBG("input received\n");
//}
//
//void MapperInterface::inputHandler(mapper::Signal msig,
//                                   mapper::Signal::Props props,
//                                   int instance_id,
//                                   void *value,
//                                   int count,
//                                   mapper::Timetag tt) {
//    DBG("static input handler");
//}
