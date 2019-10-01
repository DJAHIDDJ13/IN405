package td1.exo;

import java.util.LinkedList;

/**
 * A FIFO queue for clients.
 */
public class Queue {
	private LinkedList<Client> clients = new LinkedList<Client>();

	public boolean isEmpty() {
		return clients.isEmpty();
	}

	public void addQueueLast(Client client) {
		clients.addLast(client);
	}

	public Client getQueueFirst() {
		return clients.removeFirst();
	}

	public String toString() {
		StringBuffer results = new StringBuffer();
		results.append("Queue : ");
		for (Client client : clients) {
			results.append(client.toString());
		}
		return results.toString();
	}
}
