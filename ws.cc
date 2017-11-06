/* AUTHOR: Dakota Simonds
 * DATE: Oct 14, 2017
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
#include <functional>
#include <fstream>
#include <string>
#include <cstdlib>
#include "ws.hpp"
#include "direction.hpp"
#include "data_horse.hpp"
#include "args.hpp"


int main(int argc, char *argv[])
{
  std::cout << "wordsearch (c)opyleft Dakota Simonds 2017" << std::endl;
  Args args(argc, argv);
  
  if(args.has_errors()){
    args.show_errors();
    std::cout << "Exiting" << std::endl;
    return EXIT_FAILURE;
  }


  FileData<std::string> word_list(args.wordlist_name);

  for(auto itr = word_list.begin(); itr != word_list.end(); itr++)
    to_lower(*itr);
 
  if(args.wordlist_name == "" || word_list.fail()){
    std::cout << "no wordlist found " << args.wordlist_name << std::endl 
              << "Exiting" << std::endl;
    return EXIT_FAILURE;
  }
  

  grid<char, 15> tron(word_list);
  if( args.grid_name == "" || !tron.load(args.grid_name) ){
    std::cout << "No grid file found " << args.grid_name << std::endl 
              << "Exiting" << std::endl;
    return EXIT_FAILURE;
  }
  
  tron.show();
  std::cout << tron.solve() << " words found" << std::endl;


  return EXIT_SUCCESS;
}
