#ifndef __SEMUTIL_H__
#define __SEMUTIL_H__

/**
 * @author gehao
 * 
 * instanceof<Parent>(p)：判断p指向的对象是否为Parent的子类(含Parent) 
 * template的实现也要放在.h文件，否则make会报错
 */
template <typename Base, typename T>
inline bool instanceof (T * p) {
    return dynamic_cast<Base*>(p);
}

#endif