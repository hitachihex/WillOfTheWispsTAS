# WillOfTheWispsTAS
TAS tools for WOTW.

To use the tool, run WOTW.TAS.Injector.exe after running the game executable, make sure WOTW.TAS.dll is in the same directory as the injector executable. You will need to run the injector (and possibly the game) as administrator.

Note: inject once you are in main menu, otherwise issues can arise with pointers being grabbed too early.
(I can fix this but it wasn't priority atm)

Run Buggy.exe to for overlay display of commands being executed, and to show Position\Speed\Cursor pos, etc.

Hotkeys aren't configurable, input file is created for you if it does not exist.

In the directory where the game executable is, you can create it however if you want, it looks for Ori.rec.

Hotkeys are basic:

F1 - to pause\start framestep.

F4 - start playback, read from megaman.rec in the directory where the game executable is located.

--------------------------------------------------------

[ - To step one frame (this also reloads the input file so you can make changes to the inputs while framestepping.)<br/>
Note: It won't understep (e.g go backwards and redo) you can only edit a current input or inputs currently not being
      played back.


--------------------------------------------------------

Commands read from input file are in the format of:
   frames, Action
   
Accepted commands are: <br />
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
    Pos <br /> - for setting oris position, in form of Pos, <x pos as float>, <y pos as float>
    Wheel <br />
    Glide <br />
    Grab <br />
    Angle <br /> - for setting an angle to aim your launch, bash, etc in degrees.
    Start <br />
    Pause <br />
    Ability1 <br />
    Ability2 <br />
    Ability3 <br />
    Cancel <br />
    Select <br />

	




