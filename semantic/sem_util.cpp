#include "sem_util.h"

/**
 * @author gehao
 * 
 * instanceof<Parent>(p)：判断p指向的对象是否为Parent的子类(含Parent) 
 */
template <typename Base, typename T>
inline bool instanceof (T * p) {
    return dynamic_cast<Base*>(p);
}