#include "pch.h"
#include "CPU.h"
#include <bitset>
#include <iostream>

CPU::CPU()
	:pc{ static_cast<int8_t>(0x0100) },
	a{ 0 },
	f{ 0 },
	b{ 0 },
	c{ 0 },
	d{ 0 },
	e{ 0 },
	hl{ 0 },
	sp{ 0 },
	op{ 0 }
{
}

void CPU::SetOP(int8_t opcode)
{
	this->op = opcode;
}

void CPU::EnableFlag(Flag flag)
{
	//   0 1 0 1
	// | 0 0 0 1
	//  --------
	//   0 1 0 1
	f |= static_cast<int8_t>(flag);
}

void CPU::EnableFlags(int8_t flags, int8_t bit)
{
	// If we want to set 101 at bit 2 - 5 we do the following:
	// EnableFlags(0b101, 2) It will pad 0b101 to be 0b10100
	// and then or gate it to set the mask.
	f |= (flags << bit);
}

void CPU::DisableFlag(Flag flag)
{
	// The NOT gate will negate the original bit, then we can use
	// the AND gate to take the difference.
	// ------------------------------------------------------------
	//     1 0 1 1 => original
	// -----------
	// 
	// ~   0 0 0 1 => bitmask
	// -----------
	//     1 1 1 0 => negated bits
	// 
	// 
	//     1 0 1 1 => original
	// &   1 1 1 0 => negated bits
	// -----------
	//     1 0 1 0 => result
	f &= (~static_cast<int8_t>(flag));
}

void CPU::DisableFlags(int8_t flags, int8_t bit)
{
	// The NOT gate will negate the original bit, then we can use
	// the AND gate to take the difference.
	// ------------------------------------------------------------
	//     1 0 1 1 => original
	// -----------
	// 
	// ~   0 0 0 1 => bitmask
	// -----------
	//     1 1 1 0 => negated bits
	// 
	// 
	//     1 0 1 1 => original
	// &   1 1 1 0 => negated bits
	// -----------
	//     1 0 1 0 => result
	f &= (~flags << bit);
}

void CPU::ToggleFlag(Flag flag)
{
	// The XOR gate will flip a bit depending on the mask
	// --------------------------------------------------
	//   0 1 0 1
	// ^ 0 0 0 1
	//  --------
	//   0 1 0 0
	f ^= static_cast<int8_t>(flag);
}

void CPU::ToggleFlags(int8_t flags, int8_t bit)
{
	// The XOR gate will flip a bit depending on the mask
	// We pad the flags so that they line up correctly. 
	// NOTE: The 1's are the ones you WANT to toggle.
	// --------------------------------------------------
	//   0 1 0 1
	// ^ 0 0 0 1
	//  --------
	//   0 1 0 0
	f ^= flags << bit;
}

bool CPU::FlagIsSet(Flag flag)
{
	// The OR gate will set a single bit, but won't flip it
	// ----------------------------------------------------
	//   0 1 0 1
	// ^ 0 0 0 1
	//  --------
	//   0 1 0 0
	return f & static_cast<int8_t>(flag);
}

bool CPU::FlagIsSet(int8_t bit)
{
	// The << will pad the given bit untill it's at the right position
	// and then check if it's set with an AND gate.
	// ----------------------------------------------------
	//   0 0 0 1 0 0 0 0
	//                 1 << 4
	//  
	//	 0 0 0 1 0 0 0 0
	// & 0 0 0 1 0 0 0 0
	//   ---------------
	//   0 0 0 1 0 0 0 0
	return f & (1 << bit);
}
