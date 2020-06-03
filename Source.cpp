#include <iostream>
#include <Windows.h>
#include <ctime>
#define WIDTH 1920
#define HEIGHT 1080

struct Color {
	
	int i_colorAssumption = 20;
	struct red {
		DWORD hex = 0xff0000;
		DWORD integer[3] = { 255,0,0 };

	};
	struct blue {
		DWORD hex = 0x0000ff;
		DWORD integer[3] = { 0,0,255 };

	};
	struct green {
		DWORD hex = 0x00ff00;
		DWORD integer[3] = { 0,255,0 };

	};
	struct yellow {
		DWORD hex = 0xffff00;
		DWORD integer[3] = { 255,255,0 };

	};
};
class Config {
public:
	int i_nullCheck(int& value) {
		if (value < 0) { return value = 0; }
	};

int i_ConfiguratableValues = 5;
char ch_ConfiguratableValues[5][32] = { {"triggerbot rapidity" },
										{"aim parse accuracy"},
										{ "crosshair pos X" },
										{ "crosshair pos Y" },
										{"Player team"} };

int i_crosshairPosX = (WIDTH/2);
int i_crosshairPosY = (HEIGHT / 2) - 10;
int i_rapidity = 20;
int i_aimParseOffset = 8;
int i_crosshairOffset = 10;
float f_sensivity = 2.0f;

std::string str_PlayerTeam = "ct";
	void OutputConfigOptions() {
		for (int j = 1; j<= i_ConfiguratableValues; j++ ){
			std::cout << '[' << j << ']';
			for (int x = 0;ch_ConfiguratableValues[j-1][x] != '\0'; x++) {
				std::cout << ch_ConfiguratableValues[j - 1][x];
			}
			std::cout << std::endl;
		}
		return;
	}
	void editConfigOptions(short opt) {
		int i_buf; 
		std::cout << "\npick option and enter a new value\n";
		if(opt!=5)
		std::cin >> i_buf;
		if (opt == 1) {
			i_rapidity = i_buf;
			i_nullCheck(i_rapidity);
		}
		if (opt == 2) {
			i_aimParseOffset = i_buf;
			i_nullCheck(i_aimParseOffset);
		}
		if (opt == 3) {
			i_crosshairPosX = i_buf;
			i_nullCheck(i_crosshairPosX);
		}
		if (opt == 4) {
			i_crosshairPosY = i_buf;
			i_nullCheck(i_crosshairPosY);
		}
		if (opt == 5) {
			if (str_PlayerTeam == "ct") {
				str_PlayerTeam = "t";
				std::cout << "your team: " << str_PlayerTeam << std::endl;
				return;
			}
			else if (str_PlayerTeam == "t") {
				str_PlayerTeam = "ct";
				std::cout << "your team: " << str_PlayerTeam << std::endl;
				return;
			}
			
		}
	}
};
char color_defineColor(int r, int g, int b) {
	Color::red red;
	Color::green green;
	Color::blue blue;
	Color::yellow yellow;
	Color c;
	char color;
			if (r <= (red.integer[0]) && r >= (red.integer[0] - c.i_colorAssumption)) {
				if (g >= (red.integer[1]) && g <= (red.integer[1] + c.i_colorAssumption)) {
					if (b >= (red.integer[2]) && b <= (red.integer[2] + c.i_colorAssumption)) {
						color = 'r';
						return color;
					}
				}
			}
			if (r >= (green.integer[0]) && r <= (green.integer[0] + c.i_colorAssumption)) {
				if (g <= (green.integer[1]) && g >= (green.integer[1] - c.i_colorAssumption)) {
					if (b >= (green.integer[2] ) && b <= (green.integer[2] + c.i_colorAssumption)) {
						color = 'g';
						return color;
					}
				}
			}
			if (r >= (blue.integer[0])&& r <= (blue.integer[0] + c.i_colorAssumption)){
				if (g >= (blue.integer[1]) && g <=(blue.integer[1] + c.i_colorAssumption)) {
					if (b <= (blue.integer[2]) && b >= (blue.integer[2] - c.i_colorAssumption)) {
						color = 'b';
						return color;
					}
				}
			}
			if (r <= (yellow.integer[0]) && r>= (yellow.integer[0] - c.i_colorAssumption)) {
				if (g <= (yellow.integer[1]) && g >= (yellow.integer[1] - c.i_colorAssumption)) {
					if (b <= (yellow.integer[2])) {
						color = 'y';
						return color;
					}
				}
			}
			return '0';
}
/*void draw_crosshair(int sizex, int sizey, HDC hdc) {
	Config::OptionValues c;
	int lineXpos = (HEIGHT / 2 - c.crosshairOffset) + sizex - (HEIGHT / 2 - c.crosshairOffset) - sizex;
	int lineYpos = (WIDTH / 2) + sizey -(WIDTH / 2) - sizey;

	for (int y = 0; y <= sizey;y++) {
		for (int x =0; x<= sizex; x++) {
			if (y == lineYpos / 2 || sizex == rect / 2) {
				SetPixel(hdc, sizex,(sizey-c.crosshairOffset), 0xffffff);
			}
		}
	}
}*/
class TriggerBot {
public:
	Color::red red;
	Color::green green;
	Color::blue blue;
	Color::yellow yellow;
	Config c;
	char ch_colorSymIfDefined;
	int r, g, b;
	void enable( DWORD width, DWORD height, HDC hdc, INPUT ip, INPUT iy, std::string strPlayerTeam) {
		int i_teamId;
		if (strPlayerTeam == "ct") i_teamId = 1;
		if (strPlayerTeam == "t") i_teamId = 2;
		unsigned long  u_rawColorVal;
		do {
			u_rawColorVal = GetPixel(
				hdc,
				(width / 2),
				(height / 2) - 10
			);
			r = (int)GetRValue(u_rawColorVal);
			g = (int)GetGValue(u_rawColorVal);
			b = (int)GetBValue(u_rawColorVal);
			ch_colorSymIfDefined = color_defineColor(r, g, b);
			if (i_teamId == 1 && ch_colorSymIfDefined == 'r' ||
				i_teamId == 1 && ch_colorSymIfDefined == 'y' ||
				i_teamId == 2 && ch_colorSymIfDefined == 'b' ||
				i_teamId == 2 && ch_colorSymIfDefined =='g') {
				SendInput(1, &ip, sizeof(INPUT));
				Sleep(c.i_rapidity);
				SendInput(1, &iy, sizeof(INPUT));
				continue;
			}

		} while (false);
	}
};
class AimBot {
public:
	unsigned long color;
	TriggerBot t;
	int i_deltaHeight;
	int i_deltaWidth;
	bool running = true;
	int i_buf;
	int r, g, b;
	char ch_colorSymIfDefined;

	void enable(DWORD width, DWORD height, HDC hdc, INPUT m, std::string strPlayerTeam) {
		INPUT mouseDown;
		INPUT mouseUp;
		tagINPUT mmove;
		Config c;
		mmove.type = INPUT_MOUSE;
		mmove.mi.dwExtraInfo = 0;
		mmove.mi.dwFlags = MOUSEEVENTF_MOVE;
		mmove.mi.dx = 0;
		mmove.mi.dy = 0;
		mmove.mi.time = 0;
		mmove.mi.mouseData = 0;
		mouseUp.type = INPUT_MOUSE;
		mouseUp.mi.dx = 0;
		mouseUp.mi.dy = 0;
		mouseUp.mi.mouseData = 0;
		mouseUp.mi.dwExtraInfo = 0;
		mouseUp.mi.time = 0;
		mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		mouseDown.type = INPUT_MOUSE;
		mouseDown.mi.dx = 0;
		mouseDown.mi.dy = 0;
		mouseDown.mi.mouseData = 0;
		mouseDown.mi.dwExtraInfo = 0;
		mouseDown.mi.time = 0;
		mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		int inttct;
		if (strPlayerTeam == "ct") inttct = 1;
		if (strPlayerTeam == "t") inttct = 2;
		while(running){
			
			for (int i = (height/2)-100; i <= (height/2)+100; i += 8) {
				for (int j =( width / 2 )- 100; j <=( width / 2 )+ 100; j += 8) {
					SetPixel(hdc, j + 1, i + 1, 0xffffff);
					
					color = GetPixel(hdc, j-1, i-1);
					r = (int)GetRValue(color);
					g = (int)GetGValue(color);
					b = (int)GetBValue(color);
					ch_colorSymIfDefined = color_defineColor(r,g,b);
					
					if (
						(inttct == 1 && ch_colorSymIfDefined == 'y') || (inttct == 2 &&ch_colorSymIfDefined == 'g')
						) {
						if (j <= (width / 2) + 8 || j >= (width / 2) - 8 && i <= ((height / 2) - 10) + 8 || i >= ((height / 2) - 10) -8) {
							t.enable(width, height, hdc, mouseDown, mouseUp, strPlayerTeam);
						}
						if (j > (width / 2)) {
							i_deltaWidth = (j - (width / 2));
							m.mi.dx = 0;
							m.mi.dx += ceil((i_deltaWidth / c.f_sensivity));
						}
						else if (j < (width / 2)) {
							i_deltaWidth = ((width / 2) -j);
							m.mi.dx = 0;
							m.mi.dx -= ceil((i_deltaWidth/ c.f_sensivity));

						}
						if (i > (height / 2)-10) {
							i_deltaHeight = (i - (height / 2) /*- 10*/);
							m.mi.dy = 0;
							m.mi.dy += ceil((i_deltaHeight / c.f_sensivity));

						}
						else if (i < (height / 2) - 10) {
							i_deltaHeight = ((height / 2) - i /*-10*/);
							m.mi.dy = 0;
							m.mi.dy -= ceil((i_deltaHeight / c.f_sensivity));

						}
						
						SendInput(1, &m, sizeof(tagINPUT));
						
					}
				}
			}
		}
	}
};

int main(int argc, char** argv) {
	TriggerBot t;
	AimBot aim;
	INPUT mouseDown;
	INPUT mouseUp;
	tagINPUT mouseMove;
	Config c;
	
	mouseMove.type = INPUT_MOUSE;
	mouseMove.mi.dwExtraInfo = 0;
	mouseMove.mi.dwFlags = MOUSEEVENTF_MOVE;
	mouseMove.mi.dx = 0;
	mouseMove.mi.dy = 0;
	mouseMove.mi.time = 0;
	mouseMove.mi.mouseData = 0;
	mouseUp.type = INPUT_MOUSE;
	mouseUp.mi.dx = 0;
	mouseUp.mi.dy = 0;
	mouseUp.mi.mouseData = 0;
	mouseUp.mi.dwExtraInfo = 0;
	mouseUp.mi.time = 0;
	mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dx = 0;
	mouseDown.mi.dy = 0;
	mouseDown.mi.mouseData = 0;
	mouseDown.mi.dwExtraInfo = 0;
	mouseDown.mi.time = 0;
	mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	HWND hwnd;
	HDC hdc;
	int r, g, b;
	DWORD color = 0;
	DWORD rgbArr[3];
	HANDLE hConWnd;
	bool flag_activateConfigWindow = false;
	bool flag_activateTriggerBot = false;
	bool flag_activateAimBot = false;
	bool flag_runProgram = true;
	int i_confOption;
	RECT rect_windowRect;
	hwnd = FindWindowExW(NULL, NULL, NULL, L"Counter-Strike");
	if (hwnd == NULL) return 1;
	hdc = GetDC(hwnd);
	LPCSTR buf;
	if (hdc == NULL) return 2;
	DWORD key;
	GetWindowRect(hwnd, &rect_windowRect);
	printf("window size: width %d,  height %d \n",rect_windowRect.right, rect_windowRect.bottom);
	std::cout << "Your team: " << c.str_PlayerTeam << std::endl;
	std::cout << "Your triggerbot fire rate: " << c.i_rapidity << '\n';
	std::cout << "F3 to start aimbot, F4 to start triggerbot[switchable]\nINSERT to enter config, DELETE to exit\n";


	while (flag_runProgram){
	SetPixel(hdc, (WIDTH/2) , ((HEIGHT / 2)-c.i_crosshairOffset)-1, 0xffffff);
	if (GetAsyncKeyState(VK_F4) & 0x8000) {
		flag_activateTriggerBot = !flag_activateTriggerBot;
	}
	if (GetAsyncKeyState(VK_F3) & 0x8000) {
		flag_activateAimBot = !flag_activateAimBot;
	}
	if (GetAsyncKeyState(VK_INSERT) & 0x8000) {
		c.OutputConfigOptions();
		std::cout << "chose a number of configuratable option\n";
		std::cin >> i_confOption;
		c.editConfigOptions(i_confOption);
	}
	if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
		exit(0);
	}
	if (flag_activateTriggerBot)t.enable(WIDTH, HEIGHT, hdc, mouseDown, mouseUp, c.str_PlayerTeam);
	if (flag_activateAimBot)aim.enable(WIDTH, HEIGHT, hdc, mouseMove, c.str_PlayerTeam);
	}
	return 0;
}