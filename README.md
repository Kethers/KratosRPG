# KratosRPG

![Cover](./Docs/Imgs/Cover.png)

> [!NOTE]
>
> This project is originally hosted in [腾讯工蜂](https://git.code.tencent.com/Kethers/KratosRPG.git) community version. But something goes wrong with its git-lfs server and it makes me fail to mirror the repo with commit history to GitHub. According to the staff, community version of 腾讯工蜂 is no longer maintained. So I can only push the finished version project without commit history to GitHub.

## Introduction

KratosRPG is a God-of-War-like ARPG game demo using Unreal Engine 5.3.2.

It uses following techniques:

- Enhanced Input Component
- Gameplay Ability System
- Anim Montage and motion warping
- AI Behavior Tree

## Project Setup

Clone and open the .uproject with UE 5.3.2. Generate Visual Studio project files and build from project source might be needed.

## Input

Gameplay Inputs:

- Move: WASD
- Roll: Space
- Light attack: Mouse LB.  4 combos. 3 combo + mouse RB will trigger termination of heavy attack.
- Heavy attack: Mouse RB. 3 combos.
- Target Lock: Mouse Mid Button.
- Special Abilities: 2 abilities shown in below picture, activate with Alt + mouse LB/RB.

![SpecialAbilityIcon](./Docs/Imgs/SpecialAbilityIcon.png)

- Cure: Stand near by cure stone (heal/rage) and press E.
- Rage: Ctrl to activate rage mode when rage slot is full. Once activated, player will be invincible and unstoppable. 

## Gameplay Ability System

Heavily use GAS for player/enemy abilities’ implementations and extensions.

- Gameplay Ability: Weapon spawning, attack, death, hit react, combo, rolling, block, etc.
- Gameplay Effect: Start up, cooldown, rage cost, damage calculation, etc.
- Gameplay Cue: Attack warning, death sound, rage activation, block/perfect block, etc.

## Enemy

3 types of enemy: melee, ranged, boss

- AI: Behavior Tree with BT Tasks including AbilityTagCheck, ActivateAblityByTag, RotateToFaceTargetActor, etc. Also it’s combined with EQS Query to implement crowd behavior, and decorators to set up different condition to check AI node.

- Abilities: 

  - Attack(ed)
  - Unblockable attack (with VFX hint)

  <img src="./Docs/Imgs/UnblockableAttack.gif" alt="UnblockableAttack" style="zoom:50%;" />

  - Strafe
  - Chase
  - Death

  <img src="./Docs/Imgs/EnemyDeathVFX.gif" alt="EnemyDeathVFX" style="zoom:50%;" />

  - Summon(Boss exclusive)

## Player

- Basic: 4 combo light attacks and 3 combo heavy attacks with termination attack switching ability. 
- 2 special abilities with cooldown, activating with chorded input actions.
- Gain rage from attacking and rage stone for rage mode activation that makes player invincible.
- Block: Block attacks that is blockable and will not be hurt.

<img src="./Docs/Imgs/Block.gif" alt="Block" style="zoom: 50%;" />

- Perfect Block: Block blockable attack at the moment being hurt. It than can strike back with higher damage. You can see that Perfect Block has extra blurring VFX than normal Block.

| <img src="./Docs/Imgs/PerfectBlock.gif" alt="PerfectBlock" style="zoom:50%;" /> | <img src="./Docs/Imgs/PerfectBlock_StrikeBack.gif" alt="PerfectBlock_StrikeBack" style="zoom:50%;" /> |
| ------------------------------------------------------------ | ------------------------------------------------------------ |

- Target Lock: Lock enemy with mouse mid button, will adjust camera angle and walk speed.

## UI

- Player
  - Health Bar
  - Rage Bar
  - Special Ability Slot Icon
  - Weapon Slot Icon
- Enemy
  - Health Bar
  - Boss Health Bar
- Misc
  - Main Menu
  - Conclusion dialog



## Refs

[Unreal Engine 5 C++: Advanced Action RPG | Udemy](https://www.udemy.com/course/unreal-engine-5-advanced-action-rpg/?srsltid=AfmBOorXRMyX0i_iXaL34kWY1jodXOxzXdvbjOfgWuOCs9qVFEDifLFk&couponCode=KEEPLEARNING#instructor-1)

