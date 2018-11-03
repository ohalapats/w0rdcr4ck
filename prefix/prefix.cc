/* AUTHOR: Dakota Simonds
 * DATE: Nov 7, 2017
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

#include <string>
#include <utility>
#include "prefix.hpp"
#include "prefix.h"

using std::string;



/***   Prefix implementations   ***/

Prefix::Prefix() : root(nullptr)
{

}

Prefix::~Prefix()
{
  prefix_destruct_tree(root);
}


void Prefix::insert(const char *word)
{
  prefix_insert(&root, word);
}


void Prefix::insert(const string &word)
{
  prefix_insert(&root, word.c_str());
}


bool Prefix::find(const char *word)
{
  return prefix_find(&root, word);
}


bool Prefix::find(const string &word)
{
   return prefix_find(&root, word.c_str());
}


unsigned Prefix::depth( )
{
  return prefix_depth(root);
}

Prefix::Monkey Prefix::monkey( )
{
  return std::move( Prefix::Monkey(*this) );
}


/*** monkey implementations ***/


Prefix::Monkey::Monkey(const Prefix &p) : parent(p), cur(p.root)
{}

Prefix::Monkey::~Monkey(){}

bool Prefix::Monkey::good( )
{ return nullptr != cur; }

void Prefix::Monkey::reset()
{
  cur = parent.root;
}

void Prefix::Monkey::advance_lvl()
{
  if(good())
    cur = cur->next_lvl;
}

bool Prefix::Monkey::have_char(char c)
{
  if(!good()) return false;

  cur = *prefix_find_in_lvl(&cur, c);
  return nullptr != cur;
}

bool Prefix::Monkey::look_ahead(char c){
  if(!good()) return false;
  if(nullptr != cur->next_lvl && cur->next_lvl->c == c) return true;
  
  return false;
}

const pre_node * Prefix::Monkey::get_current() const
{
  return cur;
}
 
