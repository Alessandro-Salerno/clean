#pragma once

#define uint unsigned int
#define var auto

/// <summary>
/// throws an unmanageable exception
/// </summary>
/// <param name="functionName">the caller function name</param>
/// <param name="errorMessage">a well-explained reason why the program is crashed</param>
[[noreturn]] void trap(const char* function, const char* error);