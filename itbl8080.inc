MODULE io_tables_8080;
 { here are the custom lookup tables for the 8080 using the technique
   described in 'Pascal/MT+ Programmers refrence for CP/M'.  Pascal/MT+ 
   has no typed constants, and therefor you can not declare a constant
   table in memory. you need to include one of these (8080 or 8086) at 
   link time, along with the apropriate .tdf, and .def files in their 
   respective locations in the declaration block of your code. you 
   only need to include the .vdf if you are useing these tables in 
   your code (and if you need them they are MUCH faster than a set,
   so I recommend it ) 

   additionally, you need to call 'imkptrs' prior to useing any function
   or procedure that needs these tables. 
           
MIT License

Copyright (c) 2021 Dave Collins

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. }

Type
{$I intord.tdf}

Var
 intord     : ordptrtp;
 devisor    : decptrtp;
 chrint     : intptrtp;
 mplyerdec  : decptrtp;
 mplyerhex  : hexptrtp;

 
(* ordinal values for numbers 0 - 9 *)
procedure ords;
begin
 inline ( 48 / 49 / 50 / 51 / 52 / 53 / 54 / 55 / 56 / 57 ) 
end;

(*integer values for first digit number by ordinal value *)
procedure ints;
begin
 inline (0/1/2/3/4/5/6/7/8/9/0/0/0/0/0/0/0/10/11/12/13/14/15);
end;

(*these are factors of 10 for decimal conversion *)
procedure decm;
begin
 inline ($0A/$00/$00/$00/$00/$00/$00/$00/
         $64/$00/$0A/$00/$00/$00/$00/$00/
         $E8/$03/$64/$00/$0A/$00/$00/$00/
         $10/$27/$E8/$03/$64/$00/$0A/$00 );
end;

(*factors of 16 for hex conversion *)
procedure hexm; 
begin;      
 inline ($10/$00/$00/$00/$00/$00/
         $00/$01/$10/$00/$00/$00/
         $00/$10/$00/$01/$10/$00 );
end;

(*make all the pointers, call before exicution 8080 vs. *)
procedure imkptrs;
begin
 devisor:= addr(decm);
 intord := addr(ords);
 chrint := addr(ints);
 mplyerdec := addr(decm);
 mplyerhex := addr(hexm);
end;

MODEND.

