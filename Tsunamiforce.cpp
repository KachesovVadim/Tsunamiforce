#include "Header.h"

#define RESTART_MINING_MECHANICS    tp_to_home();                       \
                                    std::this_thread::sleep_for(2s);    \
                                    RestartFlyMode();                   \
                                    std::this_thread::sleep_for(1s);    \
                                    RandomRotate();                     \
                                    std::this_thread::sleep_for(3s);

void SetMineParams()
{
    Mine.type = INPUT_MOUSE;
    Mine.mi.mouseData = 0;
    Mine.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
}

void SetMoveParams()
{
    WORD vkey = 0x57; // key W
    Move.type = INPUT_KEYBOARD;

    Move.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
    Move.ki.time = 0;
    Move.ki.dwExtraInfo = 0;
    Move.ki.wVk = vkey;
    Move.ki.dwFlags = 0; // there is nwo KEYEVENTF_KEYDOWN
}//

void SetupTrashInputs()
{
    WORD vkey1 = 0x54; // key T
    input0.type = INPUT_KEYBOARD;

    input0.ki.wScan = MapVirtualKey(vkey1, MAPVK_VK_TO_VSC);
    input0.ki.time = 0;
    input0.ki.dwExtraInfo = 0;
    input0.ki.wVk = vkey1;
    input0.ki.dwFlags = 0;// | KEYEVENTF_KEYUP;


    std::wstring msg = L"/home t";
    for (auto ch : msg)
    {
        input1.type = INPUT_KEYBOARD;
        input1.ki.dwFlags = KEYEVENTF_UNICODE;
        input1.ki.wScan = ch;
        vec.push_back(input1);

        input1.ki.dwFlags |= KEYEVENTF_KEYUP;
        vec.push_back(input1);
    }


    WORD vkey2 = VK_RETURN; // key ENTER
    input2.type = INPUT_KEYBOARD;

    input2.ki.wScan = MapVirtualKey(vkey2, MAPVK_VK_TO_VSC);
    input2.ki.time = 0;
    input2.ki.dwExtraInfo = 0;
    input2.ki.wVk = vkey2;
    input2.ki.dwFlags = 0; // there is nwo KEYEVENTF_KEYDOWN
    vec.push_back(input2);
}

void OpenChat()
{
    if (GetAsyncKeyState(0x54) & 0x8000) // If T pressed
    {
        input0.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input0, sizeof(INPUT)); // T key
    }

    input0.ki.dwFlags = 0;
    SendInput(1, &input0, sizeof(INPUT)); // T key
}

void RestartFlyMode()
{
    input0.ki.wScan = MapVirtualKey(VK_SHIFT, MAPVK_VK_TO_VSC);
    input0.ki.wVk = VK_SHIFT;

    input0.ki.dwFlags = 0;// | KEYEVENTF_KEYUP;
    SendInput(1, &input0, sizeof(INPUT)); // Shift
    Sleep(100);

    input0.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input0, sizeof(INPUT)); // Shift
    Sleep(100);


    input0.ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC);
    input0.ki.wVk = VK_SPACE;

    for (int i = 0; i < 2; i++)
    {
        input0.ki.dwFlags = 0;// | KEYEVENTF_KEYUP;
        SendInput(1, &input0, sizeof(INPUT)); // Space
        Sleep(100);
            
        input0.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input0, sizeof(INPUT)); // Space
        Sleep(100);
    }

    input0.ki.wScan = MapVirtualKey(0x54, MAPVK_VK_TO_VSC);
    input0.ki.wVk = 0x54;
}

void tp_to_home()
{
    OpenChat();
    Sleep(500);

    SendInput(vec.size(), vec.data(), sizeof(INPUT)); // /home + ENTER
}//

void RandomRotate()
{
    for (int i = 0; i < 30; i++)
    {
        rng_type::result_type random_number = udist(rng);
        POINT p;
        GetCursorPos(&p);

        Sleep(100);
        SetCursorPos(random_number, p.y);
    }
}//

void FlushKeys()
{
    Mine.mi.dwFlags = MOUSEEVENTF_LEFTUP; // Flush mining
    SendInput(1, &Mine, sizeof(INPUT));
    Mine.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    Move.ki.dwFlags = KEYEVENTF_KEYUP; 
    SendInput(1, &Move, sizeof(INPUT));
    Move.ki.dwFlags = 0; // there is nwo KEYEVENTF_KEYDOWN
}

void MoveF()
{
    SendInput(1, &Move, sizeof(INPUT));
}

void MineF()
{
    SendInput(1, &Mine, sizeof(INPUT));
}

void Mining()
{
    while (true)
    {
        if (PauseMine == false)
        {
            MoveF(); // Start moving
            MineF(); // Start mining
        }
        std::this_thread::sleep_for(100ms);
    }
}

void RestartMining()
{
    while (true)
    {
        std::this_thread::sleep_for(restartPeriod);  // Delay before restart mining
        if (isCharging == true)
        {
            std::this_thread::sleep_for(10s);
        }
        else
        {
            FlushKeys();
            PauseMine = true;
            RESTART_MINING_MECHANICS
            PauseMine = false;
        }  
    } 
}

void RUNRAYMINER()
{
    system("py modules/RayMiner.py");
}

void RECHARGE()
{
    while (true)
    {
        Sleep(rechargePeriod); // Delay before recharging
        if (PauseMine == true)
        {
            std::this_thread::sleep_for(10s);
        }
        isCharging = true;
        PauseMine = true;
        FlushKeys();
        system("py modules/ChargeModule.py");
        Sleep(15000); // Sleep(15000);
        system("py modules/ChargeModule.py");
        Sleep(30000); // Sleep(100000);
        
        RESTART_MINING_MECHANICS
        PauseMine = false;
        isCharging = false;
    }
}

void StartInfo()
{
    cout << "    ______                                 _ ____                        " << endl;
    cout << "   /_  __/______  _______ ____ _____ ____ (_) __/____ _______________    " << endl;
    cout << "    / / / ___/ / / / __  \/ __ `/ __ `__  \/ / /_/ __  \/ ___/ ___/ _  / " << endl;
    cout << "   / / (__  ) /_/ / / / / /_/ / / / / / / / __/ /_/ / /  / /__/  __/     " << endl;
    cout << "  /_/ /____/\_____/_/ /_/\__,__/_/ /_/ /_/_/_/ /_____/_/  /____/\____/ " << endl;

    ReadAction();
/*
"  ______                                 _ ____"
" /_  __/______  ______  ____ _____ ___  (_) __/___  _____________"
"  / / / ___/ / / / __ \/ __ `/ __ `__ \/ / /_/ __ \/ ___/ ___/ _ \"
" / / (__  ) /_/ / / / / /_/ / / / / / / / __/ /_/ / /  / /__/  __/"
"/_/ /____/\__,_/_/ /_/\__,_/_/ /_/ /_/_/_/  \____/_/   \___/\___/"
*/
}

void ReadAction()
{
    cout << "\nChoose action: " << endl;
    cout << "info - information about cheat-client." << endl;
    cout << "start - cheat mode selection." << endl;

    string action;
    cin >> action;
    if (action == "info")
    {
        cout << "\n  ////////////////////////////////////////////////////////////////////" << endl;
        cout << "  ////////////////////////////////////////////////////////////////////" << endl;
        cout << "  ////                                                                " << endl;
        cout << "  //// Tsunamiforce - semi-modular cheat-client based on the          " << endl;
        cout << "  //// C++ language. Author - OMEGA, tg - @Jackson_Lighthouse         " << endl;
        cout << "  ////                                                                " << endl;
        cout << "  ////////////////////////////////////////////////////////////////////" << endl;
        cout << "  ////////////////////////////////////////////////////////////////////" << endl;
        ReadAction();
    }
    else if (action == "start") { ReadCheatMode(); }
    else { ReadAction(); }
}

void ReadCheatMode()
{
    string action;

    cout << "\nChoose cheat mode: " << endl;
    cout << "starminer - star algorithm. By default." << endl;
    cout << "rayminer - ray algorithm. By module." << endl;

    cin >> action;

    if (action == "starminer")
    {
        Sleep(5000);

        SetMineParams();
        SetMoveParams();
        SetupTrashInputs();

        std::thread th_reMining(RestartMining);
        std::thread th_mining(Mining);
        std::thread th_RECHARGING(RECHARGE);

        th_reMining.join();
        th_mining.join();
        th_RECHARGING.join();
    }

    else if (action == "rayminer")
    {
        Sleep(5000);

        std::thread th_RAYMINER(RUNRAYMINER);
        th_RAYMINER.join();
    } 

    else { ReadCheatMode(); }
}

int main()
{
    rng_type::result_type const seedval = time(0); // get this from somewhere
    rng.seed(seedval);    

    StartInfo();
    ReadCheatMode();
}