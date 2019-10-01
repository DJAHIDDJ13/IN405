package td1.exo;

/**
 * System simulation. Access point of all related information.
 */
public class Simulation {
	private Bank bank;
	private StatisticManager statisticManager;
	private SimulationEntry systemEntry;
	
	public Simulation(SimulationEntry simulationEntry) {
		this.systemEntry = simulationEntry;
		int cashierCount = simulationEntry.getCashierCount();
		bank = new Bank(cashierCount);
		statisticManager = new StatisticManager();
	}
	
	/**
	 * This is the main simulation process, that products simulation results.
	 * 
	 * TODO Complete this method. 
	 * Do not program all in this method.
	 * Try to split work in different private methods and call them in this method.
	 */
	public void simulate() {
		for(int currentSystemTime = 0; currentSystemTime < systemEntry.getSimulationDuration(); currentSystemTime++) {
			SimulationUtility.printBankStat(currentSystemTime, bank);
			
			Queue clientQueue = bank.getQueue();
			
			// A new client arrives
			if(currentSystemTime % systemEntry.getClientArrivalInterval() == 0) {
				boolean isServedImmediately = clientQueue.isEmpty() && bank.getFreeCashier() != null;
				SimulationUtility.printClientArrival(isServedImmediately);

				Client arrivingClient = new Client(currentSystemTime);
				clientQueue.addQueueLast(arrivingClient);
			}
			
			// sort out the cashiers
			for(Cashier cashier: bank.getCashiers()) {
				if(cashier.isFree()) {
					if(!clientQueue.isEmpty()) {
						Client servingClient = clientQueue.getQueueFirst();
						int randomServiceTime = SimulationUtility.getRandomServiceTime(systemEntry.getMinServiceTime(), 
					 			   													   systemEntry.getMaxServiceTime());
						cashier.serve(servingClient, randomServiceTime);						
					}
				} else {
					cashier.work();
				}
				
				// Client departs
				if(cashier.serviceFinished()) {
					SimulationUtility.printClientDeparture();
				}
			}
		}
	}

	public String simulationResults() {
		StringBuffer results = new StringBuffer();
		results.append("########## Simulation results : ##########\n");
		results.append("Simulation Duration : " + statisticManager.getSimulationDuration() + "\n");
		results.append("Served client count : " + statisticManager.servedClientCount() + "\n");
		results.append("Average client waiting time : " + statisticManager.calculateAverageClientWaitingTime() + " \n");
		results.append("Average client service time : " + statisticManager.calculateAverageClientServiceTime() + " \n");
		results.append("Cashier occupation rate : "
				+ statisticManager.calculateAverageCashierOccupationRate(systemEntry.getCashierCount()) + " %");
		return results.toString();
	}
}
