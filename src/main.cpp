#include <iostream>

#include "Simulation.h"
#include "TestObject.h"

int main()
{
	Simulation sim(800, 600, "Flock Simulation");
	sim.addSimulatable(new TestObject());

	sim.run();

	return 0;
}
