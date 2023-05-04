#include "RayTracer.h"
#include <thread>

int main() 
{
	RayTracer* app = new RayTracer();
	
	app->runWithDebugInfo();

	//std::thread rayTracer(&RayTracer::run, app, true);
	//rayTracer.join();
}