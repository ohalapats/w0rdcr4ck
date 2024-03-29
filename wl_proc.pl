#!/usr/bin/perl

# AUTHOR: Dakota Simonds
# DATE: 10/27/2017

#####
# Copyright 2017 Dakota Simonds
#
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
# copies of the Software, and to permit persons to whom the Software is furnished
# to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
# THE SOFTWARE.
#####

use warnings;
use strict;

print("Wordlist proccessor/cleaner\n");

my %table;

print("Source File: ");
my $fname = <STDIN>;
chomp $fname;

print("Destination file: ");
my $dfname = <STDIN>;
chomp $dfname;

my $fileh;
open( $fileh, "+<", $fname ) or die "invalid file\n";
my $line = "";


my $min = 0;
print("Min word size (0 to disable a minimum): ");
$min = <STDIN>;
chomp($min);

my $count = 0;
while(<$fileh>)
{
  $line = $_;
  if(length($line) > $min){
    $table{transform($line)} = "";
    $count++;
  }
}

close($fileh);

my $fin;
open( $fin, ">>", $dfname );

foreach my $key (keys(%table))
{
  print $fin ($key . "\n");
}

close( $dfname );


print("Finished! " . $count . " lines proccessed\n");

sub transform 
{
  my $line = shift();

  $line =~ s/\W//gi;

  return $line;
}
