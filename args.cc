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

#include "args.hpp"
#include <iostream>



Args::Args(int ac, char *av[]) : wordlist_path(""),  grid_path(""), flags(), argc(ac), argv(av)
{
  load( );
}

void Args::show_errors(){
  if(flags[ err_flag::NOT_ENOUGH_ARGS ])
    std::cout << "Not enough arguments. " << std::endl;

  if(flags[ err_flag::TOO_MANY_ARGS ])
    std::cout << "Too many arguments" << std::endl;

  if(flags[ err_flag::WL_NOT_FOUND ])
    std::cout << "Wordlist " << wordlist_path << " not found" << std::endl;

  if(flags[ err_flag::GRID_NOT_FOUND ])
    std::cout << "Grid " << grid_path << " not found" << std::endl;
}

bool Args::has_errors()
{
  return flags.any();
}

void Args::load( )
{
  if( argc < 3 )
    flags[ err_flag::NOT_ENOUGH_ARGS ] = true; 
  else if( argc > 3 )
    flags[ err_flag::TOO_MANY_ARGS ] = true;
  
  if( argc >= 2 )
      wordlist_path = argv[1];
  
  if( argc >= 3 )
      grid_path = argv[2];
}


void Args::flag( err_flag flg )
{  flags[ flg ] = true;  }

const string& Args::get_wordlist_path()
{ return wordlist_path; }

const string& Args::get_grid_path()
{ return grid_path; }