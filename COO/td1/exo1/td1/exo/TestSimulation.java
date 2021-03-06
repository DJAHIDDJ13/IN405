package td1.exo;

/**
 * Test simulation.
 */
public class TestSimulation {
	private static final int CLIENT_ARRIVAL_INTERVAL = 5;
	private static final int MAX_SERVICE_TIME = 20;
	private static final int MIN_SERVICE_TIME = 10;
	private static final int CASHIER_COUNT = 3;
	private static final int SIMULATION_DURATION = 10;

	public static void main(String[] args) {
		SimulationEntry simulationEntry = new SimulationEntry(SIMULATION_DURATION, CASHIER_COUNT, MIN_SERVICE_TIME, MAX_SERVICE_TIME, CLIENT_ARRIVAL_INTERVAL);
		Simulation simulation = new Simulation(simulationEntry);
		simulation.simulate();
		System.out.println(simulation.simulationResults());
	}
}
