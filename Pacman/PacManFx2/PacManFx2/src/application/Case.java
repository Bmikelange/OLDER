package application;

public class Case {
	
	//le type de case
	public int values;
	
	//si elle contient une pacgmme
	public boolean PacGomme;
	
	//si elle contient une superpacgomme
	public boolean SupPacGomme;
	
	
	//le constructeur d'une case
	public Case(int value,boolean SupPacGommes,boolean PacGommes)
	{
		values=value;
		if(SupPacGommes)
		{
			PacGomme=false;
			SupPacGomme=true;
		}
		else if(PacGommes)
			{
				PacGomme=true;
				SupPacGomme=false;
			}
			else
			{
				PacGomme=false;
				SupPacGomme=false;
			}
	}
}
