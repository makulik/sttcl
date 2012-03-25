var NAVTREE =
[
  [ "sttcl", "index.html", [
    [ "STTCL state machine template class framework", "index.html", null ],
    [ "Related Pages", "pages.html", [
      [ "Usage of the STTCL state machine template class framework", "usage_page.html", null ],
      [ "Mapping of the state diagram notation elements", "uml2gof_page.html", null ],
      [ "Configuring the STTCL library for a specific OS/build environment", "sttcl_config_page.html", null ],
      [ "Todo List", "todo.html", null ]
    ] ],
    [ "Class List", "annotated.html", [
      [ "sttcl::ActiveState< StateImpl, StateMachineImpl, IState, StateThreadType, TimeDurationType, EndDoActionSemaphoreType, ActiveStateMutexType >", "classsttcl_1_1_active_state.html", null ],
      [ "sttcl::internal::AutoLocker< Lockable >", "classsttcl_1_1internal_1_1_auto_locker.html", null ],
      [ "sttcl::ClassMethodThread< T, UserArgs, ThreadImpl, MutexImpl >", "classsttcl_1_1_class_method_thread.html", null ],
      [ "sttcl::CompositeState< CompositeStateImpl, StateMachineImpl, IInnerState, HistoryType, StateBaseImpl, StateMachineBaseImpl >", "classsttcl_1_1_composite_state.html", null ],
      [ "sttcl::internal::CompositeStateBase< InnerStateType >", "classsttcl_1_1internal_1_1_composite_state_base.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< HistoryType, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< CompositeStateHistoryType::Deep, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector_3_01_composite_state_history_type_1_1_411e935fc31fe5a2b2f2b11c5f685412.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< CompositeStateHistoryType::Shallow, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector_3_01_composite_state_history_type_1_1_982b593242060720f9ba414a3529c73e.html", null ],
      [ "sttcl::internal::CompositeStateBaseWithDeepHistory< InnerStateType >", "classsttcl_1_1internal_1_1_composite_state_base_with_deep_history.html", null ],
      [ "sttcl::internal::CompositeStateBaseWithShallowHistory< InnerStateType >", "classsttcl_1_1internal_1_1_composite_state_base_with_shallow_history.html", null ],
      [ "sttcl::CompositeStateHistoryType", "structsttcl_1_1_composite_state_history_type.html", null ],
      [ "sttcl::internal::ConcurrentCompositeBaseImplementationSelector< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "structsttcl_1_1internal_1_1_concurrent_composite_base_implementation_selector.html", null ],
      [ "sttcl::internal::ConcurrentCompositeBaseImplementationSelector< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, void, StateBaseImpl >", "structsttcl_1_1internal_1_1_concurrent_composite_base_implementation_selector_3_01_composite_sta8d142f762a15d3fea340a63ac0dbad6c.html", null ],
      [ "sttcl::ConcurrentCompositeState< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1_concurrent_composite_state.html", null ],
      [ "sttcl::internal::ConcurrentCompositeStateBase< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1internal_1_1_concurrent_composite_state_base.html", null ],
      [ "sttcl::internal::ConcurrentCompositeStateWithEventArgs< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1internal_1_1_concurrent_composite_state_with_event_args.html", null ],
      [ "sttcl::internal::ConcurrentCompositeStateWithoutEventArgs< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, StateBaseImpl >", "classsttcl_1_1internal_1_1_concurrent_composite_state_without_event_args.html", null ],
      [ "sttcl::internal::DispatchedEvent< StateMachineImpl, IInnerState, EventArgs >", "structsttcl_1_1internal_1_1_dispatched_event.html", null ],
      [ "sttcl::internal::EventArgsInterfaceSelector< StateMachineImpl, StateInterface, IInnerState, EventArgsType >", "structsttcl_1_1internal_1_1_event_args_interface_selector.html", null ],
      [ "sttcl::internal::EventArgsInterfaceSelector< StateMachineImpl, StateInterface, IInnerState, void >", "structsttcl_1_1internal_1_1_event_args_interface_selector_3_01_state_machine_impl_00_01_state_in1736ea8797feccfc9c96c455ed8619ab.html", null ],
      [ "sttcl::EventQueue< T, TimeDurationType, SemaphoreType, MutexType, InnerQueueType >", "classsttcl_1_1_event_queue.html", null ],
      [ "sttcl::internal::IRegionEventDispatchWithArgs< StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_i_region_event_dispatch_with_args.html", null ],
      [ "sttcl::internal::IRegionEventDispatchWithoutArgs< StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_i_region_event_dispatch_without_args.html", null ],
      [ "sttcl::RefCountPtr< T, MutexType >", "classsttcl_1_1_ref_count_ptr.html", null ],
      [ "sttcl::RefCountPtr< void, MutexType >", "classsttcl_1_1_ref_count_ptr_3_01void_00_01_mutex_type_01_4.html", null ],
      [ "sttcl::Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >", "classsttcl_1_1_region.html", null ],
      [ "sttcl::RegionBase< StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1_region_base.html", null ],
      [ "sttcl::internal::RegionBaseImplementationSelector< RegionImpl, StateMachineImpl, StateInterface, IInnerState, EventArgs >", "structsttcl_1_1internal_1_1_region_base_implementation_selector.html", null ],
      [ "sttcl::internal::RegionBaseImplementationSelector< RegionImpl, StateMachineImpl, StateInterface, IInnerState, void >", "structsttcl_1_1internal_1_1_region_base_implementation_selector_3_01_region_impl_00_01_state_mac1fcf30d5c7aa13a0afb15f44330e128b.html", null ],
      [ "sttcl::internal::RegionBaseImplWithEventArgs< RegionImpl, StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_region_base_impl_with_event_args.html", null ],
      [ "sttcl::internal::RegionBaseImplWithoutEventArgs< RegionImpl, StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_region_base_impl_without_event_args.html", null ],
      [ "sttcl::internal::RegionContainer< StateMachineImpl, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_region_container.html", null ],
      [ "sttcl::internal::RegionEventDispatchInterfaceSelector< StateMachineImpl, StateInterface, IInnerState, EventArgs >", "structsttcl_1_1internal_1_1_region_event_dispatch_interface_selector.html", null ],
      [ "sttcl::internal::RegionEventDispatchInterfaceSelector< StateMachineImpl, StateInterface, IInnerState, void >", "structsttcl_1_1internal_1_1_region_event_dispatch_interface_selector_3_01_state_machine_impl_00_1c9e40e315de455ca32a621514c3137d.html", null ],
      [ "sttcl::State< StateImpl, StateMachineImpl, IState >", "classsttcl_1_1_state.html", null ],
      [ "sttcl::StateBase< StateMachineImpl, IState >", "classsttcl_1_1_state_base.html", null ],
      [ "StateInterface", "class_state_machine_impl_1_1_state_interface.html", null ],
      [ "sttcl::StateMachine< StateMachineImpl, IState >", "classsttcl_1_1_state_machine.html", null ],
      [ "sttcl::internal::SttclMutex< Impl, TimeDurationType >", "classsttcl_1_1internal_1_1_sttcl_mutex.html", null ],
      [ "sttcl::internal::SttclSemaphore< Impl, TimeDurationType >", "classsttcl_1_1internal_1_1_sttcl_semaphore.html", null ],
      [ "sttcl::internal::SttclThread< Impl >", "classsttcl_1_1internal_1_1_sttcl_thread.html", null ],
      [ "sttcl::internal::ThreadFunctionHelper", "structsttcl_1_1internal_1_1_thread_function_helper.html", null ],
      [ "ThreadImpl", "class_thread_impl.html", null ],
      [ "sttcl::TimeDuration< Implementation >", "classsttcl_1_1_time_duration.html", null ]
    ] ],
    [ "Class Index", "classes.html", null ],
    [ "Class Hierarchy", "hierarchy.html", [
      [ "sttcl::internal::AutoLocker< Lockable >", "classsttcl_1_1internal_1_1_auto_locker.html", null ],
      [ "sttcl::internal::CompositeStateBase< InnerStateType >", "classsttcl_1_1internal_1_1_composite_state_base.html", [
        [ "sttcl::CompositeState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >, StateMachineImpl, IInnerState, HistoryType, ActiveState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >, StateMachineImpl, StateMachineImpl::StateInterface, StateThreadType, TimeDurationType, SemaphoreType, MutexType >, StateMachine< RegionImpl, IInnerState > >", "classsttcl_1_1_composite_state.html", [
          [ "sttcl::Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >", "classsttcl_1_1_region.html", null ]
        ] ],
        [ "sttcl::CompositeState< CompositeStateImpl, StateMachineImpl, IInnerState, HistoryType, StateBaseImpl, StateMachineBaseImpl >", "classsttcl_1_1_composite_state.html", null ]
      ] ],
      [ "sttcl::internal::CompositeStateBaseSelector< HistoryType, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< CompositeStateHistoryType::Deep, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector_3_01_composite_state_history_type_1_1_411e935fc31fe5a2b2f2b11c5f685412.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< CompositeStateHistoryType::Shallow, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector_3_01_composite_state_history_type_1_1_982b593242060720f9ba414a3529c73e.html", null ],
      [ "sttcl::internal::CompositeStateBaseWithDeepHistory< InnerStateType >", "classsttcl_1_1internal_1_1_composite_state_base_with_deep_history.html", null ],
      [ "sttcl::internal::CompositeStateBaseWithShallowHistory< InnerStateType >", "classsttcl_1_1internal_1_1_composite_state_base_with_shallow_history.html", null ],
      [ "sttcl::CompositeStateHistoryType", "structsttcl_1_1_composite_state_history_type.html", null ],
      [ "sttcl::internal::ConcurrentCompositeBaseImplementationSelector< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "structsttcl_1_1internal_1_1_concurrent_composite_base_implementation_selector.html", null ],
      [ "sttcl::internal::ConcurrentCompositeBaseImplementationSelector< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, void, StateBaseImpl >", "structsttcl_1_1internal_1_1_concurrent_composite_base_implementation_selector_3_01_composite_sta8d142f762a15d3fea340a63ac0dbad6c.html", null ],
      [ "sttcl::internal::ConcurrentCompositeStateWithEventArgs< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1internal_1_1_concurrent_composite_state_with_event_args.html", [
        [ "sttcl::internal::ConcurrentCompositeStateBase< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1internal_1_1_concurrent_composite_state_base.html", [
          [ "sttcl::ConcurrentCompositeState< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1_concurrent_composite_state.html", null ]
        ] ]
      ] ],
      [ "sttcl::internal::ConcurrentCompositeStateWithoutEventArgs< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, StateBaseImpl >", "classsttcl_1_1internal_1_1_concurrent_composite_state_without_event_args.html", null ],
      [ "sttcl::internal::DispatchedEvent< StateMachineImpl, IInnerState, EventArgs >", "structsttcl_1_1internal_1_1_dispatched_event.html", null ],
      [ "sttcl::internal::EventArgsInterfaceSelector< StateMachineImpl, StateInterface, IInnerState, EventArgsType >", "structsttcl_1_1internal_1_1_event_args_interface_selector.html", null ],
      [ "sttcl::internal::EventArgsInterfaceSelector< StateMachineImpl, StateInterface, IInnerState, void >", "structsttcl_1_1internal_1_1_event_args_interface_selector_3_01_state_machine_impl_00_01_state_in1736ea8797feccfc9c96c455ed8619ab.html", null ],
      [ "sttcl::EventQueue< T, TimeDurationType, SemaphoreType, MutexType, InnerQueueType >", "classsttcl_1_1_event_queue.html", null ],
      [ "sttcl::internal::IRegionEventDispatchWithArgs< StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_i_region_event_dispatch_with_args.html", [
        [ "sttcl::RegionBase< StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1_region_base.html", [
          [ "sttcl::internal::RegionBaseImplWithEventArgs< RegionImpl, StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_region_base_impl_with_event_args.html", [
            [ "sttcl::Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >", "classsttcl_1_1_region.html", null ]
          ] ],
          [ "sttcl::internal::RegionBaseImplWithoutEventArgs< RegionImpl, StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_region_base_impl_without_event_args.html", null ]
        ] ]
      ] ],
      [ "sttcl::internal::IRegionEventDispatchWithoutArgs< StateMachineImpl, StateInterface, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_i_region_event_dispatch_without_args.html", null ],
      [ "sttcl::RefCountPtr< T, MutexType >", "classsttcl_1_1_ref_count_ptr.html", null ],
      [ "sttcl::RefCountPtr< void, MutexType >", "classsttcl_1_1_ref_count_ptr_3_01void_00_01_mutex_type_01_4.html", null ],
      [ "sttcl::internal::RegionBaseImplementationSelector< RegionImpl, StateMachineImpl, StateInterface, IInnerState, EventArgs >", "structsttcl_1_1internal_1_1_region_base_implementation_selector.html", null ],
      [ "sttcl::internal::RegionBaseImplementationSelector< RegionImpl, StateMachineImpl, StateInterface, IInnerState, void >", "structsttcl_1_1internal_1_1_region_base_implementation_selector_3_01_region_impl_00_01_state_mac1fcf30d5c7aa13a0afb15f44330e128b.html", null ],
      [ "sttcl::internal::RegionContainer< StateMachineImpl, IInnerState, EventArgs >", "classsttcl_1_1internal_1_1_region_container.html", [
        [ "sttcl::internal::ConcurrentCompositeStateBase< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1internal_1_1_concurrent_composite_state_base.html", null ]
      ] ],
      [ "sttcl::internal::RegionEventDispatchInterfaceSelector< StateMachineImpl, StateInterface, IInnerState, EventArgs >", "structsttcl_1_1internal_1_1_region_event_dispatch_interface_selector.html", null ],
      [ "sttcl::internal::RegionEventDispatchInterfaceSelector< StateMachineImpl, StateInterface, IInnerState, void >", "structsttcl_1_1internal_1_1_region_event_dispatch_interface_selector_3_01_state_machine_impl_00_1c9e40e315de455ca32a621514c3137d.html", null ],
      [ "sttcl::StateBase< StateMachineImpl, IState >", "classsttcl_1_1_state_base.html", [
        [ "sttcl::ActiveState< StateImpl, StateMachineImpl, IState, StateThreadType, TimeDurationType, EndDoActionSemaphoreType, ActiveStateMutexType >", "classsttcl_1_1_active_state.html", null ],
        [ "sttcl::State< StateImpl, StateMachineImpl, IState >", "classsttcl_1_1_state.html", null ]
      ] ],
      [ "StateInterface", "class_state_machine_impl_1_1_state_interface.html", [
        [ "sttcl::StateBase< StateMachineImpl, StateMachineImpl::StateInterface >", "classsttcl_1_1_state_base.html", [
          [ "sttcl::ActiveState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >, StateMachineImpl, StateMachineImpl::StateInterface, StateThreadType, TimeDurationType, SemaphoreType, MutexType >", "classsttcl_1_1_active_state.html", [
            [ "sttcl::CompositeState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >, StateMachineImpl, IInnerState, HistoryType, ActiveState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >, StateMachineImpl, StateMachineImpl::StateInterface, StateThreadType, TimeDurationType, SemaphoreType, MutexType >, StateMachine< RegionImpl, IInnerState > >", "classsttcl_1_1_composite_state.html", null ]
          ] ]
        ] ]
      ] ],
      [ "sttcl::StateMachine< StateMachineImpl, IState >", "classsttcl_1_1_state_machine.html", null ],
      [ "sttcl::StateMachine< RegionImpl, IInnerState >", "classsttcl_1_1_state_machine.html", [
        [ "sttcl::CompositeState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >, StateMachineImpl, IInnerState, HistoryType, ActiveState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, TimeDurationType, SemaphoreType, MutexType, EventQueueType >, StateMachineImpl, StateMachineImpl::StateInterface, StateThreadType, TimeDurationType, SemaphoreType, MutexType >, StateMachine< RegionImpl, IInnerState > >", "classsttcl_1_1_composite_state.html", null ]
      ] ],
      [ "sttcl::internal::SttclMutex< Impl, TimeDurationType >", "classsttcl_1_1internal_1_1_sttcl_mutex.html", null ],
      [ "sttcl::internal::SttclSemaphore< Impl, TimeDurationType >", "classsttcl_1_1internal_1_1_sttcl_semaphore.html", null ],
      [ "sttcl::internal::SttclThread< Impl >", "classsttcl_1_1internal_1_1_sttcl_thread.html", null ],
      [ "sttcl::internal::ThreadFunctionHelper", "structsttcl_1_1internal_1_1_thread_function_helper.html", null ],
      [ "ThreadImpl", "class_thread_impl.html", [
        [ "sttcl::internal::SttclThread< ThreadImpl >", "classsttcl_1_1internal_1_1_sttcl_thread.html", [
          [ "sttcl::ClassMethodThread< T, UserArgs, ThreadImpl, MutexImpl >", "classsttcl_1_1_class_method_thread.html", null ]
        ] ]
      ] ],
      [ "sttcl::TimeDuration< Implementation >", "classsttcl_1_1_time_duration.html", null ]
    ] ],
    [ "Class Members", "functions.html", null ],
    [ "Namespace List", "namespaces.html", [
      [ "sttcl", "namespacesttcl.html", null ],
      [ "sttcl::internal", "namespacesttcl_1_1internal.html", null ],
      [ "sttcl::internal::boost_impl", "namespacesttcl_1_1internal_1_1boost__impl.html", null ],
      [ "sttcl::internal::cx11_impl", "namespacesttcl_1_1internal_1_1cx11__impl.html", null ],
      [ "sttcl::internal::posix_impl", "namespacesttcl_1_1internal_1_1posix__impl.html", null ]
    ] ],
    [ "File List", "files.html", [
      [ "sttcl/BoostThreads/SttclBoostMutex.h", "_sttcl_boost_mutex_8h.html", null ],
      [ "sttcl/BoostThreads/SttclBoostSemaphore.h", "_sttcl_boost_semaphore_8h.html", null ],
      [ "sttcl/BoostThreads/SttclBoostThread.h", "_sttcl_boost_thread_8h.html", null ],
      [ "sttcl/BoostThreads/src/SttclBoostMutex.cpp", "_sttcl_boost_mutex_8cpp.html", null ],
      [ "sttcl/BoostThreads/src/SttclBoostSemaphore.cpp", "_sttcl_boost_semaphore_8cpp.html", null ],
      [ "sttcl/BoostThreads/src/SttclBoostThread.cpp", "_sttcl_boost_thread_8cpp.html", null ],
      [ "sttcl/BoostTime/SttclBoostTime.h", "_sttcl_boost_time_8h.html", null ],
      [ "sttcl/C++11Threads/SttclCx11Mutex.h", "_sttcl_cx11_mutex_8h.html", null ],
      [ "sttcl/C++11Threads/SttclCx11Semaphore.h", "_sttcl_cx11_semaphore_8h.html", null ],
      [ "sttcl/C++11Threads/SttclCx11Thread.h", "_sttcl_cx11_thread_8h.html", null ],
      [ "sttcl/C++11Threads/src/SttclCx11Mutex.cpp", "_sttcl_cx11_mutex_8cpp.html", null ],
      [ "sttcl/C++11Threads/src/SttclCx11Semaphore.cpp", "_sttcl_cx11_semaphore_8cpp.html", null ],
      [ "sttcl/C++11Threads/src/SttclCx11Thread.cpp", "_sttcl_cx11_thread_8cpp.html", null ],
      [ "sttcl/C++11Time/SttclCx11Time.h", "_sttcl_cx11_time_8h.html", null ],
      [ "sttcl/Debug/BoostThreads/src/SttclBoostMutex.d", "_sttcl_boost_mutex_8d.html", null ],
      [ "sttcl/Debug/BoostThreads/src/SttclBoostSemaphore.d", "_sttcl_boost_semaphore_8d.html", null ],
      [ "sttcl/Debug/BoostThreads/src/SttclBoostThread.d", "_sttcl_boost_thread_8d.html", null ],
      [ "sttcl/Debug/C++11Threads/src/SttclCx11Mutex.d", "_sttcl_cx11_mutex_8d.html", null ],
      [ "sttcl/Debug/C++11Threads/src/SttclCx11Semaphore.d", "_sttcl_cx11_semaphore_8d.html", null ],
      [ "sttcl/Debug/C++11Threads/src/SttclCx11Thread.d", "_sttcl_cx11_thread_8d.html", null ],
      [ "sttcl/Debug/PosixThreads/src/SttclPosixMutex.d", "_sttcl_posix_mutex_8d.html", null ],
      [ "sttcl/Debug/PosixThreads/src/SttclPosixSemaphore.d", "_sttcl_posix_semaphore_8d.html", null ],
      [ "sttcl/Debug/PosixThreads/src/SttclPosixThread.d", "_sttcl_posix_thread_8d.html", null ],
      [ "sttcl/Debug/PosixTime/src/SttclPosixTime.d", "_sttcl_posix_time_8d.html", null ],
      [ "sttcl/include/ActiveState.h", "_active_state_8h.html", null ],
      [ "sttcl/include/ClassMethodThread.h", "_class_method_thread_8h.html", null ],
      [ "sttcl/include/CompositeState.h", "_composite_state_8h.html", null ],
      [ "sttcl/include/ConcurrentCompositeState.h", "_concurrent_composite_state_8h.html", null ],
      [ "sttcl/include/EventQueue.h", "_event_queue_8h.html", null ],
      [ "sttcl/include/RefCountPtr.h", "_ref_count_ptr_8h.html", null ],
      [ "sttcl/include/Region.h", "_region_8h.html", null ],
      [ "sttcl/include/State.h", "_state_8h.html", null ],
      [ "sttcl/include/StateMachine.h", "_state_machine_8h.html", null ],
      [ "sttcl/include/SttclDoxygen.h", "_sttcl_doxygen_8h.html", null ],
      [ "sttcl/include/SttclMutex.h", "_sttcl_mutex_8h.html", null ],
      [ "sttcl/include/SttclSemaphore.h", "_sttcl_semaphore_8h.html", null ],
      [ "sttcl/include/SttclThread.h", "_sttcl_thread_8h.html", null ],
      [ "sttcl/include/SttclTime.h", "_sttcl_time_8h.html", null ],
      [ "sttcl/PosixThreads/SttclPosixMutex.h", "_sttcl_posix_mutex_8h.html", null ],
      [ "sttcl/PosixThreads/SttclPosixSemaphore.h", "_sttcl_posix_semaphore_8h.html", null ],
      [ "sttcl/PosixThreads/SttclPosixThread.h", "_sttcl_posix_thread_8h.html", null ],
      [ "sttcl/PosixThreads/src/SttclPosixMutex.cpp", "_sttcl_posix_mutex_8cpp.html", null ],
      [ "sttcl/PosixThreads/src/SttclPosixSemaphore.cpp", "_sttcl_posix_semaphore_8cpp.html", null ],
      [ "sttcl/PosixThreads/src/SttclPosixThread.cpp", "_sttcl_posix_thread_8cpp.html", null ],
      [ "sttcl/PosixTime/SttclPosixTime.h", "_sttcl_posix_time_8h.html", null ],
      [ "sttcl/PosixTime/src/SttclPosixTime.cpp", "_sttcl_posix_time_8cpp.html", null ]
    ] ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

