//
//  AnyDataType.h
//  TypecheckedGenericContainer
//
//  Created by Mike Allison on 8/17/14.
//  Copyright (c) 2014 Mike Allison. All rights reserved.
//
//  Implemented from http://ciaranm.wordpress.com/2010/05/24/runtime-type-checking-in-c-without-rtti/

#include <memory>
#include <iostream>

#ifndef TypecheckedGenericContainer_AnyDataType_h
#define TypecheckedGenericContainer_AnyDataType_h

const char error[] = "[AnyData::as::ERROR] Incompatible datatype";


class AnyDataType
{
private:
    
    static int next_id()
    {
        static int data_id(0);
        return data_id++;
    }
    
    template <typename T_>
    static int id_for()
    {
        static int result( next_id() );
        return result;
    }

    
    struct AnyDataValueBase
    {
        int data_id;
        
        AnyDataValueBase(const int m) :
        data_id(m)
        {
        }
        
        virtual ~AnyDataValueBase()
        {
        }
    };
    
    template <typename T_>
    struct AnyDataValue :
    AnyDataValueBase
    {
        T_ value;
        
        AnyDataValue(const T_ & v) :
        AnyDataValueBase(id_for<T_>()),
        value(v)
        {
        }
    };
    
    std::shared_ptr<AnyDataValueBase> _value;
    
public:
    template <typename T_>
    AnyDataType(const T_ & t) :
    _value(new AnyDataValue<T_>(t))
    {
    }
    
    template <typename T_>
    const T_ & as() const
    {
        if (id_for<T_>() != _value->data_id)
            throw std::runtime_error( "[AnyDataType::as::ERROR] Invalid typecast" );
        return std::static_pointer_cast<const AnyDataValue<T_> >(_value)->value;
    }
    
    template <typename T_>
    T_ & as()
    {
        if (id_for<T_>() != _value->data_id)
            throw std::runtime_error( "[AnyDataType::as::ERROR] Invalid typecast" );
        return std::static_pointer_cast<AnyDataValue<T_> >(_value)->value;
    }
};


#endif
