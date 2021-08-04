MODULE io_main;
{intord - this adds some needed functionality to pascal/mt+ also reqired
 to include a table module for your specific processor type. in this version
 there is 8080, as well as 8086.  This is done as there is a 8 byte offset
 to the dummy procedure routine technique described in the programmers
 refrence. within that module there is a procedure that generates the 
 pointers for all the table data which must be exicuted prior to including.

 there's likely a way to do that automatically with mechine code, but as 
 it is just a look up table its not going to be any faster, so its low 
 on my priority list right now.  if sombody wants to write in drop in 
 table modules that build the data in memory and estabish the pointers
 without calling them it might be a good project if you are incredibly bored.
 
 (C)2021 D. Collins - USE AT YOUR OWN RISK - Licence to use without
 warentee from damage guarantee of functionality free to distribute }

type 
{$I intord.tdf}


var
{$I intord.vdf}

  
{ devide & conqur method, very fast no math counts digits }
function intlen(value :integer) : byte;
begin
 if value < 10000 then 
  if value < 100 then 
    if value < 10 then intlen := 1 else intlen := 2
  else
    if value < 1000 then intlen := 3 else intlen := 4
 else intlen := 5;
end;

{ procedure directly modifies a string with integer values using a 
  pointer to directly modify the string data, pass a string variable
  to the procedure using ADDR(<string name>) this will only work with
  integer values and the string should be limited to 5 characters a 
  handy type is provided see the .tdr file }

procedure intstr(value:integer;loc :strptr); 
var
 a,len : integer;
 
begin
 len  := intlen(value); (* much faster to do this just once *)
 loc^[1] := len;
 loc^[len+1] := intord^[value mod 10];
 if len > 1 then for a := len downto 2 do 
   loc^[a] := intord^[(value div devisor^[len][a]) mod 10];
end;

{positive intiger compatible string of decimal numbers to a value, 
 this will process a string up to 5 characters in length, though its
 going to output a 2's compliment number, it will output a negitive 
 value for numbers above the 2's compliment 16 bit intiger maximum }
function strint(value : otstrtp) : integer;
var 
 a,tvalue       : integer;
 valueptr       : strptr;
 
begin
 valueptr := addr(value); (* this is no slower than passing the pointer *)

 tvalue := chrint^[valueptr^[valueptr^[1]+1]];

  (* we can peek at the string length by refrenceing cell 1 of the string *)

 if valueptr^[1] > 1 then for a := valueptr^[1] downto 2 do 
   tvalue := tvalue + (mplyerdec^[valueptr^[1]][a] * chrint^[valueptr^[a]]);

 strint := tvalue;
end;

{positive integer compatible string of hexidecimal number to a value,
 this will work with a 4 digit hex value string, it expects the data
 in big endian, so its limited in it's use to simply a intiger string
 in regular notation of 4 characters. }
function hstrint(value : otstrtp) : integer;
var 
 a,tvalue      :integer;
 valueptr      :strptr;
 
begin
 valueptr := addr(value);
 tvalue := chrint^[valueptr^[valueptr^[1]+1]];
 if valueptr^[1] > 1 then for a := valueptr^[1] downto 2 do
   tvalue := tvalue + (mplyerhex^[valueptr^[1]][a] * chrint^[valueptr^[a]]);
 hstrint := tvalue;
end;

MODEND.

