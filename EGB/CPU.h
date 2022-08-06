#include <cstdint>

#pragma once
class CPU
{
public:
	enum class Flag 
	{
		Zero      =	0b10000000,
		Subtract  =	0b01000000,
		HalfCarry = 0b00100000,
		Carry	  =	0b00010000,
	};

	CPU();

	void SetOP(int8_t opcode);
	

private:
	// registers
	int8_t a; // Used for arithmatic operations
	int8_t f; // Flag register, 8 distinct bits
	int8_t b;
	int8_t c;
	int8_t d;
	int8_t e;
	uint16_t hl; // 2 8 bit registers but functions as a 16bit register

	int8_t sp; // stack pointer
	int8_t pc; // program counter

	int8_t op; // operation code

	
	void EnableFlags(int8_t flags, int8_t bit);
	void EnableFlag(Flag flag);
	void DisableFlag(Flag flag);
	void DisableFlags(int8_t flags, int8_t bit);
	void ToggleFlag(Flag flag);
	void ToggleFlags(int8_t flags, int8_t bit);
	bool FlagIsSet(Flag flag);
	bool FlagIsSet(int8_t bit);
};

