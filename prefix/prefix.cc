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

Prefix::Prefix() : root(NULL)
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


void Prefix::insert(string word)
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


Prefix::di Prefix::begin()
{
  return std::move( Prefix::di(*this) );
}
