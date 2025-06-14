# 🔥 Inferno Editor
A Vim-based Text Editor that emphasizes on modal editing

## Edit modes:

### Normal Mode:
Program starts in normal mode.  
**Navigation**: `h` : go left, `j` : go down, `k` : go up, `l` : go right  
**Mode switch**: `i` -> insert, `v` -> visual  
**Editing**: `x` -> delete, `dd` -> delete full line  

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

For now Inferno Editor only has the ability to create and save files as well as overwrite existing files with the text written.  
But we will add the functionality of opening files in a later Patch.

## Credits
Safi Ullah