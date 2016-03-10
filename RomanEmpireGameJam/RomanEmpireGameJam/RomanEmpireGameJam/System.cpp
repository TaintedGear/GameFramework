#include "System.h"

System::System()
{
}

//------------------------------------------//
// System::~System				
//------------------------------------------//
System::~System()
{
	ShutdownSystem();
}

//------------------------------------------//
// System::StartupSystem				
//------------------------------------------//
bool System::StartupSystem()
{
	return true;
}

//------------------------------------------//
// System::ShutdownSystem				
//------------------------------------------//
void System::ShutdownSystem()
{

}
