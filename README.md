# CSGOInternal

This is a simple internal mod for CS:GO written in C++. The project should be compiled to a DLL file, which will then be injected into the csgo.exe process. The mod contains several features that assist the user.  
This project dealt with a lot of reverse-engineering & researching of the Source SDK, in order to understand how the game works.
Additionally, I was required to learn quite a bit about the Windows API to understand how to interact with the game's process. Like most other internals, it also incorporated concepts such as memory addressing, hooking and so on.

# Usage
This project is not regularly updated. It is very possible that by the time you're reading this the SDK is outdated, and at the very least the memory offsets are outdated (you can find updates ones at https://github.com/frk1/hazedumper/blob/master/csgo.hpp).  
If you still want to try your luck and test this project, download it & compile it into a DLL. Then, use any DLL injector you'd like (feel free to use mine: https://github.com/AdamOron/DLLInjector) to inject the compiled DLL into the csgo.exe process once its running. **Note that you should already be ingame once you inject the DLL, and not in a waiting lobby.**  
The END key will stop the mod.

# Features
The actual features are located under `src/features`.  
The feature list includes an Aimbot, Triggerbot, Backtrack, Glow ESP, Chams ESP, BunnyHop.

# Hooking
I created a VMT hooking lirbary, it's stored under `src/hooks` and it allows very simple hooking of virtual-functions.  
This library was used for all hooking purposes in this project. I am not sure if this library is detected by VAC or not, as I never tested this online.

# SDK
The game's SDK is located under `src/sdk`.  
Most of this code is pasted from the Source SDK, it is not my own code but rather the code that the game uses.  
**I will probably not continue updating this SDK and any of the memory offsets, so it is very likely that they will become outdated.**
  
# DISCLAMER
**This project was created for educational purposes only, using a CS:GO account that has no access to online servers. It has only been tested against bots and was never intended to be used against actual players.  
PLEASE DO NOT USE THIS PROJECT DISHONESTLY. I AM NOT LIABLE FOR ANY DAMAGE CAUSED BY USAGE OF THIS PROJECT.**
