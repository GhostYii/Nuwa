#include "Time.h"
#include <time.h>
#include <GLFW/glfw3.h>

float Nuwa::Time::GetTime()
{
	return static_cast<float>(glfwGetTime());
}

std::string Nuwa::Time::GetLocalTimeStr()
{
	char buf[20];
	time_t now = time(NULL);
	struct tm* localTime = localtime(&now);
	strftime(buf, sizeof(buf), "%F %X", localTime);
	return buf;
}
