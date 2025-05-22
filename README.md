# Kela Editor
A Vim-based Text Editor that emphasizes on modal editing

## Edit modes:

### Normal Mode:
Program starts in normal mode.  
**Navigation**: arrow keys  
**Mode switch**: `i` -> insert, `v` -> visual  
**Editing**: `x` -> delete, `dd` -> delete full line  

### Insert mode:
Press `i` to swith to insert mode.  
This mode will allow you to insert characters in the text dynamically.  

Handles chars directly and *inserts* into buffer.

`esc` to go back to normal mode.  

### Visual mode:
Press `v` to switch to insert mode.  

**Starts selection** from cursor.  
Tracks current cursor and start of selection.

`esc` to go back to normal mode.

## Credits
HappyFlyingGamer
