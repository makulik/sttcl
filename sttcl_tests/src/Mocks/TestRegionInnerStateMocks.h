/*
 * TestRegionInnerStateMocks.h
 *
 *  Created on: May 22, 2013
 *      Author: user
 */

#ifndef TESTREGIONINNERSTATEMOCKS_H_
#define TESTREGIONINNERSTATEMOCKS_H_

#include <gmock/gmock.h>
#include <StateMachine.h>

#include "TestStateMocks.h"
#include "ITestInnerConcurrentStateInterfaceNoArgs.h"
#include "ITestInnerConcurrentStateInterfaceWithArgs.h"

template
    < typename RegionContainerType
    , typename RegionType
    >
class TestRegionInnerStateNoArgsMock
: public TestStateMock
      < TestRegionInnerStateNoArgsMock<RegionContainerType,RegionType>
      , RegionType
      , ITestInnerConcurrentStateInterfaceNoArgs<RegionContainerType>
      >
{
public:
    typedef TestStateMock
            < TestRegionInnerStateNoArgsMock<RegionContainerType,RegionType>
            , RegionType
            , ITestInnerConcurrentStateInterfaceNoArgs<RegionContainerType>
            > MockBaseClass;

    TestRegionInnerStateNoArgsMock(const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateNoArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateNoArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateNoArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateNoArgsMock::handleEvent4Call));
    }

    virtual ~TestRegionInnerStateNoArgsMock() {}

    MOCK_METHOD2_T(handleEvent1, void (RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext));
    MOCK_METHOD2_T(handleEvent2, void (RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext));
    MOCK_METHOD2_T(handleEvent3, void (RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext));
    MOCK_METHOD2_T(handleEvent4, void (RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext));

    void doStateChange(RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext, typename RegionType::InnerStateBaseClass* newState)
    {
        RegionType* regionImpl = static_cast<RegionType*>(regionContext);
        MockBaseClass::changeState(regionImpl,newState);
    }

    virtual void handleEvent1Call(RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionInnerStateNoArgsMock
            , "handleEvent1Call( context = " << context <<
              ", regionContext = " << regionContext <<
              ") called ..."
            );
    }

    virtual void handleEvent2Call(RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionInnerStateNoArgsMock
            , "handleEvent2Call( context = " << context <<
              ", regionContext = " << regionContext <<
              ") called ..."
            );
    }

    virtual void handleEvent3Call(RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionInnerStateNoArgsMock
            , "handleEvent3Call( context = " << context <<
              ", regionContext = " << regionContext <<
              ") called ..."
            );
    }

    virtual void handleEvent4Call(RegionContainerType* context, typename RegionContainerType::RegionBaseType* regionContext)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionInnerStateNoArgsMock
            , "handleEvent4Call( context = " << context <<
              ", regionContext = " << regionContext <<
              ") called ..."
            );
    }

};

template
    < typename RegionImpl
    >
class TestRegionInnerStateWithArgsMock
: public TestStateMock<TestRegionInnerStateWithArgsMock<RegionImpl>, RegionImpl, ITestStateInterfaceWithArgs<RegionImpl> >
{
public:
    typedef TestStateMock<TestRegionInnerStateWithArgsMock<RegionImpl>, RegionImpl, ITestStateInterfaceWithArgs<RegionImpl> > MockBaseClass;

    TestRegionInnerStateWithArgsMock(const std::string& id = "<anonymous>", bool enableLogging = false)
    : MockBaseClass(id,enableLogging)
    {
        ON_CALL(*this,handleEvent1(_,_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock::handleEvent1Call));
        ON_CALL(*this,handleEvent2(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock::handleEvent2Call));
        ON_CALL(*this,handleEvent3(_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock::handleEvent3Call));
        ON_CALL(*this,handleEvent4(_,_))
            .WillByDefault(Invoke(this, &TestRegionInnerStateWithArgsMock::handleEvent4Call));
    }

    virtual ~TestRegionInnerStateWithArgsMock() {}

    MOCK_METHOD3_T(handleEvent1, void (RegionImpl* context, const std::string& arg1, int arg2));
    MOCK_METHOD2_T(handleEvent2, void (RegionImpl* context, double arg1));
    MOCK_METHOD1_T(handleEvent3, void (RegionImpl* context));
    MOCK_METHOD2_T(handleEvent4, void (RegionImpl* context, int arg1));

    virtual void handleEvent1Call(RegionImpl* context, const std::string& arg1, int arg2)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionInnerStateWithArgsMock
            , "handleEvent1Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ", arg2 = " << arg2 <<
              ") called ..."
            );
    }

    virtual void handleEvent2Call(RegionImpl* context, double arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionInnerStateWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
    }

    virtual void handleEvent3Call(RegionImpl* context)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionInnerStateWithArgsMock
            , "handleEvent3Call( context = " << context <<  ") called ..."
            );
    }

    virtual void handleEvent4Call(RegionImpl* context, int arg1)
    {
        STTCL_MOCK_LOGDEBUG
            ( TestRegionInnerStateWithArgsMock
            , "handleEvent2Call( context = " << context <<
              ", arg1 = " << arg1 <<
              ") called ..."
            );
    }

};
#endif /* TESTREGIONINNERSTATEMOCKS_H_ */
