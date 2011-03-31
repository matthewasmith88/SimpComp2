Five Man Team

Team 206 - The Odd Man Out

Tyler Crocker
Michael Palmer
Avram Blaszka
Stanislava Auchynnikava
Matt Smith

Instructions for use of the SC2 simulator.

Run options: <name of executable>					Runs the program and brings up the menu.
	     <name of executable> -p "<name of object file>"		Runs the program, loads the specified object file, and runs the file.
	     <name of executable> -p "<name of object file>" -s		Runs the program, loads the specified object file, and begins stepping through the file

Running the program with no arguments will bring up the menu. At the menu you can load a file, run a program, step through a program, display the register file, display a segment of memory, or exit. To load a file, the .obj file must be in the same directory as the program. The object file is a column of hexadecimal bytes, one byte per line, with the low order byte of the instruction first and the high order byte next. Run will execute the program until it is halted (i.e. the halt bit is asserted in the program). Step will bring up a submenu that provides most of the same functionality of the main menu, but with a few additions. Some additions to the step submenu include: the display of PC, IR, and SW. Display registers simply prints out the contents of the whole register file. Display memory prompts the users for a beginning memory address and an ending address and prints the contents of the corresponding addresses. 

If a program is run and an error occurs, the halt bit will be asserted and execution will cease.

Since the in-class presentation we have added a few things. We added some additional print statements that notify the user whether a file was loaded successfully or not. We also added an additional option to the step menu to continue running through the rest of the program. Finally, we now display the status word. 

NOTE ABOUT kbd.obj:
When running this, it takes 3 characters, one at a time (char, enter, char enter, char enter), and then prints them in reverse order on one line. There is no output other than that (i.e. nothing saying "please enter a char").


Problems encountered.

One problem that we encountered was more of a mistake on our part. We initially wrote the load file to load an object file which had a whole instruction word on each line instead of one byte. This was not a huge problem, but it did require us to rewrite a few functions.

Another problem we found with loading files was the difference between the formats of plain text files that were generated on different platforms. For example, half of our group uses OS X, one uses Linux, and another uses Windows. In Windows, a character return character is put at the end of each line (the '\r' character) while the Unix platforms don't. This required a little bit of extra code in the string parsing section of our code. We encountered other problems with developing this program on so many different operating systems. Problems such as using certain characters in file names (like the asterisk "*").


Variations on original specifications.

We changed the store byte - base relative and store word - base relative op codes to 0x1A and 0x1B respectively. We also added a halt instruction with the op code of 0x1F.

The object files must be formatted such that it is comprised of words, meaning it has even number of lines. If a file turns out to have an odd number of lines, the second to last byte should be 0x00 (since our memory module is big endian, the second to last byte is the last byte put into memory).
