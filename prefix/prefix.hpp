#pragma once

/* AUTHOR: Nov 7th, 2017
 * DATE: Dakota Simonds
 */


/*
* Copyright 2017 Dakota Simonds
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is furnished
* to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
* THE SOFTWARE.
*/

#include <cstdlib>
#include <string>
#include "prefix.h"
#include "diroutine.hpp"

using std::string;



/* I'm inventing a new term here: diroutine
*  A diroutine is similar in nature to the coroutine
*  however it is different as follows:
*    - it takes a new argument at each call
*    - the argument it takes is it's complement diroutine
*    - it has resettable state
*/



class Prefix{
  pre_node *root;
public:
  typedef char common_ty;

  class di : public diroutine<common_ty>{
    const Prefix &parent;
    pre_node *cur;
  public:
    explicit
    di(const Prefix &p) : parent(p), cur(p.root)
    {}

    ~di()
    {}

    void reset()
    { cur = parent.root; }
    
    bool valid()
    {  return static_cast<bool>( cur ); }
 
    const common_ty& operator()()
    {
      return cur->c;
    }
 
    bool operator()( diroutine<common_ty> &complement )
    { 
      if(!cur) return false;

      /* TODO: clean this up */
      auto &comp_val = complement();
      cur = *(prefix_find_in_lvl(&cur, comp_val));
      if( NULL == cur)
         return false;
      cur = *(prefix_next_lvl(&cur));
  
      return comp_val == (*this)();
    }

    friend class Prefix;
  }; 

  Prefix();
  ~Prefix();

  void insert(const char *word);
  void insert(string word);
  bool find(const char *word);
  bool find(const string &word);
  unsigned depth( );

  di begin( );
  friend class Prefix::di;
};
