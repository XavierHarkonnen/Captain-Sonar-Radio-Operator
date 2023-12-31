# Gameplay Requirements

## Table of Contents

- [Gameplay Requirements](#gameplay-requirements)
  - [Table of Contents](#table-of-contents)
  - [Directional movements](#directional-movements)
  - [Surfacing](#surfacing)
  - [Systems](#systems)
  - [First Mate Tracking](#first-mate-tracking)
  - [Engineer Tracking](#engineer-tracking)


## Directional movements

Input, eliminates corresponding impossible spaces given edge of board/islands

## Surfacing
Sector Given, eliminates stored path

## Systems
- Sonar: One true and one false location, both cannot be true.
- Drone: Determine if they are or are not in a sector
- Torpedo: If they launch a torpedo, you can determine a specific area given range if they did not/did take any damage. Torpedoes you launch will tell location possibilities based on how much damage they do.
- Mine: You detonate a mine and amount of damage dealt will tell you info based on how much damage they take. Enemy laying a mine will tell you information as well (if a sub goes NNN-lays mine-ESSSE; you know they didn’t start at A4 and go to the northwest corner of the board since there would be nowhere to drop the mine). **Lastly, them announcing they detonated a mine reveals a good deal about their location since you know when they layed a mine.**
- Silence: Track every possible movement after a silence activation, keeping in mind they can move 0-4 times and cannot overlap their own path.
- Kaos mine: Same as mine but damage functions differently, revealing row or column until the mine hits islands. Kaos mines also cause chain reactions with other mines, revealing where they laid their mines if any are hit/subsequent damage.
- Asgard Torpedo: Similar to torpedo, only launched in straight line with range of six. Two damage on direct/indirect. Track both friendly and enemy uses.
- Kraken Missile: Only does damage on direct hit with infinite range. Will reveal if they are or are not on one specific space.
- Ulysses Repair: Take a system offline to repair a damage.
- Minos/Trident don’t really have relevant codeable executables.

## First Mate Tracking

- Damage: Track total damage to the enemy sub
- Systems: Track systems as they are announced to be online and take them off as they are used. If you’re really good use this info to determine how many movements a team took through silence.

## Engineer Tracking

Tally movements of each direction and have enemy sub engine to determine minimum number of active breakdowns.