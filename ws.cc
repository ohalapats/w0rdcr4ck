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
#include "args.hpp"

void usage(void)
{
  using namespace std;
  cout << "./w0rdcr4ck [WORDLIST] [GRID]" << endl
       << "WORDLIST is a line-separated textfile containing words" << endl
       << " You can clean up a dirty wordlist with wl_proc.pl" << endl
       << "GRID is a textfile of characters. " << endl 
       << " This is used for the puzzle itself."
       << " Each row must be on a new line" << endl;
}

int main(int argc, char *argv[])
{
  using namespace std;
  cout << "w0rdcr4ck v1.0 - copyright under MIT license 2017" << endl << endl;
  Args args(argc, argv);
  
  if(args.has_errors()){
    usage();
    args.show_errors();
    cout << "Exiting" << endl;
    return EXIT_FAILURE;
  }

  grid<char> tron(args);
  tron.show();
  cout << tron.solve() << " words found" << endl;
  return EXIT_SUCCESS;
}
