# Captain Sonar - Radio Operator

A small program to automate the Radio Operator role for Captain Sonar.  Currently incomplete.

## Table of Contents

- [Captain Sonar - Radio Operator](#captain-sonar---radio-operator)
  - [Table of Contents](#table-of-contents)
  - [Dependencies](#dependencies)
  - [Usage](#usage)
  - [Data-Update Method Structure](#data-update-method-structure)
  - [Gameplay Requirements](#gameplay-requirements)
  - [TODO](#todo)

## Dependencies

SDL2 for graphical interface

## Usage

Incomplete / Undetermined

## Data-Update Method Structure

Data-updating methods of the Map class must implement an accurate evaluation of the results of the corresponding game action on the possible locations of the opponent. Additionally, they must be completely reversible by the `undo()` method and must not cause the starting conditions established by the `clear()` method to differ from the starting conditions caused by the `Map()` constructor; they must also perform both functional error checking to warn the user if the input action is not viable.

## [Gameplay Requirements](gameplay_requirements.md)

## [TODO](TODO.md)