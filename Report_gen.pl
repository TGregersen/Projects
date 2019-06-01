#! /usr/bin/env perl
use strict;
use warnings;
use POSIX qw(strftime);

#Reading the input file

open(my $file, "<", "/home/todd/Documents/weeklyactivities.txt") or die "Can't open input file: $!";

#Parsing Line by Line into an array

#my @Lines = <$file>;

#Creating a file

my $time = strftime ("%d-%m-%y", localtime);	#getting date stamp
my $name = "/home/todd/Documents/Projects/Report/WeeklyReport$time.txt";	#including stamp
open(my $out_file, ">", "$name") or die "Can't Open output file: $!";

#Creating Email File

open(my $mail_file, ">", "/home/todd/Documents/Projects/Report/Report_Email.txt") or die "Can't Open mail output file: $!";

#Generating Output

my $day = strftime("%d",localtime)-7;	#getting start of period day
my $val = strftime ("Weekly Report %m/$day/%y-%m/%d/%y", localtime);	#setting date
my $sign = "Thank You\nTodd Gregersen\n";

#Assigning output to Weekly Report

print $out_file $val;
print $mail_file $val;
print $out_file "\n\n";
print $mail_file "\n\n";
while(<$file>){
 print $out_file $_;
 print $mail_file $_;
}
print $out_file "\n\n";
print $mail_file "\n\n";
print $out_file $sign;
print $mail_file $sign;

#assigning output to email file

#closing files

close $file or die "Cant Close in File: $!";
close $out_file or die "Cant Close out File: $!";
close $mail_file or die "Cant Clost Mail File: $!";