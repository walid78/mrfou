public class Test{
		
		public static String affiche(int i, int j){
				if(i==0 && j==0)
						return "T";
				else if(j>i)
						return "F";
				else
						return "[("+affiche(i-1,j)+" AND -bi) OR ("+affiche(i-1,j-1)+" AND bi)]";
		}

		public static void main(String[] args){
				int n,k;
				n = Integer.parseInt(args[0]);
				k = Integer.parseInt(args[1]);

				String[][] c = new String[n+1][k+1];

				for(int i=0 ; i<c.length ; i++)
						for(int j=0 ; j<c[i].length ; j++)
								c[i][j] = "test";
				
				
				for(int i=n ; i>0 ; --i){
						System.out.print("[");

						for(int j=Math.min(k,i) ; j>=0 ; --j){
								System.out.print("(c"+i+","+j+" AND [(c"+(i-1)+","+j+" AND (");

								for(int l=Math.min(k,i-1) ; l>=0 ; --l){
										if(l!=j){
												System.out.print("not c"+(i-1)+","+l);
												if(l!=0)
														System.out.print(" AND ");
										}
								}

								System.out.print(") AND not b"+i+") OR (c"+(i-1)+","+(j-1)+" AND (");
								
								for(int l=Math.min(k,i-1) ; l>=0 ; --l){
										if(l!=j-1){
												System.out.print("not c"+(i-1)+","+l);
												if(l!=0)
														System.out.print(" AND ");
										}
								}
								
								System.out.print(") AND b"+i+")])");

								if(j != 0)
										System.out.println(" OR ");

						}
						if(i > 1)
								System.out.println("] AND ");

				}
				System.out.println();
		}
}