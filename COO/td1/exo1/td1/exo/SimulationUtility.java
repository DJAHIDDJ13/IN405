package td1.exo;

/**
 * Provides utility static methods for simulation.
 */
public class SimulationUtility {
	public static int getRandomServiceTime(int min, int max) {
		return (int) (Math.random() * (max + 1 - min)) + min;
	}

	public static void printServiceTimeTrace(int currentSystemTime, int serviceTime) {
		System.out.println("Start service for " + serviceTime + " time units.");
	}

	public static void printClientArrival(boolean served) {
		if (served) {
			System.out.println("A new client arrives and is served immediately.");
		} else {
			System.out.println("A new client arrives and joins the queue.");
		}
	}

	public static void printClientDeparture() {
		System.out.println("A client leaves.");
	}

	public static void printBankStat(int currentSystemTime, Bank bank) {
		System.out.println("********** At time : " + currentSystemTime + " **********");
		System.out.println(bank.toString());
	}
}
