# Shraybn

A cross platform game engine for creating narrative and story focused games.

## About

Shraybn uses **Lua** for scripting game code, as well as **Shrift**, a custom scripting language for interactive dialogue.

### Shrift

```
$is_tired false

@ Start

    Charles: Hey there!
    Charles: What are you doing?

    - Errands.
        I neede a few things.
        = $is_tired true
            They get pretty exhausting!
        ;
        ~ Errands

    - Not much.
        I'm just taking a walk!
        ~ Not Much

@ Errands

    Charles: Oh, me too!
    Charles: I'm picking up some flowers for my mother.

@ Not Much

    Charles: Nice!
    Charles: Great weather for it.
```
