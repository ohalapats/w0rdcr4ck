#ifndef PREFIX_H
#define PREFIX_H

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
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



struct pre_node{
  char c;
  struct pre_node *next_lvl;
  struct pre_node *child;
};

typedef struct pre_node pre_node;

#ifdef __cplusplus
extern "C"{
#endif

pre_node *
prefix_init( char c, pre_node *next_lvl, pre_node *child );

pre_node *
prefix_new( char c );

inline pre_node ** prefix_next_lvl( pre_node **node);

inline pre_node ** prefix_next_child( pre_node **node);

inline char prefix_get_c( pre_node **node );

pre_node **
prefix_find_in_lvl( pre_node **lvl, char c );

void prefix_insert(pre_node **root, const char *string);

short prefix_find( pre_node **root, const char *string );

void prefix_destruct_tree( pre_node *node );

void prefix_show(pre_node *node);

unsigned prefix_depth_( pre_node *node, unsigned depth );

unsigned prefix_depth( pre_node *node );

void see_child( pre_node *node );

#ifdef __cplusplus
}
#endif


#endif
