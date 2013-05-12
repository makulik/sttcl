/**
 * @file conversion_detection.h
 * Declares numerous template classes to realize type conversion checks.
 */
// Code taken almost verbatim from Andrei Alexandrescu's article:
//    http://www.cuj.com/experts/1810/alexandr.html

namespace StaticConceptCheck
{
// I need this helper or else dumb g++ chokes.
/**
 * Declares helper constructs to check for conversions from T to U.
 *
 * @tparam T The type to check.
 * @tparam U The type to convert from T.
 */
template <class T, class U>
struct ConversionHelper {
   typedef char Small;
   struct Big { char dummy[2]; };
   static Small Test(U);
   static Big   Test(...);
   static T MakeT();
};

/**
 * Used to check if T is convertible to U.
 *
 * @tparam T The type to check.
 * @tparam U The type to convert from T.
 */
template <class T, class U>
struct Conversion {
   typedef ConversionHelper<T,U> H;
   enum { exists = sizeof(H::Test(H::MakeT())) == sizeof(typename H::Small) };
   enum { exists2Way = exists && Conversion<U, T>::exists };
   enum { sameType = false };
};

/**
 * Specialization of Conversion for the exactly same type.
 */
template <class T>
class Conversion<T, T> {
public:
   enum { exists = 1, exists2Way = 1, sameType = 1 };
};

// I dislike the SUPERSUBCLASS macro, so I use this.
/**
 * Used to check for static inheritance of Derived from Base.
 *
 * @tparam Derived The derived class to check.
 * @tparam Base The base class.
 */
template <class Derived, class Base>
struct Inherits {
   enum { value = (Conversion<const Derived*, const Base*>::exists && 
                   !Conversion<const Base*, const void*>::sameType) };
};

}
