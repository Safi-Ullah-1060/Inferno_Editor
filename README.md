# 🔥 Inferno Editor
A Vim-based Text Editor that emphasizes on modal editing.  
Inferno Editor uses ncurses for rendering output.  
**This is only supported on linux-based systems**

## Edit modes:

### Normal Mode:
Program starts in normal mode.  
**Navigation**: `h` : go left, `j` : go down, `k` : go up, `l` : go right  
**Mode switch**: `i` -> insert, `v` -> visual  
**Editing**: `x` -> delete, `dd` -> delete full line  
**Exit**: `q` -> exit, will ask to save file if unsaved  
**Save Current File**: `s` -> save, will ask to save the file with a new name if not already saved as file, otherwise will save with the current name of file  
**Open File**: `o` -> open, will ask to save the current file if unsaved, naming will be same as mentioned above  

### Insert mode:
Press `i` to swith to insert mode.  
This mode will allow you to insert characters in the text dynamically.  

Handles chars directly and *inserts* into buffer.  
`Backspace` removes a character one space left.  
Navigate with `arrow` keys  

`esc` to go back to normal mode.  

### Visual mode:
From Normal Mode, press `v` to switch to visual mode.  

**Starts selection** from cursor.  
Tracks current cursor and start of selection.  
Press `x` to delete the character followed by cursor.  
Pressing `x` also deletes the selection.  
Navigate with `arrow` keys.  

`esc` to go back to normal mode.

## File Management
For now Inferno Editor only has the ability to create, open and save files as well as overwrite existing files with the text written.

### Scrolling
**Due to lack of time, I was unable to embed a scrolling functionality.**  
This will be added in a later patch.  

## Credits
Safi Ullah