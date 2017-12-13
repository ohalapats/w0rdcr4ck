 #pragma once
/* AUTHOR: Dakota Simonds
 * DATE: Nov 5, 2017
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

#include <bitset>
#include <string>

enum err_flag{
  WORDSEARCH = 0,
  GRID,
  NOT_ENOUGH_ARGS,
  TOO_MANY_ARGS,
  GRID_NOT_FOUND,
  WL_NOT_FOUND
};


class Args
{
public:
  std::bitset<8> flags;
  std::string wordlist_name;
  std::string grid_name;

  int argc;
  char **argv;
  
  Args(int ac, char *av[]);

  void show_errors();
  bool has_errors();
  
protected:
  void load();
};





