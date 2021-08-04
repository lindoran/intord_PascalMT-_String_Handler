program iotest;

type
{$I intord.tdf}

var
 str : otstrtp;
 
{$I intord.def}

begin

imkptrs;
writeln(intlen(10000));
writeln(intlen(1000));
writeln(intlen(100));
writeln(intlen(10));
writeln(intlen(9));

str := '10000';

writeln(strint(str));
intstr(20,addr(str));
writeln(str);

intstr(10000,addr(str));
writeln(str);

end.
