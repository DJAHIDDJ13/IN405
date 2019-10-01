package td1.exo;

import java.util.ArrayList;
import java.util.List;

/**
 * This class regroup statistic information. It calculates the simulation
 * result.
 */
public class StatisticManager {
	private List<Client> servedClients = new ArrayList<Client>();
	/**
	 * Actual simulation duration.
	 */
	private int simulationDuration = 0;
	/**
	 * Time unit count of occupied cashier. For each unit time, if we have an
	 * occupied cashier, we get this count + 1.
	 */
	private int occupiedCashier = 0;

	public void register(Client client) {
		servedClients.add(client);
	}

	public void simulationDurationRecord() {
		simulationDuration++;
	}

	public void cashierOccupationRecord() {
		occupiedCashier++;
	}

	/**
	 * Calculates the average occupation percentage per cashier.
	 * 
	 * @param cashierCount cashier count
	 * @return occupation percentage
	 */
	public double calculateAverageCashierOccupationRate(int cashierCount) {
		if (cashierCount > 0 && simulationDuration > 0) {
			return (occupiedCashier * 100 / simulationDuration) / cashierCount;
		} else {
			return 0;
		}
	}

	/**
	 * Calculates the average waiting time per client.
	 * 
	 * @return average waiting time
	 */
	public double calculateAverageClientWaitingTime() {
		int clientCount = servedClientCount();

		if (clientCount > 0) {
			int totalWaitingTime = 0;
			for (Client client : servedClients) {
				int serviceStartTime = client.getServiceStartTime();
				int arrivalTime = client.getArrivalTime();
				totalWaitingTime += serviceStartTime - arrivalTime;
			}

			return totalWaitingTime / clientCount;

		} else {
			return 0;
		}
	}

	/**
	 * Calculates the average effective service time per client.
	 * 
	 * @return average service time
	 */
	public double calculateAverageClientServiceTime() {
		int clientCount = servedClientCount();

		if (clientCount > 0) {
			int totalServiceTime = 0;
			for (Client client : servedClients) {
				int departureTime = client.getDepartureTime();
				int serviceStartTime = client.getServiceStartTime();
				totalServiceTime += departureTime - serviceStartTime;
			}
			return totalServiceTime / clientCount;
		} else {
			return 0;
		}
	}

	public int servedClientCount() {
		return servedClients.size();
	}

	public int getSimulationDuration() {
		return simulationDuration;
	}
	
	
}
