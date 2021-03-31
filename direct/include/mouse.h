// Device mouse support
// Documents: https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondown
#pragma once

namespace direct {
	class MouseInput final
	{
	private:
		MouseInput();
		~MouseInput();
	public:
		static MouseInput& single();
		void onLeftKeyDown(float, float);
		void onRightKeyDown(float, float);
		void onLeftKeyUp(float, float);
		void onRightKeyUp(float, float);
		void onMove(float, float);
	};

}