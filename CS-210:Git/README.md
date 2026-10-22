//* CS-210 Programming Languages
//* Brian Beaudin  
//* Southern New Hampshire University

This folder holds my three CS-210 projects, all written in C++:
•	Corner Grocer: item purchase frequency program (the project I chose for this reflection)
•	Airgead Banking: investment growth calculator
•	Chada Clock: 12-hour and 24-hour clock display

The Corner Grocer folder contains main.cpp, GroceryTracker.h, GroceryTracker.cpp, the input file, and a sample frequency.dat output file. To run it, compile all the .cpp files together and run the program from the same folder as the input file.

**Summarize the project and what problem it was solving.**
  The Corner Grocer wanted to rearrange its produce section based on what customers buy most often. The store keeps a text file listing every item purchased during the day, but that list is hard to use on its own. My program reads the file, counts how many times each item was purchased, and gives the user a menu with four options: look up one item, print every item with its count, print a histogram using asterisks, or exit. It also saves all of the counts to a backup file called frequency.dat when the program starts.

**What did you do particularly well?**
  I think the structure of the program is the strongest part. I put all of the data work into a GroceryTracker class, with the declarations in a header file and the code in a separate .cpp file, so main() only has to run the menu. I also spent time on input validation. The menu won't crash or loop forever if the user types a letter or a number outside 1 to 4, and the file reader skips blank lines and removes extra whitespace, including the hidden \r characters that show up when a Windows text file is read on a Mac. I also made the list and histogram line up by calculating the longest item name instead of guessing at a column width.

**Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?**
  The item search ignores capitalization, but it does this by checking every item in the map one at a time. If I converted the item names to the same case when loading the file, I could use the map's normal lookup, which would be faster. That change would also fix a limitation I noticed: if the file had both "Apples" and "apples," they would be counted as two separate items. The sample file doesn't have this problem, but it could happen with other data.
I would also let the user give the file path when starting the program instead of hard-coding the file name, so the program would work from any folder and with any day's file. A few numbers in the code, like the 4 for the exit option, should be named constants so their purpose is clear. I could also check that the backup file was written correctly, not just that it opened, which would make the saved data more reliable.

**Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?**
  The hardest part was getting the program to find the input file on my Mac. My code was correct, but the program kept saying it couldn't open the file. I learned that the program looks for the file in the folder it is run from, not the folder where the code is saved. I fixed it by using the Terminal to move into the project folder before running the program and by giving Terminal permission to access that folder in my Mac's settings. Because of this, I made the error message tell the user to keep the file in the same folder as the program.
The histogram formatting was also tricky because item names are different lengths, which made the columns uneven. Finding the longest name while loading the file and using that number with setw() fixed the alignment.
I also had trouble with the access specifiers public, private, and protected earlier in the course. The course introduction explained them in a slightly confusing way, so I had to compare other sources until I understood how they really work. That taught me to check more than one source when something doesn't make sense.
The resources I'm adding to my support network are the zyBooks readings, YouTube channels like Tech With Tim and Bro Code, the Google C++ Style Guide, the Geosoft C++ Programming Style Guidelines, and the CMMI Code of Professional Conduct.

**What skills from this project will be particularly transferable to other projects or course work?**
  Using classes and splitting code into header and source files will apply to almost any larger program I write. I found that counting items with a map is the same idea as using a dictionary in Python or GROUP BY with COUNT in SQL, which I've used in other courses. Reading data from a file, cleaning it up, and writing results to another file is something most real programs need to do. Validating user input and working through problems one step at a time will help in every programming course I take.
  
**How did you make this program maintainable, readable, and adaptable?**
  I kept the item data private inside the class, so the rest of the program can only use it through methods with clear names like GetItemFrequency() and PrintHistogram(). The file names are stored as constants at the top of main.cpp, so they only need to be changed in one place. Every file starts with a comment explaining what it does, every method has a comment in the header, and I tried to write comments that explain why something is done instead of just repeating the code. I used consistent naming throughout the project. To add a new feature, I would only need to write a new method and add a new menu option, without changing the code that already works.
