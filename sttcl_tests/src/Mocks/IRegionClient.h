/*
 * IRegionClient.h
 *
 *  Created on: May 20, 2013
 *      Author: user
 */

#ifndef IREGIONCLIENT_H_
#define IREGIONCLIENT_H_

template
    < class RegionImpl
    , class RegionContainer
    , class InnerStateInterface
    >
class IRegionClient
{
public:
    typedef sttcl::StateBase<RegionImpl,InnerStateInterface> InnerStateBaseClass;

    virtual InnerStateBaseClass* getInitialStateImpl() const = 0;
    virtual bool isReadyImpl() const = 0;
    virtual bool initializeImpl(bool force) = 0;
    virtual void finalizeImpl(bool finalizeSubStateMachines) = 0;

    virtual void subStateMachineCompletedImpl() = 0;
    virtual void subStateMachineCompleted() = 0;

    virtual void enterRegionImpl(RegionContainer* context) = 0;
    virtual void exitRegionImpl(RegionContainer* context) = 0;
    virtual void startingRegionThread() = 0;
    virtual void endingRegionThread() = 0;

    virtual ~IRegionClient() {}
};


#endif /* IREGIONCLIENT_H_ */
