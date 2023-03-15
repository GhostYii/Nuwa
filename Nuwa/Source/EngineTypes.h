#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Nuwa
{
	typedef unsigned int uint;
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef long long int64;
	typedef unsigned long long uint64;

	//typedef glm::vec4 Color;
	typedef glm::vec4 Vector4;
	typedef glm::vec3 Vector3;
	typedef glm::lowp_ivec3 Vector3Int;
	typedef glm::vec2 Vector2;
	typedef glm::lowp_ivec2 Vector2Int;
	typedef glm::mat3x3 Matrix3x3;
	typedef glm::mat4x4 Matrix4x4;

	typedef glm::quat Quaternion;	

	struct ShaderSource
	{
		std::string vertex;
		std::string fragment;
	};

	enum class ShaderType
	{
		None = -1,
		Vertex,
		Fragment
	};

	struct VertexElement
	{
		uint type;
		uint count;
		uchar normalized;

		static uint GetTypeSize(uint type)
		{
			switch (type)
			{
			case GL_FLOAT: return sizeof(float);
			case GL_UNSIGNED_INT: return sizeof(uint);
			case GL_UNSIGNED_BYTE: return sizeof(uchar);
			}
			return 0;
		}
	};

	enum class LightType : uint
	{
		//Environment = 0,
		Direction = 0,
		Point
	};

	enum class KeyCode : int
	{
		None = -1,
		Backspace = 259,
		Delete = 261,
		Tab = 258,
		//Clear,
		//Return,
		//Pause,
		Escape = 256,
		Space = 32,
		Keypad0 = 320,
		Keypad1,
		Keypad2,
		Keypad3,
		Keypad4,
		Keypad5,
		Keypad6,
		Keypad7,
		Keypad8,
		Keypad9,
		KeypadDivide = 331,
		KeypadMultiply,
		KeypadMinus,
		KeypadPlus,
		KeypadEnter,
		KeypadEquals,
		UpArrow = 265,
		DownArrow = 264,
		RightArrow = 262,
		LeftArrow,
		Insert = 260,
		Home = 268,
		End,
		PageUp = 266,
		PageDown,
		F1 = 290,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		Alpha0 = 48,
		Alpha1,
		Alpha2,
		Alpha3,
		Alpha4,
		Alpha5,
		Alpha6,
		Alpha7,
		Alpha8,
		Alpha9,
		//Exclaim,
		//DoubleQuote,
		//Hash,
		//Dollar,
		//Percent,
		//Ampersand,
		//Quote,
		//LeftParen,
		//RightParen,
		//Asterisk,
		//Plus,
		//Comma,
		//Minus,
		//Period,
		//Slash,
		//Colon,
		//Semicolon,
		//Less,
		//Equals,
		//Greater,
		//Question,
		//At,
		//LeftBracket,
		//Backslash,
		//RightBracket,
		//Caret,
		//Underscore,
		//BackQuote,
		A = 65,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		//LeftCurlyBracket,
		//Pipe,
		//RightCurlyBracket,
		//Tilde,
		Numlock = 282,
		CapsLock = 280,
		ScrollLock,
		RightShift = 344,
		LeftShift = 340,
		RightControl = 345,
		LeftControl = 341,
		RightAlt = 346,
		LeftAlt = 342,
		//LeftMeta,
		//LeftCommand,
		//LeftApple,
		//LeftWindows,
		//RightMeta,
		//RightCommand,
		//RightApple,
		//RightWindows,
		//AltGr,
		//Help,
		//Print,
		//SysReq,
		//Break,
		//Menu,
		//Mouse0 = 0,
		//Mouse1,
		//Mouse2
	};

	enum class MouseButton : int
	{
		Left = 0,
		Right,
		Mid,
		Button4,
		Button5,
		Button6,
		Button7,
		Button8
	};

	enum class CursorMode : uint
	{
		Normal = 0x00034001,
		Hidden = 0x00034002,
		Disabled = 0x00034003
	};

	enum class KeyState : int
	{
		Released,
		Pressed,
		Repeat,
		//Hold
	};

	typedef std::pair<KeyState, KeyState> KeyStatePair;

	enum class FrameAttatchmentType : uint
	{
		Color0 = 0x8CE0,
		Depth = 0x8D00,
		Stencil = 0x8D20,
		DepthStencil = 0x821A		
	};

	struct CamMatrix
	{
		Matrix4x4 proj;
		Matrix4x4 view;
	};
}