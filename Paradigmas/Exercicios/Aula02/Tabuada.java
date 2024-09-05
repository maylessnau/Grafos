/* Imprime a tabuada do 6 */
class Tabuada
{
	public static void main(String args[])
	{
		int i;
		int result;

		for (i = 1; i <= 10; i++) 
		{
			result = i * 6;
			System.out.printf ("%d x 6 = %d%n", i, result);
		}		
	}
}
