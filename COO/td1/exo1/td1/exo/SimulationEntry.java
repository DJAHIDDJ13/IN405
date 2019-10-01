package td1.exo;

/**
 * This class contains a collection of simulation entry parameters.
 */
public class SimulationEntry {
	private int simulationDuration;
	private int cashierCount;
	private int minServiceTime;
	private int maxServiceTime;
	private int clientArrivalInterval;

	public SimulationEntry(int simulationDuration, int cashierCount, int minServiceTime, int maxServiceTime, int clientArrivalInterval) {
		this.simulationDuration = simulationDuration;
		this.cashierCount = cashierCount;
		this.minServiceTime = minServiceTime;
		this.maxServiceTime = maxServiceTime;
		this.clientArrivalInterval = clientArrivalInterval;
	}

	public int getSimulationDuration() {
		return simulationDuration;
	}

	public int getCashierCount() {
		return cashierCount;
	}

	public int getMinServiceTime() {
		return minServiceTime;
	}

	public int getMaxServiceTime() {
		return maxServiceTime;
	}

	public int getClientArrivalInterval() {
		return clientArrivalInterval;
	}
}
