#include "pch.h"

#define private public
#include "../EGB/CPU.h"
#include "../EGB/CPU.cpp"
TEST(CPU, SET_BIT) {
	CPU* cpu = new CPU{};

	// Set all individual flags
	cpu->EnableFlag(CPU::Flag::Carry);
	EXPECT_EQ(static_cast<int8_t>(0b00010000), cpu->f);

	cpu->EnableFlag(CPU::Flag::Subtract);
	EXPECT_EQ(static_cast<int8_t>(0b01010000), cpu->f);

	cpu->EnableFlag(CPU::Flag::HalfCarry);
	EXPECT_EQ(static_cast<int8_t>(0b01110000), cpu->f);

	cpu->EnableFlag(CPU::Flag::Zero);
	EXPECT_EQ(static_cast<int8_t>(0b11110000), cpu->f);

	// Expect to not flip a flag that is true
	cpu->EnableFlag(CPU::Flag::Zero);
	EXPECT_EQ(static_cast<int8_t>(0b11110000), cpu->f);

	delete cpu;
}

TEST(CPU, SET_BITS) {
	CPU* cpu = new CPU{};

	// Set all individual flags
	cpu->EnableFlags(0b101, 4);
	EXPECT_EQ(static_cast<int8_t>(0b01010000), cpu->f);

	// Shouldn't flip bits
	cpu->EnableFlags(0b101, 4);
	EXPECT_EQ(static_cast<int8_t>(0b01010000), cpu->f);

	cpu->EnableFlags(0b11, 5);
	EXPECT_EQ(static_cast<int8_t>(0b01110000), cpu->f);

	delete cpu;
}

TEST(CPU, UNSET_BIT) {
	CPU* cpu = new CPU{};

	// Set all individual flags
	cpu->EnableFlag(CPU::Flag::Carry);
	EXPECT_EQ(static_cast<int8_t>(0b00010000), cpu->f);

	cpu->EnableFlag(CPU::Flag::Subtract);
	EXPECT_EQ(static_cast<int8_t>(0b01010000), cpu->f);

	cpu->EnableFlag(CPU::Flag::HalfCarry);
	EXPECT_EQ(static_cast<int8_t>(0b01110000), cpu->f);

	cpu->EnableFlag(CPU::Flag::Zero);
	EXPECT_EQ(static_cast<int8_t>(0b11110000), cpu->f);

	// Remove set flags
	cpu->DisableFlag(CPU::Flag::HalfCarry);
	EXPECT_EQ(static_cast<int8_t>(0b11010000), cpu->f);

	cpu->DisableFlag(CPU::Flag::Subtract);
	EXPECT_EQ(static_cast<int8_t>(0b10010000), cpu->f);

	cpu->DisableFlag(CPU::Flag::Carry);
	EXPECT_EQ(static_cast<int8_t>(0b10000000), cpu->f);

	cpu->DisableFlag(CPU::Flag::Zero);
	EXPECT_EQ(static_cast<int8_t>(0b00000000), cpu->f);

	// Not override a 0 flag
	cpu->DisableFlag(CPU::Flag::Zero);
	EXPECT_EQ(static_cast<int8_t>(0b00000000), cpu->f);

	delete cpu;
}

TEST(CPU, UNSET_BITS) {
	CPU* cpu = new CPU{};

	// Set all individual flags
	cpu->EnableFlags(0b101, 4);
	EXPECT_EQ(static_cast<int8_t>(0b01010000), cpu->f);

	cpu->DisableFlags(0b101, 4);
	EXPECT_EQ(static_cast<int8_t>(0b00000000), cpu->f);

	cpu->EnableFlags(0b111, 5);
	EXPECT_EQ(static_cast<int8_t>(0b11100000), cpu->f);

	cpu->DisableFlags(0b111, 5);
	EXPECT_EQ(static_cast<int8_t>(0b00000000), cpu->f);

	// Can't flip bits
	cpu->DisableFlags(0b111, 5);
	EXPECT_EQ(static_cast<int8_t>(0b00000000), cpu->f);

	delete cpu;
}

TEST(CPU, TOGGLE_BIT) {
	CPU* cpu = new CPU{};

	cpu->ToggleFlag(CPU::Flag::Carry);
	EXPECT_EQ(static_cast<int8_t>(0b00010000), cpu->f);

	cpu->ToggleFlag(CPU::Flag::Carry);
	EXPECT_EQ(static_cast<int8_t>(0b00000000), cpu->f);

	cpu->ToggleFlag(CPU::Flag::Zero);
	EXPECT_EQ(static_cast<int8_t>(0b10000000), cpu->f);

	cpu->ToggleFlag(CPU::Flag::Zero);
	EXPECT_EQ(static_cast<int8_t>(0b00000000), cpu->f);

	delete cpu;
}

TEST(CPU, TOGGLE_BITS) {
	CPU* cpu = new CPU{};

	cpu->ToggleFlags(0b1111, 4);
	EXPECT_EQ(static_cast<int8_t>(0b11110000), cpu->f);

	cpu->ToggleFlags(0b1010, 4);
	EXPECT_EQ(static_cast<int8_t>(0b01010000), cpu->f);

	delete cpu;
}

TEST(CPU, BIT_IS_SET) {
	CPU* cpu = new CPU{};

	cpu->EnableFlag(CPU::Flag::Carry);

	EXPECT_EQ(true, cpu->FlagIsSet(CPU::Flag::Carry));
	EXPECT_EQ(true, cpu->FlagIsSet(4));

	cpu->DisableFlag(CPU::Flag::Carry);
	cpu->EnableFlags(0b1100, 4);

	EXPECT_EQ(true, cpu->FlagIsSet(8));
}