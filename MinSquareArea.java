import java.util.*;
import java.io.*;
import java.lang.Math.*;

// Input format:
// T - test cases
// #--repeat T times--
// N - Qty of Coords (1 <= N <= 10^9)
// @--repeat N times--
// X Y - coords N times
// @--repeat N times--
// K - Qty to Enclose (1 <= K <= N)
// #--repeat T times--

public class Solution{
	
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int testcases = in.nextInt();
		for( int t=1; t<=testcases; t++ ){

			int n = in.nextInt();
			List<Integer> x = new LinkedList<Integer>();
			List<Integer> y = new LinkedList<Integer>();

			for( int u=0; u<n; u++ ){
				x.add(in.nextInt());
				y.add(in.nextInt());
			}

			int k = in.nextInt();

			int out = find_min_area(x, y, k, n);
		
			System.out.println("Case #"+t+": "+out+"\n");
		}
	}

	public static Integer find_min_area( List<Integer> arX, List<Integer> arY, int K, int N ){
		List<Integer> difX = new LinkedList<Integer>();
		List<Integer> difY = new LinkedList<Integer>();

		difX = difference(arX);
		difY = difference(arY);

		for( int m=0; m < (N-K); m++ ){
			int dex = find_max_both(difX, difY);
			difX.remove(dex);
			difY.remove(dex);
			arX.remove(dex);
			arY.remove(dex);
		}

		int maxX = find_max(arX)+2;
		int minX = find_min(arX);

		int maxY = find_max(arY)+2;
		int minY = find_min(arY);

		int valX = (maxX-minX);
		int valY = (maxY-minY);

		int area = 0;

		if( valX > valY ){
			area = valX*valX;
		}

		if( valX <= valY ){
			area = valY*valY;
		}

		return area;
	}

	public static List<Integer> difference( List<Integer> in ){
		List<Integer> diff = new LinkedList<Integer>();
		for( int h = 0; h<in.size(); h++){
			diff.add(0);
		}
		for( int i=0; i<in.size(); i++ ){
			for( int j = i; j<in.size(); j++ ){
				
				int temp = Math.abs(in.get(i)-in.get(j));
				diff.set( i, (diff.get(i) + temp) );
				diff.set( j, (diff.get(j) + temp) );

			}
		}

		return diff;
	}

	public static Integer find_max_both( List<Integer> dX, List<Integer> dY ){
		int largest = dX.get(0);
		int index = 0;

		for( int p=0; p<dX.size(); p++ ){
			if( largest < dX.get(p) ){
				largest = dX.get(p);
				index = p;
			}
		}

		for( int q=0; q<dY.size(); q++ ){
			if( largest < dY.get(q) ){
				largest = dY.get(q);
				index = q;
			}		
		}

		return index;
	}

	public static Integer find_max( List<Integer> in ){
		int largest = in.get(0);

		for( int r=0; r<in.size(); r++ ){
			if( largest < in.get(r) ){
				largest = in.get(r);
			}
		}

		return largest;
	}

	public static Integer find_min( List<Integer> in ){
		int smallest = in.get(0);

		for( int s=0; s<in.size(); s++ ){
			if( smallest > in.get(s) ){
				smallest = in.get(s);
			}
		}

		return smallest;
	}
}