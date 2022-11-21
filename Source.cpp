#include "windows.h"   //zeromemory - fills a block of memory with zeros
#include "Xinput.h"
#include <iostream>
#include <string>


#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

/*The MIT License (MIT)
Copyright © 2022 Alexander Joseph Kostyak

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/


int main() {

	//DEAD ZONE INCLUDES AXIS OUSIDE ORIGIN /// FIX
	float deadzoneX = 0.08f;
	float deadzoneY = 0.06f;

	//find controller port if >1 connected
	int controllerId = -1;
	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

	if (XInputGetState(i, &state) == ERROR_SUCCESS)
		controllerId = i;
	}

	XINPUT_STATE state;
	while (true) {
		
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		XInputGetState(controllerId, &state);    //0 works for manual port number by headphone jack

		std::cout << (float)state.Gamepad.bLeftTrigger / 255 << "\n";
		std::cout << (float)state.Gamepad.bRightTrigger / 255 << "\n";

		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y ) != 0) << "\n";

		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN ) != 0) << "\n";

		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER ) != 0) << "\n";

		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB ) != 0) << "\n";

		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK ) != 0) << "\n";
		std::cout << ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START ) != 0) << "\n";

			

		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);
		float leftStickX = ((abs(normLX) < deadzoneX) && (abs(normLY) < deadzoneY) ? 0 : normLX);
		float leftStickY = ((abs(normLY) < deadzoneY) && (abs(normLX) < deadzoneX) ? 0 : normLY);
		std::cout << "DEAD? " << leftStickX << "  REAL " << normLX << "\n";
		std::cout << "DEAD? " << leftStickY << "  REAL " << normLY << "\n";


		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);
		float rightStickX = ((abs(normRX) < deadzoneX) && (abs(normRY) < deadzoneY) ? 0 : normRX);
		float rightStickY = ((abs(normRY) < deadzoneY) && (abs(normRX) < deadzoneX) ? 0 : normRY);
		std::cout << "DEAD? " << rightStickX << "  REAL " << normRX << "\n";
		std::cout << "DEAD? " << rightStickY << "  REAL " << normRY << "\n";


		//try catch
		Sleep(100);
		system("cls");
	}

	return 0;
}
