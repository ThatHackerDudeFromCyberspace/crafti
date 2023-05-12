[![CI](https://github.com/Bluebotlaboratories/crafti/actions/workflows/CI.yml/badge.svg)](https://github.com/Bluebotlaboratories/crafti/actions/workflows/CI.yml)

Crafti
======

3D Minecraft for TI Nspire CX calculators running Ndless  
Thread on omnimaga: http://www.omnimaga.org/ti-nspire-projects/ngl-a-fast-(enough)-3d-engine-for-the-nspire/

Screenshots
-----------

![Crafti Redstone](.github/images/crafti_redstone.gif)
![Crafti Help](.github/images/crafti_help.png)  
![Crafti Menu](.github/images/crafti_menu.gif)
![Crafti List](.github/images/crafti_v1.0_list.png)
![Crafti Showcase](.github/images/crafti_showcase.png)
![Crafti Pistons](.github/images/crafti_pistons.png)
![Crafti More Pistons](.github/images/crafti_morepistons.png)

How To Run
--------

Simply download the `crafti.tns` file from the latest release in the [releases](https://github.com/Bluebotlaboratories/crafti/releases/latest) section in GitHub and copy it over to your calculator.
Then, simply locate the copied `crafti.tns` file on your calculator, and run it

NOTE: Crafti requires a [jailbroken](http://ndless.me/) calculator to run and will not work without Ndless


Controls
--------

Move around using the numpad: 8-4-6-2  
Jump using 5  
Switch the current inventory slot with 1 and 3  
Open a list of blocks with "."  (Screenshot with CTRL+.)
Set the current inventory slot with 5 while the block list is open  
Put a block down with 7 (or select) and destroy a block with 9  
Open the menu with menu, move the cursor with 8-2 and select it with 5  
The +/- buttons let you change the render distance  
ESC/HOME is a shortcut for "Save & Exit"  



## Crafti now supports keyboard and mouse input with an OTG cable:
Note: This is experimental and may not work as expected

Move around using WASD like standard minecraft  
Jump using space  
Switch the current inventory slot with Z and C  
Open a list of blocks with E (screenshots are possible with CTRL+E and CTRL+.)  

Place a block with 7, select or LEFT MOUSE CLICK  
Remove a block with 9 or Q  
+/- let you change the render distance  
Open the menu with R, move the cursor with the arrow keys and select it with left click or enter  
Menus can also be navigated with WASD  

ESC is still a shortcut for "Save & Exit"  


Limitations
-----------

Crafti doesn't use floats, so there will be some graphical inaccuracies.


Contributors
-----------
<!-- readme: contributors -start -->
<table>
<tr>
    <td align="center">
        <a href="https://github.com/Bluebotlabz">
            <img src="https://avatars.githubusercontent.com/u/69104218?v=4" width="100;" alt="Bluebotlabz"/>
            <br />
            <sub><b>Bluebotlabz</b></sub>
        </a>
    </td>
    <td align="center">
        <a href="https://github.com/Vogtinator">
            <img src="https://avatars.githubusercontent.com/u/1622084?v=4" width="100;" alt="Vogtinator"/>
            <br />
            <sub><b>Fabian Vogt</b></sub>
        </a>
    </td>
    <td align="center">
        <a href="https://github.com/m-doescode">
            <img src="https://avatars.githubusercontent.com/u/80221594?v=4" width="100;" alt="m-doescode"/>
            <br />
            <sub><b>M-doescode</b></sub>
        </a>
    </td></tr>
</table>
<!-- readme: contributors -end -->
  
Textures from PureBDcraft ResourcePack by https://bdcraft.net, more info available in the [wiki](../../wiki/Crafti-textures)

Development
-----------
Crafti is written in C++, so an understanding of the language is recommended, documentation of how each piece of the code works, including tutorials is available:
In the [Wiki](../../wiki)

TODO for next version
-----------
- [x] Add wool
- [x] Add experimental keyboard support
- [x] Add wool as special block instead of 15 regular blocks
- [x] Add cactus
- [x] Implement special block destruction particle rendering
- [x] Make cake edible
- [x] Add slabs
- [x] Add carpet
- [x] Add basic pistons
- [x] Add advanced pistons (push limit of 12)
- [x] Add redstone block
- [ ] Commands, maybe?
- [ ] Add texture pack converter for more blocks
- [ ] Add localisation
- [ ] Add villager house generation to make world more lively
- [ ] Documentation of functions and whatnot for future devs (mostly me)
