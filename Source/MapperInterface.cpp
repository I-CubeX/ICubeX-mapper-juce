/*
 ==============================================================================
 
 MapperInterface.cpp
 Created: 10 Apr 2015 12:22:55pm
 Author:  johnty
 
 ==============================================================================
 */

#include "MapperInterface.h"
#include "ICubeXInteface.h"

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
        myMapperOut->add_output(signame.toStdString(), 1, 'i', "raw", &min, &max);
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
            
            //mapper 0.3 convergent5 branch:
            for (auto const &sig : myMapperOut->signals(MAPPER_DIR_OUTGOING))
            {
                int sensorVal = mySigVals.at(idx);
                //DBG("signame = " + sig.name());
                //a bit convoluted, but we need Device::signals() to return non-const
                // for update to work. TODO: chat to Joe about this.
                myMapperOut->signal(sig.name()).update(sensorVal);
                
            }
            
            //mapper 0.3 master:
            /*
            for (mapper::Signal::Iterator it = myMapperOut->outputs().begin(); it != myMapperOut->outputs().end(); ++it) {
                //DBG("updating " + (*it).full_name());
                //there is only one in this case...]
                threadLock.enter();
                int sensorVal = mySigVals.at(idx);
                threadLock.exit();
                (*it).update(sensorVal);
                //(*it).update(0.0f);
            }*/
            idx++;
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