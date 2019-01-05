#include <windows.h>
#include "Game.h"
#include <d3d9.h>

CGame::CGame(int _nnCmdShow)
{
	nCmdShow = _nnCmdShow;
}

int CGame::InitWindow(int nCmdShow) 
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = Game_hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = Game_Name;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	int windowStyle;
	if(Game_IsFullScreen) 
	{
		windowStyle = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; 
	} 
	else 
	{
		windowStyle = WS_OVERLAPPEDWINDOW; 
	}

	Game_hWnd = 
		CreateWindow(
		Game_Name,
		Game_Name,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
		Game_ScreenWidth,
		Game_ScreenHeight,
		NULL,
		NULL,
		Game_hInstance,
		NULL);

	if (!Game_hWnd) { 
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(Game_hWnd, nCmdShow);
	UpdateWindow(Game_hWnd);
}


int CGame::InitDirectX() 
{
	Game_DirectX = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp; 

	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	if(Game_IsFullScreen) {
		d3dpp.Windowed   = FALSE;
	} else {
		d3dpp.Windowed   = TRUE;
	}
	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = Game_ScreenHeight;
	d3dpp.BackBufferWidth = Game_ScreenWidth;

	Game_DirectX->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		Game_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&Game_Device);

	if (Game_Device==NULL) 
	{
		return 0;
	}

	
	Game_Device->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&Game_BackBuffer);

	
	D3DXCreateSprite(Game_Device, &Game_SpriteHandler);

	return 1;
}

void CGame::InitKeyboard()
{
    HRESULT 
		hr = DirectInput8Create
			( 
				GetModuleHandle(NULL), 
				DIRECTINPUT_VERSION, 
				IID_IDirectInput8, (VOID**)&Game_DirectInput, NULL 
			);

	
	if (FAILED(hr)==true)
		return;
	
	hr = Game_DirectInput->CreateDevice(GUID_SysKeyboard, &Game_KeyBoard, NULL); 
	
	
	if (FAILED(hr)==true) 
		return;

	hr = Game_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)==true) 
		return;

	hr = Game_KeyBoard->SetCooperativeLevel(Game_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	if (FAILED(hr)==true) 
		return;

    DIPROPDWORD dipdw;

    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = GL_KEY_BUFFER_SIZE;

    hr = Game_KeyBoard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if (FAILED(hr)==true) 
		return;

	hr = Game_KeyBoard->Acquire(); 
	if (FAILED(hr)==true) 
		return;
}

void CGame::InitGame()
{
	InitWindow(nCmdShow);
	InitDirectX();
	InitKeyboard();
	LoadResources(Game_Device);
}

void CGame::ProcessKeyBoard()
{
		HRESULT hr = Game_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		if(hr != S_OK)
		{
			hr = Game_KeyBoard->Acquire();
			Game_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		}
		
		Game_KeyBoard->GetDeviceState( sizeof(_KeyStates), _KeyStates);

		if (IsKeyDown(DIK_ESCAPE)) 
		{
			PostMessage(Game_hWnd,WM_QUIT,0,0);
		}

		
		DWORD dwElements = GL_KEY_BUFFER_SIZE;
		hr = Game_KeyBoard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0 );

		
		for( DWORD i = 0; i < dwElements; i++ ) 
		{
			int KeyCode = _KeyEvents[i].dwOfs;
			int KeyState = _KeyEvents[i].dwData;
			if ( (KeyState & 0x80) > 0)
				OnKeyDown(KeyCode);
			else 
				OnKeyUp(KeyCode);
		}
}

void CGame::OnKeyUp(int KeyCode) { }
void CGame::OnKeyDown(int KeyCode) { }

void GameDraw(int deltaTime)
{
	
}

void CGame::GameRun()
{
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;
	
	DWORD tick_per_frame = 100 / Game_FrameRate;

	while (!done) 
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT) done=1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}

		DWORD now = GetTickCount();
		_DeltaTime = now - frame_start; 
		if (_DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			RenderFrame();
		}

		ProcessKeyBoard();

		ProcessInput(Game_Device, _DeltaTime);
	}
}

void CGame::RenderFrame()
{
	if (Game_Device->BeginScene()) 
	{
		RenderFrame(Game_Device, _DeltaTime);
		Game_Device->EndScene();
	}
	Game_Device->Present(NULL,NULL,NULL,NULL);
}

void CGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta) 
{
}

void CGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv) { }

void CGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta) 
{
	
}

int CGame::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

void CGame::GameEnd()
{
	if (Game_Device!=NULL) Game_Device->Release();
	if (Game_DirectX!=NULL) Game_DirectX->Release();
}

LRESULT CALLBACK CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	default: 
		return DefWindowProc(hWnd, message, wParam,lParam);
	}
	return 0;
}
