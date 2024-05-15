# Simple bash units CAT/GREP


## cat - concatenate and print files 

| № | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-blank lines |
| 2 | -e implies -v (GNU only: -E same as -e but without -v) | also displays end-of-line characters as $ |
| 3 | -n (GNU: --number) | numbers all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeezes multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T same as -t but without -v) | also displays tabs as ^I |

Let's delve into the functionality of each flag that you need to implement:

### b (--number-nonblank)
Numbers only non-blank lines.

This flag should number only lines that are not empty.
Empty lines (consisting only of a newline character \n) should not be numbered.
Numbering should start at 1 and increment for each non-blank line.

### e (implies -v)
Displays end-of-line characters as `.

This flag should add the ` character at the end of each line to indicate where the line ends.
If the v flag is also set, it should work in addition to e to display invisible characters (see the description of the v flag).

### n (--number)
Numbers all output lines.

This flag should number all lines, including empty ones.
Numbering should start at 1 and increment for each line.

### s (--squeeze-blank)
Squeezes multiple adjacent blank lines.

This flag should replace sequences of two or more blank lines with a single blank line.
This allows for "squeezing" multiple blank lines to make the output more compact.

### t (implies -v)
Displays tabs as ^I.

This flag should replace tab characters (\t) with ^I to make them visible in the output.
If the v flag is also set, it should work in addition to t to display other invisible characters (see the description of the v flag).

### General Notes:
- Flags can be specified in any order and combination.
- If the v flag is set along with e or t, it should work in addition to them to display all invisible characters.
- Your program should correctly handle input from multiple files passed as command line arguments.

In the context of the cat command in Linux, the -v flag is typically used to display the contents of a file with visible representations of invisible characters. When the -v flag is set, the cat command can show special characters like end-of-line symbols or tabs, aiding users in visualizing the text structure more clearly.

For instance, using cat -v file.txt, the cat command will display the contents of file.txt, replacing invisible characters such as end-of-line symbols or tabs with their visible representations. This can be helpful for debugging or analyzing text data, allowing users to see hidden characters within the text.


## Global Regular Expression Print (grep)

| Option | Description |
| --- | --- |
| No flags | The command performs a substring search in the file and prints the line if it is found. If not, it prints nothing. <br> `grep text file.txt` |
| -e | Searches for multiple patterns in the file. |
| -i | Ignores case distinctions. |
| -v | Inverts the sense of matching, to select non-matching lines. <br> `grep -v 'error' log.txt` - This command will print all lines from the log.txt file that do not contain the word "error". The -v flag allows searching for lines that do not contain the specified pattern. |
| -c | grep will output only the number showing how many matching lines were found in the file samp.txt. |
| -l | The -l flag in grep allows printing only the names of files in which a match for the given pattern was found, without printing the lines themselves. |
| -n | Precedes each output line with its line number from the input file. |
| -h | Does not print the file name if there are multiple files. |
| -s | Suppresses error messages about nonexistent or unreadable files. |
| -f file | Obtains regular expressions from the file. <br> `grep -f patterns.txt file.txt` |
| -o | The -o flag in grep allows printing only the matching parts of lines, not the entire lines. <br> `grep -o 'the' file.txt` |

**No flags**
- The command performs a substring search in the file and prints the line if it is found.
- If the pattern is not found in the file, it prints nothing.
- Example: `grep text file.txt`

**-e**
- Searches for multiple patterns in the file.
- Allows specifying multiple patterns to search for.

**-i**
- Ignores case distinctions during the search.
- The search will be case-insensitive.

**-v**
- Inverts the sense of matching, to select non-matching lines.
- This command will print all lines from the `log.txt` file that do not contain the word "error":
  `grep -v 'error' log.txt`
- The -v flag allows searching for lines that do not contain the specified pattern.

**-c**
- grep will output only the number showing how many matching lines were found in the file `samp.txt`.
- This is useful for counting the number of occurrences of a pattern, without printing the actual lines.

**-l**
- The -l flag in grep allows printing only the names of files in which a match for the given pattern was found, without printing the lines themselves.
- This is useful when you want to know which files contain the pattern, but don't need to see the actual matching lines.

**-n**
- Precedes each output line with its line number from the input file.
- This adds line numbers to the output, making it easier to identify the location of the matches.

**-h**
- Does not print the file name if there are multiple files.
- This option is useful when you don't want the file name to be displayed in the output, especially when searching through multiple files.

**-s**
- Suppresses error messages about nonexistent or unreadable files.
- This can be useful when you want to avoid seeing error messages for files that don't exist or can't be read.

**-f file**
- Obtains regular expressions from the file.
- Example: `grep -f patterns.txt file.txt`
- This allows you to specify the patterns to search for in a separate file, rather than directly in the command.

**-o**
- The -o flag in grep allows printing only the matching parts of lines, not the entire lines.
- Example: `grep -o 'the' file.txt`
- This can be useful when you only want to see the specific parts of the lines that match the pattern, rather than the entire line.
