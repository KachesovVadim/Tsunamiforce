#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono_literals;

INPUT Mine; // Mouse control
INPUT Move; // Character moving

INPUT input0; // Trash input
INPUT input1; // Trash input
INPUT input2; // Trash input

typedef std::mt19937 rng_type;
rng_type rng;
std::uniform_int_distribution<rng_type::result_type> udist(100, 1500);

vector<INPUT> vec;

bool PauseMine = false;
bool isCharging = false;



//////////////////////////////////////////////////////////////////////////////////

auto restartPeriod = 60s; // Restart mining period in std::chrono
int rechargePeriod = 200000; // Recharging period in ms

//////////////////////////////////////////////////////////////////////////////////




// Functions declaration	
void SetMineParams();
void SetMoveParams();
void MoveF();
void MineF();
void Mining();
void RestartMining();
void SetupTrashInputs();
void FlushKeys();
void OpenChat();
void RestartFlyMode();
void tp_to_home();
void RandomRotate();
void StartInfo();
void ReadAction();
void ReadCheatMode();
