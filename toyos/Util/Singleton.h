//===- Singleton.h ------*- C++ -*-----------------------------------------===//
//
// Copyright (C) 2020-2022 Terapines Technology (Wuhan) Co., Ltd
// All rights reserved.
//
//===----------------------------------------------------------------------===//
//
// This file defines util class Singleton.
// Only one instance is allowed.
//
//===----------------------------------------------------------------------===//

#ifndef __KERNEL_SINGLETON_H_
#define __KERNEL_SINGLETON_H_

template <class T> class Singleton {
public:
    Singleton(const Singleton &) = delete;
    void operator=(const Singleton &) = delete;
    static T &getInstance() {
        static T instance;
        return instance;
    }

protected:
    Singleton() {}
};

#endif //__KERNEL_SINGLETON_H_
