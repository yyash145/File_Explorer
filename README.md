## Fully Functional File Explorer Application, with a restricted feature set.
### File Explorer works in two modes :-
1. Normal mode (default mode) - used to explore the current directory and navigate the filesystem 
2. Command mode - used to enter shell commands
- The root of this application is same as the system, and the home of the application is same as home of the current user.
- The application displays data starting from the top-left corner of the terminal window, line-by- line.

### Normal mode:
Normal mode is the default mode of your application. It has the following functionalities -
1. Display a list of directories and files in the current folder
- Every file in the directory should be displayed on a new line with the following attributes for each file -
  - File Name
  - File Size
  - Ownership (user and group) and Permissions
  - Last modified
- The file explorer shows the entries “.” and “..” for current and parent directory respectively.
- The file explorer handle scrolling using the up and down arrow keys.
- User is able to navigate up and down in the file list using the corresponding up and down arrow keys.

2. Open directories and files When enter key is pressed -
- Directory - Clear the screen and navigate into the directory and show the directory contents as specified in point 1.
- File - Open the file in the editor.

3. Traversal
- Go back - Left arrow key should take the user to the previously visited directory
- Go forward - Right arrow key should take the user to the next directory
- Up one level - Backspace key should take the user up one level
- Home – h key should take the user to the home folder

### Command Mode:
- The application enters into the Command button whenever “:” (colon) key is pressed. 
- In the command mode, the user is able to enter different commands. 
- All commands appear in the status bar at the bottom.
1. Copy 
- ‘$ copy <source_file(s)> <destination_directory>’
  - Eg. $ copy foo.txt bar.txt baz.mp4 ~/foobar
2. Move
- ‘$ move <source_file(s)> <destination_directory>’
  - Eg. $ move foo.txt bar.txt baz.mp4 ~/foobar
3. Rename
- ‘$ rename <old_filename> <new_filename>’
  - Eg. $ rename foo.txt bar.txt
  - Assume that the destination directory exists, and you have write permissions.
  - Copying/Moving directories should also be implemented
  - The file ownership and permissions should remain intact
4. Create File
- ‘$ create_file <file_name> <destination_path>’
  - Eg. $ create_file foo.txt ~/foobar 
5. Create Directory 
- ‘$ create_dir <dir_name> <destination_path>’
  - Eg. $ create_dir foo ~/foobar
6. Delete File 
- ‘$ delete_file <file_path>’
  - Eg. $ delete_file ~/foo.txt
7. Delete Directory 
- ‘$ delete_dir <dir_path>’
  - Eg. $ delete_dir ~/foobar
  - On deleting directory, it recursively delete all content present inside it .
8. Goto
- ‘$ goto <directory_path>’
  - Eg. goto ~/Documents
9. Search 
- ‘$ search <file_name>’
             or
- ‘$ search <directory_name>’
  - a. Search for a given file or folder under the current directory recursively.
  - b. Output is True or False depending on whether the file or folder exists.

- On pressing ESC key, the application go back to Normal Mode.
- On pressing q key in normal mode, the application close. 
- Similarly, entering the ‘quit’ command in command mode closes the application.
- All the commands work with both Absolute and Relative paths. 
  - Note: In absolute path whole path will be given where as in relative path, path from root folder will be given.

## How to Run:
- Enter g++ main.cpp on Terminal
- Then, ./a.out 
