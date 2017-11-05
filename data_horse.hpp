#pragma once
/* DATE: Oct 7th, 2017
 * AUTHOR: Dakota Simonds
 */

/*
* MIT License (MIT)
* 
* Copyright (c) 2017 Dakota Simonds
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/


#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using std::vector;
using std::string;
using std::fstream;


void to_lower( string &subject )
{
  for(size_t i = 0; i < subject.length(); i++)
    subject[i] = tolower( subject[i] );
}


/* expanding vector */
template<typename item_ty>
class exvector : public vector<item_ty>
{
public:
  exvector() : vector<item_ty>(1)
  {
  
  }

  bool expand( size_t index )
  {
    size_t size = vector<item_ty>::size();  
    if(index+1 > size){
      size_t expand_by = 1;
      expand_by = index / size;
      expand_by = expand_by * 2;
      size_t expand_into = size * expand_by;
      vector<item_ty>::resize(expand_into);
      return true;
    }

    return false;
  }

  item_ty &
  operator[]( size_t index )
  {
    expand(index);
    return vector<item_ty>::at(index);
  }
  
  item_ty &
  at( size_t index )
  {
    return operator[](index);
  }
 
};


template<typename item_ty>
class FileData : public exvector<item_ty>
{
  string file_path;
  bool fail_;
public:
  explicit 
  FileData( string fpath )
  : file_path(fpath), fail_(false)
  {  
     try{ load( ); }
     catch(...){} 
  }

  bool fail( )
  { return fail_; }
protected:
  void load( )
  {
    std::fstream fileh(file_path);
    fail_ = fileh.fail();
    if(fail_) return;
    for(size_t count = 0; !fileh.eof(); count++ ) 
      fileh >> exvector<item_ty>::at(count);
    fileh.close();
  }
};




