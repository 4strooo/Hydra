#include <core/serviceHandler.h>

ServiceHandler* ServiceHandler::instance;

ServiceHandler::ServiceHandler()
{
	instance = this;
	isRunning = true;
	// TODO: Implement a null check so that the first one to be created is the singleton, though the constructor shouldn't be called more than once anyway
}