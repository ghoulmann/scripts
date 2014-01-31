#ifndef EVENTMANAGER_CORE_EVMANGLOBAL_H
#define EVENTMANAGER_CORE_EVMANGLOBAL_H

#include <unordered_map>
#include <memory>

#include <QDebug>

class QString;

template <class T>
QDebug operator<<(QDebug out, std::shared_ptr<T> ptr)
   {
      out << ptr.get();
      return out;
   }

namespace Core {

struct TQStringHash
   {
      inline size_t operator()(const QString &String) const
         { return qHash(String); }
   };


void Message(const QString &Str);

inline void noop() { }
QString GetBacktrace();
void PrintBacktrace();
void on_AssertionFailed();


#ifdef Q_OS_UNIX
   QString Demangle(const QString &RawStr);
#endif  // Q_OS_UNIX

//==================  ASSERT ==================
#define RELEASE_ASSERT(cond)  \
   { if(!(cond)) \
      { \
         qDebug() << "\nASSERTION FAILED AT" << __FILE__ << ":" << __LINE__; \
         qDebug() << #cond; \
         Core::on_AssertionFailed(); \
      } }

#ifndef QT_NO_DEBUG
#   define ASSERT(cond) RELEASE_ASSERT(cond)
#else
#   define ASSERT(cond) Core::noop();
#endif



//==================  ASSERT_OP ==================
#define RELEASE_ASSERT_OP(left, op, right) \
   { if(!((left) op (right))) \
      { \
         qDebug() << "\nASSERTION FAILED AT" << __FILE__ << ":" << __LINE__; \
         qDebug() << #left << #op << #right << "=>" << (left) << #op << (right); \
         Core::on_AssertionFailed(); \
      } }

#ifndef QT_NO_DEBUG
#   define ASSERT_OP(left, op, right) RELEASE_ASSERT_OP(left, op, right)
#else
#   define ASSERT_OP(left, op, right) Core::noop();
#endif



//Output X as message
//==================  ASSERT_X ==================
#define RELEASE_ASSERT_X(cond, msg) \
   { if(!(cond)) \
      { \
         qDebug() << "\nASSERTION FAILED AT" << __FILE__ << ":" << __LINE__; \
         qDebug() << #cond << "\n" << msg; \
         Core::on_AssertionFailed(); \
      } }
#ifndef QT_NO_DEBUG
#   define ASSERT_X(cond, msg) RELEASE_ASSERT_X(cond, msg)
#else
#   define ASSERT_X(cond, msg) Core::noop();
#endif


//Output X as message and print values of conditions
//==================  ASSERT_X_OP ==================
#define RELEASE_ASSERT_X_OP(left, op, right, msg) \
   { if(!((left) op (right))) \
        { \
           qDebug() << "\nASSERTION FAILED AT" << __FILE__ << ":" << __LINE__; \
           qDebug() << #left << #op << #right << "=>" << (left) << #op << (right); \
           qDebug() << msg; \
           Core::on_AssertionFailed(); \
        } }
#ifndef QT_NO_DEBUG
#   define ASSERT_X_OP(left, op, right, msg) RELEASE_ASSERT_X_OP(left, op, right, msg)
#else
#   define ASSERT_X_OP(left, op, right, msg) Core::noop();
#endif



//===============  ASSERT_COMMAND ===============

// we do not use the  'do {...} while (0)' idiom here to be able to use
// 'break' and 'continue' as 'actions'.
#ifndef QT_NO_DEBUG
#define ASSERT_COMMAND(cond, action) \
   if(!(cond)) { qDebug() << "ASSERTION" << #cond << "FAILED AT" << __FILE__ << ":" << __LINE__; Core::PrintBacktrace(); action; }
#else
#define ASSERT_COMMAND(cond, action) \
   if(cond) {} else { action; }
#endif





template<class T>
const T &const_(const T &t) { return t; }




//==================  FOREACH ==================
template <class TCont>
class TForeachContainer
   {
    public:
      inline TForeachContainer() {}
      typedef typename TCont::const_iterator const_iterator;
      typedef typename TCont::iterator iterator;
   };

//For references
template <class TCont>
class TForeachContainer<TCont &>
   {
    public:
      inline TForeachContainer() {}
      typedef typename TCont::const_iterator const_iterator;
      typedef typename TCont::iterator iterator;
   };


#ifdef Q_COMPILER_DECLTYPE
#   define FOREACH_CONSTIT_QT_X(cont, IT) \
       for(Core::TForeachContainer<decltype(cont)>::const_iterator (IT) = (cont).constBegin(); (IT) != (cont).constEnd(); ++(IT))
#else
#   define FOREACH_CONSTIT_QT_X(cont, IT) \
       for(Core::TForeachContainer<typeof(cont)>::const_iterator (IT) = (cont).constBegin(); (IT) != (cont).constEnd(); ++(IT))
#endif


#ifdef Q_COMPILER_DECLTYPE
#   define FOREACH_CONSTIT_QT_X_TYPENAME(cont, IT) \
       for(typename Core::TForeachContainer<decltype(cont)>::const_iterator (IT) = (cont).constBegin(); (IT) != (cont).constEnd(); ++(IT))
#else
#   define FOREACH_CONSTIT_QT_X_TYPENAME(cont, IT) \
       for(typename Core::TForeachContainer<typeof(cont)>::const_iterator (IT) = (cont).constBegin(); (IT) != (cont).constEnd(); ++(IT))
#endif


#ifdef Q_COMPILER_DECLTYPE
#   define FOREACH_CONSTIT_X(cont, IT) \
       for(Core::TForeachContainer<decltype(cont)>::const_iterator (IT) = (cont).begin(); (IT) != (cont).end(); ++(IT))
#else
#   define FOREACH_CONSTIT_X(cont, IT) \
       for(Core::TForeachContainer<typeof(cont)>::const_iterator (IT) = (cont).begin(); (IT) != (cont).end(); ++(IT))
#endif


#ifdef Q_COMPILER_DECLTYPE
#   define FOREACH_CONSTIT_X_TYPENAME(cont, IT) \
       for(typename Core::TForeachContainer<decltype(cont)>::const_iterator (IT) = (cont).begin(); (IT) != (cont).end(); ++(IT))
#else
#   define FOREACH_CONSTIT_X_TYPENAME(cont, IT) \
       for(typename Core::TForeachContainer<typeof(cont)>::const_iterator (IT) = (cont).begin(); (IT) != (cont).end(); ++(IT))
#endif


#ifdef Q_COMPILER_DECLTYPE
#   define FOREACH_IT_X(cont, IT) \
       for(Core::TForeachContainer<decltype(cont)>::iterator (IT) = (cont).begin(); (IT) != (cont).end(); ++(IT))
#else
#   define FOREACH_IT_X(cont, IT) \
       for(Core::TForeachContainer<typeof(cont)>::iterator (IT) = (cont).begin(); (IT) != (cont).end(); ++(IT))
#endif


#ifdef Q_COMPILER_DECLTYPE
#   define FOREACH_IT_X_TYPENAME(cont, IT) \
       for(typename Core::TForeachContainer<decltype(cont)>::iterator (IT) = (cont).begin(); (IT) != (cont).end(); ++(IT))
#else
#   define FOREACH_IT_X_TYPENAME(cont, IT) \
       for(typename Core::TForeachContainer<typeof(cont)>::iterator (IT) = (cont).begin(); (IT) != (cont).end(); ++(IT))
#endif





#define FOREACH_CONSTIT_QT(cont)          FOREACH_CONSTIT_QT_X(cont, It)
#define FOREACH_CONSTIT_QT_TYPENAME(cont) FOREACH_CONSTIT_QT_X_TYPENAME(cont, It)

#define FOREACH_CONSTIT(cont)          FOREACH_CONSTIT_X(cont, It)
#define FOREACH_CONSTIT_TYPENAME(cont) FOREACH_CONSTIT_X_TYPENAME(cont, It)

#define FOREACH_IT(cont)          FOREACH_IT_X(cont, It)
#define FOREACH_IT_TYPENAME(cont) FOREACH_IT_X_TYPENAME(cont, It)


//================== ===========================


template <class TKey, class TValue>
bool Contains(const std::unordered_map<TKey, TValue> &Cont, const TKey &Key)
   {
      return Cont.find(Key) != Cont.end();
   }



template <class T>
T VariantValue(const QVariant &Variant)
   {
      ASSERT(Variant.isValid());
      ASSERT(Variant.canConvert<T>());
      return Variant.value<T>();
   }
inline void SetProperty(QObject *Object, const char *Name, const QVariant &Value)
   {
      const bool Ok = Object->setProperty(Name, Value);
      ASSERT(Ok);
   }
template <class T>
T Property(QObject *Object, const char *Name)
   {
      return VariantValue<T>(Object->property(Name));
   }

}
#endif // EVENTMANAGER_CORE_EVMANGLOBAL_H
