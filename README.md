<h1 style="text-align: center;"><strong>INTORD</strong></h1>
<p style="text-align: center;"><em>A modern(ish) integer strings handler for Pascal/MT+</em></p>
<p style="text-align: center;">Programmer's Reference Sheet</p>
<p style="text-align: center;">&copy; 2021 - D. Collins <br />z80dad@gmail.com</p>
<p>&nbsp;</p>
<h3>1 - INTRODUCTION:</h3>
<p>This module when included into your source will provide a few pointer driven <br />string manipulation routines which allow for (relatively) fast conversion of <br />strings to and from integers. This functionality was left out of the compiler <br />and is very handy, especially when creating programs to control a VT100 / ANSI <br />terminal.</p>
<p><br /><strong>The module consists of two parts:</strong></p>
<p><br />1 - The main module (intord.inc) which contains the 100% portable code and the<br />strings handler.</p>
<p><br />2 - the table modules (itbl8080.inc &amp; itbl8086.inc) which contain the <br />conversion tables needed for the handler to operate at speed. You will need to<br />include one of these depending on the platform. The 8080 module uses only 8080<br />instructions so it should work on both the intel 8080 as well as the Z80. The <br />8086 variant is 16 bit 8086 and should work on any 8086 platform that also runs<br />the compiler.</p>
<p><br /><strong>USE:</strong><br /><br />To use, simply include the .def and .tdf files in your declaration block by <br />using the {$I } compiler directive, directly in source and calling &lsquo;IMKPTRS&rsquo; <br />Someplace in execution before using any of the included functions; this is a <br />special procedure that declares the locations of all the custom tables for the<br />functions. In a later version I plan to use machine code to define these <br />tables, but it makes no difference at this point in terms of speed as these are<br />simply look up tables and the pointers can be declared 1x during program bootup <br />and then simply used from that point.</p>
<p><br /><strong>Example 1-1 (including modules):</strong></p>
<blockquote>
<pre><code>PROGRAM Test_Prog;</code><br /><code><br />TYPE</code><br /><code>{$I intord.tdf}</code><br /><code><br />&lt;your custom types go here&gt;</code><br /><br /><br /><code>VAR</code><br /><code><br />&lt;your custom variables go here&gt;</code><br /><br /><code>(* end of your declaration block *)</code><br /><br /><code>{$I intord.def}</code></pre>
</blockquote>
<p><br />You will then need either use the precompiled .erl / .86r files at link time or<br />compile your own. This may be necessary as your CP/M environment / dos <br />environment may be different from the V20-MBC used to compile these but they <br />are included in the repository for ease of use. Remember also that you will <br />need to link BOTH intord, as well as a compatible table module (itbl8080 or <br />itbl8086).</p>
<p><br /><strong>SIGNED DATA:</strong></p>
<p>For speed these functions only work with positive values and will not work <br />(or will produce unpredictable values with signed data). Please remember this<br />when working with these functions. It&rsquo;s possible to make these work at speed <br />with signed numbers, just not using pure pascal code. A later revision may <br />include support for floating point and negative numbers.</p>
<h3><br />2 - FUNCTION / PROCEDURE USE:</h3>
<p><br /><strong>Intlen -</strong></p>
<blockquote>
<p><br /><em>Function intlen(integer)</em></p>
<p>pass a 16 bit integer and intlen returns the number of digits. Similar to <br />length() for strings.</p>
</blockquote>
<p><br /><strong>Example 2-1 intlen use:</strong></p>
<blockquote>
<pre><br /><code>A := 100;</code><br /><code>writeln(Intlen (a));</code><br /><br /><code>&lt;Should return 3&gt;</code></pre>
</blockquote>
<p>&nbsp;</p>
<p><br /><strong>Intstr -</strong></p>
<blockquote>
<p><br /><em>Procedure intstr(integer,pointer)</em></p>
<p>Pass an integer value and a pointer to a string, the procedure will place the <br />ASCII characters of that integer value into that string.</p>
</blockquote>
<p><br /><strong>Example 2-2 intstr use:</strong></p>
<blockquote>
<pre><br />A := 100;<br />StA := &lsquo;&rsquo;;<br />intstr(a,addr(StA)); (* addr() is in paslib see compiler docs *)<br />writeln(StA);<br /><br />&lt;should return 100&gt;<br /><br /><br /></pre>
</blockquote>
<p><br /><strong>Strint &amp; hstrint -</strong></p>
<blockquote>
<p><br /><em>Function strint (string) (* a string which is 5 characters or less *)</em><br /><em>Function hstrint (string) (* &ldquo; &rdquo; 4 &ldquo; &ldquo; *)</em></p>
<p>Pass a string with ASCII Coded Decimal / Hexadecimal (HSTRINT), the function <br />will return the value as an integer. NOTE: HSTRINT uses a 4 characters <br />hexadecimal, ASCII coded and expects the numeral order as a standard 16 byte <br />BIG ENDIAN integer. If reading in 16 bit bytes in LITTLE ENDIAN notation, you <br />may need to swap the bytes before transcoding. EXAMPLE: for the value (462) <br />HSTRINT expects (1CE). Additionally, the character &lsquo;h&rsquo; following a number in<br />hex or &lsquo;0x&rsquo; preceding it will also produce issues.</p>
</blockquote>
<p><br /><strong>Example 2-3 strint use:</strong></p>
<blockquote>
<pre><br />StA := &lsquo;462&rsquo;<br />StB := &lsquo;052C&rsquo; (* value is 1324 *)<br />writeln((strint(StA)+1));<br />writeln((hstrint(StB)+4));<br /><br /><br />&lt; should return 463 and 1328 &gt;<br /><br /><br /></pre>
</blockquote>
<p><strong>Imkptrs -</strong></p>
<blockquote>
<p><br /><em>Procedure imkptrs</em></p>
<p><br />Generates the pointers for the table data for the module required to be placed<br />in your main code before calling any of the module procedures. The code for <br />this is actually located in the platform specific table module and is <br />different in size and execution time between the platforms.</p>
</blockquote>
<p><strong>Example 2-4 imkptrs:</strong></p>
<blockquote>
<pre>imkptrs;<br />&lt;hereafter, you can use any function from this module&gt;</pre>
</blockquote>
<p>&nbsp;</p>
