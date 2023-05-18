## Fully Functional File Explorer Application, with a restricted feature set.
### File Explorer works in two modes :-
1. Normal mode (default mode) - used to explore the current directory and navigate the filesystem 
2. Command mode - used to enter shell commands
- The root of this application is same as the system, and the home of the application is same as home of the current user.
- The application displays data starting from the top-left corner of the terminal window, line-by- line.

### Normal mode:
Normal mode is the default mode of your application. It has the following functionalities -
1. Display a list of directories and files in the current folder
a. Every file in the directory should be displayed on a new line with the following attributes for each file -
i. File Name
ii. File Size
iii. Ownership (user and group) and Permissions
iv. Last modified
b. The file explorer shows the entries “.” and “..” for current and parent directory respectively
c. The file explorer handle scrolling using the up and down arrow keys.
d. User is able to navigate up and down in the file list using the corresponding up and down arrow keys.

2. Open directories and files When enter key is pressed -
a. Directory - Clear the screen and navigate into the directory and show the directory contents as specified in point 1
b. File - Open the file in the editor

3. Traversal
a. Go back - Left arrow key should take the user to the previously visited directory
b. Go forward - Right arrow key should take the user to the next directory
c. Up one level - Backspace key should take the user up one level
d. Home – h key should take the user to the home folder

### Command Mode:
The application should enter the Command button whenever “:” (colon) key is pressed. In the command mode, the user should be able to enter different commands. All commands appear in the status bar at the bottom.
1. Copy –
‘$ copy <source_file(s)> <destination_directory>’
Move –
‘$ move <source_file(s)> <destination_directory>’
Rename –
‘$ rename <old_filename> <new_filename>’
a. Eg–
‘$ copy foo.txt bar.txt baz.mp4 ~/foobar move foo.txt bar.txt baz.mp4 ~/foobar rename foo.txt bar.txt’
        
b. Assume that the destination directory exists, and you have write permissions.
c. Copying/Moving directories should also be implemented
d. The file ownership and permissions should remain intact
2. Create File –
‘$ create_file <file_name> <destination_path>’
Create Directory –
‘$ create_dir <dir_name> <destination_path>’
  a. Eg – ‘$ create_file foo.txt ~/foobar ‘$ create_dir foo ~/foobar’
3. Delete File –
‘$ delete_file <file_path>’
Delete Directory –
‘$ delete_dir <dir_path>’
create_file foo.txt’.
  a. On deleting directory, you must recursively delete all content present inside it .
4. Goto –
‘$ goto <location>’
a. Eg – ‘$ goto <directory_path>’
5. Search –
‘$ search <file_name>’
or
‘$ search <directory_name>’
a. Search for a given file or folder under the current directory recursively.
b. Output should be True or False depending on whether the file or folder exists
6. On pressing ESC key, the application should go back to Normal Mode
7. On pressing q key in normal mode, the application should close. Similarly, entering the ‘quit’ command in command mode should also close the application.
 
- All the commands should work with both Absolute and Relative paths. Note: in absolute path whole path will be given where as in relative path, path from root folder will be given.

## How to Run:
Enter g++ main.cpp on Terminal
Then ./a.out 