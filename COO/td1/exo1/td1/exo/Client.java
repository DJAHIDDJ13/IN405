package td1.exo;

/**
 * We need to know when a client arrives, when the service starts and finishes.
 * When creating the client, only his arrival time can be defined.
 */
public class Client {
	private int arrivalTime;
	private int serviceStartTime;
	private int departureTime;

	public Client(int arrivalTime) {
		this.arrivalTime = arrivalTime;
	}

	public int getArrivalTime() {
		return arrivalTime;
	}

	public int getDepartureTime() {
		return departureTime;
	}

	public void setDepartureTime(int departureTime) {
		this.departureTime = departureTime;
	}

	public int getServiceStartTime() {
		return serviceStartTime;
	}

	public void setServiceStartTime(int serviceStartTime) {
		this.serviceStartTime = serviceStartTime;
	}
	
	public String toString() {
		return "Client[arrival : " + arrivalTime + "] "; 
	}
}
