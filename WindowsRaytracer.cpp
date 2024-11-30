// Windows Raytracer.cpp : Defines the entry point for the application.

#ifndef UNICODE
#define UNICODE
#endif

#include <stdint.h>
#include <iostream>
#include <vector>
#include "framework.h"
#include "WindowsRaytracer.h"

#define MAX_LOADSTRING 100

// WindowsRaytracer.cpp's Global Static Variables:
static HINSTANCE hInst;                                // current instance
static WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
static WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

static BITMAPINFO frame_bitmap_info;                   // Dimensions & color format for DIB 
static HBITMAP frame_bitmap = 0;                       // DIB for bitblit source    
static HDC frame_device_context = 0;                   // Context for frame_bitmap

static BOOL quit = false;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
HWND                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Configure bitmap

    // Set const dimensions (for now)
    frame_bitmap_info.bmiHeader.biWidth = 720;
    frame_bitmap_info.bmiHeader.biHeight = 720;
    
    // The rest stays
	frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
	frame_bitmap_info.bmiHeader.biPlanes = 1;
	frame_bitmap_info.bmiHeader.biBitCount = 32;
	frame_bitmap_info.bmiHeader.biCompression = BI_RGB; 
	frame_device_context = CreateCompatibleDC(0);


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSRAYTRACER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
       
    HWND hWnd;
    // Perform application initialization:
    if (!(hWnd = InitInstance (hInstance, nCmdShow)))
    {
        return FALSE;
    }
    
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSRAYTRACER));
  

    // Setup scene:

    // Shapes in the scene
    std::vector<Shape *> shapes;
    shapes.push_back(new Sphere((Vec3(0.0, -1.0, 3.0)), 1.0, Color(255, 0, 0), 500.0, 0.2f, INFINITY));
    shapes.push_back(new Sphere((Vec3(2.0, 0.0, 4.0)), 1.0, Color(0, 0, 255), 500.0, 0.0f, INFINITY));
    shapes.push_back(new Sphere((Vec3(-2.0, 0.0, 4.0)), 1.0, Color(0, 255, 0), 10.0, 0.6f, INFINITY));
    shapes.push_back(new Sphere((Vec3(0.0, -5001.0, 0.0)), 5000.0, Color(255, 255, 0), 1000.0, 0.5f, INFINITY));


	//shapes.push_back(new Triangle(Vec3(-4.0, -0.5, 5.0), Vec3(0.0, 5.0, 5.0), Vec3(4.0, -0.5, 5.0), Color(0, 255, 255), 500.0, 0.9f));
//	shapes.push_back(new Triangle(Vec3(-2.5, -1.0, 1.0), Vec3(0.0, 4.0, 4.0), Vec3(2.5, -1.0, 1.0), Color(0, 255, 255), 500.0, 0.1f));
//    koch_snowflake3d(Vec3(-2.5, -1.0, 1.0), Vec3(0.0, 4.0, 4.0), Vec3(2.5, -1.0, 1.0), 0, 2, shapes);
 
  //  shapes.push_back(new Triangle(Vec3(-0.5, -0.433, 0.0), Vec3(0.0, 0.866, 0.0), Vec3(0.5, -0.433, 0), Color(0, 255, 255), 100.0, 0.0f));
  //  shapes.push_back(new Triangle(Vec3(-0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.0, 0.866, 0.0), Color(0, 255, 255), 100.0, 0.0f));
  //  shapes.push_back(new Triangle(Vec3(-0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.5, -0.433, 0.0), Color(0, 255, 255), 100.0, 0.0f));
  //  shapes.push_back(new Triangle(Vec3(0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.0, 0.866, 0.0), Color(0, 255, 255), 100.0, 0.0f));
   // koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, 0.816), 1, 2, shapes);
   // koch_snowflake3d(Vec3(0.0, 0.866, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(-0.5, -0.433, 0.0), 1, 2, shapes);
   // koch_snowflake3d(Vec3(-0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.5, -0.433, 0.0), 1, 2, shapes);
   // koch_snowflake3d(Vec3(0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.0, 0.866, 0.0), 1, 2, shapes);


   //// 3D Koch Snowflake scene
   shapes.push_back(new Sphere((Vec3(0.0, -5005.0, 0.0)), 5000.0, Color(255, 0, 0), 1000.0, 0.5f));
   shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
   shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, -0.816), Color(255, 255, 255), 300.0, 0.2f));  
   shapes.push_back(new Triangle(Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(0.5, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
   shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
     
   koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), 1, 2, shapes);
   koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, -0.816), 1, 2, shapes);
   koch_snowflake3d(Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(0.5, 0.866, 0.0), 1, 2, shapes);
   koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), 1, 2, shapes);
   // 
   //std::vector<Light*> lights;
   //lights.push_back(new AmbientLight(0.2f));
   //lights.push_back(new PointLight(0.2f, Vec3(2.0, 1.0, 0.0)));
   //lights.push_back(new PointLight(0.6f, Vec3(-1.0, 0.25, -3.0)));
     
   // Single triangle
   // shapes.push_bacVec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), Ck(new Triangle(Vec3(-1.0, 1.73205, 0.0), Vec3(-1.0, -1.73205, 0.0), Vec3(2.0, 0.0, 0.0), Color(0, 255, 255), 300.0, 0.2f));  
   // koch_snowflake3d( Vec3(-1.0, -1.73205, 0.0), Vec3(-1.0, 1.73205, 0.0), Vec3(2.0, 0.0, 0.0), 1, 3, shapes);
	
   //shapes.push_back(new Triangle(Vec3(-0.28867, -0.25, 1.0), Vec3(0.0, 0.25, 1.0), Vec3(0.28867, -0.25, 1.0), Color(0, 255, 255), 500.0, 0.0f));
    // Lights in the scene
    std::vector<Light*> lights;
    lights.push_back(new AmbientLight(0.2f));
    lights.push_back(new PointLight(0.6f, Vec3(2.0, 1.0, 0.0)));
    lights.push_back(new DirectionalLight(0.4f, Vec3(1.0, 4.0, 4.0)));
    //lights.push_back(new PointLight(0.6f, Vec3(-1.0, 0.25, -3.0)));
       
    Scene scene(shapes, lights);

    // Setup camera:
    Camera camera(Vec3(0.0, 0.0, -4.0), 720, 720, 1.0, 1.0, 1.0);

    // Create DIB section, give camera's pixels as pixel buffer to BitBlit
	if (frame_bitmap) DeleteObject(frame_bitmap);
	frame_bitmap = CreateDIBSection(NULL,
	   &frame_bitmap_info,
	   DIB_RGB_COLORS,
	   (void**)&(camera.get_pixels()),
	   0, 0);

    if (frame_bitmap != 0) SelectObject(frame_device_context, frame_bitmap);
    
    camera.render(scene);
    MSG msg = {};

    while (!quit)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            DispatchMessage(&msg);
            if (msg.message == WM_SIZE)
            {

                frame_bitmap_info.bmiHeader.biWidth = 720;
                frame_bitmap_info.bmiHeader.biHeight = 720;

                if (frame_bitmap) DeleteObject(frame_bitmap);
				frame_bitmap = CreateDIBSection(NULL,
					&frame_bitmap_info,
					DIB_RGB_COLORS,
				    (void**)&(camera.get_pixels()),
					0, 0);
            
				if(frame_bitmap != 0) SelectObject(frame_device_context, frame_bitmap);
            }
        }
      
       // camera.render(scene);
         
        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
    }
    
    // Hard coded scene cleanup (for now)
    while (!shapes.empty())
    {
        delete shapes.back();
        shapes.pop_back();
    }
    
    while(!lights.empty())
    {
        delete lights.back();
        lights.pop_back();
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSRAYTRACER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSRAYTRACER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return hWnd;
   }

   //
   SetWindowPos(hWnd, HWND_TOP, 0, 0, 720, 720, SWP_NOOWNERZORDER);
   //
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return hWnd;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC device_context = BeginPaint(hWnd, &paint);
            BitBlt(device_context,      // Dest context
                paint.rcPaint.left,
                paint.rcPaint.top,
                paint.rcPaint.right - paint.rcPaint.left,
                paint.rcPaint.bottom - paint.rcPaint.top,
                frame_device_context,   // Source context
                paint.rcPaint.left,
                paint.rcPaint.top,
                SRCCOPY);
            EndPaint(hWnd, &paint);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        quit = true;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
