//
//  Object.cpp
//  Project 3
//
//  Created by Brian Chang on 5/21/20.
//  Copyright © 2020 Brian Chang. All rights reserved.
//

#include "Object.h"
#include "globals.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//      WEAPON CLASS FUNCTIONS
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//Regular Constructors

Weapon::Weapon(string name, string action, int dexb, int dmg)
:Object(name, action), dexBonus(dexb), dmgAmt(dmg) { }

Mace::Mace()
:Weapon("mace", "swings", 0, 2) {}

ShortSword::ShortSword()
:Weapon("short sword", "slashes", 0, 2) {}

LongSword::LongSword()
:Weapon("long sword", "swings", 2, 4) {}

MagicAxe::MagicAxe()
:Weapon("magic axe", "chops", 5, 5) {}

MagicFangs::MagicFangs()
:Weapon("magic fangs", "strikes", 3, 2) {}

//Drop Constructors (Because they include positions)

Weapon::Weapon(int row, int col, string name, string action, int dexb, int dmg)
:Object(row, col, name, action), dexBonus(dexb), dmgAmt(dmg) { }

Mace::Mace(int row, int col)
:Weapon(row, col, "mace", "swings", 0, 2) {}

ShortSword::ShortSword(int row, int col)
:Weapon(row, col, "short sword", "slashes", 0, 2) {}

LongSword::LongSword(int row, int col)
:Weapon(row, col, "long sword", "swings", 2, 4) {}

MagicAxe::MagicAxe(int row, int col)
:Weapon(row, col, "magic axe", "chops", 5, 5) {}

MagicFangs::MagicFangs(int row, int col)
:Weapon(row, col, "magic fangs", "strikes", 3, 2) {}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//      SCROLL CLASS FUNCTIONS
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//Regular Constructors

Scroll::Scroll(string name, string action)
:Object(name, action) {}

HPScroll::HPScroll()
:Scroll("scroll of enhance health", "You feel your heart beating stronger.")
{
    setType(HP_SCROLL);
}

ArmorScroll::ArmorScroll()
:Scroll("scroll of enhance armor", "Your armor glows blue.")
{
    setType(ARMOR_SCROLL);
}

StrengthScroll::StrengthScroll()
:Scroll("scroll of strength" , "Your muscles bulge.")
{
    setType(STRENGTH_SCROLL);
}

DexScroll::DexScroll()
:Scroll("scroll of enhance dexterity", "You feel like less of a klutz.")
{
    setType(DEX_SCROLL);
}

TPScroll::TPScroll()
:Scroll("scroll of teleportation", "You feel your body wrenched in space and time.")
{
    setType(TP_SCROLL);
}


//Drop Constructors (Because they include positions)

Scroll::Scroll(int row, int col, string name, string action)
:Object(row, col, name, action) {}

HPScroll::HPScroll(int row, int col)
:Scroll(row, col, "scroll of enhance health", "You feel your heart beating stronger.") {}

ArmorScroll::ArmorScroll(int row, int col)
:Scroll(row, col, "scroll of enhance armor", "Your armor glows blue.") {}

StrengthScroll::StrengthScroll(int row, int col)
:Scroll(row, col, "scroll of strength" , "Your muscles bulge.") {}

DexScroll::DexScroll(int row, int col)
:Scroll(row, col, "scroll of enhance dexterity", "You feel like less of a klutz.") {}

TPScroll::TPScroll(int row, int col)
:Scroll(row, col, "scroll of teleportation", "You feel your body wrenched in space and time.") {}
