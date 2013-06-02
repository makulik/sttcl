/*
 * ITestInnerConcurrentStateInterfaceNoArgs.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef ITESTINNERCONCURRENTSTATEINTERFACENOARGS_H_
#define ITESTINNERCONCURRENTSTATEINTERFACENOARGS_H_

template
    < typename RegionContainerType
    >
struct ITestInnerConcurrentStateInterfaceNoArgs
{
    typedef typename RegionContainerType::RegionBaseType RegionContextType;

    virtual void handleEvent1(RegionContainerType* context, RegionContextType* regionContext) = 0;
    virtual void handleEvent2(RegionContainerType* context, RegionContextType* regionContext) = 0;
    virtual void handleEvent3(RegionContainerType* context, RegionContextType* regionContext) = 0;
    virtual void handleEvent4(RegionContainerType* context, RegionContextType* regionContext) = 0;
};


#endif /* ITESTINNERCONCURRENTSTATEINTERFACENOARGS_H_ */
