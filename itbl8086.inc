MODULE io_tables_8086;
 {                    intord lookup tables module

  here are the custom lookup tables for the 8086/8 useing the technique
  described in 'Pascal/MT+ Programmers Reference for DOS'. Pascal/MT+ 
  has no typed constants, and therefor you can not declare a constant
  table in memory. you need to include one of these (8088 or 8086) at 
  link time, along with the apropreate .tdf and .def files in their
  respective locations in the declaration block of your code. you 
  only need to include the .vdf if you need to use these tables in 
  your code (and if you need them they are much faster than a set,
  so I recomend it.)

  additionally, you need to call 'imkptrs' prior to using any function
  or procedure that uses these tables.

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
 { we need a bunch of kludged pointers to manipulate the offset by 
   8 bytes, due to how pascal/mt+ handles procedure return calls. 
   this only works on the 8086.  I have no idea how this works on the
   68k.
   
   a better way to do this would be to build these tables in asembly language
   as a module, but as i've mentioned before; execution would not be faster
   as you can not get faster than looking up a value but it would avoid 
   declaring the pointers which would save some memory perhapse. }

 pk_iord     = record
                case boolean of
		 true  : (p : ordptrtp);
		 false : (loword : word;
                          hiword : word)
		end;

 pk_devisor  = record
		case boolean of
		 true  : (p : decptrtp);
		 false : (loword : word;
			  hiword : word)
		end;
 pk_chrint   = record
		case boolean of 
		 true  : (p : intptrtp);
		 false : (loword : word;
			  hiword : word)
		end;
 pk_decm     = record
		case boolean of
		 true  : (p : decptrtp);
		 false : (loword : word;
			  hiword : word)
		end;
 pk_hexm     = record
		case boolean of
		 true  : (p : hexptrtp);
		 false : (loword : word;
			  hiword : word)
		end;


Var
 intord     : ordptrtp;
 i	    : pk_iord;
 devisor    : decptrtp;
 d	    : pk_devisor;	
 chrint     : intptrtp;
 ci         : pk_chrint;
 mplyerdec  : decptrtp;
 md	    : pk_decm;
 mplyerhex  : hexptrtp;
 mh	    : pk_hexm;

 
(*integer values for first digit number by ordinal value *)
procedure ints;
begin
 inline (0/1/2/3/4/5/6/7/8/9/0/0/0/0/0/0/0/10/11/12/13/14/15);
end;

(* ordinal values 0 - 9 *)
procedure otbl;
begin 
 inline (48 / 49 / 50 / 51 / 52 / 53 / 54 / 55 / 56 / 57);
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

{make all the pointers, call before exicution 8086 vrs. 
 we have to add 8 because the table data starts is 8 bytes forward}
 
procedure imkptrs;
begin
 i.p := addr(otbl);
 i.loword := i.loword + wrd(8);
 intord := i.p;       

 d.p := addr(decm);
 d.loword := d.loword + wrd(8);
 devisor := d.p;
 
 ci.p := addr(ints);
 ci.loword := ci.loword + wrd(8);
 chrint := ci.p;
 
 md.p := addr(decm);
 md.loword := md.loword + wrd(8);
 mplyerdec := md.p;
 
 mh.p := addr(hexm);
 mh.loword := mh.loword + wrd(8);
 mplyerhex := mh.p;

end;

MODEND.

