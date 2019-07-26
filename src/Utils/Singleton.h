/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Singleton.h
 * Author: u0151316
 *
 * Created on July 24, 2019, 11:21 AM
 */

#ifndef SINGLETON_H
#define SINGLETON_H

namespace Huobi {
  template<typename T> 
  class Singleton
  {
    public:
      static T * instance()
      {
          static T obj;  // Assumes T has a protected default constructor.
          return &obj;
      }
  };
}

#endif /* SINGLETON_H */

