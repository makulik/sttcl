var NAVTREE =
[
  [ "sttcl", "index.html", [
    [ "STTCL state machine template class framework", "index.html", null ],
    [ "Related Pages", "pages.html", [
      [ "Usage of the STTCL state machine template class framework", "usage_page.html", null ],
      [ "Mapping of the state diagram notation elements", "uml2gof_page.html", null ]
    ] ],
    [ "Class List", "annotated.html", [
      [ "sttcl::ActiveState< StateImpl, StateMachineImpl, IState, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >", "classsttcl_1_1_active_state.html", null ],
      [ "sttcl::AutoLocker< Lockable >", "classsttcl_1_1_auto_locker.html", null ],
      [ "sttcl::CompositeState< CompositeStateImpl, StateMachineImpl, IInnerState, HistoryType, StateBaseImpl, StateMachineBaseImpl >", "classsttcl_1_1_composite_state.html", null ],
      [ "sttcl::CompositeStateBase< InnerStateType >", "classsttcl_1_1_composite_state_base.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< HistoryType, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< CompositeStateHistoryType::Deep, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector_3_01_composite_state_history_type_1_1_411e935fc31fe5a2b2f2b11c5f685412.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< CompositeStateHistoryType::Shallow, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector_3_01_composite_state_history_type_1_1_982b593242060720f9ba414a3529c73e.html", null ],
      [ "sttcl::CompositeStateBaseWithDeepHistory< InnerStateType >", "classsttcl_1_1_composite_state_base_with_deep_history.html", null ],
      [ "sttcl::CompositeStateBaseWithShallowHistory< InnerStateType >", "classsttcl_1_1_composite_state_base_with_shallow_history.html", null ],
      [ "sttcl::CompositeStateHistoryType", "structsttcl_1_1_composite_state_history_type.html", null ],
      [ "sttcl::ConcurrentCompositeState< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1_concurrent_composite_state.html", null ],
      [ "sttcl::Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >", "classsttcl_1_1_region.html", null ],
      [ "sttcl::RegionBase< StateMachineImpl, StateInterface, EventArgs >", "classsttcl_1_1_region_base.html", null ],
      [ "sttcl::State< StateImpl, StateMachineImpl, IState >", "classsttcl_1_1_state.html", null ],
      [ "sttcl::StateBase< StateMachineImpl, IState >", "classsttcl_1_1_state_base.html", null ],
      [ "StateInterface", "class_state_machine_impl_1_1_state_interface.html", null ],
      [ "sttcl::StateMachine< StateMachineImpl, IState >", "classsttcl_1_1_state_machine.html", null ],
      [ "sttcl::internal::boost_impl::SttclBoostMutex", "classsttcl_1_1internal_1_1boost__impl_1_1_sttcl_boost_mutex.html", null ],
      [ "sttcl::internal::boost_impl::SttclBoostSemaphore", "classsttcl_1_1internal_1_1boost__impl_1_1_sttcl_boost_semaphore.html", null ],
      [ "sttcl::internal::boost_impl::SttclBoostThread", "classsttcl_1_1internal_1_1boost__impl_1_1_sttcl_boost_thread.html", null ],
      [ "sttcl::internal::boost_impl::SttclBoostTimeDuration", "classsttcl_1_1internal_1_1boost__impl_1_1_sttcl_boost_time_duration.html", null ],
      [ "sttcl::SttclMutex< Impl >", "classsttcl_1_1_sttcl_mutex.html", null ],
      [ "sttcl::SttclSemaphore< Impl >", "classsttcl_1_1_sttcl_semaphore.html", null ],
      [ "sttcl::SttclThread< Impl >", "classsttcl_1_1_sttcl_thread.html", null ],
      [ "sttcl::ThreadFunctionHelper", "structsttcl_1_1_thread_function_helper.html", null ],
      [ "sttcl::TimeDuration< Implementation >", "classsttcl_1_1_time_duration.html", null ]
    ] ],
    [ "Class Index", "classes.html", null ],
    [ "Class Hierarchy", "hierarchy.html", [
      [ "sttcl::AutoLocker< Lockable >", "classsttcl_1_1_auto_locker.html", null ],
      [ "sttcl::CompositeStateBase< InnerStateType >", "classsttcl_1_1_composite_state_base.html", [
        [ "sttcl::CompositeState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachineImpl, IInnerState, HistoryType, ActiveState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachineImpl, StateMachineImpl::StateInterface, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachine< RegionImpl, IInnerState > >", "classsttcl_1_1_composite_state.html", [
          [ "sttcl::Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >", "classsttcl_1_1_region.html", null ]
        ] ],
        [ "sttcl::CompositeState< CompositeStateImpl, StateMachineImpl, IInnerState, HistoryType, StateBaseImpl, StateMachineBaseImpl >", "classsttcl_1_1_composite_state.html", null ]
      ] ],
      [ "sttcl::internal::CompositeStateBaseSelector< HistoryType, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< CompositeStateHistoryType::Deep, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector_3_01_composite_state_history_type_1_1_411e935fc31fe5a2b2f2b11c5f685412.html", null ],
      [ "sttcl::internal::CompositeStateBaseSelector< CompositeStateHistoryType::Shallow, InnerStateType >", "structsttcl_1_1internal_1_1_composite_state_base_selector_3_01_composite_state_history_type_1_1_982b593242060720f9ba414a3529c73e.html", null ],
      [ "sttcl::CompositeStateBaseWithDeepHistory< InnerStateType >", "classsttcl_1_1_composite_state_base_with_deep_history.html", null ],
      [ "sttcl::CompositeStateBaseWithShallowHistory< InnerStateType >", "classsttcl_1_1_composite_state_base_with_shallow_history.html", null ],
      [ "sttcl::CompositeStateHistoryType", "structsttcl_1_1_composite_state_history_type.html", null ],
      [ "sttcl::ConcurrentCompositeState< CompositeStateImpl, StateMachineImpl, IInnerState, NumOfRegions, EventArgs, StateBaseImpl >", "classsttcl_1_1_concurrent_composite_state.html", null ],
      [ "sttcl::RegionBase< StateMachineImpl, StateInterface, EventArgs >", "classsttcl_1_1_region_base.html", null ],
      [ "sttcl::RegionBase< StateMachineImpl, StateMachineImpl::StateInterface, EventArgs >", "classsttcl_1_1_region_base.html", [
        [ "sttcl::Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >", "classsttcl_1_1_region.html", null ]
      ] ],
      [ "sttcl::StateBase< StateMachineImpl, IState >", "classsttcl_1_1_state_base.html", [
        [ "sttcl::ActiveState< StateImpl, StateMachineImpl, IState, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >", "classsttcl_1_1_active_state.html", null ],
        [ "sttcl::State< StateImpl, StateMachineImpl, IState >", "classsttcl_1_1_state.html", null ]
      ] ],
      [ "StateInterface", "class_state_machine_impl_1_1_state_interface.html", [
        [ "sttcl::StateBase< StateMachineImpl, StateMachineImpl::StateInterface >", "classsttcl_1_1_state_base.html", [
          [ "sttcl::ActiveState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachineImpl, StateMachineImpl::StateInterface, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >", "classsttcl_1_1_active_state.html", [
            [ "sttcl::CompositeState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachineImpl, IInnerState, HistoryType, ActiveState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachineImpl, StateMachineImpl::StateInterface, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachine< RegionImpl, IInnerState > >", "classsttcl_1_1_composite_state.html", null ]
          ] ]
        ] ]
      ] ],
      [ "sttcl::StateMachine< StateMachineImpl, IState >", "classsttcl_1_1_state_machine.html", null ],
      [ "sttcl::StateMachine< RegionImpl, IInnerState >", "classsttcl_1_1_state_machine.html", [
        [ "sttcl::CompositeState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachineImpl, IInnerState, HistoryType, ActiveState< Region< RegionImpl, StateMachineImpl, IInnerState, EventArgs, HistoryType, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachineImpl, StateMachineImpl::StateInterface, StateThreadType, EndDoActionSemaphoreType, TimeDurationType, ActiveStateMutexType >, StateMachine< RegionImpl, IInnerState > >", "classsttcl_1_1_composite_state.html", null ]
      ] ],
      [ "sttcl::internal::boost_impl::SttclBoostMutex", "classsttcl_1_1internal_1_1boost__impl_1_1_sttcl_boost_mutex.html", null ],
      [ "sttcl::internal::boost_impl::SttclBoostSemaphore", "classsttcl_1_1internal_1_1boost__impl_1_1_sttcl_boost_semaphore.html", null ],
      [ "sttcl::internal::boost_impl::SttclBoostThread", "classsttcl_1_1internal_1_1boost__impl_1_1_sttcl_boost_thread.html", null ],
      [ "sttcl::internal::boost_impl::SttclBoostTimeDuration", "classsttcl_1_1internal_1_1boost__impl_1_1_sttcl_boost_time_duration.html", null ],
      [ "sttcl::SttclMutex< Impl >", "classsttcl_1_1_sttcl_mutex.html", null ],
      [ "sttcl::SttclSemaphore< Impl >", "classsttcl_1_1_sttcl_semaphore.html", null ],
      [ "sttcl::SttclThread< Impl >", "classsttcl_1_1_sttcl_thread.html", null ],
      [ "sttcl::ThreadFunctionHelper", "structsttcl_1_1_thread_function_helper.html", null ],
      [ "sttcl::TimeDuration< Implementation >", "classsttcl_1_1_time_duration.html", null ]
    ] ],
    [ "Class Members", "functions.html", null ],
    [ "Namespace List", "namespaces.html", [
      [ "sttcl", "namespacesttcl.html", null ],
      [ "sttcl::internal", "namespacesttcl_1_1internal.html", null ],
      [ "sttcl::internal::boost_impl", "namespacesttcl_1_1internal_1_1boost__impl.html", null ],
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
      [ "sttcl/include/ActiveState.h", "_active_state_8h.html", null ],
      [ "sttcl/include/CompositeState.h", "_composite_state_8h.html", null ],
      [ "sttcl/include/ConcurrentCompositeState.h", "_concurrent_composite_state_8h.html", null ],
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
      [ "sttcl/PosixTime/SttclPosixTime.h", "_sttcl_posix_time_8h.html", null ]
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

