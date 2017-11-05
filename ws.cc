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
#include "ws.hpp"
#include "direction.hpp"
#include "data_horse.hpp"


int main(int argc, char *argv[])
{
  std::string wordlist_name;
  std::string grid_name;
  
  /* refactor this */
  if( argc >= 2 )
    wordlist_name = argv[1];
  if( argc >= 3 ) 
    grid_name = argv[2];
   
  std::cout << "wordsearch";
  if(argc > 1)
    std::cout << " - " << wordlist_name << " " << grid_name;
  std::cout<< std::endl;

  FileData<std::string> word_list(wordlist_name);

  for(auto itr = word_list.begin(); itr != word_list.end(); itr++)
    to_lower(*itr);
 
  if(wordlist_name == "" || word_list.fail()){
    std::cout << "no wordlist found " << wordlist_name << std::endl 
              << "Exiting" << std::endl;
    return 1;
  }
  

  grid<char, 15> tron(word_list);
  if( grid_name == "" || !tron.load(grid_name) ){
    std::cout << "No grid file found " << grid_name << std::endl 
              << "Exiting" << std::endl;  
    return 1;
  }
  
  tron.show();
  std::cout << tron.solve() << " words found" << std::endl;


  return 0;
}
