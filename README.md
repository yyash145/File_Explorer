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
- Then run ./a.out 

## Explaination
- First of all, we find the current working directory and enable canonical mode, i.e., a read request will not return until an entire line has been typed or a signal has been received.
- Then, we list data of the top 15 files and directories in that directory(using struct dirent).
- Data includes, File name, File Size, Ownership, Permissions(using struct stat) and Modification Date.

- In Normal Mode, we use the ASCII value of UP and DOWN keys to move the pointer while LEFT and RIGHT keys to traverse, i.e., fo back and go forward respectively(using stack).
- Enter key is either used to open a file or go through a directory and backspace key is used to go one level up.
- h button is used to go to home directory and q is used for exit.
- If we want to go through Command mode, we type colon ":".

- In command mode, we are still in canonical mode, but can give any command we want by simply typing that command.
- If our command is "esc", then we will be in Normal Mode, if it is "quit", then we will exit while "enter" will follow our command while "backspace" will remove the last character.
- For copy, we make the destination directory, if it doesn't exist, than make a file an copy all the content in it character by character.
- For move, we just rename the file wrt source and destination address.
- For rename, we use inbuilt rename function, which renames the file on its own.
- For creating file, we simply use creat function, which is similar to "touch" in LINUX but giving read and write to owner and no permission to groups and others.
- For creating folder, we use mkdir function with read, write, and execute permissions for the owner of the directory, and read and execute permissions for groups and others.
- For delete files, we use remove function to delete the argumented file.
- For deleting directory, we recursively delete all the files and content within it.
- For goto, we simply change the path and list all the files to that corrosponding path.
- For search, we recursively compare the files or directory under the current directory and returns True/False.

- struct "dirent" is a structure defined in the C standard library that represents a directory entry. It typically contains information about a file or directory within a directory, such as its name and file type.
- struct "stat" is a structure defined in the C standard library that is used to store information about a file. It typically contains various fields that provide details such as file size, file permissions, file type, timestamps, and other attributes associated with the file.

