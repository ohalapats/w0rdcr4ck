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

using std::string;



class Prefix{
  pre_node *root;
public:

  /* a monkey climbs a tree */
  class Monkey{
    const Prefix &parent;
    pre_node *cur;
  public:
    explicit
    Monkey(const Prefix &p) : parent(p), cur(p.root)
    {}

    ~Monkey(){}
    
    bool good( )
    { return nullptr != cur; }
    
    void reset()
    {
      cur = parent.root;
    }
    
    void advance_lvl()
    {
      if(good())
        cur = cur->next_lvl;
    }
    
    bool have_char(char c)
    {
      if(!good()) return false;

      cur = *prefix_find_in_lvl(&cur, c);
      return nullptr != cur;
    }

    const pre_node * get_current() const
    {
      return cur;
    }
    
    friend class Prefix;
  }; 

  Prefix();
  ~Prefix();

  void insert(const char *word);
  void insert(const string &word);
  bool find(const char *word);
  bool find(const string &word);
  unsigned depth( );

  Prefix::Monkey monkey( );
  friend class Prefix::Monkey;
};
