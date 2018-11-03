/* AUTHOR: Dakota Simonds
 * DATE: Oct 31, 2017
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


#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "prefix.h"

void test(pre_node *root, const char *word)
{
    printf("%s %s\n", prefix_find(&root, word) ? "found" : "not found", word);
}

int main()
{
  printf("see prefix_test_cpp for more rigorous test");
  pre_node *root = NULL;
  const char test3[] = "sappapple";
  const char test4[] = "sappapiii";
  prefix_insert(&root, test3);
  prefix_insert(&root, test4);
  prefix_show(root);
  printf("\nexpected success:\n");
  test(root, test3);
  test(root, test4);
  printf("\nexpected failure:\n");
  test(root, "sapp");
  test(root, "sappapplee");
  test(root, "boys");

  prefix_depth(root);
  prefix_destruct_tree(root);
return 0;
}
