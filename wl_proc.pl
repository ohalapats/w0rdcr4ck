# AUTHOR: Dakota Simonds
# DATE: 10/27/2017

use warnings;
use strict;

print("Wordlist proccessor: remove dulicates, special charaters\n");

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

my $count = 0;
while(<$fileh>)
{
  $line = $_;
  $table{transform($line)} = "";
  $count++;
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
