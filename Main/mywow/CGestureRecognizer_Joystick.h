#pragma once

#include "CGestureRecognizerBase.h"

class CGestureReader;

//recognizer
class CGestureRecognizer_Joystick : public CGestureRecognizerBase
{
public:
	explicit CGestureRecognizer_Joystick(CGestureReader* gestureReader);

public:
	virtual void setHelperFunction_Joystick(fn_isValidJoystickPosition callback) 
	{
		FnIsValidPosition = callback;
	}

	virtual void onTouchBegin(const std::vector<SGesTouchInfo>& touchInfos);
	virtual void onTouchMove(const std::vector<SGesTouchInfo>& touchInfos);
	virtual void onTouchEnd(const std::vector<SGesTouchInfo>& touchInfos);
	virtual void onTouchCancel(const std::vector<SGesTouchInfo>& touchInfos);

	virtual void onEnterState(E_RECOGNIZER_STATE state);

private:
	fn_isValidJoystickPosition		FnIsValidPosition;
};