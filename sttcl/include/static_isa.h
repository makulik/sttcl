/**
 * @file static_isa.h
 * Declares numerous template classes to realize static concept checks.
 */
#include "conversion_detection.h"
/**
 * Declares numerous template classes to realize static concept checks.
 */
namespace StaticConceptCheck
{
/**
 *  For custom error messages.
 *  Instantiating the error class specifying any T and referencing any
 *  member will generate a compiler error of the form:
 *  Unknown member 'Error<T>::member' ...
 *
 *  @tparam T Any class that should appear in the error message.
 *
 */
template <class T>
struct Error {}; 

/**
 * BoolError<false> doesn't exist; used to create errors from booleans
 *
 * @tparam b The static boolean value to check
 */
template <bool b>
struct BoolError;

/**
 * Specialization of BoolError<true>. No error is generated.
 */
template <>
struct BoolError<true> {}; 

/**
 * Usual meta-IF
 * Chooses between two template parameters dependent on a given static
 * boolean value.
 *
 *  @tparam b The static boolean value to check
 *  @tparam T The class chosen when b yields true
 *  @tparam E The class chosen when b yields false
 */
template <bool b, class T, class E>
struct IF;

/**
 * Specialization for IF<true,T,E>. Chooses T for typedef RET.
 */
template <class T, class E>
struct IF<true,T,E> {
   typedef T RET;
};

/**
 * Specialization for IF<false,T,E>. Chooses E for typedef RET.
 */
template <class T, class E>
struct IF<false,T,E> {
   typedef E RET;
};

/**
 * A way to thunk an int; not useful by itself, but useful to make  "then"
 * and "else" clauses of IF parallel
 *
 */
template <int N>
struct IntHolderThunk {
   template <class T>
   struct Value {
      static const int RET = N;
   };
};

/**
 * This class helps us instantiate a template method during the act of
 * accessing a compile-time constant value.
 *
 */
template <void (*F)()>
struct Blah { static const int x = 1; };

/**
 * This just makes it easier to instantiate the check_structural()
 * function of a static interface.
 *
 * @tparam T The class to check for implementation of the static interface.
 * @tparam I The static concept definition to check against.
 */
template <class T, class I>
void check_structural() {
   (void) ((void (I::*)(T)) &I::template check_structural<T>);
}

/**
 * Used to check for full static inheritance of Derived from Base.
 *
 * @tparam Derived The derived class to check.
 * @tparam Base The base class.
 */
template <class Derived, class Base>
struct StaticIsA {     
   // Note to self: need to bootstrap this, as there's a constraint! :)

   static const bool builtin_isa = Base::template Traits<Derived>::valid;
   static const bool named_isa = Inherits<Derived,Base>::value;
   struct Thunk {
      template <class Dummy>
      struct Value {
         static const int RET = 
               Blah<&check_structural<Derived,Base> >::x;
      };
   };
   typedef typename IF<named_isa,
                       Thunk,IntHolderThunk<builtin_isa> >::RET  Compute;

   // "valid" is true if the relationship holds; will also diagnose
   // structural conformance problems if any
   static const bool valid = Compute::template Value<int>::RET;
};

/**
 * Used to check for named inheritance of Derived from Base.
 *
 * @tparam Derived The derived class to check.
 * @tparam Base The base class.
 */
template <class Derived, class Base>
struct Named {     
   static const bool valid = Inherits<Derived,Base>::value;
};

/**
 * Used to check for structural inheritance of Derived from Base.
 *
 * @tparam Derived The derived class to check.
 * @tparam Base The base class.
 */
template <class T, class Concept>
inline void RequireStructural() {
   (void) ((void (*)()) &check_structural<T,Concept>);
}

/**
 * Used to check for named inheritance of Derived from Base.
 *
 * @tparam Derived The derived class to check.
 * @tparam Base The base class.
 */
template <class T, class Concept>
inline void RequireNamed() {
   BoolError< Named<T,Concept>::valid > RequireNamed_has_failed;
   (void) RequireNamed_has_failed;
}

/**
 * Used to check for named and structural inheritance of Derived from Base.
 *
 * @tparam Derived The derived class to check.
 * @tparam Base The base class.
 */
template <class T, class Concept>
inline void RequireBoth() {
   RequireNamed<T,Concept>();
   RequireStructural<T,Concept>();
}

/**
 *  This stuff is just to help users define static interfaces easily
 */
#define MAKE_TRAITS \
   template <class Self> \
   struct Traits { \
      static const bool valid = false; \
   };

struct Valid {
   static const bool valid = true;
protected:
   ~Valid() {};
};

/**
 * Protects against 'evil' proxy definitions.
 */
template <class T>
struct HeroicProxy {
   HeroicProxy( const T& ) {}
};

}
