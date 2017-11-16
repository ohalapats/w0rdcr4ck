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

#include <iostream>
#include <string>
#include <vector>
#include "prefix.hpp"
#include "worddi.hpp"

using std::vector;
using std::string;

int main(void)
{
  Prefix test;
  vector<string> tests 
  {
    "rawr",
    "rabbit",
    "ram",
    "ramble",
    "ram",
    "ramm",
    "fly",
    "34242",
    "FLY",
    "!",
    "a",
    "1"
    "!!",
    "!!!!!!!!!!!!!!!!!!!!!!!!!!!!",
    "34$$",
    "&779*&8777*(88*&&&&&&&&&&&&**&&*&*&*&***&&&*&&*&*&*&*&*&*\0\0"
    "",
    "",
    "\0\0\0\0",
    "Glory is fleeting, but obscurity is forever.\n"
      "    - Napoleon Bonaparte (1769-1821) ",
    "C makes it easy to shoot yourself in the foot; C++ makes it harder, but"
      " when you do, it blows away your whole leg.\n - Bjarne Stroustrup"
  };
  
  for( auto itr = tests.begin(); itr != tests.end(); itr++)
  {
    test.insert(*itr);
  }
  
  bool all_passed = true;
  bool passed = true;
  int error_count = 0;
  for( auto itr = tests.begin(); itr != tests.end(); itr++)
  {
    passed = test.find(*itr);
    if(!passed){
      error_count++;
      std::cout << "FAILED: " << *itr << std::endl;
    }
    all_passed = all_passed && passed;
  }
  
  if(all_passed){
    std::cout << "All tests passed" << std::endl;
  } else {
    std::cout << error_count << " tests failed" << std::endl;
  }
 
  std::cout << std::endl;

  return 0;
}
