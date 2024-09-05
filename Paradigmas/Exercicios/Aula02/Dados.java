import java.util.Scanner;

class Dados
{
	static public void main (String args[])
	{
		Scanner teclado = new Scanner (System.in);

		System.out.printf (" Digite seu nome: ");
		String nome = teclado.nextLine();
	
		System.out.printf (" Digite o seu time de futebol preferido: ");
		String time = teclado.nextLine();

		System.out.printf (" Digite o bairro onde você mora: ");
		String bairro = teclado.nextLine();
		
		System.out.println ("Nome: " + nome);
		System.out.println ("Time: " + time);
		System.out.println ("Bairro: " + bairro);
	}
}
