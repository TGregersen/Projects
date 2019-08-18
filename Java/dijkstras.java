/*dijkstras*/

class node{
	public int tenative;
	public int length;
	public boolean visited;
	LinkedList<node> neighbors;
}

// Set all nodes to unvisited. Add to list.
// Set tenative dist val 0 for initial, infinite for others.

public static class Solution{
	LinkedList<node> unvisited;

	public static void main(string Args[]){
		take input
		unvisited.push(input)
		unvisited[input].neighbors.add()
	}
	

	int iterate_through_list_from(node start){

		for (unvisited.size() != 0){
			for(nd in unvisited){
				if(nd.tenative<lowest.tenative){
					lowest = nd;
				}
			}

			if(Select_smallest_tenative_node(lowest)){
				break;
			}
		}

		return lowest.tenative;
	}

	boolean Select_smallest_tenative_node(node current){
		if (current.tentative == infinite){
			return true;
		}
		if (node.visited == true){  // Alternatively can check for end node (such as number or coord)
			for (neighbor in current.neighbors[]){
				if(neighbor.visited == false){
					int temp = Current.tenative + Neighbor.length;
					if (temp < neighbor.tenative){
						neighbor.tenative = temp;
					}
				}
			}
			current.visited = true;
			unvisited.remove(current);
		}else{
			return true;
		}
	}
}