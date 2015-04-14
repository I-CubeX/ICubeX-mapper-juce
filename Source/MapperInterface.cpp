/*
  ==============================================================================

    MapperInterface.cpp
    Created: 10 Apr 2015 12:22:55pm
    Author:  johnty

  ==============================================================================
*/

#include "MapperInterface.h"

MapperInterface::MapperInterface() : Thread("MapperInterfaceThread")
{
    myMapperOut = new mapper::Device("ICubeX");
    float min = 0.0;
    float max = 1.0;
    //myMapper->add_output("/testSig1", 1, 'i', "num", 0, 0);
    myMapperOut->add_output("/testSig", 1, 'f', "Hz", &min, &max);
    
    
    
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
        
        if (myMapperOut != NULL)
        {
            myMapperOut->poll();
            for (mapper::Signal::Iterator it = myMapperOut->outputs().begin(); it != myMapperOut->outputs().end(); ++it) {
                //DBG("updating " + (*it).full_name());
                (*it).update(0.0f);
            }
            sleep(1000); //lets not be too hasty here...
            
        }
    }
    if (myMapperOut != NULL) {
        delete myMapperOut;
    }
    DBG("ending mapper interface thread...\n");
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