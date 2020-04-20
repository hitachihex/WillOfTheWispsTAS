# WillOfTheWispsTAS
TAS tools for WOTW.

# NOTE: ONLY WORKS ON CURRENT PATCH.

To use the tool, run WOTW.TAS.Injector.exe after running the game executable, make sure WOTW.TAS.dll is in the same directory as the injector executable. You will need to run the injector (and possibly the game) as administrator.

Note: inject once you are in main menu, otherwise issues can arise with pointers being grabbed too early.
(I can fix this but it wasn't priority atm)

Run Buggy.exe to for overlay display of commands being executed, and to show Position\Speed\Cursor pos, etc.

Hotkeys are configurable with the in-game rebind menu (default to toggle it is F8)
To rebind, press the button and then press the key you would like to assign it to.
You may use modifiers : Shift, Ctrl or Alt. (Does not distinguish between Left or Right variants)
# NOTE: Some combinations are disallowed to prevent some very annoying side effects if you manage to somehow find a combination that breaks everything, delete Config.ini
# in the directory where oriwotw.exe is located.

For playback, create a file called Ori.rec in the directory where oriwotw.exe is located.

Default hotkeys are:

F1 - To pause\unpause

F4 - Toggle playback, read from Ori.rec in the directory where the game executable is located.

F8 - Toggle in-game menu for rebinding hotkeys.

# NOTE: This is a bit of a defunct feature now currently, as it displays information 1 frame late.
# When using Buggy, you will always see the status of Ori after *everything* has executed.
F9 - Toggle display of in-game OSD 

Ctrl + Right click -  to move top left corner of in-game OSD to cursor location in-game.


Ctrl + Numpad 1 - Copy ingame cursor position to clipboard (delimited by comma: x,y and as you see it in Buggy\ingame OSD)

Ctrl + Numpad 2 - Copy player position to clipboard (delimited by comma: x,y)

Ctrl + Numpad 3 - Copy player speed to clipboard ( delimited by comma: x,y)

--------------------------------------------------------

[ - To step one frame (this also reloads the input file so you can make changes to the inputs while framestepping.)<br/>
Note: It won't understep (e.g go backwards and redo) you can only edit a current input or inputs currently not being
      played back.


--------------------------------------------------------

Commands read from input file are in the format of:
   frames, Action
   
Commnds are case-insensitive.
   
Accepted commands are: <br />
    Runto - to be placed under a line you want to fast forward playback to, then the game will pause (note, no frames for this command)<br />
    Walkto - to be placed under a line you want to normal speed playback to, then the game will pause (note, no frames for this command)<br />
    Left <br />
    Right <br />
    Up <br />
    Down <br />
    Jump <br />
    Action <br />
    MenuSelect <br />
    Dash <br />
    Bash <br />
    Grapple <br />
    AbilityWheel <br />
    Rng, Random, Seed - for setting the random seed of the game e.g Seed, 80085 <br />
    Pos  - for setting oris position, in form of Pos,xpos,ypos <br /> 
    Load - for loading a checkpoint. <br />
    Mouse - set mouse pos e.g Mouse, xpos, ypos -- values clamped to viewport from top left of game window as 0.0, 0.0 <br />
    Wheel <br />
    Glide <br />
    Grab <br />
    Angle - for setting an angle to aim your launch, bash, etc in degrees e.g Angle, 90<br /> 
    Start <br />
    Inv or Inventory <br />
    Select or Map <br />
    MenuLeft <br />
    MenuRight <br />
    Pause <br />
    Ability1 <br />
    Ability2 <br />
    Ability3 <br />
    Cancel <br />
    Select <br />

	




