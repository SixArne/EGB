#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "CPU.h"

int8_t FetchOpcode(int8_t op) 
{
    switch (op)
    {
		case 0:
			break;
		case 0x76:
            std::cout << "Halt operation code" << std::endl;
			break;
		case 0xC6:
            std::cout << "Add operation code" << std::endl;
			break;
        case 0xC2:
            std::cout << "Jump not zero" << std::endl;
            break;
        case 0xD2:
            std::cout << "Jump not carry" << std::endl;
            break;
		default:
			//std::cout << "Unable to detect opcode" << std::endl;
            break;
    }

    return 0;
}

std::vector<int8_t> GetRomBinairy() {
    std::ifstream file{ 
        "./assets/roms/SuperMarioLand.gb", 
        std::ios::binary 
    };

    std::vector<int8_t> rom{};

    /*if (file.is_open())
    {
        file.seekg(0, std::ios::end);
        std::streampos size = file.tellg();
        uint64_t currentPointer{ 0 };
        rom.reserve(size);

        while (currentPointer < size) 
        {
            file.seekg(currentPointer++, std::ios::beg);
            int8_t value{};

            file.read((char*) &value, sizeof(int8_t));
            rom.push_back(value);
        }
    }*/

    rom.assign(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );

    return rom;
}

int main()
{
    std::vector<int8_t> romData = GetRomBinairy();

    for (const int8_t& byte: romData)
    {
        FetchOpcode(byte);
    }

    CPU* cpu = new CPU{};
    
    std::cout << "Hello Emulator!\n";
}
