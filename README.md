# [Unreal Arena 3](https://github.com/SAEagle/unrealarena3)
<img width="365" alt="Splash" src="https://user-images.githubusercontent.com/5038930/190905057-5dbc8f95-51a2-4ff7-a1fd-076510c0de23.png">

The main goal of this project is to recreate Quake3 Arena in the UE5. 
At maximum add the multiplayer support. But at the current stage, there are a lot of needs to be done from the effects and the character animations. 
For the current VFX stage, placeholders were used.
Since UE is using skeletal animation only, but original animation from Quake is frame-based. 
For the beginning, I will use retargeting for the animations from UE engine samples. 
Later I'll need to manually reframe original animations for every bot character to the rigged skeletons. 

Simple goals breakdown of the project:
- [x] Move all the geometry with material to UE5
- [ ] Recreate all VFX with Niagara(current stage - placeholders or test versions)
- [ ] Recreate character animations
- [ ] Local Multiplayer support
- [ ] Improve Bot logic


Tools used during the process: 
- Q3a - 1.32c  version 
- Noesis v4466 - https://www.richwhitehouse.com/ - for geometry
- GtkRadiant 1.6.6 - https://icculus.org/gtkradiant/ - for level design 
- Blender - https://www.blender.org/ - used for fixing the models geometry with md3 plugin
- VS Community + .clang format for the code

Unreal Arena Project. All rights under (CC BY-NC 3.0) S.A. development

(This project may only be used in Unreal Engine projects as per the Unreal Engine EULA)
 
