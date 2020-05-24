```
                         _                        _           
__      _____ _ __   ___| |_ __ _ _   _ _ __ | |_| |__  _ __ ___  __ _  __| | ___ _ __ 
\ \ /\ / / _ \ '_ \ / _ \ __/ _` | | | | '_ \| __| '_ \| '__/ _ \/ _` |/ _` |/ _ \ '__|
 \ V  V /  __/ | | |  __/ || (_| | |_| | | | | |_| | | | | |  __/ (_| | (_| |  __/ |   
  \_/\_/ \___|_| |_|\___|\__\__,_|\__,_|_| |_|\__|_| |_|_|  \___|\__,_|\__,_|\___|_|   
```

Hello, my name is spv.

I work for (and am a founding member of) w212 security research.

In this writeup, I will be discussing my findings of "wenetaunthreader", an untether for iOS 9.2.1 -> 13.5.

```
 ___________________________
|                           |
| Sections:                 |
| 1  What is Guided Access? |
| 2  DISCLAIMERS!!!         |
| 3  The fun stuff          |
|    3.1 Testing            |
| 4  libapatchy - an auto-  |
|    matic patchfinder      |
|                           |
 --------------------------
 ```

# Section 1
### what is Guided Access? 
Well, Guided Access is a feature in iOS, introduced in iOS 6<details>
<summary>[1]</summary>

I actually don't know if it was introduced in iOS 6, that's just the best info I could find.

If anyone has a good source for it, please contact me!</details>that allows the user to confine the device to a single application. It even persists across reboots!
So, how do we take advantage of this?

# Section 2
### DISCLAIMERS!!!
Warning! I am NOT RESPONSIBLE if you fuck your device!!!
If you're running a firmware you would like to keep, obviously maybe don't do this.
Please don't blame me if you end up erasing /var and bootlooping your device! 
Also, this isn't very useful for spyware, because it is unable to be stealthy really in any way. 
### Requirements
You will need to install `Python` (from saurik if available, or on newer devices, from bingner), and `Core Utilities`.

# Section 3
### The fun stuff

Let's do this. 

```bash
$ # enable and disable Guided Access in jailbreak application, to prepare everything.
$ cp -R /User/Library /tmp/_TL1
$ # enable Guided Access
$ cp -R /User/Library /tmp/_TL2
```

Ok, so now we have the /var/mobile/Library folder in 2 states, when it is in Guided Access, and when it isn't.
Great!

Let's see the difference between the two.

```bash
$ diff -rq /tmp/_TL*
Files /tmp/_TL1/Accessibility/GuidedAccessState and /tmp/_TL2/Accessibility/GuidedAccessState differ
Files /tmp/_TL1/AggregateDictionary/dbbuffer and /tmp/_TL2/AggregateDictionary/dbbuffer differ
Files /tmp/_TL1/Assistant/SiriAnalytics.db and /tmp/_TL2/Assistant/SiriAnalytics.db differ
Files /tmp/_TL1/CoreDuet/Knowledge/knowledgeC.db-shm and /tmp/_TL2/CoreDuet/Knowledge/knowledgeC.db-shm differ
Files /tmp/_TL1/Preferences/com.apple.Accessibility.Collection.plist and /tmp/_TL2/Preferences/com.apple.Accessibility.Collection.plist differ
Files /tmp/_TL1/Preferences/com.apple.Accessibility.GuidedAccess.plist and /tmp/_TL2/Preferences/com.apple.Accessibility.GuidedAccess.plist differ
Files /tmp/_TL1/Preferences/com.apple.springboard.plist and /tmp/_TL2/Preferences/com.apple.springboard.plist differ
```

Now, let's do some testing.

## Section 3.1
#### Testing
                                                      
Ok, so let's try something.

If we copy the files above from _TL2 into /User/Library, and kill backboardd, we should go into the app, right?

Let's try it.

See notes <details>
<summary>[2]</summary>

This almost certainly WILL fuck up celluar service on celluar devices when not jailbroken.

This is not recommended, for the above reason. This is only for learning purposes and pacing of the writeup, thank you.</details> before doing this. 

```bash
$ cp -R /tmp/_TL2/* /User/Library/
$ killall -9 backboardd
```
And wait...

And wait...

And.........

It works, we're in the app! :D

If this didn't, see notes <details>
<summary>[3]</summary>

Sometimes this will not work due to permissions issues.

If it does not, try doing the same, but `chown -R mobile /var/mobile/Libary && chmod -R 777 /var/mobile/Library` as well. </details>

Now, let's try copying the files from _TL1, and we should go into the home screen, right?

Let's find out.

```bash
$ cp -R /tmp/_TL1/* /User/Library/
$ killall -9 backboardd
```

And wait...

And wait...

And.........

Again, if this didn't, see notes <details>
<summary>[3]</summary>

If it does not, try doing the same, but `chown -R mobile /var/mobile/Libary && chmod -R 777 /var/mobile/Library` as well. </details>

It works! We're on the home screen! :D
# Section 4

### libapatchy - the only patchfinder with a sexual identification

libapatchy's source code is available at https://www.github.com/spacepilotAV/apatchy.

Download the code, and extract it to /jbin/. (oh yeah you also have to mkdir /jbin ;)


Let's make some patches.

NOTE:

Where it says python3, if you are are on an old enough version, that must be changed to python, rather than python3. 



```bash
$ mkdir -p /npatch/
$ cp -R /tmp/_TL* /npatch/
$ cd /npatch/
$ yes | python3 /jbin/apatchy.py _TL* &>/dev/null
$ ls
_TL1  _TL2  dajb/  dajb.tar  enjb/  enjb.tar
```

Great! Now we have our patches.

Now, to test the patches, download the wenetaunthreader binaries (bins.tar) from https://github.com/spacepilotAV/wenetaunthreader, and extract it with tar to /.

Now, run `chmod +x /usr/bin/*` to fix permissions.

Now, run `enjb && killall -9 backboardd`

Your device should load the jailbreak app on respring.

Now, try `dajb && killall -9 backboardd`

Assuming your device acts normally and just goes to the lock screen, your patches should be functional!

Now, download the wenetaunthreader launchdaemons (unthreader.tar) from https://github.com/spacepilotAV/wenetaunthreader, and extract it with tar to /.

Now, reboot once, and jailbreak.

Wait about 1 - 3 minutes, and reboot again.

Assuming everything is functional, your device should auto-load the jailbreak app of your choosing.

Now jailbreak, and it should respring normally. Sometimes, it will respring back into the app, and after 15 seconds - 1 minute it will respring again normally.


Regardless, assuming you followed everything correctly, you now have an untethered jailbreak! Congratulations!

```%##(/*,,,,,,,*,,**//((####%%%#((##%##########(////////*,,..,,,****/(((///////********/////(/(#%&&&%&%((//(((((((((//////////////////////////
%#%#(/,,.,,,,,,,,,,,,,*((##(((//#%&&&%%%%%%#(/*////*,,*****/(#(/////********,,,,,*///////(#(/*/(((#%%(#(((#(#####((/////////////////////////
%%%##(*,,,,,,,,,,,,,**/(####(####&@@&&%%%%#####(/,**/(#((//****//(((######(((((((##%##%%%%%%####(///((#######(((//////**///***//////////////
%%###(/*************//(######((##((%%%%%%%##((//(((/*,*/(#######((((///////(((((((##(((((//((/((/////*,,*(((((/**,,,,*************//////////
&%%###(/********//////((####((((###(####%##((/**////(#####(((((////////////********,***,,.,**//*,,****(#(**(((/****////**,,,,,,,******//////
&%%%#(((//******/((((((#####(((##((((#%%#(///////((##(((////(((/(((((////***//////*,*/***/*,.,*/*//,..***(//(((((((((//////***,,,,,,*****///
&&%%###((////////((##((((##((((###(##%%#(((/*/(####(/***/////(///////**,,,,,,,,,*///******/(*..,//**,,,,/,///((##((((((#######((//*,,,,,****
&&%%#####((//////((###((((((//(####%&%(//////(#(///*////*****////*****///////*,*//*,/***,*///*,,,*/(/*,,**/**/(((%%##((#############(((///**
&&&%%#####(/(////((###((((((//((#####(**(/*/(/////*/(((//(//(((((((/((((((//////(((//////(////****/////*//***///(&@&%/////((((((((####%%####
&&&%%%%%##(///////((##(////(///(##(/(//**//////*//((####################%###################(/(((/((///*///*//*((((//(/((((((#######%%%%%%#%
&&&&%%%%%#(((((///(##((////((//(#((/****/((//(((((#%%%%%%%%%%%%%%%%%%%&&&&&&&&&&%%%%%%%%%%%%%######(#(/////////((((((((########%%%%%%%%%%%%%
&&&&%%%%%#(((((///(((((///((///((#(/***(//(#((((##%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&%%%&%%####(((//(((((//##########%%%%%%%&&&&&&%
&&&&%%%%%##(((///(((##(///((///((#/,,*/*/#(#((#%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%%##((((##(/(########%%%%%%%%%&&&&&%
&&&&&&&%%%#(((((//((##(//((((//(((*,,,*///(#####%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%%##(##(((#########%%%%%%%&&&&&&&%
&&&&&&&%%%#((((((((###((//((((/((/,,,,***/(####%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&&&&&&&&&&&&&&&&&&%%#####(((#######%%%%%%%%%&&&&&&%
&&&&&&&&%%#(((((((#####((((((((((*.,,,,,*/####%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@@&&&&&&&&&&&&&&&&%#(((#(((######%%%%%%%%%%%%%&&%%
&&&&&&&&%%#(((((((#####((((((((((*,,,,,*/((###%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@@@&&&&&&&&&&&&&&&&####/(((#%####%%%%%%%%%%%%%%%%%
&&&&&&&&%%#((((((######((((((((##/..,***/((##%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@@@&&&&&&&&&&&&&&&&%%##(((/#%###%%%%%%%%%%%%%%%%%%
&&&&&&&&%%#(///(###%###((((#%%%##/*,,*/*/(#%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@&&&&&&&&&&&&&&&&&%%%%((((#%###%%%%%%%%%%%%%%%%%%
&&&&&&&&%%#(/(((###%###(((##(#%%%%%*,**/(#%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@&&&&&&&&&&&&&&&&&%#######%%##%%%%%%%%%%%%%%%%%%%
&&&&&&&&%%#(/(((###%###(((###%%&&%%%(**/(%%%%%%%%%%%#%%#%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@&&&&&&&&&&&&&&&&%%##(((#%%%%%#%%%%%%%%%%%%%%%%%%%
&&&&&&&&%%#(((((#########((%%&&&%%%%#**(#%%&%%%%##((((((((((/(((##%%&&&&&&&&&&&&&&&&&&&&@@&&&&&&&&&&&&&&&&&#(((//(##%%%%%%%%%%%%%%%%%%%%%%%%
&&&&&&&&%%##(((###########(%%%%%#((%#//(%%%%%%%%%%%%%##(#(((/******/(#%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%/*/(*/##%%%%%#%%%%%%%%%%%%%%%%%%%
&&&&&&&&%%##(((############%%##%#(#%#*(%&&&&%%%%%%##((//(**,.,**/(#####%%%%&&&&&&&&&&&&&&&&&&&&&&%&&&&&&&%/,,**/((####%##%%%%%%%%%%%%%%%%%%%
&&&&&&&%%%##((#############%#//#&&&%%(%%&%&&&&&%%%%%%%%%#(/****//(//#%%%%%%%%%%%%&&&%%%%%#(((((/((###%&&&#*,*/##((((##%##%%%%%%%%%%%%%%%%%%%
&&&&&&&%%#########(########%%#((%%&%#(#%&&&&%%%&&&&%%%%%%%%%%%%%#///#%%%%%&&&&&&&%%%##(//*****//((((((((##*,(##%((((#####%%%%%%%%%%%%%%%%%%%
&&&&&&&%%########((((#####%%%&&&%##&%/#%%%&&&&%&&&&&&&%%%%%%%%%%%%%%%%%%%&&&&&&&&&%%%#////*,*//#///(#%%##(*(%#%((/(#######%%%%%%%%%%%%%%%%%%
&&%%%&&%%#########(((((###%%&&&&&&&%%/(%%&&&&&&&&&&&&&&&&&&&&&&%%%%%%%%%%%&&&&&&&&&&%%####%##%%%%%%##&%&%((%%%#((/(#######%%%%%%%%%%%%%%%%%#
%%%%%%%%%%########(((((###%%&@&%&&&%#/(%%%%&&&&&&&&&&&&&&&&&&&&&&&%%%%%%%%&&&&&&&&&&%%####%%%&&&&%&&&&&&#/(%&%#((((#######%%%%%%%%%##%%%%###
%%%%%%%%%%########(//((##%@@@@@@&%%#(/(%%%%&&&&&&&&&&&&&&&&&&&&&&%%%%%%%%&&&&&&&&&&&&&&&&%%%%%%&&&&&&&&&(/#&%##((((########%%%%%%#####%%####
%#%%%%%%%#(((((##(((((##&@@@@@@@&%%(//(#%%%%%%%&&&&&&&&&&&&&&&&&&&%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&&%((%&%#((((((#########################
#########((((((#########%&@&%%%%%%%/*/(#%%%%%%%%&&&&&&&&&%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&&&&&&&&%#&&%//////(((((((((###(((((((((#####(
%%%%%###%%%%%%%%%%%%%%%%%#(#@@@&%%#///*(#%%%%%%%%&&&&%%%##%%%%%%&%%%%%%%&&&&&&&&&&&&&%%&&&&&&&&&&&&&&&&@&%(((//////(((((((((((((((((((((##((
%%%%%%%%%%%%%%%%%%%%%%%%%(/(%&&%%%%(*//((##%%%%%%%%%###%%%%%%%%%%&&%%%%&&&&&&&&&&&&&&%##%%&&&&&&&&&&&&&&%(((((((((((((((((((((((((((((((((((
&&&&&%%%%%%%%%%%%%%%%%%%#/*(%%%%%%#***//(((#%%%%%%(###(#########%%#%%%%%&&&&&&&&&&&&%%%#(#%&&&&&&&&&##################((((((((((((((((((((((
&%%%%%&%&%%%%%&%%%%%%%%#/,/%%%%%%%%/,***((((#%%%%###(((##((/////*/*/**((#####((####%%%%%#/(#%%&&%&%########################(((((((((((((((((
&%%%%%%%%%%%%%&&&%%%(/*/#%%%%%%%%%#/,,**////((#####(((((((##(((((((///(######((///((######(#%%%%%#/(#######################(((((((((((((((((
&%%%%%%%%%%#(/*,,,..,(#%%%%%%%%%%%#/,,,**///(/(###(((/*.,#%%#####%##%%%%%#%%#####((((((((##%%%%#//(####################(((((((((((((((((((((
%%&&%#(/,..........,#%%%%%%%%%%%%%%(,,,,,*///(((/(((%%%/..,/&&&&&%&&%%#%#######%#((/((/((#%%%#(/(####################(((((((((((((((((((((((
#/,...............,/##%%%%%%%%%%%%%#/,,,***////((((#%%%%#*.,/##((#%&&&&@@&&&&%%/,./##((####//**(###################(((((((((((((((((((((((((
..................,/##%##%#%%%%%%%%%#*,,,,,*//((###%%%%%%%#*,/(#(((((#####%%%#**#%&%#(##((/***(####################(((((((((((((((((((((((((
.................../###%#%%%%%%%%%%%%#/,,****/(###%%%%&%%%%%%##(#%%%%%%&%%#(/(%%%&&&%##(/***/#####################((((((((((((((((((((((((((
...................,/(##%%%%%%%%%%%%%##/,,***//(#%%&%%%%%%%%%%%%%%##%#%%###%%%%%%&%%%#(/*,,,*/(##################(((((((((((((((((((((((((((
....................,*/(#%%%%%%%%%%%%%##*,,**//((%%&&%%&%%%%%%####%%%%%%%&%%%&&&&%%%#(***,......*(#############(((((((((((((((((((((((((((((
......................,*#%%%%%%%%%%%%%%%#/,,***/#%%%&&%%&&&%%%%%%########%%&&&&&&%%#(**,,,........*(##########((((((((((((((((((((((((((((((
........................,#%%%%%%%%%%%%%###(***//(#%%%&&&&&&&%%%###(#####%%%&&&&&&%#(/**,............*(######((((((((((((((((((((((((((((((((
..........................(%%%%%%%%%%%%%#%%#(*,*/(##%%%%%%%%%%#####(((#%%%&&&&%%%#/**,...............,/###((((((((((((((((((((((((((((((((((
...........................,#%%%%%%%%%%%######/**/((####%%%%%%%#######%%%%%%%%%%(/**,.................,/(((((((((((((((((((((((((((((///////
............................../%%%%%%##########(/***(#((######(#(#########%###(//*,....................,/(((((((((((((((((((((((((((////////
................................*#%############((////////(#((##((((######(##(///,,......................,((((((((///(((/////////////////////
.................................../######((#((((((((((*/*/(////(((((((((///**,..........................*///*******************************
......................................,(#((((((///(((((((((/(///////////**,,,............................,**,*******,,,,,,,,,,,,,,,,,,,,,,,,
..........................................,*//(((((###(#####%%(,,,,,,,,,.,...............................,,,,,,*****,,,,,,,,**,,,,,,,,,,,,,,
................................................,****,,,,,,..............................................,*,,,,,,*,,,,,,,,,,,,,,,,,...,,,,,,
```

\- spv
