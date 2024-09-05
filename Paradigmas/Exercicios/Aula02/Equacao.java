/* Calcula e imprime as raízes da equação x² + x - 6 = 0 */
/* nome do programa */
class Equacao 
{
	/* programa principal */
	public static void main (String args[]) 
	{
		double x1;
		double x2;
		int delta;
		
		/* b² - 4ac */
		delta = 1 - (4 * 1 * (-6));
		
		x1 = (-1 + Math.sqrt(delta)) / 2;
		x2 = (-1 - Math.sqrt(delta)) / 2;
			
		System.out.printf (" As raízes da equação são %.0f e %.0f%n ", x1, x2);
	}
}
